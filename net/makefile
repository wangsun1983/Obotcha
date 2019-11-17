netDir = net

link += inetaddress \
		ntpclient \
		tcpclient \
		asynctcpclient \
		tcpserver \
		udpclient \
		udpserver \
		localsocketclient \
		asynclocalsocketclient \
		localsocketserver \
		netutils \
		httpparser \
		httpheaderparser \
		httpurlparser \
		httpurl \
		httpurlbuilder \
		httpclient \
		httpheader \
		httppacket \
		httpresponsewriter \
		httpcookie \
		httpdate \
		websocketserver \
		websocketprotocol \
		websocketframecomposer \
		websocketcomposer \
		websocketframe \
		websocketparser \
		websocketclientinfo \
		websockethybi13parser \
		websockethybi07parser \
		websockethybi08parser \
		websockethybi00parser \
		websocketpermessagedeflate \
		websocketclient \

objs += $(outtmp)/inetaddress.o \
		$(outtmp)/ntpclient.o \
		$(outtmp)/tcpclient.o \
		$(outtmp)/asynctcpclient.o \
		$(outtmp)/tcpserver.o \
		$(outtmp)/udpclient.o \
		$(outtmp)/udpserver.o \
		$(outtmp)/localsocketclient.o \
		$(outtmp)/asynclocalsocketclient.o \
		$(outtmp)/localsocketserver.o \
		$(outtmp)/netutils.o \
		$(outtmp)/httpparser.o \
		$(outtmp)/httpheaderparser.o \
		$(outtmp)/httpurlparser.o \
		$(outtmp)/httpurl.o \
		$(outtmp)/httpurlbuilder.o \
		$(outtmp)/httpclient.o \
		$(outtmp)/httpheader.o \
		$(outtmp)/httppacket.o \
		$(outtmp)/httpresponsewriter.o \
		$(outtmp)/httpcookie.o \
		$(outtmp)/httpdate.o \
		$(outtmp)/websocketserver.o \
		$(outtmp)/websocketprotocol.o \
		$(outtmp)/websocketframecomposer.o \
		$(outtmp)/websocketcomposer.o \
		$(outtmp)/websocketframe.o \
		$(outtmp)/websocketparser.o \
		$(outtmp)/websockethybi13parser.o \
		$(outtmp)/websockethybi07parser.o \
		$(outtmp)/websockethybi08parser.o \
		$(outtmp)/websockethybi00parser.o \
		$(outtmp)/websocketpermessagedeflate.o \
		$(outtmp)/websocketclientinfo.o \
		$(outtmp)/websocketclient.o \

inetaddress :$(netDir)/InetAddress.cpp
	$(gcc) $(cflags) -c $(netDir)/InetAddress.cpp -o $(outtmp)/inetaddress.o $(external)

tcpserver :$(netDir)/tcp/TcpServer.cpp
	$(gcc) $(cflags) -c $(netDir)/tcp/TcpServer.cpp -o $(outtmp)/tcpserver.o $(external)

asynctcpclient :$(netDir)/tcp/AsyncTcpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/tcp/AsyncTcpClient.cpp -o $(outtmp)/asynctcpclient.o $(external)

tcpclient :$(netDir)/tcp/TcpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/tcp/TcpClient.cpp -o $(outtmp)/tcpclient.o $(external)

udpclient :$(netDir)/udp/UdpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/udp/UdpClient.cpp -o $(outtmp)/udpclient.o $(external)

udpserver :$(netDir)/udp/UdpServer.cpp
	$(gcc) $(cflags) -c $(netDir)/udp/UdpServer.cpp -o $(outtmp)/udpserver.o $(external)

localsocketclient :$(netDir)/tcp/LocalSocketClient.cpp
	$(gcc) $(cflags) -c $(netDir)/tcp/LocalSocketClient.cpp -o $(outtmp)/localsocketclient.o $(external)

asynclocalsocketclient :$(netDir)/tcp/AsyncLocalSocketClient.cpp
	$(gcc) $(cflags) -c $(netDir)/tcp/AsyncLocalSocketClient.cpp -o $(outtmp)/asynclocalsocketclient.o $(external)

localsocketserver :$(netDir)/tcp/LocalSocketServer.cpp
	$(gcc) $(cflags) -c $(netDir)/tcp/LocalSocketServer.cpp -o $(outtmp)/localsocketserver.o $(external)			

