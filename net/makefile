netDir = net

include $(netDir)/http/makefile
include $(netDir)/socket/makefile
include $(netDir)/websocket/makefile
include $(netDir)/smtp/makefile


objs += $(outtmp)/inetaddress.o \
		$(outtmp)/netevent.o \
		$(outtmp)/inet4address.o \
		$(outtmp)/inet6address.o \
		$(outtmp)/inetlocaladdress.o \
		$(outtmp)/ntpclient.o \
		$(outtmp)/url.o \
		$(outtmp)/host.o \

$(outtmp)/inetaddress.o :$(netDir)/InetAddress.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/InetAddress.cpp -o $(outtmp)/inetaddress.o 

$(outtmp)/netevent.o :$(netDir)/NetEvent.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/NetEvent.cpp -o $(outtmp)/netevent.o 

$(outtmp)/inet4address.o :$(netDir)/Inet4Address.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/Inet4Address.cpp -o $(outtmp)/inet4address.o 

$(outtmp)/inet6address.o :$(netDir)/Inet6Address.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/Inet6Address.cpp -o $(outtmp)/inet6address.o 

$(outtmp)/inetlocaladdress.o :$(netDir)/InetLocalAddress.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/InetLocalAddress.cpp -o $(outtmp)/inetlocaladdress.o 

$(outtmp)/ntpclient.o :$(netDir)/NtpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/NtpClient.cpp -o $(outtmp)/ntpclient.o 

$(outtmp)/url.o :$(netDir)/URL.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/URL.cpp -o $(outtmp)/url.o 

$(outtmp)/host.o :$(netDir)/Host.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/Host.cpp -o $(outtmp)/host.o 

