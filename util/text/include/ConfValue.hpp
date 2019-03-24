#ifndef __CONF_VALUE_H__
#define __CONF_VALUE_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"
#include "File.hpp"
#include "rapidxml.hpp"
#include "XmlValue.hpp"

extern "C" {
    #include "ccl.h"
}

namespace obotcha {

class _ConfReader;
class _ConfIterator;

DECLARE_SIMPLE_CLASS(ConfValue) {

public:
    friend class _ConfReader;
    friend class _ConfIterator;

    _ConfValue();

    ~_ConfValue();
   
    sp<_ConfIterator> getIterator();

    String getValue(String tag);

private:
    struct ccl_t config;
};

DECLARE_SIMPLE_CLASS(ConfIterator) {
public:
    _ConfIterator(_ConfValue *);
    
    _ConfIterator(ConfValue v);

    String getTag();
    
    String getValue();

    bool hasValue();
    
    bool next();

//while((iter = ccl_iterate(&config))!=0){printf("%s=%s\n", iter->key, iter->value);}
private:
    ConfValue value;
    struct ccl_pair_t* iterator;
};


}

#endif