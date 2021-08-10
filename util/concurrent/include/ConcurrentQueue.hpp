#ifndef __OBOTCHA_CONCURRENT_QUEUE_HPP__
#define __OBOTCHA_CONCURRENT_QUEUE_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "ContainerValue.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(ConcurrentQueue,1) {
public:
    inline _ConcurrentQueue() {
        mutex_t = createMutex("ConcurrentQueueMutex");
    }

    inline int size() {
        AutoLock l(mutex_t);
        return mQueue.size();
    }

    //interface like ArrayList
    inline void add(T value) {
        putLast(value);
    }

    inline T get(int index) {
        AutoLock l(mutex_t);
        if(index >= mQueue.size()) {
            return ContainerValue<T>(nullptr).get();
        }
        
        return mQueue.at(index);
    }

    ArrayList<T> toArray() {
        AutoLock l(mutex_t);
        ArrayList<T> list = createArrayList<T>();
        for(T v:mQueue) {
            list->add(v);
        }

        return list;
    }

    //interface like queue
    inline void putFirst(const T &val) {
        AutoLock l(mutex_t);
        mQueue.insert(mQueue.begin(),val);
    }

    inline void putLast(const T &val) {
        AutoLock l(mutex_t);
        mQueue.push_back(val);
    }

    inline int remove(const T &val) {
        AutoLock l(mutex_t);
        auto iterator = mQueue.begin();
        while(iterator != mQueue.end()) {
            if(*iterator == val) {
                iterator = mQueue.erase(iterator);
                continue;
            }
            iterator++;
        }
        return 0;
    }

    inline T takeFirst() {
        AutoLock l(mutex_t);

        if(mQueue.size() == 0) {
            return ContainerValue<T>(nullptr).get();
        }
        
        T ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());

        return ret;
    }

    inline T takeLast() {
        AutoLock l(mutex_t);

        if(mQueue.size() == 0) {
            return ContainerValue<T>(nullptr).get();
        }
        
        //return mQueue.pop_back();
        T ret = mQueue.back();
        mQueue.pop_back();

        return ret;
    }

    inline void clear() {
        AutoLock l(mutex_t);
        mQueue.clear();
    }
    
private:
    std::vector<T> mQueue;

    Mutex mutex_t;
};

}
#endif