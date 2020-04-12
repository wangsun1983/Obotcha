#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "FileWatcher.hpp"

using namespace obotcha;

int testCount = 0;

DECLARE_SIMPLE_CLASS(MyFileObserver) IMPLEMENTS(FileObserver){
public:
    void onFileUpdate(String filepath,int op) {
        printf("------------------------------------file %s,is %d \n",filepath->toChars(),op);
        //testCount++;
    }
};

int main() {

    printf("---[FileWatcher Test Start]--- \n");


    printf("---[TimeWatcher Test {start/stop()} case1] [FAIL]--- \n");
    break;
    FileWatcher watcher = st(FileWatcher)::getInstance();
    watcher->startWatch("/home/test/mysource/Obotcha/test/testFileWatcher/makefile",
    FileObserverType::Modify,
    createMyFileObserver());

}
