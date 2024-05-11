/**
 * @file Md.cpp
 * @brief A class that can be used to compute the Md5/Md4 of a data stream.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <unistd.h>

extern "C" {
    #include "openssl/md5.h"
    #include "openssl/md4.h"
#ifndef OPENSSL_NO_MD2         
    #include "openssl/md2.h"
#endif    
}

#include "Md.hpp"
#include "Inspect.hpp"
#include "Log.hpp"

namespace obotcha {

const ssize_t _Md::ReadDataSize = 1024;

_Md::_Md(_Md::Type type):mType(type) {
}

String _Md::encodeFile(File f) {
    switch(mType) {
        
#ifndef OPENSSL_NO_MD2       
        case Type::Md2:{
            char md2_str[MD2_DIGEST_LENGTH * 2 + 1];
            if(computeFileMd2(f->getAbsolutePath()->toChars(), md2_str) == 0) {
                return String::New(md2_str);
            }
        } break;
#endif        

        case Type::Md5: {
            char md5_str[MD5_DIGEST_LENGTH * 2 + 1];
            if(computeFileMd5(f->getAbsolutePath()->toChars(), md5_str) == 0) {
                return String::New(md5_str);
            }
        } break;

        case Type::Md4: {
            char md4_str[MD4_DIGEST_LENGTH * 2 + 1];
            if(computeFileMd4(f->getAbsolutePath()->toChars(), md4_str) == 0) {
                return String::New(md4_str);
            }
        } break;

        default:
            LOG(ERROR)<<"Md encodeFile unknow type :"<<static_cast<int>(mType);
        break;
    }

    return nullptr;
}

String _Md::encodeContent(ByteArray s) {
    switch(mType) {
#ifndef OPENSSL_NO_MD2
        case Type::Md2: {
            char md2_str[MD2_DIGEST_LENGTH*2 + 1];
            if(computeStringMd2((unsigned char *)s->toChars(), s->size(), md2_str) == 0) {
                return String::New(md2_str);
            }
        } break;
#endif
        case Type::Md4: {
            char md4_str[MD4_DIGEST_LENGTH*2 + 1];
            if(computeStringMd4(s->toValue(), s->size(), md4_str) == 0) {
                return String::New(md4_str);
            }
        } break;

        case Type::Md5: {
            char md5_str[MD5_DIGEST_LENGTH*2 + 1];
            if(computeStringMd5(s->toValue(), s->size(), md5_str) == 0) {
                return String::New(md5_str);
            }
        } break;

        default:
            LOG(ERROR)<<"Md encodeContent unknow type :"<<static_cast<int>(mType);
        break;
    }

    return nullptr;
}

int _Md::computeStringMd5(const byte *dest_str, size_t dest_len, char *md5_str) const {
    unsigned char md5_value[MD5_DIGEST_LENGTH];
    MD5_CTX md5;

    // init md5
    MD5_Init(&md5);

    MD5_Update(&md5, dest_str, dest_len);

    MD5_Final(md5_value,&md5);

    // convert md5 value to md5 string
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }

    return 0;
}

int _Md::computeStringMd4(const byte *dest_str, size_t dest_len, char *md4_str) const {
    unsigned char md4_value[MD4_DIGEST_LENGTH];
    MD4_CTX md4;

    // init md5
    MD4_Init(&md4);

    MD4_Update(&md4, dest_str, dest_len);

    MD4_Final(md4_value,&md4);

    // convert md5 value to md5 string
    for(int i = 0; i < MD4_DIGEST_LENGTH; i++) {
        snprintf(md4_str + i*2, 2+1, "%02x", md4_value[i]);
    }

    return 0;
}

#ifndef OPENSSL_NO_MD2
int _Md::computeStringMd2(const byte *dest_str, size_t dest_len, char *md2_str) const {
    unsigned char md2_value[MD2_DIGEST_LENGTH];
    MD2_CTX md2;

    // init md5
    MD2_Init(&md2);

    MD2_Update(&md2, dest_str, dest_len);

    MD2_Final(md2_value,&md2);

    // convert md5 value to md5 string
    for(int i = 0; i < MD4_DIGEST_LENGTH; i++) {
        snprintf(md2_str + i*2, 2+1, "%02x", md2_value[i]);
    }

    return 0;
}
#endif

int _Md::computeFileMd5(const char *file_path, char *md5_str) const {
    int fd;
    unsigned char data[ReadDataSize];
    unsigned char md5_value[MD5_DIGEST_LENGTH];
    MD5_CTX md5;

    fd = open(file_path, O_RDONLY);
    Inspect(fd == -1,-1)

    // init md5
    MD5_Init(&md5);

    while(true) {
        ssize_t ret = read(fd, data, ReadDataSize);
        if (-1 == ret) {
            perror("read");
            close(fd);
            return -1;
        }

        MD5_Update(&md5, data, ret);

        if (0 == ret || ret < ReadDataSize) {
            break;
        }
    }

    close(fd);

    MD5_Final(md5_value,&md5);

    // convert md5 value to md5 string
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }

    return 0;
}

int _Md::computeFileMd4(const char *file_path, char *md4_str) const {
    int fd;
    unsigned char data[ReadDataSize];
    unsigned char md4_value[MD4_DIGEST_LENGTH];
    MD4_CTX md4;

    fd = open(file_path, O_RDONLY);
    Inspect(fd == -1,-1)

    // init md5
    MD4_Init(&md4);

    while(true) {
        ssize_t ret = read(fd, data, ReadDataSize);
        if (-1 == ret) {
            perror("read");
            close(fd);
            return -1;
        }

        MD4_Update(&md4, data, ret);

        if (0 == ret || ret < ReadDataSize) {
            break;
        }
    }

    close(fd);

    MD4_Final(md4_value,&md4);

    // convert md5 value to md5 string
    for(int i = 0; i < MD4_DIGEST_LENGTH; i++) {
        snprintf(md4_str + i*2, 2+1, "%02x", md4_value[i]);
    }

    return 0;
}

#ifndef OPENSSL_NO_MD2
int _Md::computeFileMd2(const char *file_path, char *md2_str) const {
    int fd;
    unsigned char data[ReadDataSize];
    unsigned char md2_value[MD2_DIGEST_LENGTH];
    MD2_CTX md2;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    // init md5
    MD2_Init(&md2);

    InfiniteLoop {
        ssize_t ret = read(fd, data, ReadDataSize);
        if (-1 == ret) {
            perror("read");
            close(fd);
            return -1;
        }

        MD2_Update(&md2, data, ret);

        if (0 == ret || ret < ReadDataSize) {
            break;
        }
    }

    close(fd);

    MD2_Final(md2_value,&md2);

    // convert md5 value to md5 string
    for(int i = 0; i < MD2_DIGEST_LENGTH; i++) {
        snprintf(md2_str + i*2, 2+1, "%02x", md2_value[i]);
    }

    return 0;
}
#endif

}
