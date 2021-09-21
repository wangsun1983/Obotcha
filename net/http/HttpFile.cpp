#include "HttpFile.hpp"
#include "Enviroment.hpp"
#include "File.hpp"
#include "System.hpp"
#include "UUID.hpp"

namespace obotcha {

_HttpFile::_HttpFile(String realname) {
    mRealName = realname;
    String filepath = st(Enviroment)::getInstance()->get(
        st(Enviroment)::gHttpMultiPartFilePath);

    File dir = createFile(filepath);
    if (!dir->exists()) {
        dir->createDir();
    }

    UUID uuid = createUUID();
    while (1) {
        String newName = uuid->generate();
        mFile = createFile(filepath->append(newName));

        if (!mFile->exists()) {
            mFile->createNewFile();
            break;
        }
    }
}

_HttpFile::_HttpFile(File file) {
    mFile = file;
    mRealName = mFile->getName();
}

String _HttpFile::getAbsolutePath() { return mFile->getAbsolutePath(); }

_HttpFile::_HttpFile(File file, String realname) {
    mFile = file;
    mRealName = realname;
}

String _HttpFile::getRealName() { return mRealName; }

String _HttpFile::getName() { return mFile->getName(); }

File _HttpFile::getFile() { return mFile; }

} // namespace obotcha