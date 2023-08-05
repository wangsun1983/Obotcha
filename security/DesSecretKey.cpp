#include "DesSecretKey.hpp"

namespace obotcha {

const size_t _DesSecretKey::DesKeySize = 8;

std::any _DesSecretKey::get() {
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

int _DesSecretKey::saveKey(String filepath,DES_cblock *block) const {
    FILE *key_file = fopen(filepath->toChars(), "wb");
    if(key_file == nullptr) {
        return -ENOENT;
    }

    auto bytes_written = fwrite(block, 1, DesKeySize, key_file);
    fclose(key_file);
    return (bytes_written == DesKeySize)?0:-1;
}

int _DesSecretKey::loadKey(String path) {
    FILE *key_file = fopen(path->toChars(), "rb");
    if (!key_file) {
        return -ENOENT;
    }

    auto bytes_read = fread(&mKey, sizeof(unsigned char), DesKeySize, key_file);
    fclose(key_file);
    return (bytes_read == DesKeySize)?0:-1;
}

}
