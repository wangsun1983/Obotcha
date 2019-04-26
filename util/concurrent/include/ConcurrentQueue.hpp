#ifndef __CONCURRENT_QUEUE_HPP__
#define __CONCURRENT_QUEUE_HPP__

#include <vector>
#include <pthread.h>

#include "Object.hpp"
#include "AutoMutex.hpp"
#include "StrongPointer.hpp"

#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"

using namespace std;

namespace obotcha {

DECLARE_CLASS(ConcurrentQueue,1) {
public:
    inline _ConcurrentQueue();

    inline int size();
    inline T get(int index);
    

    inline void enQueueFirst(T val);
    inline void enQueueLast(T val);
    inline int remove(T val);

    //int
    inline void enQueueFirst(int val);
    inline void enQueueLast(int val);

    //bool
    inline void enQueueFirst(bool val);
    inline void enQueueLast(bool val);

    //double
    inline void enQueueFirst(double val);
    inline void enQueueLast(double val);

    //float
    inline void enQueueFirst(float val);
    inline void enQueueLast(float val);

    inline T deQueueFirst();
    inline T deQueueLast();
    
private:
    vector<T> mQueue;

    //pthread_mutex_t mMutex;
    Mutex mutex_t;

};

//template class/function must be defined in hpp file.
template <typename T>
_ConcurrentQueue<T>::_ConcurrentQueue(){
    mutex_t = createMutex();
}

template <typename T>
T _ConcurrentQueue<T>:: get(int index){
    AutoMutex l(mutex_t);
    return mQueue.at(index);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueFirst(T val) {
    AutoMutex l(mutex_t);
    mQueue.insert(mQueue.begin(),val);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueLast(T val) {
    AutoMutex l(mutex_t);
    mQueue.push_back(val);
}

template <typename T>
int _ConcurrentQueue<T>::remove(T val) {
    AutoMutex l(mutex_t);
    typename vector<T>::iterator result = find(mQueue.begin( ), mQueue.end( ),val);
    if(result != mQueue.end()) {
        mQueue.erase(result);
        return result - mQueue.begin();
    }

    return -1;
}

template <typename T>
void _ConcurrentQueue<T>::enQueueFirst(int val) {
    Integer v = createInteger(val);
    enQueueFirst(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueLast(int val) {
    Integer v = createInteger(val);
    enQueueLast(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueFirst(bool val) {
    Boolean v = createBoolean(val);
    enQueueFirst(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueLast(bool val) {
    Boolean v = createBoolean(val);
    enQueueLast(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueFirst(double val) {
    Double v = createDouble(val);
    enQueueFirst(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueLast(double val) {
    Double v = createDouble(val);
    enQueueLast(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueFirst(float val) {
    Float v = createFloat(val);
    enQueueFirst(v);
}

template <typename T>
void _ConcurrentQueue<T>::enQueueLast(float val) {
    Float v = createFloat(val);
    enQueueLast(v);
}

template <typename T>
T _ConcurrentQueue<T>::deQueueFirst() {
    AutoMutex l(mutex_t);
    
    T ret = mQueue.at(0);
    mQueue.erase(mQueue.begin());

    return ret;
}

template <typename T>
T _ConcurrentQueue<T>::deQueueLast() {
    AutoMutex l(mutex_t);
    
    //return mQueue.pop_back();
    T ret = mQueue.back();
    mQueue.pop_back();

    return ret;
}

template <typename T>
int _ConcurrentQueue<T>::size() {
    AutoMutex l(mutex_t);
    return mQueue.size();
}

}
#endif