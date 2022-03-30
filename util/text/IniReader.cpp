#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "HashMap.hpp"
#include "IniReader.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_IniReader::_IniReader(String content) {
    // TODO
}

_IniReader::_IniReader(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "parse fail \n");
    }

    filepath = file->getAbsolutePath();
}

IniValue _IniReader::parse() {
    IniValue iniValue = createIniValue();
    if (!st(File)::exists(filepath)) {
        LOG(ERROR) << "InitReader file not exsits";
        return nullptr;
    }

    if(iniValue->dict != nullptr) {
        iniparser_freedict(iniValue->dict);
    }
    
    iniValue->dict = iniparser_load(filepath->toChars());

    // reflect to HashMap
    int sections = iniparser_getnsec(iniValue->dict);
    for (int i = 0; i < sections; i++) {
        //bool isRoot = false;
        char *sectionName = (char *)iniparser_getsecname(iniValue->dict, i);
        HashMap<String, String> mKeyValue = createHashMap<String, String>();
        iniValue->mValues->put(createString(sectionName), mKeyValue);
        
        const char *keys[1024] = {0};
        auto k = iniparser_getseckeys(iniValue->dict, sectionName, keys);

        if (k == nullptr) {
            continue;
        }

        for (int j = 0; j < 1024; j++) {
            if (k[j] == nullptr) {
                break;
            }

            char *v = (char *)iniparser_getstring(iniValue->dict, k[j], "");
            //section:key
            ArrayList<String> p = createString(k[j])->split(":");
            mKeyValue->put(p->get(p->size() - 1), createString(v));
        }
    }

    return iniValue;
}

_IniReader::~_IniReader() {
    
}

} // namespace obotcha