#include "HttpFile.hpp"
#include "UUID.hpp"
#include "File.hpp"
#include "Enviroment.hpp"
#include "System.hpp"

namespace obotcha {

_HttpFile::_HttpFile(String realname) {
    mRealName = realname;
    String filepath = st(Enviroment)::getInstance()->get(st(Enviroment)::gHttpMultiPartFilePath);
    UUID uuid = createUUID();
    while(1) {
        String newName = uuid->generate();
        mFile = createFile(filepath->append(newName));
        mFile->createDirs();
        if(!mFile->exists()) {
            mFile->createNewFile();
            break;
        }
    }
}

_HttpFile::_HttpFile(File file) {
    mFile = file;
    mRealName = mFile->getName();
}

_HttpFile::_HttpFile(File file,String realname) {
    mFile = file;
    mRealName = realname;
}

String _HttpFile::getRealName() {
    return mRealName;
}

String _HttpFile::getName() {
    return mFile->getName();
}

File _HttpFile::getFile() {
    return mFile;
}

}