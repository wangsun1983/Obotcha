#include "json/value.h"

#include "ArrayList.hpp"
#include "JsonValue.hpp"
#include "Field.hpp"
#include "OStdInstanceOf.hpp"
#include "Log.hpp"

namespace obotcha {

_JsonValue::_JsonValue(const Json::Value &v, String name):mName(name),jvalue(v) {
}

_JsonValue::_JsonValue(const sp<_JsonValue> &v, String name):_JsonValue(v->jvalue,name) {
}

bool _JsonValue::put(String tag,sp<_JsonValue> value) {
    try {
        jvalue[tag->toChars()] = value->jvalue;
        return true;
    } catch(Json::LogicError &err) {
        LOG(ERROR)<<"json value put ["<<tag->toChars()<<"] failed,reason is "
                  <<err.what();
    }
    return false;
}

JsonValue _JsonValue::remove(String tag) {
    JsonValue v = JsonValue::New();
    jvalue.removeMember(tag->toChars(), &v->jvalue);
    return v;
}

JsonValue _JsonValue::removeAt(int index) {
    JsonValue v = JsonValue::New();
    jvalue.removeIndex(index, &v->jvalue);
    return v;
}

String _JsonValue::getName() const { 
    return mName;
}

String _JsonValue::getString(String tag) const { 
    return getString(tag->toChars());
}

String _JsonValue::getString(const char *tag) const {
    return jvalue.isMember(tag)?String::New(jvalue[tag].asString()):nullptr;
}

String _JsonValue::getString() const {
    return String::New(jvalue.asString());
}

Integer _JsonValue::getInteger(String tag) const {
    return getInteger(tag->toChars());
}

Integer _JsonValue::getInteger(const char *tag) const {
    return jvalue.isMember(tag)?Integer::New(jvalue[tag].asInt()):nullptr;
}

Integer _JsonValue::getInteger() const {
    return Integer::New(jvalue.asInt());
}

bool _JsonValue::isEmpty() const { 
    return jvalue.empty();
}

Uint64 _JsonValue::getUint64(String tag) const { 
    return getUint64(tag->toChars());
}

Uint64 _JsonValue::getUint64(const char *tag) const {
    if (tag != nullptr && jvalue.isMember(tag)) {
        Json::Value va = jvalue[tag];
        if (!va.isNull()) {
            return Uint64::New(va.asUInt64());
        }
    }
    return nullptr;
}

Uint64 _JsonValue::getUint64() const {
    return jvalue.isNull()?nullptr:Uint64::New(jvalue.asUInt64());
}

Long _JsonValue::getLong(String tag) const { 
    return getLong(tag->toChars());
}

Long _JsonValue::getLong(const char *tag) const {
    return jvalue.isMember(tag)?Long::New(jvalue[tag].asLargestInt()):nullptr;
}

Long _JsonValue::getLong() const {
    return Long::New(jvalue.asLargestInt());
}

int _JsonValue::size() const { 
    return jvalue.size();
}

Boolean _JsonValue::getBoolean(String tag) const {
    return getBoolean(tag->toChars());
}

Boolean _JsonValue::getBoolean(const char *tag) const {
    return jvalue.isMember(tag)?Boolean::New(jvalue[tag].asBool()):nullptr;
}

Boolean _JsonValue::getBoolean() const {
    return Boolean::New(jvalue.asBool());
}

Double _JsonValue::getDouble(String tag) const { 
    return getDouble(tag->toChars());
}

Double _JsonValue::getDouble(const char *tag) const {
    return jvalue.isMember(tag)?Double::New(jvalue[tag].asDouble()):nullptr;
}

Double _JsonValue::getDouble() const {
    return Double::New(jvalue.asDouble());
}

sp<_JsonValue> _JsonValue::getValue(String tag) {
    return getValue(tag->toChars());
}

sp<_JsonValue> _JsonValue::getValue(const char *tag) {
    return jvalue.isMember(tag)?JsonValue::New(jvalue[tag], String::New(tag)):nullptr;
}

bool _JsonValue::contains(String tag) const {
    return (tag == nullptr)?false:jvalue.isMember(tag->toChars());
}

bool _JsonValue::isBool() const { 
    return jvalue.isBool();
}

bool _JsonValue::isInt() const { 
    return jvalue.isInt();
}

bool _JsonValue::isUint64() const { 
    return jvalue.isUInt64();
}

bool _JsonValue::isString() const { 
    return jvalue.isString();
}

bool _JsonValue::isDouble() const { 
    return jvalue.isDouble();
}

bool _JsonValue::isArray() const { 
    return jvalue.isArray();
}

bool _JsonValue::isObject() const { 
    return jvalue.isObject();
}

bool _JsonValue::isNull() const {
    if(jvalue.isArray() || jvalue.isObject()) {
        return jvalue.size() == 0;
    }
    return jvalue.isNull();
}

void _JsonValue::append(sp<_JsonValue> value) { 
    jvalue.append(value->jvalue);
}

sp<_JsonValue> _JsonValue::getValueAt(int index) {
    if (Json::Value v = jvalue[index];!v.isNull()) {
        return jvalue.isObject()?
                    JsonValue::New(v, String::New(jvalue.getMemberNames()[index])):JsonValue::New(v);
    }
    
    return nullptr;
}

sp<_JsonValue> _JsonValue::getListItemAt(unsigned int index) {
    Json::Value v = jvalue[index];
    return v.isNull()?nullptr:JsonValue::New(v);
}

String _JsonValue::getStringAt(int index) {
    Json::Value v = jvalue[index];
    return v.isNull()?nullptr:String::New(v.asString());
}

Integer _JsonValue::getIntegerAt(int index) {
    Json::Value v = jvalue[index];
    return v.isNull()?nullptr:String::New(v.asString())->toInteger();
}

Boolean _JsonValue::getBooleanAt(int index) {
    Json::Value v = jvalue[index];
    return v.isNull()?nullptr:Boolean::New(v.asBool());
}

Double _JsonValue::getDoubleAt(int index) {
    Json::Value v = jvalue[index];
    return v.isNull()?nullptr:Double::New(v.asDouble());
}

String _JsonValue::toString() { 
    return String::New(jvalue.toStyledString());
}

void _JsonValue::reflectTo(Object obj,st(Text)::Syntax type) {
    //if it is a Lang/Container class
    try {
        if (obj->__ReflectClassName()->sameAs("_ArrayList")) {
            reflectToArrayList(obj);
            return;
        } else if (obj->__ReflectClassName()->sameAs("_HashMap")) {
            reflectToHashMap(obj);
            return;
        }
    } catch(MethodNotSupportException &){} 

    if (IsInstance(Integer, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Integer>(obj)->update(v->toBasicInt());
        return;
    } else if (IsInstance(Long, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Long>(obj)->update(v->toBasicLong());
        return;
    } else if (IsInstance(Boolean, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Boolean>(obj)->update(v->toBasicBool());
        return;
    } else if (IsInstance(Double, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Double>(obj)->update(v->toBasicDouble());
        return;
    } else if (IsInstance(Float, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Float>(obj)->update(v->toBasicFloat());
        return;
    } else if (IsInstance(Byte, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Byte>(obj)->update(v->toBasicByte());
        return;
    } else if (IsInstance(Uint8, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Uint8>(obj)->update(v->toBasicUint8());
        return;
    } else if (IsInstance(Uint16, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Uint16>(obj)->update(v->toBasicUint16());
        return;
    } else if (IsInstance(Uint32, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Uint32>(obj)->update(v->toBasicUint32());
        return;
    } else if (IsInstance(Uint64, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<Uint64>(obj)->update(v->toBasicUint64());
        return;
    } else if (IsInstance(String, obj)) {
        String v = (type == st(Text)::Syntax::Value)?this->getString():this->getName();
        Cast<String>(obj)->update(v->toChars());
        return;
    }

    sp<_JsonValueIterator> iterator = this->getIterator();
    while (iterator->hasValue()) {
        String key = iterator->getTag();
        Field field = obj->getField(key);
        if (field == nullptr) {
            iterator->next();
            continue;
        }
        std::string name = field->getName()->getStdString();
        JsonValue jsonnode = iterator->getValue();
        switch (field->getType()) {
            case st(Field)::Type::Long: {
                field->setValue(jsonnode->getString()->toBasicLong());
            } break;

            case st(Field)::Type::Int: {
                field->setValue(jsonnode->getString()->toBasicInt());
            } break;

            case st(Field)::Type::Byte: {
                field->setValue(jsonnode->getString()->toBasicByte());
            } break;

            case st(Field)::Type::Bool: {
                field->setValue(jsonnode->getString()->toBasicBool());
            } break;

            case st(Field)::Type::Double: {
                field->setValue(jsonnode->getString()->toBasicDouble());
            } break;

            case st(Field)::Type::Float: {
                field->setValue(jsonnode->getString()->toBasicFloat());
            } break;

            case st(Field)::Type::String: {
                field->setValue(jsonnode->getString());
            } break;

            case st(Field)::Type::Uint16: {
                field->setValue(jsonnode->getString()->toBasicUint16());
            } break;

            case st(Field)::Type::Uint32: {
                field->setValue(jsonnode->getString()->toBasicUint32());
            } break;

            case st(Field)::Type::Uint64: {
                field->setValue(jsonnode->getString()->toBasicUint64());
            } break;

            case st(Field)::Type::Object: {
                // create Objectt
                sp<_Object> newObject = field->createObject();
                jsonnode->reflectTo(newObject);
            } break;

            case st(Field)::Type::ArrayList: {
                Object newObject = field->createObject();
                jsonnode->reflectToArrayList(newObject);
            } break;

            case st(Field)::Type::HashMap: {
                Object newObject = field->createObject();
                jsonnode->reflectToHashMap(newObject);
            } break;

            case st(Field)::Type::UnKnow: {
                LOG(ERROR)<<"JsonValue reflectTo unknow type";
            } break;
        }
        iterator->next();
    }
}

void _JsonValue::importFrom(Object value) {
    try {
        if (value->__ReflectClassName()->sameAs("_ArrayList")) {
            importFromArrayList(nullptr,value);
            return;
        } else if (value->__ReflectClassName()->sameAs("_HashMap")) {
            importFromHashMap(nullptr,value);
            return;
        }
    } catch(MethodNotSupportException &){}

    if (IsInstance(Integer, value)) {
        jvalue = Cast<Integer>(value)->toValue();
        return;
    } else if (IsInstance(Long, value)) {
        jvalue = Cast<Long>(value)->toValue();
        return;
    } else if (IsInstance(Boolean, value)) {
        jvalue = Cast<Boolean>(value)->toValue();
        return;
    } else if (IsInstance(Double, value)) {
        jvalue = Cast<Double>(value)->toValue();
        return;
    } else if (IsInstance(Float, value)) {
        jvalue = Cast<Float>(value)->toValue();
        return;
    } else if (IsInstance(Byte, value)) {
        jvalue = (uint64_t)(Cast<Byte>(value)->toValue());
        return;
    } else if (IsInstance(Uint8, value)) {
        jvalue = (uint64_t)(Cast<Uint8>(value)->toValue());
        return;
    } else if (IsInstance(Uint16, value)) {
        jvalue = (uint64_t)(Cast<Uint16>(value)->toValue());
        return;
    } else if (IsInstance(Uint32, value)) {
        jvalue = (uint64_t)(Cast<Uint32>(value)->toValue());
        return;
    } else if (IsInstance(Uint64, value)) {
        jvalue = Cast<Uint64>(value)->toValue();
        return;
    } else if (IsInstance(String, value)) {
        jvalue = Cast<String>(value)->getStdString();
        return;
    }

    ArrayList<Field> fields = value->getAllFields();
    if (fields == nullptr) {
        LOG(ERROR) << "import class has no reflect filed";
        return;
    }
    ArrayListIterator<Field> iterator = fields->getIterator();
    while (iterator->hasValue()) {
        Field field = iterator->getValue();
        String name = field->getName();
        switch (field->getType()) {
            case st(Field)::Type::Long: {
                this->put(name, field->getLongValue());
            } break;

            case st(Field)::Type::Int: {
                this->put(name, field->getIntValue());
            } break;

            case st(Field)::Type::Bool: {
                this->put(name, field->getBoolValue());
            } break;

            case st(Field)::Type::Double: {
                this->put(name, field->getDoubleValue());
            } break;

            case st(Field)::Type::Float: {
                this->put(name, field->getFloatValue());
            } break;

            case st(Field)::Type::String: {
                this->put(name, field->getStringValue());
            } break;

            case st(Field)::Type::Byte: {
                this->put(name,field->getByteValue());
            } break;

            case st(Field)::Type::Uint16: {
                this->put(name,field->getUint16Value());
            } break;

            case st(Field)::Type::Uint32: {
                this->put(name,field->getUint32Value());
            } break;

            case st(Field)::Type::Uint64: {
                this->put(name,field->getUint64Value());
            } break;

            case st(Field)::Type::Object: {
                // check whether it is Number
                auto newObject = field->getObjectValue();
                if(newObject != nullptr) {
                    JsonValue newValue = JsonValue::New();
                    newValue->importFrom(newObject);
                    this->put(name, newValue);
                }
            }break;

            case st(Field)::Type::ArrayList: {
                auto newObject = field->getObjectValue();
                if(newObject != nullptr) {
                    importFromArrayList(name,newObject);
                }
            } break;

            case st(Field)::Type::HashMap: {
                auto newObject = field->getObjectValue();
                if(newObject != nullptr) {
                    importFromHashMap(name,newObject);
                }
            } break;

            case st(Field)::Type::UnKnow: {
                LOG(ERROR)<<"JsonValue importFrom unknow type";
            } break;
        }
        iterator->next();
    }
}

void _JsonValue::reflectToArrayList(Object obj) {
    int size = this->size();
    for (int index = 0; index < size; index++) {
        auto newObject = obj->__createListItemObject("");
        JsonValue value = this->getListItemAt(index);
        value->reflectTo(newObject);
        obj->__addListItemObject("", newObject);
    }
}

void _JsonValue::reflectToHashMap(Object obj) {
    sp<_JsonValueIterator> iterator = this->getIterator();
    while (iterator->hasValue()) {
        JsonValue value = iterator->getValue();
        String tag = iterator->getTag();
        Pair<Object, Object> pair = obj->__createMapItemObject("");

        Object key = pair->getKey();
        value->reflectTo(key,st(Text)::Syntax::Name);

        Object pairValue = pair->getValue();
        value->reflectTo(pairValue);

        obj->__addMapItemObject("", key, pairValue);
        iterator->next();
    }
}

void _JsonValue::importFromArrayList(String name,Object value) {
    size_t size = value->__getContainerSize("");
    JsonValue arrayNode = nullptr;
    if(name != nullptr) {
        arrayNode = JsonValue::New();
    } else {
        arrayNode = AutoClone(this);
    }

    for (size_t i = 0; i < size; i++) {
        JsonValue item = JsonValue::New();
        auto newObject = value->__getListItemObject("", i);
        item->importFrom(newObject);
        arrayNode->append(item);
    }

    if(name != nullptr) {
        this->put(name, arrayNode);
    }
}

void _JsonValue::importFromHashMap(String name,Object value) {
    size_t size = value->__getContainerSize("");
    ArrayList<Pair<Object, Object>> members = value->__getMapItemObjects("");
    JsonValue mapItems = nullptr;

    if(name != nullptr){
        mapItems = JsonValue::New();
    } else {
        mapItems = AutoClone(this);
    }

    for (size_t i = 0;i < size;i++) {
        Pair<Object, Object> pair = members->get(i);
        Object key = pair->getKey();
        Object objvalue = pair->getValue();
        JsonValue newValue = JsonValue::New();
        newValue->importFrom(objvalue);

        String keyStr = nullptr;
        if (IsInstance(Integer, key)) {
            keyStr = String::New(Cast<Integer>(key));
        } else if (IsInstance(Long, key)) {
            keyStr = String::New(Cast<Long>(key));
        } else if (IsInstance(Boolean, key)) {
            keyStr = String::New(Cast<Boolean>(key));
        } else if (IsInstance(Double, key)) {
            keyStr = String::New(Cast<Double>(key));
        } else if (IsInstance(Float, key)) {
            keyStr = String::New(Cast<Float>(key));
        } else if (IsInstance(Byte, key)) {
            keyStr = String::New(Cast<Byte>(key));
        } else if (IsInstance(Uint8, key)) {
            keyStr = String::New(Cast<Uint8>(key));
        } else if (IsInstance(Uint16, key)) {
            keyStr = String::New(Cast<Uint16>(key));
        } else if (IsInstance(Uint32, key)) {
            keyStr = String::New(Cast<Uint32>(key));
        } else if (IsInstance(Uint64, key)) {
            keyStr = String::New(Cast<Uint64>(key));
        } else if (IsInstance(String, key)) {
            keyStr = Cast<String>(key);
        }

        if(keyStr != nullptr) {
            mapItems->put(keyStr, newValue);
        }
    }

    if(name != nullptr) {
        this->put(name,mapItems);
    }
}

sp<_JsonValueIterator> _JsonValue::getIterator() {
    auto v = AutoClone(this);
    return JsonValueIterator::New(v);
}

//---- JsonValueIterator ----
_JsonValueIterator::_JsonValueIterator(const JsonValue &v):value(v) {
    if (!v->jvalue.isArray()) {
        mMembers = v->jvalue.getMemberNames();
        isArrayMember = false;
        size = mMembers.size();
    } else {
        isArrayMember = true;
        size = v->jvalue.size();
    }
}

String _JsonValueIterator::getTag() {
    return (index < size)?String::New(mMembers[index]):nullptr;
}

bool _JsonValueIterator::hasValue() const { 
    return index < size;
}

bool _JsonValueIterator::next() {
    index++;
    if(index > size) {
        index = size;
        return false;
    }

    return true;
}

bool _JsonValueIterator::isBool() {
    return isArrayMember?
            (value->jvalue)[index].isBool():(value->jvalue)[mMembers[index]].isBool();
}

bool _JsonValueIterator::isInt() {
    return isArrayMember?
            (value->jvalue)[index].isInt():(value->jvalue)[mMembers[index]].isInt();
}

bool _JsonValueIterator::isString() {
    return isArrayMember?
            (value->jvalue)[index].isString():(value->jvalue)[mMembers[index]].isString();
}

bool _JsonValueIterator::isDouble() {
    return isArrayMember?
            (value->jvalue)[index].isDouble():(value->jvalue)[mMembers[index]].isDouble();
}

bool _JsonValueIterator::isArray() {
    return isArrayMember?
            (value->jvalue)[index].isArray():(value->jvalue)[mMembers[index]].isArray();
}

bool _JsonValueIterator::isObject() {
    return isArrayMember?
            (value->jvalue)[index].isObject():(value->jvalue)[mMembers[index]].isObject();
}

sp<_JsonValue> _JsonValueIterator::getValue() {
    return isArrayMember?
            JsonValue::New((value->jvalue)[index]):
            JsonValue::New((value->jvalue)[mMembers[index]],String::New(mMembers[index]));
}

String _JsonValueIterator::getString() {
    return isArrayMember?
            String::New((value->jvalue)[index].asString()):
            String::New((value->jvalue)[mMembers[index]].asString());
}

Integer _JsonValueIterator::getInteger() {
    return isArrayMember?
            Integer::New((value->jvalue)[index].asInt()):
            Integer::New((value->jvalue)[mMembers[index]].asInt());
}

Boolean _JsonValueIterator::getBoolean() {
    return isArrayMember?
            Boolean::New((value->jvalue)[index].asBool()):
            Boolean::New((value->jvalue)[mMembers[index]].asBool());
}

Double _JsonValueIterator::getDouble() {
    return isArrayMember?
            Double::New((value->jvalue)[index].asDouble()):
            Double::New((value->jvalue)[mMembers[index]].asDouble());
}

sp<_JsonValue> _JsonValueIterator::getObject() {
    return isArrayMember?
            JsonValue::New((value->jvalue)[index]):
            JsonValue::New((value->jvalue)[mMembers[index]],String::New(mMembers[index]));
} 

}// namespace obotcha