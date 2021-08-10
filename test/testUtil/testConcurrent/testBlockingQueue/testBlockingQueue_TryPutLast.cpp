#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueueTryPutLast() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        bool result = list->tryPutLast(createString("d"));
        if(result) {
          printf("BlockingQueue tryPutLast test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 3) {
          printf("BlockingQueue tryPutLast test1_1-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingQueue<String> list = createBlockingQueue<String>(3);
      list->tryPutLast(createString("a"));
      list->tryPutLast(createString("b"));
      list->tryPutLast(createString("c"));
      list->tryPutLast(createString("d"));
      if(list->size() != 3) {
        printf("BlockingQueue tryPutLast test2-------[FAIL] \n");
        break;
      }

      ArrayList<String> result = createArrayList<String>();
      result->add(createString("a"));
      result->add(createString("b"));
      result->add(createString("c"));
      auto iterator = result->getIterator();
      while(iterator->hasValue()) {
        auto v = iterator->getValue();
        auto v2 = list->takeFirst();
        if(!v->equals(v2)) {
          printf("BlockingQueue tryPutLast test3-------[FAIL],v is %s,v2 is %s \n",v->toChars(),v2->toChars());
          break;
        }
        iterator->next();
      }

      list->tryPutLast(createString("a"));
      list->tryPutLast(createString("b"));
      list->tryPutLast(createString("c"));
      list->tryPutLast(createString("d"));
      list->takeFirst();
      list->putLast(createString("e"));
      ArrayList<String> ll2 = list->toArray();
      if(ll2->size() != 3 || !ll2->get(0)->equals("b")|| !ll2->get(1)->equals("c")|| !ll2->get(2)->equals("e")) {
        printf("BlockingQueue tryPutLast test4-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingQueue tryPutLast test100-------[OK] \n");
}
