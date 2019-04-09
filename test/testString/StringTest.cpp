#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "String.hpp"

using namespace obotcha;

int main() {

  printf("---[String Test Start]--- \n");
  //test replaceAll()
  while(1) {
      String str = createString("AaAbAc");
      String str2 = str->replaceAll("A","t");
      //printf("after replace is %s \n",str2->toChars());
      if(!str2->equals("tatbtc")) {
        printf("String replaceAll test1-------[FAIL] \n");
        break;
      }

      printf("String replaceAll test1-------[OK] \n");
      break;
  }

  //test replaceFirst()
  while(1) {
      String str = createString("AaAbAc");
      String str2 = str->replaceFirst("A","t");
      //printf("after replace is %s \n",str2->toChars());
      if(!str2->equals("taAbAc")) {
        printf("String replaceFirst test1-------[FAIL] \n");
        break;
      }

      printf("String replaceFirst test1-------[OK] \n");
      break;
  }

  //test toLowerCase()
  while(1) {
      String str = createString("AaAbAc");
      String str2 = str->toLowerCase();
      if(!str2->equals("aaabac")) {
        printf("String toLowerCase test1-------[FAIL] \n");
        break;
      }

      printf("String toLowerCase test1-------[OK] \n");
      break;
  }

  //test equalsIgnoreCase()
  while(1) {
      String str = createString("AaAbAc");
      if(!str->equalsIgnoreCase("aaabAC")) {
        printf("String equalsIgnoreCase test1-------[FAIL] \n");
        break;
      }

      printf("String equalsIgnoreCase test1-------[OK] \n");
      break;
  }

  //test endsWith()
  while(1) {
      String str = createString("AaAbAc");
      if(!str->endsWith("Ac")) {
        printf("String endsWith test1-------[FAIL] \n");
        break;
      }

      printf("String endsWith test1-------[OK] \n");
      break;
  }

  //containsIgnoreCase
  while(1) {
      String str = createString("AaAbAc");
      if(!str->containsIgnoreCase("ab")) {
        printf("String containsIgnoreCase test1-------[FAIL] \n");
        break;
      }

      if(str->containsIgnoreCase("dd")) {
        printf("String containsIgnoreCase test2-------[FAIL] \n");
        break;
      }

      printf("String containsIgnoreCase test1-------[OK] \n");
      break;
  }

}
