#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

int testHashIteratorRemove() {

    //remove string
    while(1) {
        HashSet<String> set = createHashSet<String>();
        set->add(createString("abc"));
        set->add(createString("abc1"));
        set->add(createString("abc2"));
        set->add(createString("abc3"));
        HashSetIterator<String> iterator = set->getIterator();
        while(iterator->hasValue()) {
          String v1 = iterator->getValue();
          if(v1->equals("abc2")) {
            iterator->remove();
            continue;
          }

          iterator->next();
        }

        if(set->size() != 3) {
          printf("HashSet iterator remove test1-------[FAIL] \n");
          break;
        }

        int count = 0;
        iterator = set->getIterator();
        while(iterator->hasValue()) {
          String v1 = iterator->getValue();
          if(!v1->equals("abc") && !v1->equals("abc1") && !v1->equals("abc3")) {
            iterator->next();
            continue;
          }
          count++;
          iterator->next();
        }

        if(count != 3) {
          printf("HashSet iterator remove test2-------[FAIL] \n");
        }

        break;
    }

    //remove int
    while(1) {
        HashSet<int> set = createHashSet<int>();
        set->add(1);
        set->add(2);
        set->add(3);
        set->add(4);
        HashSetIterator<int> iterator = set->getIterator();
        while(iterator->hasValue()) {
          int v1 = iterator->getValue();
          if(v1 == 2) {
            iterator->remove();
            continue;
          }

          iterator->next();
        }

        if(set->size() != 3) {
          printf("HashSet iterator remove test3-------[FAIL] \n");
          break;
        }

        int count = 0;
        iterator = set->getIterator();
        while(iterator->hasValue()) {
          int v1 = iterator->getValue();
          if(v1!=1 && v1!=3 && v1!=4) {
            iterator->next();
            continue;
          }
          count++;
          iterator->next();
        }

        if(count != 3) {
          printf("HashSet iterator remove test4-------[FAIL] \n");
        }

        break;
    }

    printf("HashSet iterator remove test100-------[OK] \n");
}
