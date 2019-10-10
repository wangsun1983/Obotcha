#ifndef __RUNNABLE_HPP__
#define __RUNNABLE_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Runnable) {

public:
	virtual void run() = 0;
    
    virtual void onInterrupt(){
    };

    virtual ~_Runnable() {}
};

}
#endif