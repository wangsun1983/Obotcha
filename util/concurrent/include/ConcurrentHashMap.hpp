#ifndef __OBOTCHA_CONCURRENT_HASHMAP_HPP__
#define __OBOTCHA_CONCURRENT_HASHMAP_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(ConcurrentHashMap,2) {
public:
    _ConcurrentHashMap() {
        mutex = createMutex("ConcurrentHashMap");
    };

    int size() {
        AutoLock l(mutex);
        return mMap->size();
    }

    U get(const T &key) {
        AutoLock l(mutex);
        return mMap->get(key);
    }

    void put(const T &key,const U &value) {
        AutoLock l(mutex);
        return mMap->put(key,value);
    }

    void clear() {
        AutoLock l(mutex);
        mMap->clear();
    }
    
private:
    HashMap<T,U> mMap;
    Mutex mutex;
};

}
#endif