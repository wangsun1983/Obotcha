extern "C" {
    #include "openssl/pem.h"
    #include "openssl/err.h"
}

#include "Rsa.hpp"
#include "Base64.hpp"
#include "RsaSecretKey.hpp"
#include "CipherDebug.hpp"
#include "PaddingNotSupportException.hpp"

namespace obotcha {

using RsaFunc = int (*)(int flen, const unsigned char *from, unsigned char *to,
                       RSA *rsa, int padding);

const RsaFunc RsaFunctions[2][2] = 
{                    /*Decrypt*/            /*Encrypt*/
/*RsaPublicKey*/   {RSA_public_decrypt,    RSA_public_encrypt   },
/*RsaPrivateKey*/  {RSA_private_decrypt,   RSA_private_encrypt  }
};

ByteArray _Rsa::decryptContent(ByteArray content) {
    return doRsa(content,st(Cipher)::Mode::Decrypt);
}

ByteArray _Rsa::encryptContent(ByteArray content) {
    return doRsa(content,st(Cipher)::Mode::Encrypt);
}

ByteArray _Rsa::doRsa(ByteArray inputdata,st(Cipher)::Mode mode /*Decrypt/Encrypt*/) {
    const RSA * key = std::any_cast<RSA*>(getSecretKey()->get());
    int key_len =  RSA_size(key);
    int encrypt_len = 0;
    int paddingMode = RSA_PKCS1_PADDING;
    ByteArray out = nullptr;
    RsaSecretKey rsaKey = Cast<RsaSecretKey>(getSecretKey());
    Base64 base64 = createBase64();

    switch(getPadding()) {
        case st(Cipher)::Padding::PKCS1:
            encrypt_len = key_len - 11;
            paddingMode = RSA_PKCS1_PADDING;
        break;

        case st(Cipher)::Padding::OAEP:
            encrypt_len = key_len - 42; //minus size must larger than 41
            paddingMode = RSA_PKCS1_OAEP_PADDING;
        break;

        case st(Cipher)::Padding::PSS:
            Trigger(PaddingNotSupportException,"do not support PSSPadding")

        default:
            Trigger(PaddingNotSupportException,"unknow padding type")
    }

    //in Encrypt mode,use key length.
    if(mode == st(Cipher)::Mode::Decrypt) {
        encrypt_len = key_len;
        inputdata = base64->decode(inputdata);
    }

    int rsaKeyMode = rsaKey->getKeyType();
    RsaFunc rsafunction = RsaFunctions[rsaKeyMode][static_cast<int>(mode)];
    
    if(auto inputsize = inputdata->size();inputsize > encrypt_len) {
        int times = inputsize/encrypt_len;
        byte *input = inputdata->toValue();
        ByteArray outputdata = createByteArray(key_len);
        for(int i = 0; i < times; i++) {
            int encryptSize = rsafunction(encrypt_len,
                                                input,
                                                outputdata->toValue(),
                                                std::any_cast<RSA*>(getSecretKey()->get()),
                                                paddingMode);
            if(encryptSize < 0) {
                st(CipherDebug)::dumpSSLError();
            }
            input += encrypt_len;
            outputdata->quickShrink(encryptSize);

            if(out == nullptr) {
                out = outputdata;
                outputdata = createByteArray(key_len);
            } else {
                out->append(outputdata);
            }
            outputdata->quickRestore();
        }
        
        int remain = inputsize%encrypt_len;
        if(remain > 0) {
            input = inputdata->toValue();
            input += times*encrypt_len;
            ByteArray remaindata = createByteArray(key_len);
            int encryptSize = rsafunction(remain,
                                          input,
                                          remaindata->toValue(),
                                          std::any_cast<RSA*>(getSecretKey()->get()),
                                          paddingMode);
            remaindata->quickShrink(encryptSize);
            if(out == nullptr) {
                out = remaindata;
            } else {
                out->append(remaindata);
            }
        }
    } else {
        byte *input = inputdata->toValue();
        ByteArray outputdata = createByteArray(key_len);
        int encryptSize = rsafunction(inputsize,
                                      input,
                                      outputdata->toValue(),
                                      std::any_cast<RSA*>(getSecretKey()->get()),
                                      paddingMode);
        outputdata->quickShrink(encryptSize);
        out = outputdata;
    }

    //in Encrypt mode, the data should do base64 & save
    if(mode == st(Cipher)::Mode::Encrypt) {
        return base64->encode(out);
    }

    return out;
}

}
