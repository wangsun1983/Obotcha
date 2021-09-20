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
}

//_XmlValue::_XmlValue(xml_node<> *n,_XmlDocument* r,String _name,String _value) {
_XmlValue::_XmlValue(xml_node<> *n,_XmlDocument* r) {
    node = n;
    doc.set_pointer(r);
}

String _XmlValue::getStringAttr(String attr) {
    xml_attribute<> *v = node->first_attribute(attr->toChars());

    if(v == nullptr) {
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
    String v = createString(node->name());
    return v;
}

void _XmlValue::updateName(String n) {
    if(n == nullptr) {
        return;
    }

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
        createString(doc->xmlDoc.allocate_string(trimres->toChars())),
        createString(doc->xmlDoc.allocate_string(value->toChars())));

    node->append_node(newnode->node);
}

int _XmlValue::updateAttr(String name,String newvalue) {
    if(name == nullptr || newvalue == nullptr) {
        return -InvalidParam;
    }

    xml_attribute<> *attr = node->first_attribute(name->toChars());
    if(attr != nullptr) {
        attr->value(doc->xmlDoc.allocate_string(newvalue->toChars()),newvalue->size());
        return 0;
    }

    return -NotFound;
}

int _XmlValue::renameAttr(String name,String newname) {
    if(name == nullptr || newname == nullptr) {
        return -InvalidParam;
    }

    xml_attribute<> *attr = node->first_attribute(name->toChars());
    if(attr != nullptr) {
        attr->name(doc->xmlDoc.allocate_string(newname->toChars()),
                   newname->size());
        return 0;
    }

    return -NotFound;
}

