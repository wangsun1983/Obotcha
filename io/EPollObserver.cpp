#include <fcntl.h>

#include "EPollObserver.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "TimeWatcher.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

//----------------_EPollObserver----------------
void _EPollObserver::run() {
    struct epoll_event events[mSize];
    memset(events, 0, sizeof(struct epoll_event) * mSize);
    int mPipeFd = mPipe->getReadChannel();
    InfiniteLoop {
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        if (epoll_events_count < 0) {
            LOG(ERROR) << "epoll_wait count is -1,error is "<<CurrentError;
            return;
        }

        for (int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            Inspect(fd == mPipeFd)
            EPollListener listener = mListeners->get(fd);

            if (listener == nullptr) {
                LOG(ERROR) << "EpollObserver get event,but no callback,fd is "
                           << fd << "event is " << fd;
                continue;
            }

            if (listener->onEvent(fd, events[i].events) == st(IO)::Epoll::Result::Remove) {
                removeObserver(fd);
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
    memset(&ev, 0, sizeof(struct epoll_event));
    ev.data.fd = fd;
    ev.events = events;
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
}

int _EPollObserver::close() {
    Inspect(mEpollFd == -1,0)

    ByteArray data = createByteArray(1);
    data[0] = 1;
    mPipe->write(data);

    join();

    mPipe->closeReadChannel();
    mPipe->closeWriteChannel();

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
