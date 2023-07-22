#include <fcntl.h>

#include "EPollFileObserver.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "TimeWatcher.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

//----------------_EPollFileObserver----------------
void _EPollFileObserver::run() {
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
            Inspect(fd == mPipeFd);
            EPollFileObserverListener listener = mListeners->get(fd);

            if (listener == nullptr) {
                LOG(ERROR) << "EpollObserver get event,but no callback,fd is "
                           << fd << "event is " << fd;
                continue;
            }

            if (listener->onEvent(fd, events[i].events) == st(EPollFileObserver)::Remove) {
                removeObserver(fd);
            }
        }
    }
}

_EPollFileObserver::_EPollFileObserver(int size) {
    mListeners = createConcurrentHashMap<int, EPollFileObserverListener>();
    mSize = size;
    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    addEpollFd(mPipe->getReadChannel(), EPOLLIN | EPOLLRDHUP | EPOLLHUP);
    start();
}

_EPollFileObserver::_EPollFileObserver()
    : _EPollFileObserver(kDefaultEpollSize) {}

int _EPollFileObserver::removeObserver(int fd) {
    // we should clear
    int ret = epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    mListeners->remove(fd);
    return ret;
}

void _EPollFileObserver::addEpollFd(int fd, uint32_t events) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(struct epoll_event));
    ev.data.fd = fd;
    ev.events = events;
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
}

int _EPollFileObserver::close() {
    Inspect(mEpollFd == -1,0);

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

_EPollFileObserver::~_EPollFileObserver() {
    close();
}

} // namespace obotcha
