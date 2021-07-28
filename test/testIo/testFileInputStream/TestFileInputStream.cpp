#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"

using namespace obotcha;

int main() {
    //test readline
    printf("---[FileInputStream Test Start]--- \n");

    ByteArray testData = createByteArray(14);
    for(int i = 0;i<14;i++) {
      testData->fill(i,'a' + i);
    }
    
    //_FileInputStream(File f);
    while(1) {
      File f = createFile("abc.txt");
      FileInputStream stream = createFileInputStream(f);
      if(stream == nullptr) {
          printf("---[FileInputStream Test {construct(File)} case1] [FAIL]--- \n");
          break;
      }
      stream->close();

      f = createFile("test_data.txt");
      stream = createFileInputStream(f);
      if(stream == nullptr) {
          printf("---[FileInputStream Test {construct(File)} case2] [FAIL]--- \n");
          break;
      }
      stream->close();

      printf("---[FileInputStream Test {construct(File)} case3] [Success]--- \n");
      break;
    }
    
    //_FileInputStream(String path);
    while(1) {
      FileInputStream stream = createFileInputStream(createString("abc.txt"));
      if(stream == nullptr) {
          printf("---[FileInputStream Test {construct(String)} case1] [FAIL]--- \n");
          break;
      }
      stream->close();

      stream = createFileInputStream(createString("test_data.txt"));
      if(stream == nullptr) {
          printf("---[FileInputStream Test {construct(String)} case2] [FAIL]--- \n");
          break;
      }
      stream->close();

      printf("---[FileInputStream Test {construct(String)} case3] [Success]--- \n");
      break;
    }
    

    //int read();
    while(1) {
      FileInputStream stream = createFileInputStream(createString("abc.txt"));
      stream->open();
      try{
        int v = stream->read();
        printf("---[FileInputStream Test {read()} case1] [FAIL]--- \n");
        break;
      } catch(FileNotFoundException e) {
        //TODO
      }
      stream->close();

      stream = createFileInputStream(createString("test_data.txt"));
      stream->open();
      int value = stream->read();
      if(value == 0) {
        printf("---[FileInputStream Test {read()} case2] [FAIL]--- \n");
        break;
      }

      printf("---[FileInputStream Test {read()} case3] [Success]--- \n");
      break;
    }

    //long read(ByteArray buffer);
    while(1) {
        FileInputStream stream = createFileInputStream(createString("abc.txt"));
        stream->open();
        ByteArray buff = createByteArray(16);
        long size = stream->read(buff);
        if(size != -1) {
            printf("---[FileInputStream Test {read(ByteArray)} case1] [FAIL]--- \n");
            break;
        }

        stream->close();

        stream = createFileInputStream(createString("test_data.txt"));
        stream->open();
        buff = createByteArray(8);
        size = stream->read(buff);
        
        if(size != 8) {
            printf("---[FileInputStream Test {read(ByteArray)} case2] [FAIL]--- \n");
            break;
        }

        for(int i = 0;i < buff->size();i++) {
            if(buff->at(i) != testData->at(i)) {
                printf("---[FileInputStream Test {read(ByteArray)} case3] [FAIL]--- \n");
                break;
            }
        }
        stream->close();

        File f = createFile("test_data.txt");
        stream = createFileInputStream(createString("test_data.txt"));
        stream->open();
        buff = createByteArray(64);
        size = stream->read(buff);
        
        if(size != f->length()) {
            printf("---[FileInputStream Test {read(ByteArray)} case4] [FAIL]--- \n");
            break;
        }

        for(int i = 0;i < testData->size();i++) {
            if(buff->at(i) != testData->at(i)) {
                printf("---[FileInputStream Test {read(ByteArray)} case5] [FAIL]--- \n");
                break;
            }
        }

        printf("---[FileInputStream Test {read(ByteArray)} case6] [Success]--- \n");
        break;
    }
    
    //ByteArray readAll();
    while(1) {
        FileInputStream stream = createFileInputStream(createString("abc.txt"));
        stream->open();
        ByteArray array = stream->readAll();
        if(array != nullptr) {
            printf("---[FileInputStream Test {readAll()} case1] [FAIL]--- \n");
            break;
        }
        stream->close();

        File f = createFile("test_data.txt");
        stream = createFileInputStream(createString("test_data.txt"));
        stream->open();        
        array = stream->readAll();
        if(array->size() != f->length()) {
            printf("---[FileInputStream Test {readAll()} case2] [FAIL]--- \n");
            break;
        }
        stream->close();

        printf("---[FileInputStream Test {readAll()} case3] [Success]--- \n");
        break;
    }

    //bool open();
    while(1) {
        FileInputStream stream = createFileInputStream(createString("abc.txt"));
        if(stream->open()) {
            printf("---[FileInputStream Test {open()} case1] [FAIL]--- \n");
            break;
        }

        stream = createFileInputStream(createString("test_data.txt"));
        if(!stream->open()) {
            printf("---[FileInputStream Test {open()} case2] [FAIL]--- \n");
            break;
        }

        printf("---[FileInputStream Test {open()} case3] [Success]--- \n");
        break;
    }

    //void close();
    while(1) {
        FileInputStream stream = createFileInputStream(createString("abc.txt"));
        stream->open();
        stream->close();
        printf("---[FileInputStream Test {close()} case3] [Success]--- \n");
        break;
    }

    //String readLine();
    while(1) {
        FileInputStream stream = createFileInputStream(createString("abc.txt"));
        stream->open();
        String line = stream->readLine();
        if(line != nullptr) {
            printf("---[FileInputStream Test {readLine()} case1] [FAIL]--- \n");
            break;
        }

        stream = createFileInputStream(createString("test_data2.txt"));
        stream->open();
        String list[] = {
          createString("abc"),
          createString("def"),
          createString("ghi"),
          createString("jkl")
        };

        int index = 0;
        while(1) {
            String s = stream->readLine();
            if(s == nullptr) {
              break;
            }

            if(!s->equals(list[index])) {
                printf("---[FileInputStream Test {readLine()} case2] [FAIL]--- \n");
                break;
            }
            index++;
        }

        printf("---[FileInputStream Test {readLine()} case3] [Success]--- \n");
        break;
    }

    //void reset();
    while(1) {
        FileInputStream stream = createFileInputStream(createString("abc.txt"));
        stream->open();
        stream->reset();

        stream = createFileInputStream(createString("test_data2.txt"));
        stream->open();
        while(1) {
            String s = stream->readLine();
            if(s == nullptr) {
              break;
            }
        }

        String s = stream->readLine();
        if(s != nullptr) {
            printf("---[FileInputStream Test {reset()} case1] [FAIL]--- \n");
            break;
        }

        stream->reset();
        String list[] = {
          createString("abc"),
          createString("def"),
          createString("ghi"),
          createString("jkl")
        };

        int index = 1;
        s = stream->readLine();
        if(s == nullptr || !s->equals(list[0])) {
            printf("---[FileInputStream Test {reset()} case2] [FAIL]--- \n");
            break;
        }

        while(1) {
            String s = stream->readLine();
            if(s == nullptr) {
              break;
            }

            if(!s->equals(list[index])) {
                printf("---[FileInputStream Test {reset()} case3] [FAIL]--- \n");
                break;
            }
            index++;
        }

        printf("---[FileInputStream Test {reset()} case4] [Success]--- \n");
        break;
    }

}
