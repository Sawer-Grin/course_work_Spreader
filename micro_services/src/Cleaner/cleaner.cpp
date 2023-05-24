#include "./cleaner.hpp"

void Cleaner::task() {
    try {
        auto connection = db_utils::connect_to_db(db_url, name_of_service);
        while (true) {
            this->iteration_of_task(connection);
        }
        connection->disconnect();
    } catch (const std::exception& error) {
        print_log(name_of_service, 3,
            "Error: ", error.what(), " Finish work of service.");
    }
}

inline void Cleaner::iteration_of_task(std::shared_ptr<pqxx::connection> conn) {
    using namespace db_enums;
    
    auto list_of_uuids = db_requests::get_uuids_over(conn, name_of_service);

    for(auto const& uuid_as_name_folder: list_of_uuids) {
        if (!this->delete_unnecessary_folder(uuid_as_name_folder.uuid)) {
            print_log(name_of_service, 2,
                "Problem with deleting folder -- ",
                uuid_as_name_folder.uuid.c_str());
        }
    }

    auto result_of_request = db_requests::set_folders_status(conn, 
        name_of_service, list_of_uuids, FileStatus::Deleted);

    boost::this_thread::sleep_for(
        boost::chrono::seconds(config_service::time_sleeping_cleaner)
    );
}

bool Cleaner::delete_unnecessary_folder(std::string uuid_as_folder){
    auto path_to = file_utils::subtract_folder_uuid(path_to_main, uuid_as_folder,
        file_utils::to_folder);
    return file_utils::delete_folder(name_of_service, path_to);
}

Cleaner::~Cleaner() {
    std::cout << "Finish work Cleaner()" << std::endl;
}