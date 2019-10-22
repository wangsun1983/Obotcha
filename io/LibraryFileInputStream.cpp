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
    if(!mFile->exists()) {
        return false;
    }
    
    mHandle = dlopen(mFile->getAbsolutePath()->toChars(), RTLD_LAZY|RTLD_GLOBAL);
    
    char *error = nullptr;
    if ((error = dlerror()) != NULL)  {
       return false;
    }

    return true;
}
    
void * _LibraryFileInputStream::getMethod(String method) {
    char *error;
    void *result = dlsym(mHandle, method->toChars());

    return result;
}

void _LibraryFileInputStream::close() {
    dlclose(mHandle);
    mHandle = nullptr;
}


}

