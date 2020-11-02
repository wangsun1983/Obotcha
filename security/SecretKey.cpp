#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "SecretKey.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

_SecretKey::_SecretKey() {
    mSecretContent = nullptr;
    mSecretFile = nullptr;
}

File _SecretKey::getFile() {
    return mSecretFile;
}

ByteArray _SecretKey::getContent() {
    //printf("get content \n");
    if(mSecretContent != nullptr) {
        //printf("get content trace1 \n");
        return mSecretContent;
    }
    
    if(mSecretFile != nullptr && mSecretFile->exists()) {
        //printf("get content trace2 \n");
        FileInputStream stream = createFileInputStream(mSecretFile);
        stream->open();
        mSecretContent = stream->readAll();
        if(mSecretContent == nullptr) {
            printf("it is nullptr \n");
        }
        stream->close();
    }
    //printf("get content trace3 \n");
    return mSecretContent;
}

void _SecretKey::setFile(File f) {
    this->mSecretFile = f;
}
    
void _SecretKey::setContent(ByteArray c) {
    this->mSecretContent = c;
}


}

