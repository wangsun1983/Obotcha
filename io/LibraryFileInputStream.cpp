#include <dlfcn.h>
#include "LibraryFileInputStream.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

_LibraryFileInputStream::_LibraryFileInputStream(LibraryFile f) {
    mFile = f;
}
    
_LibraryFileInputStream::_LibraryFileInputStream(String path) {
    mFile = createLibraryFile();
    mFile->setPath(path);
}


int _LibraryFileInputStream::read() {
    throw new MethodNotSupportException("LibraryFileInputStream not support read");
}
    
long _LibraryFileInputStream::read(ByteArray) {
    throw new MethodNotSupportException("LibraryFileInputStream not support read");
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
    void *result = dlsym(mHandle, method->toChars());
    return result;
}

void _LibraryFileInputStream::close() {
    dlclose(mHandle);
    mHandle = nullptr;
}


}

