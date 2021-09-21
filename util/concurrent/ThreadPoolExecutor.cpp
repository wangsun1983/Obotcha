#include <stdio.h>
#include <stdlib.h>

#include "Error.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "TimeWatcher.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(int capacity, int threadnum) {
    mPool = createBlockingLinkedList<ExecutorTask>(capacity);
    mHandlers = createArrayList<Thread>();

    for (int i = 0; i < threadnum; i++) {
        Thread thread = createThread(
            [](ThreadPoolExecutor executor) {
                while (1) {
                    ExecutorTask mCurrentTask = executor->mPool->takeFirst();

                    if (mCurrentTask == nullptr) {
                        // clear executor to enable executor release.
                        executor = nullptr;
                        return;
                    }
                    mCurrentTask->execute();
                }
            },
            AutoClone(this));

        thread->start();
        mHandlers->add(thread);
    }

    mMutex = createMutex();
    mStatus = Executing;
}

int _ThreadPoolExecutor::shutdown() {
    {
        AutoLock l(mMutex);
        if (mStatus != Executing) {
            return -AlreadyDestroy;
        }

        mStatus = ShutDown;
    }

    mPool->freeze();
    mPool->foreach ([](ExecutorTask task) {
        task->cancel();
        return Global::Continue;
    });

    mPool->destroy();
    mPool->unfreeze();

    // interrupt all thread
    mHandlers->foreach ([](Thread t) {
        t->interrupt();
        return Global::Continue;
    });

    return 0;
}

bool _ThreadPoolExecutor::isShtuDown() {
    AutoLock l(mMutex);
    return mStatus == ShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    bool isAllTerminated = true;
    mHandlers->foreach ([&isAllTerminated](Thread &t) {
        if (t->getStatus() != st(Thread)::Complete) {
            isAllTerminated = false;
            return Global::Break;
        }
        return Global::Continue;
    });

    return isAllTerminated;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    {
        AutoLock l(mMutex);
        if (mStatus != ShutDown) {
            return -InvalidStatus;
        }
    }

    bool isWaitForever = (millseconds == 0);
    ListIterator<Thread> iterator = mHandlers->getIterator();
    TimeWatcher watcher = createTimeWatcher();

    while (iterator->hasValue()) {
        Thread handler = iterator->getValue();
        watcher->start();
        handler->join(millseconds);
        if (!isWaitForever) {
            millseconds -= watcher->stop();
            if (millseconds <= 0) {
                return -WaitTimeout;
            }
        }
        iterator->next();
    }

    return 0;
}

int _ThreadPoolExecutor::getThreadsNum() { return mHandlers->size(); }

int _ThreadPoolExecutor::getTasksNum() { return mPool->size(); }

_ThreadPoolExecutor::~_ThreadPoolExecutor() {}

} // namespace obotcha
