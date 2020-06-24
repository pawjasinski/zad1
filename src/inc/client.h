#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "threadsHandler.h"
#include <vector>
#include <random>
#include <functional>
#include <fstream>
#include <cstring>

using my_engine = std::default_random_engine;
using my_distribution = std::uniform_int_distribution<>;

class Client {
public:
    Client();
    ~Client();
    //void random();
    void push(ThreadsHandler& th);
    void setlogName(const char* name);
    void saveLog();
private:
int rand_now() { return my_dist(my_eng); }
    my_engine my_eng;
    my_distribution my_dist;
    std::vector<int> vec;
    char file[20] = "log_rand.log";
};

#endif // _CLIENT_H_