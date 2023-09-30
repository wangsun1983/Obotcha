#ifndef __OBOTCHA_FILA_EXECUTOR_RESULT_HPP__
#define __OBOTCHA_FILA_EXECUTOR_RESULT_HPP__

#include "co_routine.h"
#include "co_routine_inner.h"

#include "Object.hpp"
#include "ExecutorResult.hpp"
#include "HashMap.hpp"

namespace obotcha {

class _Filament;

DECLARE_CLASS(FilaExecutorResult) IMPLEMENTS(ExecutorResult) {
public:
    friend class _Filament;
    template <typename T> static void Set(T value) {
        auto co = GetCurrThreadCo();
        if(co != nullptr) {
            auto result = gFilaExecutorResults->get((uint64_t)co);
            if(result != nullptr) {
                result->update(value);
            }
        }
    }

private:
    static void BindResult(stCoRoutine_t *,FilaExecutorResult);
    static void UnBindResult(stCoRoutine_t *);
    static HashMap<uint64_t,FilaExecutorResult> gFilaExecutorResults;
};

} // namespace obotcha
#endif
