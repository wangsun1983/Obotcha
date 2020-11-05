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
    printf("trace1 \n");
    SecretKey enckey = st(SecretKeyCreator)::getInstance("RSA");
    enckey->generate(createString("./deckey"),createString("./enckey"),createString("RSAF4/PKCS1Padding"));
    printf("trace2 \n");

    SecretKey enckey2 = st(SecretKeyCreator)::getInstance("RSA");
    enckey2->loadEncryptKey("./enckey");
    printf("trace3 \n");
    Cipher aes = st(CipherCreator)::getInstance("RSA/ECB/PKCS1Padding");
    aes->init(st(Cipher)::Encrypt,enckey2);
    aes->encrypt(createFile("./simpleTest_"),createFile("./encdata"));
    printf("trace4 \n");

    SecretKey enckey3 = st(SecretKeyCreator)::getInstance("RSA");
    enckey3->loadDecryptKey("./deckey");
    Cipher aes3 = st(CipherCreator)::getInstance("RSA/ECB/PKCS1Padding");
    aes3->init(st(Cipher)::Decrypt,enckey3);
    aes3->decrypt("./encdata","./decryptdata");


}
