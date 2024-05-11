/**
 * @file LibraryFile.cpp
 * @brief A representation of library file.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include <dlfcn.h>

#include "File.hpp"
#include "LibraryFile.hpp"
#include "Log.hpp"
#include "FileNotFoundException.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_LibraryFile::_LibraryFile(const char *path) {
    File f = File::New(path);
    Panic(!f->exists(),FileNotFoundException,"lib file not found")
    mHandle = dlopen(f->getAbsolutePath()->toChars(), RTLD_LAZY | RTLD_GLOBAL);
    if (!mHandle) {
        LOG(ERROR)<<"LibraryFile open lib fail,reason is "<<dlerror();
        Trigger(InitializeException,"lib file open failed")
    }
}
    
_LibraryFile::_LibraryFile(String path):_LibraryFile(path->toChars()) {

}

_LibraryFile::~_LibraryFile() {
    if (mHandle != nullptr) {
        dlclose(mHandle);
        mHandle = nullptr;
    }
}

} // namespace obotcha
