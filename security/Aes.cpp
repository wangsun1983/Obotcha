extern "C" {
    #include "openssl/aes.h"
}

#include "Aes.hpp"
#include "ByteArray.hpp"
#include "Log.hpp"
#include "IllegalStateException.hpp"
#include "Cipher.hpp"

namespace obotcha {

ByteArray _Aes::encryptContent(ByteArray buff) {
    if(getMode() != st(Cipher)::Mode::Encrypt) {
        Trigger(IllegalStateException,"do encrypt,but mode is decrypt")
    }

    switch(getPattern()) {
        case st(Cipher)::Pattern::ECB:
            return _aesECB(buff);

        case st(Cipher)::Pattern::CBC:
            return _aesCBC(buff);

        case st(Cipher)::Pattern::CFB1:
            return _aesCFB1(buff);
        
        case st(Cipher)::Pattern::CFB8:
            return _aesCFB8(buff);
        
        case st(Cipher)::Pattern::CFB128:
            return _aesCFB128(buff);

        case st(Cipher)::Pattern::OFB128:
            return _aesOFB128(buff);

        default:
            LOG(ERROR)<<"Aes encryptContent unknow pattern:"<<static_cast<int>(getPattern());
            return nullptr;
    }
}

ByteArray _Aes::decryptContent(ByteArray buff) {
    if(getMode() != st(Cipher)::Mode::Decrypt) {
        Trigger(IllegalStateException,"do decrypt,but mode is encrypt")
    }

    switch(getPattern()) {
        case st(Cipher)::Pattern::ECB:
            return _aesECB(buff);

        case st(Cipher)::Pattern::CBC:
            return _aesCBC(buff);

        case st(Cipher)::Pattern::CFB1:
            return _aesCFB1(buff);
        
        case st(Cipher)::Pattern::CFB8:
            return _aesCFB8(buff);
        
        case st(Cipher)::Pattern::CFB128:
            return _aesCFB128(buff);

        case st(Cipher)::Pattern::OFB128:
            return _aesOFB128(buff);
        
        default:
            LOG(ERROR)<<"Aes decryptContent unknow pattern:"<<static_cast<int>(getPattern());
            return nullptr;
    }
}

ByteArray _Aes::_aesECB(ByteArray data) {
    int type = AES_DECRYPT;

    if(getMode() == st(Cipher)::Mode::Encrypt) {
        doPadding(data,AES_BLOCK_SIZE);
        type = AES_ENCRYPT;
    }
    
    ByteArray out = createByteArray(data->size());
    auto output = out->toValue();
    auto input = data->toValue();
    size_t length = data->size();
    
    for(size_t i = 0; i < length/AES_BLOCK_SIZE; i++) {
        AES_ecb_encrypt(input,
                        output,
                        std::any_cast<AES_KEY *>(getSecretKey()->get()),
                        type);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
    }

    if(getMode() == st(Cipher)::Mode::Decrypt) {
        doUnPadding(out);
    }
 
    return out;
}

ByteArray _Aes::_aesCBC(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int type = AES_DECRYPT;

    if(getMode() == st(Cipher)::Mode::Encrypt) {
        doPadding(data,AES_BLOCK_SIZE);
        type = AES_ENCRYPT;
    }

    ByteArray out = createByteArray(data->size());
    auto output = out->toValue();
    auto input = data->toValue();

    size_t length = data->size();
    AES_cbc_encrypt(input,
                    output,
                    length,
                    std::any_cast<AES_KEY *>(getSecretKey()->get()),
                    ivec,
                    type);
    
    if(getMode() == st(Cipher)::Mode::Decrypt) {
        doUnPadding(out);
    }

    return out;
}

ByteArray _Aes::_aesCFB1(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };    
    int type = (getMode() == st(Cipher)::Mode::Encrypt)?AES_ENCRYPT:AES_DECRYPT;

    ByteArray out = createByteArray(data->size());
    auto output = out->toValue();
    auto input = data->toValue();
    size_t length = data->size();
    int num = 0;

    AES_cfb1_encrypt(input,
                    output,
                    length*8,
                    std::any_cast<AES_KEY *>(getSecretKey()->get()),
                    ivec,
                    &num,
                    type);

    return out;
}

ByteArray _Aes::_aesCFB8(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    int type = (getMode() == st(Cipher)::Mode::Encrypt)?AES_ENCRYPT:AES_DECRYPT;
    
    ByteArray out = createByteArray(data->size());
    auto output = out->toValue();
    auto input = data->toValue();
    size_t length = data->size();
    int num = 0;

    AES_cfb8_encrypt(input,
                    output,
                    length,
                    std::any_cast<AES_KEY *>(getSecretKey()->get()),
                    ivec,
                    &num,
                    type);
                    
    return out;
}

ByteArray _Aes::_aesCFB128(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int type = (getMode() == st(Cipher)::Mode::Encrypt)?AES_ENCRYPT:AES_DECRYPT;
    
    ByteArray out = createByteArray(data->size());
    auto output = out->toValue();
    auto input = data->toValue();
    size_t length = data->size();
    int num = 0;

    AES_cfb128_encrypt(input,
                       output,
                        length,
                        std::any_cast<AES_KEY *>(getSecretKey()->get()),
                        ivec,
                        &num,
                        type);

    return out;
}

ByteArray _Aes::_aesOFB128(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ByteArray out = createByteArray(data->size());
    auto output = out->toValue();
    auto input = data->toValue();
    size_t length = data->size();
    int num = 0;
    
    AES_ofb128_encrypt(input,
                       output,
                       length,
                       std::any_cast<AES_KEY *>(getSecretKey()->get()),
                       ivec,
                       &num);
    return out;
}

}
