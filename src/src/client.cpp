#include "client.h"

Client::Client() {
    my_eng.seed(reinterpret_cast<intptr_t>(this));
}

Client::~Client() {}

void Client::setlogName(const char* name) {
    std::strncpy(file, name, 20);
}


void Client::push(ThreadsHandler& th) {
    int r = rand_now();
    th.add(r);
    vec.push_back(r);
}

void Client::saveLog() {
    std::ofstream f(file, std::ios::out );
    for(int i = 0; i < vec.size(); ++i) {
        f << vec.at(i) << "\n";
    }
    f.close();
}