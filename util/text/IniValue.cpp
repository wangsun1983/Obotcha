#include "IniValue.hpp"
#include "Field.hpp"
#include "OStdInstanceOf.hpp"
#include "Log.hpp"

namespace obotcha {

String _IniValue::RootSection = createString("__root__");

_IniValue::_IniValue() {
    mValues = createHashMap<String, HashMap<String, String>>();
    dict = dictionary_new(0);
}

void _IniValue::init() {
    // reflect to HashMap
    int sections = iniparser_getnsec(dict);
    for (int i = 0; i < sections; i++) {
        const char *sectionName = iniparser_getsecname(dict, i);
        HashMap<String, String> mKeyValue = createHashMap<String, String>();
        mValues->put(createString(sectionName), mKeyValue);
        
        const char *keys[1024] = {nullptr};
        auto k = iniparser_getseckeys(dict, sectionName, keys);

        if (k == nullptr) {
            continue;
        }

        for (int j = 0; j < 1024; j++) {
            if (k[j] == nullptr) {
                break;
            }

            const char *v = iniparser_getstring(dict, k[j], "");
            //section:key
            ArrayList<String> p = createString(k[j])->split(":");
            mKeyValue->put(p->get(p->size() - 1), createString(v));
        }
    }
}

void _IniValue::reflectTo(Object obj) {
    auto iterator = mValues->getIterator();
    while(iterator->hasValue()) {
        String section = iterator->getKey();
        HashMap<String,String> values = iterator->getValue();
        if(section->equals(RootSection)) {
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

void _IniValue::importFrom(Object obj) {
    mValues->clear();
    importFrom(obj,nullptr);
}

/**
* if need set value:
*   iniparser_set(ini, "section:key2", "value2");
* or:
*   iniparser_set(ini, "section:key1", NULL);
* if nedd add new section:
*   iniparser_set(ini, "section", NULL);
**/
void _IniValue::importFrom(Object obj,String section) {
    ArrayList<Field> fields = obj->getAllFields();
    auto iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        String sectionKey = nullptr;
        String name = f->getName();

        if(section != nullptr) {
            dictionary_set(dict, section->toChars(), "");
            sectionKey = section->append(":",f->getName());
        } else {
            dictionary_set(dict, RootSection->toChars(), "");
            sectionKey = RootSection->append(":",f->getName());
            section = RootSection;
        }

        HashMap<String,String> map = mValues->get(section);
        if(map == nullptr) {
            map = createHashMap<String,String>();
            mValues->put(section,map);
        }
        switch (f->getType()) {
            case st(Field)::FieldTypeLong: {
                String value = createString(f->getLongValue());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeInt: {
                String value = createString(f->getIntValue());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeByte: {
                String value = createString(f->getByteValue());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeBool: {
                String value = createString(f->getBoolValue());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeDouble: {
                String value = createString(f->getDoubleValue());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeFloat: {
                String value = createString(f->getFloatValue());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeString: {
                String value = f->getStringValue();
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeUint16: {
                String value = createString(f->getUint16Value());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeUint32: {
                String value = createString(f->getUint32Value());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeUint64: {
                String value = createString(f->getUint64Value());
                map->put(name,value);
                iniparser_set(dict,sectionKey->toChars(),value->toChars());
            } break;

            case st(Field)::FieldTypeObject: {
                Object o = f->getObjectValue();
                if (IsInstance(Integer, o)) {
                    String value = createString(Cast<Integer>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Long, o)) {
                    String value = createString(Cast<Long>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Boolean, o)) {
                    String value = createString(Cast<Boolean>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Double, o)) {
                    String value = createString(Cast<Double>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Float, o)) {
                    String value = createString(Cast<Float>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Byte, o)) {
                    String value = createString(Cast<Byte>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Uint8, o)) {
                    String value = createString(Cast<Uint8>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Uint16, o)) {
                    String value = createString(Cast<Uint16>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Uint32, o)) {
                    String value = createString(Cast<Uint32>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(Uint64, o)) {
                    String value = createString(Cast<Uint64>(o));
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),value->toChars());
                } else if (IsInstance(String, o)) {
                    String value = Cast<String>(o);
                    map->put(name,value);
                    iniparser_set(dict,sectionKey->toChars(),Cast<String>(o)->toChars());
                } else {
                    importFrom(o,f->getName());
                }
            } break;

            default:
            LOG(ERROR)<<"IniValue importFrom unknow type:"<<f->getType();
            break;
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

            default:
                LOG(ERROR)<<"reflectWithObject unknow type:"<<field->getType();
            break;
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
    //save to map
    auto map = mValues->get(section);
    if(map == nullptr) {
        map = createHashMap<String,String>();
        mValues->put(section,map);
    }

    map->put(key,value);

    iniparser_set_with_serction(dict,
                                section->toChars(),
                                key->toChars(),
                                value->toChars());
}

void _IniValue::set(String key,String value) {
    set(RootSection,key,value);
}

String _IniValue::get(String section,String key) {
    auto map = mValues->get(section);
    if(map != nullptr) {
        return map->get(key);
    }

    return nullptr;
}

String _IniValue::get(String key) {
    return get(RootSection,key);
}

HashMap<String,String> _IniValue::getSection(String section) {
    return mValues->get(section);
}

HashMap<String,HashMap<String,String>> _IniValue::getAll() {
    return mValues;
}
    

} // namespace obotcha