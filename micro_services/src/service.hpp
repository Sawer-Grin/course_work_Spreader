#ifndef SERVICE_DEFINE
#define SERVICE_DEFINE

#include <pqxx/pqxx>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/thread.hpp>
#include <iostream>

#include "./settings/settigns.hpp"

class Service {
    public:
        Service(): time_for_sleep{0} {};
        Service(const int time_for_sleep): time_for_sleep{time_for_sleep} {};
        virtual ~Service() {};

        virtual boost::thread* run() = 0;

    protected:
        int time_for_sleep;
        const char* name_of_service;

        virtual void task() = 0;
        virtual inline void iteration_of_task(std::shared_ptr<pqxx::connection> conn) = 0;
};

#endif /* SERVICE_DEFINE */
