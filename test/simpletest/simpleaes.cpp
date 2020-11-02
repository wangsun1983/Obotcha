#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"
#include "CipherCreator.hpp"
#include "SecretKeyGenerator.hpp"

using namespace obotcha;

int main() {

    /*SecretKeyGenerator generator = createSecretKeyGenerator();
    generator->genKey("./encryptKey","./decryptKey","AES/abcdefgh");*/


    SecretKey enckey = st(SecretKeyGenerator)::loadKey("./encryptKey");
    Cipher aes = st(CipherCreator)::getInstance("AES/ECB/PKCS5Padding");
    aes->init(st(Cipher)::Encrypt,enckey);

    aes->encrypt("./simpleTest_","./encdata");
    

    
}
