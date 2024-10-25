#ifndef __OBOTCHA_TIME_WATCHER_HPP__
#define __OBOTCHA_TIME_WATCHER_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

class AutoTimeWatcher {
public:
    explicit AutoTimeWatcher(String);
    ~AutoTimeWatcher();

private:
    String mTag;
    long mCurrent;
};

DECLARE_CLASS(TimeWatcher) {
public:
    _TimeWatcher();
    void start();
    long stop() const;

private:
    long mCurrent;
};

} // namespace obotcha
#endif