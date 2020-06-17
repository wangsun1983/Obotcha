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
#include "Error.hpp"

namespace obotcha {

const uint32_t _EPollFileObserver::EpollEvent[] = {EpollIn,
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
    if(mStartFlag->get() == 0) {
        mStartFlag->set(1);
    }

    while(1) {
        //doRequest();
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);

        doRequest();

        if(epoll_events_count < 0) {
            return;
        }
        
        //StartAutoTimeWatcher("do epoll event");
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            uint32_t recvEvents = events[i].events;
            //printf("epollevent observer fd is %d,recvEvents is %p \n",fd,recvEvents);
            ByteArray recvData = nullptr;

            ll->clear();

            if(fd == mPipe->getReadPipe()) {
                ByteArray pipeData = createByteArray(1);
                mPipe->readFrom(pipeData);
                if(pipeData->at(0) == 0) {
                    break;
                } else {
                    return;
                }
            }
        
            HashMap<int,ArrayList<EPollFileObserverListener>> map = mListeners->get(fd);
            if(map == nullptr || map->size() == 0) {
                //printf("epollevent observer fd is %d,return \n",fd);
                continue;
            }

            for(int j = 0;j<sizeof(EpollEvent)/sizeof(uint32_t);j++) {
                uint32_t event = recvEvents & EpollEvent[j];
                if(event != 0) {
                    ArrayList<EPollFileObserverListener> list = map->get(event);
                    if(list == nullptr) {
                        continue;
                    }
                    
                    ListIterator<EPollFileObserverListener> iterator = list->getIterator();
                    //printf("epollevent observer fd is %d,list size is %d,recvEvents is %p,event is %p \n",fd,list->size(),recvEvents,event);

                    while(iterator->hasValue()) {
                        EPollFileObserverListener c = iterator->getValue();
                        if(ll->get(c) != nullptr) {
                            
                            iterator->next();
                            continue;
                        }
                        
                        if(recvData == nullptr) {
                            //we need read all data
                            int len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);
            
                            ByteArray data = nullptr;
                            if(len > 0) {
                                recvData = createByteArray(readbuff,len);
                                while(len == st(EPollFileObserver)::DefaultBufferSize) {
                                    len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);
                                    recvData->append(readbuff,len);
                                }
                            }
                        }

                        ll->put(c,createBoolean(true));
                        if(c->onEvent(fd,recvEvents,recvData) == st(EPollFileObserver)::OnEventRemoveObserver) {
                            //update c's fds
                            AutoLock l(mRequestMutex);
                            int size = c->fds.size();
                            for(int i = 0;i < size;i++){
                                if(c->fds[i] == fd) {
                                    c->events[i] = (c->events[i]&~recvEvents);
                                    c->fds[i] = 0;
                                    break;
                                }
                            }
                            iterator->remove();
                            continue;
                        };
                        iterator->next();
                    }
                    
                    if(list->size() == 0) {
                        map->remove(event);
                    }
                }
            }
            
            if((recvEvents & (EpollRdHup|EpollHup)) != 0) {
                //map->remove(EpollRdHup);
                //map->remove(EpollHup);
                mListeners->remove(fd);
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
                close(fd);
            }else if(map->size() == 0) {
                mListeners->remove(fd);
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
                close(fd);
            }
        }
    }
}

_EPollFileObserver::_EPollFileObserver(int size) {
    mListeners = createHashMap<int,HashMap<int,ArrayList<EPollFileObserverListener>>>();
    mSize = size;
    mRequestMutex = createMutex("Epoll Mutex");
    mReqeusts = createArrayList<EpollObserverRequest>();
    
    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    mPipe->init();
    //addObserver(mPipe->getReadPipe(),EPOLLIN|EPOLLRDHUP|EPOLLHUP,nullptr);
    addEpollFd(mPipe->getReadPipe(),EPOLLIN|EPOLLRDHUP|EPOLLHUP);

    mStartFlag = createAtomicInteger(0);
    start();
    while(mStartFlag->getAndAnd(1) != 1) {}
}

void _EPollFileObserver::doRequest() {
    AutoLock l(mRequestMutex);
    ListIterator<EpollObserverRequest> iterator = mReqeusts->getIterator();
    while(iterator->hasValue()) {
        EpollObserverRequest r = iterator->getValue();
        switch(r->action) {
            case st(EpollObserverRequest)::Remove:
                _removeObserver(r->fd,r->event,r->l);
                break;

            case st(EpollObserverRequest)::Add:
                _addObserver(r->fd,r->event,r->l);
                break;
        }
        iterator->next();
    }
    mReqeusts->clear();
}

_EPollFileObserver::_EPollFileObserver():_EPollFileObserver{DefaultEpollSize}{
}

