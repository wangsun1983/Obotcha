securityDir = security

objs += $(outtmp)/crc32.o \
		$(outtmp)/md.o \
		$(outtmp)/des.o \
		$(outtmp)/base64.o \
		$(outtmp)/aes.o \
		$(outtmp)/rsa.o \
		$(outtmp)/sha.o \
		$(outtmp)/ciphercreator.o \
		$(outtmp)/secretkey.o \
		$(outtmp)/secretkeycreator.o \
		$(outtmp)/cipher.o \
		$(outtmp)/asesecretkey.o \
		$(outtmp)/dessecretkey.o \
		$(outtmp)/rsasecretkey.o \
		
$(outtmp)/asesecretkey.o :$(securityDir)/AesSecretKey.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/AesSecretKey.cpp -o $(outtmp)/asesecretkey.o 		

$(outtmp)/dessecretkey.o :$(securityDir)/DesSecretKey.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/DesSecretKey.cpp -o $(outtmp)/dessecretkey.o 

$(outtmp)/rsasecretkey.o :$(securityDir)/RsaSecretKey.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/RsaSecretKey.cpp -o $(outtmp)/rsasecretkey.o 	

$(outtmp)/crc32.o :$(securityDir)/Crc32.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Crc32.cpp -o $(outtmp)/crc32.o 

$(outtmp)/ciphercreator.o :$(securityDir)/CipherCreator.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/CipherCreator.cpp -o $(outtmp)/ciphercreator.o 

$(outtmp)/cipher.o :$(securityDir)/Cipher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Cipher.cpp -o $(outtmp)/cipher.o 

$(outtmp)/md.o :$(securityDir)/Md.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Md.cpp -o $(outtmp)/md.o 

$(outtmp)/des.o :$(securityDir)/Des.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Des.cpp -o $(outtmp)/des.o 

$(outtmp)/base64.o :$(securityDir)/Base64.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Base64.cpp -o $(outtmp)/base64.o 

$(outtmp)/aes.o :$(securityDir)/Aes.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Aes.cpp -o $(outtmp)/aes.o 

$(outtmp)/rsa.o :$(securityDir)/Rsa.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Rsa.cpp -o $(outtmp)/rsa.o 

$(outtmp)/sha.o :$(securityDir)/Sha.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Sha.cpp -o $(outtmp)/sha.o 

$(outtmp)/secretkey.o :$(securityDir)/SecretKey.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/SecretKey.cpp -o $(outtmp)/secretkey.o 

$(outtmp)/secretkeycreator.o :$(securityDir)/SecretKeyCreator.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/SecretKeyCreator.cpp -o $(outtmp)/secretkeycreator.o 
