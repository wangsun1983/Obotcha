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
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
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
        return mSets->remove(val);
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

    template<class Function>
    void syncReadAction(Function action) {
        AutoLock l(rdLock);
        action();
    }

    template<class Function>
    void syncWriteAction(Function action) {
        AutoLock l(wrLock);
        action();
    }

private:
    HashSet<T> mSets = createHashSet<T>();
    ReadWriteLock rdwrLock = createReadWriteLock();
    ReadLock rdLock;
    WriteLock wrLock;
};


} // namespace obotcha
#endif
