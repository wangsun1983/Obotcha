#ifndef __OBOTCHA_SYSTEM_HPP__
#define __OBOTCHA_SYSTEM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "Closeable.hpp"
#include "Mutex.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(System) {

public:
    static long int CurrentTimeMillis();

    static int AvailableProcessors();

    static int OnlineProcessors();

    static String ExecuteForResult(String cmd);

    static void Execute(String cmd);

    static void GetNextTime(long timeInterval, struct timespec *ts);

    static void GetTimeVal(long timeInterval, struct timeval *tv);

    static int GetEndianness();

    static void ArrayCopy(ByteArray dest,int destPos,
                          ByteArray src,int srcPos,
                          int length);
private:
    static const int kExecuteBuffSize;                          
};

} // namespace obotcha
#endif