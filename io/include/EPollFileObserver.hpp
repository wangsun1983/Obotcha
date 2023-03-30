#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <sys/epoll.h>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Pipe.hpp"
#include "String.hpp"
#include "Thread.hpp"
#include "ConcurrentHashMap.hpp"

namespace obotcha {

class _EPollFileObserver;

DECLARE_CLASS(EPollFileObserverListener) {
  public:
    virtual int onEvent(int fd, uint32_t events) = 0;
};

template <class Function, class... Args>
class _LambdaEPollFileObserverListener : public _EPollFileObserverListener {
  public:
    _LambdaEPollFileObserverListener(Function &&f, Args &&... args)
        : _EPollFileObserverListener(), func(f),
          _arguments(std::make_tuple(args...)) {}

    int onEvent(int fd, uint32_t events) {
        auto param = std::tuple_cat(std::make_tuple(fd, events), _arguments);
        return ostd::apply(func, param);
    }

  private:
    std::tuple<Args...> _arguments;
    Function func;
};

template <typename Callfunc, typename... Args>
sp<_EPollFileObserverListener>
createLambdaEPollFileObserverListener(Callfunc f, Args... args) {
    _EPollFileObserverListener *r =
        new _LambdaEPollFileObserverListener<Callfunc, Args...>(
            std::forward<Callfunc>(f), std::forward<Args>(args)...);
    return AutoClone(r);
}

DECLARE_CLASS(EPollFileObserver) IMPLEMENTS(Thread) {
  public:
    _EPollFileObserver(int size);

    _EPollFileObserver();

    template <typename X> int addObserver(int fd, uint32_t events, sp<X> l) {
        mListeners->put(fd, l);
        addEpollFd(fd, events);
        return 0;
    }

    template <class Function, class... Args>
    int addObserver(int fd, uint32_t events, Function &&f, Args &&... args) {
        EPollFileObserverListener l =
            createLambdaEPollFileObserverListener(f, args...);
        return addObserver(fd, events, l);
    }

    int removeObserver(int fd);

    int removeObserver(EPollFileObserverListener l);

    int close();

    void run();
    
    void dump();

    ~_EPollFileObserver();

    enum EpollEvent {
        EpollIn = EPOLLIN,
        EpollPri = EPOLLPRI,
        EpollOut = EPOLLOUT,
        EpollRdNorm = EPOLLRDNORM,
        EpollRdBand = EPOLLRDBAND,
        EpollWrNorm = EPOLLWRNORM,
        EpollWrBand = EPOLLWRBAND,
        EpollMsg = EPOLLMSG,
        EpollErr = EPOLLERR,
        EpollHup = EPOLLHUP,
        EpollRdHup = EPOLLRDHUP,
#ifdef EPOLLEXCLUSIVE
        EpollExClusive = EPOLLEXCLUSIVE,
#endif
        EpollWakeUp = EPOLLWAKEUP,
        EpollOneShot = EPOLLONESHOT,
        EpollEt = EPOLLET,
    };

    enum EpollResult {
        OK = 0,
        Remove
    };

  private:
    // static const int kDefaultBufferSize = 16 * 1024;
    // static const int kDefaultMaxBuffSize = 1024 * 1024;
    static const int kDefaultEpollSize = 1024 * 64;

    void addEpollFd(int fd, uint32_t events);
    
    int mEpollFd;
    ConcurrentHashMap<int, EPollFileObserverListener> mListeners;
    Pipe mPipe;
    int mSize;
};

} // namespace obotcha
#endif
