#ifndef _BASEWATCHED_H_
#define _BASEWATCHED_H_

class AbstractWatched {
public:
    virtual bool checkActivity() {}
    virtual bool reset() {}
};


#endif // _BASEWATCHED_H_