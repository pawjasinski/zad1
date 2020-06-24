#ifndef _WATCHER_H_
#define _WATCHER_H_

#include "log.h"
#include "baseWatched.h"
#include <vector>
#include <mutex>

class Watcher {
public:
    void regist(AbstractWatched* abs);
    AbstractWatched* checkInactive();

private:
    std::vector<AbstractWatched*> watch;
    std::mutex m;
};

#endif // _WATCHER_H_