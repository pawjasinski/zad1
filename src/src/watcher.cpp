#include "watcher.h"

AbstractWatched* Watcher::checkInactive() {
    for(int i = 0; i < watch.size(); ++i) {
        if( !watch.at(i)->checkActivity() )
            return watch.at(i);
    }
}

void Watcher::regist(AbstractWatched* abs) {
    std::unique_lock<std::mutex> lck(m);
    watch.push_back(abs);
}