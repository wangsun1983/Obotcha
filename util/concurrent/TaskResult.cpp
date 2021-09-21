#include "TaskResult.hpp"

namespace obotcha {

ThreadLocal<ExecutorTask> _TaskResult::mTasks =
    createThreadLocal<ExecutorTask>();

void _TaskResult::set(int v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createInteger(v));
    }
}

void _TaskResult::set(byte v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createByte(v));
    }
}

void _TaskResult::set(double v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createDouble(v));
    }
}

void _TaskResult::set(bool v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createBoolean(v));
    }
}

void _TaskResult::set(long v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createLong(v));
    }
}

void _TaskResult::set(uint16_t v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createUint16(v));
    }
}

void _TaskResult::set(uint32_t v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createUint32(v));
    }
}

void _TaskResult::set(uint64_t v) {
    ExecutorTask t = mTasks->get();
    if (t != nullptr) {
        t->setResult(createUint64(v));
    }
}

void _TaskResult::addTask(ExecutorTask t) { mTasks->set(t); }

void _TaskResult::removeTask() { mTasks->remove(); }

} // namespace obotcha