#include "./file_utils.hpp"

static const char* postfix_zip = ".zip";
static const char* postfix_folder = "/";

std::string file_utils::to_zip(const std::string& path_to_folder) {
    std::string path = path_to_folder;
    path.append(postfix_zip);
    return path;
}

std::string file_utils::to_folder(const std::string& path_to_folder) {
    std::string path = path_to_folder;
    path.append(postfix_folder);
    return path;
}

bool file_utils::delete_folder(const char* name_of_service,
    const std::string& path_to_folder
) {
    namespace fs = std::filesystem;

    print_log(name_of_service, 2,
        "Start deleting folder: ", path_to_folder.c_str());

    bool result_of_operation = true;
    fs::path folder_with_info = path_to_folder;

    if (!fs::exists(folder_with_info)) {
        print_log(name_of_service, 2,
            "Try to delete not existing folder path to folder -- ",
            folder_with_info.c_str());
        result_of_operation = false;
    }

    auto amount_deleted_files = fs::remove_all(folder_with_info);
    print_log(name_of_service, 4,
        "for folder -- ", folder_with_info.c_str(), " -- amount of deleted files -- ",
        std::to_string(amount_deleted_files).c_str());
    if (amount_deleted_files == 0) {
        result_of_operation = false;
    }

    return result_of_operation;
}

std::string file_utils::subtract_folder_uuid(const std::string& path_folder,
        const std::string& uuid_as_folder, function_adding(adding)
){
    std::string needed_path(path_folder);
    needed_path.append(uuid_as_folder);
    return adding(needed_path);
}

