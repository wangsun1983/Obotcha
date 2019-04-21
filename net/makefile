netDir = net

link += inetaddress \
		tcpclient \
		tcpserver \
		udpclient \
		udpserver \
		socketpacket \

objs += $(outtmp)/inetaddress.o \
		$(outtmp)/tcpclient.o \
		$(outtmp)/tcpserver.o \
		$(outtmp)/udpclient.o \
		$(outtmp)/udpserver.o \
		$(outtmp)/socketpacket.o \

inetaddress :$(netDir)/InetAddress.cpp
	$(gcc) $(cflags) -c $(netDir)/InetAddress.cpp -o $(outtmp)/inetaddress.o $(external)

tcpserver :$(netDir)/TcpServer.cpp
	$(gcc) $(cflags) -c $(netDir)/TcpServer.cpp -o $(outtmp)/tcpserver.o $(external)

tcpclient :$(netDir)/TcpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/TcpClient.cpp -o $(outtmp)/tcpclient.o $(external)

udpclient :$(netDir)/UdpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/UdpClient.cpp -o $(outtmp)/udpclient.o $(external)

udpserver :$(netDir)/UdpServer.cpp
	$(gcc) $(cflags) -c $(netDir)/UdpServer.cpp -o $(outtmp)/udpserver.o $(external)

socketpacket :$(netDir)/SocketPacket.cpp
	$(gcc) $(cflags) -c $(netDir)/SocketPacket.cpp -o $(outtmp)/socketpacket.o $(external)		

