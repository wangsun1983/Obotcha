#ifndef __OBOTCHA_MD_HPP__
#define __OBOTCHA_MD_HPP__

#include "String.hpp"
#include "File.hpp"
#include "String.hpp"
#include "MessageDigestInterface.hpp"

namespace obotcha {

DECLARE_CLASS(Md) IMPLEMENTS(MessageDigestInterface) {

public:
   enum class Type {
      Md2 = 0,
      Md4,
      Md5,
   };

   _Md(Type type = Type::Md5);
   String encodeContent(ByteArray) override;
   String encodeFile(File) override;

private:
   Type mType = Type::Md5;

   static const ssize_t ReadDataSize;

   int computeStringMd5(const byte *dest_str, size_t dest_len, char *md5_str) const;
   int computeStringMd4(const byte *dest_str, size_t dest_len, char *md4_str) const;
#ifndef OPENSSL_NO_MD2   
   int computeStringMd2(const byte *dest_str, size_t dest_len, char *md2_str) const;
#endif   

   int computeFileMd5(const char *file_path, char *md5_str) const;
   int computeFileMd4(const char *file_path, char *md4_str) const;
#ifndef OPENSSL_NO_MD2   
   int computeFileMd2(const char *file_path, char *md2_str) const;
#endif   
};

}
#endif
