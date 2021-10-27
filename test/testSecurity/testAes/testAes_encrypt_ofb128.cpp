#include "Aes.hpp"
#include "SecretKeyCreator.hpp"
#include "FileOutputStream.hpp"
#include "CipherCreator.hpp"
#include "Md.hpp"

using namespace obotcha;

//openssl Aes-Ofb -e -nosalt -in ./tmp/Aes_encrypt_Ofb_data -out decode.txt -kfile tmp/test_Aes_encrypt_Ofb_enckey

void testAesEncryptOfb128() {
  //create test data
  File data = createFile("./tmp/Aes_encrypt_Ofb_data");
  if(!data->exists()) {
    data->createNewFile();
  }

  FileOutputStream stream = createFileOutputStream(data);
  String str = createString("abcdefghi");
  stream->open();
  stream->write(str->toByteArray());
  stream->close();

  String key = createString("1234567812345678");
  Md md5sum = createMd(st(Md)::Md5);
  String testDataMd5 = md5sum->encrypt(data);


  printf("trace1 \n");
  //pkcs5
  while(1) {
    SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/OFB128");
    secretKey->generate(createString("./tmp/test_Aes_encrypt_Ofb128_deckey"),
                        createString("./tmp/test_Aes_encrypt_Ofb128_enckey"),
                        key);

    printf("trace1_1 \n");
    SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/OFB128");
    enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Ofb128_enckey");
    Cipher Aes = st(CipherCreator)::getInstance("AES/OFB128/PKCS5Padding");
    Aes->init(st(Cipher)::Encrypt,enckey);
    Aes->encrypt(data,"./tmp/Aes_encrypt_Ofb128_outdata_pksc5");
    printf("trace1_2\n");
    SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/OFB128");
    deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Ofb128_deckey");
    Cipher Aes2 = st(CipherCreator)::getInstance("AES/OFB128/PKCS5Padding");
    Aes2->init(st(Cipher)::Decrypt,deckey);
    Aes2->decrypt("./tmp/Aes_encrypt_Ofb128_outdata_pksc5","./tmp/Aes_encrypt_Ofb128_outdata_pksc5_dec");
    String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Ofb128_outdata_pksc5_dec"));

    if(!result->equals(testDataMd5)) {
      printf("---[TestAes Ofb128 PKCS5Padding case1] [FAILED]--- \n");
    }
    break;
  }
  printf("---[TestAes Ofb case100] [OK]--- \n");
}
