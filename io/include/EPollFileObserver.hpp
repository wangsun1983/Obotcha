#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <sys/epoll.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "Thread.hpp"
#include "Pipe.hpp"

namespace obotcha {

class _EPollFileObserver;

DECLARE_SIMPLE_CLASS(EPollFileObserverListener) {
public:
    friend class _EPollFileObserver;

    virtual int onEvent(int fd,uint32_t events,ByteArray) = 0;

private:
    int notifyEvent(int fd,uint32_t events,ByteArray);
    std::map<int,int> mFdEventsMap;
};

DECLARE_SIMPLE_CLASS(EPollFileObserver) EXTENDS(Thread) {
public:
    _EPollFileObserver(int size);

    _EPollFileObserver();

    int addObserver(int fd,uint32_t events,EPollFileObserverListener l);

    int removeObserver(int fd);

    int removeObserver(EPollFileObserverListener l);

    int release();

    void run();
    
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

    static const int OnEventOK = 0;
    static const int OnEventRemoveObserver = 1;

    static const int DefaultEpollSize = 1024*8;
    
private:
    static const int DefaultBufferSize = 16*1024;
    static const int DefaultMaxBuffSize = 1024*1024;
    static const uint32_t EpollEvent[];
    
    void addEpollFd(int fd,uint32_t events);

    void updateFdEventsMap(int fd,uint32_t events,std::map<int,int> &maps);

    int mEpollFd;

    Mutex mListenerMutex;
    HashMap<int,ArrayList<EPollFileObserverListener>> mListeners;
    std::map<int,int> mFdEventsMap;
    
    Pipe mPipe;

    int mSize;
};

}
#endif
