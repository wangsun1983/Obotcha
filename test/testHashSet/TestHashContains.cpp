#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

int testHashContains() {

    HashSet<String> set = createHashSet<String>();
    set->add(createString("abc"));
    set->add(createString("abc"));
    set->add(createString("abc1"));
    set->add(createString("abc2"));
    set->add(createString("abc3"));
    if(!set->contains(createString("abc1"))) {
        printf("HashSet Contains test1-------[FAIL] \n");
    }

    if(set->contains(createString("abcd"))) {
        printf("HashSet Contains test2-------[FAIL] \n");
    }

    printf("HashSet Contains test100-------[OK] \n");
}
