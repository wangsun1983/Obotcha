#include <stdio.h>
#include <stdlib.h>

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
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section->toChars(),tag->toChars(),buff,ConvertBuffSize);
    char *p = (char *)iniparser_getstring(ini,buff,defaultValue->toChars());
    return createString(p);
}

String _IniValue::getString(String tag,String defaultValue) {
    return getString(tag->toChars(),defaultValue->toChars());
}

int _IniValue::getInteger(String section,String tag,int defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section->toChars(),tag->toChars(),buff,ConvertBuffSize);
    return iniparser_getint(ini,buff,defaultValue);
}

int _IniValue::getInteger(String tag,int defaultValue) {
    return getInteger(tag->toChars(),defaultValue);
}

double _IniValue::getDouble(String section,String tag,double defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section->toChars(),tag->toChars(),buff,ConvertBuffSize);

    return iniparser_getdouble(ini,buff,defaultValue);
}

double _IniValue::getDouble(String tag,double defaultValue) {
    return getDouble(tag->toChars(),defaultValue);
}

bool _IniValue::getBoolean(String section,String tag,bool defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section->toChars(),tag->toChars(),buff,ConvertBuffSize);

    return iniparser_getboolean(ini,buff,defaultValue);
}

bool _IniValue::getBoolean(String tag,bool defaultValue) {
    return getBoolean(tag->toChars(),defaultValue);
}

String _IniValue::getString(const char* section,const char* tag,const char * defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section,tag,buff,ConvertBuffSize);
    char *p = (char *)iniparser_getstring(ini,buff,defaultValue);
    return createString(p);
}

String _IniValue::getString(const char* tag,const char* defaultValue) {
    String v = searchStringValue(tag);
    if(v == nullptr) {
        return createString(defaultValue);
    }

    return v;
}

int _IniValue::getInteger(const char* section,const char* tag,int defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section,tag,buff,ConvertBuffSize);
    return iniparser_getint(ini,buff,defaultValue);
}

int _IniValue::getInteger(const char* tag,int defaultValue) {
    Integer v = searchIntValue(tag);
    if(v == nullptr) {
        return defaultValue;
    }

    return v->toValue();
}

double _IniValue::getDouble(const char* section,const char* tag,double defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section,tag,buff,ConvertBuffSize);
    return iniparser_getdouble(ini,buff,defaultValue);
}

double _IniValue::getDouble(const char* tag,double defaultValue) {
    Double v = searchDoubleValue(tag);
    if(v == nullptr) {
        return defaultValue;
    }

    return v->toValue();
}

bool _IniValue::getBoolean(const char* section,const char* tag,bool defaultValue) {
    //String key = genKey(section,tag);
    char buff[ConvertBuffSize] = {0};
    getKey(section,tag,buff,ConvertBuffSize);
    return iniparser_getboolean(ini,buff,defaultValue);
}

bool _IniValue::getBoolean(const char* tag,bool defaultValue) {
    Boolean v = searchBooleanValue(tag);
    if(v == nullptr) {
        return defaultValue;
    }

    return v->toValue();
}

bool _IniValue::contains(String section,String tag) {
    //String key = genKey(section,tag);
    return contains(section->toChars(),tag->toChars());
}

bool _IniValue::contains(const char *section,const char *tag) {
    char buff[ConvertBuffSize] = {0};
    getKey(section,tag,buff,ConvertBuffSize);
    int ret = iniparser_find_entry(ini,buff);
    return (1 == ret);
}

_IniValue::~_IniValue() {
    iniparser_freedict(ini);
}

void _IniValue::getKey(const char *section,const char *tag,char *buff,int length) {
    snprintf(buff,length,"%s:%s",section,tag);
}

Integer _IniValue::searchIntValue(const char *tag) {
    //check whether exist values with no section
    if(contains("",tag)) {
        return createInteger(getInteger("",tag,1));
    }

    int sections = iniparser_getnsec(ini);
    
    for(int i = 0;i<sections;i++) {
        char *sectionName = (char *)iniparser_getsecname(ini,i);

        if(contains(sectionName,tag)){
            return createInteger(getInteger(sectionName,tag,1));
        }
    }

    return nullptr;
}

Boolean _IniValue::searchBooleanValue(const char *tag) {
    //check whether exist values with no section
    if(contains("",tag)) {
        return createBoolean(getBoolean("",tag,false));
    }
    
    int sections = iniparser_getnsec(ini);
    
    for(int i = 0;i<sections;i++) {
        char *sectionName = (char *)iniparser_getsecname(ini,i);
        if(contains(sectionName,tag)){
            return createBoolean(getBoolean(sectionName,tag,false));
        }
    }

    return nullptr;
}

Double _IniValue::searchDoubleValue(const char *tag) {
    //check whether exist values with no section
    if(contains("",tag)) {
        return createDouble(getDouble("",tag,1.0));
    }
    
    int sections = iniparser_getnsec(ini);
    
    for(int i = 0;i<sections;i++) {
        char *sectionName = (char *)iniparser_getsecname(ini,i);
        if(contains(sectionName,tag)){
            return createDouble(getDouble(sectionName,tag,1.0));
        }
    }

    return nullptr;
}

String _IniValue::searchStringValue(const char *tag) {
    //check whether exist values with no section
    if(contains("",tag)) {
        return getString("",tag,"");
    }
    
    int sections = iniparser_getnsec(ini);
    
    for(int i = 0;i<sections;i++) {
        char *sectionName = (char *)iniparser_getsecname(ini,i);
        if(contains(sectionName,tag)){
            return getString(sectionName,tag,"");
        }
    }

    return nullptr;
}


}