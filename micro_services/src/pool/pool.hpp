#ifndef POOL_DEFINE
#define POOL_DEFINE

#include<boost/thread.hpp>

class Pool {
    public:
        Pool(): all_threads{0} {};
        ~Pool();
        void add_new_thread(boost::thread* new_thread);

    private:
        std::vector<boost::thread*> all_threads;
}

#endif /* POOL_DEFINE */
