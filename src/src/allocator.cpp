#include "allocator.h"

Allocator::Allocator() {}

Allocator::~Allocator() {
    if(buffer != nullptr) delete[] buffer;
}

void Allocator::alloc_mem(uint len) {
    std::unique_lock<std::mutex> lck(allck);
    cond.wait(lck, [&]{ return buffer == nullptr; });
    try {
        buffer = new char[len];
        condg.notify_one();
    }
    catch(std::bad_alloc) {
        buffer == nullptr;
    }
}

char* Allocator::get_buffer() {
    std::unique_lock<std::mutex> lck(allck);
    condg.wait(lck, [&] { return buffer != nullptr; });
    char* ret = buffer;
    buffer = nullptr;
    cond.notify_one();
    return ret;
}