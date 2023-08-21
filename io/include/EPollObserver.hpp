#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <sys/epoll.h>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Pipe.hpp"
#include "String.hpp"
#include "Thread.hpp"
#include "ConcurrentHashMap.hpp"
#include "OStdApply.hpp"
#include "IO.hpp"

namespace obotcha {

class _EPollObserver;

DECLARE_CLASS(EPollListener) {
  public:
    virtual st(IO)::Epoll::Result onEvent(int fd, uint32_t events) = 0;
};

template <class Function, class... Args>
class _LambdaEPollListener : public _EPollListener {
  public:
    _LambdaEPollListener(Function f, Args... args)
        : _EPollListener(), func(f),
          _arguments(std::make_tuple(args...)) {}

    st(IO)::Epoll::Result onEvent(int fd, uint32_t events) override {
        auto param = std::tuple_cat(std::make_tuple(fd, events), _arguments);
        return ostd::apply(func, param);
    }

  private:
    std::tuple<Args...> _arguments;
    Function func;
};

DECLARE_CLASS(EPollObserver) IMPLEMENTS(Thread) {
  public:
    // enum EpollResult {
    //     OK = 0,
    //     Remove
    // };

    explicit _EPollObserver(int size);
    _EPollObserver();

    template<typename T>
    int addObserver(int fd, uint32_t events,sp<T> l) {
        mListeners->put(fd, l);
        addEpollFd(fd, events);
        return 0;
    }

    template <class Function, class... Args>
    int addObserver(int fd, uint32_t events, Function f, Args... args) {
        _EPollListener *r = 
            new _LambdaEPollListener<Function, Args...>(f, args...);
        return addObserver(fd, events, AutoClone(r));
    }

    int removeObserver(int fd);
    int close();
    void run() override;
    ~_EPollObserver()override;
  
  private:
    static const int kDefaultEpollSize = 1024 * 64;

    void addEpollFd(int fd, uint32_t events);

    int mEpollFd;
    ConcurrentHashMap<int, EPollListener> mListeners = createConcurrentHashMap<int, EPollListener>();
    Pipe mPipe = createPipe();
    int mSize;
};

} // namespace obotcha
#endif
