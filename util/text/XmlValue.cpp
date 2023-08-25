#include "XmlValue.hpp"
#include "Error.hpp"
#include "XmlDocument.hpp"
#include "XmlReader.hpp"
#include "Inspect.hpp"

#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace obotcha {

//------------------ XmlAttrIterator -----------------//
_XmlAttrIterator::_XmlAttrIterator(sp<_XmlValue> node, sp<_XmlDocument> r):
                    xmlvalue(node),reader(r) {
    attr = xmlvalue->mNode->first_attribute();
}

bool _XmlAttrIterator::hasValue() const { 
    return attr != nullptr; 
}

bool _XmlAttrIterator::next() {
    attr = attr->next_attribute();
    return attr != nullptr;
}

String _XmlAttrIterator::getName() const {
    return (attr == nullptr)?nullptr:createString(attr->name());
}

String _XmlAttrIterator::getValue() const {
    return (attr == nullptr)?nullptr:createString(attr->value());
}

//------------------ XmlValueIterator ---------------//
_XmlValueIterator::_XmlValueIterator(sp<_XmlValue> n, sp<_XmlDocument> r):
                    xmlValue(n),reader(r) {
    node = xmlValue->mNode->first_node();
}

bool _XmlValueIterator::hasValue() const { 
    return node != nullptr; 
}

bool _XmlValueIterator::next() {
    node = node->next_sibling();
    return node != nullptr;
}

XmlValue _XmlValueIterator::getValue() {
    return (node == nullptr)?nullptr:createXmlValue(node, reader);
}

//------------------ XmlValue -----------------//
_XmlValue::_XmlValue(rapidxml::xml_node<> *n, sp<_XmlDocument> d):
                        doc(d),mNode(n) {
}

_XmlValue::_XmlValue(rapidxml::xml_node<> *n, _XmlDocument *r):
                        doc(AutoClone(r)),mNode(n) {
}

String _XmlValue::getStringAttr(String attr) const {
    auto v = mNode->first_attribute(attr->toChars());
    return (v == nullptr)?nullptr:createString(v->value());
}

Integer _XmlValue::getIntegerAttr(String attr) const {
    auto v = mNode->first_attribute(attr->toChars());
    return (v == nullptr)?nullptr:createString(v->value())->toInteger();
}

Boolean _XmlValue::getBooleanAttr(String attr) const {
    auto v = mNode->first_attribute(attr->toChars());
    return (v == nullptr)?nullptr:createString(v->value())->toBoolean();
}

Double _XmlValue::getDoubleAttr(String attr) const {
    auto v = mNode->first_attribute(attr->toChars());
    return (v == nullptr)?nullptr:createString(v->value())->toDouble();
}

Float _XmlValue::getFloatAttr(String attr) const {
    auto v = mNode->first_attribute(attr->toChars());
    return (v == nullptr)?nullptr:createString(v->value())->toFloat();
}

String _XmlValue::getStringValue() const {
    return createString(mNode->value());
}

Integer _XmlValue::getIntegerValue() const {
    return createString(mNode->value())->toInteger();
}

Boolean _XmlValue::getBooleanValue() const {
    return createString(mNode->value())->toBoolean();
}

Double _XmlValue::getDoubleValue() const {
    return createString(mNode->value())->toDouble();
}

Float _XmlValue::getFloatValue() const {
    return createString(mNode->value())->toFloat();
}

String _XmlValue::getStringValue(String name) const {
    return searchNode(name);
}

Integer _XmlValue::getIntegerValue(String name) const {
    String nodeValue = searchNode(name);
    return (nodeValue == nullptr)?nullptr:nodeValue->toInteger();
}

Boolean _XmlValue::getBooleanValue(String name) const {
    String nodeValue = searchNode(name);
    return (nodeValue == nullptr)?nullptr:nodeValue->toBoolean();
}

Double _XmlValue::getDoubleValue(String name) const {
    String nodeValue = searchNode(name);
    return (nodeValue == nullptr)?nullptr:nodeValue->toDouble();
}

Float _XmlValue::getFloatValue(String name) const {
    String nodeValue = searchNode(name);
    return (nodeValue == nullptr)?nullptr:nodeValue->toFloat();
}

String _XmlValue::searchNode(String name) const {
    Inspect(name == nullptr,nullptr)
    auto first = mNode->first_node(name->toChars());
    return (first == nullptr)?nullptr:createString(first->value());
}

