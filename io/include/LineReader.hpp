#ifndef __OBOTCHA_LINE_READER_HPP__
#define __OBOTCHA_LINE_READER_HPP__

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
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(LineReader) {
  public:
    _LineReader(File);

    _LineReader(String);

    _LineReader(ByteArray); 

    String readLine();

    void reset();

    ~_LineReader();

  private:
    enum type {
      ReadFile,
      ReadContent
    };

    std::stringstream mStringStream;
    std::ifstream mFileStream;

    int type;
};

} // namespace obotcha
#endif
