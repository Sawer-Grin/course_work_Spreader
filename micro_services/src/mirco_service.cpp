#include <iostream>
#include <pqxx/pqxx>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>

#include "./settings/settigns.hpp"
#include "./Cleaner/cleaner.hpp"
#include "./Compressor/compressor.hpp"
#include "./Decompressor/decompressor.hpp"

std::vector<Service*> list_of_services(
    const char* url_db, const char* path_to_temp_dir,
    const char* path_to_main_dir, const char* password
) {
    std::vector<Service*> list(0);

    Service* temp = new Cleaner(config_service::time_sleeping_cleaner,
        path_to_main_dir, url_db
    );
    list.push_back(temp);
    temp = new Compressor( config_service::default_time_sleeping,
        path_to_main_dir, path_to_temp_dir, url_db, password
    );
    list.push_back(temp);
    temp = new Decompressor(config_service::default_time_sleeping,
        path_to_main_dir, path_to_temp_dir, url_db, password
    );
    list.push_back(temp);
    return list;
}

int main(int argc, char* argv[]) {
    default_settings();
    auto zipper_password = get_zipper_password();

    auto url = url_for_database();
    auto services = list_of_services(
        url.c_str(), config_service::path_to_temp_dir,
        config_service::path_to_main_dir, "password");
    std::vector<boost::thread*> threads;
    for(auto service: services) {
        threads.push_back(service->run());
    }
    std::cout << "Main thread." << std::endl;
    for(auto thread: threads) {
        thread->join();
    }

    std::cout << "All threads have finished work" << std::endl;
    return 0;
}