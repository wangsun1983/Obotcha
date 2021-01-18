#ifndef __OBOTCHA_ATOMIC_BOOLEANR_HPP__
#define __OBOTCHA_ATOMIC_BOOLEANR_HPP__

#include <pthread.h>
#include <sys/time.h>

#include "Mutex.hpp"
#include <atomic>

namespace obotcha {

DECLARE_SIMPLE_CLASS(AtomicBoolean) {

public:
    _AtomicBoolean(bool val);
    
    void set(bool val);
    bool get();
   
private:
    std::atomic_bool mValue;
};

}
#endif