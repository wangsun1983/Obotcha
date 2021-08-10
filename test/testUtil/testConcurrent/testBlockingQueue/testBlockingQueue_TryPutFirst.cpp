#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueueTryPutFirst() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        bool result = list->tryPutFirst(createString("d"));
        if(result) {
          printf("BlockingQueue TryPutFirst test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 3) {
          printf("BlockingQueue TryPutFirst test1_1-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingQueue<String> list = createBlockingQueue<String>(3);
      list->tryPutFirst(createString("a"));
      list->tryPutFirst(createString("b"));
      list->tryPutFirst(createString("c"));

      ArrayList<String> result = createArrayList<String>();
      result->add(createString("c"));
      result->add(createString("b"));
      result->add(createString("a"));
      auto iterator = result->getIterator();
      while(iterator->hasValue()) {
        auto v = iterator->getValue();
        auto v2 = list->takeFirst();
        if(!v->equals(v2)) {
          printf("BlockingQueue TryPutFirst test2-------[FAIL],v is %s,v2 is %s \n",v->toChars(),v2->toChars());
          break;
        }
        iterator->next();
      }
      break;
    }

    printf("BlockingQueue TryPutFirst test100-------[OK] \n");
}
