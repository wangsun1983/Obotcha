#ifndef __OBOTCHA_CONF_VALUE_H__
#define __OBOTCHA_CONF_VALUE_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "File.hpp"
#include "Field.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "Uint8.hpp"
#include "Uint16.hpp"
#include "Uint32.hpp"
#include "Uint64.hpp"
#include "Boolean.hpp"
#include "Float.hpp"
#include "Double.hpp"
#include "OStdInstanceOf.hpp"
#include "Log.hpp"
#include "HashMap.hpp"

extern "C" {
#include "ccl.h"
#include "bst.h"
}

namespace obotcha {

class _ConfReader;
class _ConfIterator;

DECLARE_CLASS(ConfValue) {
public:
    friend class _ConfReader;
    friend class _ConfIterator;
    _ConfValue();
    ~_ConfValue();

    String get(String tag);
    void set(String key,String value);
    sp<_ConfIterator> getIterator();

    template <typename T> void reflectTo(T obj) {
        ccl_t * pair = &mConfig;
        ccl_reset(pair);
        auto iterator = (ccl_pair_t *)ccl_iterate(pair);
        while(iterator != nullptr) {
            auto key = iterator->key;
            auto value = createString(iterator->value);

            auto field = obj->getField(createString(key));
            switch (field->getType()) {
                case st(Field)::FieldTypeLong: {
                    field->setValue(value->toBasicLong());
                } break;

                case st(Field)::FieldTypeInt: {
                    field->setValue(value->toBasicInt());
                } break;

                case st(Field)::FieldTypeByte: {
                    field->setValue(value->toBasicByte());
                } break;

                case st(Field)::FieldTypeBool: {
                    field->setValue(value->toBasicBool());
                } break;

                case st(Field)::FieldTypeDouble: {
                    field->setValue(value->toBasicDouble());
                } break;

                case st(Field)::FieldTypeFloat: {
                    field->setValue(value->toBasicFloat());
                } break;

                case st(Field)::FieldTypeString: {
                    field->setValue(value);
                } break;

                case st(Field)::FieldTypeUint16: {
                    field->setValue(value->toBasicUint16());
                } break;

                case st(Field)::FieldTypeUint32: {
                    field->setValue(value->toBasicUint32());
                } break;

                case st(Field)::FieldTypeUint64: {
                    field->setValue(value->toBasicUint64());
                } break;

                case st(Field)::FieldTypeObject: {
                    auto item = field->createObject();
                    if (IsInstance(Integer, obj)) {
                        Cast<Integer>(item)->update(value->toBasicInt());
                    } else if (IsInstance(Long, obj)) {
                        Cast<Long>(item)->update(value->toBasicLong());
                    } else if (IsInstance(Boolean, obj)) {
                        Cast<Boolean>(item)->update(value->toBasicBool());
                    } else if (IsInstance(Double, obj)) {
                        Cast<Double>(item)->update(value->toBasicDouble());
                    } else if (IsInstance(Float, obj)) {
                        Cast<Float>(item)->update(value->toBasicFloat());
                    } else if (IsInstance(Byte, obj)) {
                        Cast<Byte>(item)->update(value->toBasicByte());                        
                    } else if (IsInstance(Uint8, obj)) {
                        Cast<Uint8>(item)->update(value->toBasicUint8());
                    } else if (IsInstance(Uint16, obj)) {
                        Cast<Uint16>(item)->update(value->toBasicUint16());
                    } else if (IsInstance(Uint32, obj)) {
                        Cast<Uint32>(item)->update(value->toBasicUint32());
                    } else if (IsInstance(Uint64, obj)) {
                        Cast<Uint64>(item)->update(value->toBasicUint64());
                    } else if (IsInstance(String, obj)) {
                        Cast<String>(item)->update(value->toString());
                    }
                }
                break;
            }
        
            iterator = (ccl_pair_t *)ccl_iterate(pair);
        }
    }

    template <typename T> void importFrom(T value) {
        ArrayList<Field> fields = value->getAllFields();
        if (fields == nullptr) {
            LOG(ERROR) << "import class has no reflect filed";
            return;
        }

        ArrayListIterator<Field> iterator = fields->getIterator();
        while(iterator->hasValue()) {
            Field field = iterator->getValue();
            String name = field->getName();
            switch(field->getType()) {
                case st(Field)::FieldTypeLong: {
                    set(name,createString(field->getLongValue()));
                } break;

                case st(Field)::FieldTypeInt: {
                    set(name,createString(field->getIntValue()));
                } break;

                case st(Field)::FieldTypeByte: {
                    set(name,createString(field->getByteValue()));
                } break;

                case st(Field)::FieldTypeBool: {
                    set(name,createString(field->getBoolValue()));
                } break;

                case st(Field)::FieldTypeDouble: {
                    set(name,createString(field->getDoubleValue()));
                } break;

                case st(Field)::FieldTypeFloat: {
                    set(name,createString(field->getFloatValue()));
                } break;

                case st(Field)::FieldTypeString: {
                    set(name,createString(field->getStringValue()));
                } break;

                case st(Field)::FieldTypeUint16: {
                    set(name,createString(field->getUint16Value()));
                } break;

                case st(Field)::FieldTypeUint32: {
                    set(name,createString(field->getUint32Value()));
                } break;

                case st(Field)::FieldTypeUint64: {
                    set(name,createString(field->getUint64Value()));
                } break;

                case st(Field)::FieldTypeObject: {
                    auto obj = field->getObjectValue();
                    if (IsInstance(Integer, obj)) {
                        set(name,createString(Cast<Integer>(obj)));
                    } else if (IsInstance(Long, obj)) {
                        set(name,createString(Cast<Integer>(obj)));
                    } else if (IsInstance(Boolean, obj)) {
                        set(name,createString(Cast<Boolean>(obj)));
                    } else if (IsInstance(Double, obj)) {
                        set(name,createString(Cast<Double>(obj)));
                    } else if (IsInstance(Float, obj)) {
                        set(name,createString(Cast<Float>(obj)));
                    } else if (IsInstance(Byte, obj)) {
                        set(name,createString(Cast<Byte>(obj)));
                    } else if (IsInstance(Uint8, obj)) {
                        set(name,createString(Cast<Uint8>(obj)));
                    } else if (IsInstance(Uint16, obj)) {
                        set(name,createString(Cast<Uint16>(obj)));
                    } else if (IsInstance(Uint32, obj)) {
                        set(name,createString(Cast<Uint32>(obj)));
                    } else if (IsInstance(Uint64, obj)) {
                        set(name,createString(Cast<Uint64>(obj)));
                    } else if (IsInstance(String, obj)) {
                        set(name,createString(Cast<String>(obj)));
                    }
                } break;
            }
            iterator->next();
        }
    }

private:
    struct ccl_t mConfig;
};

DECLARE_CLASS(ConfIterator) {
public:
    friend class _ConfValue;

    _ConfIterator(_ConfValue *);
    
    _ConfIterator(ConfValue v);

    String getTag();
    
    String getValue();

    bool hasValue();
    
    bool next();

private:
    ConfValue mValue;
    struct ccl_pair_t* mIterator;
};


} // namespace obotcha

#endif