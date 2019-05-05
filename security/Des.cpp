#include "Des.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace obotcha {

_Des::_Des(int destype) {
    mDesType = destype;
}

_Des::_Des() {
    mDesType = DesTypeEBC;
}

void _Des::encrypt(File src,File des) {
    //TODO
}

ByteArray _Des::encrypt(ByteArray input) {
    
    DES_key_schedule schedule;
    DES_set_key_checked(&mKey, &schedule);

    switch(mDesType) {
        case DesTypeEBC:
            return _desECB(input,&schedule,DesEncrypt);
        break;

        case DesTypeCBC:
            DES_cblock ivec;
            memset((char*)&ivec, 0, sizeof(ivec));
            return _desCBC(input,&schedule,&ivec,DesEncrypt);
        break;
    }

    return nullptr;
}

void _Des::decrypt(File src,File des) {
    //TODO
}

ByteArray _Des::decrypt(ByteArray input) {

    DES_key_schedule schedule;
    DES_set_key_checked(&mKey, &schedule);

    switch(mDesType) {
        case DesTypeEBC:
            return _desECB(input,&schedule,DesDecrypt);
        break;

        case DesTypeCBC:
            DES_cblock ivec;
            memset((char*)&ivec, 0, sizeof(ivec));
            return _desCBC(input,&schedule,&ivec,DesDecrypt);
        break;
    }

    return nullptr;
}

void _Des::genKey(File file) {
    _genKey();
    _saveKey(file->getAbsolutePath());
}

void _Des::genKey(String filepath) {
    _genKey();
    _saveKey(filepath);
}

void _Des::genKey(const char * filepath) {
    _genKey();
    _saveKey(createString(filepath));
}

void _Des::genKey(File file,String content) {
    _genKey(content);
    _saveKey(file->getAbsolutePath());
}

void _Des::genKey(String filepath,String content) {
    _genKey(content);
    _saveKey(filepath);
}

void _Des::genKey(const char * filepath,String content) {
    _genKey(content);
    _saveKey(createString(filepath));
}

void _Des::loadKey(File file) {
    loadKey(file->getAbsolutePath()->toChars());
}

void _Des::loadKey(String filepath) {
    loadKey(filepath->toChars());
}

void _Des::loadKey(const char *filepath) {
    FILE *key_file = fopen(filepath, "rb");
    if (!key_file) {
        printf("loadKey trace2 \n");
        return;
    }

    short int bytes_read;
    unsigned short int padding; 
    //unsigned char* des_key = (unsigned char*) malloc(8*sizeof(char));
    bytes_read = fread(&mKey, sizeof(unsigned char), DES_KEY_SIZE, key_file);
    if (bytes_read != DES_KEY_SIZE) {
        fclose(key_file);
        //free(des_key);
        printf("trace3 \n");
        return;
    }
    
    fclose(key_file);
}

ByteArray _desECB(ByteArray data,DES_key_schedule *schedule,int mode) {
    int inputSize = data->size();
    ByteArray out = createByteArray(inputSize);
    unsigned char *output = (unsigned char*)out->toValue();
    unsigned char *input = (unsigned char*)data->toValue();
    const_DES_cblock inputBuff;
    DES_cblock outputBuff;

    for(int i = 0; i < inputSize / 8; i++){
        memcpy(inputBuff,input,8);
        DES_ecb_encrypt(&inputBuff, &outputBuff, schedule, mode);
        memcpy(output,outputBuff,8);

        input += 8;
        output += 8;
    }

    if (inputSize%8 != 0) {
        memset(inputBuff, 0, 8);  
        memcpy(inputBuff,input,inputSize%8);  
        DES_ecb_encrypt(&inputBuff, &outputBuff, schedule, DES_ENCRYPT);
        memcpy(output,outputBuff,8);
    }

    return out;
}

ByteArray _desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec,int mode) {
    
    ByteArray out;
    int inputSize = data->size();
    int outputSize = inputSize%8?(inputSize/8 + 1) * 8 : inputSize;  

    if(mode == DesEncrypt) {
        out = createByteArray(outputSize + 16);
    } else {
        out = createByteArray(outputSize);
    }

    unsigned char *output = (unsigned char *)out->toValue();
    unsigned char *input = (unsigned char *)data->toValue();

    DES_ncbc_encrypt(input, output, data->size(), schedule, ivec, mode);

    return out;
}

void _Des::_genKey(String content) {
    DES_string_to_key(content->toChars(), &mKey);
}

void _Des::_genKey() {
    DES_random_key(&mKey);
}

void _Des::_saveKey(String filepath) {
    FILE *key_file = fopen(filepath->toChars(), "wb");
    short int bytes_written = fwrite(&mKey, 1, DES_KEY_SIZE, key_file);
    if (bytes_written != DES_KEY_SIZE) {
        fclose(key_file);
        //free(des_key);
        return;
    }

    //free(des_key);
    fclose(key_file);
}

}
