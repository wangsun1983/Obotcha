#ifndef __OBOTCHA_CONCURRENT_HASHSET_HPP__
#define __OBOTCHA_CONCURRENT_HASHSET_HPP__

#include "Object.hpp"
#include "HashKey.hpp"
#include "AutoLock.hpp"
#include "HashSet.hpp"
#include "ReadWriteLock.hpp"

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

    Lock acquireReadLock() {
        return rdLock;
    }


    HashSetIterator<T> getIterator() {
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

    void syncReadAction(std::function<void()> action) {
        AutoLock l(rdLock);
        action();
    }

    void syncWriteAction(std::function<void()> action) {
        AutoLock l(wrLock);
        action();
    }

private:
    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
    HashSet<T> mSets;
};


} // namespace obotcha
#endif
