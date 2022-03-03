#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "AutoLock.hpp"
#include "System.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

Mutex _System::mMutex = createMutex();
ArrayList<Closeable> _System::mListeners = createArrayList<Closeable>();

long int _System::currentTimeMillis() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int _System::availableProcessors() {
    int cpu_num = sysconf(_SC_NPROCESSORS_CONF);
    return cpu_num;
}

int _System::onlineProcessors() {
    int cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
    return cpu_num;
}

String _System::executeForResult(String cmd) {
    FILE *fp;
    char buffer[1024 * 64];
    fp = popen(cmd->toChars(), "r");

    if (fp == nullptr) {
        return nullptr;
    }

    fread(buffer, 1, 1024 * 64, fp);
    pclose(fp);

    return createString(buffer);
}

void _System::execute(String cmd) { system(cmd->toChars()); }

void _System::exit(int reason) {
    // we should close all before exit
    {
        AutoLock l(mMutex);
        auto iterator = mListeners->getIterator();
        while (iterator->hasValue()) {
            iterator->getValue()->close();
            iterator->next();
        }
    }
    exit(reason);
}

void _System::getNextTime(long timeInterval, struct timespec *ts) {
    ts->tv_sec = 0;
    ts->tv_nsec = 0;

    clock_gettime(CLOCK_REALTIME, ts);
    ts->tv_nsec += timeInterval * 1000 * 1000;
    ts->tv_sec += (ts->tv_nsec) / (1000 * 1000 * 1000);
    ts->tv_nsec = ts->tv_nsec % (1000 * 1000 * 1000);
}

void _System::getTimeVal(long timeInterval, struct timeval *tv) {
    tv->tv_sec = timeInterval / 1000;
    tv->tv_usec = (timeInterval % 1000) * 1000;
}

int _System::myPid() { return getpid(); }

int _System::myTid() { return syscall(SYS_gettid);}

void _System::closeOnExit(Closeable c) {
    AutoLock l(mMutex);
    mListeners->add(c);
}

int _System::getEndianness() {
    short int x;
    char x0;
    x = 0x1122;
    x0 = ((char*)&x)[0];
    return (x0==0x11)?Global::BigEndian:Global::LittleEndian;
}

void _System::arrayCopy(ByteArray dest,int destPos,
                        ByteArray src,int srcPos,
                        int length) {
    if(destPos < 0 || srcPos < 0) {
        Trigger(IllegalArgumentException,"illeagl param");
    }

    if(srcPos > src->size() - length ||
       destPos > dest->size() - length) {
        Trigger(ArrayIndexOutOfBoundsException,"oversize");
    }

    memcpy(&dest->toValue()[destPos],&src->toValue()[srcPos],length);
}

} // namespace obotcha