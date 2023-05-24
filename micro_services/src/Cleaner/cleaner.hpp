#include "../service.hpp"
#include "../Requests/requests.hpp"
#include "../settings/settigns.hpp"
#include "../FileUtils/file_utils.hpp"

#include <filesystem>

class Cleaner: public Service {
    public:
        Cleaner() : Service(0) {};
        Cleaner(
            const int time_for_sleep,
            const char* path_to_dir, const char* db_url
        ): Service(time_for_sleep) {
            this->path_to_main = std::string(path_to_dir);
            this->db_url = std::string(db_url);
        };
        ~Cleaner();

        boost::thread* run() override {
            return new boost::thread(&Cleaner::task, this);
        }

        // temp
        const std::string name_service = std::string("Cleaner: ");

    protected:
        // Path to main storage
        std::string path_to_main;
        std::string db_url;
        boost::thread cur_thread;
        const char* name_of_service = "Cleaner";

        void task() override;
        inline void iteration_of_task(std::shared_ptr<pqxx::connection> conn) override;
        bool delete_unnecessary_folder(std::string uuid_as_folder);
};