extern "C" {
    #include "openssl/crypto.h"
}

#include "Cipher.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "Log.hpp"

namespace obotcha {

const String _Cipher::ZeroPadingStr = String::New("ZeroPading");
const String _Cipher::PKCS7PaddingStr = String::New("PKCS7Padding");
const String _Cipher::PKCS5PaddingStr = String::New("PKCS5Padding");
const String _Cipher::PKCS1PaddingStr = String::New("PKCS1Padding");
const String _Cipher::PKCS8PaddingStr = String::New("PKCS8Padding");
const String _Cipher::OAEPPaddingStr = String::New("OEAPPadding");
const String _Cipher::PSSPaddingStr = String::New("PSSPadding");

const String _Cipher::AesStr = String::New("AES");
const String _Cipher::Aes128Str = String::New("AES128");
const String _Cipher::Aes192Str = String::New("AES192");
const String _Cipher::Aes256Str = String::New("AES256");

const String _Cipher::DesStr = String::New("DES");
const String _Cipher::RsaStr = String::New("RSA");
const String _Cipher::Rsa3Str = String::New("RSA3");
const String _Cipher::Rsaf4Str = String::New("RSAF4");

const String _Cipher::CbcStr = String::New("CBC");
const String _Cipher::EcbStr = String::New("ECB");
const String _Cipher::CtrStr = String::New("CTR");
const String _Cipher::OcfStr = String::New("OCF");
const String _Cipher::Cfb1Str = String::New("CFB1");
const String _Cipher::Cfb8Str = String::New("CFB8");
const String _Cipher::Cfb128Str = String::New("CFB128");
const String _Cipher::Ofb128Str = String::New("OFB128");

// int _Cipher::getAlgorithm() const {
//     return algorithmType;
// }

_Cipher::Pattern _Cipher::getPattern() const {
    return patternType;
}

_Cipher::Padding _Cipher::getPadding() const {
    return paddingType;
}

// void _Cipher::setAlgorithm(int v) {
//     algorithmType = v;
// }

void _Cipher::setPattern(_Cipher::Pattern v) {
    patternType = v;
}

void _Cipher::setPadding(_Cipher::Padding v) {
    paddingType = v;
}

_Cipher::Mode _Cipher::getMode() const {
    return mMode;
}

void _Cipher::init(_Cipher::Mode mode,SecretKey key) {
    mMode = mode;
    mKey = key;
}

void _Cipher::encryptFile(File in,File out) {
    doEncryptOrDescrypt(in,out);
}

void _Cipher::decryptFile(File in,File out) {
    doEncryptOrDescrypt(in,out);
}

void _Cipher::doPadding(ByteArray data,int blocksize) const {
    switch(paddingType) {
        case _Cipher::Padding::Zero:
            doPKCSZeroPadding(data,blocksize);
        break;

        case _Cipher::Padding::PKCS7:
            doPKCS7Padding(data,blocksize);
        break;

        case _Cipher::Padding::PKCS5:
            doPKCS5Padding(data);
        break;

        default:
            //PKCS1Padding or PKCS8Padding or unSupport
            LOG(ERROR)<<"Cipher doPadding unknow or not support,paddingType:"<<static_cast<int>(paddingType);
        break;    
    }
}

void _Cipher::doUnPadding(ByteArray data) const {
    switch(paddingType) {
        case Padding::Zero:
            doPKCSZeroUnPadding(data);
        break;

        case Padding::PKCS7:
            doPKCS7UnPadding(data);
        break;

        case Padding::PKCS5:
            doPKCS5UnPadding(data);
        break;

        default:
            //PKCS1Padding or PKCS8Padding or unSupport
            LOG(ERROR)<<"Cipher doUnPadding unknow or not support,paddingType:"<<static_cast<int>(paddingType);
        break;    
    }
}


SecretKey _Cipher::getSecretKey() {
    return mKey;
}

void _Cipher::doPKCS7Padding(ByteArray data,int blocksize) const {
    int paddingSize = (blocksize - (data->size()%blocksize));
    if(paddingSize == 0) {
        paddingSize = blocksize;
    }
    
    ByteArray padding = ByteArray::New(paddingSize);
    padding->fill(static_cast<byte>(paddingSize));
    data->append(padding);
}

void _Cipher::doPKCS5Padding(ByteArray data) const {
    doPKCS7Padding(data,8);
}

void _Cipher::doPKCSZeroPadding(ByteArray data,int blocksize) const {
    int paddingSize = (blocksize - (data->size()%blocksize));
    if(paddingSize != blocksize) {
        ByteArray padding = ByteArray::New(paddingSize);
        padding->fill(0);
        data->append(padding);
    }
}

void _Cipher::doPKCS7UnPadding(ByteArray data) const {
    int paddingsize = data->at(data->size() - 1);
    data->quickShrink(data->size() - paddingsize);
}

void _Cipher::doPKCS5UnPadding(ByteArray data) const {
    doPKCS7UnPadding(data);
}

void _Cipher::doPKCSZeroUnPadding(ByteArray data) const {
    size_t index = data->size() - 1;
    for(;index > 0;index--) {
        if(data->at(index) != 0) {
            break;
        }
    }

    data->quickShrink(index + 1);
}


void _Cipher::doEncryptOrDescrypt(File in,File out) {
    if(!out->exists()) {
        out->createNewFile();
    }
  
    FileInputStream inputStream = FileInputStream::New(in);
    inputStream->open();
    if(ByteArray inputData = inputStream->readAll();inputData != nullptr) {
        FileOutputStream outputStream = FileOutputStream::New(out);
        ByteArray outputData = nullptr;
        
        switch(getMode()) {
            case Mode::Decrypt: {
                outputData = decryptContent(inputData);
            } break;

            case Mode::Encrypt: {
                outputData = encryptContent(inputData);
            } break;

            default:
                LOG(ERROR)<<"Cipher doEncryptOrDescrypt unknow mode:"<<static_cast<int>(getMode());
            break;
        }

        if(outputData != nullptr) {
            outputStream->open();
            outputStream->write(outputData);
            outputStream->flush();
            outputStream->close();
        }
    }

    inputStream->close();
}

}
