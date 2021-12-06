#ifndef __OBOTCHA_HTTP_HPACK_SENSITIVE_TABLE_HPP__
#define __OBOTCHA_HTTP_HPACK_SENSITIVE_TABLE_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Mutex.hpp"
#include "HashMap.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_CLASS(HPackSensitiveTable) {

public:
    bool isSensitive(String);
    void add(String);
    void remove(String);

private:
    static HashMap<String,Integer> maps;
    static ReadWriteLock lock;
    static ReadLock readlock;
    static WriteLock writelock;
};

}

#endif
