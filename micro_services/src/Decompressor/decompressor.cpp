#include "./decompressor.hpp"

void Decompressor::task() {
    try {
        auto connection = db_utils::connect_to_db(db_url, name_of_service);
        while (true) {
            this->iteration_of_task(connection);
        }
        connection->disconnect();
    } catch(const std::exception& error) {
        print_log(name_of_service, 3,
            "Error: ", error.what(), " Finish work of service.");
    }
}

inline void Decompressor::iteration_of_task(std::shared_ptr<pqxx::connection> conn) {
    using namespace db_enums;

    auto list_of_uuids = db_requests::get_directories_by_status(
        conn, FileStatus::Unclenched, this->name_of_service
    );

    for(auto const& uuid_as_name_of_folder: list_of_uuids) {
        if (!this->process_folder(uuid_as_name_of_folder)) {
            print_log(name_of_service, 2,
                "Problem with decompress folder -- ",
                uuid_as_name_of_folder.uuid.c_str());
        }
    }

    auto result_of_updating = db_requests::set_folders_status(
        conn, name_of_service, list_of_uuids, FileStatus::ReadyToSend);
    if (!result_of_updating) {
        print_log(name_of_service, 1, "Problem with updating value");
    }

    boost::this_thread::sleep_for(
        boost::chrono::seconds(config_service::default_time_sleeping)
    );
}

bool Decompressor::process_folder(const UuidDirectories& uuid_as_folder) {
    auto path_to = file_utils::subtract_folder_uuid(path_to_temp, uuid_as_folder.uuid,
        file_utils::to_folder);
    auto path_from = file_utils::subtract_folder_uuid(path_to_main, uuid_as_folder.uuid,
        file_utils::to_zip);
    return compression_alg::decompress(name_of_service, path_from, path_to,
        password.c_str());
}

Decompressor::~Decompressor() {
    std::cout << "Finish work Scrambler" << std::endl;
}
