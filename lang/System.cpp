#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "AutoLock.hpp"
#include "System.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"
#include "StringBuffer.hpp"
#include "Inspect.hpp"
#include "Definations.hpp"

namespace obotcha {

const size_t _System::kExecuteBuffSize = 1024*32;

long int _System::CurrentTimeMillis() {
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

long _System::AvailableProcessors() {
    return sysconf(_SC_NPROCESSORS_CONF);
}

long _System::OnlineProcessors() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

String _System::ExecuteForResult(String cmd) {
    char buffer[kExecuteBuffSize + 1];
    StringBuffer result = createStringBuffer();

    FILE *fp = popen(cmd->toChars(), "r");
    Inspect(fp == nullptr,nullptr)
    
    int read_cnt = 0;
    while(true) {
        read_cnt = fread(buffer, 1, kExecuteBuffSize, fp);
        if(read_cnt <= 0) {
            break;
        }

        buffer[read_cnt] = 0;
        result->append(buffer);

        if(read_cnt == kExecuteBuffSize) {
            continue;
        }
        break;
    }
    pclose(fp);
    return result->toString();
}

void _System::Execute(String cmd) { 
    system(cmd->toChars()); 
}

void _System::GetNextTime(long timeInterval, struct timespec *ts) {
    ts->tv_sec = 0;
    ts->tv_nsec = 0;

    clock_gettime(CLOCK_REALTIME, ts);
    ts->tv_nsec += timeInterval * 1000 * 1000;
    ts->tv_sec += (ts->tv_nsec) / (1000 * 1000 * 1000);
    ts->tv_nsec = ts->tv_nsec % (1000 * 1000 * 1000);
}

void _System::GetTimeVal(long timeInterval, struct timeval *tv) {
    tv->tv_sec = timeInterval / 1000;
    tv->tv_usec = (timeInterval % 1000) * 1000;
}

int _System::GetEndianness() {
    short int x;
    char x0;
    x = 0x1122;
    x0 = ((char*)&x)[0];
    return (x0==0x11)?Defination::BigEndian:Defination::LittleEndian;
}

void _System::ArrayCopy(ByteArray dest,int destPos,
                        ByteArray src,int srcPos,
                        int length) {
    Panic (destPos < 0 || srcPos < 0,IllegalArgumentException,"illeagl param")
    Panic(srcPos > src->size() - length ||
       destPos > dest->size() - length,ArrayIndexOutOfBoundsException,"oversize")
    
    memcpy(&dest->toValue()[destPos],&src->toValue()[srcPos],length);
}

} // namespace obotcha