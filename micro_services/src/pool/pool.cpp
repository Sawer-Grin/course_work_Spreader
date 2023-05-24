#include "./pool.hpp"
#include "pool.hpp"

void Pool::add_new_thread(boost::thread *new_thread) {

}

Pool::~Pool() {
    for(auto thread: all_threads) {
        thread->join();
    }
}
