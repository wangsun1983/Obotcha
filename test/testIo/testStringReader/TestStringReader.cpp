#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "StringReader.hpp"

using namespace obotcha;

int main() {

  printf("---[StringReader Test Start]--- \n");
  //readLine();
  while(1) {
      String str = createString("hello\nworld\nni\nhao");
      StringReader reader = createStringReader(str);
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[StringReader Test {readLine()} case1] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[StringReader Test {readLine()} case2] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[StringReader Test {readLine()} case3] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[StringReader Test {readLine()} case4] [FAIL]--- \n");
          break;
      }

      printf("---[StringReader Test {readLine()} case5] [Success]--- \n");
      break;
  }

  //reset
  while(1) {
      String str = createString("hello\nworld\nni\nhao");
      StringReader reader = createStringReader(str);
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[StringReader Test {reset()} case1] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[StringReader Test {reset()} case2] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[StringReader Test {reset()} case3] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[StringReader Test {reset()} case4] [FAIL]--- \n");
          break;
      }

      reader->reset();
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[StringReader Test {reset()} case5] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[StringReader Test {reset()} case6] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[StringReader Test {reset()} case7] [FAIL]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[StringReader Test {reset()} case8] [FAIL]--- \n");
          break;
      }

      printf("---[StringReader Test {readLine()} case9] [Success]--- \n");
      break;
  }

}
