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

enum XmlValueFailReason {
    XmlValueFailWrongParam = 200,
    XmlValueFailNotFound,
};

DECLARE_SIMPLE_CLASS(XmlAttrIterator) {
public:
    _XmlAttrIterator(sp<_XmlValue> node,sp<_XmlDocument> r);

    bool hasValue();

    bool next();

    //sp<_XmlAttribute> getAttribute();
    String getName();

    String getValue();

private:
    sp<_XmlValue> xmlvalue;

    sp<_XmlDocument> reader;

    xml_attribute<char> * attr;
};

DECLARE_SIMPLE_CLASS(XmlValueIterator) {
public:
    _XmlValueIterator(sp<_XmlValue> node,sp<_XmlDocument> r);

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
    
    _XmlAttribute(sp<_XmlValue> node,sp<_XmlDocument> r,String n,String v);

    int updateName(String name,String newname);

    int updateValue(String name,String newvalue);

private:
    sp<_XmlDocument> reader;

    //xml_attribute<char> * attr;
    sp<_XmlValue> xmlvalue;

    //xml_node<>*  node; 
};


DECLARE_SIMPLE_CLASS(XmlValue) {

public:
    friend class _XmlReader;
    friend class _XmlAttrIterator;
    friend class _XmlValueIterator;
    friend class _XmlDocument;
    friend class _XmlWriter;
    friend class _XmlAttribute;

    _XmlValue(xml_node<> *n,sp<_XmlDocument> d);

    _XmlValue(xml_node<> *n,_XmlDocument* r);    

    sp<_XmlAttrIterator> getAttrIterator();

    sp<_XmlValueIterator> getValueIterator();

    String getStringAttr(String attr);

    Integer getIntegerAttr(String attr);

    Boolean getBooleanAttr(String attr);

    Double getDoubleAttr(String attr);

    Float getFloatAttr(String attr);

    sp<_XmlAttribute> getAttribute();

    String getStringValue();

    Integer getIntegerValue();

    Boolean getBooleanValue();

    Double getDoubleValue();

    Float getFloatValue();
    
    String getStringValue(String);

    Integer getIntegerValue(String);

    Boolean getBooleanValue(String);

    Double getDoubleValue(String);

    Float getFloatValue(String);

    XmlValue getNode(String);

    String getName();

    void updateName(String name);

    void updateValue(String value);

    void appendNode(XmlValue v);

    void appendNode(String name,String value);

    void appendAttr(String name,String value);

    void removeNode(XmlValue v);

    void removeNode(String);

private:
    String value;

    String name;

    sp<_XmlDocument> doc; //

    xml_node<>*  node;

    String searchNode(String name);
};

}


#endif