#ifndef __XML_VALUE_H__
#define __XML_VALUE_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

#include "rapidxml.hpp"


using namespace rapidxml;

namespace obotcha {

class _XmlReader;
class _XmlValue;
class _XmlAttribute;
class _XmlDocument;
class _XmlWriter;

DECLARE_SIMPLE_CLASS(XmlAttrIterator) {
public:
    _XmlAttrIterator(_XmlValue *,sp<_XmlDocument> r);

    bool hasValue();

    bool next();

    sp<_XmlAttribute> getAttribute();

private:
    sp<_XmlValue> xmlvalue;

    sp<_XmlDocument> reader;

    xml_attribute<char> * attr;
};

DECLARE_SIMPLE_CLASS(XmlValueIterator) {
public:
    _XmlValueIterator(_XmlValue *,sp<_XmlDocument> r);

    bool hasValue();

    bool next();

    sp<_XmlValue> getValue();

private:
    sp<_XmlValue> xmlValue;

    sp<_XmlDocument> reader;

    xml_node<>*  node; 
};

DECLARE_SIMPLE_CLASS(XmlAttribute) {

public:
    friend class _XmlValue;
    
    _XmlAttribute(xml_attribute<char> * attribute,sp<_XmlDocument> r,String n,String v);

    String getName();
    
    String getValue();

    void updateName(String);

    void updateValue(String);

private:
    String value;

    String name;

    sp<_XmlDocument> reader;

    xml_attribute<char> * attr;
};


DECLARE_SIMPLE_CLASS(XmlValue) {

public:
    friend class _XmlReader;
    friend class _XmlAttrIterator;
    friend class _XmlValueIterator;
    friend class _XmlDocument;
    friend class _XmlWriter;

    //_XmlValue(xml_node<> *n);

    _XmlValue(xml_node<> *n,sp<_XmlDocument> d,String,String);

    _XmlValue(xml_node<> *n,_XmlDocument* r,String,String);

    //_XmlValue(sp<_XmlDocument> r);

    sp<_XmlAttrIterator> getAttrIterator();

    sp<_XmlValueIterator> getValueIterator();

    String getStringAttr(String attr);

    Integer getIntegerAttr(String attr);

    Boolean getBooleanAttr(String attr);

    Double getDoubleAttr(String attr);

    Float getFloatAttr(String attr);

    String getStringValue();

    Integer getIntegerValue();

    Boolean getBooleanValue();

    Double getDoubleValue();

    Float getFloatValue();

    String getName();

    void updateName(String name);

    void updateValue(String value);

    void appendNode(XmlValue v);

    void appendAttr(XmlAttribute v);

    void removeNode(XmlValue v);

private:
    //void setParser(sp<_XmlReader> r);
    ArrayList<XmlValue> valueCache;

    ArrayList<XmlAttribute> attrCache;

    String value;

    String name;

    sp<_XmlDocument> doc; //

    xml_node<>*  node;
};

}


#endif