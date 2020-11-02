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
		$(outtmp)/secretkeygenrator.o \
		$(outtmp)/cipher.o \
		

$(outtmp)/crc32.o :$(securityDir)/Crc32.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Crc32.cpp -o $(outtmp)/crc32.o $(external)

$(outtmp)/ciphercreator.o :$(securityDir)/CipherCreator.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/CipherCreator.cpp -o $(outtmp)/ciphercreator.o $(external)

$(outtmp)/cipher.o :$(securityDir)/Cipher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Cipher.cpp -o $(outtmp)/cipher.o $(external)

$(outtmp)/md.o :$(securityDir)/Md.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Md.cpp -o $(outtmp)/md.o $(external)

$(outtmp)/des.o :$(securityDir)/Des.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Des.cpp -o $(outtmp)/des.o $(external)

$(outtmp)/base64.o :$(securityDir)/Base64.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Base64.cpp -o $(outtmp)/base64.o $(external)

$(outtmp)/aes.o :$(securityDir)/Aes.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Aes.cpp -o $(outtmp)/aes.o $(external)

$(outtmp)/rsa.o :$(securityDir)/Rsa.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Rsa.cpp -o $(outtmp)/rsa.o $(external)

$(outtmp)/sha.o :$(securityDir)/Sha.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Sha.cpp -o $(outtmp)/sha.o $(external)

$(outtmp)/secretkey.o :$(securityDir)/SecretKey.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/SecretKey.cpp -o $(outtmp)/secretkey.o $(external)

$(outtmp)/secretkeygenrator.o :$(securityDir)/SecretKeyGenerator.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/SecretKeyGenerator.cpp -o $(outtmp)/secretkeygenrator.o $(external)
