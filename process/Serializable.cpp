#include "Serializable.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"
#include "ByteArrayReader.hpp"
#include "Field.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "Float.hpp"
#include "Uint8.hpp"
#include "Uint16.hpp"
#include "Uint32.hpp"
#include "Uint64.hpp"
#include "Byte.hpp"
#include "OStdInstanceOf.hpp"
#include "Log.hpp"

namespace obotcha {

ByteArray _Serializable::serialize() {
    ByteArrayWriter writer = createByteArrayWriter();
    
    ArrayList<Field> fields = getAllFields();
    ArrayListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        switch(f->getType()) {
            case st(Field)::Type::Int: {
                writer->write<uint32_t>(sizeof(int));
                writer->write<int>(f->getIntValue());
            }
            break;

            case st(Field)::Type::Bool: {
                writer->write<uint32_t>(1);
                byte value = f->getBoolValue()?1:0;
                writer->write<byte>(value);
            }
            break;

            case st(Field)::Type::Byte: {
                writer->write<uint32_t>(1);
                writer->write<byte>(f->getByteValue());
            }
            break;

            case st(Field)::Type::Double:{
                String value = createString(f->getDoubleValue());
                writer->write<uint32_t>(value->size());
                writer->write(value->toByteArray());
            }
            break;

            case st(Field)::Type::Float:{
                String value = createString(f->getDoubleValue());
                writer->write<uint32_t>(value->size());
                writer->write(value->toByteArray());
            }
            break;

            case st(Field)::Type::Long: {
                writer->write<uint32_t>(sizeof(long));
                writer->write<long>(f->getLongValue());
            }
            break;

            case st(Field)::Type::String: {
                String value = f->getStringValue();
                if(value == nullptr) {
                    writer->write<uint32_t>(0);
                } else {
                    writer->write<uint32_t>(value->size());
                    writer->write(value->toByteArray());
                }
            }
            break;

            case st(Field)::Type::Uint16:{
                writer->write<uint32_t>(sizeof(uint16_t));
                writer->write<uint16_t>(f->getUint16Value());
            }
            break;

            case st(Field)::Type::Uint32:{
                writer->write<uint32_t>(sizeof(uint32_t));
                writer->write<uint32_t>(f->getUint32Value());
            }
            break;

            case st(Field)::Type::Uint64: {
                writer->write<uint32_t>(sizeof(uint64_t));
                writer->write<uint64_t>(f->getUint64Value());
            }
            break;

            case st(Field)::Type::ArrayList: {
                int count = f->getContainerSize();
                if(count == 0) {
                    writer->write<uint32_t>(0);
                } else {
                    int startIndex = writer->getIndex();
                    writer->write<uint32_t>(0);

                    //write each object
                    uint32_t size = 0;
                    for(int i = 0;i < count;i++) {
                        ByteArray data = serialize(f->getListItemObject(i));
                        writer->write(data);
                        size += data->size();
                    }
                    int endIndex = writer->getIndex();
                    writer->setIndex(startIndex);
                    writer->write<uint32_t>(size);
                    writer->setIndex(endIndex);
                }
            }
            break;

            case st(Field)::Type::HashMap: {
                ArrayList<Pair<Object, Object>> members = f->getMapItemObjects();
                if(members == nullptr) {
                    writer->write<uint32_t>(0);
                } else {
                    int count = members->size();
                    
                    int startIndex = writer->getIndex();
                    writer->write<uint32_t>(0);

                    uint32_t size = 0;
                    for(int i = 0;i < count;i++) {
                        Pair<Object,Object> pair = members->get(i);
                        ByteArray data = serialize(pair->getKey());
                        size += data->size();
                        writer->write(data);
                        data = serialize(pair->getValue());
                        size += data->size();
                        writer->write(data);
                    }

                    int endIndex = writer->getIndex();
                    writer->setIndex(startIndex);
                    writer->write<uint32_t>(size);
                    writer->setIndex(endIndex);

                }
            }
            break;

            case st(Field)::Type::Object: {
                Object obj = f->getObjectValue();
                if(obj == nullptr) {
                    writer->write<uint32_t>(0);
                } else {
                    ByteArray data = serialize(f->getObjectValue());
                    writer->write(data);
                }
            }
            break;

            case st(Field)::Type::UnKnow: {
                LOG(ERROR)<<"Serializable serialize unknow type";
            }
        }
        iterator->next();
    }