int _EPollFileObserver::addObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    if(fd <= -1) {
        return -InvalidParam;
    }

    //check whether registed
    struct epoll_event ev;
    memset(&ev,0,sizeof(struct epoll_event));

    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);

    int size = l->fds.size();
    int index = 0;
    uint32_t observerEvent = 0;
    
    {
        AutoLock ll(mRequestMutex);
        for(;index<size;index++) {
            if(l->fds[index] == fd) {
                if(events & (~l->events[index]) == 0) {
                    return 0;
                }
                break;
            }
        }
    }

    if(size != 0) {
        observerEvent = l->events[index];
    } else {
        l->fds.push_back(fd);
        l->events.push_back(events);
    }

    EpollObserverRequest request = createEpollObserverRequest();
    request->action = st(EpollObserverRequest)::Add;
    request->event = (events & (~observerEvent));
    request->l = l;
    request->fd = fd;

    {
        AutoLock lock(mRequestMutex);
        //update events
        l->events[index] = observerEvent|= events;
        mReqeusts->add(request);
    }
    
    ByteArray data = createByteArray(1);
    data->fill(0,0);
    mPipe->writeTo(data);

    return 0;
}

int _EPollFileObserver::removeObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    int index = 0;
    uint32_t observerEvent = 0;

    AutoLock lock(mRequestMutex);
    int size = l->fds.size();
    for(;index<size;index++) {
        if(l->fds[index] == fd) {
            uint32_t observerEvent = l->events[index];
            if((events & observerEvent)!=0) {
                EpollObserverRequest request = createEpollObserverRequest();
                request->action = st(EpollObserverRequest)::Remove;
                request->event = (~observerEvent & events);
                request->l = l;
                l->events[index] = (observerEvent|events);
                
                AutoLock lock(mRequestMutex);
                mReqeusts->add(request);

                ByteArray data = createByteArray(1);
                data->fill(0,0);
                mPipe->writeTo(data);
                return 0;
            }
            
            struct epoll_event ev;
            ev.events = l->events[index];
            epoll_ctl(mEpollFd, EPOLL_CTL_MOD,fd, &ev);
        }
    }

    return -1;
}

int _EPollFileObserver::removeObserver(EPollFileObserverListener l) {
    AutoLock lock(mRequestMutex);
    int size = l->fds.size();
    int index = 0;
    for(;index<size;index++) {
        int fd = l->fds[index];
        
        EpollObserverRequest request = createEpollObserverRequest();
        request->action = st(EpollObserverRequest)::Remove;
        request->event = l->events[index];
        request->l = l;
        request->fd = fd;
        mReqeusts->add(request);

        ByteArray data = createByteArray(1);
        data->fill(0,0);
        mPipe->writeTo(data);
    }

    l->fds.clear();
    l->events.clear();

    return 0;
}

int _EPollFileObserver::_addObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    //printf("add observer fd is %d,events is %p \n",fd,events);
    
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

int _EPollFileObserver::_removeObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    HashMap<int,ArrayList<EPollFileObserverListener>> map = mListeners->get(fd);
    if(map == nullptr) {
        epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
        return 0;
    }
    //printf("_removeObserver,fd is %d,events is %p \n",fd,events);

    for(int i = 0;i<sizeof(EpollEvent)/sizeof(int);i++) {
        int event = events & EpollEvent[i];
        if(event != 0) {
            ArrayList<EPollFileObserverListener> list = map->get(event);
            if(list == nullptr) {
                continue;
            }

            list->remove(l);
            if(list->size() == 0) {
                //printf("_removeObserver,fd is %d,events is %p ,size is 0\n",fd,events);
                map->remove(event);
            }
        }
    }

    if(map->size() == 0) {
        epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    }

    //printf("map size is %d \n",map->size());
    return 0;
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

    mListeners->clear();
    mReqeusts->clear();
    
    return 0;
}

void _EPollFileObserver::dump() {
    MapIterator<int,HashMap<int,ArrayList<EPollFileObserverListener>>> iterator = mListeners->getIterator();
    while(iterator->hasValue()) {
        int fd = iterator->getKey();
        HashMap<int,ArrayList<EPollFileObserverListener>> fdmap = iterator->getValue();
        printf("start fd is %d,regist listener size is %d \n",fd,fdmap->size());
        if(fdmap != nullptr) {
            MapIterator<int,ArrayList<EPollFileObserverListener>> iter2 = fdmap->getIterator();
            while(iter2->hasValue()) {
                int event = iter2->getKey();
                ArrayList<EPollFileObserverListener> list = iter2->getValue();
                printf("    event is %p,listener is %d \n",event,list->size());
                iter2->next();
            }
        }
        iterator->next();
    }
}

_EPollFileObserver::~_EPollFileObserver() {
    release();
}


}

