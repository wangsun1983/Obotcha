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

void _Cipher::doPKCS7Padding(ByteArray data,int blocksize) {
    byte paddingSize = (blocksize - (data->size()%blocksize));
    ByteArray padding = createByteArray((int)paddingSize);
    padding->fill(paddingSize);
    data->append(padding);
}

}
