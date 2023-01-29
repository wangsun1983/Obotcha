#ifndef __OBOTCHA_SQL_CONTENT_VALUES_H__
#define __OBOTCHA_SQL_CONTENT_VALUES_H__

#include "Object.hpp"
#include "TextContent.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

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
                       createSqlContent(createTextContent(value),false));
    }

    template<typename T>
    void putString(String tag,T value) {
        mContents->put(tag,
                       createSqlContent(createTextContent(value),true));
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
                case st(Field)::FieldTypeLong: {
                    content = createSqlContent(createTextContent(field->getLongValue()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeInt: {
                    content = createSqlContent(createTextContent(field->getIntValue()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeBool: {
                    content = createSqlContent(createTextContent(field->getBoolValue()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeDouble: {
                    content = createSqlContent(createTextContent(field->getDoubleValue()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeFloat: {
                    content = createSqlContent(createTextContent(field->getFloatValue()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeString: {
                    String value = field->getStringValue();
                    if(value != nullptr) {
                        content = createSqlContent(createTextContent(value),true);
                    }
                    break;
                }

                case st(Field)::FieldTypeUint8: {
                    content = createSqlContent(createTextContent(field->getByteValue()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeUint16: {
                    content = createSqlContent(createTextContent(field->getUint16Value()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeUint32: {
                    content = createSqlContent(createTextContent(field->getUint32Value()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeUint64: {
                    content = createSqlContent(createTextContent(field->getUint64Value()),
                                               false);
                    break;
                }

                case st(Field)::FieldTypeObject: {
                    Object o = field->getObjectValue();
                    if (IsInstance(Integer, o)) {
                        content = createSqlContent(createTextContent(Cast<Integer>(o)),false);
                    } else if (IsInstance(Long, o)) {
                        content = createSqlContent(createTextContent(Cast<Long>(o)),false);
                    } else if (IsInstance(Boolean, o)) {
                        content = createSqlContent(createTextContent(Cast<Boolean>(o)),false);
                    } else if (IsInstance(Double, o)) {
                        content = createSqlContent(createTextContent(Cast<Double>(o)),false);
                    } else if (IsInstance(Float, o)) {
                        content = createSqlContent(createTextContent(Cast<Float>(o)),false);
                    } else if (IsInstance(Byte, o)) {
                        content = createSqlContent(createTextContent(Cast<Byte>(o)),false);
                    } else if (IsInstance(Uint8, o)) {
                        content = createSqlContent(createTextContent(Cast<Uint8>(o)),false);
                    } else if (IsInstance(Uint16, o)) {
                        content = createSqlContent(createTextContent(Cast<Uint16>(o)),false);
                    } else if (IsInstance(Uint32, o)) {
                        content = createSqlContent(createTextContent(Cast<Uint32>(o)),false);
                    } else if (IsInstance(Uint64, o)) {
                        content = createSqlContent(createTextContent(Cast<Uint64>(o)),false);
                    }
                    break;
                }
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