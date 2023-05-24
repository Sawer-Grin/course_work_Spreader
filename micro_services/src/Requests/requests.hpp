#ifndef DB_REQUESTS
#define DB_REQUESTS

#include <iostream>
#include <memory>

#include <pqxx/pqxx>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>

#include "../settings/settigns.hpp"

struct UuidDirectories {
    std::string uuid;
} typedef UuidDirectories;

namespace db_requests {
    std::vector<UuidDirectories> get_directories_by_status(
        std::shared_ptr<pqxx::connection> pool, const db_enums::FileStatus& status,
        const char* name_of_service
    );

    std::vector<UuidDirectories> get_uuids_over(
        std::shared_ptr<pqxx::connection> pool, const char* name_of_service
    );

    bool set_folders_status(
        std::shared_ptr<pqxx::connection> pool, const char* name_of_service,
        const std::vector<UuidDirectories>& uuids, const db_enums::FileStatus& new_status
    );

    bool set_folder_status(
        std::shared_ptr<pqxx::connection> pool, const char* name_of_service,
        const UuidDirectories& uuids, const db_enums::FileStatus& new_status
    );
}

namespace process_result {
    inline std::vector<UuidDirectories> from_result(
        const pqxx::result& result_of_request
    );
}

namespace db_utils {
    std::shared_ptr<pqxx::connection> connect_to_db(
        std::string url, const char* name_of_service
    );
    inline std::vector<std::string> to_uuids(
        const std::vector<UuidDirectories>& uuid_as_directories
    );
}

#endif