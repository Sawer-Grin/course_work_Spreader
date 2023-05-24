#include "../service.hpp"
#include "../settings/settigns.hpp"
#include "../Requests/requests.hpp"
#include "../Compression/compression.hpp"
#include "../FileUtils/file_utils.hpp"

class Compressor: public Service {
    public:
        Compressor(): Service(0) { };
        Compressor(
            const int time_for_sleep, const char* path_to_storage,
            const char* path_to_temp_dir, const char* url_db, const char* pass
        ): Service(time_for_sleep) {
            this->path_to_main = std::string(path_to_storage);
            this->path_to_temp = std::string(path_to_temp_dir);
            this->db_url = std::string(url_db);
            this->password = std::string(pass);
        };
        ~Compressor();

        boost::thread* run() override {
            return new boost::thread(&Compressor::task, this);
        }

    private:
        std::string path_to_main;
        std::string db_url;
        // Path to temp storage
        std::string path_to_temp;
        std::string password;
        const char* name_of_service = "Compressor";

        void task() override;
        inline void iteration_of_task(std::shared_ptr<pqxx::connection> conn) override;
        bool process_folder(const UuidDirectories& uuid_as_folder);
};