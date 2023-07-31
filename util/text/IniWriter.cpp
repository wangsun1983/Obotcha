#include "IniWriter.hpp"
#include "Log.hpp"

namespace obotcha {

_IniWriter::_IniWriter(File f):mFile(f) {
}

_IniWriter::_IniWriter(String path):mFile(createFile(path)) {
}

int _IniWriter::write(IniValue ini) {
    if(ini->dict == nullptr) {
        return -1;
    }

    if(!mFile->exists()) {
        mFile->createNewFile();
    }

    FILE * pFile = fopen(mFile->getAbsolutePath()->toChars(),"w");
    if(pFile != nullptr) {
        iniparser_dump_ini(ini->dict,pFile);
        fclose(pFile);
    } else {
        LOG(ERROR)<<"IniWriter open file failed,path is "<<mFile->getAbsolutePath()->toChars();
    }
    return 0;
}


} // namespace obotcha
