#include "Des.hpp"
#include "Log.hpp"
#include "Cipher.hpp"

namespace obotcha {

ByteArray _Des::encryptContent(ByteArray input) {
    DES_key_schedule schedule;
    
    switch(getPattern()) {
        case st(Cipher)::Pattern::ECB: {
            DES_set_key_unchecked(std::any_cast<const_DES_cblock *>(getSecretKey()->get()), &schedule);
            return _desECB(input,&schedule);
        }

        case st(Cipher)::Pattern::CBC: {
            DES_set_key_checked(std::any_cast<const_DES_cblock *>(getSecretKey()->get()), &schedule);
            DES_cblock ivec;
            memset((char*)&ivec, 0, sizeof(ivec));
            return _desCBC(input,&schedule,&ivec);
        }

        default:
            LOG(ERROR)<<"Des encryptContent unknow pattern:"<<static_cast<int>(getPattern());
    }

    return nullptr;
}

ByteArray _Des::decryptContent(ByteArray input) {
    return encryptContent(input);
}

ByteArray _Des::_desECB(ByteArray data,DES_key_schedule *schedule) const {
    int type = DES_DECRYPT;
    if(getMode() == st(Cipher)::Mode::Encrypt) {
        doPadding(data,8);
        type = DES_ENCRYPT;
    }

    size_t inputSize = data->size();

    ByteArray out = createByteArray(inputSize);
    auto output = out->toValue();
    auto input = data->toValue();
    
    for(size_t i = 0; i < inputSize / 8; i++){
        DES_ecb_encrypt((const_DES_cblock *)(input + i*sizeof(const_DES_cblock)),
                            (DES_cblock *)(output + i*sizeof(DES_cblock)), 
                            schedule, 
                            type);
    }

    if(getMode() == st(Cipher)::Mode::Decrypt) {
        doUnPadding(out);
    }
    return out;
}

ByteArray _Des::_desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec) const {
    int type = DES_DECRYPT;
    if(getMode() == st(Cipher)::Mode::Encrypt) {
        doPadding(data,8);
        type = DES_ENCRYPT;
    }

    ByteArray out = createByteArray(data->size());

    auto output = out->toValue();
    auto input = data->toValue();

    DES_ncbc_encrypt(input, output, data->size(), schedule, ivec, type);
    
    if(getMode() == st(Cipher)::Mode::Decrypt) {
        doUnPadding(out);
    }
    return out;
}

}
