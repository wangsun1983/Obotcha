#include "XmlValue.hpp"
#include "XmlReader.hpp"
#include "XmlDocument.hpp"
#include "Error.hpp"

#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

namespace obotcha {

//------------------ XmlAttrIterator -----------------//
_XmlAttrIterator::_XmlAttrIterator(sp<_XmlValue> node,sp<_XmlDocument> r) {
    xmlvalue = node;
    reader = r;
    attr = xmlvalue->node->first_attribute();
}

bool _XmlAttrIterator::hasValue() {
    return attr != nullptr;
}

bool _XmlAttrIterator::next() {
    attr = attr->next_attribute();
    return attr != nullptr;
}

//sp<_XmlAttribute> _XmlAttrIterator::getAttribute() {
//    String name = createString(attr->name());
//    String value = createString(attr->value());
//    sp<_XmlAttribute> attribute = createXmlAttribute(attr,reader,name,value);
//    return attribute;
//}
String _XmlAttrIterator::getName() {
    if(attr == nullptr) {
        return nullptr;
    }

    return createString(attr->name());
}

String _XmlAttrIterator::getValue() {
    if(attr == nullptr) {
        return nullptr;
    }

    return createString(attr->value());
}


//------------------ XmlValueIterator ---------------//
_XmlValueIterator::_XmlValueIterator(sp<_XmlValue> n,sp<_XmlDocument> r) {
    xmlValue = n;
    reader = r;
    node = xmlValue->node->first_node();
}

bool _XmlValueIterator::hasValue() {
    return node != nullptr;
}

bool _XmlValueIterator::next() {
    node = node->next_sibling();
    return true;
}

XmlValue _XmlValueIterator::getValue() {
    if(node == nullptr) {
        return nullptr;
    }

    //String n = createString(node->name());
    //String v = createString(node->value());
    XmlValue value = createXmlValue(node,reader);
    return value;
}

//------------------ XmlAttribute -----------------//
_XmlAttribute::_XmlAttribute(sp<_XmlValue> node,sp<_XmlDocument> r,String n,String v) {
    xmlvalue = node;
    reader = r;
}

int _XmlAttribute::updateName(String name,String newname) {
    if(name == nullptr || newname == nullptr) {
        return -InvalidParam;
    }

    xml_attribute<> *attr = xmlvalue->node->first_attribute(name->toChars());
    if(attr != nullptr) {
        attr->name(reader->xmlDoc.allocate_string(newname->toChars()),
                   newname->size());
        return 0;
    }

    return -NotFound;
}

int _XmlAttribute::updateValue(String name,String newvalue) {
    if(name == nullptr || newvalue == nullptr) {
        return -InvalidParam;
    }

    xml_attribute<> *attr = xmlvalue->node->first_attribute(name->toChars());
    if(attr != nullptr) {
        attr->value(reader->xmlDoc.allocate_string(newvalue->toChars()),newvalue->size());
        return 0;
    }

    return -NotFound;
}

//------------------ XmlValue -----------------//
//_XmlValue::_XmlValue(xml_node<> *n) {
//    node = n;
//}

//_XmlValue::_XmlValue(sp<_XmlDocument> r) {
//    doc = r;
//    node = doc->xmlDoc.allocate_node(node_element);
//}

//_XmlValue::_XmlValue(xml_node<> *n,sp<_XmlDocument> d,String _name,String _value) {
_XmlValue::_XmlValue(xml_node<> *n,sp<_XmlDocument> d) {
    node = n;
    doc = d;
    //name = _name;
    //value = _value;

    //valueCache = createArrayList<XmlValue>();
    //attrCache = createArrayList<XmlAttribute>();
}

//_XmlValue::_XmlValue(xml_node<> *n,_XmlDocument* r,String _name,String _value) {
_XmlValue::_XmlValue(xml_node<> *n,_XmlDocument* r) {
    node = n;
    doc.set_pointer(r);
    //name = _name;
    //value = _value;

    //valueCache = createArrayList<XmlValue>();
    //attrCache = createArrayList<XmlAttribute>();
}

//void _XmlValue::setParser(sp<_XmlDocument> r) {
//    reader = r;
//}

String _XmlValue::getStringAttr(String attr) {
    //printf("getString arrt is %s,node is %x \n",attr->toChars(),node);
    xml_attribute<> *v = node->first_attribute(attr->toChars());

    if(v == nullptr) {
        printf("getString arrt is null \n");
        return nullptr;
    }
    return createString(v->value());
}

Integer _XmlValue::getIntegerAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    if(v == nullptr) {
        return nullptr;
    }
    String val = createString(v->value());
    return val->toInteger();
}

