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

//EpollObserverRequest---------------------
_EpollObserverRequest::_EpollObserverRequest() {
    action = 0;
    event = 0;
    fd = -1;;
}

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
        //sleep(1);
        doRequest();

        if(epoll_events_count < 0) {
            return;
        }
        
        //StartAutoTimeWatcher("do epoll event");
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            uint32_t recvEvents = events[i].events;

            //printf("epollevent observer fd is %d,recvEvents is %p,epoll_events_count is %d \n",fd,recvEvents,epoll_events_count);
            ByteArray recvData = nullptr;

            ll->clear();

            if(fd == mPipe->getReadPipe()) {
                ByteArray pipeData = createByteArray(1);
                mPipe->readFrom(pipeData);
                if(pipeData->at(0) == 0) {
                    //printf("epollevent break \n");
                    break;
                } else {
                    //printf("epollevent return \n");
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
                        //printf("epollevent observer continue \n");
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
                            c->fd2eventMap[fd] = 0;
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
            
            if(((recvEvents & EpollRdHup) != 0)
               ||(map->size() == 0)) {
                //map->remove(EpollRdHup);
                //map->remove(EpollHup);
                //clear listener's fds
                //printf("start remove fd is %d \n",fd);
                MapIterator<EPollFileObserverListener,Boolean> iterator = ll->getIterator();
                while(iterator->hasValue()) {
                    EPollFileObserverListener ml = iterator->getKey();
                    if(ml->fd2eventMap.find(fd) != ml->fd2eventMap.end()) {
                        //printf("start remove fd is %d,hit!!!,ml is %x \n",fd,ml.get_pointer());
                        ml->fd2eventMap[fd] = 0;
                    }
                    iterator->next();
                }

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
                //printf("start call r->fd is %d,r->event is %p \n",r->fd,r->event);
                _addObserver(r->fd,r->event,r->l);
                break;

            case st(EpollObserverRequest)::RemoveByFd:
                //printf("remove fd is %d \n",r->fd);
                _removeObserver(r->fd);
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

    int index = 0;
    uint32_t observerEvent = 0;
    {
        AutoLock ll(mRequestMutex);
        if(l->fd2eventMap.find(fd) != l->fd2eventMap.end()) {
            observerEvent = l->fd2eventMap[fd];
            if((events|observerEvent) == observerEvent) {
                //printf("wang,,,,, add Observer fd is %d,events is %p,observerEvent is %d return,l is %x \n",fd,events,observerEvent,l.get_pointer());
                return 0;
            }

            l->fd2eventMap[fd] = (observerEvent | events);
        } else {
            l->fd2eventMap[fd] = events;
        }
    }

    //printf("wang,,,,, add Observer fd is %d,events is %p,observerEvent is %d,l is %x \n",fd,events,observerEvent,l.get_pointer());

    EpollObserverRequest request = createEpollObserverRequest();
    request->action = st(EpollObserverRequest)::Add;
    request->event = (events & (uint32_t)(~observerEvent));
    
    request->l = l;
    request->fd = fd;

    {
        AutoLock lock(mRequestMutex);
        mReqeusts->add(request);
    }

    struct epoll_event ev;
    memset(&ev,0,sizeof(struct epoll_event));
    //printf("add observer fd is %d \n",fd);
    
    ev.data.fd = fd;
    ev.events = events|EpollRdHup;
    epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
    
    ByteArray data = createByteArray(1);
    data->fill(0,0);
    mPipe->writeTo(data);

    return 0;
}

int _EPollFileObserver::removeObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    int index = 0;
    uint32_t observerEvent = 0;
    //printf("remove observer,fd is %d \n",fd);

    AutoLock lock(mRequestMutex);

    if(l->fd2eventMap.find(fd) != l->fd2eventMap.end()) {
        uint32_t observerEvent = l->fd2eventMap[fd];
            if((events|observerEvent)!= observerEvent) {
                EpollObserverRequest request = createEpollObserverRequest();
                request->action = st(EpollObserverRequest)::Remove;
                request->event = (~observerEvent & events);
                request->l = l;
                l->fd2eventMap[fd] = (observerEvent|~events);
                
                AutoLock lock(mRequestMutex);
                mReqeusts->add(request);

                ByteArray data = createByteArray(1);
                data->fill(0,0);
                mPipe->writeTo(data);
                return 0;
            }
            
        struct epoll_event ev;
        ev.events = l->fd2eventMap[fd];
        epoll_ctl(mEpollFd, EPOLL_CTL_MOD,fd, &ev);
    }

    return -1;
}

#if 0
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

    l->fd2eventMap.clear();

    return 0;
}
#endif

int _EPollFileObserver::removeObserver(int fd) {
    AutoLock lock(mRequestMutex);
    EpollObserverRequest request = createEpollObserverRequest();
    request->action = st(EpollObserverRequest)::RemoveByFd;
    request->fd = fd;
    mReqeusts->add(request);

    //we should clear 
    HashMap<int,ArrayList<EPollFileObserverListener>> m = mListeners->get(fd);

    MapIterator<int,ArrayList<EPollFileObserverListener>> iterator = m->getIterator();
    while(iterator->hasValue()) {
        ArrayList<EPollFileObserverListener> list = iterator->getValue();
        ListIterator<EPollFileObserverListener> iterator2 = list->getIterator();
        while(iterator2->hasValue()) {
            EPollFileObserverListener ob = iterator2->getValue();
            ob->fd2eventMap.clear();
            iterator2->next();
        }
        iterator->next();
    }

    ByteArray data = createByteArray(1);
    data->fill(0,0);
    mPipe->writeTo(data);
}

int _EPollFileObserver::_addObserver(int fd,uint32_t events,EPollFileObserverListener l) {
    //printf("add observer fd is %d,events is %p \n",fd,events);
    
    if(l != nullptr) {
        //printf("add observer fd is %d,l is not null\n",fd);
        HashMap<int,ArrayList<EPollFileObserverListener>> m = mListeners->get(fd);
        if(m == nullptr) {
            m = createHashMap<int,ArrayList<EPollFileObserverListener>>();
            mListeners->put(fd,m);
        }
        
        for(int i = 0;i<sizeof(EpollEvent)/sizeof(int);i++) {
            int event = (events & EpollEvent[i]);
            //printf("add observer fd is %d,check event is %p\n",fd,event);
            if(event != 0) {
                ArrayList<EPollFileObserverListener> ll = m->get(event);
                if(ll == nullptr) {
                    ll = createArrayList<EPollFileObserverListener>();
                    m->put(event,ll);
                }
                //printf("really add fd is %d,event is %p \n",fd,event);
                ll->add(l);
            }
        }
    }

    return 0;
}

int _EPollFileObserver::_removeObserver(int fd) {
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    mListeners->remove(fd);
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

    //close all fd
    MapIterator<int,HashMap<int,ArrayList<EPollFileObserverListener>>> m = mListeners->getIterator();
    while(m->hasValue()) {
        int fd = m->getKey();
        close(fd);
    }

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

