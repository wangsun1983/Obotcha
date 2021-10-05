#ifndef __OBOTCHA_LIBRARY_FILE_HPP__
#define __OBOTCHA_LIBRARY_FILE_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(LibraryFile) {
public:
    _LibraryFile(const char *);
    
    _LibraryFile(String path);

    ~_LibraryFile();

    void *getMethod(String method);
    void *getMethod(const char *);

private:
    void *mHandle;
};

} // namespace obotcha
#endif
