#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <fstream>
#include <iostream>
#include <sys/epoll.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "Thread.hpp"
#include "Pipe.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(EPollFileObserverListener) {
public:
    virtual int onEvent(int fd,int events,ByteArray) = 0;    
};

DECLARE_SIMPLE_CLASS(EPollFileObserver) EXTENDS(Thread) {
public:
    friend class _EPollThread;
    
    _EPollFileObserver(int size);

    _EPollFileObserver();

    int addObserver(int fd,int events,EPollFileObserverListener l);

    int removeObserver(int fd,int events,EPollFileObserverListener l);

    int release();

    void run();
    
    ~_EPollFileObserver();

    static const int EpollIn = EPOLLIN;
    static const int EpollPri = EPOLLPRI;
    static const int EpollOut = EPOLLOUT;
    static const int EpollRdNorm = EPOLLRDNORM;
    static const int EpollRdBand = EPOLLRDBAND;
    static const int EpollWrNorm = EPOLLWRNORM;
    static const int EpollWrBand = EPOLLWRBAND;
    static const int EpollMsg = EPOLLMSG;
    static const int EpollErr = EPOLLERR;
    static const int EpollHup = EPOLLHUP;
    static const int EpollRdHup = EPOLLRDHUP;
    static const int EpollExClusive = EPOLLEXCLUSIVE;
    static const int EpollWakeUp = EPOLLWAKEUP;
    static const int EpollOneShot = EPOLLONESHOT;
    static const int EpollEt = EPOLLET;

    static const int OnEventOK = 1;
    static const int OnEventRemoveObserver = 2;

    static const int DefaultEpollSize = 1024*8;
    
private:
    static const int DefaultBufferSize = 16*1024;
    static const int EpollEvent[];
    int mEpollFd;

    //EPollFileObserverListener mListener;
    HashMap<int,HashMap<int,ArrayList<EPollFileObserverListener>>> mListeners;

    Thread mEpollThread;

    Pipe mPipe;

    int mSize;
};

}
#endif
