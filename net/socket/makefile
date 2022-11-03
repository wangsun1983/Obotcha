socketDir = $(netDir)/socket

objs += $(outtmp)/socket.o \
		$(outtmp)/serversocket.o \
		$(outtmp)/socketbuilder.o \
		$(outtmp)/socketimpl.o \
		$(outtmp)/socketoption.o \
		$(outtmp)/sockssocketimpl.o \
		$(outtmp)/sslsockssocketimpl.o \
		$(outtmp)/serversocketimpl.o \
		$(outtmp)/sslserversocketimpl.o \
		$(outtmp)/datagramsocketimpl.o \
		$(outtmp)/socketmonitor.o \
		$(outtmp)/sslsocketcontext.o \
		

$(outtmp)/socketimpl.o :$(netDir)/socket/SocketImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SocketImpl.cpp -o $(outtmp)/socketimpl.o 

$(outtmp)/sslsocketcontext.o :$(netDir)/socket/SSLSocketContext.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SSLSocketContext.cpp -o $(outtmp)/sslsocketcontext.o 

$(outtmp)/socketoption.o :$(netDir)/socket/SocketOption.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SocketOption.cpp -o $(outtmp)/socketoption.o 

$(outtmp)/sockssocketimpl.o :$(netDir)/socket/SocksSocketImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SocksSocketImpl.cpp -o $(outtmp)/sockssocketimpl.o 

$(outtmp)/sslsockssocketimpl.o :$(netDir)/socket/SSLSocksSocketImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SSLSocksSocketImpl.cpp -o $(outtmp)/sslsockssocketimpl.o 

$(outtmp)/serversocketimpl.o :$(netDir)/socket/ServerSocketImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/ServerSocketImpl.cpp -o $(outtmp)/serversocketimpl.o 

$(outtmp)/sslserversocketimpl.o :$(netDir)/socket/SSLServerSocketImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SSLServerSocketImpl.cpp -o $(outtmp)/sslserversocketimpl.o 

#$(outtmp)/localsocketimpl.o :$(netDir)/socket/LocalSocketImpl.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/LocalSocketImpl.cpp -o $(outtmp)/localsocketimpl.o 

#$(outtmp)/serverlocalsocketimpl.o :$(netDir)/socket/ServerLocalSocketImpl.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/ServerLocalSocketImpl.cpp -o $(outtmp)/serverlocalsocketimpl.o 

$(outtmp)/datagramsocketimpl.o :$(netDir)/socket/DatagramSocketImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/DatagramSocketImpl.cpp -o $(outtmp)/datagramsocketimpl.o 

$(outtmp)/socket.o :$(netDir)/socket/Socket.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/Socket.cpp -o $(outtmp)/socket.o 

$(outtmp)/serversocket.o :$(netDir)/socket/ServerSocket.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/ServerSocket.cpp -o $(outtmp)/serversocket.o 

$(outtmp)/socketbuilder.o :$(netDir)/socket/SocketBuilder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SocketBuilder.cpp -o $(outtmp)/socketbuilder.o 

$(outtmp)/socketmonitor.o :$(netDir)/socket/SocketMonitor.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/socket/SocketMonitor.cpp -o $(outtmp)/socketmonitor.o 