XmlValue _XmlValue::getNode(String name) {
    Inspect(name == nullptr,nullptr)
    auto first = mNode->first_node(name->toChars());
    return (first == nullptr)?nullptr:createXmlValue(first, doc);
}

String _XmlValue::getName() const {
    return createString(mNode->name());
}

void _XmlValue::updateName(String v) {
    Inspect(v == nullptr)
    mNode->name(doc->xmlDoc.allocate_string(v->toChars()), v->size());
}

void _XmlValue::updateValue(String v) {
    Inspect(v == nullptr)
    mNode->value(doc->xmlDoc.allocate_string(v->toChars()), v->size());
}

void _XmlValue::appendNode(XmlValue v) {
    Inspect(v == nullptr)
    mNode->append_node(v->mNode);
}

void _XmlValue::appendNode(String name, String value) {
    Inspect(name == nullptr || value == nullptr)

    String trimres = name->trimAll();
    XmlValue newnode = doc->newNode(
        createString(doc->xmlDoc.allocate_string(trimres->toChars())),
        createString(doc->xmlDoc.allocate_string(value->toChars())));

    mNode->append_node(newnode->mNode);
}

int _XmlValue::updateAttr(String name, String newvalue) {
    Inspect(name == nullptr || newvalue == nullptr,-EINVAL)
    if (auto attr = mNode->first_attribute(name->toChars());attr != nullptr) {
        attr->value(doc->xmlDoc.allocate_string(newvalue->toChars()),
                    newvalue->size());
        return 0;
    }

    return -1;
}

int _XmlValue::renameAttr(String name, String newname) {
    Inspect(name == nullptr || newname == nullptr,-EINVAL)
    if (auto attr = mNode->first_attribute(name->toChars());
        attr != nullptr) {
        attr->name(doc->xmlDoc.allocate_string(newname->toChars()),
                   newname->size());
        return 0;
    }

    return -1;
}

void _XmlValue::appendAttr(String name, String value) {
    String newres = name->trimAll();
    auto attr = doc->xmlDoc.allocate_attribute(
        doc->xmlDoc.allocate_string(newres->toChars()),
        doc->xmlDoc.allocate_string(value->toChars()));

    mNode->append_attribute(attr);
}

void _XmlValue::removeNode(XmlValue v) {
    mNode->remove_node(v->mNode);
}

void _XmlValue::removeNode(String v) {
    rapidxml::xml_node<> *searchNode = mNode->first_node(v->toChars());
    Inspect(searchNode == nullptr)
    mNode->remove_node(searchNode);
}

sp<_XmlAttrIterator> _XmlValue::getAttrIterator() {
    return createXmlAttrIterator(this, doc);
}

sp<_XmlValueIterator> _XmlValue::getValueIterator() {
    return createXmlValueIterator(this, doc);
}

void _XmlValue::reflectToArrayList(Object obj) {
    auto iterator = this->getValueIterator();
    while (iterator->hasValue()) {
        auto newObject = obj->__createListItemObject("");
        XmlValue value = iterator->getValue();
        value->reflectTo(newObject);
        obj->__addListItemObject("", newObject);
        iterator->next();
    }
}

void _XmlValue::reflectToHashMap(Object obj) {
    XmlValueIterator iterator = this->getValueIterator();
    while (iterator->hasValue()) {
        XmlValue xmlnode = iterator->getValue();
        Pair<Object, Object> pair = obj->__createMapItemObject("");
        Object key = pair->getKey();
        xmlnode->reflectTo(key,st(Text)::Syntax::Name);
        Object pairValue = pair->getValue();
        xmlnode->reflectTo(pairValue);
        obj->__addMapItemObject("", key, pairValue);
        iterator->next();
    }
}


