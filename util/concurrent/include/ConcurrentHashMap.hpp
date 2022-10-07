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

    U remove(const T &key) {
        AutoLock l(wrLock);
        return mMap->remove(key);
    }

    void clear() {
        AutoLock l(wrLock);
        mMap->clear();
    }

    void syncReadAction(std::function<void()> action) {
        AutoLock l(rdLock);
        action();
    }

    void syncWriteAction(std::function<void()> action) {
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
        AutoLock l(rdLock);
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

    /*
    void foreach(std::function<int(const T&,const U&)> f,
                 std::function<void()> after = nullptr) {
        auto lock = ((after == nullptr)?Cast<Lock>(rdLock):Cast<Lock>(wrLock));
        AutoLock l(lock);

        auto iterator = mMap->getIterator();
        while(iterator->hasValue()) {
            if(f(iterator->getKey(),iterator->getValue()) != Continue) {
                break;
            }
            iterator->next();
        }

        if(after != nullptr) {
            after();
            return;
        }
    }*/

    Lock acquireReadLock() {
        return rdLock;
    }


private:
    HashMap<T, U> mMap;
    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif
