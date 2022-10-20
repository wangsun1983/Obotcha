#include "Serializable.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

ByteArray _Serializable::serialize() {
    ByteArrayWriter writer = createByteArrayWriter();
    
    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        int type = f->getType();

        switch(f->getType()) {
            case st(Field)::FieldTypeInt: {
                writer->write<int>(sizeof(int));
                writer->write<int>(f->getIntValue());
            }
            break;

            case st(Field)::FieldTypeBool: {
                writer->write<int>(1);
                bool value = f->getBoolValue();
                if(value) {
                    writer->write<byte>(1);
                } else {
                    writer->write<byte>(0);
                }
            }
            break;

            case st(Field)::FieldTypeByte: {
                writer->write<int>(1);
                byte value = f->getByteValue();
                writer->write<byte>(value);
            }
            break;

            case st(Field)::FieldTypeDouble:{
                String value = createString(f->getDoubleValue());
                writer->write<int>(value->size());
                writer->write(value->toByteArray());
            }
            break;

            case st(Field)::FieldTypeFloat:{
                String value = createString(f->getDoubleValue());
                writer->write<int>(value->size());
                writer->write(value->toByteArray());
            }
            break;

            case st(Field)::FieldTypeLong: {
                writer->write<int>(sizeof(long));
                writer->write<long>(f->getLongValue());
            }
            break;

            case st(Field)::FieldTypeString: {
                String value = f->getStringValue();
                if(value == nullptr) {
                    writer->write<int>(0);
                } else {
                    writer->write<int>(value->size());
                    writer->write(value->toByteArray());
                }
            }
            break;

            case st(Field)::FieldTypeUint16:{
                uint16_t value = f->getUint16Value();
                writer->write<int>(sizeof(uint16_t));
                writer->write<uint16_t>(value);
            }
            break;

            case st(Field)::FieldTypeUint32:{
                uint32_t value = f->getUint32Value();
                writer->write<int>(sizeof(uint32_t));
                writer->write<uint32_t>(value);
            }
            break;

            case st(Field)::FieldTypeUint64: {
                uint64_t value = f->getUint64Value();
                writer->write<int>(sizeof(uint64_t));
                writer->write<uint64_t>(value);
            }
            break;

            case st(Field)::FieldTypeArrayList: {
                int count = f->getContainerSize();
                if(count == 0) {
                    writer->write<int>(0);
                } else {
                    //calculate size first
                    int size = 0;
                    for(int i = 0;i < count;i++) {
                        Serializable serialzabledData = Cast<Serializable>(f->getListItemObject(i));
                        //printf("serialzabledData size is %d,field size is %d \n",serialzabledData->calculateSize(),serialzabledData->getAllFields()->size());

                        size += (serialzabledData->calculateSize()
                                + serialzabledData->getAllFields()->size() * sizeof(int));

                        size += sizeof(int);
                    }
                    //printf("write array size is %d \n",size);
                    writer->write<int>(size);

                    //write each object
                    for(int i = 0;i < count;i++) {
                        ByteArray data = serialize(f->getListItemObject(i));
                        writer->write(data);
                        //printf("write data size is %d \n",data->size());
                    }
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                ArrayList<Pair<Object, Object>> members = f->getMapItemObjects();
                if(members == nullptr) {
                    writer->write<int>(0);
                } else {
                    int count = members->size();
                    int size = 0;
                    //calculate size
                    for(int i = 0;i < count;i++) {
                        Pair<Object,Object> pair = members->get(i);
                        Serializable serialzabledKey = Cast<Serializable>(pair->getKey());

                        Serializable serialzabledValue = Cast<Serializable>(pair->getValue());

                        size += (serialzabledKey->calculateSize()
                                + serialzabledKey->getAllFields()->size() * sizeof(int));
                        size += sizeof(int);
                        //printf("FieldTypeHashMap size is %d \n",size);

                        size += (serialzabledValue->calculateSize()
                                + serialzabledValue->getAllFields()->size() * sizeof(int));
                        //printf("FieldTypeHashMap2 size is %d \n",size);
                        size += sizeof(int);
                        //printf("FieldTypeHashMap3 size is %d \n",size);
                    }

                    writer->write<int>(size);
                    for(int i = 0;i < count;i++) {
                        Pair<Object,Object> pair = members->get(i);
                        ByteArray data = serialize(pair->getKey());
                        writer->write(data);
                        data = serialize(pair->getValue());
                        writer->write(data);
                    }
                }
            }
            break;

            case st(Field)::FieldTypeObject: {
                Object obj = f->getObjectValue();
                if(obj == nullptr) {
                    writer->write<int>(0);
                } else {
                    ByteArray data = serialize(f->getObjectValue());
                    //printf("data size is %d \n",data->size());
                    writer->write(data);
                }
            }
            break;
        }
        iterator->next();
    }

    return writer->getByteArray();
}

