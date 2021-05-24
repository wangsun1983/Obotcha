#include <fcntl.h>

#include "String.hpp"
#include "ByteArray.hpp"
#include "EPollFileObserver.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

//----------------_EPollFileObserver----------------
void _EPollFileObserver::run() {
    struct epoll_event events[mSize];
    memset(events,0,sizeof(struct epoll_event) *mSize);
    byte readbuff[st(EPollFileObserver)::DefaultBufferSize];

    while(1) {
        //printf("observer run start \n");
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        if(epoll_events_count < 0) {
            LOG(ERROR)<<"epoll_wait count is -1";
            return;
        }
        
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            if(fd == mPipe->getReadPipe()) {
                return;
            }
            printf("on epoll fd is %d \n",fd);

            uint32_t recvEvents = events[i].events;
            //printf("observer run fd is %d,events is %x \n",fd,recvEvents);
            EPollFileObserverListener listener = nullptr;
            
            {
                AutoLock l(mListenerMutex);
                listener = mListeners->get(fd);
            }

            if(listener == nullptr) {
                LOG(ERROR)<<"EpollObserver get event,but no callback,fd is "<<fd<<"event is "<<recvEvents;
                continue;
            }

            int result = listener->onEvent(fd,recvEvents);
            if(result == st(EPollFileObserver)::OnEventRemoveObserver) {
                removeObserver(fd);
            }
        }
    }
}

_EPollFileObserver::_EPollFileObserver(int size) {
    mListeners = createHashMap<int,EPollFileObserverListener>();
    mSize = size;
    mListenerMutex = createMutex("Epoll Listener Mutex");
    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    mPipe->init();

    addEpollFd(mPipe->getReadPipe(),EPOLLIN|EPOLLRDHUP|EPOLLHUP);
    start();
}

_EPollFileObserver::_EPollFileObserver():_EPollFileObserver(DefaultEpollSize){
}

int _EPollFileObserver::removeObserver(int fd) {
    //we should clear
    AutoLock l(mListenerMutex);
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    mListeners->remove(fd);
    return 0;
}

void _EPollFileObserver::addEpollFd(int fd,uint32_t events) {

    struct epoll_event ev;
    memset(&ev,0,sizeof(struct epoll_event));

    ev.data.fd = fd;
    ev.events = events;
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0)| O_NONBLOCK);
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
}

int _EPollFileObserver::close() {
    if(mEpollFd != -1) {
        ::close(mEpollFd);
        mEpollFd = -1;
    } else {
        return 0;
    }

    ByteArray data = createByteArray(1);
    data->fill(0,1);
    mPipe->writeTo(data);
    
    join();

    mPipe->closeReadPipe();
    mPipe->closeWritePipe();

    AutoLock l(mListenerMutex);
    mListeners->clear();
    return 0;
}

_EPollFileObserver::~_EPollFileObserver() {
    close();
}

}

