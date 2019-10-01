/**
 * @file ByteArray.cpp
 * @brief this class used for memory operation as buffer
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "ByteArray.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> b) {
    buff = (char *)malloc(b->size());
    memcpy(buff,b->toValue(),b->size());
    _size = b->size();
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(int length) {
    buff = (char *)malloc(length);
    memset(buff,0,length);
    _size = length;
}

/**
 * @brief ByteArray construct function
 * @param str save str as ByteArray
 */
_ByteArray::_ByteArray(String str) {
    int size = str->size();
    _size = size;
    buff = (char *)malloc(_size + 1);
    memset(buff,0,_size + 1);
    memcpy(buff,str->toChars(),size);
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(const char *data,int len) {
    buff = (char *)malloc(len);
    memset(buff,0,len);
    _size = len;
    memcpy(buff,data,len);
}


/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    memset(buff,0,_size);
}

/**
 * @brief ByteArray destruct function
 */
_ByteArray::~_ByteArray() {
    if(buff != nullptr) {
        free(buff);
        buff = nullptr;
    }
    _size = 0;
}


char *_ByteArray::toValue() {
    return buff;
}

int _ByteArray::size() {
    return _size;
}

void _ByteArray::qucikShrink(int size) {
    if(size >= _size) {
        return;
    }

    buff[size] = 0;

    _size = size;
}

int _ByteArray::resize(int size) {
    if(size <= _size) {
        return -ByteArrayWrongParam;
    }

    if(buff == nullptr) {
        return -ByteArrayNoMemory;
    }

    buff = (char *)realloc(buff,size);
    //memset(buff,0,size);
    //memcpy(buff,toFree,_size);
    _size = size;
    
    return 0;
}

bool _ByteArray::isEmpty() {
    if(buff == nullptr || _size == 0) {
        return true;
    }

    return false;
}

char _ByteArray::at(int index) {
    if(index >= _size) {
        throw createArrayIndexOutOfBoundsException(createString("ByteArray"),_size,index);
    }
    return buff[index];
}

int _ByteArray::fill(char v) {
    if(buff == nullptr) {
        return -ByteArrayNoMemory;
    }

    memset(buff,v,_size);
    
    return 0;
}

int _ByteArray::fill(int index,char v) {
    if(buff == nullptr) {
        return -ByteArrayNoMemory;
    }

    if(index >= _size || index < 0) {
        return -ByteArrayWrongParam;
    }
    //printf("fill index is %d,v is %d",index,v);
    buff[index] = v;

    return 0;
}

int _ByteArray::fill(int index,int length,char v) {
    if(buff == nullptr) {
        return -ByteArrayNoMemory;
    }

    if((index >= _size) 
        || (index < 0)
        || (index + length > _size)) {
        return -ByteArrayWrongParam;
    }

    memset(&buff[index],v,length);

    return 0;
}

int _ByteArray::append(sp<_ByteArray> b) {
    if(b == nullptr) {
        return -ByteArrayWrongParam;
    }

    if(buff == nullptr) {
        buff = (char *)malloc(b->size());
        _size = b->size();
        memcpy(buff,b->toValue(),b->size());
        return 0;
    }

    char *newData = (char *)malloc(_size + b->size());
    memcpy(newData,buff,_size);
    memcpy(newData + _size,b->toValue(),b->size());

    free(buff);
    buff = newData;
    _size = _size + b->size();
    return 0;
}

String _ByteArray::toString() {
    //printf("buff buff is %s ,_size is %d\n",buff,_size);
    char _buff[_size + 1];
    memset(_buff,0,_size+1);
    memcpy(_buff,buff,_size);
    return createString(&_buff[0],0,_size + 1);
}

}
