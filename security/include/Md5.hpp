#ifndef __MD5_HPP__
#define __MD5_HPP__

#include <openssl/md5.h>

#include "File.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Md5) {

public:
    String verify(File);
    String verify(String);

private:
   int computeStringMd5(unsigned char *dest_str, unsigned int dest_len, char *md5_str);
   int computeFileMd5(const char *file_path, char *md5_str);
};

}
#endif
