#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"

int main() {
    //test readline
    File f = createFile("/home/dji/mysource/Obotcha/test/testFileInputStream/TestFileInputStream.cpp");
    FileInputStream stream = createFileInputStream(f);
    if(stream->open()) {
      printf("open success \n");
    } else {
      printf("open fail \n");
    }

    String content = stream->readLine();
    printf("content is %s \n",content->toChars());

    while(true) {
      if(content == nullptr) {
        break;
      }

      printf("%s \n",content->toChars());
      content = stream->readLine();
    }
}
