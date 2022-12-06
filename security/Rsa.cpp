extern "C" {
    #include "openssl/pem.h"
}

#include "Rsa.hpp"
#include "Base64.hpp"
#include "RsaSecretKey.hpp"

namespace obotcha {

typedef int (*rsafunc)(int flen, const unsigned char *from, unsigned char *to,
                       RSA *rsa, int padding);

rsafunc RsaFunctions[2][2] = 
{                    /*Decrypt*/            /*Encrypt*/
/*RsaPublicKey*/   {RSA_public_decrypt,    RSA_public_encrypt   },
/*RsaPrivateKey*/  {RSA_private_decrypt,   RSA_private_encrypt  }
};

ByteArray _Rsa::decrypt(ByteArray content) {
    return doRsa(content,st(Cipher)::Decrypt);
}

ByteArray _Rsa::encrypt(ByteArray content) {
    return doRsa(content,st(Cipher)::Encrypt);
}

ByteArray _Rsa::doRsa(ByteArray inputdata,int mode /*Decrypt/Encrypt*/) {
    const RSA * key = (const RSA*)getSecretKey()->get();
    int key_len =  RSA_size(key);
    int encrypt_len = key_len;
    int paddingMode = RSA_PKCS1_PADDING;
    ByteArray out = nullptr;
    RsaSecretKey rsaKey = Cast<RsaSecretKey>(getSecretKey());
    Base64 base64 = createBase64();

    switch(getPadding()) {
        case PKCS1Padding:
            encrypt_len = key_len - 11;
            paddingMode = RSA_PKCS1_PADDING;
        break;

        case OAEPPadding:
            encrypt_len = key_len - 41;
            paddingMode = RSA_PKCS1_OAEP_PADDING;
        break;

        case PSSPadding:
            //TODO
        break;

        default:
        //TODO
        break;
    }

    //in Encrypt mode,use key length.
    if(mode == st(Cipher)::Decrypt) {
        encrypt_len = key_len;
        inputdata = base64->decode(inputdata);
    }

    int rsaKeyMode = rsaKey->getKeyType();
    rsafunc rsafunction = RsaFunctions[rsaKeyMode][mode];
    
    int inputsize = inputdata->size();
    
    if(inputsize > encrypt_len) {
        int times = inputsize/(encrypt_len); 
        char *input = (char *)inputdata->toValue();
        for(int i = 0; i < times; i++) {
            ByteArray outputdata = createByteArray(key_len);
            int encryptSize = rsafunction(encrypt_len,
                                                (unsigned char *)input,
                                                (unsigned char*)outputdata->toValue(),
                                                (RSA*)getSecretKey()->get(),
                                                paddingMode);
            input += encrypt_len;
            outputdata->quickShrink(encryptSize);
            if(out == nullptr) {
                out = outputdata;
            } else {
                out->append(outputdata);
            } 
        }
        
        int remain = inputsize%encrypt_len;
        if(remain > 0) {
            input = (char *)inputdata->toValue();
            input += times*encrypt_len;
            ByteArray outputdata = createByteArray(key_len);
            int encryptSize = rsafunction(remain,
                                                (unsigned char *)input,
                                                (unsigned char*)outputdata->toValue(),
                                                (RSA*)getSecretKey()->get(),
                                                paddingMode);
            outputdata->quickShrink(encryptSize);
            if(out == nullptr) {
                out = outputdata;
            } else {
                out->append(outputdata);
            }
        }
    } else {
        char *input = (char *)inputdata->toValue();
        ByteArray outputdata = createByteArray(key_len);
        int encryptSize = rsafunction(inputsize,
                                            (unsigned char *)input,
                                            (unsigned char*)outputdata->toValue(),
                                            (RSA*)getSecretKey()->get(),
                                            paddingMode);
        outputdata->quickShrink(encryptSize);
        out = outputdata;
    }

    //in Encrypt mode, the data should do base64 & save
    if(mode == st(Cipher)::Encrypt) {
        return base64->encode(out);
    }

    return out;
}

}
