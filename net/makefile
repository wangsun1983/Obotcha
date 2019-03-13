netDir = net

link += inetaddress \
		serversocket \
		socketpacket \
		socket \

objs += $(outtmp)/inetaddress.o \
		$(outtmp)/serversocket.o \
		$(outtmp)/socketpacket.o \
		$(outtmp)/socket.o \

inetaddress :$(netDir)/InetAddress.cpp
	$(gcc) $(cflags) -c $(netDir)/InetAddress.cpp -o $(outtmp)/inetaddress.o $(external)

serversocket :$(netDir)/ServerSocket.cpp
	$(gcc) $(cflags) -c $(netDir)/ServerSocket.cpp -o $(outtmp)/serversocket.o $(external)

socketpacket :$(netDir)/SocketPacket.cpp
	$(gcc) $(cflags) -c $(netDir)/SocketPacket.cpp -o $(outtmp)/socketpacket.o $(external)

socket :$(netDir)/Socket.cpp
	$(gcc) $(cflags) -c $(netDir)/Socket.cpp -o $(outtmp)/socket.o $(external)

