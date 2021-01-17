#include <fcntl.h>

#include "String.hpp"
#include "ByteArray.hpp"
#include "EPollFileObserver.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"

namespace obotcha {

const uint32_t _EPollFileObserver::EpollEvent[] = {
                                     EpollIn,
                                     EpollPri,
                                     EpollOut,
                                     EpollRdNorm,
                                     EpollRdBand,
                                     EpollWrNorm,
                                     EpollWrBand,
                                     EpollMsg,
                                     EpollErr,
                                     EpollHup,
                                     EpollRdHup,
#ifdef EPOLLEXCLUSIVE                                     
                                     EpollExClusive,
#endif
                                     EpollWakeUp,
                                     EpollOneShot,
                                     EpollEt};

//----------------EPollFileObserverListener----------------
int _EPollFileObserverListener::notifyEvent(int fd,uint32_t events,ByteArray data) {
    auto iterator = mFdEventsMap.find(fd);
    if(iterator == mFdEventsMap.end()) {
        return -1;
    }

    if((iterator->second & events)!= 0) {
        return onEvent(fd,events,data);
    }

    return 0;
}

//----------------_EPollFileObserver----------------
void _EPollFileObserver::run() {
    struct epoll_event events[mSize];
    memset(events,0,sizeof(struct epoll_event) *mSize);
    byte readbuff[st(EPollFileObserver)::DefaultBufferSize];

    while(1) {
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

            uint32_t recvEvents = events[i].events;
            //printf("receive events is %lx \n",recvEvents);
            ByteArray recvData = nullptr;
            int len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);
            if(len > 0) {
                recvData = createByteArray(readbuff,len);
            }
            
            AutoLock l(mListenerMutex);
            ArrayList<EPollFileObserverListener> listeners = mListeners->get(fd);
            if(listeners == nullptr || listeners->size() == 0) {
                LOG(ERROR)<<"EpollObserver get event,but no callback,fd is "<<fd;
                continue;
            }

            ListIterator<EPollFileObserverListener> iterator = listeners->getIterator();
            while(iterator->hasValue()) {
                EPollFileObserverListener l = iterator->getValue();
                int result = l->notifyEvent(fd,recvEvents,recvData);
                if(result == st(EPollFileObserver)::OnEventRemoveObserver) {
                    l->mFdEventsMap.erase(fd);
                    iterator->remove();
                    continue;
                }

                iterator->next();
            }

            if(listeners->size() == 0 ||
                (recvEvents & (EpollRdHup|EPOLLHUP)) != 0) {
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
                close(fd);
                mFdEventsMap.erase(fd);
                mListeners->remove(fd);
            }
        }
    }
}

_EPollFileObserver::_EPollFileObserver(int size) {
    mListeners = createHashMap<int,ArrayList<EPollFileObserverListener>>();
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

int _EPollFileObserver::addObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    AutoLock mylock(mListenerMutex);
    auto iterator = mFdEventsMap.find(fd);
    if(iterator != mFdEventsMap.end() && (iterator->second & events) == events) {
        return -AlreadyRegist;
    }

    int regEvents = 0;
    regEvents |= events;
    
    ArrayList<EPollFileObserverListener> ll = mListeners->get(fd);
    if(ll == nullptr) {
        ll = createArrayList<EPollFileObserverListener>();
        mListeners->put(fd,ll);
    }

    ll->add(l);
    updateFdEventsMap(fd,events,l->mFdEventsMap);
    updateFdEventsMap(fd,events,mFdEventsMap);

    addEpollFd(fd,regEvents|EpollRdHup|EPOLLHUP);

    return 0;
}

int _EPollFileObserver::removeObserver(EPollFileObserverListener l) {
    AutoLock mylock(mListenerMutex);
    for (auto &kv : l->mFdEventsMap) {
        int fd = kv.first;
        ArrayList<EPollFileObserverListener> list = mListeners->get(fd);
        if(list->size() != 0) {
            list->remove(l);
        }

        if(list->size() == 0) {
            mListeners->remove(fd);
            epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
        }
    }

    l->mFdEventsMap.clear();

    return 0;
}

int _EPollFileObserver::removeEvent(int fd,int event) {
    int e = mFdEventsMap[fd];
    e &= ~event;

    struct epoll_event ev;
    ev.events = e;
    ev.data.fd = fd;

    epoll_ctl(mEpollFd, EPOLL_CTL_MOD, fd, &ev);
}

int _EPollFileObserver::addEvent(int fd,int event) {
    int e = mFdEventsMap[fd];
    e &= ~event;

    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
}

int _EPollFileObserver::removeObserver(int fd) {
    //we should clear
    AutoLock l(mListenerMutex);
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);

    ArrayList<EPollFileObserverListener> listeners = mListeners->get(fd);
    ListIterator<EPollFileObserverListener> iterator = listeners->getIterator();
    while(iterator->hasValue()) {
        EPollFileObserverListener l = iterator->getValue();
        l->mFdEventsMap.erase(fd);
        iterator->next();
    }
    
    mFdEventsMap.erase(fd);
    mListeners->remove(fd);
}

void _EPollFileObserver::addEpollFd(int fd,uint32_t events) {
    struct epoll_event ev;
    memset(&ev,0,sizeof(struct epoll_event));

    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

int _EPollFileObserver::release() {
    if(mEpollFd != -1) {
        close(mEpollFd);
        mEpollFd = -1;
    }

    ByteArray data = createByteArray(1);
    data->fill(0,1);
    mPipe->writeTo(data);
    
    join();

    //if one listener is registered in to EpollFileObserver.
    //we should clear the events which were registered in the released observer.
    AutoLock l(mListenerMutex);
    MapIterator<int,ArrayList<EPollFileObserverListener>> iterator = mListeners->getIterator();
    while(iterator->hasValue()) {
        int fd = iterator->getKey();
        removeObserver(fd);
        iterator->next();
    }

    mListeners->clear();
    
    return 0;
}

void _EPollFileObserver::updateFdEventsMap(int fd,uint32_t events,std::map<int,int> &maps) {
    auto iterator = maps.find(fd);
    if(iterator == maps.end()) {
        maps[fd] = events;
    } else {
        maps[fd] = (iterator->second|events);
    }
}

_EPollFileObserver::~_EPollFileObserver() {
    release();
}

}

