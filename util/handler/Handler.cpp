/**
 * @file Handler.cpp
 * @brief A Handler allows you to send and process Message and Runnable
 * objects associated with a thread's MessageQueue.  Each Handler
 * instance is associated with a single thread and that thread's message
 * queue. When you create a new Handler it is bound to a Looper.
 * It will deliver messages and runnables to that Looper's message
 * queue and execute them on that Looper's thread.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2023-01-17
 * @license none
 */

#include "Handler.hpp"
#include "System.hpp"

namespace obotcha {

HandlerThread _Handler::kHandlerThread = nullptr;

_Handler::_Handler(Looper loop):mLooper(loop) {
}

_Handler::_Handler() {
   static std::once_flag s_flag;
   std::call_once(s_flag, []() {
      kHandlerThread = HandlerThread::New();
      kHandlerThread->start();
   });
   mLooper = kHandlerThread->getLooper();
}

Looper _Handler::getLooper() {
   return mLooper;
}

sp<_Message> _Handler::obtainMessage(int what) {
   Message msg = Message::New(what);
   msg->setTarget(AutoClone(this));
   return msg;
}

sp<_Message> _Handler::obtainMessage() {
   Message msg = Message::New();
   msg->setTarget(AutoClone(this));
   return msg;
}

int _Handler::sendEmptyMessage(int what) {
   return sendEmptyMessageDelayed(what,0);
}

int _Handler::sendEmptyMessageDelayed(int what, long delay) {
   Message msg = Message::New(what);
   return sendMessageDelayed(msg,delay);
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
   mLooper->getQueue()->removeMessages(AutoClone(this),what);
}

void _Handler::removeEqualMessages(int what,Object data) {
   mLooper->getQueue()->removeEqualMessages(AutoClone(this),what,data);
}

void _Handler::removeCallbacks(Runnable r) {
   mLooper->getQueue()->removeMessages(AutoClone(this),r);
}

int _Handler::size() {
   return mLooper->getQueue()->querySize(AutoClone(this));
}

} // namespace obotcha