void _XmlValue::reflectTo(Object obj,st(Text)::Syntax type) {
    try {
        if (obj->__ReflectClassName()->sameAs("_ArrayList")) {
            this->reflectToArrayList(obj);
            return;
        } else if (obj->__ReflectClassName()->sameAs("_HashMap")) {
            this->reflectToHashMap(obj);
            return;
        }
    }catch(...){}

    if (IsInstance(Integer, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Integer>(obj)->update(v->toBasicInt());
        return;
    } else if (IsInstance(Long, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Long>(obj)->update(v->toBasicLong());
        return;
    } else if (IsInstance(Boolean, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        if (v->equalsIgnoreCase("true")) {
            Cast<Boolean>(obj)->update(true);
        } else {
            Cast<Boolean>(obj)->update(false);
        }
        return;
    } else if (IsInstance(Double, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Double>(obj)->update(v->toBasicDouble());
        return;
    } else if (IsInstance(Float, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Float>(obj)->update(v->toBasicFloat());
        return;
    } else if (IsInstance(Byte, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Byte>(obj)->update(v->toBasicByte());
        return;
    } else if (IsInstance(Uint8, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Uint8>(obj)->update(v->toBasicUint8());
        return;
    } else if (IsInstance(Uint16, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Uint16>(obj)->update(v->toBasicUint16());
        return;
    } else if (IsInstance(Uint32, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Uint32>(obj)->update(v->toBasicUint32());
        return;
    } else if (IsInstance(Uint64, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<Uint64>(obj)->update(v->toBasicUint64());
        return;
    } else if (IsInstance(String, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getStringValue():this->getName();
        Cast<String>(obj)->update(v->toChars());
        return;
    }
    
    sp<_XmlValueIterator> iterator = getValueIterator();
    while (iterator->hasValue()) {
        sp<_XmlValue> node = iterator->getValue();
        Field field = obj->getField(node->getName());       

        if (field == nullptr) {
            LOG(ERROR) << "XmlValue reflect to fields is null!!!,name is "<<node->getName()->toChars();
            iterator->next();
            continue;
        }

        switch (field->getType()) {
            case st(Field)::Type::Long: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicLong());
            } break;

            case st(Field)::Type::Int: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicInt());
            } break;

            case st(Field)::Type::Bool: {
                String nodeValue = node->getStringValue();
                if (nodeValue->equalsIgnoreCase("true")) {
                    field->setValue(true);
                } else {
                    field->setValue(false);
                }
            } break;

            case st(Field)::Type::Double: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicDouble());
            } break;

            case st(Field)::Type::Float: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicFloat());
            } break;

            case st(Field)::Type::String: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue);
            } break;

            case st(Field)::Type::Byte: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicUint8());
            } break;

            case st(Field)::Type::Uint16: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicUint16());
            } break;

            case st(Field)::Type::Uint32: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicUint32());
            } break;

            case st(Field)::Type::Uint64: {
                String nodeValue = node->getStringValue();
                field->setValue(nodeValue->toBasicUint64());
            } break;

            case st(Field)::Type::Object: {
                auto newObject = field->createObject();
                node->reflectTo(newObject);
            } break;

            case st(Field)::Type::ArrayList: {
                auto newObject = field->createObject();
                node->reflectToArrayList(newObject);
            } break;

            case st(Field)::Type::HashMap: {
                auto newObject = field->createObject();
                node->reflectToHashMap(newObject);
            } break;

            default:
                LOG(ERROR)<<"XmlValue reflectTo,unknown type is "<<static_cast<int>(field->getType());
            break;
        }
        iterator->next();
    }
}

//import
void _XmlValue::importArrayListFrom(Object value) {
    int size = value->__getContainerSize("");
    for (int i = 0; i < size; i++) {
        XmlValue item = doc->newNode("tmp");
        item->mNeedUpdateName = true;
        auto newObject = value->__getListItemObject("", i);
        item->importFrom(newObject);
        appendNode(item);
    }
}
    
void _XmlValue::importHashMapFrom(Object hashmap) {
    //int size = this->__getContainerSize("");
    ArrayList<Pair<Object, Object>> members = hashmap->__getMapItemObjects("");
    auto iterator = members->getIterator();
    while (iterator->hasValue()) {
        Pair<Object, Object> node = iterator->getValue();
        Object key = node->getKey();
        Object value = node->getValue();
        sp<_XmlValue> item;
        if (IsInstance(Integer, key)) {
            Integer data = Cast<Integer>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Long, key)) {
            Long data = Cast<Long>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Boolean, key)) {
            Boolean data = Cast<Boolean>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Double, key)) {
            Double data = Cast<Double>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Float, key)) {
            Float data = Cast<Float>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Byte, key)) {
            Byte data = Cast<Byte>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Uint8, key)) {
            Uint8 data = Cast<Uint8>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Uint16, key)) {
            Uint16 data = Cast<Uint16>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Uint32, key)) {
            Uint32 data = Cast<Uint32>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(Uint64, key)) {
            Uint64 data = Cast<Uint64>(key);
            item = doc->newNode(createString(data->toValue()));
        } else if (IsInstance(String, key)) {
            item = doc->newNode(Cast<String>(key));
        } else {
            Trigger(TransformException, "not support key type")
        }
        
        item->importFrom(value);
        this->appendNode(item);
        iterator->next();
    }
}

