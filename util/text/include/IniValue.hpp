#ifndef __OBOTCHA_INI_VALUE_H__
#define __OBOTCHA_INI_VALUE_H__

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
    
    _IniValue(dictionary *dict);

    int getSectionNum();

    String getSectionName(int index);
   
    int getSectionKeyNum(String sectionName);

    String getString(String section,String tag,String defaultValue);

    String getString(String tag,String defaultValue);

    int getInteger(String section,String tag,int defaultValue);

    int getInteger(String tag,int defaultValue);

    double getDouble(String section,String tag,double defaultValue);

    double getDouble(String tag,double defaultValue);

    bool getBoolean(String section,String tag,bool defaultValue);

    bool getBoolean(String tag,bool defaultValue);

    String getString(const char *section,const char* tag,const char* defaultValue);

    String getString(const char* tag,const char* defaultValue);

    int getInteger(const char *section,const char* tag,int defaultValue);

    int getInteger(const char* tag,int defaultValue);

    double getDouble(const char *section,const char* tag,double defaultValue);

    double getDouble(const char* tag,double defaultValue);

    bool getBoolean(const char *section,const char* tag,bool defaultValue);

    bool getBoolean(const char* tag,bool defaultValue);

    bool contains(String section,String tag);

    bool contains(const char *section,const char *tag);

    ~_IniValue();

private:

    dictionary * ini;
    
    void getKey(const char *section,const char *tag,char *buff,int size);

    Integer searchIntValue(const char *tag);

    Boolean searchBooleanValue(const char *tag);

    Double searchDoubleValue(const char *tag);

    String searchStringValue(const char *tag);

    static const int ConvertBuffSize = 1024;
};

}


#endif