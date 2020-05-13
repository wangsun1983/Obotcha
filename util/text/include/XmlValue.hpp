#ifndef __OBOTCHA_XML_VALUE_H__
#define __OBOTCHA_XML_VALUE_H__

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
class _XmlDocument;
class _XmlWriter;


DECLARE_SIMPLE_CLASS(XmlAttrIterator) {
public:
    _XmlAttrIterator(sp<_XmlValue> node,sp<_XmlDocument> r);

    bool hasValue();

    bool next();

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

DECLARE_SIMPLE_CLASS(XmlValue) {

public:
    friend class _XmlReader;
    friend class _XmlAttrIterator;
    friend class _XmlValueIterator;
    friend class _XmlDocument;
    friend class _XmlWriter;

    _XmlValue(xml_node<> *n,sp<_XmlDocument> d);

    _XmlValue(xml_node<> *n,_XmlDocument* r);    

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

    int updateAttr(String name,String value);

    int renameAttr(String name,String newnanme);

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