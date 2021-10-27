#include "Aes.hpp"
#include "SecretKeyCreator.hpp"
#include "FileOutputStream.hpp"
#include "CipherCreator.hpp"
#include "Md.hpp"

using namespace obotcha;

//openssl Aes-Cfb -e -nosalt -in ./tmp/Aes_encrypt_Cfb_data -out decode.txt -kfile tmp/test_Aes_encrypt_Cfb_enckey

void testAesEncryptCfb() {
  //create test data
  File data = createFile("./tmp/Aes_encrypt_Cfb_data");
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
    SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB1");
    secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb1_deckey"),
                        createString("./tmp/test_Aes_encrypt_Cfb1_enckey"),
                        key);

    printf("trace1_1 \n");
    SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB1");
    enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb1_enckey");
    Cipher Aes = st(CipherCreator)::getInstance("AES/CFB1/PKCS5Padding");
    Aes->init(st(Cipher)::Encrypt,enckey);
    Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb1_outdata_pksc5");
    printf("trace1_2\n");
    SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB1");
    deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb_deckey");
    Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB1/PKCS5Padding");
    Aes2->init(st(Cipher)::Decrypt,deckey);
    Aes2->decrypt("./tmp/Aes_encrypt_Cfb1_outdata_pksc5","./tmp/Aes_encrypt_Cfb1_outdata_pksc5_dec");
    String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb1_outdata_pksc5_dec"));

    if(!result->equals(testDataMd5)) {
      printf("---[TestAes Cfb1 PKCS5Padding case1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB8");
    secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb8_deckey"),
                        createString("./tmp/test_Aes_encrypt_Cfb8_enckey"),
                        key);

    printf("trace1_1 \n");
    SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB8");
    enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb8_enckey");
    Cipher Aes = st(CipherCreator)::getInstance("AES/CFB8/PKCS5Padding");
    Aes->init(st(Cipher)::Encrypt,enckey);
    Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb8_outdata_pksc5");
    printf("trace1_2\n");
    SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB8");
    deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb8_deckey");
    Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB8/PKCS5Padding");
    Aes2->init(st(Cipher)::Decrypt,deckey);
    Aes2->decrypt("./tmp/Aes_encrypt_Cfb8_outdata_pksc5","./tmp/Aes_encrypt_Cfb8_outdata_pksc5_dec");
    String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb8_outdata_pksc5_dec"));

    if(!result->equals(testDataMd5)) {
      printf("---[TestAes Cfb1 case2] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB8");
    secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb128_deckey"),
                        createString("./tmp/test_Aes_encrypt_Cfb128_enckey"),
                        key);

    printf("trace1_1 \n");
    SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB128");
    enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb128_enckey");
    Cipher Aes = st(CipherCreator)::getInstance("AES/CFB128/PKCS5Padding");
    Aes->init(st(Cipher)::Encrypt,enckey);
    Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb128_outdata_pksc5");
    printf("trace1_2\n");
    SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB128");
    deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb128_deckey");
    Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB128/PKCS5Padding");
    Aes2->init(st(Cipher)::Decrypt,deckey);
    Aes2->decrypt("./tmp/Aes_encrypt_Cfb128_outdata_pksc5","./tmp/Aes_encrypt_Cfb128_outdata_pksc5_dec");
    String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb128_outdata_pksc5_dec"));

    if(!result->equals(testDataMd5)) {
      printf("---[TestAes Cfb1 case3] [FAILED]--- \n");
    }
    break;
  }

  //-------------------
    //create a test data
    printf("trace1 \n");
    //pkcs5
    while(1) {
      SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB1");
      secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb1_deckey"),
                          createString("./tmp/test_Aes_encrypt_Cfb1_enckey"),
                          key);

      printf("trace1_1 \n");
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB1");
      enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb1_enckey");
      Cipher Aes = st(CipherCreator)::getInstance("AES/CFB1/PKCS5Padding");
      Aes->init(st(Cipher)::Encrypt,enckey);
      Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb1_outdata_pksc5");
      printf("trace1_2\n");
      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB1");
      deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb_deckey");
      Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB1/PKCS5Padding");
      Aes2->init(st(Cipher)::Decrypt,deckey);
      Aes2->decrypt("./tmp/Aes_encrypt_Cfb1_outdata_pksc5","./tmp/Aes_encrypt_Cfb1_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb1_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAes Cfb1 PKCS5Padding case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb8_deckey"),
                          createString("./tmp/test_Aes_encrypt_Cfb8_enckey"),
                          key);

      printf("trace1_1 \n");
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb8_enckey");
      Cipher Aes = st(CipherCreator)::getInstance("AES/CFB8/PKCS5Padding");
      Aes->init(st(Cipher)::Encrypt,enckey);
      Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb8_outdata_pksc5");
      printf("trace1_2\n");
      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb8_deckey");
      Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB8/PKCS5Padding");
      Aes2->init(st(Cipher)::Decrypt,deckey);
      Aes2->decrypt("./tmp/Aes_encrypt_Cfb8_outdata_pksc5","./tmp/Aes_encrypt_Cfb8_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb8_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAes Cfb1 case2] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb128_deckey"),
                          createString("./tmp/test_Aes_encrypt_Cfb128_enckey"),
                          key);

      printf("trace1_1 \n");
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB128");
      enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb128_enckey");
      Cipher Aes = st(CipherCreator)::getInstance("AES/CFB128/PKCS5Padding");
      Aes->init(st(Cipher)::Encrypt,enckey);
      Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb128_outdata_pksc5");
      printf("trace1_2\n");
      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB128");
      deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb128_deckey");
      Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB128/PKCS5Padding");
      Aes2->init(st(Cipher)::Decrypt,deckey);
      Aes2->decrypt("./tmp/Aes_encrypt_Cfb128_outdata_pksc5","./tmp/Aes_encrypt_Cfb128_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb128_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAes Cfb1 case3] [FAILED]--- \n");
      }
      break;
    }

    //------ random key
    while(1) {
      SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB1");
      secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb1_random_deckey"),
                          createString("./tmp/test_Aes_encrypt_Cfb1_random_enckey"));

      printf("trace1_1 \n");
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB1");
      enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb1_random_enckey");
      Cipher Aes = st(CipherCreator)::getInstance("AES/CFB1/PKCS5Padding");
      Aes->init(st(Cipher)::Encrypt,enckey);
      Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb1_random_outdata_pksc5");
      printf("trace1_2\n");
      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB1");
      deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb1_random_deckey");
      Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB1/PKCS5Padding");
      Aes2->init(st(Cipher)::Decrypt,deckey);
      Aes2->decrypt("./tmp/Aes_encrypt_Cfb1_random_outdata_pksc5","./tmp/Aes_encrypt_Cfb1_random_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb1_random_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAes Cfb4 PKCS5Padding case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb8_random_deckey"),
                          createString("./tmp/test_Aes_encrypt_Cfb8_random_enckey"));

      printf("trace1_1 \n");
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb8_random_enckey");
      Cipher Aes = st(CipherCreator)::getInstance("AES/CFB8/PKCS5Padding");
      Aes->init(st(Cipher)::Encrypt,enckey);
      Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb8_random_outdata_pksc5");
      printf("trace1_2\n");
      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb8_random_deckey");
      Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB8/PKCS5Padding");
      Aes2->init(st(Cipher)::Decrypt,deckey);
      Aes2->decrypt("./tmp/Aes_encrypt_Cfb8_random_outdata_pksc5","./tmp/Aes_encrypt_Cfb8_random_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb8_random_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAes Cfb5 case2] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      SecretKey secretKey = st(SecretKeyCreator)::getInstance("AES/CFB8");
      secretKey->generate(createString("./tmp/test_Aes_encrypt_Cfb128_random_deckey"),
                          createString("./tmp/test_Aes_encrypt_Cfb128_random_enckey"));

      printf("trace1_1 \n");
      SecretKey enckey = st(SecretKeyCreator)::getInstance("AES/CFB128");
      enckey->loadEncryptKey("./tmp/test_Aes_encrypt_Cfb128_random_enckey");
      Cipher Aes = st(CipherCreator)::getInstance("AES/CFB128/PKCS5Padding");
      Aes->init(st(Cipher)::Encrypt,enckey);
      Aes->encrypt(data,"./tmp/Aes_encrypt_Cfb128_random_outdata_pksc5");
      printf("trace1_2\n");
      SecretKey deckey = st(SecretKeyCreator)::getInstance("AES/CFB128");
      deckey->loadDecryptKey("./tmp/test_Aes_encrypt_Cfb128_random_deckey");
      Cipher Aes2 = st(CipherCreator)::getInstance("AES/CFB128/PKCS5Padding");
      Aes2->init(st(Cipher)::Decrypt,deckey);
      Aes2->decrypt("./tmp/Aes_encrypt_Cfb128_random_outdata_pksc5","./tmp/Aes_encrypt_Cfb128_random_outdata_pksc5_dec");
      String result = md5sum->encrypt(createFile("./tmp/Aes_encrypt_Cfb128_random_outdata_pksc5_dec"));

      if(!result->equals(testDataMd5)) {
        printf("---[TestAes Cfb6 case3] [FAILED]--- \n");
      }
      break;
    }

    printf("---[TestAes Cfb case100] [OK]--- \n");
}