void _XmlValue::appendAttr(String name,String value) {
    //node->append_attribute(v->attr);
    //attrCache->add(v);
    String newres = name->trimAll();
    xml_attribute<> *attr = doc->xmlDoc.allocate_attribute(doc->xmlDoc.allocate_string(newres->toChars()),
        doc->xmlDoc.allocate_string(value->toChars()));

    node->append_attribute(attr);
    //xml_attribute<> *attr2 = node->first_attribute(name->toChars());
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

void _XmlValue::reflectToArrayList(Object obj) {
    auto iterator = this->getValueIterator();

    while(iterator->hasValue()) {
        auto newObject = obj->__createListItemObject("");
        XmlValue value = iterator->getValue();
        if(IsInstance(Integer,newObject)) {
            Integer data = Cast<Integer>(newObject);
            data->update(value->getStringValue()->toBasicInt());
        } else if(IsInstance(Long,newObject)) {
            Long data = Cast<Long>(newObject);
            data->update(value->getStringValue()->toBasicLong());
        } else if(IsInstance(Boolean,newObject)) {
            Boolean data = Cast<Boolean>(newObject);
            if(value->getStringValue()->toBasicInt() == 0) {
                data->update(false);
            } else {
                data->update(true);
            }
        } else if(IsInstance(Double,newObject)) {
            Double data = Cast<Double>(newObject);
            data->update(value->getStringValue()->toBasicDouble());
        } else if(IsInstance(Float,newObject)) {
            Float data = Cast<Float>(newObject);
            data->update(value->getStringValue()->toBasicDouble());
        } else if(IsInstance(Byte,newObject)) {
            Byte data = Cast<Byte>(newObject);
            data->update(value->getStringValue()->toBasicByte());
        } else if(IsInstance(Uint8,newObject)) {
            Uint8 data = Cast<Uint8>(newObject);
            data->update(value->getStringValue()->toBasicUint8());
        } else if(IsInstance(Uint16,newObject)) {
            Uint16 data = Cast<Uint16>(newObject);
            data->update(value->getStringValue()->toBasicUint16());
        } else if(IsInstance(Uint32,newObject)) {
            Uint32 data = Cast<Uint32>(newObject);
            data->update(value->getStringValue()->toBasicUint32());
        } else if(IsInstance(Uint64,newObject)) {
            Uint64 data = Cast<Uint64>(newObject);
            data->update(value->getStringValue()->toBasicUint64());
        } else if(IsInstance(String,newObject)) {
            String data = Cast<String>(newObject);
            data->update(value->getStringValue()->getStdString());
        } else if(newObject->__ReflectClassName()->equals("_ArrayList")) {
            value->reflectToArrayList(newObject);
        } else if(newObject->__ReflectClassName()->equals("_HashMap")) {
            value->reflectToHashMap(newObject);
        } else {
            value->reflectTo(newObject);
        }
        obj->__addListItemObject("",newObject);
        iterator->next();
    }
}

void _XmlValue::reflectToHashMap(Object obj) {
    auto sub_iterator = this->getValueIterator();
    while(sub_iterator->hasValue()) {
        sp<_XmlValue> xmlnode = sub_iterator->getValue();
        KeyValuePair<Object,Object> pair = obj->__createMapItemObject("");
        Object key = pair->getKey();
        String name = xmlnode->getName();
        if(IsInstance(Integer,key)) {
            Integer data = Cast<Integer>(key);
            data->update(name->toBasicInt());
        } else if(IsInstance(Long,key)) {
            Long data = Cast<Long>(key);
            data->update(name->toBasicLong());
        } else if(IsInstance(Boolean,key)) {
            Boolean data = Cast<Boolean>(key);
            data->update(name->toBasicBool());
        } else if(IsInstance(Double,key)) {
            Double data = Cast<Double>(key);
            data->update(name->toBasicDouble());
        } else if(IsInstance(Float,key)) {
            Float data = Cast<Float>(key);
            data->update(name->toBasicFloat());
        } else if(IsInstance(Byte,key)) {
            Byte data = Cast<Byte>(key);
            data->update(name->toBasicByte());
        } else if(IsInstance(Uint8,key)) {
            Uint8 data = Cast<Uint8>(key);
            data->update(name->toBasicUint8());
        } else if(IsInstance(Uint16,key)) {
            Uint16 data = Cast<Uint16>(key);
            data->update(name->toBasicUint16());
        } else if(IsInstance(Uint32,key)) {
            Uint32 data = Cast<Uint32>(key);
            data->update(name->toBasicUint32());
        } else if(IsInstance(Uint64,key)) {
            Uint64 data = Cast<Uint64>(key);
            data->update(name->toBasicUint64());
        } else if(IsInstance(String,key)) {
            String data = Cast<String>(key);
            data->update(name->toChars());
        } else {
            Trigger(TransformException,"not support key type");
        }

        Object pairValue = pair->getValue();
        String xmlValue = xmlnode->getStringValue();
        if(IsInstance(Integer,pairValue)) {
            Integer data = Cast<Integer>(pairValue);
            data->update(xmlValue->toBasicInt());
        } else if(IsInstance(Long,pairValue)) {
            Long data = Cast<Long>(pairValue);
            data->update(xmlValue->toBasicLong());
        } else if(IsInstance(Boolean,pairValue)) {
            Boolean data = Cast<Boolean>(pairValue);
            data->update(xmlValue->toBasicBool());
        } else if(IsInstance(Double,pairValue)) {
            Double data = Cast<Double>(pairValue);
            data->update(xmlValue->toBasicDouble());
        } else if(IsInstance(Float,pairValue)) {
            Float data = Cast<Float>(pairValue);
            data->update(xmlValue->toBasicFloat());
        } else if(IsInstance(Byte,pairValue)) {
            Byte data = Cast<Byte>(pairValue);
            data->update(xmlValue->toBasicByte());
        } else if(IsInstance(Uint8,pairValue)) {
            Uint8 data = Cast<Uint8>(pairValue);
            data->update(xmlValue->toBasicUint8());
        } else if(IsInstance(Uint16,pairValue)) {
            Uint16 data = Cast<Uint16>(pairValue);
            data->update(xmlValue->toBasicUint16());
        } else if(IsInstance(Uint32,pairValue)) {
            Uint32 data = Cast<Uint32>(pairValue);
            data->update(xmlValue->toBasicUint32());
        } else if(IsInstance(Uint64,pairValue)) {
            Uint64 data = Cast<Uint64>(pairValue);
            data->update(xmlValue->toBasicUint64());
        } else if(IsInstance(String,pairValue)) {
            String data = Cast<String>(pairValue);
            data->update(xmlValue->toChars());
        } else if(pairValue->__ReflectClassName()->equals("_ArrayList")) {
            xmlnode->reflectToArrayList(pairValue);
        } else if(pairValue->__ReflectClassName()->equals("_HashMap")) {
            xmlnode->reflectToHashMap(pairValue);
        } else {
            xmlnode->reflectTo(pairValue);
        }
        obj->__addMapItemObject("",key,pairValue);
        sub_iterator->next();
    }
}

void _XmlValue::reflectTo(Object obj) {
    if(obj->__ReflectClassName()->equals("_ArrayList")) {
        this->reflectToArrayList(obj);
        return;
    } else if(obj->__ReflectClassName()->equals("_HashMap")) {
        this->reflectToHashMap(obj);
        return;
    }

    sp<_XmlValueIterator> iterator = getValueIterator();
    while(iterator->hasValue()) {
        sp<_XmlValue> node = iterator->getValue();
        Field field = obj->getField(node->getName());
        if(field == nullptr) {
            LOG(ERROR)<<"reflect to fields is null!!!";
            iterator->next();
            continue;
        }

        switch(field->getType()) {
            case st(Field)::FieldTypeLong:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicLong());
                }
                break;

            case st(Field)::FieldTypeInt: {
                    String value = node->getStringValue();
                    field->setValue(value->toBasicInt());
                }
                break;

            case st(Field)::FieldTypeBool:{
                    String value = node->getStringValue();
                    if(value->toBasicInt() > 0) {
                        field->setValue(true);
                    } else {
                        field->setValue(false);
                    }
                }
                break;

            case st(Field)::FieldTypeDouble:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicDouble());
                }
                break;

            case st(Field)::FieldTypeFloat:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicFloat());
                }
                break;

            case st(Field)::FieldTypeString:{
                    String value = node->getStringValue();
                    field->setValue(value);
                }
                break;

            case st(Field)::FieldTypeUint8:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicUint8());
                }
                break;

            case st(Field)::FieldTypeUint16:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicUint16());
                }
                break;

            case st(Field)::FieldTypeUint32:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicUint32());
                }
                break;

            case st(Field)::FieldTypeUint64:{
                    String value = node->getStringValue();
                    field->setValue(value->toBasicUint64());
                }
                break;
                    
            case st(Field)::FieldTypeObject: {
                    auto newObject = field->createObject();
                    if(IsInstance(Integer,newObject)) {
                        String value = node->getStringValue();
                        Integer data = Cast<Integer>(newObject);
                        data->update(value->toBasicInt());
                    } else if(IsInstance(Long,newObject)) {
                        String value = node->getStringValue();
                        Long data = Cast<Long>(newObject);
                        data->update(value->toBasicLong());
                    } else if(IsInstance(Boolean,newObject)) {
                        String value = node->getStringValue();
                        Boolean data = Cast<Boolean>(newObject);
                        if(value->toBasicInt() == 0) {
                            data->update(false);
                        } else {
                            data->update(true);
                        }
                    } else if(IsInstance(Double,newObject)) {
                        String value = node->getStringValue();
                        Double data = Cast<Double>(newObject);
                        data->update(value->toBasicDouble());
                    } else if(IsInstance(Float,newObject)) {
                        String value = node->getStringValue();
                        Float data = Cast<Float>(newObject);
                        data->update(value->toBasicFloat());
                    } else if(IsInstance(Byte,newObject)) {
                        String value = node->getStringValue();
                        Byte data = Cast<Byte>(newObject);
                        data->update(value->toBasicByte());
                    } else if(IsInstance(Uint8,newObject)) {
                        String value = node->getStringValue();
                        Uint8 data = Cast<Uint8>(newObject);
                        data->update(value->toBasicByte());
                    } else if(IsInstance(Uint16,newObject)) {
                        String value = node->getStringValue();
                        Uint16 data = Cast<Uint16>(newObject);
                        data->update(value->toBasicUint16());
                    } else if(IsInstance(Uint32,newObject)) {
                        String value = node->getStringValue();
                        Uint32 data = Cast<Uint32>(newObject);
                        data->update(value->toBasicUint32());
                    } else if(IsInstance(Uint64,newObject)) {
                        String value = node->getStringValue();
                        Uint64 data = Cast<Uint64>(newObject);
                        data->update(value->toBasicUint64());
                    } else {
                        node->reflectTo(newObject);
                    }
                }
                break;

            case st(Field)::FieldTypeArrayList:{
                    auto newObject = field->createObject();
                    node->reflectToArrayList(newObject);
                }
                break;

            case st(Field)::FieldTypeHashMap:{
                    auto newObject = field->createObject();
                    node->reflectToHashMap(newObject);
                }
                break;
        }

        iterator->next();
    }
}

