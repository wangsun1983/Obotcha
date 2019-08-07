netDir = net

link += inetaddress \
		ntpclient \
		tcpclient \
		tcpserver \
		udpclient \
		udpserver \
		localsocketclient \
		localsocketserver \
		netutils \
		httpparser \
		httpheaderparser \
		httpurlparser \
		httpurl \
		httpheader \
		httpresponse \
		httppacket \
		httpresponsewriter \
		httpcookie \
		websocketserver \
		websocketprotocol \
		websocketframecomposer \
		websocketframe \
		websocketparser \
		websockethybi13parser \
		websocketclient \
		


objs += $(outtmp)/inetaddress.o \
		$(outtmp)/ntpclient.o \
		$(outtmp)/tcpclient.o \
		$(outtmp)/tcpserver.o \
		$(outtmp)/udpclient.o \
		$(outtmp)/udpserver.o \
		$(outtmp)/localsocketclient.o \
		$(outtmp)/localsocketserver.o \
		$(outtmp)/netutils.o \
		$(outtmp)/httpparser.o \
		$(outtmp)/httpheaderparser.o \
		$(outtmp)/httpurlparser.o \
		$(outtmp)/httpurl.o \
		$(outtmp)/httpheader.o \
		$(outtmp)/httpresponse.o \
		$(outtmp)/httppacket.o \
		$(outtmp)/httpresponsewriter.o \
		$(outtmp)/httpcookie.o \
		$(outtmp)/websocketserver.o \
		$(outtmp)/websocketprotocol.o \
		$(outtmp)/websocketframecomposer.o \
		$(outtmp)/websocketframe.o \
		$(outtmp)/websocketparser.o \
		$(outtmp)/websockethybi13parser.o \
		$(outtmp)/websocketclient.o \

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

localsocketclient :$(netDir)/LocalSocketClient.cpp
	$(gcc) $(cflags) -c $(netDir)/LocalSocketClient.cpp -o $(outtmp)/localsocketclient.o $(external)

localsocketserver :$(netDir)/LocalSocketServer.cpp
	$(gcc) $(cflags) -c $(netDir)/LocalSocketServer.cpp -o $(outtmp)/localsocketserver.o $(external)			

netutils :$(netDir)/NetUtils.cpp
	$(gcc) $(cflags) -c $(netDir)/NetUtils.cpp -o $(outtmp)/netutils.o $(external)				

httpparser :$(netDir)/HttpParser.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpParser.cpp -o $(outtmp)/httpparser.o $(external)	

httpheaderparser :$(netDir)/HttpHeaderParser.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpHeaderParser.cpp -o $(outtmp)/httpheaderparser.o $(external)

httpurlparser :$(netDir)/HttpUrlParser.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpUrlParser.cpp -o $(outtmp)/httpurlparser.o $(external)

httpurl :$(netDir)/HttpUrl.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpUrl.cpp -o $(outtmp)/httpurl.o $(external)

httpcookie :$(netDir)/HttpCookie.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpCookie.cpp -o $(outtmp)/httpcookie.o $(external)

httpheader :$(netDir)/HttpHeader.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpHeader.cpp -o $(outtmp)/httpheader.o $(external)

httpresponse :$(netDir)/HttpResponse.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpResponse.cpp -o $(outtmp)/httpresponse.o $(external)

httppacket :$(netDir)/HttpPacket.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpPacket.cpp -o $(outtmp)/httppacket.o $(external)	

httpresponsewriter :$(netDir)/HttpResponseWriter.cpp
	$(gcc) $(cflags) -c $(netDir)/HttpResponseWriter.cpp -o $(outtmp)/httpresponsewriter.o $(external)

websocketserver :$(netDir)/WebSocketServer.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketServer.cpp -o $(outtmp)/websocketserver.o $(external)

websocketprotocol :$(netDir)/WebSocketProtocol.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketProtocol.cpp -o $(outtmp)/websocketprotocol.o $(external)

websocketframecomposer :$(netDir)/WebSocketFrameComposer.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketFrameComposer.cpp -o $(outtmp)/websocketframecomposer.o $(external)

websocketframe :$(netDir)/WebSocketFrame.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketFrame.cpp -o $(outtmp)/websocketframe.o $(external)	

websocketparser :$(netDir)/WebSocketParser.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketParser.cpp -o $(outtmp)/websocketparser.o $(external)

websockethybi13parser :$(netDir)/WebSocketHybi13Parser.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketHybi13Parser.cpp -o $(outtmp)/websockethybi13parser.o $(external)		

websocketclient :$(netDir)/WebSocketClient.cpp
	$(gcc) $(cflags) -c $(netDir)/WebSocketClient.cpp -o $(outtmp)/websocketclient.o $(external)		

ntpclient :$(netDir)/NtpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/NtpClient.cpp -o $(outtmp)/ntpclient.o $(external)			