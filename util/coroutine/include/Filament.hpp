#ifndef __OBOTCHA_FILAMENT_HPP__
#define __OBOTCHA_FILAMENT_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "FilaMutex.hpp"
#include "OStdApply.hpp"
#include "FilaFuture.hpp"
#include "FilaExecutorResult.hpp"

namespace obotcha {

class _FilaRoutine;
class _FilaMutex;

DECLARE_CLASS(Filament) IMPLEMENTS(Runnable){

  public:
    friend class _FilaRoutine;
    friend class _FilaMutex;
    
    enum Type {
        RunWithFuture = 0,
        RunWithOutFuture
    };
    
    _Filament();

    virtual void run() {};

    void start();

    void resume();

    void yield();

    //void destroy();
    void setType(int);

    FilaFuture getFuture();

    bool onInterrupt();

    ~_Filament();

  private:
    static void *localFilaRun(void *args);
    static void *onComplete(void *args);
    
    void markAsReleased();

    FilaFuture genFuture();

    stCoRoutine_t *coa;

    String mName;

    FilaFuture mFuture;
};

template <class Function, class... Args>
class _LambdaFilament : public _Filament {
public:
    _LambdaFilament(Function &&f, Args &&... args)
        : _Filament(), func(f), _arguments(std::make_tuple(args...)) {}

    void run() {
        // func(initializer_list(_arguments));
        ostd::apply(func, _arguments);
    }

    ~_LambdaFilament() {
        // do nothing
    }

private:
    std::tuple<Args...> _arguments;
    Function func;
};

template <typename Callfunc, typename... Args>
sp<_Filament> createLambdaFilament(Callfunc f, Args... args) {
    _Filament *r = new _LambdaFilament<Callfunc, Args...>(
        std::forward<Callfunc>(f), std::forward<Args>(args)...);
    return AutoClone(r);
}

} // namespace obotcha
#endif