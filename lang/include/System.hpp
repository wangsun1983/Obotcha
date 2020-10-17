#ifndef __OBOTCHA_SYSTEM_HPP__
#define __OBOTCHA_SYSTEM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

#ifndef TEMP_FAILURE_RETRY
/* Used to retry syscalls that can return EINTR. */
#define TEMP_FAILURE_RETRY(exp) ({         \
    typeof (exp) _rc;                      \
    do {                                   \
        _rc = (exp);                       \
    } while (_rc == -1 && errno == EINTR); \
    _rc; })

#endif

DECLARE_SIMPLE_CLASS(System) {

public:
    static long int currentTimeMillis();

    static void exit(int);

    static int availableProcessors();
    
    static int onlineProcessors();

    static String executeForResult(String cmd);

    static void execute(String cmd);

    static void getNextTime(long timeInterval,struct timespec *ts);

    static int myPid();
};

}
#endif