void _XmlValue::importFrom(Object value) {
    try {
        if (value->__ReflectClassName()->sameAs("_ArrayList")) {
            this->importArrayListFrom(value);
            return;
        } else if (value->__ReflectClassName()->sameAs("_HashMap")) {
            this->importHashMapFrom(value);
            return;
        }
    } catch(...){}

    if (IsInstance(Integer, value)) {
        Integer data = Cast<Integer>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Long, value)) {
        Long data = Cast<Long>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Boolean, value)) {
        Boolean data = Cast<Boolean>(value);
        updateValue(data->toString());
        return;
    } else if (IsInstance(Double, value)) {
        Double data = Cast<Double>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Float, value)) {
        Float data = Cast<Float>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Byte, value)) {
        Byte data = Cast<Byte>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Uint8, value)) {
        Uint8 data = Cast<Uint8>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Uint16, value)) {
        Uint16 data = Cast<Uint16>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Uint32, value)) {
        Uint32 data = Cast<Uint32>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(Uint64, value)) {
        Uint64 data = Cast<Uint64>(value);
        updateValue(createString(data->toValue()));
        return;
    } else if (IsInstance(String, value)) {
        String data = Cast<String>(value);
        updateValue(data);
        return;
    }

    String reflectClassName = value->__ReflectClassName();
    if(mNeedUpdateName) {
        updateName(reflectClassName);
    }
    
    ArrayList<Field> fields = value->getAllFields();
    if (fields == nullptr) {
        LOG(ERROR) << "XmlVale importFrom fields is null!!!";
        return;
    }

    ArrayListIterator<Field> iterator = fields->getIterator();
    while (iterator->hasValue()) {
        Field field = iterator->getValue();
        String name = field->getName();
        sp<_XmlValue> refNode = nullptr;
        switch (field->getType()) {
            case st(Field)::Type::Long: {
                refNode = doc->newNode(name, createString(field->getLongValue()));
            } break;

            case st(Field)::Type::Int: {
                refNode = doc->newNode(name, createString(field->getIntValue()));
            } break;

            case st(Field)::Type::Bool: {
                refNode = doc->newNode(name, createString(field->getBoolValue()));
            } break;

            case st(Field)::Type::Double: {
                refNode = doc->newNode(name, createString(field->getDoubleValue()));
            } break;

            case st(Field)::Type::Float: {
                refNode = doc->newNode(name, createString(field->getFloatValue()));
            } break;

            case st(Field)::Type::String: {
                String str = field->getStringValue();
                if(str != nullptr) {
                    refNode = doc->newNode(name, str);
                }
            } break;

            case st(Field)::Type::Byte: {
                refNode = doc->newNode(name, createString(field->getByteValue()));
            } break;

            case st(Field)::Type::Uint16: {
                refNode = doc->newNode(name, createString(field->getUint16Value()));
            } break;

            case st(Field)::Type::Uint32: {
                refNode = doc->newNode(name, createString(field->getUint32Value()));
            } break;

            case st(Field)::Type::Uint64: {
                refNode = doc->newNode(name, createString(field->getUint64Value()));
            } break;

            case st(Field)::Type::Object: {
                auto newObject = field->getObjectValue();
                if(newObject != nullptr) {
                    refNode = doc->newNode(name);
                    refNode->importFrom(newObject);
                }
            } break;

            case st(Field)::Type::ArrayList: {
                auto newObject = field->getObjectValue();
                if(newObject != nullptr) {
                    refNode = doc->newNode(name);
                    refNode->importArrayListFrom(newObject);
                }
            } break;

            case st(Field)::Type::HashMap: {
                auto newObject = field->getObjectValue();
                if(newObject != nullptr) {
                    refNode = doc->newNode(name);
                    refNode->importHashMapFrom(newObject);
                }
            } break;

            default:
                LOG(ERROR)<<"XmlValue importFrom fail,unkown type is "<<static_cast<int>(field->getType());
            break;
        }

        if (refNode != nullptr) {
            this->appendNode(refNode);
        }
        iterator->next();
    }
}

} // namespace obotcha