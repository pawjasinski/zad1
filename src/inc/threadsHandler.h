#ifndef _THREADSHANDLER_H_
#define _THREADSHANDLER_H_
#include <list>
#include <mutex>
#include <condition_variable>

class ThreadsHandler {
public:
    ThreadsHandler();
    ~ThreadsHandler();
    void add(int rand);
    int pop();
private:
    bool flag = true;
    std::mutex cl;
    std::mutex srv;
    std::condition_variable cond;
    std::list<int> lst;
};

#endif // _THREADSHANDLER_H_