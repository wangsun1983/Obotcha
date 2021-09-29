#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "File.hpp"
#include "String.hpp"
#include "Base64.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

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
    String result = createByteArray((const byte *)p,size)->toString();
    free(p);
    return result;
}
    
ByteArray _Base64::encode(ByteArray buff) {
    int size = 0;
    char *p = _encode((char *)buff->toValue(),buff->size(),false,&size);
    ByteArray result = createByteArray((byte *)p,size);
    free(p);
    return result;
}

ByteArray _Base64::encode(ByteArray buff,int length) {
    int size = 0;
    char *p = _encode((char *)buff->toValue(),length,false,&size);
    ByteArray result = createByteArray((byte *)p,size);
    free(p);
    return result;
}

ByteArray _Base64::decode(ByteArray buff) {
    int length = 0;
    char *p = _decode((char *)buff->toValue(),buff->size(),false,&length);
    ByteArray result = createByteArray((byte *)p,length);
    free(p);
    return result;
}

ByteArray _Base64::encode(File f) {
    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray result = stream->readAll();
    stream->close();
    return encode(result);
}

ByteArray _Base64::decode(File f) {
    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray result = stream->readAll();
    stream->close();
    return decode(result);
}

char * _Base64::_encode(const char * input, int length, bool with_new_line,int *retLength) {
    BIO * bmem = nullptr;
    BUF_MEM * bptr = nullptr;
 
    BIO * b64 = BIO_new(BIO_f_base64());

    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }

    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    
    int encodeLength = bptr->length;  //strlen(bptr->data) + 1;

    char * buff = (char *)malloc(encodeLength+1);
    memset(buff,0,encodeLength);
    memcpy(buff, bptr->data, encodeLength);
    
    BIO_free_all(b64);
    *retLength = encodeLength;
    
    return buff;
}

char * _Base64::_decode(const char * input, int length, bool with_new_line,int *retLen) {
    BIO * bmem = nullptr;

    char * buffer = (char *)malloc(length);
    memset(buffer, 0, length);
  
    BIO * b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    *retLen = BIO_read(bmem, buffer, length);
    if(bmem) {
        BIO_free_all(bmem);
    }
    
    return buffer;
}

}