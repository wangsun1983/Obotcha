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

int testDes() {

    /*SecretKeyGenerator generator = createSecretKeyGenerator();
    generator->genKey("./encryptKey","./decryptKey","AES/abcdefgh");*/

    //AES
    printf("trace1 \n");
    SecretKey enckey = st(SecretKeyCreator)::getInstance("DES");
    enckey->generate(createString("./deckey"),createString("./enckey"),createString("hello world"));
    printf("trace2 \n");
    SecretKey enckey2 = st(SecretKeyCreator)::getInstance("DES");
    enckey2->loadEncryptKey("./enckey");
    printf("trace3 \n");
    Cipher aes = st(CipherCreator)::getInstance("DES/CBC/PKCS5Padding");
    aes->init(st(Cipher)::Encrypt,enckey2);
    aes->encrypt(createFile("./simpleTest_"),createFile("./encdata"));
    printf("trace4 \n");
    SecretKey enckey3 = st(SecretKeyCreator)::getInstance("DES");
    enckey3->loadDecryptKey("./deckey");
    Cipher aes3 = st(CipherCreator)::getInstance("DES/CBC/PKCS5Padding");
    aes3->init(st(Cipher)::Decrypt,enckey3);
    aes3->decrypt("./encdata","./decryptdata");


}
