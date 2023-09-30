#include "FilaExecutorResult.hpp"

namespace obotcha {

HashMap<uint64_t,FilaExecutorResult> _FilaExecutorResult::gFilaExecutorResults
    = createHashMap<uint64_t,FilaExecutorResult>();

void _FilaExecutorResult::BindResult(stCoRoutine_t *co,FilaExecutorResult r) {
    gFilaExecutorResults->put((uint64_t)co,r);
}

void _FilaExecutorResult::UnBindResult(stCoRoutine_t *co) {
    gFilaExecutorResults->remove((uint64_t)co);
}


} // namespace obotcha
