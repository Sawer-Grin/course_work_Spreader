#include "../service.hpp"
#include "../Requests/requests.hpp"
#include "../settings/settigns.hpp"
#include "../Compression/compression.hpp"
#include "../FileUtils/file_utils.hpp"

class Decompressor: public Service {
    public:
        Decompressor(): Service(0) { };
        Decompressor(
            const int time_for_sleep, const char* path_to_storage,
            const char* path_to_temp_dir, const char* url_db, const char* pass
        ): Service(time_for_sleep) {
            this->path_to_main = std::string(path_to_storage);
            this->path_to_temp = std::string(path_to_temp_dir);
            this->db_url = std::string(url_db);
            this->password = std::string(pass);
        };
        ~Decompressor();

        boost::thread* run() override {
            return new boost::thread(&Decompressor::task, this);
        }

    private:
        std::string path_to_main;
        std::string db_url;
        std::string path_to_temp;
        std::string password;
        const char* name_of_service = "Decompressor";

        void task() override;

        bool process_folder(const UuidDirectories& uuid_as_folder);
        inline void iteration_of_task(std::shared_ptr<pqxx::connection> conn) override;
};