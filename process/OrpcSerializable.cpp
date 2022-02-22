#include "OrpcSerializable.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

ByteArray _OrpcSerializable::toByteArray() {
    ByteArray data = createByteArray(1024*4);
    ByteArrayWriter writer = createByteArrayWriter(data);
    //int size = caculateSize();
    //int ret = writer->writeInt(size);

    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        int type = f->getType();

        writer->writeByte((byte)type);
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
                //TODO
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                //TODO
            }
            break;

            case st(Field)::FieldTypeObject: {
                //TODO
            }
            break;
        }
        iterator->next();
    }

    return writer->getByteArray();
}

void _OrpcSerializable::import(ByteArray data) {
    int index = 0;
    ByteArrayReader reader = createByteArrayReader(data);
    
    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();

    while(reader->getRemainSize() != 0) {
        byte type = reader->readByte();
        int size = reader->readInt();
        printf("type is %d,size is %d \n",type,size);
        switch(type) {
            case st(Field)::FieldTypeInt: {
                Field f = fields->get(index);
                int v = reader->readInt();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeBool: {
                Field f = fields->get(index);
                byte v = reader->readByte();
                if(v == 0) {
                    f->setValue(false);
                } else {
                    f->setValue(true);
                }
            }
            break;

            case st(Field)::FieldTypeByte: {
                Field f = fields->get(index);
                byte v = reader->readByte();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeDouble:{
                ByteArray str = createByteArray(size);
                reader->readByteArray(str);
                Field f = fields->get(index);
                f->setValue(str->toString()->toBasicDouble());
            }
            break;

            case st(Field)::FieldTypeFloat:{
                ByteArray str = createByteArray(size);
                reader->readByteArray(str);
                Field f = fields->get(index);
                f->setValue(str->toString()->toBasicFloat());
            }
            break;

            case st(Field)::FieldTypeLong: {
                Field f = fields->get(index);
                long v = reader->readLong();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeString: {
                ByteArray str = createByteArray(size);
                reader->readByteArray(str);
                Field f = fields->get(index);

                f->setValue(str->toString());
            }
            break;

            case st(Field)::FieldTypeUint16:{
                Field f = fields->get(index);
                uint16_t v = reader->readUint16();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeUint32:{
                Field f = fields->get(index);
                uint32_t v = reader->readUint32();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeUint64: {
                Field f = fields->get(index);
                uint64_t v = reader->readUint64();
                f->setValue(v);
            }
            break;

            case st(Field)::FieldTypeArrayList: {
                //TODO
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                //TODO
            }
            break;

            case st(Field)::FieldTypeObject: {
                //TODO
            }
            break;
        }
        index++;
    }
}

int _OrpcSerializable::caculateSize() {
    int size = 0;
    ArrayList<Field> fields = getAllFields();
    ListIterator<Field> iterator = fields->getIterator();
    while(iterator->hasValue()) {
        Field f = iterator->getValue();
        int type = f->getType();

        switch(f->getType()) {
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
                //TODO
            }
            break;

            case st(Field)::FieldTypeHashMap: {
                //TODO
            }
            break;

            case st(Field)::FieldTypeObject: {
                //TODO
            }
            break;
        }
        iterator->next();
    }
    printf("size is %d \n",size);
    return size;
}

}
