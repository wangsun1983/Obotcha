#ifndef __STRING_READER_HPP__
#define __STRING_READER_HPP__

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

namespace obotcha {

DECLARE_SIMPLE_CLASS(StringReader) {
public:
    _StringReader(String);
    
    String readLine();

    void reset();

    ~_StringReader();

private:
    std::stringstream mStringStream;

};

}
#endif