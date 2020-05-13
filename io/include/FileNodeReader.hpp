#ifndef __OBOTCHA_FILE_NODE_READER_HPP__
#define __OBOTCHA_FILE_NODE_READER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileNodeReader) {
public:
    static int readInt(String);

    static long readLong(String);

    static String readString(String);

    static String readString(String,int buffsize);
};

}
#endif
