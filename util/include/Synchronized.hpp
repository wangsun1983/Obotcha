#ifndef __OBOTCHA_SYNCHRONIZED_HPP__
#define __OBOTCHA_SYNCHRONIZED_HPP__


namespace obotcha {

#define Synchronized(X)  for(AutoLock __l__(X);X->isOwner();__l__.release())

} // namespace obotcha

#endif
