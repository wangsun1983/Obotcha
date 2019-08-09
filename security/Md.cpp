#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openssl/md5.h"
#include "openssl/md4.h"
#include "openssl/md2.h"

#include "File.hpp"
#include "String.hpp"
#include "Md.hpp"

namespace obotcha {

#define READ_DATA_SIZE  1024

_Md::_Md() {
    mType = MdType5;
}

_Md::_Md(int type) {
    mType = type;
}

String _Md::encrypt(File f) {
    switch(mType) {
        
#ifndef OPENSSL_NO_MD2       
        case MdType2:{
            char md2_str[MD2_DIGEST_LENGTH * 2 + 1];
            int ret = computeFileMd2(f->getAbsolutePath()->toChars(), md2_str);
            if(ret == 0) {
                return createString(md2_str);
            }
        }
        break;
#endif        

        case MdType5: {
            char md5_str[MD5_DIGEST_LENGTH * 2 + 1];
            int ret = computeFileMd5(f->getAbsolutePath()->toChars(), md5_str);
            if(ret == 0) {
                return createString(md5_str);
            }
        }
        break;

        case MdType4: {
            char md4_str[MD4_DIGEST_LENGTH * 2 + 1];
            int ret = computeFileMd4(f->getAbsolutePath()->toChars(), md4_str);
            if(ret == 0) {
                return createString(md4_str);
            }
        }
        break;
    }

    return nullptr;
}

String _Md::encrypt(String s) {
    //printf("encrypt trace1,mType is %d,Md5 is %d \n",mType,MdType5);
    switch(mType) {
#ifndef OPENSSL_NO_MD2
        case MdType2: {
            char md2_str[MD2_DIGEST_LENGTH*2 + 1];
            int ret = computeStringMd2((unsigned char *)s->toChars(), s->size(), md2_str);
            if(ret == 0) {
                return createString(md2_str);
            }
        }
        break;
#endif
        case MdType4: {
            char md4_str[MD4_DIGEST_LENGTH*2 + 1];
            int ret = computeStringMd4((unsigned char *)s->toChars(), s->size(), md4_str);
            if(ret == 0) {
                return createString(md4_str);
            }
        }
        break;

        case MdType5: {
            char md5_str[MD5_DIGEST_LENGTH*2 + 1];
            int ret = computeStringMd5((unsigned char *)s->toChars(), s->size(), md5_str);
            if(ret == 0) {
                return createString(md5_str);
            }
        }
        break;
    }

    return nullptr;
}

int _Md::computeStringMd5(unsigned char *dest_str, unsigned int dest_len, char *md5_str) {
    int i;
    unsigned char md5_value[MD5_DIGEST_LENGTH];
    MD5_CTX md5;

    // init md5
    MD5_Init(&md5);

    MD5_Update(&md5, dest_str, dest_len);

    MD5_Final(md5_value,&md5);

    // convert md5 value to md5 string
    for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }

    //printf("md5_str is %s,MD5_DIGEST_LENGTH is %d \n",md5_str,MD5_DIGEST_LENGTH);

    return 0;
}

int _Md::computeStringMd4(unsigned char *dest_str, unsigned int dest_len, char *md4_str) {
    int i;
    unsigned char md4_value[MD4_DIGEST_LENGTH];
    MD4_CTX md4;

    // init md5
    MD4_Init(&md4);

    MD4_Update(&md4, dest_str, dest_len);

    MD4_Final(md4_value,&md4);

    // convert md5 value to md5 string
    for(i = 0; i < MD4_DIGEST_LENGTH; i++) {
        snprintf(md4_str + i*2, 2+1, "%02x", md4_value[i]);
    }

    return 0;
}

#ifndef OPENSSL_NO_MD2
int _Md::computeStringMd2(unsigned char *dest_str, unsigned int dest_len, char *md2_str) {
    int i;
    unsigned char md2_value[MD2_DIGEST_LENGTH];
    MD2_CTX md2;

    // init md5
    MD2_Init(&md2);

    MD2_Update(&md2, dest_str, dest_len);

    MD2_Final(md2_value,&md2);

    // convert md5 value to md5 string
    for(i = 0; i < MD4_DIGEST_LENGTH; i++) {
        snprintf(md2_str + i*2, 2+1, "%02x", md2_value[i]);
    }

    return 0;
}
#endif

int _Md::computeFileMd5(const char *file_path, char *md5_str) {
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md5_value[MD5_DIGEST_LENGTH];
    MD5_CTX md5;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    // init md5
    MD5_Init(&md5);

    while (1) {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret) {
            perror("read");
            close(fd);
            return -1;
        }

        MD5_Update(&md5, data, ret);

        if (0 == ret || ret < READ_DATA_SIZE) {
            break;
        }
    }

    close(fd);

    MD5_Final(md5_value,&md5);

    // convert md5 value to md5 string
    for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }

    return 0;
}

int _Md::computeFileMd4(const char *file_path, char *md4_str) {
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md4_value[MD4_DIGEST_LENGTH];
    MD4_CTX md4;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    // init md5
    MD4_Init(&md4);

    while (1) {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret) {
            perror("read");
            close(fd);
            return -1;
        }

        MD4_Update(&md4, data, ret);

        if (0 == ret || ret < READ_DATA_SIZE) {
            break;
        }
    }

    close(fd);

    MD4_Final(md4_value,&md4);

    // convert md5 value to md5 string
    for(i = 0; i < MD4_DIGEST_LENGTH; i++) {
        snprintf(md4_str + i*2, 2+1, "%02x", md4_value[i]);
    }

    return 0;
}

#ifndef OPENSSL_NO_MD2
int _Md::computeFileMd2(const char *file_path, char *md2_str) {
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md2_value[MD2_DIGEST_LENGTH];
    MD2_CTX md2;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    // init md5
    MD2_Init(&md2);

    while (1) {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret) {
            perror("read");
            close(fd);
            return -1;
        }

        MD2_Update(&md2, data, ret);

        if (0 == ret || ret < READ_DATA_SIZE) {
            break;
        }
    }

    close(fd);

    MD2_Final(md2_value,&md2);

    // convert md5 value to md5 string
    for(i = 0; i < MD2_DIGEST_LENGTH; i++) {
        snprintf(md2_str + i*2, 2+1, "%02x", md2_value[i]);
    }

    return 0;
}
#endif

}
