#ifndef __TIME_WATCHER_HPP__
#define __TIME_WATCHER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

#define startAutoTimeWatcher(X) \
    AutoTimeWatcher autoTime = createAutoTimeWatcher(#X); \


DECLARE_SIMPLE_CLASS(AutoTimeWatcher) {

public:
    _AutoTimeWatcher(String);

    ~_AutoTimeWatcher();

private:
    String mTag;

    long current;
};

DECLARE_SIMPLE_CLASS(TimeWatcher) {

public:
    void start();

    long stop();

private:

    long current;
};

}
#endif