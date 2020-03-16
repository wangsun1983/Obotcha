#include <stdio.h>
#include <iostream>
#include <type_traits>

#include <string.h>
#include "String.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"
#include "TransformException.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

int splittest() {
    
    //----------------------------
    

    //sp<_ArrayList<String>> split(const char* v);

    //sp<_ArrayList<String>> split(std::string v);
    //----------------------------

    ////sp<_ArrayList<String>> split(String v);
    while(1) {
        String str1 = createString(" a b c d ");
        ArrayList<String> str1list = str1->split(createString(" "));
        ListIterator<String> iterator = str1list->getIterator();
        while(iterator->hasValue()) {
            String v = iterator->getValue();
            printf("v is %s \n",v->toChars());
            iterator->next();
        }
        break;
    }

}
