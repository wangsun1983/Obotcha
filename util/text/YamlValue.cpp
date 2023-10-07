#include "YamlValue.hpp"
#include "YamlReader.hpp"
#include "Field.hpp"
#include "OStdInstanceOf.hpp"
#include "Error.hpp"
#include "TransformException.hpp"
#include "Log.hpp"

namespace obotcha {

_YamlValue::_YamlValue(YAML::Node v):yamlNode(v) {
}

String _YamlValue::getTag() const {
    return tag;
}

void _YamlValue::setTag(String p) {
    tag = p;
}

size_t _YamlValue::size() const { 
    return yamlNode.size(); 
}

void _YamlValue::set(String key,String value) {
    if(key == nullptr) {
        yamlNode = value->toChars();
    } else {
        yamlNode[key->toChars()] = value->toChars();
    }
}

void _YamlValue::set(String key,YamlValue value) {
    if(key == nullptr) {
        yamlNode = value->yamlNode;
    } else {
        yamlNode[key->toChars()] = value->yamlNode;
    }
}

void _YamlValue::set(int index,String value) {
    yamlNode[index] = value->toChars();
}
void _YamlValue::set(int index,YamlValue value) {
    yamlNode[index] = value->yamlNode;
}

void _YamlValue::set(String value) {
    yamlNode = value->toChars();
}

void _YamlValue::set(YamlValue value) {
    yamlNode = value->yamlNode;
}

void _YamlValue::pushBack(String value) {
    yamlNode.push_back(value->toChars());
}

void _YamlValue::pushBack(YamlValue value) {
    yamlNode.push_back(value->yamlNode);
}

void _YamlValue::reflectToArrayList(Object obj) {
    int size = this->size();
    for(int i = 0;i<size;i++) {
        auto newObject = obj->__createListItemObject("");
        YamlValue v = this->getAt<YamlValue>(i);
        v->reflectTo(newObject);
        obj->__addListItemObject("", newObject);
    }
}

void _YamlValue::reflectToHashMap(Object obj) {
    auto iterator = yamlNode.begin();
    while(iterator != yamlNode.end()) {
        Pair<Object, Object> pair = obj->__createMapItemObject("");
        YamlValue keyNode = createYamlValue(iterator->first);
        Object key = pair->getKey();
        keyNode->reflectTo(key,st(Text)::Syntax::Name);

        YamlValue valueNode = createYamlValue(iterator->second);
        Object pairValue = pair->getValue();
        valueNode->reflectTo(pairValue);

        obj->__addMapItemObject("", key, pairValue);
        iterator++;
    }
}

void _YamlValue::reflectTo(Object obj,st(Text)::Syntax type) {
    try {
        if (obj->__ReflectClassName()->sameAs("_ArrayList")) {
            this->reflectToArrayList(obj);
            return;
        } else if (obj->__ReflectClassName()->sameAs("_HashMap")) {
            this->reflectToHashMap(obj);
            return;
        }
    } catch(MethodNotSupportException &){}

    String v = nullptr;
    try {
        auto nodevalue = yamlNode.begin()->second.as<std::string>();
        auto nodename = yamlNode.begin()->first.as<std::string>();    
        v = (type == st(Text)::Syntax::Value)?
                createString(nodevalue):createString(nodename);
    } catch(YAML::TypedBadConversion<std::string> &) {
        try {
            v = createString(yamlNode.as<std::string>());
        } catch(YAML::TypedBadConversion<std::string> &) {}
    }
        
    if(v != nullptr) {
        if (IsInstance(Integer, obj)) {
            Cast<Integer>(obj)->update(v->toBasicInt());
            return;
        } else if (IsInstance(Long, obj)) {
            Cast<Long>(obj)->update(v->toBasicLong());
            return;
        } else if (IsInstance(Boolean, obj)) {
            if (v->equalsIgnoreCase("true")) {
                Cast<Boolean>(obj)->update(true);
            } else {
                Cast<Boolean>(obj)->update(false);
            }
            return;
        } else if (IsInstance(Double, obj)) {
            Cast<Double>(obj)->update(v->toBasicDouble());
            return;
        } else if (IsInstance(Float, obj)) {
            Cast<Float>(obj)->update(v->toBasicFloat());
            return;
        } else if (IsInstance(Byte, obj)) {
            Cast<Byte>(obj)->update(v->toBasicByte());
            return;
        } else if (IsInstance(Uint8, obj)) {
            Cast<Uint8>(obj)->update(v->toBasicUint8());
            return;
        } else if (IsInstance(Uint16, obj)) {
            Cast<Uint16>(obj)->update(v->toBasicUint16());
            return;
        } else if (IsInstance(Uint32, obj)) {
            Cast<Uint32>(obj)->update(v->toBasicUint32());
            return;
        } else if (IsInstance(Uint64, obj)) {
            Cast<Uint64>(obj)->update(v->toBasicUint64());
            return;
        } else if (IsInstance(String, obj)) {
            Cast<String>(obj)->update(v->toChars());
            return;
        }
    }

    ArrayList<Field> fields = obj->getAllFields();
    auto iterator = fields->getIterator();

    while(iterator->hasValue()) {
        Field field = iterator->getValue();
        switch (field->getType()) {
            case st(Field)::Type::Long: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicLong());
            } break;

            case st(Field)::Type::Int: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicInt());
            } break;

            case st(Field)::Type::Bool: {
                String value = get<String>(field->getName());
                if (value->equalsIgnoreCase("true")) {
                    field->setValue(true);
                } else {
                    field->setValue(false);
                }
            } break;

            case st(Field)::Type::Double: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicDouble());
            } break;

            case st(Field)::Type::Float: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicFloat());
            } break;

            case st(Field)::Type::String: {
                String value = get<String>(field->getName());
                field->setValue(value);
            } break;

            case st(Field)::Type::Byte: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicUint8());
            } break;

            case st(Field)::Type::Uint16: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicUint16());
            } break;

            case st(Field)::Type::Uint32: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicUint32());
            } break;

            case st(Field)::Type::Uint64: {
                String value = get<String>(field->getName());
                field->setValue(value->toBasicUint64());
            } break;

            case st(Field)::Type::Object: {
                auto newObject = field->createObject();
                YamlValue nextV = get<YamlValue>(field->getName());
                nextV->setTag(field->getName());
                nextV->reflectTo(newObject);
            } break;

            case st(Field)::Type::ArrayList: {
                auto newObject = field->createObject();
                YamlValue nextV = get<YamlValue>(field->getName());
                nextV->setTag(field->getName());
                nextV->reflectToArrayList(newObject);
            } break;

            case st(Field)::Type::HashMap: {
                auto newObject = field->createObject();
                YamlValue nextV = get<YamlValue>(field->getName());
                nextV->setTag(field->getName());
                nextV->reflectToHashMap(newObject);
            } break;

            default:
                LOG(ERROR)<<"YamlValue,reflectTo failed,unknown type is "<<static_cast<int>(field->getType());
            break;
        }

        iterator->next();
    }
}

