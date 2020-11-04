#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Des.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "Error.hpp"

namespace obotcha {

ByteArray _Des::encrypt(ByteArray input) {
    
    DES_key_schedule schedule;
    DES_set_key_checked((const_DES_cblock *)getSecretKey()->get(), &schedule);

    switch(getPattern()) {
        case ECB:
            return _desECB(input,&schedule);
        break;

        case CBC:
            DES_cblock ivec;
            memset((char*)&ivec, 0, sizeof(ivec));
            return _desCBC(input,&schedule,&ivec);
        break;
    }

    return nullptr;
}

ByteArray _Des::decrypt(ByteArray input) {

    DES_key_schedule schedule;
    DES_set_key_checked((const_DES_cblock *)getSecretKey()->get(), &schedule);

    switch(getPattern()) {
        case ECB:
            return _desECB(input,&schedule);
        break;

        case CBC:
            DES_cblock ivec;
            memset((char*)&ivec, 0, sizeof(ivec));
            return _desCBC(input,&schedule,&ivec);
        break;
    }

    return nullptr;
}

ByteArray _Des::_desECB(ByteArray data,DES_key_schedule *schedule) {
    doPadding(data,8);
    int inputSize = data->size();

    ByteArray out = createByteArray(inputSize);
    unsigned char *output = (unsigned char*)out->toValue();
    unsigned char *input = (unsigned char*)data->toValue();
    const_DES_cblock inputBuff;
    DES_cblock outputBuff;
    
    for(int i = 0; i < inputSize / 8; i++){
        memcpy(inputBuff,input,8);
        switch(getMode()) {
            case Decrypt:
                DES_ecb_encrypt(&inputBuff, &outputBuff, schedule, DES_DECRYPT);
            break;

            case Encrypt:
                DES_ecb_encrypt(&inputBuff, &outputBuff, schedule, DES_ENCRYPT);
            break;
        }
        
        memcpy(output,outputBuff,8);

        input += 8;
        output += 8;
    }

    doUnPadding(out);
    return out;
}

ByteArray _Des::_desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec) {
    if(getMode() == Encrypt) {
        doPadding(data,8);
    }

    ByteArray out = createByteArray(data->size());

    unsigned char *output = (unsigned char *)out->toValue();
    unsigned char *input = (unsigned char *)data->toValue();
    switch(getMode()) {
        case Decrypt:
            DES_ncbc_encrypt(input, output, data->size(), schedule, ivec, DES_DECRYPT);
        break;

        case Encrypt:
            DES_ncbc_encrypt(input, output, data->size(), schedule, ivec, DES_ENCRYPT);
        break; 
    }
    
    if(getMode() == Decrypt) {
        doUnPadding(out);
    }
    return out;
}


}
