#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"

int main() {

    HashSet<String> set = createHashSet<String>();
    set->put("abc1");
    set->put("abc2");
    set->put("abc1");
    set->put("abc2");
    set->put("abc3");

    uint64_t tt;

    SetIterator<String> it = set->getIterator();
    while(it->hasValue()) {
      printf("value is %s \n",it->getValue()->toChars());
      it->next();
    }

}