    return writer->getByteArray();
}

ByteArray _Serializable::serialize(Object obj) {
    ByteArray content;
    if (IsInstance(Integer, obj)) {
        Integer data = Cast<Integer>(obj);
        content = createByteArray(sizeof(int) + sizeof(int));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(sizeof(int));
        writer->write<int>(data->toValue());
    } else if (IsInstance(Long, obj)) {
        Long data = Cast<Long>(obj);
        content = createByteArray(sizeof(int) + sizeof(long));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(sizeof(long));
        writer->write<long>(data->toValue());
    } else if (IsInstance(Boolean, obj)) {;
        Boolean data = Cast<Boolean>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(1);
        if(data->toValue()) {
            writer->write<byte>(1);
        } else {
            writer->write<byte>(0);
        }
    } else if (IsInstance(Double, obj)) {
        Double data = Cast<Double>(obj);
        String value = createString(data->toValue());
        content = createByteArray(sizeof(int) + value->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(value->size());
        writer->write(value->toByteArray());
    } else if (IsInstance(Float, obj)) {
        Float data = Cast<Float>(obj);
        String value = createString(data->toValue());
        content = createByteArray(sizeof(int) + value->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(value->size());
        writer->write(value->toByteArray());
    } else if (IsInstance(Byte, obj)) {
        Byte data = Cast<Byte>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(1);
        writer->write<byte>(data->toValue());
    } else if (IsInstance(Uint8, obj)) {
        Uint8 data = Cast<Uint8>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(sizeof(uint8_t));
        writer->write<byte>(data->toValue());
    } else if (IsInstance(Uint16, obj)) {
        Uint16 data = Cast<Uint16>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint16_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(sizeof(uint16_t));
        writer->write<uint16_t>(data->toValue());
    } else if (IsInstance(Uint32, obj)) {
        Uint32 data = Cast<Uint32>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint32_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(sizeof(uint32_t));
        writer->write<uint32_t>(data->toValue());
    } else if (IsInstance(Uint64, obj)) {
        Uint64 data = Cast<Uint64>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint64_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(sizeof(uint64_t));
        writer->write<uint64_t>(data->toValue());
    } else if (IsInstance(ByteArray,obj)) {
        ByteArray array = Cast<ByteArray>(obj);
        content = createByteArray(sizeof(int) + array->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(array->size());
        writer->write(array);
    } else {
        Serializable data = Cast<Serializable>(obj);
        ByteArray array = data->serialize();
        content = createByteArray(sizeof(int) + array->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<uint32_t>(array->size());
        writer->write(array);
    }

    return content;
}

void _Serializable::deserialize(ByteArray data) {
    int index = 0;
    ByteArrayReader reader = createByteArrayReader(data);

    ArrayList<Field> fields = getAllFields();
    ArrayListIterator<Field> iterator = fields->getIterator();

    while(reader->getRemainSize() != 0) {
        int size = reader->read<uint32_t>();
        if(size == 0) {
            index++;
            continue;
        }

        Field f = fields->get(index);
        switch(f->getType()) {
            case st(Field)::Type::Int: {
                int v = reader->read<int>();
                f->setValue(v);
            }
            break;

            case st(Field)::Type::Bool: {
                byte v = reader->read<byte>();
                if(v == 0) {
                    f->setValue(false);
                } else {
                    f->setValue(true);
                }
            }
            break;

            case st(Field)::Type::Byte: {
                byte v = reader->read<byte>();
                f->setValue(v);
            }
            break;

            case st(Field)::Type::Double:{
                ByteArray str = createByteArray(size);
                reader->read(str);
                f->setValue(str->toString()->toBasicDouble());
            }
            break;

            case st(Field)::Type::Float:{
                ByteArray str = createByteArray(size);
                reader->read(str);
                f->setValue(str->toString()->toBasicFloat());
            }
            break;

            case st(Field)::Type::Long: {
                long v = reader->read<long>();
                f->setValue(v);
            }
            break;

            case st(Field)::Type::String: {
                ByteArray str = createByteArray(size);
                reader->read(str);
                auto value = str->toString();
                if(value != nullptr) {
                    f->setValue(str->toString());
                }
            }
            break;

            case st(Field)::Type::Uint16:{
                uint16_t v = reader->read<uint16_t>();
                f->setValue(v);
            }
            break;

            case st(Field)::Type::Uint32:{
                uint32_t v = reader->read<uint32_t>();
                f->setValue(v);
            }
            break;

            case st(Field)::Type::Uint64: {
                uint64_t v = reader->read<uint64_t>();
                f->setValue(v);
            }
            break;

            case st(Field)::Type::ArrayList: {
                ByteArray content = createByteArray(size);
                reader->read(content);

                ByteArrayReader arrayReader = createByteArrayReader(content);
                f->createObject();
                while(arrayReader->getRemainSize() != 0) {
                    Object memberObj = f->createListItemObject();
                    int memberSize = arrayReader->read<int>();

                    ByteArray memberArray = createByteArray(memberSize);
                    arrayReader->read(memberArray);
                    deserialize(memberObj,memberArray);
                    f->addListItemObject(memberObj);
                }
            }
            break;

            case st(Field)::Type::HashMap: {
                ByteArray content = createByteArray(size);
                reader->read(content);

                ByteArrayReader arrayReader = createByteArrayReader(content);
                f->createObject();
                while(arrayReader->getRemainSize() != 0) {
                    Pair<Object,Object> memberObj = f->createMapItemObject();
                    Object key = memberObj->getKey();
                    Object value = memberObj->getValue();

                    int keySize = arrayReader->read<int>();
                    ByteArray keyArray = createByteArray(keySize);
                    arrayReader->read(keyArray);
                    deserialize(key,keyArray);

                    int valueSize = arrayReader->read<int>();
                    ByteArray valueArray = createByteArray(valueSize);
                    arrayReader->read(valueArray);
                    deserialize(value,valueArray);
                    f->addMapItemObject(key,value);
                }
            }
            break;

            case st(Field)::Type::Object: {
                ByteArray content = createByteArray(size);
                reader->read(content);
                Object obj = f->createObject();
                deserialize(f->createObject(),content);
            }
            break;

            case st(Field)::Type::UnKnow: {
                LOG(ERROR)<<"Serializable deserialize unknow type";
            }
        }
        index++;
    }
}

void _Serializable::deserialize(Object obj,ByteArray data) const {
    ByteArrayReader reader = createByteArrayReader(data);
    if (IsInstance(Integer, obj)) {
        Integer v = Cast<Integer>(obj);
        int value = reader->read<int>();
        v->update(value);
    } else if (IsInstance(Long, obj)) {
        Long v = Cast<Long>(obj);
        long value = reader->read<long>();
        v->update(value);
    } else if (IsInstance(Boolean, obj)) {
        Boolean v = Cast<Boolean>(obj);
        byte value = reader->read<byte>();
        v->update(value == 1);
    } else if (IsInstance(Double, obj)) {
        Double v = Cast<Double>(obj);
        String value = v->toString();
        v->update(value->toBasicDouble());
    } else if (IsInstance(Float, obj)) {
        Float v = Cast<Float>(obj);
        String value = v->toString();
        v->update(value->toBasicFloat());
    } else if (IsInstance(Byte, obj)) {
        Byte v = Cast<Byte>(obj);
        byte value = reader->read<byte>();
        v->update(value);
    } else if (IsInstance(Uint8, obj)) {
        Uint8 v = Cast<Uint8>(obj);
        byte value = reader->read<byte>();
        v->update(value);
    } else if (IsInstance(Uint16, obj)) {
        Uint16 v = Cast<Uint16>(obj);
        uint16_t value = reader->read<uint16_t>();
        v->update(value);
    } else if (IsInstance(Uint32, obj)) {
        Uint32 v = Cast<Uint32>(obj);
        uint32_t value = reader->read<uint32_t>();
        v->update(value);
    } else if (IsInstance(Uint64, obj)) {
        Uint64 v = Cast<Uint64>(obj);
        uint64_t value = reader->read<uint64_t>();
        v->update(value);
    } else if (IsInstance(ByteArray,obj)) {
        ByteArray v = Cast<ByteArray>(obj);
        if(v->size() < data->size()) {
            v->growTo(data->size());
        } else {
            v->quickShrink(data->size());
        }
        v->fillFrom(data->toValue(),0,data->size());
    } else {
        Serializable serializedObj = Cast<Serializable>(obj);
        if(obj != nullptr) {
            serializedObj->deserialize(data);
        }
    }
}

}
