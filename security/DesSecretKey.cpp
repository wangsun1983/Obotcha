#include "DesSecretKey.hpp"
#include "Error.hpp"

namespace obotcha {

const int _DesSecretKey::DesKeySize = 8;

void * _DesSecretKey::get() {
    return &mKey;
}
    
int _DesSecretKey::loadEncryptKey(String path) {
    return loadKey(path);
}

int _DesSecretKey::loadDecryptKey(String path) {
    return loadKey(path);
}

int _DesSecretKey::generate(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    DES_cblock key;
    if(params != nullptr && params->size() != 0) {
        DES_string_to_key(params->get(0)->toChars(), &key);
    } else {
        DES_random_key(&key);
    }
    
    return (saveKey(decKeyFile,&key) == 0) && (saveKey(encKeyFile,&key) == 0);
}

int _DesSecretKey::saveKey(String filepath,DES_cblock *block) {
    FILE *key_file = fopen(filepath->toChars(), "wb");
    if(key_file == nullptr) {
        return -OpenFail;
    }

    short int bytes_written = fwrite(block, 1, DesKeySize, key_file);
    if (bytes_written != DesKeySize) {
        fclose(key_file);
        return -WriteFail;
    }

    fclose(key_file);
    return 0;
}

int _DesSecretKey::loadKey(String path) {
    FILE *key_file = fopen(path->toChars(), "rb");
    if (!key_file) {
        return -FileNotExists;
    }

    short int bytes_read;
    bytes_read = fread(&mKey, sizeof(unsigned char), DesKeySize, key_file);
    if (bytes_read != DesKeySize) {
        fclose(key_file);
        return -OpenFail;
    }
    
    fclose(key_file);
    return 0;
}

}
