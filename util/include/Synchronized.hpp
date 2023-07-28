#ifndef __OBOTCHA_SYNCHRONIZED_HPP__
#define __OBOTCHA_SYNCHRONIZED_HPP__

#include "AutoLock.hpp"

#define Synchronized(X)  for(AutoLock __l__(X);X->isOwner();__l__.release())

#endif
