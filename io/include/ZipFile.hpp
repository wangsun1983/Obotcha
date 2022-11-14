#ifndef __OBOTCHA_ZIP_FILE_HPP__
#define __OBOTCHA_ZIP_FILE_HPP__

#include "Object.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(ZipFile) IMPLEMENTS(File) {
  public:
    using _File::_File; // use File's all construct method
};

} // namespace obotcha
#endif
