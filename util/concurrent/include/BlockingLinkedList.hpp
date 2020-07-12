#ifndef __OBOTCHA_BLOCKING_LINKED_LIST_HPP__
#define __OBOTCHA_BLOCKING_LINKED_LIST_HPP__

#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "InitializeException.hpp"
#include "IllegalStateException.hpp"
#include "LinkedList.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"

using namespace std;

namespace obotcha {

DECLARE_CLASS(BlockingLinkedList,1) {
public:
    _BlockingLinkedList(int capacity = -1) {
        mMutex = createMutex("BlockingLinkedList");
        mList = createLinkedList<T>();
        mCapacity = capacity;
        mEnqueueCond = createCondition();
        mDequeueCond = createCondition();
        isDestroy = false;
    }

    int size() {
        AutoLock l(mMutex);
        return mList->size();
    }

    inline void enQueueFirst(T val) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return;
            }

            int size = mList.size();
            if(mCapacity != -1 && size == mCapacity) {
               mEnqueueCond->wait(mMutex);
               continue;
            }

            mList->enQueueFirst(val);
            mDequeueCond->notify();
            break;
        }
    }

    inline void enQueueLast(T val) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return;
            }
            
            int size = mList->size();
            if(mCapacity != -1 && size == mCapacity) {
               mEnqueueCond->wait(mMutex);
               continue;
            }

            mList->enQueueLast(val);
            mDequeueCond->notify();
            break;
        }
    }

    inline bool enQueueFirst(T val,long timeout) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return false;
            }
            
            int size = mList.size();
            if(mCapacity != -1 && size == mCapacity) {
               if(mEnqueueCond->wait(mMutex,timeout) == -WaitTimeout) {
                   return false;
               }
               continue;
            }

            mList->enQueueFirst(val);
            mDequeueCond->notify();
            break;
        }

         return true;
    }


    inline bool enQueueLast(T val,long timeout) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return false;
            }
            
            int size = mList.size();
            if(mCapacity != -1 && size == mCapacity) {
               if(mEnqueueCond->wait(mMutex,timeout) == -WaitTimeout) {
                   return false;
               }
               continue;
            }

            mList->enQueueLast(val);
            mDequeueCond->notify();
            break;
        }

        return true;
    }

    //inline bool remove(T val); 

    //dequeue
    inline T deQueueFirst() {
        T ret;
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                throw IllegalStateException("dequeue");
            }
            
            int size = mList->size();
            if(size == 0) {
                mDequeueCond->wait(mMutex);
                continue;
            }

            ret = mList->deQueueFirst();
            mEnqueueCond->notify();        
            break;
        }

        return ret;
    }

    inline T deQueueLast() {
        T ret;
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                throw IllegalStateException("dequeue");
            }
            int size = mList->size();
            if(size == 0) {
                mDequeueCond->wait(mMutex);
                continue;
            }

            ret = mList->deQueueLast();
            mEnqueueCond->notify();        
            break;
        }

        return ret;
    }

    inline T deQueueFirst(long timeout) {
        T ret;
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                throw IllegalStateException("dequeue");
            }
            int size = mList->size();
            if(size == 0) {
                if(mDequeueCond->wait(mMutex,timeout) == -WaitTimeout) {
                    return nullptr;
                }

                continue;
            }

            ret = mList->deQueueFirst();
            mEnqueueCond->notify();        
            break;
        }

        return ret;
    }

    inline T deQueueLast(long timeout) {
        T ret;
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                throw IllegalStateException("dequeue");
            }
            int size = mList->size();
            if(size == 0) {
                if(mDequeueCond->wait(mMutex,timeout) == -WaitTimeout) {
                    return nullptr;
                }

                continue;
            }

            ret = mList->deQueueLast();
            mEnqueueCond->notify();        
            break;
        }

        return ret;
    }

    //add interface for async
    inline T deQueueFirstNoBlock() {
        T ret;
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                throw IllegalStateException("dequeue");
            }
            int size = mList->size();
            if(size == 0) {
                return nullptr;
            }

            ret = mList->deQueueFisrt();
            mEnqueueCond->notify();   
            break;
        }
        return ret;
    }

    inline T deQueueLastNoBlock() {
        T ret;
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                throw IllegalStateException("dequeue");
            }
            int size = mList->size();
            if(size == 0) {
                return nullptr;
            }

            ret = mList->deQueueLast();
            mEnqueueCond->notify();   
            break;
        }
        return ret;
    }

    //destroy
    inline void destroy() {
        AutoLock l(mMutex);
        isDestroy = true;
    }

    inline void clear() {
        //TODO
    }

private:
    LinkedList<T> mList;
    int mCapacity;
    Mutex mMutex;
    Condition mEnqueueCond;
    Condition mDequeueCond;
    bool isDestroy;
};

}
#endif