#include "XmlValue.hpp"
#include "XmlReader.hpp"
#include "XmlDocument.hpp"

#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

namespace obotcha {

//------------------ XmlAttrIterator -----------------//
_XmlAttrIterator::_XmlAttrIterator(_XmlValue *v,sp<_XmlDocument> r) {
    xmlvalue.set_pointer(v);
    reader = r;
    attr = v->node->first_attribute();
}

bool _XmlAttrIterator::hasValue() {
    return attr != nullptr;
}

bool _XmlAttrIterator::next() {
    attr = attr->next_attribute();
    return attr != nullptr;
}

sp<_XmlAttribute> _XmlAttrIterator::getAttribute() {
    String name = createString(attr->name());
    String value = createString(attr->value());
    sp<_XmlAttribute> attribute = createXmlAttribute(attr,reader,name,value);
    return attribute;
}

//------------------ XmlValueIterator ---------------//
_XmlValueIterator::_XmlValueIterator(_XmlValue *v,sp<_XmlDocument> r) {
    xmlValue.set_pointer(v);
    reader = r;
    node = v->node->first_node();
}

bool _XmlValueIterator::hasValue() {
    return node != nullptr;
}

bool _XmlValueIterator::next() {
    node = node->next_sibling();
}

XmlValue _XmlValueIterator::getValue() {
    if(node == nullptr) {
        return nullptr;
    }

    String n = createString(node->name());
    String v = createString(node->value());
    XmlValue value = createXmlValue(node,reader,n,v);
    return value;
}

//------------------ XmlAttribute -----------------//
_XmlAttribute::_XmlAttribute(xml_attribute<char> * attribute,sp<_XmlDocument> r,String n,String v) {
    attr = attribute;
    reader = r;
    name = n;
    value = v;
}

String _XmlAttribute::getName() {
    //return createString(attr->name());
    return name;
}
    
String _XmlAttribute::getValue() {
    //return createString(attr->value());
    return value;
}

void _XmlAttribute::updateName(String n) {
    name = n;
    return attr->name(name->toChars(),name->size());
}

void _XmlAttribute::updateValue(String v) {
    value = v;
    return attr->value(value->toChars(),value->size());
}

//------------------ XmlValue -----------------//
//_XmlValue::_XmlValue(xml_node<> *n) {
//    node = n;
//}

//_XmlValue::_XmlValue(sp<_XmlDocument> r) {
//    doc = r;
//    node = doc->xmlDoc.allocate_node(node_element);
//}

_XmlValue::_XmlValue(xml_node<> *n,sp<_XmlDocument> d,String _name,String _value) {
    node = n;
    doc = d;
    name = _name;
    value = _value;

    valueCache = createArrayList<XmlValue>();
    attrCache = createArrayList<XmlAttribute>();
}

_XmlValue::_XmlValue(xml_node<> *n,_XmlDocument* r,String _name,String _value) {
    node = n;
    doc.set_pointer(r);
    name = _name;
    value = _value;

    valueCache = createArrayList<XmlValue>();
    attrCache = createArrayList<XmlAttribute>();
}

//void _XmlValue::setParser(sp<_XmlDocument> r) {
//    reader = r;
//}

String _XmlValue::getStringAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    return createString(v->value());
}

Integer _XmlValue::getIntegerAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    String val = createString(v->value());
    return val->toInteger();
}

Boolean _XmlValue::getBooleanAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    String val = createString(v->value());
    return val->toBoolean();
}

Double _XmlValue::getDoubleAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    String val = createString(v->value());
    return val->toDouble();
}

Float _XmlValue::getFloatAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    String val = createString(v->value());
    return val->toFloat();
}

String _XmlValue::getStringValue() {
    String v = createString(node->value());
    return v;
}

Integer _XmlValue::getIntegerValue() {
    String v = createString(node->value());
    return v->toInteger();
}

Boolean _XmlValue::getBooleanValue() {
    String v = createString(node->value());
    return v->toBoolean();
}

Double _XmlValue::getDoubleValue() {
    String v = createString(node->value());
    return v->toDouble();
}

Float _XmlValue::getFloatValue() {
    String v = createString(node->value());
    return v->toFloat();
}

String _XmlValue::getName() {
    String v = createString(node->name());
    return v;
}

void _XmlValue::updateName(String n) {
    node->name(name->toChars(),name->size());
    name = n;
}

void _XmlValue::updateValue(String v) {
    node->value(value->toChars(),value->size());
    value = v;
}

void _XmlValue::appendNode(XmlValue v) {
    node->append_node(v->node);
    valueCache->add(v);
}

void _XmlValue::appendAttr(XmlAttribute v) {
    node->append_attribute(v->attr);
    attrCache->add(v);
}

void _XmlValue::removeNode(XmlValue v) {
    node->remove_node(v->node);
    valueCache->remove(v);
}

sp<_XmlAttrIterator> _XmlValue::getAttrIterator() {
    XmlAttrIterator iterator = createXmlAttrIterator(this,doc);
    return iterator;
}

sp<_XmlValueIterator> _XmlValue::getValueIterator() {
    XmlValueIterator iterator = createXmlValueIterator(this,doc);
    return iterator;
}


}