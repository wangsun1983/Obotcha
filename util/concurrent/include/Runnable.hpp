#ifndef __RUNNABLE_HPP__
#define __RUNNABLE_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(Runnable) {

public:
	virtual void run() = 0;
    
    virtual void onInterrupt(){};
};


#endif