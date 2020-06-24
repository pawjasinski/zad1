#include "threadsHandler.h"

ThreadsHandler::ThreadsHandler() {}

ThreadsHandler::~ThreadsHandler() {}

void ThreadsHandler::add(int rand) {
    std::unique_lock<std::mutex> lck(cl);
    lst.push_back(rand);
    cond.notify_all();
}

int ThreadsHandler::pop() {
    std::unique_lock<std::mutex> lck(cl);
    cond.wait(lck, [&](){ return lst.empty() == false; });
    int ret = lst.front();
    lst.pop_front();
    return ret;
}
