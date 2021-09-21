#ifndef __OBOTCHA_MEMORY_FILE_HPP__
#define __OBOTCHA_MEMORY_FILE_HPP__

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

DECLARE_CLASS(MemoryFile) IMPLEMENTS(File) {
  public:
    using _File::_File; // use File's all construct method
};

} // namespace obotcha
#endif
