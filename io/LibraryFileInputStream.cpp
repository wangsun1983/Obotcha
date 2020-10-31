/**
 * @file FileNodeReader.cpp
 * @brief write data to file data(like dev/xxxx)
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <dlfcn.h>
#include "LibraryFileInputStream.hpp"
#include "MethodNotSupportException.hpp"
#include "Log.hpp"

namespace obotcha {

_LibraryFileInputStream::_LibraryFileInputStream(LibraryFile f) {
    mFile = f;
}
    
_LibraryFileInputStream::_LibraryFileInputStream(String path) {
    mFile = createLibraryFile(path);
}

int _LibraryFileInputStream::read() {
    Trigger(MethodNotSupportException,"LibraryFileInputStream not support read");
}
    
long _LibraryFileInputStream::read(ByteArray) {
    Trigger(MethodNotSupportException,"LibraryFileInputStream not support read");
}

bool _LibraryFileInputStream::open() {
    if(!mFile->exists()) {
        return false;
    }
    
    mHandle = dlopen(mFile->getAbsolutePath()->toChars(), RTLD_LAZY|RTLD_GLOBAL);
    
    char *error = dlerror();
    if (error != NULL)  {
        LOG(ERROR)<<"LibraryFileInputStream open fail,reason is "<<error;
        return false;
    }

    return true;
}
    
void * _LibraryFileInputStream::getMethod(String method) {
    void *result = dlsym(mHandle, method->toChars());
    return result;
}

void _LibraryFileInputStream::close() {
    if(mHandle != nullptr) {
        dlclose(mHandle);
        mHandle = nullptr;
    }
}


}

