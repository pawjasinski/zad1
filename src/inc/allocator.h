#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <thread>
#include <condition_variable>

#include <iostream>

class Allocator {
public:
    Allocator();
    ~Allocator();
    void alloc_mem(uint len = 12);
    char* get_buffer();
private:
    std::mutex allck;
    std::mutex getlck;
    std::condition_variable cond;
    std::condition_variable condg;
    char* buffer = nullptr;
};

#endif // _ALLOCATOR_H_