void _XmlValue::importHashMapFrom(Object hashmap) {
    int size = this->__getContainerSize("");
    ArrayList<KeyValuePair<Object,Object>> members = hashmap->__getMapItemObjects("");
    auto iterator = members->getIterator();
    while(iterator->hasValue()) {
        KeyValuePair<Object,Object> node = iterator->getValue();
        Object key = node->getKey();
        Object value = node->getValue();
        sp<_XmlValue> item;
        if(IsInstance(Integer,key)) {
            Integer data = Cast<Integer>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Long,key)) {
            Long data = Cast<Long>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Boolean,key)) {
            Boolean data = Cast<Boolean>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Double,key)) {
            Double data = Cast<Double>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Float,key)) {
            Float data = Cast<Float>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Byte,key)) {
            Byte data = Cast<Byte>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Uint8,key)) {
            Uint8 data = Cast<Uint8>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Uint16,key)) {
            Uint16 data = Cast<Uint16>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Uint32,key)) {
            Uint32 data = Cast<Uint32>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(Uint64,key)) {
            Uint64 data = Cast<Uint64>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if(IsInstance(String,key)) {
            item = doc->newNode(Cast<String>(key));
        } else {
            Trigger(TransformException,"not support key type");
        }
        
        if(IsInstance(Integer,value)) {
            Integer data = Cast<Integer>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Long,value)) {
            Long data = Cast<Long>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Boolean,value)) {
            Boolean data = Cast<Boolean>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Double,value)) {
            Double data = Cast<Double>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Float,value)) {
            Float data = Cast<Float>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Byte,value)) {
            Byte data = Cast<Byte>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Uint8,value)) {
            Uint8 data = Cast<Uint8>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Uint16,value)) {
            Uint16 data = Cast<Uint16>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Uint32,value)) {
            Uint32 data = Cast<Uint32>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(Uint64,value)) {
            Uint64 data = Cast<Uint64>(value);
            item->updateValue(createString(data->toValue()));
        } else if(IsInstance(String,value)) {
            String data = Cast<String>(value);
            item->updateValue(data);
        } else {
            item->importFrom(value);
        }
        this->appendNode(item);
        iterator->next();
    }
}

