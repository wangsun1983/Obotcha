#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

int testHashAdd() {

    //case string
    while(1) {
        HashSet<String> set = createHashSet<String>();
        set->add(createString("abc"));
        set->add(createString("abc"));
        set->add(createString("abc1"));
        set->add(createString("abc2"));
        set->add(createString("abc3"));

        if(set->size() != 4) {
          printf("HashSet base test1-------[FAIL] \n");
          break;
        }

        HashSetIterator<String> it = set->getIterator();
        int count = 0;
        while(it->hasValue()) {
          String vv = it->getValue();
          if(!vv->equals("abc") && !vv->equals("abc1") && !vv->equals("abc2") && !vv->equals("abc3")) {
            it->next();
            continue;
          }
          count++;
          it->next();
        }

        if(count != 4) {
          printf("HashSet base test2-------[FAIL] \n");
          break;
        }

        set->remove(createString("abc"));
        it = set->getIterator();
        count = 0;
        while(it->hasValue()) {
          String vv = it->getValue();
          if(!vv->equals("abc1") && !vv->equals("abc2") && !vv->equals("abc3")) {
            it->next();
            continue;
          }
          count++;
          it->next();
        }

        if(count != 3) {
          printf("HashSet base test3-------[FAIL] \n");
          break;
        }

        break;
    }

    //case int
    while(1) {
        HashSet<int> set = createHashSet<int>();
        set->add(1);
        set->add(2);
        set->add(2);
        set->add(3);
        set->add(4);

        if(set->size() != 4) {
          printf("HashSet base test4-------[FAIL] \n");
          break;
        }

        HashSetIterator<int> it = set->getIterator();
        int count = 0;
        while(it->hasValue()) {
          int vv = it->getValue();
          if(vv != 1 && vv != 2 && vv != 3 && vv != 4) {
            it->next();
            continue;
          }
          count++;
          it->next();
        }

        if(count != 4) {
          printf("HashSet base test5-------[FAIL] \n");
          break;
        }

        set->remove(2);
        it = set->getIterator();
        count = 0;
        while(it->hasValue()) {
          int vv = it->getValue();
          if(vv != 1 && vv != 3 && vv !=4) {
            it->next();
            continue;
          }
          count++;
          it->next();
        }

        if(count != 3) {
          printf("HashSet base test6-------[FAIL] \n");
          break;
        }

        break;
    }

    //case string
    while(1) {
        HashSet<String> set = createHashSet<String>();
        set->add(createString("abc"));
        set->add(createString("abc"));
        set->add(createString("abc1"));
        set->add(createString("abc2"));
        set->add(createString("abc3"));

        if(set->size() != 4) {
          printf("HashSet base test7-------[FAIL] \n");
          break;
        }

        set->remove(createString("abc"));
        set->remove(createString("abc1"));
        set->remove(createString("abc2"));
        set->remove(createString("abc3"));

        if(set->size() != 0) {
          printf("HashSet base test8-------[FAIL] \n");
        }
        break;
    }

    //case int
    while(1) {
        HashSet<int> set = createHashSet<int>();
        set->add(1);
        set->add(2);
        set->add(1);
        set->add(3);
        set->add(4);

        if(set->size() != 4) {
          printf("HashSet base test8-------[FAIL] \n");
          break;
        }

        set->remove(1);
        set->remove(2);
        set->remove(3);
        set->remove(4);

        if(set->size() != 0) {
          printf("HashSet base test9-------[FAIL] \n");
        }
        break;
    }

    printf("HashSet base test100-------[OK] \n");
}
