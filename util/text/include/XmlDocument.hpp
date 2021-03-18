#ifndef __OBOTCHA_XML_DOCUMENT_H__
#define __OBOTCHA_XML_DOCUMENT_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Log.hpp"
#include "Field.hpp"
#include "XmlValue.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "OStdInstanceOf.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlValue;
class _XmlAttribute;

DECLARE_SIMPLE_CLASS(XmlDocument) {

public:
    friend class _XmlValue;
    friend class _XmlReader;
    friend class _XmlAttribute;

    _XmlDocument(String path,long size);

    _XmlDocument(String content);

    _XmlDocument();

    sp<_XmlValue> newRootNode(String rootNode);
    
    sp<_XmlValue> newNode(String name,String value);

    sp<_XmlValue> newNode(String name);

    sp<_XmlValue> getRootNode();

    String toString();

    template<typename T>
    void reflectTo(T value) {
        sp<_XmlValue> root = getRootNode();
        reflectTo(root,value);
    }
    
    template<typename T>
    void importFrom(T value) {
        String name = value->__ReflectClassName();
        sp<_XmlValue> root = newRootNode(name);
        importFrom(root,value);
    }


private:
    xml_document<> xmlDoc;

    rapidxml::file<> fdoc;

    long mFileSize;

    template<typename T>
    void reflectTo(sp<_XmlValue> parent,T obj) {
        sp<_XmlValueIterator> iterator = parent->getValueIterator();
        while(iterator->hasValue()) {
            sp<_XmlValue> node = iterator->getValue();
            Field field = obj->getField(node->getName());
            if(field == nullptr) {
                LOG(ERROR)<<"reflect to fields is null!!!";
                iterator->next();
                continue;
            }

            switch(field->getType()) {
                case st(Field)::FieldTypeLong:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicLong());
                    }
                    break;

                case st(Field)::FieldTypeInt: {
                        String value = node->getStringValue();
                        field->setValue(value->toBasicInt());
                    }
                    break;

                //case st(Field)::FieldTypeByte:{
                //        String value = node->getStringValue();
                //        field->setValue(value->toBasicByte());
                //    }
                //    break;

                case st(Field)::FieldTypeBool:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicBool());
                    }
                    break;

                case st(Field)::FieldTypeDouble:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicDouble());
                    }
                    break;

                case st(Field)::FieldTypeFloat:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicFloat());
                    }
                    break;

                case st(Field)::FieldTypeString:{
                        String value = node->getStringValue();
                        field->setValue(value);
                    }
                    break;

                case st(Field)::FieldTypeUint8:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicUint8());
                    }
                    break;

                case st(Field)::FieldTypeUint16:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicUint16());
                    }
                    break;

                case st(Field)::FieldTypeUint32:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicUint32());
                    }
                    break;

                case st(Field)::FieldTypeUint64:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicUint64());
                    }
                    break;
                        
                case st(Field)::FieldTypeObject: {
                        auto newObject = field->createObject();
                        if(ostd::instanceOf<Integer>(newObject)) {
                            String value = node->getStringValue();
                            Integer data = Cast<Integer>(newObject);
                            data->update(value->toBasicInt());
                        } else if(ostd::instanceOf<Long>(newObject)) {
                            String value = node->getStringValue();
                            Long data = Cast<Long>(newObject);
                            data->update(value->toBasicLong());
                        } else if(ostd::instanceOf<Boolean>(newObject)) {
                            String value = node->getStringValue();
                            Boolean data = Cast<Boolean>(newObject);
                            data->update(value->toBasicBool());
                        } else if(ostd::instanceOf<Double>(newObject)) {
                            String value = node->getStringValue();
                            Double data = Cast<Double>(newObject);
                            data->update(value->toBasicDouble());
                        } else if(ostd::instanceOf<Float>(newObject)) {
                            String value = node->getStringValue();
                            Float data = Cast<Float>(newObject);
                            data->update(value->toBasicFloat());
                        } else if(ostd::instanceOf<Byte>(newObject)) {
                            String value = node->getStringValue();
                            Byte data = Cast<Byte>(newObject);
                            data->update(value->toBasicByte());
                        } else if(ostd::instanceOf<Uint8>(newObject)) {
                            String value = node->getStringValue();
                            Uint8 data = Cast<Uint8>(newObject);
                            data->update(value->toBasicByte());
                        } else if(ostd::instanceOf<Uint16>(newObject)) {
                            String value = node->getStringValue();
                            Uint16 data = Cast<Uint16>(newObject);
                            data->update(value->toBasicUint16());
                        } else if(ostd::instanceOf<Uint32>(newObject)) {
                            String value = node->getStringValue();
                            Uint32 data = Cast<Uint32>(newObject);
                            data->update(value->toBasicUint32());
                        } else if(ostd::instanceOf<Uint64>(newObject)) {
                            String value = node->getStringValue();
                            Uint64 data = Cast<Uint64>(newObject);
                            data->update(value->toBasicUint64());
                        } else {
                            reflectTo(node,newObject);
                        }
                    }
                    break;

                case st(Field)::FieldTypeArrayList:{
                        sp<_XmlValueIterator> sub_iterator = node->getValueIterator();
                        field->createObject();
                        while(sub_iterator->hasValue()) {
                            sp<_XmlValue> xmlnode = sub_iterator->getValue();
                            auto newObject = field->createListItemObject();
                            if(ostd::instanceOf<Integer>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Integer data = Cast<Integer>(newObject);
                                data->update(value->toBasicInt());
                            } else if(ostd::instanceOf<Long>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Long data = Cast<Long>(newObject);
                                data->update(value->toBasicLong());
                            } else if(ostd::instanceOf<Boolean>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Boolean data = Cast<Boolean>(newObject);
                                data->update(value->toBasicBool());
                            } else if(ostd::instanceOf<Double>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Double data = Cast<Double>(newObject);
                                data->update(value->toBasicDouble());
                            } else if(ostd::instanceOf<Float>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Float data = Cast<Float>(newObject);
                                data->update(value->toBasicFloat());
                            } else if(ostd::instanceOf<Byte>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Byte data = Cast<Byte>(newObject);
                                data->update(value->toBasicByte());
                            } else if(ostd::instanceOf<Uint8>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Uint8 data = Cast<Uint8>(newObject);
                                data->update(value->toBasicUint8());
                            } else if(ostd::instanceOf<Uint16>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Uint16 data = Cast<Uint16>(newObject);
                                data->update(value->toBasicUint16());
                            } else if(ostd::instanceOf<Uint32>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Uint32 data = Cast<Uint32>(newObject);
                                data->update(value->toBasicUint32());
                            } else if(ostd::instanceOf<Uint64>(newObject)) {
                                String value = xmlnode->getStringValue();
                                Uint64 data = Cast<Uint64>(newObject);
                                data->update(value->toBasicUint64());
                            } else if(ostd::instanceOf<String>(newObject)) {
                                String value = xmlnode->getStringValue();
                                String data = Cast<String>(newObject);
                                data->update(value);
                            } else {
                                reflectTo(xmlnode,newObject);
                            }
                            sub_iterator->next();
                        }
                    }
                    break;
            }

            iterator->next();
        }
    }

    template<typename T>
    void importFrom(sp<_XmlValue> parent,T value) {
        String name = value->__ReflectClassName();
        ArrayList<Field> fields = value->getAllFields();
        if(fields == nullptr) {
            LOG(ERROR)<<"XmlVale importFrom fields is null!!!";
            return;
        }

        ListIterator<Field> iterator = fields->getIterator();
        while(iterator->hasValue()) {
            Field field = iterator->getValue();
            String name = field->getName();
            sp<_XmlValue> refNode = nullptr;
            switch(field->getType()) {
                case st(Field)::FieldTypeLong: {
                    refNode = newNode(name,createString(field->getLongValue()));
                }
                break;

                case st(Field)::FieldTypeInt: {
                    refNode = newNode(name,createString(field->getIntValue()));
                }
                break;

                //case st(Field)::FieldTypeByte:{
                //    refNode = newNode(name,createString(field->getByteValue()));
                //}
                //break;

                case st(Field)::FieldTypeBool:{
                    refNode = newNode(name,createString(field->getBoolValue()));
                }
                break;

                case st(Field)::FieldTypeDouble:{
                    refNode = newNode(name,createString(field->getDoubleValue()));
                }
                break;

                case st(Field)::FieldTypeFloat:{
                    refNode = newNode(name,createString(field->getFloatValue()));
                }
                break;

                case st(Field)::FieldTypeString:{
                    refNode = newNode(name,field->getStringValue());
                }
                break;

                case st(Field)::FieldTypeUint8:{
                    refNode = newNode(name,createString(field->getByteValue()));
                }
                break;

                case st(Field)::FieldTypeUint16:{
                    refNode = newNode(name,createString(field->getUint16Value()));
                }
                break;

                case st(Field)::FieldTypeUint32:{
                    refNode = newNode(name,createString(field->getUint32Value()));
                }
                break;

                case st(Field)::FieldTypeUint64:{
                    refNode = newNode(name,createString(field->getUint64Value()));
                }
                break;

                case st(Field)::FieldTypeObject: {
                    auto newObject = field->getObjectValue();
                    refNode = newNode(name);
                    if(ostd::instanceOf<Integer>(newObject)) {
                        Integer data = Cast<Integer>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Long>(newObject)) {
                        Long data = Cast<Long>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Boolean>(newObject)) {
                        Boolean data = Cast<Boolean>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Double>(newObject)) {
                        Double data = Cast<Double>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Float>(newObject)) {
                        Float data = Cast<Float>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Byte>(newObject)) {
                        Byte data = Cast<Byte>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Uint8>(newObject)) {
                        Uint8 data = Cast<Uint8>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Uint16>(newObject)) {
                        Uint16 data = Cast<Uint16>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Uint32>(newObject)) {
                        Uint32 data = Cast<Uint32>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<Uint64>(newObject)) {
                        Uint64 data = Cast<Uint64>(newObject);
                        refNode->updateValue(createString(data->toValue()));
                    } else if(ostd::instanceOf<String>(newObject)) {
                        String data = Cast<String>(newObject);
                        refNode->updateValue(data);
                    } else {    
                        auto newObject = field->getObjectValue();
                        importFrom(refNode,newObject);
                    }
                }
                break;
                
                case st(Field)::FieldTypeArrayList: {
                    int count = 0;
                    int length = field->getListObjectSize();

                    refNode = newNode(name);
                    while(count < length) {
                        auto newObject = field->getListItemObject(count);
                        if(newObject != nullptr) {
                            sp<_XmlValue> item;
                            if(ostd::instanceOf<Integer>(newObject)) {
                                item = newNode(st(Integer)::className());
                                Integer data = Cast<Integer>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Long>(newObject)) {
                                item = newNode(st(Long)::className());
                                Long data = Cast<Long>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Boolean>(newObject)) {
                                item = newNode(st(Boolean)::className());
                                Boolean data = Cast<Boolean>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Double>(newObject)) {
                                item = newNode(st(Double)::className());
                                Double data = Cast<Double>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Float>(newObject)) {
                                item = newNode(st(Float)::className());
                                Float data = Cast<Float>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Byte>(newObject)) {
                                item = newNode(st(Byte)::className());
                                Byte data = Cast<Byte>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Uint8>(newObject)) {
                                item = newNode(st(Uint8)::className());
                                Uint8 data = Cast<Uint8>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Uint16>(newObject)) {
                                item = newNode(st(Uint16)::className());
                                Uint16 data = Cast<Uint16>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Uint32>(newObject)) {
                                item = newNode(st(Uint32)::className());
                                Uint32 data = Cast<Uint32>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<Uint64>(newObject)) {
                                item = newNode(st(Uint64)::className());
                                Uint64 data = Cast<Uint64>(newObject);
                                item->updateValue(createString(data->toValue()));
                            } else if(ostd::instanceOf<String>(newObject)) {
                                item = newNode(st(String)::className());
                                String data = Cast<String>(newObject);
                                item->updateValue(data);
                            } else {
                                item = newNode(newObject->__ReflectClassName());
                                importFrom(item,newObject);
                            }
                            refNode->appendNode(item);
                        }
                        count++;
                    }
                }
                break;
            }

            if(refNode != nullptr) {
                parent->appendNode(refNode);
            }
            iterator->next();
        }
    }
};

}


#endif