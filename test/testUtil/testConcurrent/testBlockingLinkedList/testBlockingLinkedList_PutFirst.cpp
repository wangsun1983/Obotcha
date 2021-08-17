#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListPutFirst() {

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        Thread t = createThread([&list]{
          usleep(100*1000);
          list->takeLast();
        });
        t->start();

        long time1 = st(System)::currentTimeMillis();
        list->putFirst("d");
        long time2 = st(System)::currentTimeMillis();

        if((time2 - time1) < 100 || (time2 - time1) > 105) {
          printf("BlockingLinkedList PutFirst test1-------[FAIL],value is %ld \n",time2 - time1);
          break;
        }

        ArrayList<String> result = createArrayList<String>();
        result->add(createString("d"));
        result->add(createString("a"));
        result->add(createString("b"));
        auto iterator = result->getIterator();
        while(iterator->hasValue()) {
          auto v = iterator->getValue();
          auto v2 = list->takeFirst();
          if(!v->equals(v2)) {
            printf("BlockingLinkedList PutFirst test2-------[FAIL],v is %s,v2 is %s \n",v->toChars(),v2->toChars());
            break;
          }
          iterator->next();
        }

        break;
    }


    printf("BlockingLinkedList PutFirst test100-------[OK] \n");
}
