#include "log.h"
#include <thread>
#include <chrono>
#include "threadsHandler.h"
#include "client.h"
#include "server.h"
#include "watcher.h"
#include "baseWatched.h"
#include <csignal>
#include <chrono>
#include <sstream>

void client(ThreadsHandler&, uint i);
void server(ThreadsHandler&, Allocator&, Watcher&);
void allocator(Allocator&);
void watchdog(ThreadsHandler&, Watcher& w);
void signal_handler(int signal);

const size_t delay = 1000; // 1s
bool run = true;

int main(int argc, char** argv) {
    std::signal(SIGINT, signal_handler);

    ThreadsHandler th;
    Allocator al;
    Watcher w;


    std::thread cl1 {client, std::ref(th), 1};
    std::thread cl2 {client, std::ref(th), 2};
    std::thread cl3 {client, std::ref(th), 3};

    std::thread srv1 {server, std::ref(th), std::ref(al), std::ref(w)};
    std::thread srv2 {server, std::ref(th), std::ref(al), std::ref(w)};

    std::thread alloc {allocator, std::ref(al)};

    std::thread watcher {watchdog, std::ref(th), std::ref(w)};

    cl1.join();
    cl2.join();
    cl3.join();

    srv1.join();
    srv2.join();

    alloc.join();

    watcher.join();

}

void client(ThreadsHandler& th, uint i) {
    Client cl;
    
    std::stringstream ss;
    ss << i <<".log";
    cl.setlogName(ss.str().c_str());
    while(run) {
        cl.push(th);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    cl.saveLog();
}

void server(ThreadsHandler& th, Allocator& al, Watcher& w) {
    Server srv;
    srv.registHandler(&th);
    w.regist(&srv);
    while(run) {
        srv.pull_int();
        srv.getBuffer(al);
        srv.intToString();
        srv.show();
        srv.freeBuffer();
    }
    logr("server is ending");
}

void allocator(Allocator& al) {
    while(run) {
        al.alloc_mem();
    }
    logr("alocator is ending");
}

 void watchdog(ThreadsHandler& th, Watcher& w) {
     AbstractWatched* ww = nullptr;
     while(run) {
         std::this_thread::sleep_for(std::chrono::milliseconds(delay + 1000));
         ww = w.checkInactive();
         if(ww != nullptr) {
             ww->reset();
             ww = nullptr;
         }
     }
 }

void signal_handler(int signal) {
    run = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    exit(1);
}