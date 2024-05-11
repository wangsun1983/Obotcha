#ifndef __OBOTCHA_SQL_CONTENT_VALUES_H__
#define __OBOTCHA_SQL_CONTENT_VALUES_H__

#include "Object.hpp"
#include "TextContent.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"
#include "Log.hpp"

namespace obotcha {

DECLARE_CLASS(SqlContent) {
public:
    bool isStringContent;
    TextContent mContent;

    _SqlContent(TextContent c,bool isString = false) {
        mContent = c;
        isStringContent = isString;
    }
};

DECLARE_CLASS(SqlContentValues) {
public:
    _SqlContentValues();

    template<typename T>
    void put(String tag,T value) {
        mContents->put(tag,
                       SqlContent::New(TextContent::New(value),false));
    }

    template<typename T>
    void putString(String tag,T value) {
        mContents->put(tag,
                       SqlContent::New(TextContent::New(value),true));
    }

    template<typename T>
    void put(T value) {
        ArrayList<Field> fields = value->getAllFields();
         if (fields == nullptr) {
            LOG(ERROR) << "SqlContentValues put class has no reflect filed";
            return;
        }

        ForEveryOne(field,fields) {
            String name = field->getName();
            SqlContent content = nullptr;

            switch (field->getType()) {
                case st(Field)::Type::Long: {
                    content = SqlContent::New(TextContent::New(field->getLongValue()),
                                               false);
                    break;
                }

                case st(Field)::Type::Int: {
                    content = SqlContent::New(TextContent::New(field->getIntValue()),
                                               false);
                    break;
                }

                case st(Field)::Type::Bool: {
                    content = SqlContent::New(TextContent::New(field->getBoolValue()),
                                               false);
                    break;
                }

                case st(Field)::Type::Double: {
                    content = SqlContent::New(TextContent::New(field->getDoubleValue()),
                                               false);
                    break;
                }

                case st(Field)::Type::Float: {
                    content = SqlContent::New(TextContent::New(field->getFloatValue()),
                                               false);
                    break;
                }

                case st(Field)::Type::String: {
                    String value = field->getStringValue();
                    if(value != nullptr) {
                        content = SqlContent::New(TextContent::New(value),true);
                    }
                    break;
                }

                case st(Field)::Type::Byte: {
                    content = SqlContent::New(TextContent::New(field->getByteValue()),
                                               false);
                    break;
                }

                case st(Field)::Type::Uint16: {
                    content = SqlContent::New(TextContent::New(field->getUint16Value()),
                                               false);
                    break;
                }

                case st(Field)::Type::Uint32: {
                    content = SqlContent::New(TextContent::New(field->getUint32Value()),
                                               false);
                    break;
                }

                case st(Field)::Type::Uint64: {
                    content = SqlContent::New(TextContent::New(field->getUint64Value()),
                                               false);
                    break;
                }

                case st(Field)::Type::Object: {
                    Object o = field->getObjectValue();
                    if (IsInstance(Integer, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Integer>(o)),false);
                    } else if (IsInstance(Long, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Long>(o)),false);
                    } else if (IsInstance(Boolean, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Boolean>(o)),false);
                    } else if (IsInstance(Double, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Double>(o)),false);
                    } else if (IsInstance(Float, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Float>(o)),false);
                    } else if (IsInstance(Byte, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Byte>(o)),false);
                    } else if (IsInstance(Uint8, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Uint8>(o)),false);
                    } else if (IsInstance(Uint16, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Uint16>(o)),false);
                    } else if (IsInstance(Uint32, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Uint32>(o)),false);
                    } else if (IsInstance(Uint64, o)) {
                        content = SqlContent::New(TextContent::New(Cast<Uint64>(o)),false);
                    }
                    break;
                }

                default:
                LOG(ERROR)<<"SqlContentValues unsupport type: "<<static_cast<int>(field->getType());
                break;
            }

            if(content != nullptr) {
                mContents->put(name,content);
            }
        }
    }

    String getTags();
    String getValues();
    
    HashMap<String,SqlContent> getContentValues();
private:
    HashMap<String,SqlContent> mContents;
};

} // namespace obotcha
#endif