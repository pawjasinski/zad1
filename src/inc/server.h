#ifndef _SERVER_H_
#define _SERVER_H_
#include "threadsHandler.h"
#include "allocator.h"
#include "baseWatched.h"
#include "log.h"
#include <iostream>

class Server : public AbstractWatched {
public:
    Server();
    virtual ~Server();
    void pull_int();
    void getBuffer(Allocator& alloc);
    void freeBuffer();
    void intToString();
    void show();
    virtual bool inline checkActivity() override {bool f = flagActivity; flagActivity = false; return f;}
    virtual bool reset() override;
    void registHandler(ThreadsHandler* t);
private:
ThreadsHandler* th = nullptr;
void inline logActivity() { flagActivity = true; }
bool flagActivity = true;
char* buff;
int rnd;
};

#endif // _SERVER_H_