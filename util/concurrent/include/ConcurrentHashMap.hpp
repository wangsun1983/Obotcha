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

DECLARE_TEMPLATE_CLASS(ConcurrentHashMap, 2) {
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

    ArrayList<U> entrySet() {
        AutoLock l(rdLock);
        return mMap->entrySet();
    }


private:
    HashMap<T, U> mMap;
    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif