#ifndef __OBOTCHA_POSIX_SEM_HPP__
#define __OBOTCHA_POSIX_SEM_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>
#include <semaphore.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(PosixSem) {

public:

    _PosixSem(String name,int n);

    bool init();

    int tryWait();

    int wait();

    int wait(long);

    int post();

    int getValue();

    void destroy();

    void release();

    void clean();
    
    ~_PosixSem();

private:
    String mName;

    sem_t *sem;

    int num;

    static long SEM_MAX_VALUE;
};

}
#endif
