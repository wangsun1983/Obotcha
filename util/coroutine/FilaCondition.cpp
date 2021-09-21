#include "FilaCondition.hpp"

namespace obotcha {

_FilaCondition::_FilaCondition() { mCond = co_cond_alloc(); }

void _FilaCondition::wait() { co_cond_timedwait(mCond, -1); }

void _FilaCondition::wait(long mseconds) { co_cond_timedwait(mCond, mseconds); }

void _FilaCondition::notify() { co_cond_signal(mCond); }

void _FilaCondition::notifyAll() { co_cond_broadcast(mCond); }

_FilaCondition::~_FilaCondition() { co_cond_free(mCond); }

} // namespace obotcha