#include "Base64.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

String _Base64::decode(String str) const {
    ByteArray data = _decode(str->toChars(),str->size(),false);
    return data->toString();
}

ByteArray _Base64::decodeBase64Url(ByteArray data) const {
    int size = data->size() + 2;
    ByteArray decodeBuff = createByteArray(size);
    memcpy(decodeBuff->toValue(),data->toValue(),data->size());
    decodeBuff[size - 1] = '=';
    decodeBuff[size - 2] = '=';
    
    auto p = decodeBuff->toValue();
    for(int i = 0;i < size;i++) {
        if(p[i] == '-') {
            p[i] = '+';
        } else if(p[i] == '_') {
            p[i] = '/';
        }
    }

    return decode(decodeBuff);
}

ByteArray _Base64::encodeBase64Url(ByteArray data) const {
    ByteArray result = _encode((const char *)data->toValue(),data->size(),false);
    auto p = (char *)result->toValue();
    int size = result->size();
    //Replaces “+” by “-” (minus)
    //Replaces “/” by “_” (underline)
    for(int i = 0;i<size;i++) {
        if(p[i] == '+') {
            p[i] = '-';
        } else if(p[i] == '/') {
            p[i] = '_';
        }
    }

    //remove last "=="
    result->quickShrink(result->size() - 2);
    return result;
}

String _Base64::encode(String str) const {
    return _encode(str->toChars(),str->size(),false)->toString();
}
    
ByteArray _Base64::encode(ByteArray buff) const {
    return _encode((char *)buff->toValue(),buff->size(),false);
}

ByteArray _Base64::encode(ByteArray buff,int length) const {
    return _encode((char *)buff->toValue(),length,false);
}

ByteArray _Base64::decode(ByteArray buff) const {
    return _decode((char *)buff->toValue(),buff->size(),false);
}

ByteArray _Base64::encode(File f) const {
    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray result = stream->readAll();
    stream->close();
    return encode(result);
}

ByteArray _Base64::decode(File f) const {
    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray result = stream->readAll();
    stream->close();
    return decode(result);
}

ByteArray _Base64::_encode(const char * input, 
                           int length,
                           bool with_new_line) const {
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
    
    ByteArray data = createByteArray((byte *)bptr->data,bptr->length);   
    BIO_free_all(b64);
    return data;
}

ByteArray _Base64::_decode(const char * input, 
                           int length, 
                           bool with_new_line) const {
    BIO * bmem = nullptr;
    ByteArray data = createByteArray(length);
    byte *buffer = data->toValue();
  
    BIO * b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    
    int ret = BIO_read(bmem, buffer, length);
    if(bmem) {
        BIO_free_all(bmem);
    }
    data->quickShrink(ret);
    return data;
}

}