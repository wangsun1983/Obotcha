#ifndef __ZIP_FILE_HPP__
#define __ZIP_FILE_HPP__

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

DECLARE_SIMPLE_CLASS(ZipFile) EXTENDS(File){
public:
    using _File::_File; //use File's all construct method
};

}
#endif