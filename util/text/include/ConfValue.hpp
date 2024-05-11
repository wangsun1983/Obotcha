#ifndef __OBOTCHA_CONF_VALUE_H__
#define __OBOTCHA_CONF_VALUE_H__

#include "Object.hpp"
#include "String.hpp"
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
    ~_ConfValue() override;

    String get(String tag) const;
    void set(String key,String value);
    sp<_ConfIterator> getIterator();

    template <typename T> void reflectTo(T obj) {
        ccl_t * pair = &mConfig;
        ccl_reset(pair);
        auto iterator = ccl_iterate(pair);
        while(iterator != nullptr) {
            auto key = iterator->key;
            auto value = String::New(iterator->value);
            switch (auto field = obj->getField(String::New(key));
                    field->getType()) {
                case st(Field)::Type::Long: {
                    field->setValue(value->toBasicLong());
                } break;

                case st(Field)::Type::Int: {
                    field->setValue(value->toBasicInt());
                } break;

                case st(Field)::Type::Byte: {
                    field->setValue(value->toBasicByte());
                } break;

                case st(Field)::Type::Bool: {
                    field->setValue(value->toBasicBool());
                } break;

                case st(Field)::Type::Double: {
                    field->setValue(value->toBasicDouble());
                } break;

                case st(Field)::Type::Float: {
                    field->setValue(value->toBasicFloat());
                } break;

                case st(Field)::Type::String: {
                    field->setValue(value);
                } break;

                case st(Field)::Type::Uint16: {
                    field->setValue(value->toBasicUint16());
                } break;

                case st(Field)::Type::Uint32: {
                    field->setValue(value->toBasicUint32());
                } break;

                case st(Field)::Type::Uint64: {
                    field->setValue(value->toBasicUint64());
                } break;

                case st(Field)::Type::Object: {
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
                } break;

                default:
                    LOG(ERROR)<<"ConfValue reflectTo unknow type:"<<static_cast<int>(field->getType());
                break;
            }
        
            iterator = ccl_iterate(pair);
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
                case st(Field)::Type::Long: {
                    set(name,String::New(field->getLongValue()));
                } break;

                case st(Field)::Type::Int: {
                    set(name,String::New(field->getIntValue()));
                } break;

                case st(Field)::Type::Byte: {
                    set(name,String::New(field->getByteValue()));
                } break;

                case st(Field)::Type::Bool: {
                    set(name,String::New(field->getBoolValue()));
                } break;

                case st(Field)::Type::Double: {
                    set(name,String::New(field->getDoubleValue()));
                } break;

                case st(Field)::Type::Float: {
                    set(name,String::New(field->getFloatValue()));
                } break;

                case st(Field)::Type::String: {
                    set(name,String::New(field->getStringValue()));
                } break;

                case st(Field)::Type::Uint16: {
                    set(name,String::New(field->getUint16Value()));
                } break;

                case st(Field)::Type::Uint32: {
                    set(name,String::New(field->getUint32Value()));
                } break;

                case st(Field)::Type::Uint64: {
                    set(name,String::New(field->getUint64Value()));
                } break;

                case st(Field)::Type::Object: {
                    auto obj = field->getObjectValue();
                    if (IsInstance(Integer, obj)) {
                        set(name,String::New(Cast<Integer>(obj)));
                    } else if (IsInstance(Long, obj)) {
                        set(name,String::New(Cast<Long>(obj)));
                    } else if (IsInstance(Boolean, obj)) {
                        set(name,String::New(Cast<Boolean>(obj)));
                    } else if (IsInstance(Double, obj)) {
                        set(name,String::New(Cast<Double>(obj)));
                    } else if (IsInstance(Float, obj)) {
                        set(name,String::New(Cast<Float>(obj)));
                    } else if (IsInstance(Byte, obj)) {
                        set(name,String::New(Cast<Byte>(obj)));
                    } else if (IsInstance(Uint8, obj)) {
                        set(name,String::New(Cast<Uint8>(obj)));
                    } else if (IsInstance(Uint16, obj)) {
                        set(name,String::New(Cast<Uint16>(obj)));
                    } else if (IsInstance(Uint32, obj)) {
                        set(name,String::New(Cast<Uint32>(obj)));
                    } else if (IsInstance(Uint64, obj)) {
                        set(name,String::New(Cast<Uint64>(obj)));
                    } else if (IsInstance(String, obj)) {
                        set(name,String::New(Cast<String>(obj)));
                    }
                } break;

                default:
                    LOG(ERROR)<<"ConfValue importFrom unknow type:"<<static_cast<int>(field->getType());
                break;
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

    explicit _ConfIterator(_ConfValue *);
    
    explicit _ConfIterator(ConfValue v);

    String getTag() const;
    
    String getValue() const;

    bool hasValue() const;
    
    bool next();

private:
    ConfValue mValue;
    const struct ccl_pair_t* mIterator;
};


} // namespace obotcha

#endif