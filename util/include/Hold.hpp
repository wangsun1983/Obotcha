#ifndef __OBOTCHA_SYNCHRONIZED_HPP__
#define __OBOTCHA_SYNCHRONIZED_HPP__


namespace obotcha {

#define Synchronized(X) \ for(x->lock();x->isOwner(); x->unlock())

} // namespace obotcha

#endif
