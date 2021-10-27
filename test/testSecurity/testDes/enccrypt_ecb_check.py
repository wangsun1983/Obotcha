from pyDes import des, PAD_PKCS5, ECB

DES_SECRET_KEY = b'8a626479a1160291'
#s = 'abc'.encode()
f = open("./tmp/des_encrypt_ecb_outdata",'rb')
data = f.read(1024)

key = open("./tmp/test_des_encrypt_ecb_deckey",'rb').read(8)

des_obj = des(key, ECB, key, padmode=PAD_PKCS5)
secret_bytes = des_obj.encrypt("a")
s = des_obj.decrypt(data)

print(secret_bytes)
print(data)
print(s)