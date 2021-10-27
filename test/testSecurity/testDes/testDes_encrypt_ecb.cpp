#include "Des.hpp"
#include "SecretKeyCreator.hpp"
#include "FileOutputStream.hpp"
#include "CipherCreator.hpp"
#include "Md.hpp"

using namespace obotcha;

//openssl des-ecb -e -nosalt -in ./tmp/des_encrypt_ecb_data -out decode.txt -kfile tmp/test_des_encrypt_ecb_enckey

void testDesEncryptEcb() {
  //create test data
  File data = createFile("./tmp/des_encrypt_ecb_data");
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
    SecretKey secretKey = st(SecretKeyCreator)::getInstance("DES");
    secretKey->generate(createString("./tmp/test_des_encrypt_ecb_deckey"),
                        createString("./tmp/test_des_encrypt_ecb_enckey"),
                        key);

    //pkcs5
    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("DES");
      enckey->loadEncryptKey("./tmp/test_des_encrypt_ecb_enckey");
      Cipher des = st(CipherCreator)::getInstance("DES/ECB/PKCS5Padding");
      des->init(st(Cipher)::Encrypt,enckey);
      des->encrypt(data,"./tmp/des_encrypt_ecb_outdata_pksc5");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("DES");
      deckey->loadDecryptKey("./tmp/test_des_encrypt_ecb_deckey");
      Cipher des2 = st(CipherCreator)::getInstance("DES/ECB/PKCS5Padding");
      des2->init(st(Cipher)::Decrypt,deckey);
      des2->decrypt("./tmp/des_encrypt_ecb_outdata_pksc5","./tmp/des_encrypt_ecb_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/des_encrypt_ecb_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestDes Ecb PKCS5Padding case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("DES");
      enckey->loadEncryptKey("./tmp/test_des_encrypt_ecb_enckey");
      Cipher des = st(CipherCreator)::getInstance("DES/ECB/PKCS7Padding");
      des->init(st(Cipher)::Encrypt,enckey);
      des->encrypt(data,"./tmp/des_encrypt_ecb_outdata_pksc7");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("DES");
      deckey->loadDecryptKey("./tmp/test_des_encrypt_ecb_deckey");
      Cipher des2 = st(CipherCreator)::getInstance("DES/ECB/PKCS7Padding");
      des2->init(st(Cipher)::Decrypt,deckey);
      des2->decrypt("./tmp/des_encrypt_ecb_outdata_pksc7","./tmp/des_encrypt_ecb_outdata_pksc7_dec");
      String result = md5sum->encrypt(createFile("./tmp/des_encrypt_ecb_outdata_pksc7_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestDes Ecb PKCS5Padding case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("DES");
      enckey->loadEncryptKey("./tmp/test_des_encrypt_ecb_enckey");
      Cipher des = st(CipherCreator)::getInstance("DES/ECB/PKCS7Padding");
      des->init(st(Cipher)::Encrypt,enckey);
      des->encrypt(data,"./tmp/des_encrypt_ecb_outdata_pksc7");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("DES");
      deckey->loadDecryptKey("./tmp/test_des_encrypt_ecb_deckey");
      Cipher des2 = st(CipherCreator)::getInstance("DES/ECB/PKCS7Padding");
      des2->init(st(Cipher)::Decrypt,deckey);
      des2->decrypt("./tmp/des_encrypt_ecb_outdata_pksc7","./tmp/des_encrypt_ecb_outdata_pksc7_dec");
      String result = md5sum->encrypt(createFile("./tmp/des_encrypt_ecb_outdata_pksc7_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestDes Ecb PKCS7Padding case2] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey enckey = st(SecretKeyCreator)::getInstance("DES");
      enckey->loadEncryptKey("./tmp/test_des_encrypt_ecb_enckey");
      Cipher des = st(CipherCreator)::getInstance("DES/ECB/ZeroPading");
      des->init(st(Cipher)::Encrypt,enckey);
      des->encrypt(data,"./tmp/des_encrypt_ecb_outdata_pksc0");

      SecretKey deckey = st(SecretKeyCreator)::getInstance("DES");
      deckey->loadDecryptKey("./tmp/test_des_encrypt_ecb_deckey");
      Cipher des2 = st(CipherCreator)::getInstance("DES/ECB/ZeroPading");
      des2->init(st(Cipher)::Decrypt,deckey);
      des2->decrypt("./tmp/des_encrypt_ecb_outdata_pksc0","./tmp/des_encrypt_ecb_outdata_pksc0_dec");
      String result = md5sum->encrypt(createFile("./tmp/des_encrypt_ecb_outdata_pksc0_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestDes Ecb ZeroPading case3] [FAILED]--- \n");
      }
      break;
    }

    break;
  }
}
