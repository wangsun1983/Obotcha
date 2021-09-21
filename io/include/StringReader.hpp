#ifndef __OBOTCHA_STRING_READER_HPP__
#define __OBOTCHA_STRING_READER_HPP__

#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "FileInputStream.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(StringReader) {
  public:
    _StringReader(FileInputStream);

    String readLine();

    void reset();

    ~_StringReader();

  private:
    std::stringstream mStringStream;
};

} // namespace obotcha
#endif
