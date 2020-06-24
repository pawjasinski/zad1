#ifndef _LOG_H_
#define _LOG_H_
#include <iostream>

#define logr(message) std::cout<<"\033[31m"<<message<<"\033[0m"<<"\n";

#endif