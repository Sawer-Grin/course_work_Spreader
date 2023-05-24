#include "./compression.hpp"

const char* postfix_zip = ".zip";
const char* postfix_folder = "/";

bool compression_alg::compress(
    const char* name_of_service, const std::string& path_from,
    const std::string& path_to, const char* password
) {
    print_log(name_of_service, 4,
        "Start compression from -- ", path_from.c_str(),
        " -- to -- ", path_to.c_str());
    bool status_operation = true;

    try {
        zipper::Zipper zipper(path_to, password);
        zipper.add(path_from);
        zipper.close();
    } catch (std::runtime_error const& e) {
        print_log(name_of_service, 2,
            "Error in decompress: ", e.what());
        status_operation = false;
    }
    return status_operation;
}

bool compression_alg::decompress(
    const char* name_of_service, const std::string& path_from,
    const std::string& path_to, const char* password
) {
    print_log(name_of_service, 4,
        "Start decompression from -- ", path_from.c_str(),
        " -- to -- ", path_to.c_str());
    bool status_operation = true;
    try {
        zipper::Unzipper unzipper(path_from, password);
        unzipper.extract(path_to);
        unzipper.close();
    } catch (std::runtime_error const& e){
        print_log(name_of_service, 2,
            "Error in decompress: ", e.what());
        status_operation = false;
    }
    return status_operation;
}
