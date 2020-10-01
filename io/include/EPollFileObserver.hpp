#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <fstream>
#include <iostream>
#include <sys/epoll.h>
#include <vector>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "Thread.hpp"
#include "Pipe.hpp"
#include "Uint32.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(EPollFileObserverListener) {
public:
    friend class _EpollObserverRequest;
    friend class _EPollFileObserver;

    virtual int onEvent(int fd,uint32_t events,ByteArray) = 0;

private:
    std::vector<int> fds;

    void removeFd(int fd);
};

DECLARE_SIMPLE_CLASS(EPollFileObserver) EXTENDS(Thread) {
public:
    friend class _EPollThread;
    
    _EPollFileObserver(int size);

    _EPollFileObserver();

    int addObserver(int fd,uint32_t events,EPollFileObserverListener l);

    int removeObserver(int fd);

    int removeObserver(EPollFileObserverListener l);

    int release();

    void dump();

    void run();
    
    ~_EPollFileObserver();

    static const uint32_t EpollIn = EPOLLIN;
    static const uint32_t EpollPri = EPOLLPRI;
    static const uint32_t EpollOut = EPOLLOUT;
    static const uint32_t EpollRdNorm = EPOLLRDNORM;
    static const uint32_t EpollRdBand = EPOLLRDBAND;
    static const uint32_t EpollWrNorm = EPOLLWRNORM;
    static const uint32_t EpollWrBand = EPOLLWRBAND;
    static const uint32_t EpollMsg = EPOLLMSG;
    static const uint32_t EpollErr = EPOLLERR;
    static const uint32_t EpollHup = EPOLLHUP;
    static const uint32_t EpollRdHup = EPOLLRDHUP;
#ifdef EPOLLEXCLUSIVE    
    static const uint32_t EpollExClusive = EPOLLEXCLUSIVE;
#endif
    static const uint32_t EpollWakeUp = EPOLLWAKEUP;
    static const uint32_t EpollOneShot = EPOLLONESHOT;
    static const uint32_t EpollEt = EPOLLET;

    static const int OnEventOK = 0;
    static const int OnEventRemoveObserver = 1;

    static const int DefaultEpollSize = 1024*8;
    
private:
    static const int DefaultBufferSize = 16*1024;
    static const uint32_t EpollEvent[];
    
    void addEpollFd(int fd,uint32_t events);

    int mEpollFd;

    //<fd,listener>
    Mutex mListenerMutex;
    HashMap<int,HashMap<int,ArrayList<EPollFileObserverListener>>> mListeners;

    Pipe mPipe;

    int mSize;

    AtomicInteger mStartFlag;
};

}
#endif
