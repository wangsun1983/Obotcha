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

                case st(Field)::FieldTypeByte:{
                        String value = node->getStringValue();
                        field->setValue(value->toBasicByte());
                    }
                    break;

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
                        field->createObject();
                        auto reflectValue = field->getObjectValue();
                        reflectTo(node,reflectValue);
                    }
                    break;

                case st(Field)::FieldTypeArrayList:{
                        sp<_XmlValueIterator> sub_iterator = node->getValueIterator();
                        field->createObject();
                        
                        while(sub_iterator->hasValue()) {
                            sp<_XmlValue> xmlnode = sub_iterator->getValue();
                            auto vv = field->createListItemObject();
                            reflectTo(xmlnode,vv);
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

                case st(Field)::FieldTypeByte:{
                    refNode = newNode(name,createString(field->getByteValue()));
                }
                break;

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
                    importFrom(refNode,newObject);
                }
                break;
                
                case st(Field)::FieldTypeArrayList: {
                    int count = 0;
                    refNode = newNode(name);
                    while(1) {
                        auto newObject = field->getListItemObject(count);
                        if(newObject != nullptr) {
                            //JsonValue newValue = createJsonValue();
                            sp<_XmlValue> item = newNode(newObject->__ReflectClassName());
                            importFrom(item,newObject);
                            refNode->appendNode(item);
                            count++;
                            continue;
                        }
                        break;
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