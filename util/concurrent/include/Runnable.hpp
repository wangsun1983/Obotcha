#ifndef __OBOTCHA_RUNNABLE_HPP__
#define __OBOTCHA_RUNNABLE_HPP__

#include <stdio.h>
#include <future>
#include <utility>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "IllegalStateException.hpp"
#include "Error.hpp"
#include "OStdApply.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

class _Future;
class _ExecutorTask;

DECLARE_SIMPLE_CLASS(Runnable) {

public:
    friend class _Future;
    friend class _ExecutorTask;

	virtual void run() = 0;
    
    virtual void onInterrupt(){};

    virtual ~_Runnable() {}

};

template<class Function,class... Args> 
class _LambdaRunnable:public _Runnable{
public:
    _LambdaRunnable(Function &&f,Args&&... args):_Runnable(),func(f),_arguments(std::make_tuple(args...)) {

    }

    void run() {
        //func(initializer_list(_arguments));
        ostd::apply(func,_arguments);
    }

    ~_LambdaRunnable() {
        //do nothing
    }

private:
    std::tuple<Args...> _arguments;
    Function func;
};

template<typename Callfunc,typename... Args> 
sp<_Runnable> createLambdaRunnable(Callfunc f,Args ...args) {
    _Runnable *r = new _LambdaRunnable<Callfunc,Args ...>(std::forward<Callfunc>(f),
			     std::forward<Args>(args)...);
    return AutoClone(r);
}

}

#endif