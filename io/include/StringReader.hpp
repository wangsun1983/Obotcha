#ifndef __OBOTCHA_STRING_READER_HPP__
#define __OBOTCHA_STRING_READER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(StringReader) {
public:
    _StringReader(FileInputStream);
    
    String readLine();

    void reset();

    ~_StringReader();

private:
    std::stringstream mStringStream;

};

}
#endif
