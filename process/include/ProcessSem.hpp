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
    void close();
    ~_ProcessSem() override;

    static int Create(String name,int num = 1);
    static int Clear(String name);    
private:
    String mName;
    sem_t *mSem;
    int mNum;
    static long kSemMax;
};

}
#endif