ByteArray _Serializable::serialize(Object obj) {
    ByteArray content;
    if (IsInstance(Integer, obj)) {
        //printf("toByteArray integer \n");
        Integer data = Cast<Integer>(obj);
        content = createByteArray(sizeof(int) + sizeof(int));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(sizeof(int));
        writer->write<int>(data->toValue());
    } else if (IsInstance(Long, obj)) {
        //printf("toByteArray Long \n");
        Long data = Cast<Long>(obj);
        content = createByteArray(sizeof(int) + sizeof(long));
        ByteArrayWriter writer = createByteArrayWriter(sizeof(int) + sizeof(long));
        writer->write<int>(sizeof(long));
        writer->write<long>(data->toValue());
    } else if (IsInstance(Boolean, obj)) {
        //printf("toByteArray boolean \n");
        Boolean data = Cast<Boolean>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(1);
        if(data->toValue()) {
            writer->write<byte>(1);
        } else {
            writer->write<byte>(0);
        }
    } else if (IsInstance(Double, obj)) {
        //printf("toByteArray double \n");
        Double data = Cast<Double>(obj);
        auto value = createString(data->toValue())->toByteArray();
        content = createByteArray(sizeof(int) + value->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(value->size());
        writer->write(value);
    } else if (IsInstance(Float, obj)) {
        //printf("toByteArray float \n");
        Float data = Cast<Float>(obj);
        auto value = createString(data->toValue())->toByteArray();
        content = createByteArray(sizeof(int) + value->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(value->size());
        writer->write(value);
    } else if (IsInstance(Byte, obj)) {
        //printf("toByteArray byte \n");
        Byte data = Cast<Byte>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(1);
        writer->write<byte>(data->toValue());
    } else if (IsInstance(Uint8, obj)) {
        //printf("toByteArray uint8 \n");
        Uint8 data = Cast<Uint8>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(sizeof(uint8_t));
        writer->write<byte>(data->toValue());
    } else if (IsInstance(Uint16, obj)) {
        //printf("toByteArray uint16 \n");
        Uint16 data = Cast<Uint16>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint16_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(sizeof(uint16_t));
        writer->write<uint16_t>(data->toValue());
    } else if (IsInstance(Uint32, obj)) {
        Uint32 data = Cast<Uint32>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint32_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(sizeof(uint32_t));
        writer->write<uint32_t>(data->toValue());
    } else if (IsInstance(Uint64, obj)) {
        //printf("toByteArray uint64 \n");
        Uint64 data = Cast<Uint64>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint64_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(sizeof(uint64_t));
        writer->write<uint64_t>(data->toValue());
    } else if (IsInstance(ByteArray,obj)) {
        //printf("toByteArray byteArray \n");
        ByteArray array = Cast<ByteArray>(obj);
        content = createByteArray(sizeof(int) + array->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(array->size());
        writer->write(array);
    } else {
        //printf("toByteArray object \n");
        Serializable data = Cast<Serializable>(obj);
        ByteArray array = data->serialize();
        content = createByteArray(sizeof(int) + array->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->write<int>(array->size());
        writer->write(array);
    }

    return content;
}

void _Serializable::deserialize(ByteArray data) {
    int index = 0;
    ByteArrayReader reader = createByteArrayReader(data);

    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();

    while(reader->getRemainSize() != 0) {
        //byte type = reader->read<byte>();
        int size = reader->read<int>();
        if(size == 0) {
            index++;
            continue;
        }
        Field f = fields->get(index);
        //printf("type is %d,size is %d \n",f->getType(),size);

        switch(f->getType()) {
            case st(Field)::FieldTypeInt: {
                int v = reader->read<int>();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeBool: {
                byte v = reader->read<byte>();
                if(v == 0) {
                    f->setValue(false);
                } else {
                    f->setValue(true);
                }
            }
            break;

            case st(Field)::FieldTypeByte: {
                byte v = reader->read<byte>();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeDouble:{
                ByteArray str = createByteArray(size);
                reader->read(str);
                f->setValue(str->toString()->toBasicDouble());
            }
            break;

            case st(Field)::FieldTypeFloat:{
                ByteArray str = createByteArray(size);
                reader->read(str);
                f->setValue(str->toString()->toBasicFloat());
            }
            break;

            case st(Field)::FieldTypeLong: {
                long v = reader->read<long>();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeString: {
                ByteArray str = createByteArray(size);
                reader->read(str);
                f->setValue(str->toString());
            }
            break;

            case st(Field)::FieldTypeUint16:{
                uint16_t v = reader->read<uint16_t>();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeUint32:{
                uint32_t v = reader->read<uint32_t>();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeUint64: {
                uint64_t v = reader->read<uint64_t>();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeArrayList: {
                ByteArray content = createByteArray(size);
                //printf("arraylist total size is %d \n",size);
                reader->read(content);

                ByteArrayReader arrayReader = createByteArrayReader(content);
                f->createObject();
                while(arrayReader->getRemainSize() != 0) {
                    //printf("remainsize is %d \n",arrayReader->getRemainSize());
                    Object memberObj = f->createListItemObject();
                    int memberSize = arrayReader->read<int>();
                    //printf("memberSize is %d \n",memberSize);

                    ByteArray memberArray = createByteArray(memberSize);
                    //printf("memberArraySize is %d \n",memberArray->size());
                    int rs = arrayReader->read(memberArray);
                    //printf("rs is %d,remainsize is %d \n",rs,arrayReader->getRemainSize());
                    deserialize(memberObj,memberArray);
                    f->addListItemObject(memberObj);
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                ByteArray content = createByteArray(size);
                //printf("arraylist total size is %d \n",size);
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

            case st(Field)::FieldTypeObject: {
                ByteArray content = createByteArray(size);
                reader->read(content);
                Object obj = f->createObject();
                deserialize(f->createObject(),content);
                //Serializable data = Cast<Serializable>(fields->get(index)->createObject());
                //data->import(byteArray);
            }
            break;
        }
        index++;
    }
}

void _Serializable::deserialize(Object obj,ByteArray data) {
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
        if(value == 1) {
            v->update(true);
        } else {
            v->update(false);
        }
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

int _Serializable::calculateSize() {
    int size = 0;
    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        int type = f->getType();
        //size += sizeof(int); //wangsl

        switch(f->getType()) {
            case st(Field)::FieldTypeInt: {
                size += sizeof(int);
            }
            break;

            case st(Field)::FieldTypeBool:
            case st(Field)::FieldTypeByte: {
                size += 1;
            }
            break;

            case st(Field)::FieldTypeDouble:{
                String value = createString(f->getDoubleValue());
                size += value->size();
            }
            break;

            case st(Field)::FieldTypeFloat:{
                String value = createString(f->getDoubleValue());
                size += value->size();
            }
            break;

            case st(Field)::FieldTypeLong: {
                size += sizeof(long);
            }
            break;

            case st(Field)::FieldTypeString: {
                String str = f->getStringValue();
                if(str != nullptr) {
                    size += f->getStringValue()->size();
                }
            }
            break;

            case st(Field)::FieldTypeUint16:{
                size += sizeof(uint16_t);
            }
            break;

            case st(Field)::FieldTypeUint32:{
                size += sizeof(uint32_t);
            }
            break;

            case st(Field)::FieldTypeUint64: {
                size += sizeof(uint64_t);
            }
            break;

            case st(Field)::FieldTypeArrayList: {
                int count = f->getContainerSize();
                if(count != -1) {
                    //calculate size first
                    for(int i = 0;i < count;i++) {
                        Serializable serialzabledData = Cast<Serializable>(f->getListItemObject(i));
                        size += serialzabledData->calculateSize();
                    }
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                ArrayList<Pair<Object, Object>> members = f->getMapItemObjects();
                if(members != nullptr) {
                    int count = members->size();
                    int size = 0;
                    //calculate size
                    for(int i = 0;i < count;i++) {
                        Pair<Object,Object> pair = members->get(i);
                        Serializable serialzabledKey = Cast<Serializable>(pair->getKey());
                        Serializable serialzabledValue = Cast<Serializable>(pair->getValue());
                        size += (serialzabledKey->calculateSize() + serialzabledValue->calculateSize());
                    }
                }
            }
            break;

            case st(Field)::FieldTypeObject: {
                Object obj = f->getObjectValue();
                if(obj != nullptr) {
                    if(IsInstance(Serializable,obj)) {
                        Serializable serializedData = Cast<Serializable>(obj);
                        size += serializedData->calculateSize();
                    }
                }
                //size += (Serializable)f->getObjectValue())
            }
            break;
        }
        iterator->next();
    }
    return size;
}

}
