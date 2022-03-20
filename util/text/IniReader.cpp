#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "HashMap.hpp"
#include "IniReader.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

String _IniReader::RootSectionName = createString("__root__");

_IniReader::_IniReader(String content) {
    // TODO
}

_IniReader::_IniReader(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "parse fail \n");
    }

    filepath = file->getAbsolutePath();

    mIniValues = createHashMap<String, HashMap<String, String>>();
    parse();
}

void _IniReader::parse() {
    if (!st(File)::exists(filepath)) {
        LOG(ERROR) << "InitReader file not exsits";
        return;
    }

    dict = iniparser_load(filepath->toChars());

    // reflect to HashMap
    int sections = iniparser_getnsec(dict);

    for (int i = 0; i < sections; i++) {
        //bool isRoot = false;
        char *sectionName = (char *)iniparser_getsecname(dict, i);
        HashMap<String, String> mKeyValue = createHashMap<String, String>();
        if (RootSectionName->equals(sectionName)) {
            mIniValues->put(createString(""), mKeyValue);
            //isRoot = true;
        } else {
            mIniValues->put(createString(sectionName), mKeyValue);
        }

        const char *keys[1024] = {0};
        auto k = iniparser_getseckeys(dict, sectionName, keys);

        if (k == nullptr) {
            continue;
        }

        for (int j = 0; j < 1024; j++) {
            if (k[j] == nullptr) {
                break;
            }

            char *v = (char *)iniparser_getstring(dict, k[j], "");
            ArrayList<String> p = createString(k[j])->split(":");
            mKeyValue->put(p->get(p->size() - 1), createString(v));
        }
    }
}

HashMap<String, String> _IniReader::get(String section) {
    return mIniValues->get(section);
}

HashMap<String, HashMap<String, String>> _IniReader::getAll() {
    return mIniValues;
}

_IniReader::~_IniReader() {
    if (dict != nullptr) {
        iniparser_freedict(dict);
        dict = nullptr;
    }
}

} // namespace obotcha