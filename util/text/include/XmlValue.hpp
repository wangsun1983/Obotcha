#ifndef __XML_VALUE_H__
#define __XML_VALUE_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

#include "rapidxml.hpp"
using namespace rapidxml;

namespace obotcha {

class _XmlReader;

DECLARE_SIMPLE_CLASS(XmlValue) {

public:
    friend class _XmlReader;

    _XmlValue(xml_node<> *n);

private:
    void setParser(sp<_XmlReader> r);

    sp<_XmlReader> reader; //

    xml_node<>*  node; 
};

}


#endif