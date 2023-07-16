#include "Des.hpp"

namespace obotcha {

ByteArray _Des::encrypt(ByteArray input) {
    DES_key_schedule schedule;
    
    switch(getPattern()) {
        case ECB: {
            DES_set_key_unchecked((const_DES_cblock *)getSecretKey()->get(), &schedule);
            return _desECB(input,&schedule);
        }

        case CBC: {
            DES_set_key_checked((const_DES_cblock *)getSecretKey()->get(), &schedule);
            DES_cblock ivec;
            memset((char*)&ivec, 0, sizeof(ivec));
            return _desCBC(input,&schedule,&ivec);
        }
    }

    return nullptr;
}

ByteArray _Des::decrypt(ByteArray input) {
    return encrypt(input);
}

ByteArray _Des::_desECB(ByteArray data,DES_key_schedule *schedule) {
    int type = DES_DECRYPT;
    if(getMode() == Encrypt) {
        doPadding(data,8);
        type = DES_ENCRYPT;
    }

    int inputSize = data->size();

    ByteArray out = createByteArray(inputSize);
    unsigned char *output = (unsigned char*)out->toValue();
    unsigned char *input = (unsigned char*)data->toValue();
    
    for(int i = 0; i < inputSize / 8; i++){
        DES_ecb_encrypt((const_DES_cblock *)(input + i*sizeof(const_DES_cblock)),
                            (DES_cblock *)(output + i*sizeof(DES_cblock)), 
                            schedule, 
                            type);
    }

    if(getMode() == Decrypt) {
        doUnPadding(out);
    }
    return out;
}

ByteArray _Des::_desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec) {
    int type = DES_DECRYPT;
    if(getMode() == Encrypt) {
        doPadding(data,8);
        type = DES_ENCRYPT;
    }

    ByteArray out = createByteArray(data->size());

    unsigned char *output = (unsigned char *)out->toValue();
    unsigned char *input = (unsigned char *)data->toValue();

    DES_ncbc_encrypt(input, output, data->size(), schedule, ivec, type);
    
    if(getMode() == Decrypt) {
        doUnPadding(out);
    }
    return out;
}

}
