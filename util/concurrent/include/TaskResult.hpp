#ifndef __OBOTCHA_TASK_RESULT_HPP__
#define __OBOTCHA_TASK_RESULT_HPP__

#include "Object.hpp"
#include "Byte.hpp"
#include "ThreadLocal.hpp"
#include "ExecutorTask.hpp"

namespace obotcha {

DECLARE_CLASS(TaskResult) {

public:
    template<typename T>
    static void set(T value) {
        ExecutorTask t = mTasks->get();
        if(t != nullptr) {
            t->setResult(value);
        }
    }

    static void set(int);
    static void set(byte);
    static void set(double);
    static void set(bool);
    static void set(long);
    static void set(uint16_t);
    static void set(uint32_t);
    static void set(uint64_t);

    static void addTask(ExecutorTask);
    static void removeTask();

private:
    static ThreadLocal<ExecutorTask> mTasks;
};

}

#endif