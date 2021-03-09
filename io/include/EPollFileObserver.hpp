#ifndef __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__
#define __OBOTCHA_EPOLL_FILE_OBSERVER_HPP__

#include <sys/epoll.h>
#include <map>
#include <stdio.h>
#include <future>
#include <utility>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "Thread.hpp"
#include "Pipe.hpp"
#include "OStdApply.hpp"


namespace obotcha {

class _EPollFileObserver;

DECLARE_SIMPLE_CLASS(EPollFileObserverListener) {
public:
    friend class _EPollFileObserver;

    virtual int onEvent(int fd,uint32_t events,ByteArray) = 0;

private:
    int notifyEvent(int fd,uint32_t events,ByteArray);
    std::map<int,int> mFdEventsMap;
};

template<class Function,class... Args>
class _LambdaEPollFileObserverListener:public _EPollFileObserverListener{
public:
    _LambdaEPollFileObserverListener(Function &&f,Args&&... args):_EPollFileObserverListener(),func(f),_arguments(std::make_tuple(args...)) {

    }

    int onEvent(int fd,uint32_t events,ByteArray data) {
        auto param = std::tuple_cat(std::make_tuple(fd,events,data),_arguments);
        return ostd::apply(func,param);
    }

private:
    std::tuple<Args...> _arguments;
    Function func;
};

template<typename Callfunc,typename... Args> 
sp<_EPollFileObserverListener> createLambdaEPollFileObserverListener(Callfunc f,Args ...args) {
    _EPollFileObserverListener *r = new _LambdaEPollFileObserverListener<Callfunc,Args ...>(std::forward<Callfunc>(f),
			     std::forward<Args>(args)...);
    return AutoClone(r);
}

DECLARE_SIMPLE_CLASS(EPollFileObserver) EXTENDS(Thread) {
public:
    _EPollFileObserver(int size);

    _EPollFileObserver();

    template<typename X>
    int addObserver(int fd,uint32_t events,sp<X> l) {
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

        ll->add(Cast<EPollFileObserverListener>(l));
        updateFdEventsMap(fd,events,l->mFdEventsMap);
        updateFdEventsMap(fd,events,mFdEventsMap);

        addEpollFd(fd,regEvents|EpollRdHup|EPOLLHUP);
        return 0;
    }

    //wangsl add lambda function
    template< class Function, class... Args >
    int addObserver(int fd,uint32_t events,Function&& f, Args&&... args ) {
        //printf("addObserver start \n");
        EPollFileObserverListener l = createLambdaEPollFileObserverListener(f,args...);
        return addObserver(fd,events,l);
    }
    //wangsl add lambda function

    int removeObserver(int fd);

    int removeObserver(EPollFileObserverListener l);

    int release();

    void run();
    
    ~_EPollFileObserver();
    
    enum EpollEvent {
        EpollIn = EPOLLIN,
        EpollPri = EPOLLPRI,
        EpollOut = EPOLLOUT,
        EpollRdNorm = EPOLLRDNORM,
        EpollRdBand = EPOLLRDBAND,
        EpollWrNorm = EPOLLWRNORM,
        EpollWrBand = EPOLLWRBAND,
        EpollMsg = EPOLLMSG,
        EpollErr = EPOLLERR,
        EpollHup = EPOLLHUP,
        EpollRdHup = EPOLLRDHUP,
#ifdef EPOLLEXCLUSIVE    
        EpollExClusive = EPOLLEXCLUSIVE,
#endif
        EpollWakeUp = EPOLLWAKEUP,
        EpollOneShot = EPOLLONESHOT,
        EpollEt = EPOLLET,
    };

    static const int OnEventOK = 0;
    static const int OnEventRemoveObserver = 1;

    static const int DefaultEpollSize = 1024*8;
    
private:
    static const int DefaultBufferSize = 16*1024;
    static const int DefaultMaxBuffSize = 1024*1024;
    static const uint32_t EpollEvent[];
    
    void addEpollFd(int fd,uint32_t events);

    void updateFdEventsMap(int fd,uint32_t events,std::map<int,int> &maps);

    int mEpollFd;

    Mutex mListenerMutex;
    HashMap<int,ArrayList<EPollFileObserverListener>> mListeners;
    std::map<int,int> mFdEventsMap;
    
    Pipe mPipe;

    int mSize;
};

}
#endif
