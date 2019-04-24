#ifndef __POSIX_SEM_HPP__
#define __POSIX_SEM_HPP__

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

    void tryWait();

    void wait();

    void wait(long);

    void post();

    int getValue();

    void destroy();

    ~_PosixSem();

private:
    String mName;

    sem_t *sem;

    int num;
};

}
#endif
