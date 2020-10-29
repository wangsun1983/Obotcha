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
void _EPollFileObserverListener::removeFd(int fd) {
    auto iter = fds.begin();
    while (iter != fds.end()) {
        if (*iter == fd) {
            iter = fds.erase(iter);
            continue;
        }

        iter++;
    }
}

//----------------_EPollFileObserver----------------
void _EPollFileObserver::run() {
    struct epoll_event events[mSize];
    memset(events,0,sizeof(struct epoll_event) *mSize);
    byte readbuff[st(EPollFileObserver)::DefaultBufferSize];
    HashMap<EPollFileObserverListener,Boolean> ll = createHashMap<EPollFileObserverListener,Boolean>();

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
            ByteArray recvData = nullptr;
            ll->clear();
            
            AutoLock l(mListenerMutex);
            HashMap<int,ArrayList<EPollFileObserverListener>> map = mListeners->get(fd);
            if(map == nullptr || map->size() == 0) {
                LOG(ERROR)<<"Fd not regist,it is "<<fd;
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
                    while(iterator->hasValue()) {
                        EPollFileObserverListener c = iterator->getValue();
                        if(ll->get(c) != nullptr) {
                            //already called
                            iterator->next();
                            continue;
                        }
                        
                        if(recvData == nullptr) {
                            //we need read all data
                            int len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);
                            if(len > 0) {
                                recvData = createByteArray(readbuff,len);
                                if(len == st(EPollFileObserver)::DefaultBufferSize) {
                                    while(1) {
                                        len = read(fd,readbuff,st(EPollFileObserver)::DefaultBufferSize);
                                        if(len <= 0) {
                                            break;
                                        }
                                        recvData->append(readbuff,len);
                                        //too large content,send part data to observers first.
                                        if(recvData->size() >= DefaultMaxBuffSize) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        
                        if(c->onEvent(fd,recvEvents,recvData) == st(EPollFileObserver)::OnEventRemoveObserver) {
                            //remove listener
                            MapIterator<int,ArrayList<EPollFileObserverListener>> rmItemIterator = map->getIterator();
                            while(rmItemIterator->hasValue()) {
                                ArrayList<EPollFileObserverListener> rmLists = rmItemIterator->getValue();
                                if(rmLists != nullptr) {
                                    rmLists->remove(c);
                                }
                                
                                if(rmLists->size() == 0) {
                                    rmItemIterator->remove();
                                } else {
                                    rmItemIterator->next();
                                }
                            }
                            c->removeFd(fd);
                        }

                        if(recvEvents & (EpollRdHup|EPOLLHUP) != 0) {
                            c->removeFd(fd);
                        }

                        ll->put(c,createBoolean(true));
                        iterator->next();
                    }
                }
            }
            
            if(((recvEvents & (EpollRdHup|EPOLLHUP)) != 0)
               ||(map->size() == 0)) {
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
    //printf("_EPollFileObserver addObserver,fd is %d \n",fd);
    if(fd <= -1) {
        return -InvalidParam;
    }

    if(l != nullptr) {
        AutoLock mylock(mListenerMutex);
        //check whether allready regist
        int length = l->fds.size();
        for (int i =0; i < length; i ++) {
            if(fd == l->fds[i]) {
                return -AlreadyRegist;
            }
        }

        l->fds.push_back(fd);

        HashMap<int,ArrayList<EPollFileObserverListener>> m = mListeners->get(fd);
        if(m == nullptr) {
            m = createHashMap<int,ArrayList<EPollFileObserverListener>>();
            mListeners->put(fd,m);
        }
        
        for(int i = 0;i<sizeof(EpollEvent)/sizeof(uint32_t);i++) {
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

        struct epoll_event ev;
        memset(&ev,0,sizeof(struct epoll_event));
        //printf("add observer fd is %d \n",fd);
        
        ev.data.fd = fd;
        ev.events = events|EpollRdHup|EPOLLHUP;
        epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
    }

    return 0;
}

int _EPollFileObserver::removeObserver(EPollFileObserverListener l) {
    AutoLock mylock(mListenerMutex);
    int length = l->fds.size();
    for(int i = 0;i < length;i++) {
        int fd = l->fds[i];
        HashMap<int,ArrayList<EPollFileObserverListener>> m = mListeners->get(fd);
        if(m != nullptr) {
            MapIterator<int,ArrayList<EPollFileObserverListener>> mapiterator = m->getIterator();
            while(mapiterator->hasValue()) {
                ArrayList<EPollFileObserverListener> list = mapiterator->getValue();
                list->remove(l);
                if(list->size() == 0) {
                    mapiterator->remove();
                } else {
                    mapiterator->next();
                }
            }
            if(m->size() == 0) {
                epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
            }
        }
    }
    return 0;
}


int _EPollFileObserver::removeObserver(int fd) {
    //we should clear
    AutoLock l(mListenerMutex);
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
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

    //close all fd
    AutoLock l(mListenerMutex);
    MapIterator<int,HashMap<int,ArrayList<EPollFileObserverListener>>> m = mListeners->getIterator();
    while(m->hasValue()) {
        int fd = m->getKey();
        close(fd);
    }

    mListeners->clear();
    
    return 0;
}

void _EPollFileObserver::dump() {
    MapIterator<int,HashMap<int,ArrayList<EPollFileObserverListener>>> iterator = mListeners->getIterator();
    while(iterator->hasValue()) {
        int fd = iterator->getKey();
        HashMap<int,ArrayList<EPollFileObserverListener>> fdmap = iterator->getValue();
        if(fdmap != nullptr) {
            MapIterator<int,ArrayList<EPollFileObserverListener>> iter2 = fdmap->getIterator();
            while(iter2->hasValue()) {
                int event = iter2->getKey();
                ArrayList<EPollFileObserverListener> list = iter2->getValue();
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

