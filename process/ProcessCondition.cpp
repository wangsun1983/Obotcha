#include "ProcessCondition.hpp"

namespace obotcha {

_ProcessCondition::_ProcessCondition(String path) {
    String hascode = createString(path->hashcode());
    sem = createPosixSem(hascode,0);
    mMutex = createProcessMutex(path->append("_mutex"));
    mCount = createPosixShareMemory(hascode->append("_count"),
                                    sizeof(int),
                                    st(PosixShareMemory)::WriteRead);
}

int _ProcessCondition::wait(ProcessMutex m, long int millseconds) {
    increase(1);
    m->unlock();
    int ret = sem->wait(millseconds);
    m->lock();
    return ret;
}

int _ProcessCondition::wait(AutoLock &m, long int millseconds) {
    increase(1);
    m.mLock->unlock();
    int ret = sem->wait(millseconds);
    m.mLock->lock();
    return ret;
}

void _ProcessCondition::increase(int v) {
    AutoLock l(mMutex);
    ByteArray data = createByteArray(sizeof(int));
    mCount->read(data);

    ByteArrayReader r = createByteArrayReader(data);
    int count = r->read<int>();
    count += v;
    ByteArrayWriter w = createByteArrayWriter(data);
    w->write<int>(count);
    mCount->write(data);
}

void _ProcessCondition::notify() {
    AutoLock l(mMutex);
    sem->post();
    increase(-1);
}

void _ProcessCondition::notifyAll() {
    AutoLock l(mMutex);
    ByteArray data = createByteArray(sizeof(int));
    mCount->read(data);

    ByteArrayReader r = createByteArrayReader(data);
    int count = r->read<int>();
    while(count > 0) {
        sem->post();
        count--;
    }

    ByteArrayWriter w = createByteArrayWriter(data);
    w->write<int>(0);
    mCount->write(data);
}

_ProcessCondition::~_ProcessCondition() {
    sem->close();
    mCount->close();
}

void _ProcessCondition::clear() {
    sem->clear();
    mCount->clear();
}


}
