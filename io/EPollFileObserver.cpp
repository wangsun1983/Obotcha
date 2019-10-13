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
        printf("EpollThread run1 \n");
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        printf("EpollThread run2 \n");
        if(epoll_events_count < 0) {
            printf("EpollThread exit1 \n");
            return;
        }
        printf("EpollThread run3 \n");
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            int event = events[i].events;

            if(fd == mPipe->getReadPipe()) {
                printf("EpollThread exit2 \n");
                return;
            }
            printf("EpollThread run4 \n");
            if(mListener->onEvent(fd,event) == EPollOnEventResultRemoveFd) {
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
            };
            printf("EpollThread run5 \n");
        }
        printf("EpollThread run6 \n");
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
    printf("EPollFileObserver start 1\n");
    if(mEpollThread != nullptr) {
        return -EPollFileObserverAlreadyStart;
    }
    printf("EPollFileObserver start 2\n");
    mEpollThread = createEPollThread(mEpollFd,mSize,mPipe,mListener);
    mEpollThread->start();
    printf("EPollFileObserver start 3\n");
    return 0;
}

int _EPollFileObserver::release() {
    printf("EPollFileObserver release 1\n");
    mPipe->writeTo(createByteArray(1));
    printf("EPollFileObserver release 2\n");

    mEpollThread->join();
    printf("EPollFileObserver release 3\n");

    if(mEpollFd != -1) {
        close(mEpollFd);
        mEpollFd = -1;
    }
    
    return 0;
}

_EPollFileObserver::~_EPollFileObserver() {

}


}