void _YamlValue::importArrayListFrom(Object value) {
    auto size = value->__getContainerSize("");
    for (size_t i = 0; i < size; i++) {
        YamlValue node = createYamlValue();
        auto newObject = value->__getListItemObject("", i);
        node->importFrom(newObject);
        this->pushBack(node);
    }
}

void _YamlValue::importHashMapFrom(Object hashmap) {
    ArrayList<Pair<Object, Object>> members = hashmap->__getMapItemObjects("");
    auto iterator = members->getIterator();
    while (iterator->hasValue()) {
        Pair<Object, Object> node = iterator->getValue();
        Object key = node->getKey();
        Object value = node->getValue();
        String keyStr = nullptr;
        if (IsInstance(Integer, key)) {
            Integer data = Cast<Integer>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Long, key)) {
            Long data = Cast<Long>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Boolean, key)) {
            Boolean data = Cast<Boolean>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Double, key)) {
            Double data = Cast<Double>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Float, key)) {
            Float data = Cast<Float>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Byte, key)) {
            Byte data = Cast<Byte>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Uint8, key)) {
            Uint8 data = Cast<Uint8>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Uint16, key)) {
            Uint16 data = Cast<Uint16>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Uint32, key)) {
            Uint32 data = Cast<Uint32>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(Uint64, key)) {
            Uint64 data = Cast<Uint64>(key);
            keyStr = createString(data->toValue());
        } else if (IsInstance(String, key)) {
            keyStr = Cast<String>(key);
        } else {
            Trigger(TransformException, "not support key type")
        }
        
        YamlValue v = createYamlValue();
        v->importFrom(value);
        set(keyStr,v);

        iterator->next();
    }
}

