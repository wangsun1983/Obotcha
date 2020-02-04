securityDir = security

link += crc32 \
		md \
		des \
		base64 \
		aes \
		rsa \
		sha \
		
objs += $(outtmp)/crc32.o \
		$(outtmp)/md.o \
		$(outtmp)/des.o \
		$(outtmp)/base64.o \
		$(outtmp)/aes.o \
		$(outtmp)/rsa.o \
		$(outtmp)/sha.o \

crc32 :$(securityDir)/Crc32.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Crc32.cpp -o $(outtmp)/crc32.o $(external)

md :$(securityDir)/Md.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Md.cpp -o $(outtmp)/md.o $(external)

des :$(securityDir)/Des.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Des.cpp -o $(outtmp)/des.o $(external)		

base64 :$(securityDir)/Base64.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Base64.cpp -o $(outtmp)/base64.o $(external)		

aes :$(securityDir)/Aes.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Aes.cpp -o $(outtmp)/aes.o $(external)		

rsa :$(securityDir)/Rsa.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Rsa.cpp -o $(outtmp)/rsa.o $(external)		

sha :$(securityDir)/Sha.cpp
	$(cppcompiler) $(obotchacppflags) -c $(securityDir)/Sha.cpp -o $(outtmp)/sha.o $(external)	