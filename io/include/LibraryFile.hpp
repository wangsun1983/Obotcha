#ifndef __OBOTCHA_LIBRARY_FILE_HPP__
#define __OBOTCHA_LIBRARY_FILE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(LibraryFile) {
public:
    explicit _LibraryFile(const char *);
    explicit _LibraryFile(String path);
    ~_LibraryFile();

    //auto func = sample:getMethod<int(*)(int,int)>(createString("start"))
    //int ret = func(1,2);
    template<class Function>
    Function getMethod(String method) {
        return getMethod<Function>(method->toChars());
    }
    
    template<class Function>
    Function getMethod(const char *method) {
        return (Function) dlsym(mHandle, method);
    }

private:
    void *mHandle;
};

} // namespace obotcha
#endif
