#include "IniValue.hpp"
#include "Field.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

String _IniValue::RootSectionName = createString("__root__");

_IniValue::_IniValue() {
    mValues = createHashMap<String, HashMap<String, String>>();
    dict = dictionary_new(0);;
}

void _IniValue::reflectTo(Object obj) {
    auto iterator = mValues->getIterator();
    while(iterator->hasValue()) {
        String section = iterator->getKey();
        HashMap<String,String> values = iterator->getValue();
        if(section->equals(RootSectionName)) {
            reflectWithObject(obj,values);
        } else {
            Field f = obj->getField(section);
            if(f != nullptr) {
                Object newObject = f->createObject();
                reflectWithObject(newObject,values);
            }
        }
        iterator->next();
    }
}

/*
set value:
iniparser_set(ini, 
     "section:key2", 
     "value2");

iniparser_set(ini, 
     "section:key1", 
     NULL);

new section:
iniparser_set(ini, 
     "section", 
     NULL);
*/

void _IniValue::importFrom(Object obj,String section) {
    mValues->clear();

    ArrayList<Field> fields = obj->getAllFields();
    auto iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        String sectionKey = nullptr;
        if(section != nullptr) {
            dictionary_set(dict, section->toChars(), "");
            sectionKey = section->append(":",f->getName());
        } else {
            dictionary_set(dict, RootSectionName->toChars(), "");
            sectionKey = RootSectionName->append(":",f->getName());;
        }

        switch (f->getType()) {
            case st(Field)::FieldTypeLong: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getLongValue())->toChars());
            } break;

            case st(Field)::FieldTypeInt: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getIntValue())->toChars());
            } break;

            case st(Field)::FieldTypeByte: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getByteValue())->toChars());
            } break;

            case st(Field)::FieldTypeBool: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getBoolValue())->toChars());
            } break;

            case st(Field)::FieldTypeDouble: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getDoubleValue())->toChars());
            } break;

            case st(Field)::FieldTypeFloat: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getFloatValue())->toChars());
            } break;

            case st(Field)::FieldTypeString: {
                iniparser_set(dict,sectionKey->toChars(),f->getStringValue()->toChars());
            } break;

            case st(Field)::FieldTypeUint16: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getUint16Value())->toChars());
            } break;

            case st(Field)::FieldTypeUint32: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getUint32Value())->toChars());
            } break;

            case st(Field)::FieldTypeUint64: {
                iniparser_set(dict,sectionKey->toChars(),createString(f->getUint64Value())->toChars());
            } break;

            case st(Field)::FieldTypeObject: {
                Object o = f->getObjectValue();
                if (IsInstance(Integer, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Integer>(o))->toChars());
                } else if (IsInstance(Long, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Long>(o))->toChars());
                } else if (IsInstance(Boolean, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Boolean>(o))->toChars());
                } else if (IsInstance(Double, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Double>(o))->toChars());
                } else if (IsInstance(Float, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Float>(o))->toChars());
                } else if (IsInstance(Byte, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Byte>(o))->toChars());
                } else if (IsInstance(Uint8, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Uint8>(o))->toChars());
                } else if (IsInstance(Uint16, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Uint16>(o))->toChars());
                } else if (IsInstance(Uint32, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Uint32>(o))->toChars());
                } else if (IsInstance(Uint64, o)) {
                    iniparser_set(dict,sectionKey->toChars(),createString(Cast<Uint64>(o))->toChars());
                } else if (IsInstance(String, o)) {
                    iniparser_set(dict,sectionKey->toChars(),Cast<String>(o)->toChars());
                } else {
                    importFrom(o,f->getName());
                }
            } break;
        }
        iterator->next();
    }
}

void _IniValue::reflectWithObject(Object obj,HashMap<String,String> map) {
    auto niter = map->getIterator();
    while(niter->hasValue()) {
        String nkey = niter->getKey();
        String nvalue = niter->getValue();
        Field field = obj->getField(nkey);
        switch (field->getType()) {
            case st(Field)::FieldTypeLong: {
                field->setValue(nvalue->toBasicLong());
            } break;

            case st(Field)::FieldTypeInt: {
                field->setValue(nvalue->toBasicInt());
            } break;

            case st(Field)::FieldTypeByte: {
                field->setValue(nvalue->toBasicByte());
            } break;

            case st(Field)::FieldTypeBool: {
                field->setValue(nvalue->toBasicBool());
            } break;

            case st(Field)::FieldTypeDouble: {
                field->setValue(nvalue->toBasicDouble());
            } break;

            case st(Field)::FieldTypeFloat: {
                field->setValue(nvalue->toBasicFloat());
            } break;

            case st(Field)::FieldTypeString: {
                field->setValue(nvalue);
            } break;

            case st(Field)::FieldTypeUint16: {
                field->setValue(nvalue->toBasicUint16());
            } break;

            case st(Field)::FieldTypeUint32: {
                field->setValue(nvalue->toBasicUint32());
            } break;

            case st(Field)::FieldTypeUint64: {
                field->setValue(nvalue->toBasicUint64());
            } break;

            case st(Field)::FieldTypeObject: {
                Object o = field->createObject();
                if (IsInstance(Integer, o)) {
                    Cast<Integer>(o)->update(nvalue->toBasicInt());
                } else if (IsInstance(Long, o)) {
                    Cast<Long>(o)->update(nvalue->toBasicLong());
                } else if (IsInstance(Boolean, o)) {
                    Cast<Boolean>(o)->update(nvalue->toBasicBool());
                } else if (IsInstance(Double, o)) {
                    Cast<Double>(o)->update(nvalue->toBasicDouble());
                } else if (IsInstance(Float, o)) {
                    Cast<Float>(o)->update(nvalue->toBasicFloat());
                } else if (IsInstance(Byte, o)) {
                    Cast<Byte>(o)->update(nvalue->toBasicByte());
                } else if (IsInstance(Uint8, o)) {
                    Cast<Uint8>(o)->update(nvalue->toBasicUint8());
                } else if (IsInstance(Uint16, o)) {
                    Cast<Uint16>(o)->update(nvalue->toBasicUint16());
                } else if (IsInstance(Uint32, o)) {
                    Cast<Uint32>(o)->update(nvalue->toBasicUint32());
                } else if (IsInstance(Uint64, o)) {
                    Cast<Uint64>(o)->update(nvalue->toBasicUint64());
                } else if (IsInstance(String, o)) {
                    Cast<String>(o)->update(nvalue->toChars());
                }
            } break;
        }
        niter->next();
    }
}

_IniValue::~_IniValue() {
    if (dict != nullptr) {
        iniparser_freedict(dict);
        dict = nullptr;
    }
}

void _IniValue::set(String section,String key,String value) {
    auto map = mValues->get(section);
    if(map == nullptr) {
        map = createHashMap<String,String>();
        mValues->put(section,map);
    }

    map->put(key,value);

    //start write to dict
    String comm = section->append(":","key");
    iniparser_set(dict,comm->toChars(),value->toChars());
}

void _IniValue::set(String key,String value) {
    set(RootSectionName,key,value);
}

String _IniValue::get(String section,String key) {
    auto map = mValues->get(section);
    if(map != nullptr) {
        return map->get(key);
    }

    return nullptr;
}

String _IniValue::get(String key) {
    return get(RootSectionName,key);
}

HashMap<String,String> _IniValue::getSection(String section) {
    return mValues->get(section);
}

} // namespace obotcha