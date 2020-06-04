#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "EPollFileObserver.hpp"
#include "TimeWatcher.hpp"
#include "AutoLock.hpp"

namespace obotcha {

const int _EPollFileObserver::EpollEvent[] = {EpollIn,
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
                                     EpollExClusive,
                                     EpollWakeUp,
                                     EpollOneShot,
                                     EpollEt};

void _EPollFileObserver::run() {
    struct epoll_event events[mSize];
    memset(events,0,sizeof(struct epoll_event) *mSize);
    byte readbuff[st(EPollFileObserver)::DefaultBufferSize];
    HashMap<EPollFileObserverListener,Boolean> ll = createHashMap<EPollFileObserverListener,Boolean>();
    while(1) {
        {
            AutoLock l(mRequestMutex);
            ListIterator<EpollObserverRequest> iterator = mReqeusts->getIterator();
            printf("mReqeusts size is %d \n",mReqeusts->size());
            while(iterator->hasValue()) {
                EpollObserverRequest r = iterator->getValue();
                switch(r->action) {
                    case st(EpollObserverRequest)::Remove:
                    _removeObserver(r->fd,r->events,r->l);
                    break;

                    case st(EpollObserverRequest)::Add:
                    _addObserver(r->fd,r->events,r->l);
                    break;
                }
                iterator->next();
            }

            mReqeusts->clear();
        }

        mStartFlag->set(1);
        printf("start wait epoll \n");
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        
        if(epoll_events_count < 0) {
            return;
        }
        StartAutoTimeWatcher("do epoll event");
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            int recvEvents = events[i].events;
            if(fd == mPipe->getReadPipe()) {
                ByteArray pipeData = createByteArray(1);
                mPipe->readFrom(pipeData);
                if(pipeData->at(0) == 0) {
                    break;
                } else {
                    return;
                }
            }
            
            //we need read all data
            int len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);

            ByteArray data = nullptr;
            if(len > 0) {
                data = createByteArray(readbuff,len);
                while(len == st(EPollFileObserver)::DefaultBufferSize) {
                    len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);
                    data->append(readbuff,len);
                }
            }

            HashMap<int,ArrayList<EPollFileObserverListener>> map = mListeners->get(fd);
            if(map == nullptr) {
                continue;
            }
            
            for(int j = 0;j<sizeof(EpollEvent)/sizeof(int);j++) {
                int event = recvEvents & EpollEvent[i];
                if(event != 0) {
                    ArrayList<EPollFileObserverListener> list = map->get(event);
                    if(list == nullptr) {
                        continue;
                    }
                    
                    ListIterator<EPollFileObserverListener> iterator = list->getIterator();
                    
                    while(iterator->hasValue()) {
                        EPollFileObserverListener c = iterator->getValue();
                        if(ll->get(c) != nullptr) {
                            iterator->next();
                            continue;
                        }

                        ll->put(c,createBoolean(true));
                        if(c->onEvent(fd,recvEvents,data) == st(EPollFileObserver)::OnEventRemoveObserver) {
                            iterator->remove();
                            continue;
                        };
                        iterator->next();
                    }

                    if(list->size() == 0) {
                        map->remove(event);
                        epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
                    }
                }
            }
            ll->clear();
        }
    }
}

_EPollFileObserver::_EPollFileObserver(int size) {
    mListeners = createHashMap<int,HashMap<int,ArrayList<EPollFileObserverListener>>>();
    mSize = size;
    mRequestMutex = createMutex("Epoll Mutex");
    mReqeusts = createArrayList<EpollObserverRequest>();
    printf("create1 mReqeusts size is %d \n",mReqeusts->size());

    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    mPipe->init();
    addObserver(mPipe->getReadPipe(),EPOLLIN|EPOLLRDHUP|EPOLLHUP,nullptr);
    printf("create2 mReqeusts size is %d \n",mReqeusts->size());
    mStartFlag = createAtomicInteger(0);
    start();
    while(mStartFlag->getAndAnd(1) != 1) {}
    printf("create3 mReqeusts size is %d \n",mReqeusts->size());
}

_EPollFileObserver::_EPollFileObserver():_EPollFileObserver{DefaultEpollSize}{
}

int _EPollFileObserver::addObserver(int fd,int events,EPollFileObserverListener l) {
    //printf("add!!!! \n");
    EpollObserverRequest request = createEpollObserverRequest();
    request->action = st(EpollObserverRequest)::Add;
    request->fd = fd;
    request->events = events;
    request->l = l;

    AutoLock lock(mRequestMutex);
    mReqeusts->add(request);
    
    ByteArray data = createByteArray(1);
    data->fill(0,0);
    mPipe->writeTo(data);
}

int _EPollFileObserver::removeObserver(int fd,int events,EPollFileObserverListener l) {
    printf("remove!!!! \n");
    EpollObserverRequest request = createEpollObserverRequest();
    request->action = st(EpollObserverRequest)::Remove;
    request->fd = fd;
    request->events = events;
    request->l = l;

    AutoLock lock(mRequestMutex);
    mReqeusts->add(request);
}

int _EPollFileObserver::_addObserver(int fd,int events,EPollFileObserverListener l) {
    struct epoll_event ev;
    memset(&ev,0,sizeof(struct epoll_event));

    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
    
    if(l != nullptr) {
        HashMap<int,ArrayList<EPollFileObserverListener>> m = mListeners->get(fd);
        if(m == nullptr) {
            m = createHashMap<int,ArrayList<EPollFileObserverListener>>();
            mListeners->put(fd,m);
        }
        
        for(int i = 0;i<sizeof(EpollEvent)/sizeof(int);i++) {
            int event = (events & EpollEvent[i]);
            if(event != 0) {
                ArrayList<EPollFileObserverListener> ll = m->get(event);
                if(ll == nullptr) {
                    ll = createArrayList<EPollFileObserverListener>();
                    m->put(event,ll);
                }
                ll->add(l);
            }
        }
    }

    return 0;
}

int _EPollFileObserver::_removeObserver(int fd,int event,EPollFileObserverListener l) {

    HashMap<int,ArrayList<EPollFileObserverListener>> m = mListeners->get(fd);
    ArrayList<EPollFileObserverListener> list;
    if(m == nullptr) {
        goto remove;
    }

    list = m->get(event);
    if(list == nullptr) {
        goto remove;
    }

    list->remove(l);
    if(list->size() == 0) {
        m->remove(event);
    } else {
        return 0;
    }
    
remove:
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}

int _EPollFileObserver::release() {
    ByteArray data = createByteArray(1);
    data->fill(0,1);
    mPipe->writeTo(data);
    
    join();
    
    if(mEpollFd != -1) {
        close(mEpollFd);
        mEpollFd = -1;
    }

    mListeners->clear();
    mReqeusts->clear();
    
    return 0;
}

_EPollFileObserver::~_EPollFileObserver() {
    if(mEpollFd != -1) {
        close(mEpollFd);
    }
}


}

