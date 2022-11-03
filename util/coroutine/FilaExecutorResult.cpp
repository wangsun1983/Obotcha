#include "FilaExecutorResult.hpp"

namespace obotcha {

HashMap<uint64_t,FilaExecutorResult> _FilaExecutorResult::FilaExecutorResults
    = createHashMap<uint64_t,FilaExecutorResult>();

void _FilaExecutorResult::bindResult(stCoRoutine_t *co,FilaExecutorResult r) {
    FilaExecutorResults->put((uint64_t)co,r);
}

void _FilaExecutorResult::unBindResult(stCoRoutine_t *co) {
    FilaExecutorResults->remove((uint64_t)co);
}


} // namespace obotcha
