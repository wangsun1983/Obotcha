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

template<typename T>
class __RunnableResult {
public:
    T get(Object value) {
        return Cast<T>(value);
    }
};

#define __RunnableResultMacro(X,Y) \
template<> \
class __RunnableResult<X> { \
public: \
    X get(Object value) { \
        if(value == nullptr) { \
            Trigger(NullPointerException,"no result"); \
        }\
        return Cast<Y>(value)->toValue(); \
    } \
};

__RunnableResultMacro(int,Integer)
__RunnableResultMacro(byte,Byte)
__RunnableResultMacro(double,Double)
__RunnableResultMacro(bool,Boolean)
__RunnableResultMacro(float,Double)
__RunnableResultMacro(long,Long)
__RunnableResultMacro(uint16_t,Uint16)
__RunnableResultMacro(uint32_t,Uint32)
__RunnableResultMacro(uint64_t,Uint64)

DECLARE_SIMPLE_CLASS(Runnable) {

public:
    friend class _Future;
    friend class _ExecutorTask;

	virtual void run() = 0;
    
    virtual void onInterrupt(){};

    virtual ~_Runnable() {}

    template<typename T>
    void setResult(T value) {
        mResult = value;
    }

    void setResult(int);
    void setResult(byte);
    void setResult(double);
    void setResult(bool);
    void setResult(long);
    void setResult(uint16_t);
    void setResult(uint32_t);
    void setResult(uint64_t);

private:
    sp<_Object> mResult;

    template<typename T>
    T getResult() {
        return __RunnableResult<T>().get(mResult);
    }
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