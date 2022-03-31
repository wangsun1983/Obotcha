#include "YamlValue.hpp"
#include "YamlReader.hpp"
#include "Field.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

_YamlValue::_YamlValue() {
    // TODO
}

_YamlValue::_YamlValue(YAML::Node v) { 
    yamlNode = v; 
}

String _YamlValue::getTag() {
    return tag;
}

sp<_YamlValue> _YamlValue::getYamlValue(String tag) {
    if (tag == nullptr) {
        return nullptr;
    }

    try {
        const char *name = tag->toChars();
        YAML::Node newNode = yamlNode[name].as<YAML::Node>();

        YamlValue result = createYamlValue(newNode);
        result->tag = createString(yamlNode[name].Tag());
        return result;

    } catch (std::exception &e) {
        return nullptr;
    }

    return nullptr;
}

int _YamlValue::getIntAt(int index, int def) {
    try {
        int result = yamlNode[index].as<int>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}

String _YamlValue::getStringAt(int index, String def) {
    try {
        std::string result = yamlNode[index].as<std::string>();
        return createString(result);

    } catch (std::exception &e) {
        return def;
    }
}

double _YamlValue::getDoubleAt(int index, double def) {
    try {
        double result = yamlNode[index].as<double>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}

long _YamlValue::getLongAt(int index, long def) {
    try {
        long result = yamlNode[index].as<long>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}

bool _YamlValue::getBoolAt(int index, bool def) {
    try {
        bool result = yamlNode[index].as<bool>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}
    
sp<_YamlValue> _YamlValue::getYamlValueAt(int index) {
    try {
        YAML::Node newNode = yamlNode[index].as<YAML::Node>();

        YamlValue result = createYamlValue(newNode);
        result->tag = createString(yamlNode[index].Tag());
        return result;

    } catch (std::exception &e) {
        return nullptr;
    }
}

int _YamlValue::size() { 
    return yamlNode.size(); 
}

void _YamlValue::reflectToArrayList(Object obj) {
    int size = this->size();
    for(int i = 0;i<size;i++) {
        auto newObject = obj->__createListItemObject("");
        YamlValue v = this->getYamlValueAt(i);
        v->reflectTo(newObject);
        obj->__addListItemObject("", newObject);
    }
}

void _YamlValue::reflectToHashMap(Object obj) {
    int size = this->size();
    for(int i = 0;i<size;i++) {
        Pair<Object, Object> pair = obj->__createMapItemObject("");
        Object key = pair->getKey();
        YamlValue v = this->getYamlValueAt(i);

        v->reflectTo(key,ReflectName);
        Object pairValue = pair->getValue();
        v->reflectTo(pairValue);
        obj->__addMapItemObject("", key, pairValue);
    }
}

void _YamlValue::reflectTo(Object obj,int type) {
    try {
        if (obj->__ReflectClassName()->equals("_ArrayList")) {
            this->reflectToArrayList(obj);
            return;
        } else if (obj->__ReflectClassName()->equals("_HashMap")) {
            this->reflectToHashMap(obj);
            return;
        }
    }catch(...){}

    if (IsInstance(Integer, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Integer>(obj)->update(v->toBasicInt());
        return;
    } else if (IsInstance(Long, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Long>(obj)->update(v->toBasicLong());
        return;
    } else if (IsInstance(Boolean, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        if (v->equalsIgnoreCase("true")) {
            Cast<Boolean>(obj)->update(true);
        } else {
            Cast<Boolean>(obj)->update(false);
        }
        return;
    } else if (IsInstance(Double, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Double>(obj)->update(v->toBasicDouble());
        return;
    } else if (IsInstance(Float, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Float>(obj)->update(v->toBasicFloat());
        return;
    } else if (IsInstance(Byte, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Byte>(obj)->update(v->toBasicByte());
        return;
    } else if (IsInstance(Uint8, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Uint8>(obj)->update(v->toBasicUint8());
        return;
    } else if (IsInstance(Uint16, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Uint16>(obj)->update(v->toBasicUint16());
        return;
    } else if (IsInstance(Uint32, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Uint32>(obj)->update(v->toBasicUint32());
        return;
    } else if (IsInstance(Uint64, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<Uint64>(obj)->update(v->toBasicUint64());
        return;
    } else if (IsInstance(String, obj)) {
        String v = (type == ReflectValue)?this->getStringAt(0,nullptr):createString(this->yamlNode[0].Tag());
        Cast<String>(obj)->update(v->toChars());
        return;
    }

    int size = this->size();
    for(int i = 0;i < size;i++) {
        YamlValue v = this->getYamlValueAt(i);
        Field field = obj->getField(v->getTag());
        if(field == nullptr) {
            continue;
        }

        switch (field->getType()) {
            case st(Field)::FieldTypeLong: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicLong());
            } break;

            case st(Field)::FieldTypeInt: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicInt());
            } break;

            case st(Field)::FieldTypeBool: {
                String value = v->getStringAt(0,nullptr);
                if (value->equalsIgnoreCase("true")) {
                    field->setValue(true);
                } else {
                    field->setValue(false);
                }
            } break;

            case st(Field)::FieldTypeDouble: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicDouble());
            } break;

            case st(Field)::FieldTypeFloat: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicFloat());
            } break;

            case st(Field)::FieldTypeString: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value);
            } break;

            case st(Field)::FieldTypeUint8: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicUint8());
            } break;

            case st(Field)::FieldTypeUint16: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicUint16());
            } break;

            case st(Field)::FieldTypeUint32: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicUint32());
            } break;

            case st(Field)::FieldTypeUint64: {
                String value = v->getStringAt(0,nullptr);
                field->setValue(value->toBasicUint64());
            } break;

            case st(Field)::FieldTypeObject: {
                auto newObject = field->createObject();
                YamlValue nextV = v->getYamlValueAt(0);
                nextV->reflectTo(newObject);
            } break;

            case st(Field)::FieldTypeArrayList: {
                auto newObject = field->createObject();
                YamlValue nextV = v->getYamlValueAt(0);
                nextV->reflectToArrayList(newObject);
            } break;

            case st(Field)::FieldTypeHashMap: {
                auto newObject = field->createObject();
                YamlValue nextV = v->getYamlValueAt(0);
                nextV->reflectToHashMap(newObject);
            } break;
        }
    }
}

void importFrom(Object obj) {
    //TODO
}


_YamlValue::~_YamlValue() {}

} // namespace obotcha