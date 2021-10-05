#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "LineReader.hpp"

using namespace obotcha;

void testLineReader() {
  //readLine();
  while(1) {
      String str = createString("hello\nworld\nni\nhao");
      LineReader reader = createLineReader(str);
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[LineReader Test {readLine()} case1] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[LineReader Test {readLine()} case2] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[LineReader Test {readLine()} case3] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[LineReader Test {readLine()} case4] [FAILED]--- \n");
          break;
      }

      printf("---[LineReader Test {readLine()} case5] [OK]--- \n");
      break;
  }

  //reset
  while(1) {
      String str = createString("hello\nworld\nni\nhao");
      LineReader reader = createLineReader(str);
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[LineReader Test {reset()} case1] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[LineReader Test {reset()} case2] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[LineReader Test {reset()} case3] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[LineReader Test {reset()} case4] [FAILED]--- \n");
          break;
      }

      reader->reset();
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[LineReader Test {reset()} case5] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[LineReader Test {reset()} case6] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[LineReader Test {reset()} case7] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[LineReader Test {reset()} case8] [FAILED]--- \n");
          break;
      }

      printf("---[LineReader Test {readLine()} case9] [OK]--- \n");
      break;
  }

  //read file
  while(1) {
    LineReader reader = createLineReader(createFile("./tmp/base_data"));
    if(!reader->readLine()->equals(createString("hello"))) {
        printf("---[LineReader Test {readLine()} case10] [FAILED]--- \n");
        break;
    }

    if(!reader->readLine()->equals(createString("world"))) {
        printf("---[LineReader Test {readLine()} case11] [FAILED]--- \n");
        break;
    }

    if(!reader->readLine()->equals(createString("ni"))) {
        printf("---[LineReader Test {readLine()} case12] [FAILED]--- \n");
        break;
    }

    if(!reader->readLine()->equals(createString("hao"))) {
        printf("---[LineReader Test {readLine()} case13] [FAILED]--- \n");
        break;
    }

    printf("---[LineReader Test {readLine()} case14] [OK]--- \n");
    break;
  }

  //reset file
  while(1) {
      LineReader reader = createLineReader(createFile("./tmp/base_data"));
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[LineReader Test {reset()} case15] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[LineReader Test {reset()} case16] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[LineReader Test {reset()} case17] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[LineReader Test {reset()} case18] [FAILED]--- \n");
          break;
      }

      reader->reset();
      if(!reader->readLine()->equals(createString("hello"))) {
          printf("---[LineReader Test {reset()} case19] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("world"))) {
          printf("---[LineReader Test {reset()} case20] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("ni"))) {
          printf("---[LineReader Test {reset()} case21] [FAILED]--- \n");
          break;
      }

      if(!reader->readLine()->equals(createString("hao"))) {
          printf("---[LineReader Test {reset()} case22] [FAILED]--- \n");
          break;
      }

      printf("---[LineReader Test {readLine()} case23] [OK]--- \n");
      break;
  }

  printf("---[LineReader Test {readLine()} case100] [OK]--- \n");
}
