#ifndef __OBOTCHA_AUTO_CLOSE_HPP__
#define __OBOTCHA_AUTO_CLOSE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {
DECLARE_SIMPLE_CLASS(CloseInterface) {
public:
    virtual void doClose() = 0;    
};

class AutoClose {
public:  
    AutoClose(CloseInterface c){
        mInterface = c;
    }

    ~AutoClose() {
        if(mInterface != nullptr) {
            mInterface->doClose();
        }
    }

private:
    CloseInterface mInterface;
};


}

#endif
