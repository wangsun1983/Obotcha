#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "FileWatcher.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyFileObserver) IMPLEMENTS(FileObserver){
public:
    void onFileUpdate(String filepath,int op) {
        printf("------------------------------------file %s,is %d \n",filepath->toChars(),op);
    }
};

int main() {
    FileWatcher watcher = st(FileWatcher)::getInstance();
    watcher->startWatch("/home/dji/mysource/Obotcha/test/testFileWatcher/makefile",
    FileObserverType::Modify,
    createMyFileObserver());

    while(1) {

    }
}