void _XmlValue::importFrom(Object value) {
    if(value->__ReflectClassName()->equals("_ArrayList")) {
        int size = value->__getContainerSize("");
        for(int i = 0;i<size;i++) {
            sp<_XmlValue> refNode = doc->newNode(createString("_array_item"));
            auto nValue = value->__getListItemObject("",i);
            refNode->importFrom(nValue);
            this->appendNode(refNode);
        }
        return;
    } else if(value->__ReflectClassName()->equals("_HashMap")) {
        this->importHashMapFrom(value);
        return;
    }

    String name = value->__ReflectClassName();
    ArrayList<Field> fields = value->getAllFields();
    if(fields == nullptr) {
        LOG(ERROR)<<"XmlVale importFrom fields is null!!!";
        return;
    }

    ListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field field = iterator->getValue();
        String name = field->getName();
        sp<_XmlValue> refNode = nullptr;
        switch(field->getType()) {
            case st(Field)::FieldTypeLong: {
                refNode = doc->newNode(name,createString(field->getLongValue()));
            }
            break;

            case st(Field)::FieldTypeInt: {
                refNode = doc->newNode(name,createString(field->getIntValue()));
            }
            break;

            case st(Field)::FieldTypeBool:{
                refNode = doc->newNode(name,createString(field->getBoolValue()));
            }
            break;

            case st(Field)::FieldTypeDouble:{
                refNode = doc->newNode(name,createString(field->getDoubleValue()));
            }
            break;

            case st(Field)::FieldTypeFloat:{
                refNode = doc->newNode(name,createString(field->getFloatValue()));
            }
            break;

            case st(Field)::FieldTypeString:{
                refNode = doc->newNode(name,field->getStringValue());
            }
            break;

            case st(Field)::FieldTypeUint8:{
                refNode = doc->newNode(name,createString(field->getByteValue()));
            }
            break;

            case st(Field)::FieldTypeUint16:{
                refNode = doc->newNode(name,createString(field->getUint16Value()));
            }
            break;

            case st(Field)::FieldTypeUint32:{
                refNode = doc->newNode(name,createString(field->getUint32Value()));
            }
            break;

            case st(Field)::FieldTypeUint64:{
                refNode = doc->newNode(name,createString(field->getUint64Value()));
            }
            break;

            case st(Field)::FieldTypeObject: {
                auto newObject = field->getObjectValue();
                refNode = doc->newNode(name);
                if(IsInstance(Integer,newObject)) {
                    Integer data = Cast<Integer>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Long,newObject)) {
                    Long data = Cast<Long>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Boolean,newObject)) {
                    Boolean data = Cast<Boolean>(newObject);
                    refNode->updateValue(createString((int)data->toValue()));
                } else if(IsInstance(Double,newObject)) {
                    Double data = Cast<Double>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Float,newObject)) {
                    Float data = Cast<Float>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Byte,newObject)) {
                    Byte data = Cast<Byte>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Uint8,newObject)) {
                    Uint8 data = Cast<Uint8>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Uint16,newObject)) {
                    Uint16 data = Cast<Uint16>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Uint32,newObject)) {
                    Uint32 data = Cast<Uint32>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(Uint64,newObject)) {
                    Uint64 data = Cast<Uint64>(newObject);
                    refNode->updateValue(createString(data->toValue()));
                } else if(IsInstance(String,newObject)) {
                    String data = Cast<String>(newObject);
                    refNode->updateValue(data);
                } else {    
                    auto newObject = field->getObjectValue();
                    refNode->importFrom(newObject);
                }
            }
            break;
            
            case st(Field)::FieldTypeArrayList: {
                int count = 0;
                int length = field->getContainerSize();

                refNode = doc->newNode(name);
                while(count < length) {
                    auto newObject = field->getListItemObject(count);
                    if(newObject != nullptr) {
                        sp<_XmlValue> item;
                        if(IsInstance(Integer,newObject)) {
                            item = doc->newNode(st(Integer)::className());
                            Integer data = Cast<Integer>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Long,newObject)) {
                            item = doc->newNode(st(Long)::className());
                            Long data = Cast<Long>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Boolean,newObject)) {
                            item = doc->newNode(st(Boolean)::className());
                            Boolean data = Cast<Boolean>(newObject);
                            item->updateValue(createString((int)data->toValue()));
                        } else if(IsInstance(Double,newObject)) {
                            item = doc->newNode(st(Double)::className());
                            Double data = Cast<Double>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Float,newObject)) {
                            item = doc->newNode(st(Float)::className());
                            Float data = Cast<Float>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Byte,newObject)) {
                            item = doc->newNode(st(Byte)::className());
                            Byte data = Cast<Byte>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Uint8,newObject)) {
                            item = doc->newNode(st(Uint8)::className());
                            Uint8 data = Cast<Uint8>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Uint16,newObject)) {
                            item = doc->newNode(st(Uint16)::className());
                            Uint16 data = Cast<Uint16>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Uint32,newObject)) {
                            item = doc->newNode(st(Uint32)::className());
                            Uint32 data = Cast<Uint32>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(Uint64,newObject)) {
                            item = doc->newNode(st(Uint64)::className());
                            Uint64 data = Cast<Uint64>(newObject);
                            item->updateValue(createString(data->toValue()));
                        } else if(IsInstance(String,newObject)) {
                            item = doc->newNode(st(String)::className());
                            String data = Cast<String>(newObject);
                            item->updateValue(data);
                        } else {
                            item = doc->newNode(newObject->__ReflectClassName());
                            item->importFrom(newObject);
                        }
                        refNode->appendNode(item);
                    }
                    count++;
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                auto newObject = field->getObjectValue();
                refNode = doc->newNode(name);
                refNode->importHashMapFrom(newObject);
            }
            break;
        }

        if(refNode != nullptr) {
            this->appendNode(refNode);
        }
        iterator->next();
    }
}


}