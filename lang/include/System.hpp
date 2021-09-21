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
    static long int currentTimeMillis();

    static void exit(int);

    static int availableProcessors();

    static int onlineProcessors();

    static String executeForResult(String cmd);

    static void execute(String cmd);

    static void getNextTime(long timeInterval, struct timespec *ts);

    static void getTimeVal(long timeInterval, struct timeval *tv);

    static int myPid();

    static void closeOnExit(Closeable);

private:
    static Mutex mMutex;
    static ArrayList<Closeable> mListeners;
};

} // namespace obotcha
#endif