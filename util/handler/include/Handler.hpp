#ifndef __OBOTCHA_HANDLER_HPP__
#define __OBOTCHA_HANDLER_HPP__

#include "Object.hpp"
#include "HandlerTarget.hpp"
#include "Runnable.hpp"
#include "Message.hpp"
#include "MessageQueue.hpp"
#include "Looper.hpp"
#include "HandlerThread.hpp"

namespace obotcha {

DECLARE_CLASS(Handler) IMPLEMENTS(HandlerTarget){
public:
   explicit _Handler(Looper);
   _Handler();
   
   virtual void handleMessage(sp<_Message>){
      // Intentionally unimplemented...
   }
   
   sp<_Message> obtainMessage(int);

   sp<_Message> obtainMessage();

   int sendEmptyMessage(int what);

   int sendEmptyMessageDelayed(int what, long delay);

   int sendMessageDelayed(sp<_Message>, long delay);

   int sendMessage(sp<_Message>);

   int sendMessageAtFrontOfQueue(Message msg);

   bool hasMessage(int what);

   void removeMessages(int what);

   void removeCallbacks(Runnable r);

   Looper getLooper();

   int size();

   template <typename X> int post(sp<X> r) { 
        return postDelayed(0, r); 
   }

   template <class Function, class... Args>
   int post(Function f, Args... args) {
      return postDelayed(0, createLambdaRunnable(f, args...));
   }

   template <typename X> int postDelayed(long delay, sp<X> r) {
      Message msg = obtainMessage();
      msg->mRunnable = r;
      return sendMessageDelayed(msg, delay);
   }

   template <class Function, class... Args>
   int postDelayed(long delay, Function f, Args... args) {
      return postDelayed(delay, createLambdaRunnable(f, args...));
   }

private:
   //MessageQueue mQueue;
   Looper mLooper;
   static HandlerThread kHandlerThread;
};

} // namespace obotcha
#endif