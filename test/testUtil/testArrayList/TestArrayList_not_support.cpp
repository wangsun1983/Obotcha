#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "MethodNotSupportException.hpp"

using namespace obotcha;

void testArrayList_type_int() {
  //ARRAYLIST_NOT_SUPPORT(bool);
  while(1) {
    try {
        ArrayList<bool> list = createArrayList<bool>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case1] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case2] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(byte);
  while(1) {
    try {
        ArrayList<byte> list = createArrayList<byte>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case3] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case4] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(double);
  while(1) {
    try {
        ArrayList<double> list = createArrayList<double>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case5] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case6] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(float);
  while(1) {
    try {
        ArrayList<float> list = createArrayList<float>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case7] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case8] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(int);
  while(1) {
    try {
        ArrayList<int> list = createArrayList<int>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case9] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case10] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(long);
  while(1) {
    try {
        ArrayList<long> list = createArrayList<long>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case11] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case12] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(std::uint8_t);
  while(1) {
    try {
        ArrayList<std::uint8_t> list = createArrayList<std::uint8_t>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case13] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case14] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(std::uint16_t);
  while(1) {
    try {
        ArrayList<std::uint16_t> list = createArrayList<std::uint16_t>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case15] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case16] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(std::uint32_t);
  while(1) {
    try {
        ArrayList<std::uint32_t> list = createArrayList<std::uint32_t>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case17] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case18] [Fail]--- \n");
    break;
  }

  //ARRAYLIST_NOT_SUPPORT(std::uint64_t);
  while(1) {
    try {
        ArrayList<std::uint64_t> list = createArrayList<std::uint64_t>();
    } catch(MethodNotSupportException e){
        printf("---[ArrayList<int> Test {add()} case19] [OK]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {add()} case20] [Fail]--- \n");
    break;
  }
}
