#ifndef __OBOTCHA_CONCURRENT_HASHMAP_HPP__
#define __OBOTCHA_CONCURRENT_HASHMAP_HPP__

#include <vector>

#include "AutoLock.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentHashMap, T,U) {
public:
    _ConcurrentHashMap() { 
        mMap = createHashMap<T, U>();
        rdwrLock = createReadWriteLock();
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
    };

    int size() {
        AutoLock l(rdLock);
        return mMap->size();
    }

    U get(const T &key) {
        AutoLock l(rdLock);
        return mMap->get(key);
    }

    void put(const T &key, const U &value) {
        AutoLock l(wrLock);
        return mMap->put(key, value);
    }

    void remove(const T &key) {
        AutoLock l(wrLock);
        mMap->remove(key);
    }

    void clear() {
        AutoLock l(wrLock);
        mMap->clear();
    }

    //remove this
    HashMap<T,U> toMap() {
        AutoLock l(rdLock);
        HashMap<T,U> map = createHashMap<T,U>();
        auto iterator = mMap->getIterator();
        while(iterator->hasValue()) {
            map->put(iterator->getKey(),iterator->getValue());
            iterator->next();
        }

        return map;
    }

    MapIterator<T,U> getIterator() {
        AutoLock l(rdLock);
        return mMap->getIterator();
    }

    ArrayList<U> entrySet() {
        AutoLock l(rdLock);
        auto iterator = mMap->getIterator();
        ArrayList<U> lists = createArrayList<U>();
        while(iterator->hasValue()) {
            lists->add(iterator->getValue());
            iterator->next();
        }

        return lists;
    }

    ArrayList<T> keySet() {
        AutoLock l(rdLock);
        auto iterator = mMap->getIterator();
        ArrayList<T> lists = createArrayList<T>();
        while(iterator->hasValue()) {
            lists->add(iterator->getKey());
            iterator->next();
        }

        return lists;
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

private:
    HashMap<T, U> mMap;
    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif