#ifndef __OBOTCHA_XML_VALUE_H__
#define __OBOTCHA_XML_VALUE_H__

#include "dictionary.h"
#include "iniparser.h"
#include "rapidxml.hpp"

#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "Field.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Log.hpp"
#include "Long.hpp"
#include "OStdInstanceOf.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "TransformException.hpp"
#include "Uint32.hpp"

namespace obotcha {

class _XmlReader;
class _XmlValue;
class _XmlDocument;
class _XmlWriter;

DECLARE_CLASS(XmlAttrIterator) {
public:
    _XmlAttrIterator(sp<_XmlValue> node, sp<_XmlDocument> r);

    bool hasValue() const;

    bool next();

    String getName() const;

    String getValue() const;

private:
    sp<_XmlValue> xmlvalue;

    sp<_XmlDocument> reader;

    rapidxml::xml_attribute<char> *attr;
};

DECLARE_CLASS(XmlValueIterator) {
public:
    _XmlValueIterator(sp<_XmlValue> node, sp<_XmlDocument> r);

    bool hasValue() const;

    bool next();

    sp<_XmlValue> getValue();

private:
    sp<_XmlValue> xmlValue;

    sp<_XmlDocument> reader;

    rapidxml::xml_node<> *node;
};

DECLARE_CLASS(XmlValue) {
public:
    friend class _XmlReader;
    friend class _XmlAttrIterator;
    friend class _XmlValueIterator;
    friend class _XmlDocument;
    friend class _XmlWriter;

    _XmlValue(rapidxml::xml_node<> * n, sp<_XmlDocument> d);

    _XmlValue(rapidxml::xml_node<> * n, _XmlDocument * r);

    sp<_XmlAttrIterator> getAttrIterator();

    sp<_XmlValueIterator> getValueIterator();

    String getStringAttr(String attr) const;

    Integer getIntegerAttr(String attr) const;

    Boolean getBooleanAttr(String attr) const;

    Double getDoubleAttr(String attr) const;

    Float getFloatAttr(String attr) const;

    String getStringValue() const;

    Integer getIntegerValue() const;

    Boolean getBooleanValue() const;

    Double getDoubleValue() const;

    Float getFloatValue() const;

    String getStringValue(String) const;

    Integer getIntegerValue(String) const;

    Boolean getBooleanValue(String) const;

    Double getDoubleValue(String) const;

    Float getFloatValue(String) const;

    XmlValue getNode(String);

    String getName() const;

    void updateName(String name);

    void updateValue(String value);

    void appendNode(XmlValue v);

    void appendNode(String name, String value);

    void appendAttr(String name, String value);

    int updateAttr(String name, String value);

    int renameAttr(String name, String newnanme);

    void removeNode(XmlValue v);

    void removeNode(String);

    void importFrom(Object);

    void reflectTo(Object,int type = ReflectValue);

private:
    enum ReflectType {
        ReflectName = 0,
        ReflectValue,
    };

    // String mValue;

    // String name;

    sp<_XmlDocument> doc; //

    rapidxml::xml_node<> *node;

    bool mNeedUpdateName = false;

    String searchNode(String name) const;

    void reflectToArrayList(Object obj);
    void reflectToHashMap(Object obj);
    void importArrayListFrom(Object value);
    void importHashMapFrom(Object value);
};

} // namespace obotcha

#endif