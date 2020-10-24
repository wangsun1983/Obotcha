#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "NullPointerException.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testArrayList_String() {
  //---[ArrayList<String> Test Start]---

      //---[ArrayList<String> Test {add(char *val)} Start]---
      while(1) {
          ArrayList<String> list = createArrayList<String>();
          list->add(createString("a"));
          list->add(createString("b"));
          list->add(createString("c"));
          if(!list->get(0)->equals("a")
          || !list->get(1)->equals("b")
          || !list->get(2)->equals("c")) {
              printf("---[ArrayList<String> Test {add(char * val)} case1] [FAILED]--- \n");
              break;
          }

          int size = list->size();
          String pp;
          list->add(pp);
          if(list->size() == size) {
            printf("---[ArrayList<String> Test {add(char * val)} case2] [FAILED]--- \n");
            break;
          }

          printf("---[ArrayList<String> Test {add(char * val)}] [OK]--- \n");
          break;
      }

      //---[ArrayList<String> Test {add(std::string v)} Start]---
      while(1) {
          ArrayList<String> list = createArrayList<String>();

          std::string s1("a");
          std::string s2("b");
          std::string s3("c");

          list->add(createString(s1));
          list->add(createString(s2));
          list->add(createString(s3));

          if(!list->get(0)->equals("a")
          || !list->get(1)->equals("b")
          || !list->get(2)->equals("c")) {
              printf("---[ArrayList<String> Test {add(std::string val) case1] [FAILED]--- \n");
              break;
          }

          printf("---[ArrayList<String> Test {add(std::string val)] [OK]--- \n");
          break;
      }

      //---[ArrayList<String> Test {add(String val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));
        if(!list->get(0)->equals("a")
        || !list->get(1)->equals("b")
        || !list->get(2)->equals("c")) {
            printf("---[ArrayList<String> Test {add(String val)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[ArrayList<String> Test {add(String val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {add(ArrayList<String> list)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));

        ArrayList<String> list2 = createArrayList<String>();
        list2->add(createString("c"));
        list2->add(createString("d"));

        list->add(list2);

        if(!list->get(0)->equals("a")
        || !list->get(1)->equals("b")
        || !list->get(2)->equals("c")
        || !list->get(3)->equals("d")) {
            printf("---[ArrayList<String> Test {add(ArrayList<String> list)}] [FAILED]--- \n");
            break;
        }

        printf("---[ArrayList<String> Test {add(ArrayList<String> list)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {clear()} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("1"));
        int size = list->size();
        list->clear();
        if(list->size() != 0 || size != 1) {
          printf("---[ArrayList<String> Test {clear()}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {clear()}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {remove(int index)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        String v = list->removeAt(1);
        if(!v->equals("b")) {
          printf("---[ArrayList<String> Test {remove(int index)} case1] [FAILED]--- \n");
          break;
        }

        if(list->size() != 2) {
          printf("---[ArrayList<String> Test {remove(int index)} case2] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
            v = list->removeAt(5);
        } catch(ArrayIndexOutOfBoundsException e) {
            isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {remove(int index)} case3] [FAILED]--- \n");
          break;
        }

        v = list->removeAt(0);
        v = list->removeAt(0);
        isException = false;
        try {
            v = list->removeAt(0);
            v = list->removeAt(0);
        } catch(ArrayIndexOutOfBoundsException e) {
           isException = true;
        }

        if(v == nullptr || !isException) {
          printf("---[ArrayList<String> Test {remove(int index)} case4] [FAILED]--- \n");
          break;
        }

        isException = false;
        try {
            v = list->removeAt(-1);
        } catch(ArrayIndexOutOfBoundsException e) {
            isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {remove(int index)} case5] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {remove(int index)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {remove(String v)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        int result = list->remove("a");
        if(result == -1) {
          printf("---[ArrayList<String> Test {remove(String v)} case1] [FAILED]--- \n");
          break;
        }

        if(list->size() != 2) {
          printf("---[ArrayList<String> Test {remove(String v)} case2] [FAILED]--- \n");
          break;
        }

        String s;
        result = list->remove(s);
        if(result != -1) {
          printf("---[ArrayList<String> Test {remove(String v)} case3] [FAILED]--- \n");
          break;
        }

        if(list->size() != 2) {
          printf("---[ArrayList<String> Test {remove(String v)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {remove(String v)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {indexOf(String v)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        if(list->indexOf("a") < 0
        ||list->indexOf("b") < 0
        ||list->indexOf("c") < 0) {
          printf("---[ArrayList<String> Test {indexOf(String v)} case1] [FAILED]--- \n");
          break;
        }

        String s;
        int index = list->indexOf(s);
        if(list->indexOf(s) != -1) {
          printf("---[ArrayList<String> Test {indexOf(String v)} case2] [FAILED]--- \n");
          break;
        }

        if(list->indexOf("d") >= 0) {
          printf("---[ArrayList<String> Test {indexOf(String v)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {indexOf(String v)}] [OK]--- \n");
        break;
      }
      //---[ArrayList<String> Test {set(int index,String val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        list->set(0,"d");
        if(!list->get(0)->equals("d")
        || !list->get(1)->equals("b")
        || !list->get(2)->equals("c")) {
            printf("---[ArrayList<String> Test {set(int index,String val)} case1] [FAILED]--- \n");
            break;
        }

        bool isException = false;
        try {
          list->set(100,"a");
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {set(int index,String val)} case2] [FAILED]--- \n");
          break;
        }

        isException = false;
        try {
             list->set(-1,"a");
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {set(int index,String val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {set(int index,String val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {get(int index)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("c")) {
          printf("---[ArrayList<String> Test {get(int index)} case1] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
          list->get(-1);
        } catch(ArrayIndexOutOfBoundsException e) {
           isException = true;
        }

        if(!isException) {
            printf("---[ArrayList<String> Test {get(int index)} case2] [FAILED]--- \n");
            break;
        }

        isException = false;
        try {
          String str2 = list->get(1000);
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {get(int index)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {get(int index)}] [OK]--- \n");
        break;
      }
      //---[ArrayList<String> Test {insert(int index,String val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        list->insert(1,createString("d"));
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("d")
        ||!list->get(2)->equals("b")
        ||!list->get(3)->equals("c")) {
          printf("---[ArrayList<String> Test {insert(int index,String val)} case1] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
            list->insert(50,createString("d"));
        } catch(ArrayIndexOutOfBoundsException e) {
               isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,String val)} case2] [FAILED]--- \n");
          break;
        }

        isException = false;
        try {
            list->insert(-1,createString("d"));
        }catch(ArrayIndexOutOfBoundsException e) {
            isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,String val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,String val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,char* val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        list->insert(1,createString("d"));
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("d")
        ||!list->get(2)->equals("b")
        ||!list->get(3)->equals("c")) {
          printf("---[ArrayList<String> Test {insert(int index,char* val)} case1] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
            int result = list->insert(50,createString("d"));
        } catch(ArrayIndexOutOfBoundsException e) {
           isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,char* val)} case2] [FAILED]--- \n");
          break;
        }

        isException = false;
        try {
            list->insert(-1,createString("d"));
        } catch(ArrayIndexOutOfBoundsException e) {
            isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,char* val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,char* val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,std::string val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString(std::string("a")));
        list->add(createString(std::string("b")));
        list->add(createString(std::string("c")));

        list->insert(1,createString(std::string("d")));
        if(!list->get(0)->equals(std::string("a"))
        ||!list->get(1)->equals(std::string("d"))
        ||!list->get(2)->equals(std::string("b"))
        ||!list->get(3)->equals(std::string("c"))) {
          printf("---[ArrayList<String> Test {insert(int index,std::string val)} case1] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
            list->insert(50,createString(std::string("d")));
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,std::string val)} case2] [FAILED]--- \n");
          break;
        }

        isException = false;
        try {
            list->insert(-1,createString(std::string("d")));
        } catch(ArrayIndexOutOfBoundsException e) {
            isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,std::string val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,std::string val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        ArrayList<String> list2 = createArrayList<String>();
        list2->add(createString("d"));
        list2->add(createString("e"));

        list->insert(2,list2);
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("d")
        ||!list->get(3)->equals("e")
        ||!list->get(4)->equals("c")){
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case1] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
             list->insert(200,list2);
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case2] [FAILED]--- \n");
          break;
        }

        isException = false;
        try {
            list->insert(-1,list2);
        } catch(ArrayIndexOutOfBoundsException e) {
            isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case3] [FAILED]--- \n");
          break;
        }

        int size = list->size();
        ArrayList<String> list3 = createArrayList<String>();
        list->insert(0,list3);

        if(size != list->size()) {
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        ArrayList<String> list2 = createArrayList<String>();
        list2->add(createString("d"));
        list2->add(createString("e"));
        list2->add(createString("f"));

        list->insert(2,list2,2);
        //printf("list->get(0) is %s \n",list->get(0)->toChars());
        //printf("list->get(1) is %s \n",list->get(1)->toChars());
        //printf("list->get(2) is %s \n",list->get(2)->toChars());
        //printf("list->get(3) is %s \n",list->get(3)->toChars());
        //printf("list->get(4) is %s \n",list->get(4)->toChars());
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("d")
        ||!list->get(3)->equals("e")
        ||!list->get(4)->equals("c")){
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)} case1] [FAILED]--- \n");
          break;
        }


        list->clear();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));
        bool isException1 = false;
        try {
            list->insert(2,list2,100);
        }catch(ArrayIndexOutOfBoundsException e) {
            isException1 = true;
        }
        
        if(!isException1) {
            printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)} case2] [FAILED]--- \n");
        }
        //printf("list->get(0) is %s \n",list->get(0)->toChars());
        //printf("list->get(1) is %s \n",list->get(1)->toChars());
        //printf("list->get(2) is %s \n",list->get(2)->toChars());
        //printf("list->get(3) is %s \n",list->get(3)->toChars());
        //printf("list->get(4) is %s \n",list->get(4)->toChars());
        //printf("list->get(5) is %s \n",list->get(5)->toChars());

        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("d")
        ||!list->get(3)->equals("e")
        ||!list->get(4)->equals("f")
        ||!list->get(5)->equals("c")){
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)}] [OK]--- \n");
        break;
      }

  //---[ArrayList<String> Test {insertFirst(String val)} Start]---
  while(1){
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    list->insertFirst(createString("d"));
    if(!list->get(0)->equals("d")
    ||!list->get(1)->equals("a")
    ||!list->get(2)->equals("b")
    ||!list->get(3)->equals("c")){
      printf("---[ArrayList<String> Test {insertFirst(String val)} case1] [FAILED]--- \n");
      break;
    }

    String str1;
    int size = list->size();
    list->insertFirst(str1);
    if(list->size() == size) {
      printf("---[ArrayList<String> Test {insertFirst(String val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertFirst(String val)}] [OK]--- \n");
    break;
  }

  //---[ArrayList<String> Test {insertFirst(const char * val)} Start]---
  while(1){
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    list->insertFirst(createString("d"));
    if(!list->get(0)->equals("d")
    ||!list->get(1)->equals("a")
    ||!list->get(2)->equals("b")
    ||!list->get(3)->equals("c")){
      printf("---[ArrayList<String> Test {insertFirst(const char * val)} case1] [FAILED]--- \n");
      break;
    }

    String str1;
    int size = list->size();
    list->insertFirst(str1);
    if(list->size() == size) {
      printf("---[ArrayList<String> Test {insertFirst(const char * val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertFirst(const char * val)}] [OK]--- \n");
    break;
  }

  //---[ArrayList<String> Test {insertFirst(ArrayList<String> list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("e"));
    list2->add(createString("f"));
    list2->add(createString("g"));

    list->insertFirst(list2);
    if(!list->get(0)->equals("e")
    ||!list->get(1)->equals("f")
    ||!list->get(2)->equals("g")
    ||!list->get(3)->equals("a")
    ||!list->get(4)->equals("b")
    ||!list->get(5)->equals("c")){
      //printf("list->get(0) is %s \n",list->get(0)->toChars());
      //printf("list->get(1) is %s \n",list->get(1)->toChars());
      //printf("list->get(2) is %s \n",list->get(2)->toChars());
      //printf("list->get(3) is %s \n",list->get(3)->toChars());
      //printf("list->get(4) is %s \n",list->get(4)->toChars());
      //printf("list->get(5) is %s \n",list->get(5)->toChars());
      printf("---[ArrayList<String> Test {insertFirst(ArrayList<String> list)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<String> list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      printf("---[ArrayList<String> Test {insertFirst(ArrayList<String> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertFirst(ArrayList<String> list)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {insertLast(String v)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    list->insertLast(createString("d"));
    if(!list->get(0)->equals("a")
    ||!list->get(1)->equals("b")
    ||!list->get(2)->equals("c")
    ||!list->get(3)->equals("d")){
      printf("---[ArrayList<String> Test {insertLast(String v)} case1] [FAILED]--- \n");
      break;
    }

    String s;
    int size = list->size();
    list->insertLast(s);
    if(size == list->size()) {
      printf("---[ArrayList<String> Test {insertLast(String v)} case2] [FAILED]--- \n");
      break;
    }
    printf("---[ArrayList<String> Test {insertLast(String v)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {insertLast(const char *s)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    list->insertLast(createString("d"));
    if(!list->get(0)->equals("a")
    ||!list->get(1)->equals("b")
    ||!list->get(2)->equals("c")
    ||!list->get(3)->equals("d")){
      printf("---[ArrayList<String> Test {insertLast(const char * s)} case1] [FAILED]--- \n");
      break;
    }

    char *p = nullptr;
    int size = list->size();
    try {
      list->insertLast(createString(p));
      printf("---[ArrayList<String> Test {insertLast(const char *s )} case2] [FAILED]--- \n");
    } catch(InitializeException e) {}

    printf("---[ArrayList<String> Test {insertLast(const char *s)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {insertLast(ArrayList<String> list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("e"));
    list2->add(createString("f"));
    list2->add(createString("g"));

    list->insertLast(list2);
    if(!list->get(0)->equals("a")
    ||!list->get(1)->equals("b")
    ||!list->get(2)->equals("c")
    ||!list->get(3)->equals("e")
    ||!list->get(4)->equals("f")
    ||!list->get(5)->equals("g")){
      printf("---[ArrayList<String> Test {insertLast(ArrayList<String> list)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    ArrayList<String> list3;
    list->insertLast(list3);
    if(size != list->size()) {
      printf("---[ArrayList<String> Test {insertLast(ArrayList<String> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertLast(ArrayList<String> list)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {size()} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    if(list->size() != 1) {
      printf("---[ArrayList<String> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    list->clear();
    if(list->size() != 0) {
      printf("---[ArrayList<String> Test {size()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {size()}] [OK]--- \n");
    break;
  }

  //---[ArrayList<String> Test {getIterator()} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    if(list->getIterator()== nullptr) {
      printf("---[ArrayList<String> Test {getIterator()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {getIterator()}] [OK]--- \n");
    break;
  }
  //--[_ListIterator<String> Test {_ListIterator(ArrayList<String> list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));
    list->add(createString("d"));

    ListIterator<String> iterator = createListIterator<String>(list);
    int index = 0;
    bool isOk = true;
    while(iterator->hasValue()) {
      if(!iterator->getValue()->equals(list->get(index))) {
        isOk = false;
        break;
      }
      iterator->next();
      index++;
    }

    if(!isOk) {
      printf("---[ArrayList<String> Test {_ListIterator(ArrayList<String> list)} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {_ListIterator(ArrayList<String> list)}] [OK]--- \n");
    break;
  }

  //--[_ListIterator<String> Test {_ListIterator(_ArrayList<String> *list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));
    list->add(createString("d"));

    ListIterator<String> iterator = list->getIterator();
    int index = 0;
    bool isOk = true;
    while(iterator->hasValue()) {
      if(!iterator->getValue()->equals(list->get(index))) {
        isOk = false;
        break;
      }
      iterator->next();
      index++;
    }

    if(!isOk) {
      printf("---[ArrayList<String> Test {_ListIterator(_ArrayList<String> *list)} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {_ListIterator(_ArrayList<String> *list)}] [OK]--- \n");
    break;
  }

  //--[_ListIterator<String> Test {remove()} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));
    list->add(createString("d"));
    list->add(createString("e"));
    ListIterator<String> iterator = list->getIterator();
    while(iterator->hasValue()) {
      if(iterator->getValue()->equals("c")) {
        iterator->remove();
      }else {
        iterator->next();
      }
    }

    if(list->size() != 4) {
        printf("---[_ListIterator<String> Test {remove()} case0] [FAILED]--- \n");
        break;
    }

    if(!list->get(0)->equals("a") ||!list->get(1)->equals("b")
      ||!list->get(2)->equals("d")||!list->get(3)->equals("e")) {
        printf("---[_ListIterator<String> Test {remove()} case2] [FAILED]--- \n");
        break;
    }

    printf("---[_ListIterator<String> Test {remove()} case3] [OK]--- \n");
    break;
  }
}
