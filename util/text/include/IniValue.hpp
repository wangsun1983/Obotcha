#ifndef __OBOTCHA_INI_VALUE_H__
#define __OBOTCHA_INI_VALUE_H__

#include "iniparser.h"

#include "File.hpp"
#include "HashMap.hpp"
#include "Object.hpp"

namespace obotcha {

class _IniReader;
class _IniWriter;

DECLARE_CLASS(IniValue) {
public:
    friend class _IniReader;
    friend class _IniWriter;

    _IniValue();
    
    void reflectTo(Object obj);
    void importFrom(Object);

    void set(String section,String key,String value);
    void set(String key,String value);

    String get(String section,String key);
    String get(String key);

    HashMap<String,String> getSection(String section);
    HashMap<String,HashMap<String,String>> getAll();

    ~_IniValue() override;

    void init();

    static String RootSection;

private:
    dictionary *dict;
    
    HashMap<String, HashMap<String, String>> mValues;
    
    void importFrom(Object obj,String section);
    void reflectWithObject(Object,HashMap<String,String>) const;
};

} // namespace obotcha

#endif