#ifndef __OBOTCHA_LIBRARY_FILE_HPP__
#define __OBOTCHA_LIBRARY_FILE_HPP__

#include "Object.hpp"

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
