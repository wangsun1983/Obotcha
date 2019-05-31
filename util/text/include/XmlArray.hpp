#ifndef __XML_ARRAY_H__
#define __XML_ARRAY_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

#include "rapidxml.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlReader;
class _XmlValue;

DECLARE_SIMPLE_CLASS(XmlArray) {

public:
    friend class _XmlReader;

    _XmlValue(xml_node<> *n);

    String getStringAttr(String attr);

    Integer getIntegerAttr(String attr);

    Boolean getBooleanAttr(String attr);

    Double getDoubleAttr(String attr);

    Float getFloatAttr(String attr);

    String getStringValue(int index);

    Integer getIntegerValue(int index);

    Boolean getBooleanValue(int index);

    Double getDoubleValue(int index);

    Float getFloatValue(int index);

    sp<_XmlValue> getValue(int index);

    String getName();

private:
    void setParser(sp<_XmlReader> r);

    sp<_XmlReader> reader; //

    xml_node<>*  node; 
};

}


#endif