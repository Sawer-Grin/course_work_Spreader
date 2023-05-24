#include "./requests.hpp"

/*
 +-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 |P|r|i|v|a|t|e| |f|u|n|c|t|i|o|n|
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |i|n| |m|o|d|u|l|e|
 +-+-+ +-+-+-+-+-+-+
*/

inline pqxx::result::size_type update_status(
    std::shared_ptr<pqxx::work> transaction,
    const db_enums::FileStatus& new_status,
    const std::string& uuid
) {
    auto sql =
        "UPDATE file_storage            "
        "SET status = $1::status_files  "
        "WHERE uuid = $2::uuid;         ";
    return transaction->exec_params(
        sql, db_enums::to_string(new_status), uuid
    ).affected_rows();
}

inline void print_uuid_struct(
    const std::vector<UuidDirectories>& list_of_uuid,
    const char* name_of_service
){
    if (!list_of_uuid.empty()) {
        std::cout << "Print UuidDirectories for service: " << name_of_service \
            << std::endl;
        for (auto& uuid: list_of_uuid) {
            print_log(name_of_service, 2,
                "UUID: ", uuid.uuid.c_str());
        }
        std::cout << "Finished printing for service: " << name_of_service \
            << std::endl;
    }
}

inline bool check_connection(
    std::shared_ptr<pqxx::connection> pool,
    const char* name_of_service
) {
    bool result = true;
    if (!pool->is_open()) {
        print_log(name_of_service, 1,
            "Can't open database");
        result = false;
    }
    return result;
}

/*
  _____                    __  .__                        .__  __  .__
_/ ____\_ __  ____   _____/  |_|__| ____   ____   __  _  _|__|/  |_|  |__
\   __\  |  \/    \_/ ___\   __\  |/  _ \ /    \  \ \/ \/ /  \   __\  |  \
 |  | |  |  /   |  \  \___|  | |  (  <_> )   |  \  \     /|  ||  | |   Y  \
 |__| |____/|___|  /\___  >__| |__|\____/|___|  /   \/\_/ |__||__| |___|  /
                 \/     \/                    \/                        \/
                                             __
_______   ____  ________ __   ____   _______/  |_
\_  __ \_/ __ \/ ____/  |  \_/ __ \ /  ___/\   __\
 |  | \/\  ___< <_|  |  |  /\  ___/ \___ \  |  |
 |__|    \___  >__   |____/  \___  >____  > |__|
             \/   |__|           \/     \/
*/

std::vector<UuidDirectories> db_requests::get_directories_by_status(
    std::shared_ptr<pqxx::connection> pool,
    const db_enums::FileStatus& status,
    const char* name_of_service
) {
    check_connection(pool, name_of_service);
    auto sql =
        "SELECT uuid FROM file_storage      "
        "WHERE status = $1::status_files;   ";

    pqxx::work transaction(*pool);
    pqxx::result result_of_request = transaction.exec_params(
        sql, db_enums::to_string(status)
    );
    transaction.commit();

    auto uuids = process_result::from_result(result_of_request);
    print_uuid_struct(uuids, name_of_service);
    return uuids;
}

bool db_requests::set_folders_status(
    std::shared_ptr<pqxx::connection> pool, const char* name_of_service,
    const std::vector<UuidDirectories>& uuids_as_dirs,
    const db_enums::FileStatus& new_status
) {
    print_log(name_of_service, 1, "Start setting new status");
    bool is_ok = check_connection(pool, name_of_service);
    if (!is_ok) {
        return is_ok;
    }
    auto transaction = std::make_shared<pqxx::work>(*pool);
    auto uuids = db_utils::to_uuids(uuids_as_dirs);

    pqxx::result::size_type affected_rows = 0,
        before_updating = uuids_as_dirs.size();
    for(auto const &uuid: uuids) {
        affected_rows += update_status(transaction, new_status, uuid);
    }
    transaction->commit();

    if (affected_rows < before_updating) {
        print_log(
            name_of_service, 2,
            "Problem with updating values for new status -- ",
            db_enums::to_string(new_status).c_str()
        );
        is_ok = false;
    }
    return is_ok;
}

