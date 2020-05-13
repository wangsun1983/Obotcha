#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <fstream>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "Thread.hpp"
#include "Pipe.hpp"

namespace obotcha {

#define EPOLL_DEFAULT_SIZE 1024*8

enum EPollFileObserverFailResaon {
    EPollFileObserverNotInit = 200,
    EPollFileObserverAlreadyStart,
};

enum EPollOnEventResult {
    EPollOnEventResultOK = 1,
    EPollOnEventResultRemoveFd,
};

DECLARE_SIMPLE_CLASS(EPollFileObserverListener) {
public:
    virtual int onEvent(int fd,int events) = 0;    
};

DECLARE_SIMPLE_CLASS(EPollThread) EXTENDS(Thread) {
public:
    _EPollThread(int fd,int size,Pipe pipe,EPollFileObserverListener);

    void run();

private:
    int mEpollFd;

    EPollFileObserverListener mListener;

    int mSize;

    Pipe mPipe;
};

DECLARE_SIMPLE_CLASS(EPollFileObserver) {
public:
    _EPollFileObserver(EPollFileObserverListener,int size);

    _EPollFileObserver(EPollFileObserverListener);

    int addFd(int fd,int events);

    int removeFd(int fd);

    int start();

    int release();
    
    ~_EPollFileObserver();
    
private:
    int mEpollFd;

    EPollFileObserverListener mListener;

    Thread mEpollThread;

    Pipe mPipe;

    int mSize;
};

}
#endif
