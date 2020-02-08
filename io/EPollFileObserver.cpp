#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <stddef.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "EPollFileObserver.hpp"

namespace obotcha {

_EPollThread::_EPollThread(int fd,int size,Pipe pipe,EPollFileObserverListener listener) {
    mEpollFd = fd;
    mListener = listener;
    mSize = size;
    mPipe = pipe;
}

void _EPollThread::run() {
    struct epoll_event events[mSize];
    memset(events,0,sizeof(struct epoll_event) *mSize);

    while(1) {
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        if(epoll_events_count < 0) {
            return;
        }
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            int event = events[i].events;

            if(fd == mPipe->getReadPipe()) {
                return;
            }
            if(mListener->onEvent(fd,event) == EPollOnEventResultRemoveFd) {
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
            };
        }
    }
}

_EPollFileObserver::_EPollFileObserver(EPollFileObserverListener l,int size) {
    this->mListener = l;
    mSize = size;
    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    mPipe->init();
    addFd(mPipe->getReadPipe(),EPOLLIN|EPOLLRDHUP|EPOLLHUP);
}

_EPollFileObserver::_EPollFileObserver(EPollFileObserverListener l):_EPollFileObserver{l,EPOLL_DEFAULT_SIZE} {

}

int _EPollFileObserver::addFd(int fd,int events) {
    struct epoll_event ev;
    memset(&ev,0,sizeof(struct epoll_event));

    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);

    return 0;
}

int _EPollFileObserver::removeFd(int fd) {
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}

int _EPollFileObserver::start() {
    if(mEpollThread != nullptr) {
        return -EPollFileObserverAlreadyStart;
    }
    mEpollThread = createEPollThread(mEpollFd,mSize,mPipe,mListener);
    mEpollThread->start();
    return 0;
}

int _EPollFileObserver::release() {
    mPipe->writeTo(createByteArray(1));
    
    mEpollThread->join();
    
    if(mEpollFd != -1) {
        close(mEpollFd);
        mEpollFd = -1;
    }
    
    return 0;
}

_EPollFileObserver::~_EPollFileObserver() {

}


}

