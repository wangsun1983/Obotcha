#ifndef __OBOTCHA_CONCURRENT_HASHSET_HPP__
#define __OBOTCHA_CONCURRENT_HASHSET_HPP__

#include <algorithm>
#include <unordered_set>

#include "HashKey.hpp"
#include "Long.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "HashSet.hpp"
#include "ReadWriteLock.hpp"

#include <set>

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentHashSet, 1) {
public:
    _ConcurrentHashSet() {
        rdwrLock = createReadWriteLock();
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
        mSets = createHashSet<T>();
    }

    void add(T val) {  
        AutoLock l(wrLock);
        mSets->add(val);
    }

    bool contains(T val) {
        AutoLock l(rdLock);
        return mSets->contains;
    }

    void add(HashSet<T> list) {
        AutoLock l(wrLock);
        mSets->add(list);
    }

    inline void clear() { 
        AutoLock l(wrLock);
        mSets->clear(); 
    }

    inline int remove(T val) { 
        AutoLock l(wrLock);
        return mSets->erase(val); 
    }

    inline T get(int index) { 
        AutoLock l(rdLock);
        return mSets->get(index); 
    }

    inline int size() { 
        AutoLock l(rdLock);
        return mSets->size(); 
    }

    void freezeWrite() {
        rdLock->lock();
    }

    void freezeRead() {
        wrLock->lock();
    }

    void unfreezeWrite() {
        rdLock->unlock();
    }

    void unfreezeRead() {
        wrLock->unlock();
    }

    HashSetIterator<T> getIterator() {
        AutoLock l(rdLock);
        return mSets->getIterator();
    }

    HashSet<T> toSet() {
        AutoLock l(rdLock);
        HashSet<T> sets = createHashSet<T>();
        auto iterator = mSets->getIterator();
        while(iterator->hasValue()) {
            sets->add(iterator->getValue());
            iterator->next();
        }
        return sets;
    }

private:
    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
    HashSet<T> mSets;
};


} // namespace obotcha
#endif