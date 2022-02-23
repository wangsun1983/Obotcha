#include "Serializable.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

ByteArray _Serializable::toByteArray() {
    ByteArray data = createByteArray(1024*4);
    ByteArrayWriter writer = createByteArrayWriter(data);
    //int size = caculateSize();
    //int ret = writer->writeInt(size);

    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        int type = f->getType();

        //writer->writeByte((byte)type);
        printf("type is %d \n",type);
        switch(f->getType()) {
            case st(Field)::FieldTypeInt: {
                writer->writeInt(sizeof(int));
                writer->writeInt(f->getIntValue());
            }
            break;

            case st(Field)::FieldTypeBool: {
                writer->writeInt(1);
                bool value = f->getBoolValue();
                if(value) {
                    writer->writeByte(1);
                } else {
                    writer->writeByte(0);
                }
            }
            break;

            case st(Field)::FieldTypeByte: {
                writer->writeInt(1);
                byte value = f->getByteValue();
                writer->writeByte(value);
            }
            break;

            case st(Field)::FieldTypeDouble:{
                String value = createString(f->getDoubleValue());
                writer->writeInt(value->size());
                writer->writeByteArray(value->toByteArray());
            }
            break;

            case st(Field)::FieldTypeFloat:{
                String value = createString(f->getDoubleValue());
                writer->writeInt(value->size());
                writer->writeByteArray(value->toByteArray());
            }
            break;

            case st(Field)::FieldTypeLong: {
                writer->writeByte(sizeof(long));
                writer->writeLong(f->getLongValue());
            }
            break;

            case st(Field)::FieldTypeString: {
                String value = f->getStringValue();
                writer->writeInt(value->size());
                writer->writeByteArray(value->toByteArray());
            }
            break;

            case st(Field)::FieldTypeUint16:{
                uint16_t value = f->getUint16Value();
                writer->writeInt(sizeof(uint16_t));
                writer->writeUint16(value);
            }
            break;

            case st(Field)::FieldTypeUint32:{
                uint32_t value = f->getUint32Value();
                writer->writeInt(sizeof(uint32_t));
                writer->writeUint32(value);
            }
            break;

            case st(Field)::FieldTypeUint64: {
                uint64_t value = f->getUint64Value();
                writer->writeInt(sizeof(uint64_t));
                writer->writeUint64(value);
            }
            break;

            case st(Field)::FieldTypeArrayList: {
                int count = f->getContainerSize();
                //calculate size first
                int size = 0;
                for(int i = 0;i < count;i++) {
                    Serializable serialzabledData = Cast<Serializable>(f->getListItemObject(i));
                    printf("serialzabledData size is %d,field size is %d \n",serialzabledData->calculateSize(),serialzabledData->getAllFields()->size());

                    size += (serialzabledData->calculateSize() 
                            + serialzabledData->getAllFields()->size() * sizeof(int));
                    
                    size += sizeof(int);
                }
                printf("write array size is %d \n",size);
                writer->writeInt(size);

                //write each object
                for(int i = 0;i < count;i++) {
                    ByteArray data = toByteArray(f->getListItemObject(i));
                    writer->writeByteArray(data);
                    printf("write data size is %d \n",data->size());
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                ArrayList<KeyValuePair<Object, Object>> members = f->getMapItemObjects();
                int count = members->size();
                int size = 0;
                //calculate size
                for(int i = 0;i < count;i++) {
                    KeyValuePair<Object,Object> pair = members->get(i);
                    Serializable serialzabledKey = Cast<Serializable>(pair->getKey());

                    Serializable serialzabledValue = Cast<Serializable>(pair->getValue());

                    size += (serialzabledKey->calculateSize() 
                            + serialzabledKey->getAllFields()->size() * sizeof(int));
                    size += sizeof(int);
                    printf("FieldTypeHashMap size is %d \n",size);

                    size += (serialzabledValue->calculateSize() 
                            + serialzabledValue->getAllFields()->size() * sizeof(int));
                    printf("FieldTypeHashMap2 size is %d \n",size);
                    size += sizeof(int);
                    printf("FieldTypeHashMap3 size is %d \n",size);
                }

                writer->writeInt(size);
                for(int i = 0;i < count;i++) {
                    KeyValuePair<Object,Object> pair = members->get(i);
                    ByteArray data = toByteArray(pair->getKey());
                    writer->writeByteArray(data);
                    data = toByteArray(pair->getValue());
                    writer->writeByteArray(data);
                }
            }
            break;

            case st(Field)::FieldTypeObject: {
                ByteArray data = toByteArray(f->getObjectValue());
                writer->writeByteArray(data);
            }
            break;
        }
        iterator->next();
    }

    return writer->getByteArray();
}

