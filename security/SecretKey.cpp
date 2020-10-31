#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "SecretKey.hpp"

namespace obotcha {

_SecretKey::_SecretKey() {
    mSecretContent = nullptr;
    mSecretFile = nullptr;
}

File _SecretKey::getFile() {
    return mSecretFile;
}

ByteArray _SecretKey::getContent() {
    return mSecretContent;
}


}

