#ifndef __INI_VALUE_H__
#define __INI_VALUE_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

class _IniReader;

DECLARE_SIMPLE_CLASS(IniValue) {

public:

    _IniValue(int size);

    _IniValue();
    
    //no use
    //_IniValue(IniValue v);
    
    _IniValue(dictionary *dict);

    int getSectionNum();

    String getSectionName(int index);
   
    int getSectionKeyNum(String sectionName);

    String getString(String section,String tag,String defaultValue);

    int getInteger(String section,String tag,int defaultValue);

    double getDouble(String section,String tag,double defaultValue);

    bool getBoolean(String section,String tag,bool defaultValue);

    String getString(const char *section,const char* tag,String defaultValue);

    int getInteger(const char *section,const char* tag,int defaultValue);

    double getDouble(const char *section,const char* tag,double defaultValue);

    bool getBoolean(const char *section,const char* tag,bool defaultValue);

    //int set(String section,String tag,String value);

    //void remove(String section,String tag);

    bool contains(String section,String tag);

    //void save(String file);

    ~_IniValue();

private:

    dictionary * ini;

    String genKey(String section,String tag);

    String genKey(const char *section,const char *tag);

};

}


#endif