#ifndef __OBOTCHA_POSIX_SEM_HPP__
#define __OBOTCHA_POSIX_SEM_HPP__

 #include <semaphore.h>

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessSem) {

public:
    _ProcessSem(String name,int n = 1);

    bool init();

    int tryWait();

    int wait();

    int wait(long);

    int post();

    int getValue();

    void clear();

    void close();
    
    ~_ProcessSem();

private:
    String mName;

    sem_t *sem;

    int num;

    static long SEM_MAX_VALUE;
};

}
#endif
