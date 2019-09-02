#include <dlfcn.h>
#include "LibraryFileInputStream.hpp"

namespace obotcha {

_LibraryFileInputStream::_LibraryFileInputStream(LibraryFile f) {
    mFile = f;
}
    
_LibraryFileInputStream::_LibraryFileInputStream(String path) {
    mFile = createLibraryFile();
    mFile->setPath(path);
}


int _LibraryFileInputStream::read() {
    //Not Support
    return -1;
}
    
long _LibraryFileInputStream::read(ByteArray) {
    //Not Support
    return -1;
}

bool _LibraryFileInputStream::open() {
    printf("open file path is %s \n",mFile->getAbsolutePath()->toChars());
    if(!mFile->exists()) {
        return false;
    }
    printf("read file path is %s \n",mFile->getAbsolutePath()->toChars());
    mHandle = dlopen(mFile->getAbsolutePath()->toChars(), RTLD_LAZY|RTLD_GLOBAL);
    printf("mHandler is %x \n",mHandle);
    char *error = nullptr;
    if ((error = dlerror()) != NULL)  {
       printf("error is %s\n", error);
    }
}
    
void * _LibraryFileInputStream::getMethod(String method) {
    char *error;
    void *result = dlsym(mHandle, method->toChars());
    //f ((error = dlerror()) != NULL)  {
       //printf("getMethod error is %s\n", error);
    //}

    return result;
}

void _LibraryFileInputStream::close() {
    dlclose(mHandle);
    mHandle = nullptr;
}


}

