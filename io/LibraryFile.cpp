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

#include "File.hpp"
#include "LibraryFile.hpp"
#include "Log.hpp"
#include "MethodNotSupportException.hpp"
#include "FileNotFoundException.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_LibraryFile::_LibraryFile(const char *path) {
    File f = createFile(path);
    if (!f->exists()) {
        Trigger(FileNotFoundException,"lib file not found");
    }

    mHandle = dlopen(f->getAbsolutePath()->toChars(), RTLD_LAZY | RTLD_GLOBAL);

    char *error = dlerror();
    if (error != NULL) {
        Trigger(InitializeException,"lib file open failed");
    }
}
    
_LibraryFile::_LibraryFile(String path):_LibraryFile(path->toChars()) {

}

void *_LibraryFile::getMethod(String method) {
    return dlsym(mHandle, method->toChars());
}

void *_LibraryFile::getMethod(const char* method) {
    return dlsym(mHandle, method);
}

_LibraryFile::~_LibraryFile() {
    if (mHandle != nullptr) {
        dlclose(mHandle);
        mHandle = nullptr;
    }
}

} // namespace obotcha