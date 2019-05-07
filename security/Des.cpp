#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Des.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

_Des::_Des(int destype) {
    mDesType = destype;
}

_Des::_Des() {
    mDesType = DesTypeECB;
}

void _Des::encrypt(File src,File des) {
    if(!des->exists()) {
        des->createNewFile();
    }

    switch(mDesType) {
        case DesTypeECB:
        //TODO
        break;

        case DesTypeCBC: {
            FileInputStream inputStream = createFileInputStream(src);
            inputStream->open();

            //calcute size for 8 byte
            int inputSize = src->length();
            int length = (inputSize%8 == 0)?(inputSize + 8):(inputSize/8)*8 + 8;
            ByteArray inputData = createByteArray(length);
            inputStream->readAll(inputData);

            //we should fill the last 8 byte data;
            if(inputSize%8 == 0) {
                char *lastData = inputData->toValue() + (inputData->size() - 1) - 8;
                memset(lastData,0,8);
            } else {
                int padding = inputSize%8;
                char *p = inputData->toValue();
                char *lastData = inputData->toValue() + inputData->size()  - 8 + padding;
                memset(lastData,(char)padding,8-padding);
            }

            if(inputData != nullptr) {
                char *p = inputData->toValue();
                ByteArray outputData = encrypt(inputData);
                FileOutputStream outputStream = createFileOutputStream(des);
                outputStream->open(st(FileOutputStream)::FileOpenType::Trunc);
                char *finalresult = outputData->toValue();
                outputStream->write(outputData);
                outputStream->flush();
                outputStream->close();
            }
            inputStream->close();
            break;
        }
    }
}

ByteArray _Des::encrypt(ByteArray input) {
    
    DES_key_schedule schedule;
    DES_set_key_checked(&mKey, &schedule);

    switch(mDesType) {
        case DesTypeECB:
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
    printf("wangsl,decrypt 1 \n");
    if(!des->exists()) {
        des->createNewFile();
    }

    switch(mDesType) {
        case DesTypeECB:
        //TODO
        break;

        case DesTypeCBC:{
            FileInputStream inputStream = createFileInputStream(src);
            inputStream->open();
            ByteArray inputData = inputStream->readAll();
            if(inputData != nullptr) {
                ByteArray outputData = decrypt(inputData);
                char *finalresult = outputData->toValue();

                FileOutputStream outputStream = createFileOutputStream(des);
                outputStream->open(st(FileOutputStream)::FileOpenType::Trunc);

                //we should check last 8byte
                char *checkP = outputData->toValue();
                int length = outputData->size();

                int padding = 0;
                if(checkP[(length-1)] != 0) {
                    padding = checkP[(length-1)];
                }
                
                if(padding == 0) {
                    outputStream->write(outputData,length - 8);
                } else {
                    outputStream->write(outputData,length - 8 + padding);
                }
                outputStream->flush();
                outputStream->close();
            }

            inputStream->close();
            break;
        }
    }
}

ByteArray _Des::decrypt(ByteArray input) {

    DES_key_schedule schedule;
    DES_set_key_checked(&mKey, &schedule);

    switch(mDesType) {
        case DesTypeECB:
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

ByteArray _Des::_desECB(ByteArray data,DES_key_schedule *schedule,int mode) {
    int inputSize = data->size();

    int length = (inputSize%8 == 0)?inputSize:(inputSize/8)*8 + 8;
    
    ByteArray out = createByteArray(length);
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
        DES_ecb_encrypt(&inputBuff, &outputBuff, schedule, mode);
        memcpy(output,outputBuff,8);
    }

    return out;
}

ByteArray _Des::_desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec,int mode) {
    
    ByteArray out;
    int inputSize = data->size();
    int outputSize = inputSize%8?(inputSize/8 + 1) * 8 : inputSize;  
    printf("_desCBC outputSize %d,input is %d \n",outputSize,inputSize);

    if(mode == DesEncrypt) {
        out = createByteArray(outputSize);
    } else {
        out = createByteArray(outputSize);
    }

    unsigned char *output = (unsigned char *)out->toValue();
    unsigned char *input = (unsigned char *)data->toValue();
    printf("_desCBC input is %s \n",input);

    DES_ncbc_encrypt(input, output, data->size(), schedule, ivec, mode);
    printf("_desCBC output is %s,length is %d \n",output,out->size());
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
