#ifndef __LIBRARY_FILE_HPP__
#define __LIBRARY_FILE_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LibraryFile) EXTENDS(File){
public:
    using _File::_File; //use File's all construct method
};

}
#endif