void _YamlValue::importFrom(Object value) {
    try {
        if (value->__ReflectClassName()->sameAs("_ArrayList")) {
            this->importArrayListFrom(value);
            return;
        } else if (value->__ReflectClassName()->sameAs("_HashMap")) {
            this->importHashMapFrom(value);
            return;
        }
    } catch(MethodNotSupportException &){}

    if (IsInstance(Integer, value)) {
        Integer data = Cast<Integer>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Long, value)) {
        Long data = Cast<Long>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Boolean, value)) {
        Boolean data = Cast<Boolean>(value);
        set(tag,data->toString());
        return;
    } else if (IsInstance(Double, value)) {
        Double data = Cast<Double>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Float, value)) {
        Float data = Cast<Float>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Byte, value)) {
        Byte data = Cast<Byte>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Uint8, value)) {
        Uint8 data = Cast<Uint8>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Uint16, value)) {
        Uint16 data = Cast<Uint16>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Uint32, value)) {
        Uint32 data = Cast<Uint32>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(Uint64, value)) {
        Uint64 data = Cast<Uint64>(value);
        set(tag,createString(data->toValue()));
        return;
    } else if (IsInstance(String, value)) {
        String data = Cast<String>(value);
        set(tag,data);
        return;
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
        switch (field->getType()) {
            case st(Field)::Type::Long: {
                set(name, createString(field->getLongValue()));
            } break;

            case st(Field)::Type::Int: {
                set(name, createString(field->getIntValue()));
            } break;

            case st(Field)::Type::Bool: {
                set(name, createString(field->getBoolValue()));
            } break;

            case st(Field)::Type::Double: {
                set(name, createString(field->getDoubleValue()));
            } break;

            case st(Field)::Type::Float: {
                set(name, createString(field->getFloatValue()));
            } break;

            case st(Field)::Type::String: {
                set(name, field->getStringValue());
            } break;

            case st(Field)::Type::Byte: {
                set(name, createString(field->getByteValue()));
            } break;

            case st(Field)::Type::Uint16: {
                set(name, createString(field->getUint16Value()));
            } break;

            case st(Field)::Type::Uint32: {
                set(name, createString(field->getUint32Value()));
            } break;

            case st(Field)::Type::Uint64: {
                set(name, createString(field->getUint64Value()));
            } break;

            case st(Field)::Type::Object: {
                auto newObject = field->getObjectValue();
                YamlValue newValue = createYamlValue();
                newValue->setTag(name);
                newValue->importFrom(newObject);
                set(name,newValue);
            } break;

            case st(Field)::Type::ArrayList: {
                auto newObject = field->getObjectValue();
                YamlValue newValue = createYamlValue();
                newValue->setTag(name);
                newValue->importArrayListFrom(newObject);
                set(name,newValue);
            } break;

            case st(Field)::Type::HashMap: {
                auto newObject = field->getObjectValue();
                YamlValue newValue = createYamlValue();
                newValue->setTag(name);
                newValue->importHashMapFrom(newObject);
                set(name,newValue);
            } break;

            default:
                LOG(ERROR) << "YamlValue,importFrom failed,unknow type is " << static_cast<int>(field->getType());
            break;
        }
        iterator->next();
    }
}

} // namespace obotcha