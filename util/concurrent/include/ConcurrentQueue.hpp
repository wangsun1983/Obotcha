#ifndef __OBOTCHA_CONCURRENT_QUEUE_HPP__
#define __OBOTCHA_CONCURRENT_QUEUE_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(ConcurrentQueue,1) {
public:
    inline _ConcurrentQueue();

    inline int size();
    inline T get(int index);
    
    inline void enQueueFirst(const T &val);
    inline void enQueueLast(const T &val);
    inline int remove(const T &val);

    inline T deQueueFirst();
    inline T deQueueLast();

    inline void clear();
    
private:
    std::vector<T> mQueue;

    Mutex mutex_t;
};

//template class/function must be defined in hpp file.
template <typename T>
_ConcurrentQueue<T>::_ConcurrentQueue(){
    mutex_t = createMutex("ConcurrentQueueMutex");
}

template <typename T>
T _ConcurrentQueue<T>:: get(int index){
    AutoLock l(mutex_t);
    if(index >= mQueue.size()) {
        return nullptr;
    }
    
    return mQueue.at(index);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueFirst(const T &val) {
    AutoLock l(mutex_t);
    mQueue.insert(mQueue.begin(),val);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueLast(const T &val) {
    AutoLock l(mutex_t);
    mQueue.push_back(val);
}

template <typename T>
int _ConcurrentQueue<T>::remove(const T &val) {
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

template <typename T>
T _ConcurrentQueue<T>::deQueueFirst() {
    AutoLock l(mutex_t);

    if(mQueue.size() == 0) {
        return nullptr;
    }
    
    T ret = mQueue.at(0);
    mQueue.erase(mQueue.begin());

    return ret;
}

template <typename T>
T _ConcurrentQueue<T>::deQueueLast() {
    AutoLock l(mutex_t);

    if(mQueue.size() == 0) {
        return nullptr;
    }
    
    //return mQueue.pop_back();
    T ret = mQueue.back();
    mQueue.pop_back();

    return ret;
}

template <typename T>
int _ConcurrentQueue<T>::size() {
    AutoLock l(mutex_t);
    return mQueue.size();
}

template <typename T>
void _ConcurrentQueue<T>::clear() {
    AutoLock l(mutex_t);
    mQueue.clear();
}

}
#endif