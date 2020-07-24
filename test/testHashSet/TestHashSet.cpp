#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

int main() {

    HashSet<String> set = createHashSet<String>();
    set->add(createString("abc"));
    set->add(createString("abc"));
    set->add(createString("abc1"));
    set->add(createString("abc2"));
    set->add(createString("abc3"));

    uint64_t tt;

    HashSetIterator<String> it = set->getIterator();
    while(it->hasValue()) {
      printf("value is %s \n",it->getValue()->toChars());
      it->next();
    }

}
