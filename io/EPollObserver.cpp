/**
 * @file EPollObserver.cpp
 * @brief Provides access to the Linux epoll facility.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include <fcntl.h>

#include "EPollObserver.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

namespace obotcha {

//----------------_EPollObserver----------------
void _EPollObserver::run() {
    struct epoll_event events[mSize];
    memset(events, 0, sizeof(struct epoll_event) * mSize);
    int mPipeFd = mPipe->getReadChannel();
    while(true) {
        int count = epoll_wait(mEpollFd, events, mSize, -1);
        if (count < 0) {
            LOG(ERROR) << "epoll_wait count is -1,error is "<<CurrentError;
            return;
        }

        for (int i = 0; i < count; i++) {
            int fd = events[i].data.fd;
            Inspect(fd == mPipeFd)
            EPollListener listener = mListeners->get(fd);

            if (listener == nullptr) {
                LOG(ERROR) << "EpollObserver get event,but no callback,fd is "
                           << fd << " event is " << events[i].events;
                continue;
            }

            if (listener->onEvent(fd, events[i].events) == st(IO)::Epoll::Result::Remove) {
                removeObserver(fd);
            }

            //remove this fd or you will receive RDHUP|HUP event repeatly
            if((events[i].events & (EPOLLRDHUP|EPOLLHUP)) != 0) {
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
            }
        }
    }
}

_EPollObserver::_EPollObserver(int size):mSize(size) {
    mEpollFd = epoll_create(size);
    addEpollFd(mPipe->getReadChannel(), EPOLLIN | EPOLLRDHUP | EPOLLHUP);
    start();
}

_EPollObserver::_EPollObserver()
    : _EPollObserver(kDefaultEpollSize) {}

int _EPollObserver::removeObserver(int fd) {
    // we should clear
    int ret = epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    mListeners->remove(fd);
    return ret;
}

void _EPollObserver::addEpollFd(int fd, uint32_t events) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
}

int _EPollObserver::close() {
    Inspect(mEpollFd == -1,0)
    mPipe->write(createByteArray(1));

    join();
    mPipe->close();
    
    if (mEpollFd != -1) {
        ::close(mEpollFd);
        mEpollFd = -1;
    }

    mListeners->clear();
    return 0;
}

_EPollObserver::~_EPollObserver() {
    close();
}

} // namespace obotcha
