#ifndef __OBOTCHA_FILAMENT_HPP__
#define __OBOTCHA_FILAMENT_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "String.hpp"
#include "FilaMutex.hpp"
#include "FilaFuture.hpp"

namespace obotcha {

class _FilaRoutine;

DECLARE_CLASS(Filament) IMPLEMENTS(Runnable){

  public:
    friend class _FilaRoutine;
    friend class _FilaMutex;
    
    enum Type {
        RunWithFuture = 0,
        RunWithOutFuture
    };
    
    _Filament();

    virtual void run() override {
        // Intentionally unimplemented...
    }

    void start();

    void resume();

    void yield();

    void setType(int);

    FilaFuture getFuture();

    bool onInterrupt() override;

    ~_Filament() override;

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
    _LambdaFilament(Function f, Args... args)
        : _Filament(), func(f), _arguments(std::make_tuple(args...)) {}

    void run() override {
        ostd::apply(func, _arguments);
    }

    ~_LambdaFilament() override = default;

private:
    std::tuple<Args...> _arguments;
    Function func;
};

} // namespace obotcha
#endif