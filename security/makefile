securityDir = security

link += crc32 \
		md5 \
		des \
		base64 \
		aes \
		
objs += $(outtmp)/crc32.o \a
		$(outtmp)/md5.o \
		$(outtmp)/des.o \
		$(outtmp)/base64.o \
		$(outtmp)/aes.o \

crc32 :$(securityDir)/Crc32.cpp
	$(gcc) $(cflags) -c $(securityDir)/Crc32.cpp -o $(outtmp)/crc32.o $(external)

md5 :$(securityDir)/Md5.cpp
	$(gcc) $(cflags) -c $(securityDir)/Md5.cpp -o $(outtmp)/md5.o $(external)

des :$(securityDir)/Des.cpp
	$(gcc) $(cflags) -c $(securityDir)/Des.cpp -o $(outtmp)/des.o $(external)		

base64 :$(securityDir)/Base64.cpp
	$(gcc) $(cflags) -c $(securityDir)/Base64.cpp -o $(outtmp)/base64.o $(external)		

aes :$(securityDir)/Aes.cpp
	$(gcc) $(cflags) -c $(securityDir)/Aes.cpp -o $(outtmp)/aes.o $(external)		
