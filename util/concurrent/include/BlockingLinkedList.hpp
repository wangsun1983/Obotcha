#ifndef __OBOTCHA_BLOCKING_LINKED_LIST_HPP__
#define __OBOTCHA_BLOCKING_LINKED_LIST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "InitializeException.hpp"
#include "IllegalStateException.hpp"
#include "LinkedList.hpp"
#include "Error.hpp"

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

    bool isEmpty() {
        AutoLock l(mMutex);
        return mList->isEmpty();
    }

    int size() {
        AutoLock l(mMutex);
        return mList->size();
    }

    inline void enQueueFirst(T val) {
        enQueueFirst(val,0);
    }

    inline void enQueueLast(T val) {
        enQueueLast(val,0);
    }

    inline bool enQueueFirst(T val,long timeout) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return false;
            }
            
            if(mCapacity != -1 && mList->size() == mCapacity) {
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
            
            if(mCapacity != -1 && mList->size() == mCapacity) {
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

    inline T deQueueFirst() {
        return deQueueFirst(0);
    }

    inline T deQueueLast() {
        return deQueueLast(0);
    }

    inline T deQueueFirst(long timeout) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return nullptr;
            }

            if(mList->size() == 0) {
                if(mDequeueCond->wait(mMutex,timeout) == -WaitTimeout) {
                    return nullptr;
                }

                continue;
            }

            T data = mList->deQueueFirst();
            mEnqueueCond->notify();        
            return data;
        }

        return nullptr;
    }

    inline T deQueueLast(long timeout) {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return nullptr;
            }
            
            if(mList->size() == 0) {
                if(mDequeueCond->wait(mMutex,timeout) == -WaitTimeout) {
                    return nullptr;
                }

                continue;
            }

            T data = mList->deQueueLast();
            mEnqueueCond->notify();        
            return data;
        }

        return nullptr;
    }

    inline T deQueueFirstNoBlock() {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return nullptr;
            }

            if(mList->size() == 0) {
                return nullptr;
            }

            T data = mList->deQueueFisrt();
            mEnqueueCond->notify();   
            return data;
        }
        return nullptr;
    }

    inline T deQueueLastNoBlock() {
        while(1) {
            AutoLock l(mMutex);
            if(isDestroy) {
                return nullptr;
            }
            int size = mList->size();
            if(size == 0) {
                return nullptr;
            }

            T data = mList->deQueueLast();
            mEnqueueCond->notify();   
            return data;
        }

        return nullptr;
    }

    //destroy
    inline void destroy() {
        AutoLock l(mMutex);
        mList->clear();
        isDestroy = true;
    }

    inline void clear() {
        AutoLock l(mMutex);
        mList->clear();
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