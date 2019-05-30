#include <stdio.h>
#include <unistd.h>

#include "IniValue.hpp"
#include "IniReader.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
    printf("---[IniValue Test Start]--- \n");
    IniReader reader = createIniReader("testData.ini");
    IniValue value = reader->parse();

    //int getSectionNum();
    while(1) {
        int size = value->getSectionNum();
        if(size != 4) {
          printf("---[IniValue Test {getSectionNum()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[IniValue Test {getSectionNum()} case2] [Success]--- \n");
        break;
    }

    //getSectionName
    while(1) {
      String v1 = value->getSectionName(0);
      if(!v1->equals("l1")) {
        printf("---[IniValue Test {getSectionName()} case1] [FAILED]--- \n");
        break;
      }

      v1 = value->getSectionName(1);
      if(!v1->equals("l2")) {
        printf("---[IniValue Test {getSectionName()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[IniValue Test {getSectionName()} case3] [Success]--- \n");
      break;
    }

    //getString
    while(1) {
      String v1 = value->getString("l1","a","0");
      if(!v1->equals("1")) {
        printf("---[IniValue Test {getString()} case1] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("l1","b","0");
      if(!v1->equals("2")) {
        printf("---[IniValue Test {getString()} case2] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("l1","c","0");
      if(!v1->equals("3")) {
        printf("---[IniValue Test {getString()} case3] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("l1","c","0");
      if(!v1->equals("3")) {
        printf("---[IniValue Test {getString()} case3] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("l1","e","0");
      if(!v1->equals("4")) {
        printf("---[IniValue Test {getString()} case4] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("l1","f","0");
      if(!v1->equals("5")) {
        printf("---[IniValue Test {getString()} case5] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("l1","g","0");
      if(!v1->equals("6")) {
        printf("---[IniValue Test {getString()} case6] [FAILED]--- \n");
        break;
      }

      v1 = value->getString("","abc1","0");
      if(!v1->equals("1")) {
        printf("---[IniValue Test {getString()} case7] [FAILED]--- \n");
        break;
      }

      v1 = value->getString(nullptr,"abc1","0");
      if(!v1->equals("1")) {
        printf("---[IniValue Test {getString()} case8] [FAILED]--- \n");
        break;
      }

      printf("---[IniValue Test {getString()} case9] [Success]--- \n");
      break;
    }

    //getInteger
    while(1) {
      int v1 = value->getInteger("l1","a",0);
      if(v1 != 1) {
        printf("---[IniValue Test {getInteger()} case1] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger("l1","b",0);
      if(v1 != 2) {
        printf("---[IniValue Test {getInteger()} case2] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger("l1","c",0);
      if(v1 != 3) {
        printf("---[IniValue Test {getInteger()} case3] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger("l1","e",0);
      if(v1 != 4) {
        printf("---[IniValue Test {getInteger()} case4] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger("l1","f",0);
      if(v1 != 5) {
        printf("---[IniValue Test {getInteger()} case5] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger("l1","g",0);
      if(v1 != 6) {
        printf("---[IniValue Test {getInteger()} case6] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger("","abc1",0);
      if(v1 != 1) {
        printf("---[IniValue Test {getInteger()} case7] [FAILED]--- \n");
        break;
      }

      v1 = value->getInteger(nullptr,"abc1",0);
      if(v1 != 1) {
        printf("---[IniValue Test {getInteger()} case8] [FAILED]--- \n");
        break;
      }

      printf("---[IniValue Test {getInteger()} case9] [Success]--- \n");
      break;
    }

    //getDouble
    while(1) {
      double v1 = value->getDouble("l3","a",0);
      if(v1 != 1.1) {
        printf("---[IniValue Test {getDouble()} case1] [FAILED]--- \n");
        break;
      }

      v1 = value->getDouble("l3","b",0);
      if(v1 != 2.1) {
        printf("---[IniValue Test {getDouble()} case2] [FAILED]--- \n");
        break;
      }

      v1 = value->getDouble("l3","c",0);
      if(v1 != 3.1) {
        printf("---[IniValue Test {getDouble()} case3] [FAILED]--- \n");
        break;
      }

      printf("---[IniValue Test {getDouble()} case4] [Success]--- \n");
      break;
    }

    //getBoolean
    while(1) {
      bool v1 = value->getBoolean("l4","a",false);
      if(!v1) {
        printf("---[IniValue Test {getBoolean()} case1] [FAILED]--- \n");
        break;
      }

      v1 = value->getBoolean("l4","b",true);
      if(v1) {
        printf("---[IniValue Test {getBoolean()} case2] [FAILED]--- \n");
        break;
      }

      v1 = value->getBoolean("l4","c",false);
      if(!v1) {
        printf("---[IniValue Test {getBoolean()} case3] [FAILED]--- \n");
        break;
      }

      printf("---[IniValue Test {getBoolean()} case4] [Success]--- \n");
      break;
    }

    //bool contains(String section,String tag);
    while(1) {
      if(!value->contains("l4","c")) {
        printf("---[IniValue Test {contains()} case1] [FAILED]--- \n");
        break;
      }

      if(value->contains("l4","ab")) {
        printf("---[IniValue Test {contains()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[IniValue Test {contains()} case3] [Success]--- \n");
      break;
    }
}
