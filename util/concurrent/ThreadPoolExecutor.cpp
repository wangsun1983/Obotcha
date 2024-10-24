/**
 * @file ThreadPoolExecutor.cpp
 * @brief  An ThreadPoolExecutor that provides methods to manage termination and
 * methods that can produce a {@link Future} for tracking progress of one or 
 * more asynchronous tasks.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <stdio.h>
#include <stdlib.h>

#include "ThreadPoolExecutor.hpp"
#include "Log.hpp"
#include "TimeWatcher.hpp"
#include "ForEveryOne.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(size_t maxPendingTaskNum,
                                         long defalutThreadNum,
                                         uint32_t maxSubmitTaskWaitTime):_Executor() {
    mPendingTasks = BlockingLinkedList<ExecutorTask>::New(maxPendingTaskNum);
    mHandlers = ArrayList<Thread>::New();
    mRunningTaskMutex = Mutex::New();
    mRunningTasks = List<ExecutorTask>::New(defalutThreadNum);

    mMaxSubmitTaskWaitTime = maxSubmitTaskWaitTime;
    mMaxPendingTaskNum = maxPendingTaskNum;
    mDefaultThreadNum = defalutThreadNum;

    for (int i = 0; i < defalutThreadNum; i++) {
        Thread thread = Thread::New([this](int id,
                            [[maybe_unused]]ThreadPoolExecutor executor) {
            while(true) {
                ExecutorTask mCurrentTask = mPendingTasks->takeFirst();
                Inspect(mCurrentTask == nullptr)
                Synchronized(mRunningTaskMutex) {
                    mRunningTasks[id] = mCurrentTask;
                }

                mCurrentTask->execute();

                Synchronized(mRunningTaskMutex) {
                    mRunningTasks[id] = nullptr;
                }
            }
        },i,AutoClone(this));

        thread->start();
        mHandlers->add(thread);
    }

    updateStatus(st(Concurrent)::Status::Running);
}

Future _ThreadPoolExecutor::submitTask(ExecutorTask task) {
    Inspect(isShutDown(),nullptr)
    task->setPending();
    return mPendingTasks->putLast(task, mMaxSubmitTaskWaitTime)
            ?Future::New(task):nullptr;
}


int _ThreadPoolExecutor::shutdown() {
    Inspect(!isExecuting(),0)

    updateStatus(st(Concurrent)::Status::ShutDown);
    ForEveryOne(task,mPendingTasks) {
        task->cancel();
    }

    mPendingTasks->destroy();
    Synchronized(mRunningTaskMutex) {
        ForEveryOne(tsk,mRunningTasks) {
            if(tsk != nullptr)  {
                tsk->cancel();
            }
        }
    }

    ForEveryOne(t,mHandlers) {
        t->interrupt();
    }

    return 0;
}

bool _ThreadPoolExecutor::isTerminated() {
    ForEveryOne(t,mHandlers) {
        Inspect(t->getStatus() != st(Concurrent)::Status::Complete,false)
    }

    return true;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    Inspect(!isShutDown(),-1)

    bool isWaitForever = (millseconds == 0);
    TimeWatcher watcher = TimeWatcher::New();
    ForEveryOne(handler,mHandlers) {
        watcher->start();
        handler->join(millseconds);
        if (!isWaitForever) {
            if((millseconds -= watcher->stop()) <= 0) {
                return -ETIMEDOUT;
            }
        }
    }

    return 0;
}

size_t _ThreadPoolExecutor::getExecutingThreadNum() {
    return mHandlers->size();
}

size_t _ThreadPoolExecutor::getPendingTaskNum() {
    return mPendingTasks->size();
}

void _ThreadPoolExecutor::onRemoveTask(ExecutorTask task) {
    Inspect(!isExecuting())
    mPendingTasks->remove(task);
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    if(!isShutDown()) {
        LOG(ERROR)<<"ThreadPoolExecutor release without shutdown!!!!";
        try {
            shutdown();
            awaitTermination();
        } catch(...) {
            LOG(ERROR) <<"shutdown/awaitermination exception when destruct ThreadPool";
        }
    }
}

} // namespace obotcha
