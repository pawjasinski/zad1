#include "server.h"
#include <cstring>
#include <sstream>
#include <iostream>

Server::Server() {}

Server::~Server() {}

void Server::pull_int() {
    if(th == nullptr) {
        logr("bad threadShandler pointer");
        return;
    }
    rnd = th->pop();
    while(rnd <= 100000000 && rnd >= 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    logActivity();
}

void Server::getBuffer(Allocator& alloc) {
    buff = alloc.get_buffer();
    logActivity();
}

void Server::freeBuffer() {
    if(buff != nullptr) delete[] buff;
    buff = nullptr;
    logActivity();
}

void Server::intToString() {
    if(buff != nullptr) {
        sprintf(buff, "%d", rnd);
    }
    else {
        logr("empty buffer");
    }
    logActivity();
}

void Server::show() {
    std::cout << buff << "\n";
    logActivity();
}

bool Server::reset() {
    std::stringstream ss;
    ss << "zagubiono liczbe: " << rnd;
    logr(ss.str().c_str());
    pull_int();
}

void Server::registHandler(ThreadsHandler* t) {
    if(!t) {
        logr("Bad pointer");
        return;
    }
    th = t;
}