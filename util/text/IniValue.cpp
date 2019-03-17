#include "IniValue.hpp"

namespace obotcha {

 _IniValue::_IniValue(int size) {
    ini = dictionary_new(size);
 }

 _IniValue::_IniValue() {
    ini = dictionary_new(256);
 }

 _IniValue::_IniValue(dictionary *dict) {
    ini = dict;
 }

_IniValue::_IniValue(IniValue v) {
    //TODO
}

int _IniValue::getSectionNum() {
    if(ini != nullptr) {
        return iniparser_getnsec(ini);
    }
    
    return -1;
}

String _IniValue::getSectionName(int index) {
    char *p = (char *)iniparser_getsecname(ini,index);
    return createString(p);
}
   
int _IniValue::getSectionKeyNum(String sectionName) {
    return iniparser_getsecnkeys(ini,sectionName->toChars());
}

String _IniValue::getString(String section,String tag,String defaultValue) {
    String key = genKey(section,tag);

    char *p = (char *)iniparser_getstring(ini,key->toChars(),defaultValue->toChars());
    return createString(p);
}

int _IniValue::getInteger(String section,String tag,int defaultValue) {
    String key = genKey(section,tag);

    return iniparser_getint(ini,key->toChars(),defaultValue);
}

double _IniValue::getDouble(String section,String tag,double defaultValue) {
    String key = genKey(section,tag);

    return iniparser_getdouble(ini,key->toChars(),defaultValue);
}

bool _IniValue::getBoolean(String section,String tag,bool defaultValue) {
    String key = genKey(section,tag);

    return iniparser_getboolean(ini,key->toChars(),defaultValue);
}

String _IniValue::getString(const char* section,const char* tag,String defaultValue) {
    String key = genKey(section,tag);

    char *p = (char *)iniparser_getstring(ini,key->toChars(),defaultValue->toChars());
    return createString(p);
}

int _IniValue::getInteger(const char* section,const char* tag,int defaultValue) {
    String key = genKey(section,tag);

    return iniparser_getint(ini,key->toChars(),defaultValue);
}

double _IniValue::getDouble(const char* section,const char* tag,double defaultValue) {
    String key = genKey(section,tag);

    return iniparser_getdouble(ini,key->toChars(),defaultValue);
}

bool _IniValue::getBoolean(const char* section,const char* tag,bool defaultValue) {
    String key = genKey(section,tag);

    return iniparser_getboolean(ini,key->toChars(),defaultValue);
}

int _IniValue::set(String section,String tag,String value) {
    String key = genKey(section,tag);

    return iniparser_set(ini,key->toChars(),value->toChars());
}

void _IniValue::remove(String section,String tag) {
    String key = genKey(section,tag);

    iniparser_unset(ini,key->toChars());
}

bool _IniValue::contains(String section,String tag) {
    section->append(":");
    section->append(tag);

    return iniparser_find_entry(ini,tag->toChars());
}

_IniValue::~_IniValue() {
    iniparser_freedict(ini);
}

String _IniValue::genKey(String section,String tag) {
    String content = createString("");

    if(section != nullptr) {
        content = section;
    }

    content->append(":");
    content->append(tag);

    return content;
}
    
String _IniValue::genKey(const char *section,const char *tag) {
    String content = createString("");

    if(section != nullptr) {
        content = createString(section);
    }

    content->append(":");
    content->append(tag);

    return content;
}

}