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

DECLARE_TEMPLATE_CLASS(ConcurrentHashSet, T) {
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
        return mSets->contains(val);
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

    void foreach(std::function<int(const T &)> f,std::function<void()> after = nullptr) {
        auto lock = ((after == nullptr)?Cast<Lock>(rdLock):Cast<Lock>(wrLock));
        AutoLock l(lock);

        auto iterator = mSets->getIterator();
        while(iterator->hasValue()) {
            if(f(iterator->getValue()) != Continue) {
                break;
            }
            iterator->next();
        }

        if(after != nullptr) {
            after();
            return;
        }
    }

    //remove this function,iterator is not threadsafe
    //HashSetIterator<T> getIterator() {
    //    AutoLock l(rdLock);
    //    return mSets->getIterator();
    //}

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
