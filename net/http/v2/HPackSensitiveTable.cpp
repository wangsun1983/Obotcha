#include "HPackSensitiveTable.hpp"
#include "AutoLock.hpp"

namespace obotcha {

HashMap<String,Integer> _HPackSensitiveTable::maps = createHashMap<String,Integer>();
ReadWriteLock _HPackSensitiveTable::lock = createReadWriteLock();
ReadLock _HPackSensitiveTable::readlock = lock->getReadLock();
WriteLock _HPackSensitiveTable::writelock = lock->getWriteLock();

bool _HPackSensitiveTable::isSensitive(String name) {
    AutoLock l(readlock);
    return (maps->get(name) != nullptr);
}

void _HPackSensitiveTable::add(String name) {
    AutoLock l(writelock);
    maps->put(name,createInteger(0));
}

void _HPackSensitiveTable::remove(String name) {
    AutoLock l(writelock);
    maps->remove(name);
}



}
