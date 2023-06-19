#ifndef __OBOTCHA_LOOPER_HPP__
#define __OBOTCHA_LOOPER_HPP__

#include "Object.hpp"
#include "MessageQueue.hpp"

namespace obotcha {

DECLARE_CLASS(Looper) {
public:
   _Looper();

   void loop();

   MessageQueue getQueue();

private:
   MessageQueue mQueue;
};

} // namespace obotcha
#endif