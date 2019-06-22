#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "File.hpp"
#include "String.hpp"
#include "Base64.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

_Base64::_Base64() {
    //nothing
}

String _Base64::decode(String str) {
    int size = 0;
    char *p = _decode(str->toChars(),str->size(),false,&size);
    String result = createString(p);
    free(p);
    return result;
}

String _Base64::encode(String str) {
    int size = 0;
    char *p = _encode(str->toChars(),str->size(),false,&size);
    String result = createString(p);
    free(p);
    return result;
}
    
ByteArray _Base64::encode(ByteArray buff) {
    int size;
    char *p = _encode(buff->toValue(),buff->size(),false,&size);
    printf("encode buff size is %d \n",size);
    ByteArray result = createByteArray(p,size);
    free(p);
    return result;
}

ByteArray _Base64::decode(ByteArray buff) {
    int length = 0;
    char *p = _decode(buff->toValue(),buff->size(),false,&length);
    ByteArray result = createByteArray(p,length);
    return result;
}

ByteArray _Base64::encode(File f) {
    FileInputStream steam = createFileInputStream(f);
    ByteArray result = steam->readAll();
    return encode(result);
}

ByteArray _Base64::decode(File f) {
    FileInputStream steam = createFileInputStream(f);
    ByteArray result = steam->readAll();
    return decode(result);
}

char * _Base64::_encode(const char * input, int length, bool with_new_line,int *retLength) {
    printf("input is %s,length is %d",input,length);
    BIO * bmem = nullptr;
    BIO * b64 = nullptr;
    BUF_MEM * bptr = nullptr;
 
    b64 = BIO_new(BIO_f_base64());

    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }

    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    
    char * buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
 
    BIO_free_all(b64);
    //BIO_free_all(bmem);
    *retLength = bptr->length + 1;
    printf("bptr->length is %d \n",bptr->length);

    return buff;
}

char * _Base64::_decode(const char * input, int length, bool with_new_line,int *retLen) {
    BIO * b64 = nullptr;
    BIO * bmem = nullptr;

    char * buffer = (char *)malloc(length);
    memset(buffer, 0, length);
    *retLen = length;

    b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);
 
    
    BIO_free_all(bmem);
    //BIO_free_all(b64);

    return buffer;
}

}