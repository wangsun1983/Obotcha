#include "Aes.hpp"
#include "SecretKeyCreator.hpp"
#include "FileOutputStream.hpp"
#include "CipherCreator.hpp"
#include "Md.hpp"

using namespace obotcha;

//openssl AES128-ecb -e -nosalt -in ./tmp/AES128_encrypt_ecb_data -out decode.txt -kfile tmp/test_AES128_encrypt_ecb_enckey

void testAes128EncryptEcb() {
  //create test data
  File data = createFile("./tmp/AES128_encrypt_ecb_data");
  if(!data->exists()) {
    data->createNewFile();
  }

  FileOutputStream stream = createFileOutputStream(data);
  String str = createString("abcdefghi");
  stream->open();
  stream->write(str->toByteArray());
  stream->close();

  String key = createString("12345678");
  Md md5sum = createMd(st(Md)::Md5);
  String testDataMd5 = md5sum->encrypt(data);

  while(1) {
    //create a test data
    SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES128");
    secretKey->generate(createString("./tmp/test_AES128_encrypt_ecb_deckey"),
                        createString("./tmp/test_AES128_encrypt_ecb_enckey"),
                        key);

    //pkcs5
    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES128");
      enckey->loadEncryptKey("./tmp/test_AES128_encrypt_ecb_enckey");
      Cipher AES128 = st(CipherCreator)::getInstance("AES128/ECB/PKCS5Padding");
      AES128->init(st(Cipher)::Encrypt,enckey);
      AES128->encrypt(data,"./tmp/AES128_encrypt_ecb_outdata_pksc5");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES128");
      deckey->loadDecryptKey("./tmp/test_AES128_encrypt_ecb_deckey");
      Cipher AES1282 = st(CipherCreator)::getInstance("AES128/ECB/PKCS5Padding");
      AES1282->init(st(Cipher)::Decrypt,deckey);
      AES1282->decrypt("./tmp/AES128_encrypt_ecb_outdata_pksc5","./tmp/AES128_encrypt_ecb_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/AES128_encrypt_ecb_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAES128 Ecb PKCS5Padding case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES128");
      enckey->loadEncryptKey("./tmp/test_AES128_encrypt_ecb_enckey");
      Cipher AES128 = st(CipherCreator)::getInstance("AES128/ECB/PKCS7Padding");
      AES128->init(st(Cipher)::Encrypt,enckey);
      AES128->encrypt(data,"./tmp/AES128_encrypt_ecb_outdata_pksc7");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES128");
      deckey->loadDecryptKey("./tmp/test_AES128_encrypt_ecb_deckey");
      Cipher AES1282 = st(CipherCreator)::getInstance("AES128/ECB/PKCS7Padding");
      AES1282->init(st(Cipher)::Decrypt,deckey);
      AES1282->decrypt("./tmp/AES128_encrypt_ecb_outdata_pksc7","./tmp/AES128_encrypt_ecb_outdata_pksc7_dec");
      String result = md5sum->encrypt(createFile("./tmp/AES128_encrypt_ecb_outdata_pksc7_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAES128 Ecb PKCS5Padding case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES128");
      enckey->loadEncryptKey("./tmp/test_AES128_encrypt_ecb_enckey");
      Cipher AES128 = st(CipherCreator)::getInstance("AES128/ECB/PKCS7Padding");
      AES128->init(st(Cipher)::Encrypt,enckey);
      AES128->encrypt(data,"./tmp/AES128_encrypt_ecb_outdata_pksc7");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES128");
      deckey->loadDecryptKey("./tmp/test_AES128_encrypt_ecb_deckey");
      Cipher AES1282 = st(CipherCreator)::getInstance("AES128/ECB/PKCS7Padding");
      AES1282->init(st(Cipher)::Decrypt,deckey);
      AES1282->decrypt("./tmp/AES128_encrypt_ecb_outdata_pksc7","./tmp/AES128_encrypt_ecb_outdata_pksc7_dec");
      String result = md5sum->encrypt(createFile("./tmp/AES128_encrypt_ecb_outdata_pksc7_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAES128 Ecb PKCS7Padding case2] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES128");
      enckey->loadEncryptKey("./tmp/test_AES128_encrypt_ecb_enckey");
      Cipher AES128 = st(CipherCreator)::getInstance("AES128/ECB/ZeroPading");
      AES128->init(st(Cipher)::Encrypt,enckey);
      AES128->encrypt(data,"./tmp/AES128_encrypt_ecb_outdata_pksc0");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES128");
      deckey->loadDecryptKey("./tmp/test_AES128_encrypt_ecb_deckey");
      Cipher AES1282 = st(CipherCreator)::getInstance("AES128/ECB/ZeroPading");
      AES1282->init(st(Cipher)::Decrypt,deckey);
      AES1282->decrypt("./tmp/AES128_encrypt_ecb_outdata_pksc0","./tmp/AES128_encrypt_ecb_outdata_pksc0_dec");
      String result = md5sum->encrypt(createFile("./tmp/AES128_encrypt_ecb_outdata_pksc0_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAES128 Ecb ZeroPading case3] [FAILED]--- \n");
      }
      break;
    }

    break;
  }
  printf("---[TestAES128 cbc case100] [OK]--- \n");
}
