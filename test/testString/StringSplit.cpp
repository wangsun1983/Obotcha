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
        //case 1
        String str1 = createString(" a b c d ");
        ArrayList<String> str1list = str1->split(createString(" "));
        ListIterator<String> iterator = str1list->getIterator();

        if(str1list->size() != 4) {
            printf("String split Special test1-------[FAIL] \n");
            break;
        }

        if(!str1list->get(0)->equals("a")
            ||!str1list->get(1)->equals("b")
            ||!str1list->get(2)->equals("c")
            ||!str1list->get(3)->equals("d")) {
            printf("String split Special test2-------[FAIL] \n");
            break;
        }

        //case 2
        String str2 = createString(" ");
        ArrayList<String> str2list = str2->split(createString(" "));
        if(str2list->size() != 0) {
            printf("String split Special test3-------[FAIL] \n");
            break;
        }

        //case 3
        String str3 = createString("accbcc");
        ArrayList<String> str3list = str3->split(createString("cc"));
        if(str3list->size() != 2) {
            printf("String split Special test5-------[FAIL] \n");
            break;
        }

        if(!str3list->get(0)->equals("a")
            ||!str3list->get(1)->equals("b")) {
            printf("String split Special test6-------[FAIL] \n");
            break;
        }

        printf("String split Special test8-------[Success] \n");
        break;
    }

}
