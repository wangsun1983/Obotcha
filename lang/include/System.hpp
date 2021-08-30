#ifndef __OBOTCHA_SYSTEM_HPP__
#define __OBOTCHA_SYSTEM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(SystemListener) {
public:
    virtual void onSystemExit() = 0;
};

DECLARE_CLASS(System) {

public:
    static long int currentTimeMillis();

    static void exit(int);

    static int availableProcessors();
    
    static int onlineProcessors();

    static String executeForResult(String cmd);

    static void execute(String cmd);

    static void getNextTime(long timeInterval,struct timespec *ts);
    
    static void getTimeVal(long timeInterval,struct timeval *tv);

    static int myPid();

private:
    static Mutex mMutex;
    static ArrayList<SystemListener> mListeners;
};

}
#endif