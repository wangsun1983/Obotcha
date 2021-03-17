#ifndef __OBOTCHA_LIBRARY_INPUT_STREAM_HPP__
#define __OBOTCHA_LIBRARY_INPUT_STREAM_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "LibraryFile.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LibraryFileInputStream) IMPLEMENTS(InputStream){
public:

    _LibraryFileInputStream(LibraryFile f);
    
    _LibraryFileInputStream(String path);

    int read();
    
    long read(ByteArray);

    bool open();
    
    void close();

    void * getMethod(String);

private:
    void *mHandle;

    LibraryFile mFile; 
};

}
#endif
