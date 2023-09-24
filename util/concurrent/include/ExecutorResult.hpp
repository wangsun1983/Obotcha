#ifndef __OBOTCHA_EXECUTOR_RESULT_HPP__
#define __OBOTCHA_EXECUTOR_RESULT_HPP__

#include "Object.hpp"

#include "Byte.hpp"
#include "Executor.hpp"
#include "NullPointerException.hpp"
#include "ExecutorTask.hpp"

namespace obotcha {

template <typename T> class __ExecutorTaskResult__ {
  public:
    T get(Object value) { return Cast<T>(value); }
};

#define __ExecutorGetResult__(X, Y)                                            \
    template <> class __ExecutorTaskResult__<X> {                              \
      public:                                                                  \
        X get(Object value) {                                                  \
            if (value == nullptr) {                                            \
                Trigger(NullPointerException, "no result")                     \
            }                                                                  \
            auto v = Cast<Y>(value);                                           \
            if (v == nullptr) {                                                \
                Trigger(NullPointerException, "no result")                     \
            }                                                                  \
            return v->toValue();                                               \
        }                                                                      \
    };

__ExecutorGetResult__(int,Integer);
__ExecutorGetResult__(byte,Byte);
__ExecutorGetResult__(double,Double);
__ExecutorGetResult__(float,Float);
__ExecutorGetResult__(bool,Boolean);
__ExecutorGetResult__(long,Long);
__ExecutorGetResult__(uint16_t,Uint16);
__ExecutorGetResult__(uint32_t,Uint32);
__ExecutorGetResult__(uint64_t,Uint64);

DECLARE_CLASS(ExecutorResult) {
  public:
    template <typename T> static void Set(T value) {
        auto task = st(Executor)::GetCurrentTask();
        task->mResult->update(value);
    }

    void update(int);
    void update(byte);
    void update(double);
    void update(float);
    void update(bool);
    void update(long);
    void update(uint16_t);
    void update(uint32_t);
    void update(uint64_t);

    template <typename T> void update(T v) { 
        mResult = v; 
    }

    template <typename T> T get() { 
        return __ExecutorTaskResult__<T>().get(mResult); 
    }

  private:
    Object mResult;
};

} // namespace obotcha

#endif