Boolean _XmlValue::getBooleanAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    if(v == nullptr) {
        return nullptr;
    }
    String val = createString(v->value());
    return val->toBoolean();
}

Double _XmlValue::getDoubleAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    if(v == nullptr) {
        return nullptr;
    }
    String val = createString(v->value());
    return val->toDouble();
}

Float _XmlValue::getFloatAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());
    if(v == nullptr) {
        return nullptr;
    }
    String val = createString(v->value());
    return val->toFloat();
}

sp<_XmlAttribute> _XmlValue::getAttribute() {
    
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


String _XmlValue::getStringValue(String name) {
    String value = searchNode(name);
    if(value != nullptr) {
        return value;
    }

    return nullptr;
}

Integer _XmlValue::getIntegerValue(String name) {
    String value = searchNode(name);
    if(value != nullptr) {
        return value->toInteger();
    }

    return nullptr;
}

Boolean _XmlValue::getBooleanValue(String name) {
    String value = searchNode(name);
    if(value != nullptr) {
        return value->toBoolean();
    }

    return nullptr;
}

Double _XmlValue::getDoubleValue(String name) {
    String value = searchNode(name);
    if(value != nullptr) {
        return value->toDouble();
    }

    return nullptr;
}

Float _XmlValue::getFloatValue(String name) {
    String value = searchNode(name);
    if(value != nullptr) {
        return value->toFloat();
    }

    return nullptr;
}

String _XmlValue::searchNode(String name) {
    if(name == nullptr) {
        return nullptr;
    }

    xml_node<> *first = node->first_node(name->toChars());
    if(first != nullptr) {
        return createString(first->value());
    }

    return nullptr;
}

XmlValue _XmlValue::getNode(String name) {
    if(name == nullptr) {
        return nullptr;
    }

    xml_node<> *first = node->first_node(name->toChars());
    if(first != nullptr) {
        return createXmlValue(first,doc);
    }
    
    return nullptr;
}


String _XmlValue::getName() {
    //printf("xmlvalue getname is %x \n",node);
    String v = createString(node->name());
    return v;
}

void _XmlValue::updateName(String n) {
    if(n == nullptr) {
        return;
    }

    //printf("xmlvalue update name is %x \n",node);

    node->name(doc->xmlDoc.allocate_string(n->toChars()),n->size());
    name = n;
}

void _XmlValue::updateValue(String v) {
    if(v == nullptr) {
        return;
    }
    
    node->value(doc->xmlDoc.allocate_string(v->toChars()),v->size());
    value = v;
}

void _XmlValue::appendNode(XmlValue v) {
    if(v == nullptr) {
        return;
    }

    node->append_node(v->node);
    //valueCache->add(v);
}

void _XmlValue::appendNode(String name,String value) {
    if(name == nullptr || value == nullptr) {
        return;
    }

    String trimres = name->trimAll();

    XmlValue newnode = doc->newNode(
        doc->xmlDoc.allocate_string(trimres->toChars()),
        doc->xmlDoc.allocate_string(value->toChars()));

    node->append_node(newnode->node);
}

void _XmlValue::appendAttr(String name,String value) {
    //node->append_attribute(v->attr);
    //attrCache->add(v);
    //printf("appendAttr name is %s,value is %s \n",name->toChars(),value->toChars());
    String newres = name->trimAll();
    xml_attribute<> *attr = doc->xmlDoc.allocate_attribute(doc->xmlDoc.allocate_string(newres->toChars()),
        doc->xmlDoc.allocate_string(value->toChars()));

    node->append_attribute(attr);
    //xml_attribute<> *attr2 = node->first_attribute(name->toChars());
    //printf("result is %s,node is %x \n",attr2->value(),node);
}

void _XmlValue::removeNode(XmlValue v) {
    node->remove_node(v->node);
    //valueCache->remove(v);
}

void _XmlValue::removeNode(String v) {
    //node->remove_node(v->node);
    //valueCache->remove(v);
    xml_node<>* searchNode = node->first_node(v->toChars());
    if(searchNode == nullptr) {
        return;
    }

    node->remove_node(searchNode);
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