#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "Random.hpp"
#include "AutoLock.hpp"

using namespace obotcha;

class DelayTestData {
public:
  long start;
  long interval;
  long finished;
};

Mutex delayDataMutex = createMutex();
std::vector<DelayTestData *> datas;

DECLARE_SIMPLE_CLASS(MyDelayedHandler) EXTENDS(Handler) {
public:

  void handleMessage(Message msg) {
    AutoLock l(delayDataMutex);
    DelayTestData *data = datas[msg->what];
    data->finished = st(System)::currentTimeMillis();
  }
};


int testSendMessageDelayed() {
  MyDelayedHandler m = createMyDelayedHandler();
  Random rnd = createRandom();

  for(int i = 0;i<1024;i++) {
    int interval = rnd->nextInt(100,800);
    {
      AutoLock l(delayDataMutex);
      DelayTestData *data = new DelayTestData();
      data->start = st(System)::currentTimeMillis();
      data->interval = interval;
      datas.push_back(data);
    }
    m->sendEmptyMessageDelayed(i,interval);
  }
  
  sleep(5);

  for(int i = 0;i<1024;i++) {
      DelayTestData *data = datas[i];
      //printf("trace start is %ld,finished is %ld,interval is %ld,real interval is %ld \n",data->start,data->finished,data->interval,data->finished - data->start);
      if((data->finished - data->start) > (data->interval + 10)) {
        printf("!!!!error,start is %ld,finished is %ld,interval is %ld \n",data->start,data->finished,data->interval);
        printf("---[Handler Test {Test SendMessageDelayed} case1] [FAILED]--- \n");
      }
      delete data;
  }

}