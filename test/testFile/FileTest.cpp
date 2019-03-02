#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"


DECLARE_SIMPLE_CLASS(ABC) {
public:
  int k;
};

int main() {
    char *path = "bb";

    File file = createFile(path);
    String ss = file->getName();
    printf("char is %s \n",ss->toChars());

    File file2 = createFile("/home/dji/mysource/Obotcha/test/testFile/FileTest.cpp");
    printf("file name is %s \n",file2->getName()->toChars());

    File file3 = createFile("/home/dji/mysource/Obotcha/test/testFile");
    ArrayList<File> files = file3->listFiles();
    int size = files->size();
    for(int i = 0;i<size;i++) {
      File f = files->get(i);
      printf("name is %s \n",f->getName()->toChars());
    }

    //File file4 = createFile("/home/dji/test/tst");
    //file4->removeAll();
    printf("===========start remove ============ \n");
    File file5 = createFile("/home/dji/test/tt");
    file5->removeAll();
    //printf("absolute path is %s\n",file->getAbsolutePath()->toChars());


}
