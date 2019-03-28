securityDir = security

link += crc32 \
		md5 \
		des \
		
objs += $(outtmp)/crc32.o \
		$(outtmp)/md5.o \
		$(outtmp)/des.o

crc32 :$(securityDir)/Crc32.cpp
	$(gcc) $(cflags) -c $(securityDir)/Crc32.cpp -o $(outtmp)/crc32.o $(external)

md5 :$(securityDir)/Md5.cpp
	$(gcc) $(cflags) -c $(securityDir)/Md5.cpp -o $(outtmp)/md5.o $(external)

des :$(securityDir)/Des.cpp
	$(gcc) $(cflags) -c $(securityDir)/Des.cpp -o $(outtmp)/des.o $(external)		
