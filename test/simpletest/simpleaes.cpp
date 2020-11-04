#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"
#include "CipherCreator.hpp"
#include "SecretKeyCreator.hpp"
#include "File.hpp"

using namespace obotcha;

int main() {

    /*SecretKeyGenerator generator = createSecretKeyGenerator();
    generator->genKey("./encryptKey","./decryptKey","AES/abcdefgh");*/

    //AES

    SecretKey enckey = st(SecretKeyCreator)::getInstance("AES");
    enckey->generate(createString("./deckey"),createString("./enckey"),createString("hello world"));

    SecretKey enckey2 = st(SecretKeyCreator)::getInstance("AES");
    enckey2->loadEncryptKey("./enckey");

    Cipher aes = st(CipherCreator)::getInstance("AES/ECB/PKCS5Padding");
    aes->init(st(Cipher)::Encrypt,enckey2);
    aes->encrypt(createFile("./simpleTest_"),createFile("./encdata"));


    SecretKey enckey3 = st(SecretKeyCreator)::getInstance("AES");
    enckey3->loadDecryptKey("./enckey");
    Cipher aes3 = st(CipherCreator)::getInstance("AES/ECB/PKCS5Padding");
    aes3->init(st(Cipher)::Decrypt,enckey3);
    aes3->decrypt("./encdata","./decryptdata");

    
}
