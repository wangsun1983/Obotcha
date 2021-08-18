#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "FileWatcher.hpp"

using namespace obotcha;

int testCount = 0;

DECLARE_CLASS(MyFileObserver) IMPLEMENTS(FileObserver){
public:
    void onFileUpdate(String filepath,int op) {
        printf("------------------------------------file %s,is %x \n",filepath->toChars(),op);
        //testCount++;
    }
};

int main() {

    printf("---[FileWatcher Test Start]--- \n");

    FileWatcher watcher = createFileWatcher();
    watcher->startWatch("./testdata.txt",st(FileWatcher)::Full,createMyFileObserver());
    while(1) {sleep(100);}
}
