#include <fcntl.h>

#include "AutoLock.hpp"
#include "ByteArray.hpp"
#include "EPollFileObserver.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "String.hpp"
#include "TimeWatcher.hpp"

namespace obotcha {

//----------------_EPollFileObserver----------------
void _EPollFileObserver::run() {
    struct epoll_event events[mSize];
    memset(events, 0, sizeof(struct epoll_event) * mSize);
    //byte readbuff[st(EPollFileObserver)::DefaultBufferSize];

    while (1) {
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        //AutoTimeWatcher watcher = createAutoTimeWatcher("Epoll monitor");
        if (epoll_events_count < 0) {
            LOG(ERROR) << "epoll_wait count is -1,error is "<<CurrentError;
            return;
        }

        for (int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            if (fd == mPipe->getReadChannel()) {
                return;
            }
            uint32_t recvEvents = events[i].events;
            EPollFileObserverListener listener = nullptr;
            {
                AutoLock l(mListenerMutex);
                listener = mListeners->get(fd);
            }

            if (listener == nullptr) {
                LOG(ERROR) << "EpollObserver get event,but no callback,fd is "
                           << fd << "event is " << recvEvents;
                continue;
            }

            if (listener->onEvent(fd, recvEvents) ==
                      st(EPollFileObserver)::OnEventRemoveObserver) {
                removeObserver(fd);
            }
        }
    }
}

_EPollFileObserver::_EPollFileObserver(int size) {
    mListeners = createHashMap<int, EPollFileObserverListener>();
    mSize = size;
    mListenerMutex = createMutex("Epoll Listener Mutex");
    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    addEpollFd(mPipe->getReadChannel(), EPOLLIN | EPOLLRDHUP | EPOLLHUP);

    mCloseMutex = createMutex();
    isClosed = false;

    start();
}

_EPollFileObserver::_EPollFileObserver()
    : _EPollFileObserver(DefaultEpollSize) {}

int _EPollFileObserver::removeObserver(int fd) {
    // we should clear
    AutoLock l(mListenerMutex);
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
    if(epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev) != 0) {
        LOG(ERROR)<<"add epoll fd,reason is "<<strerror(errno);
    }
}

int _EPollFileObserver::close() {
    {
        AutoLock l(mCloseMutex);
        if(isClosed) {
            return 0;
        }

        isClosed = true;
    }

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

    AutoLock l(mListenerMutex);
    mListeners->clear();
    return 0;
}

_EPollFileObserver::~_EPollFileObserver() {
  close();
}

void _EPollFileObserver::dump() {
    printf("EPollFileObserver,mListeners is %d \n",mListeners->size());
}

} // namespace obotcha
