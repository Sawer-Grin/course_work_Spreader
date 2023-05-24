#include "./settigns.hpp"

/*
 +-+-+-+-+ +-+-+-+-+ +-+-+-+ +-+-+-+-+-+-+-+-+-+
 |M|e|t|a| |d|a|t|a| |f|o|r| |a|l|g|o|r|i|t|h|m|
 +-+-+-+-+ +-+-+-+-+ +-+-+-+ +-+-+-+-+-+-+-+-+-+
*/

const char* adding_for_log = ": ";

/*
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |i|m|p|l|e|m|e|n|t|a|t|i|o|n|
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

void default_settings() {
    #ifdef USED_DOCKER
        std::ios_base::Init();
    #endif
}

void problem_with_env(const char* name_env) {
    printf("Problem with getting env. Name env: %s\n", name_env);
    exit(1);
}

std::string url_for_database() {
    std::string url("postgresql://");

    char* env_variable = getenv(name_env::pg_user);
    if (env_variable != nullptr) {
        url.append(env_variable);
        url.push_back(':');
    } else { problem_with_env(name_env::pg_user); }

    env_variable = getenv(name_env::pg_password);
    if (env_variable != nullptr) {
        url.append(env_variable);
        url.push_back('@');
    } else { problem_with_env(name_env::pg_password); }

    env_variable = getenv(name_env::pg_host);
    if (env_variable != nullptr) {
        url.append(env_variable);
        url.push_back(':');
    } else { problem_with_env(name_env::pg_host); }

    env_variable = getenv(name_env::pg_port);
    if (env_variable != nullptr) {
        url.append(env_variable);
        url.push_back('/');
    } else { problem_with_env(name_env::pg_port); }

    env_variable = getenv(name_env::pg_db);
    if (env_variable != nullptr) {
        url.append(env_variable);
    } else { problem_with_env(name_env::pg_db); }

    printf("Created url: %s\n", url.c_str());

    return url;
}

std::string db_enums::to_string(const FileStatus& status) {
    using namespace db_enums;
    std::string as_string = "";
    switch (status)
    {
        case FileStatus::Uploaded:
            as_string += "Uploaded";
            break;
        case FileStatus::Compressing:
            as_string += "Compressing";
            break;
        case FileStatus::Saved:
            as_string += "Saved";
            break;
        case FileStatus::Unclenched:
            as_string += "Unclenched";
            break;
        case FileStatus::ReadyToSend:
            as_string += "ReadyToSend";
            break;
        case FileStatus::Deleted:
            as_string += "Deleted";
            break;
    };
    return as_string;
}

void print_log(const char* name_of_service, int amount_of_messages, ...) {
    va_list list_of_messages;
    va_start(list_of_messages, amount_of_messages);
    std::string all_log(name_of_service);
    all_log.append(adding_for_log);

    for (int i = 0; i < amount_of_messages; ++i)
        all_log.append(va_arg(list_of_messages, const char*));

    va_end(list_of_messages);
    std::cout << all_log << std::endl;
}


std::string get_zipper_password() {
    char* env_variable = getenv(name_env::zipper_password);
    if (env_variable != nullptr) {
    } else { problem_with_env(name_env::zipper_password); }

    return std::string(env_variable);
}