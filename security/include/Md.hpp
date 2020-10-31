#ifndef __OBOTCHA_MD_HPP__
#define __OBOTCHA_MD_HPP__

#include "File.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Md) {

public:
   enum MdType {
      Md2,
      Md4,
      Md5,
   };

    _Md();
    _Md(int type);
    String encrypt(File);
    String encrypt(String);

private:
   int mType;

   static const int ReadDataSize;

   int computeStringMd5(unsigned char *dest_str, unsigned int dest_len, char *md5_str);
   int computeStringMd4(unsigned char *dest_str, unsigned int dest_len, char *md4_str);
#ifndef OPENSSL_NO_MD2   
   int computeStringMd2(unsigned char *dest_str, unsigned int dest_len, char *md2_str);
#endif   

   int computeFileMd5(const char *file_path, char *md5_str);
   int computeFileMd4(const char *file_path, char *md4_str);
#ifndef OPENSSL_NO_MD2   
   int computeFileMd2(const char *file_path, char *md2_str);
#endif   
};

}
#endif
