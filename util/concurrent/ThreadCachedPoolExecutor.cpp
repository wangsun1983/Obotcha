#include "ThreadCachedPoolExecutor.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "Thread.hpp"
#include "TimeWatcher.hpp"
#include "ForEveryOne.hpp"
#include "Inspect.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

//---------------ThreadCachedPoolExecutor ---------------------
_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int maxPendingTaskNum, 
                                                     int maxThreadNum, 
                                                     int minThreadNum,
                                                     uint32_t maxSubmitTaskWaittime,
                                                     uint32_t maxNoWorkingTime):_Executor() {
    Panic(minThreadNum > maxThreadNum,
        InitializeException, "ThreadCachedPool illeagal param")
    mMaxThreadNum = maxThreadNum;
    mMinThreadNum = minThreadNum;
    mMaxNoWorkingTime = maxNoWorkingTime;
    mMaxSubmitTaskWaitTime = maxSubmitTaskWaittime;

    mHandlers = createConcurrentQueue<Thread>();
    mTasks = createBlockingLinkedList<ExecutorTask>(maxPendingTaskNum);
    mRunningTasks = createConcurrentHashMap<int,ExecutorTask>();
    updateStatus(Executing);

    mIdleNum = createAtomicInteger(0);
    handlerId = 0;
}

int _ThreadCachedPoolExecutor::shutdown() {
    Inspect(!isExecuting(),0)
    updateStatus(ShutDown);
    ForEveryOne(task,mTasks) {
        task->cancel();
    }

    mTasks->destroy();
    // notify all thread to close
    ForEveryOne(pair,mRunningTasks) {
        auto task = pair->getValue();
        task->cancel();
    }

    mRunningTasks->clear();
    ForEveryOne(t,mHandlers) {
        t->interrupt();
    }
    
    return 0;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    ForEveryOne(t,mHandlers) {
        Inspect(t->getStatus() != st(Thread)::Complete,false)
    }
    return true;
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    Inspect(isExecuting(),-1)

    bool isWaitForever = (millseconds == 0);
    ArrayList<Thread> list = mHandlers->toArray();
    
    TimeWatcher watcher = createTimeWatcher();
    ForEveryOne(handler,list) {        
        watcher->start();
        handler->join(millseconds);
        long interval = watcher->stop();

        if (!isWaitForever) {
            if ((millseconds -= interval) <= 0) {
                return -ETIMEDOUT;
            }
        }
    }
    return 0;
}

int _ThreadCachedPoolExecutor::getExecutingThreadNum() {
    return mHandlers->size();
}

int _ThreadCachedPoolExecutor::getPendingTaskNum() {
    return mTasks->size();
}

Future _ThreadCachedPoolExecutor::submitTask(ExecutorTask task) {
    Inspect(!isExecuting(),nullptr)
    task->setPending();
    mTasks->putLast(task, mMaxSubmitTaskWaitTime);
    if (mIdleNum->get() == 0) {
        setUpOneIdleThread();
    }
    return createFuture(task);
}

void _ThreadCachedPoolExecutor::onRemoveTask(ExecutorTask task) {
    Inspect(!isExecuting())
    mTasks->remove(task);
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    if(!isShutDown()) {
        LOG(ERROR)<<"ThreadCachedPoolExecutor release without shutdown!!!!";
        try {
            shutdown();
            awaitTermination();
        } catch(...) {
            LOG(ERROR) << "shutdown/awaitermination exception when destruct ThreadCachedPool";
        }
    }
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    Inspect(!isExecuting()||mHandlers->size() >= mMaxThreadNum)
    
    Thread handler = createThread(
        [this](ThreadCachedPoolExecutor executor) {
            auto exec = executor;//use this to keep executor instance
            handlerId++;
            InfiniteLoop {
                auto mCurrentTask = mTasks->takeFirst(mMaxNoWorkingTime);
                mIdleNum->subAndGet(1);
                if (mCurrentTask == nullptr) {
                    Thread handler = st(Thread)::current();
                    mHandlers->remove(handler);
                    exec = nullptr;
                    return;
                }

                mRunningTasks->put(handlerId,mCurrentTask);
                mCurrentTask->execute();
                mRunningTasks->remove(handlerId);
                mIdleNum->addAndGet(1);
            }
        },
        AutoClone(this));

    mHandlers->add(handler);
    mIdleNum->addAndGet(1);
    handler->start();
}

} // namespace obotcha
