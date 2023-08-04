#ifndef __OBOTCHA_TIME_WATCHER_HPP__
#define __OBOTCHA_TIME_WATCHER_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

#define StartAutoTimeWatcher(X)                                                \
    AutoTimeWatcher autoTime = createAutoTimeWatcher(#X);

DECLARE_CLASS(AutoTimeWatcher) {
public:
    explicit _AutoTimeWatcher(String);

    ~_AutoTimeWatcher() override;

private:
    String mTag;

    long current;
};

DECLARE_CLASS(TimeWatcher) {
public:
    void start();

    long stop() const;

private:
    long current;
};

} // namespace obotcha
#endif