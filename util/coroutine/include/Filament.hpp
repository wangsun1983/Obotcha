#ifndef __OBOTCHA_FILAMENT_HPP__
#define __OBOTCHA_FILAMENT_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "FilaMutex.hpp"

namespace obotcha {

class _FilaCroutine;
class _FilaMutex;

DECLARE_CLASS(Filament) IMPLEMENTS(Runnable){

  public:
    friend class _FilaCroutine;
    friend class _FilaMutex;

    virtual void run() {};

    void start();

    void resume();

    void yield();

    void destroy();

  private:
    static void *localFilaRun(void *args);

    stCoRoutine_t *coa;

    String mName;
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