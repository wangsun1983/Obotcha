#ifndef __OBOTCHA_CONCURRENT_HASHMAP_HPP__
#define __OBOTCHA_CONCURRENT_HASHMAP_HPP__

#include "Object.hpp"
#include "AutoLock.hpp"
#include "HashMap.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentHashMap, T,U) {
public:
    _ConcurrentHashMap() {
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
    };

    size_t size() {
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

    U remove(const T &key) {
        AutoLock l(wrLock);
        return mMap->remove(key);
    }

    void clear() {
        AutoLock l(wrLock);
        mMap->clear();
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

    HashMap<T,U> toMap() {
        HashMap<T,U> map = createHashMap<T,U>();
        AutoLock l(rdLock);
        auto iterator = mMap->getIterator();
        while(iterator->hasValue()) {
            map->put(iterator->getKey(),iterator->getValue());
            iterator->next();
        }

        return map;
    }

    MapIterator<T,U> getIterator() {
        return mMap->getIterator();
    }

    ArrayList<U> entrySet() {
        AutoLock l(rdLock);
        return mMap->entrySet();
    }

    ArrayList<T> keySet() {
        AutoLock l(rdLock);
        return mMap->keySet();
    }

    Lock acquireReadLock() {
        return rdLock;
    }


private:
    HashMap<T, U> mMap = createHashMap<T, U>();
    ReadWriteLock rdwrLock = createReadWriteLock();
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif
