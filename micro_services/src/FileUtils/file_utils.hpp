#ifndef FILE_UTILS_DEFINE
#define FILE_UTILS_DEFINE

#define function_adding(adding)  std::string (*adding)(const std::string&)

#include <iostream>
#include <filesystem>

#include "../settings/settigns.hpp"

namespace file_utils {
    std::string to_zip(const std::string& path_to_folder);
    std::string to_folder(const std::string& path_to_folder);
    bool delete_folder(const char* name_service, const std::string& path_to_folder);
    std::string subtract_folder_uuid(const std::string& path_folder,
        const std::string& uuid_as_folder, function_adding(adding));
}

#endif
