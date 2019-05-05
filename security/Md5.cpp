#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//extern "C" {
//#include "md5.h"
//}

#include "File.hpp"
#include "String.hpp"
#include "Md5.hpp"

namespace obotcha {

#define READ_DATA_SIZE  1024
#define MD5_SIZE        16
#define MD5_STR_LEN     (MD5_SIZE * 2)

String _Md5::verify(File f) {
    char md5_str[MD5_STR_LEN + 1];
    int ret = computeFileMd5(f->getAbsolutePath()->toChars(), md5_str);
    if(ret == 0) {
        return createString(md5_str);
    }

    return nullptr;
}

String _Md5::verify(String s) {
    char md5_str[MD5_STR_LEN + 1];
    int ret = computeStringMd5((unsigned char *)s->toChars(), s->size(), md5_str);
    if(ret == 0) {
        return createString(md5_str);
    }

    return nullptr;
}

int _Md5::computeStringMd5(unsigned char *dest_str, unsigned int dest_len, char *md5_str) {
    int i;
    unsigned char md5_value[MD5_SIZE];
    MD5_CTX md5;

    // init md5
    MD5_Init(&md5);

    MD5_Update(&md5, dest_str, dest_len);

    MD5_Final(md5_value,&md5);

    // convert md5 value to md5 string
    for(i = 0; i < MD5_SIZE; i++)
    {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }

    return 0;
}

int _Md5::computeFileMd5(const char *file_path, char *md5_str) {
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md5_value[MD5_SIZE];
    MD5_CTX md5;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }

    // init md5
    MD5_Init(&md5);

    while (1)
    {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret)
        {
            perror("read");
            close(fd);
            return -1;
        }

        MD5_Update(&md5, data, ret);

        if (0 == ret || ret < READ_DATA_SIZE)
        {
            break;
        }
    }

    close(fd);

    MD5_Final(md5_value,&md5);

    // convert md5 value to md5 string
    for(i = 0; i < MD5_SIZE; i++)
    {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }

    return 0;
}

}
