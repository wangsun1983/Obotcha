#include "IniWriter.hpp"
#include "Log.hpp"

namespace obotcha {

_IniWriter::_IniWriter(File f):mFile(f) {
}

_IniWriter::_IniWriter(String path):mFile(File::New(path)) {
}

int _IniWriter::write(IniValue ini) const {
    if(ini->dict == nullptr) {
        return -1;
    }

    if(!mFile->exists()) {
        mFile->createNewFile();
    }

    if(FILE * pFile = fopen(mFile->getAbsolutePath()->toChars(),"w");
        pFile != nullptr) {
        iniparser_dump_ini(ini->dict,pFile);
        fclose(pFile);
        return 0;
    } 
    
    LOG(ERROR)<<"IniWriter open file failed,path is "<<mFile->getAbsolutePath()->toChars();
    return -1;
}


} // namespace obotcha
