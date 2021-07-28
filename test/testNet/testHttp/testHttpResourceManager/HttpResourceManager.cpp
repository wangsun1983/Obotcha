
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpResourceManager.hpp"

using namespace obotcha;


int main() {

    HttpResourceManager instance = st(HttpResourceManager)::getInstance();
    instance->setViewRedirect("hello","hello.html");
    instance->setResourceDir("./static");
    File file = instance->findResource("hello1.html");
    if(file != nullptr) {
        printf("file path is %s \n",file->getAbsolutePath()->toChars());
    }

    File file2 = instance->findResource("hello");
    if(file2 != nullptr) {
        printf("file2 path is %s \n",file2->getAbsolutePath()->toChars());
    }
}
