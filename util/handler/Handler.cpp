#include "Handler.hpp"
#include "System.hpp"

namespace obotcha {

HandlerThread _Handler::kHandlerThread = nullptr;

_Handler::_Handler(Looper loop) {
   mLooper = loop;
}

_Handler::_Handler() {
   static std::once_flag s_flag;
   std::call_once(s_flag, []() {
      kHandlerThread = createHandlerThread();
      kHandlerThread->start();
   });
   mLooper = kHandlerThread->getLooper();
}

Looper _Handler::getLooper() {
   return mLooper;
}

sp<_Message> _Handler::obtainMessage(int what) {
   Message msg = createMessage(what);
   msg->setTarget(AutoClone(this));
   return msg;
}

sp<_Message> _Handler::obtainMessage() {
   Message msg = createMessage();
   msg->setTarget(AutoClone(this));
   return msg;
}

int _Handler::sendEmptyMessage(int what) {
   return sendEmptyMessageDelayed(what,0);
}

int _Handler::sendEmptyMessageDelayed(int what, long delay) {
   Message msg = createMessage(what);
   msg->setTarget(AutoClone(this));
   msg->nextTime = st(System)::CurrentTimeMillis() + delay;
   return mLooper->getQueue()->enqueueMessage(msg);
}

int _Handler::sendMessageDelayed(sp<_Message> msg, long delay) {
   msg->setTarget(AutoClone(this));
   msg->nextTime = st(System)::CurrentTimeMillis() + delay;
   return mLooper->getQueue()->enqueueMessage(msg);
}

int _Handler::sendMessage(sp<_Message> msg) {
   msg->setTarget(AutoClone(this));
   return sendMessageDelayed(msg,0);
}

int _Handler::sendMessageAtFrontOfQueue(Message msg) {
   msg->setTarget(AutoClone(this));
   return mLooper->getQueue()->enqueueMessageAtFront(msg);
}

bool _Handler::hasMessage(int what) {
   return mLooper->getQueue()->hasMessage(AutoClone(this),what);
}

void _Handler::removeMessages(int what) {
   mLooper->getQueue()->removeMessage(AutoClone(this),what);
}

void _Handler::removeCallbacks(Runnable r) {
   mLooper->getQueue()->removeMessage(AutoClone(this),r);
}

int _Handler::size() {
   return mLooper->getQueue()->querySize(AutoClone(this));
}

} // namespace obotcha