netutils :$(netDir)/NetUtils.cpp
	$(gcc) $(cflags) -c $(netDir)/NetUtils.cpp -o $(outtmp)/netutils.o $(external)				

httpparser :$(netDir)/http/HttpParser.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpParser.cpp -o $(outtmp)/httpparser.o $(external)	

httpclient :$(netDir)/http/HttpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpClient.cpp -o $(outtmp)/httpclient.o $(external)	

httpheaderparser :$(netDir)/http/HttpHeaderParser.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpHeaderParser.cpp -o $(outtmp)/httpheaderparser.o $(external)

httpurlparser :$(netDir)/http/HttpUrlParser.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpUrlParser.cpp -o $(outtmp)/httpurlparser.o $(external)

httpurl :$(netDir)/http/HttpUrl.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpUrl.cpp -o $(outtmp)/httpurl.o $(external)

httpurlbuilder :$(netDir)/http/HttpUrlBuilder.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpUrlBuilder.cpp -o $(outtmp)/httpurlbuilder.o $(external)

httpcookie :$(netDir)/http/HttpCookie.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpCookie.cpp -o $(outtmp)/httpcookie.o $(external)

httpdate :$(netDir)/http/HttpDate.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpDate.cpp -o $(outtmp)/httpdate.o $(external)

httpheader :$(netDir)/http/HttpHeader.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpHeader.cpp -o $(outtmp)/httpheader.o $(external)

httppacket :$(netDir)/http/HttpPacket.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpPacket.cpp -o $(outtmp)/httppacket.o $(external)	

httpresponsewriter :$(netDir)/http/HttpResponseWriter.cpp
	$(gcc) $(cflags) -c $(netDir)/http/HttpResponseWriter.cpp -o $(outtmp)/httpresponsewriter.o $(external)

websocketserver :$(netDir)/websocket/WebSocketServer.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketServer.cpp -o $(outtmp)/websocketserver.o $(external)

websocketprotocol :$(netDir)/websocket/WebSocketProtocol.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketProtocol.cpp -o $(outtmp)/websocketprotocol.o $(external)

websocketframecomposer :$(netDir)/websocket/WebSocketFrameComposer.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketFrameComposer.cpp -o $(outtmp)/websocketframecomposer.o $(external)

websocketframe :$(netDir)/websocket/WebSocketFrame.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketFrame.cpp -o $(outtmp)/websocketframe.o $(external)	

websocketparser :$(netDir)/websocket/WebSocketParser.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketParser.cpp -o $(outtmp)/websocketparser.o $(external)

websockethybi13parser :$(netDir)/websocket/WebSocketHybi13Parser.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketHybi13Parser.cpp -o $(outtmp)/websockethybi13parser.o $(external)		

websockethybi07parser :$(netDir)/websocket/WebSocketHybi07Parser.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketHybi07Parser.cpp -o $(outtmp)/websockethybi07parser.o $(external)		

websockethybi08parser :$(netDir)/websocket/WebSocketHybi08Parser.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketHybi08Parser.cpp -o $(outtmp)/websockethybi08parser.o $(external)		

websockethybi00parser :$(netDir)/websocket/WebSocketHybi00Parser.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketHybi00Parser.cpp -o $(outtmp)/websockethybi00parser.o $(external)		

websocketpermessagedeflate :$(netDir)/websocket/WebSocketPermessageDeflate.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketPermessageDeflate.cpp -o $(outtmp)/websocketpermessagedeflate.o $(external)		

websocketclient :$(netDir)/websocket/WebSocketClient.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketClient.cpp -o $(outtmp)/websocketclient.o $(external)		

websocketclientinfo :$(netDir)/websocket/WebSocketClientInfo.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketClientInfo.cpp -o $(outtmp)/websocketclientinfo.o $(external)

websocketcomposer :$(netDir)/websocket/WebSocketComposer.cpp
	$(gcc) $(cflags) -c $(netDir)/websocket/WebSocketComposer.cpp -o $(outtmp)/websocketcomposer.o $(external)		

ntpclient :$(netDir)/NtpClient.cpp
	$(gcc) $(cflags) -c $(netDir)/NtpClient.cpp -o $(outtmp)/ntpclient.o $(external)			