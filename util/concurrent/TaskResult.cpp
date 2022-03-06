#include "TaskResult.hpp"

namespace obotcha {

ThreadLocal<ExecutorTask> _TaskResult::mTasks = createThreadLocal<ExecutorTask>();

#define TASK_RESULT_SET(X)              \
    ExecutorTask t = mTasks->get();     \
    if (t != nullptr) {                 \
        t->setResult(X);                \
    }

void _TaskResult::set(int v) {
    TASK_RESULT_SET(createInteger(v));
}

void _TaskResult::set(byte v) {
    TASK_RESULT_SET(createByte(v));
}

void _TaskResult::set(double v) {
    TASK_RESULT_SET(createDouble(v));
}

void _TaskResult::set(bool v) {
    TASK_RESULT_SET(createBoolean(v));
}

void _TaskResult::set(long v) {
    TASK_RESULT_SET(createLong(v));
}

void _TaskResult::set(uint16_t v) {
    TASK_RESULT_SET(createUint16(v));
}

void _TaskResult::set(uint32_t v) {
    TASK_RESULT_SET(createUint32(v));
}

void _TaskResult::set(uint64_t v) {
    TASK_RESULT_SET(createUint64(v));
}

#undef TASK_RESULT_SET

void _TaskResult::addTask(ExecutorTask t) { 
    mTasks->set(t); 
}

void _TaskResult::removeTask() { 
    mTasks->remove(); 
}

} // namespace obotcha