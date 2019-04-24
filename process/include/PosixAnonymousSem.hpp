#ifndef __POSIX_ANONYMOUS_SEM_HPP__
#define __POSIX_ANONYMOUS_SEM_HPP__

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

DECLARE_SIMPLE_CLASS(PosixAnonymousSem) {

public:
    _PosixAnonymousSem(int);

    bool init();

    void tryWait();

    void wait();

    void wait(long);

    void post();

    int getValue();

    void destroy();

    ~_PosixAnonymousSem();

private:
    String mName;

    sem_t sem;

    int num;
};

}
#endif