ByteArray _Serializable::toByteArray(Object obj) {
    ByteArray content;
    if (IsInstance(Integer, obj)) {
        printf("toByteArray integer \n");
        Integer data = Cast<Integer>(obj);
        content = createByteArray(sizeof(int) + sizeof(int));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(sizeof(int));
        writer->writeInt(data->toValue());
    } else if (IsInstance(Long, obj)) {
        printf("toByteArray Long \n");
        Long data = Cast<Long>(obj);
        content = createByteArray(sizeof(long));
        ByteArrayWriter writer = createByteArrayWriter(sizeof(int) + sizeof(long));
        writer->writeInt(sizeof(long));
        writer->writeLong(data->toValue());
    } else if (IsInstance(Boolean, obj)) {
        printf("toByteArray boolean \n");
        Boolean data = Cast<Boolean>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(1);
        if(data->toValue()) {
            writer->writeByte(1);
        } else {
            writer->writeByte(0);
        }
    } else if (IsInstance(Double, obj)) {
        printf("toByteArray double \n");
        Double data = Cast<Double>(obj);
        String value = createString(data->toValue());
        content = createByteArray(sizeof(int) + value->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(value->size());
        writer->writeByteArray(value->toByteArray());
    } else if (IsInstance(Float, obj)) {
        printf("toByteArray float \n");
        Float data = Cast<Float>(obj);
        String value = createString(data->toValue());
        content = createByteArray(sizeof(int) + value->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(value->size());
        writer->writeByteArray(value->toByteArray());
    } else if (IsInstance(Byte, obj)) {
        printf("toByteArray byte \n");
        Byte data = Cast<Byte>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(1);
        writer->writeByte(data->toValue());
    } else if (IsInstance(Uint8, obj)) {
        printf("toByteArray uint8 \n");
        Uint8 data = Cast<Uint8>(obj);
        content = createByteArray(sizeof(int) + 1);
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(sizeof(uint8_t));
        writer->writeByte(data->toValue());
    } else if (IsInstance(Uint16, obj)) {
        printf("toByteArray uint16 \n");
        Uint16 data = Cast<Uint16>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint16_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(sizeof(uint16_t));
        writer->writeUint16(data->toValue());
    } else if (IsInstance(Uint32, obj)) {
        printf("toByteArray uint32 \n");
        Uint32 data = Cast<Uint32>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint32_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(sizeof(uint32_t));
        writer->writeUint32(data->toValue());
    } else if (IsInstance(Uint64, obj)) {
        printf("toByteArray uint64 \n");
        Uint64 data = Cast<Uint64>(obj);
        content = createByteArray(sizeof(int) + sizeof(uint64_t));
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(sizeof(uint64_t));
        writer->writeUint64(data->toValue());
    } else if (IsInstance(ByteArray,obj)) {
        printf("toByteArray byteArray \n");
        ByteArray array = Cast<ByteArray>(obj);
        content = createByteArray(sizeof(int) + array->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(array->size());
        writer->writeByteArray(array);
    } else {
        printf("toByteArray object \n");
        Serializable data = Cast<Serializable>(obj);
        ByteArray array = data->toByteArray();
        content = createByteArray(sizeof(int) + array->size());
        ByteArrayWriter writer = createByteArrayWriter(content);
        writer->writeInt(array->size());
        writer->writeByteArray(array);
    }

    return content;
}

void _Serializable::import(ByteArray data) {
    int index = 0;
    ByteArrayReader reader = createByteArrayReader(data);
    
    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();

    while(reader->getRemainSize() != 0) {
        //byte type = reader->readByte();
        int size = reader->readInt();
        Field f = fields->get(index);
        printf("type is %d,size is %d \n",f->getType(),size);
        
        switch(f->getType()) {
            case st(Field)::FieldTypeInt: {
                int v = reader->readInt();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeBool: {
                byte v = reader->readByte();
                if(v == 0) {
                    f->setValue(false);
                } else {
                    f->setValue(true);
                }
            }
            break;

            case st(Field)::FieldTypeByte: {
                byte v = reader->readByte();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeDouble:{
                ByteArray str = createByteArray(size);
                reader->readByteArray(str);
                f->setValue(str->toString()->toBasicDouble());
            }
            break;

            case st(Field)::FieldTypeFloat:{
                ByteArray str = createByteArray(size);
                reader->readByteArray(str);
                f->setValue(str->toString()->toBasicFloat());
            }
            break;

            case st(Field)::FieldTypeLong: {
                long v = reader->readLong();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeString: {
                ByteArray str = createByteArray(size);
                reader->readByteArray(str);
                f->setValue(str->toString());
            }
            break;

            case st(Field)::FieldTypeUint16:{
                uint16_t v = reader->readUint16();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeUint32:{
                uint32_t v = reader->readUint32();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeUint64: {
                uint64_t v = reader->readUint64();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeArrayList: {
                ByteArray content = createByteArray(size);
                printf("arraylist total size is %d \n",size);
                reader->readByteArray(content);
                
                ByteArrayReader arrayReader = createByteArrayReader(content);
                f->createObject();
                while(arrayReader->getRemainSize() != 0) {
                    printf("remainsize is %d \n",arrayReader->getRemainSize());
                    Object memberObj = f->createListItemObject();
                    int memberSize = arrayReader->readInt();
                    printf("memberSize is %d \n",memberSize);

                    ByteArray memberArray = createByteArray(memberSize);
                    printf("memberArraySize is %d \n",memberArray->size());
                    int rs = arrayReader->readByteArray(memberArray);
                    printf("rs is %d,remainsize is %d \n",rs,arrayReader->getRemainSize());
                    import(memberObj,memberArray);
                    f->addListItemObject(memberObj);
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                ByteArray content = createByteArray(size);
                printf("arraylist total size is %d \n",size);
                reader->readByteArray(content);
                
                ByteArrayReader arrayReader = createByteArrayReader(content);
                f->createObject();
                while(arrayReader->getRemainSize() != 0) {
                    KeyValuePair<Object,Object> memberObj = f->createMapItemObject();
                    Object key = memberObj->getKey();
                    Object value = memberObj->getValue();

                    int keySize = arrayReader->readInt();
                    ByteArray keyArray = createByteArray(keySize);
                    int rs = arrayReader->readByteArray(keyArray);
                    import(key,keyArray);

                    int valueSize = arrayReader->readInt();
                    ByteArray valueArray = createByteArray(valueSize);
                    rs = arrayReader->readByteArray(valueArray);
                    import(value,valueArray);

                    f->addMapItemObject(key,value);
                }
            }
            break;

            case st(Field)::FieldTypeObject: {
                ByteArray content = createByteArray(size);
                reader->readByteArray(content);
                import(f->createObject(),content);
                //Serializable data = Cast<Serializable>(fields->get(index)->createObject());
                //data->import(byteArray);
            }
            break;
        }
        index++;
    }
}

void _Serializable::import(Object obj,ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data);
    if (IsInstance(Integer, obj)) {
        Integer v = Cast<Integer>(obj);
        int value = reader->readInt();
        v->update(value);
    } else if (IsInstance(Long, obj)) {
        Long v = Cast<Long>(obj);
        long value = reader->readLong();
        v->update(value);
    } else if (IsInstance(Boolean, obj)) {
        Boolean data = Cast<Boolean>(obj);
        byte value = reader->readByte();
        if(value == 1) {
            data->update(true);
        } else {
            data->update(false);
        }
    } else if (IsInstance(Double, obj)) {
        Double data = Cast<Double>(obj);
        String value = data->toString();
        data->update(value->toBasicDouble());
    } else if (IsInstance(Float, obj)) {
        Float data = Cast<Float>(obj);
        String value = data->toString();
        data->update(value->toBasicFloat());
    } else if (IsInstance(Byte, obj)) {
        Byte data = Cast<Byte>(obj);
        byte v = reader->readByte();
        data->update(v);
    } else if (IsInstance(Uint8, obj)) {
        Uint8 data = Cast<Uint8>(obj);
        byte v = reader->readByte();
        data->update(v);
    } else if (IsInstance(Uint16, obj)) {
        Uint16 data = Cast<Uint16>(obj);
        uint16_t v = reader->readUint16();
        data->update(v);
    } else if (IsInstance(Uint32, obj)) {
        Uint32 data = Cast<Uint32>(obj);
        uint32_t v = reader->readUint32();
        data->update(v);
    } else if (IsInstance(Uint64, obj)) {
        Uint64 data = Cast<Uint64>(obj);
        uint64_t v = reader->readUint64();
        data->update(v);
    } else {
        Serializable serializedObj = Cast<Serializable>(obj);
        if(obj != nullptr) {
            serializedObj->import(data);
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
                size += f->getStringValue()->size();
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
                //calculate size first
                for(int i = 0;i < count;i++) {
                    Serializable serialzabledData = Cast<Serializable>(f->getListItemObject(i));
                    size += serialzabledData->calculateSize();
                }
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                ArrayList<KeyValuePair<Object, Object>> members = f->getMapItemObjects();
                int count = members->size();
                int size = 0;
                //calculate size
                for(int i = 0;i < count;i++) {
                    KeyValuePair<Object,Object> pair = members->get(i);
                    Serializable serialzabledKey = Cast<Serializable>(pair->getKey());
                    Serializable serialzabledValue = Cast<Serializable>(pair->getValue());
                    size += (serialzabledKey->calculateSize() + serialzabledValue->calculateSize());
                }
            }
            break;

            case st(Field)::FieldTypeObject: {
                Object obj = f->getObjectValue();
                if(IsInstance(Serializable,obj)) {
                    Serializable serializedData = Cast<Serializable>(obj);
                    size += serializedData->calculateSize();
                }
                //size += (Serializable)f->getObjectValue())
            }
            break;
        }
        iterator->next();
    }
    printf("size is %d \n",size);
    return size;
}

}
