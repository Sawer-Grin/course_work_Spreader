#ifndef CONFIG_DEFINE
#define CONFIG_DEFINE

#include <iostream>
#include <string>

#include <stdlib.h>
#include <stdarg.h>

#include <pqxx/pqxx>
#include <pqxx/strconv>

namespace name_env {
    static const char* pg_user = "DB_USER";
    static const char* pg_password = "DB_PASSWORD";
    static const char* pg_host = "DB_HOST";
    static const char* pg_port = "DB_PORT";
    static const char* pg_db = "DB_NAME";
    static const char* zipper_password = "ZIPPER_PASSWORD";
}

namespace config_db {
    static const int period_between_connection = 20;
}

namespace config_service {
    // Should be 1 hour
    static const int time_sleeping_cleaner = 12;
    static const int default_time_sleeping = 3; // set some timeout for batching
    static const char* path_to_main_dir = "./uploads/";
    static const char* path_to_temp_dir = "./temp/";
}

namespace db_enums {
    enum FileStatus{
        Uploaded, Compressing, Saved, Unclenched, ReadyToSend, Deleted
    };
    std::string to_string(const FileStatus& status);
}

void default_settings();
void problem_with_env(const char* name_env);
std::string url_for_database();
void print_log(const char* name_of_service, int amount_of_messages, ...);
std::string subtract_folder_uuid(const std::string& path_folder,
    const std::string& uuid_as_folder);
std::string get_zipper_password();

#endif
