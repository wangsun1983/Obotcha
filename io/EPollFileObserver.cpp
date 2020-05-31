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
        int epoll_events_count = epoll_wait(mEpollFd, events, mSize, -1);
        if(epoll_events_count < 0) {
            return;
        }
        for(int i = 0; i < epoll_events_count; i++) {
            int fd = events[i].data.fd;
            int recvEvents = events[i].events;

            if(fd == mPipe->getReadPipe()) {
                return;
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
                    ListIterator<EPollFileObserverListener> iterator = list->getIterator();
                    while(iterator->hasValue()) {
                        EPollFileObserverListener c = iterator->getValue();
                        if(ll->get(c) != nullptr) {
                            continue;
                        }

                        ll->put(c,createBoolean(true));
                        if(c->onEvent(fd,recvEvents,data) == st(EPollFileObserver)::OnEventRemoveObserver) {
                            for(int k = 0;k<sizeof(EpollEvent)/sizeof(int);k++) {
                                int rmEvent = recvEvents & EpollEvent[i];
                                removeObserver(fd,rmEvent,c);
                            }
                        };
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
    mEpollFd = epoll_create(size);
    mPipe = createPipe();
    mPipe->init();
    addObserver(mPipe->getReadPipe(),EPOLLIN|EPOLLRDHUP|EPOLLHUP,nullptr);
    start();
}

_EPollFileObserver::_EPollFileObserver():_EPollFileObserver{DefaultEpollSize}{
}


int _EPollFileObserver::addObserver(int fd,int events,EPollFileObserverListener l) {
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
            int event = events & EpollEvent[i];
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

int _EPollFileObserver::removeObserver(int fd,int event,EPollFileObserverListener l) {

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
        goto remove;
    }

remove:
    epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}

int _EPollFileObserver::release() {
    mPipe->writeTo(createByteArray(1));
    
    join();
    
    if(mEpollFd != -1) {
        close(mEpollFd);
        mEpollFd = -1;
    }

    mListeners->clear();
    
    return 0;
}

_EPollFileObserver::~_EPollFileObserver() {
    close(mEpollFd);
}


}