bool db_requests::set_folder_status(
    std::shared_ptr<pqxx::connection> pool, const char* name_of_service,
    const UuidDirectories& uuids_as_dir, const db_enums::FileStatus& new_status
) {
    print_log(name_of_service, 1, "Start setting new status");
    bool is_ok = check_connection(pool, name_of_service);
    if (!is_ok) {
        return is_ok;
    }

    auto transaction = std::make_shared<pqxx::work>(*pool);
    auto affected_rows = update_status(
        transaction, new_status, uuids_as_dir.uuid
    );
    transaction->commit();

    print_log(name_of_service, 2, "Amount of affected rows -- ",
        std::to_string(affected_rows).c_str()
    );
    if (affected_rows == 0) {
        print_log(name_of_service, 2,
            "Problem with updating values for new status -- ", 
            db_enums::to_string(new_status).c_str());
        is_ok = false;
    }
    return is_ok;
}

std::vector<UuidDirectories> db_requests::get_uuids_over(
    std::shared_ptr<pqxx::connection> pool,
    const char* name_of_service
) {
    if (check_connection(pool, name_of_service)) {
        return std::vector<UuidDirectories>(0);
    }
    auto sql =  
        "SELECT uuid FROM file_storage  "
        "WHERE last_moment <= now();    ";
    pqxx::work transaction(*pool);
    pqxx::result result_of_request = transaction.exec(sql);
    transaction.commit();

    auto uuids = process_result::from_result(result_of_request);
    print_uuid_struct(uuids, name_of_service);
    return uuids;
}

/*
        __  .__.__             _____
 __ ___/  |_|__|  |   ______ _/ ____\___________
|  |  \   __\  |  |  /  ___/ \   __\/  _ \_  __ \
|  |  /|  | |  |  |__\___ \   |  | (  <_> )  | \/
|____/ |__| |__|____/____  >  |__|  \____/|__|
                         \/
    .___       __        ___.                                               __
  __| _/____ _/  |______ \_ |__ _____    ______ ____   __  _  _____________|  | __
 / __ |\__  \\   __\__  \ | __ \\__  \  /  ___// __ \  \ \/ \/ /  _ \_  __ \  |/ /
/ /_/ | / __ \|  |  / __ \| \_\ \/ __ \_\___ \\  ___/   \     (  <_> )  | \/    <
\____ |(____  /__| (____  /___  (____  /____  >\___  >   \/\_/ \____/|__|  |__|_ \
     \/     \/          \/    \/     \/     \/     \/                           \/
*/

std::shared_ptr<pqxx::connection> db_utils::connect_to_db(std::string url,
    const char* name_of_service
) { 
    std::shared_ptr<pqxx::connection> pool;
    while (true) {
        pool = std::make_shared<pqxx::connection>(url);
        if (pool->is_open()) {
            std::cout << name_of_service << ": " \
                << "Open connection to db successfully" << std::endl;
            break;
        }
        std::cout << "Problem with establishing connection" << std::endl;
        boost::this_thread::sleep_for(
            boost::chrono::seconds(
                config_db::period_between_connection
            )
        );
    }
    return pool;
}

inline std::vector<UuidDirectories> process_result::from_result(
    const pqxx::result& result_of_request
) {
    std::vector<UuidDirectories> list_of_uuids(0);
    for (auto const &row: result_of_request) {
        list_of_uuids.push_back(
            UuidDirectories{ uuid: std::string(row[0].c_str()) }
        );
    }
    return list_of_uuids;
}

inline std::vector<std::string> db_utils::to_uuids(
    const std::vector<UuidDirectories>& uuid_as_directories
) {
    std::vector<std::string> list_uuids(0);
    for (auto const& uuid_as_directory: uuid_as_directories) {
        list_uuids.push_back(uuid_as_directory.uuid);
    }
    return list_uuids;
}
