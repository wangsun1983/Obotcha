#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "Cipher.hpp"

namespace obotcha {

const String _Cipher::ZeroPadingStr = createString("ZeroPading");
const String _Cipher::PKCS7PaddingStr = createString("PKCS7Padding");
const String _Cipher::PKCS5PaddingStr = createString("PKCS5Padding");
const String _Cipher::PKCS1PaddingStr = createString("PKCS1Padding");
const String _Cipher::PKCS8PaddingStr = createString("PKCS8Padding");

const String _Cipher::AesStr = createString("AES");
const String _Cipher::DesStr = createString("DES");
const String _Cipher::RsaStr = createString("RSA");

const String _Cipher::CbcStr = createString("CBC");
const String _Cipher::EcbStr = createString("ECB");
const String _Cipher::CtrStr = createString("CTR");
const String _Cipher::OcfStr = createString("OCF");
const String _Cipher::CfbStr = createString("CFB");

int _Cipher::getAlgorithm() {
    return algorithmType;
}

int _Cipher::getPattern() {
    return patternType;
}

int _Cipher::getPadding() {
    return paddingType;
}

void _Cipher::setAlgorithm(int v) {
    algorithmType = v;
}

void _Cipher::setPattern(int v) {
    patternType = v;
}

void _Cipher::setPadding(int v) {
    paddingType = v;
}

int _Cipher::getMode() {
    return mMode;
}

void _Cipher::init(int mode,SecretKey key) {
    mMode = mode;
    mKey = key;
}

void _Cipher::doPadding(ByteArray data,int blocksize) {
    switch(paddingType) {
        case ZeroPadding:
            doPKCSZeroPadding(data,blocksize);
        break;

        case PKCS7Padding:
            doPKCS7Padding(data,blocksize);
        break;

        case PKCS5Padding:
            doPKCS5Padding(data);
        break;

        case PKCS1Padding:
            //TODO
        break;

        case PKCS8Padding:
            //TODO
        break;    
    }
}

void _Cipher::doUnPadding(ByteArray data) {
    switch(paddingType) {
        case ZeroPadding:
            doPKCSZeroUnPadding(data);
        break;

        case PKCS7Padding:
            doPKCS7UnPadding(data);
        break;

        case PKCS5Padding:
            doPKCS5UnPadding(data);
        break;

        case PKCS1Padding:
            //TODO
        break;

        case PKCS8Padding:
            //TODO
        break;    
    }
}

void _Cipher::doPKCS7Padding(ByteArray data,int blocksize) {
    byte paddingSize = (blocksize - (data->size()%blocksize));
    ByteArray padding = createByteArray((int)paddingSize);
    padding->fill(paddingSize);
    data->append(padding);
}

void _Cipher::doPKCS5Padding(ByteArray data) {
    doPKCS7Padding(data,8);
}

void _Cipher::doPKCSZeroPadding(ByteArray data,int blocksize) {
    byte paddingSize = (blocksize - (data->size()%blocksize));
    if(paddingSize != blocksize) {
        ByteArray padding = createByteArray((int)paddingSize);
        padding->fill(0);
        data->append(padding);
    }
}

void _Cipher::doPKCS7UnPadding(ByteArray data) {
    int paddingsize = data->at(data->size() - 1);
    data->quickShrink(data->size() - paddingsize);
}

void _Cipher::doPKCS5UnPadding(ByteArray data) {
    int paddingsize = data->at(data->size() - 1);
    data->quickShrink(data->size() - paddingsize);
}

void _Cipher::doPKCSZeroUnPadding(ByteArray data) {
    int index = data->size() - 1;
    for(;index > 0;index--) {
        if(data->at(index) != 0) {
            break;
        }
    }

    data->quickShrink(index);
}

}