netDir = net

objs += $(outtmp)/inetaddress.o \
		$(outtmp)/ntpclient.o \
		$(outtmp)/tcpclient.o \
		$(outtmp)/tcpserver.o \
		$(outtmp)/udpclient.o \
		$(outtmp)/udpserver.o \
		$(outtmp)/socket.o \
		$(outtmp)/localsocketclient.o \
		$(outtmp)/localsocketserver.o \
		$(outtmp)/httpurlparser.o \
		$(outtmp)/httpurl.o \
		$(outtmp)/httpfile.o \
		$(outtmp)/httpstatus.o \
		$(outtmp)/httpversion.o \
		$(outtmp)/httpcontenttype.o \
		$(outtmp)/httpurlbuilder.o \
		$(outtmp)/httpresponse.o \
		$(outtmp)/httpclient.o \
		$(outtmp)/httpmethod.o \
		$(outtmp)/httpheader.o \
		$(outtmp)/httpheaderparser.o \
		$(outtmp)/httppacket.o \
		$(outtmp)/httptext.o \
		$(outtmp)/httprequest.o \
		$(outtmp)/httprequestwriter.o \
		$(outtmp)/httpcachecontrol.o \
		$(outtmp)/httpresponsewriter.o \
		$(outtmp)/httpresponseparser.o \
		$(outtmp)/httpclientmanager.o \
		$(outtmp)/httpcookie.o \
		$(outtmp)/httpdate.o \
		$(outtmp)/httpmultipart.o \
		$(outtmp)/httpmultipartparser.o \
		$(outtmp)/httpserver.o \
		$(outtmp)/httpclientinfo.o \
		$(outtmp)/httprequestparser.o \
		$(outtmp)/websocketserver.o \
		$(outtmp)/websocketprotocol.o \
		$(outtmp)/websocketframe.o \
		$(outtmp)/websocketparser.o \
		$(outtmp)/websockethybi13parser.o \
		$(outtmp)/websockethybi07parser.o \
		$(outtmp)/websockethybi08parser.o \
		$(outtmp)/websockethybi00parser.o \
		$(outtmp)/websockethybi13composer.o \
		$(outtmp)/websockethybi07composer.o \
		$(outtmp)/websockethybi08composer.o \
		$(outtmp)/websockethybi00composer.o \
		$(outtmp)/websocketpermessagedeflate.o \
		$(outtmp)/websocketclientinfo.o \
		$(outtmp)/websocketclient.o \
		$(outtmp)/httpv2hpackutil.o \
		$(outtmp)/httpv2huffmandecoder.o \
		$(outtmp)/httpv2huffmanencoder.o \
		$(outtmp)/httpv2headerencoder.o \
		$(outtmp)/httpv2headerdecoder.o \
		$(outtmp)/httpv2headerfield.o \
		$(outtmp)/sslserver.o \
		$(outtmp)/sslinfo.o \
		$(outtmp)/sslmanager.o \
		$(outtmp)/socketresponser.o \

$(outtmp)/socket.o :$(netDir)/Socket.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/Socket.cpp -o $(outtmp)/socket.o $(external)

$(outtmp)/inetaddress.o :$(netDir)/InetAddress.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/InetAddress.cpp -o $(outtmp)/inetaddress.o $(external)

$(outtmp)/socketresponser.o :$(netDir)/SocketResponser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/SocketResponser.cpp -o $(outtmp)/socketresponser.o $(external)

$(outtmp)/tcpserver.o :$(netDir)/tcp/TcpServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/tcp/TcpServer.cpp -o $(outtmp)/tcpserver.o $(external)

$(outtmp)/tcpclient.o :$(netDir)/tcp/TcpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/tcp/TcpClient.cpp -o $(outtmp)/tcpclient.o $(external)

$(outtmp)/udpclient.o :$(netDir)/udp/UdpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/udp/UdpClient.cpp -o $(outtmp)/udpclient.o $(external)

$(outtmp)/udpserver.o :$(netDir)/udp/UdpServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/udp/UdpServer.cpp -o $(outtmp)/udpserver.o $(external)

$(outtmp)/localsocketclient.o :$(netDir)/tcp/LocalSocketClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/tcp/LocalSocketClient.cpp -o $(outtmp)/localsocketclient.o $(external)

$(outtmp)/localsocketserver.o :$(netDir)/tcp/LocalSocketServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/tcp/LocalSocketServer.cpp -o $(outtmp)/localsocketserver.o $(external)

$(outtmp)/httprequestparser.o :$(netDir)/http/HttpRequestParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpRequestParser.cpp -o $(outtmp)/httprequestparser.o $(external)

$(outtmp)/httpclient.o :$(netDir)/http/HttpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpClient.cpp -o $(outtmp)/httpclient.o $(external)

$(outtmp)/httpmethod.o :$(netDir)/http/HttpMethod.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpMethod.cpp -o $(outtmp)/httpmethod.o $(external)

$(outtmp)/httpurlparser.o :$(netDir)/http/HttpUrlParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpUrlParser.cpp -o $(outtmp)/httpurlparser.o $(external)

$(outtmp)/httpurl.o :$(netDir)/http/HttpUrl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpUrl.cpp -o $(outtmp)/httpurl.o $(external)

$(outtmp)/httpfile.o :$(netDir)/http/HttpFile.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpFile.cpp -o $(outtmp)/httpfile.o $(external)

$(outtmp)/httpstatus.o :$(netDir)/http/HttpStatus.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpStatus.cpp -o $(outtmp)/httpstatus.o $(external)

$(outtmp)/httpversion.o :$(netDir)/http/HttpVersion.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpVersion.cpp -o $(outtmp)/httpversion.o $(external)

$(outtmp)/httpcontenttype.o :$(netDir)/http/HttpContentType.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpContentType.cpp -o $(outtmp)/httpcontenttype.o $(external)

$(outtmp)/httpurlbuilder.o :$(netDir)/http/HttpUrlBuilder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpUrlBuilder.cpp -o $(outtmp)/httpurlbuilder.o $(external)

$(outtmp)/httpcookie.o :$(netDir)/http/HttpCookie.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpCookie.cpp -o $(outtmp)/httpcookie.o $(external)

$(outtmp)/httpdate.o :$(netDir)/http/HttpDate.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpDate.cpp -o $(outtmp)/httpdate.o $(external)

$(outtmp)/httpmultipart.o :$(netDir)/http/HttpMultiPart.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpMultiPart.cpp -o $(outtmp)/httpmultipart.o $(external)

$(outtmp)/httpmultipartparser.o :$(netDir)/http/HttpMultiPartParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpMultiPartParser.cpp -o $(outtmp)/httpmultipartparser.o $(external)

$(outtmp)/httpserver.o :$(netDir)/http/HttpServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpServer.cpp -o $(outtmp)/httpserver.o $(external)

$(outtmp)/httpclientinfo.o :$(netDir)/http/HttpClientInfo.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpClientInfo.cpp -o $(outtmp)/httpclientinfo.o $(external)

$(outtmp)/httpheader.o :$(netDir)/http/HttpHeader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpHeader.cpp -o $(outtmp)/httpheader.o $(external)

$(outtmp)/httpheaderparser.o :$(netDir)/http/HttpHeaderParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpHeaderParser.cpp -o $(outtmp)/httpheaderparser.o $(external)

$(outtmp)/httppacket.o :$(netDir)/http/HttpPacket.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpPacket.cpp -o $(outtmp)/httppacket.o $(external)

$(outtmp)/httptext.o :$(netDir)/http/HttpText.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpText.cpp -o $(outtmp)/httptext.o $(external)

$(outtmp)/httprequest.o :$(netDir)/http/HttpRequest.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpRequest.cpp -o $(outtmp)/httprequest.o $(external)

$(outtmp)/httprequestwriter.o :$(netDir)/http/HttpRequestWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpRequestWriter.cpp -o $(outtmp)/httprequestwriter.o $(external)

$(outtmp)/httpcachecontrol.o :$(netDir)/http/HttpCacheControl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpCacheControl.cpp -o $(outtmp)/httpcachecontrol.o $(external)

$(outtmp)/httpresponse.o :$(netDir)/http/HttpResponse.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpResponse.cpp -o $(outtmp)/httpresponse.o $(external)

$(outtmp)/httpresponsewriter.o :$(netDir)/http/HttpResponseWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpResponseWriter.cpp -o $(outtmp)/httpresponsewriter.o $(external)

$(outtmp)/httpresponseparser.o :$(netDir)/http/HttpResponseParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpResponseParser.cpp -o $(outtmp)/httpresponseparser.o $(external)

$(outtmp)/httpclientmanager.o :$(netDir)/http/HttpClientManager.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/HttpClientManager.cpp -o $(outtmp)/httpclientmanager.o $(external)

$(outtmp)/websocketserver.o :$(netDir)/websocket/WebSocketServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketServer.cpp -o $(outtmp)/websocketserver.o $(external)

$(outtmp)/websocketprotocol.o :$(netDir)/websocket/WebSocketProtocol.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketProtocol.cpp -o $(outtmp)/websocketprotocol.o $(external)

$(outtmp)/websocketframe.o :$(netDir)/websocket/WebSocketFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketFrame.cpp -o $(outtmp)/websocketframe.o $(external)

$(outtmp)/websocketparser.o :$(netDir)/websocket/WebSocketParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketParser.cpp -o $(outtmp)/websocketparser.o $(external)

$(outtmp)/websockethybi13parser.o :$(netDir)/websocket/WebSocketHybi13Parser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi13Parser.cpp -o $(outtmp)/websockethybi13parser.o $(external)

$(outtmp)/websockethybi07parser.o :$(netDir)/websocket/WebSocketHybi07Parser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi07Parser.cpp -o $(outtmp)/websockethybi07parser.o $(external)

$(outtmp)/websockethybi08parser.o :$(netDir)/websocket/WebSocketHybi08Parser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi08Parser.cpp -o $(outtmp)/websockethybi08parser.o $(external)

$(outtmp)/websockethybi00parser.o :$(netDir)/websocket/WebSocketHybi00Parser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi00Parser.cpp -o $(outtmp)/websockethybi00parser.o $(external)

$(outtmp)/websockethybi13composer.o :$(netDir)/websocket/WebSocketHybi13Composer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi13Composer.cpp -o $(outtmp)/websockethybi13composer.o $(external)

$(outtmp)/websockethybi07composer.o :$(netDir)/websocket/WebSocketHybi07Composer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi07Composer.cpp -o $(outtmp)/websockethybi07composer.o $(external)

$(outtmp)/websockethybi08composer.o :$(netDir)/websocket/WebSocketHybi08Composer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi08Composer.cpp -o $(outtmp)/websockethybi08composer.o $(external)

$(outtmp)/websockethybi00composer.o :$(netDir)/websocket/WebSocketHybi00Composer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketHybi00Composer.cpp -o $(outtmp)/websockethybi00composer.o $(external)

$(outtmp)/websocketpermessagedeflate.o :$(netDir)/websocket/WebSocketPermessageDeflate.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketPermessageDeflate.cpp -o $(outtmp)/websocketpermessagedeflate.o $(external)

$(outtmp)/websocketclient.o :$(netDir)/websocket/WebSocketClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketClient.cpp -o $(outtmp)/websocketclient.o $(external)

$(outtmp)/websocketclientinfo.o :$(netDir)/websocket/WebSocketClientInfo.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/websocket/WebSocketClientInfo.cpp -o $(outtmp)/websocketclientinfo.o $(external)

$(outtmp)/ntpclient.o :$(netDir)/NtpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/NtpClient.cpp -o $(outtmp)/ntpclient.o $(external)

$(outtmp)/httpv2hpackutil.o :$(netDir)/http/v2/HttpV2HpackUtil.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2HpackUtil.cpp -o $(outtmp)/httpv2hpackutil.o $(external)

$(outtmp)/httpv2huffmandecoder.o :$(netDir)/http/v2/HttpV2HuffmanDecoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2HuffmanDecoder.cpp -o $(outtmp)/httpv2huffmandecoder.o $(external)

$(outtmp)/httpv2huffmanencoder.o :$(netDir)/http/v2/HttpV2HuffmanEncoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2HuffmanEncoder.cpp -o $(outtmp)/httpv2huffmanencoder.o $(external)

$(outtmp)/httpv2headerencoder.o :$(netDir)/http/v2/HttpV2HeaderEncoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2HeaderEncoder.cpp -o $(outtmp)/httpv2headerencoder.o $(external)

$(outtmp)/httpv2headerdecoder.o :$(netDir)/http/v2/HttpV2HeaderDecoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2HeaderDecoder.cpp -o $(outtmp)/httpv2headerdecoder.o $(external)

$(outtmp)/httpv2headerfield.o :$(netDir)/http/v2/HttpV2HeaderField.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2HeaderField.cpp -o $(outtmp)/httpv2headerfield.o $(external)

$(outtmp)/httpv2dynamictable.o :$(netDir)/http/v2/HttpV2DynamicTable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/v2/HttpV2DynamicTable.cpp -o $(outtmp)/httpv2dynamictable.o $(external)

$(outtmp)/sslserver.o :$(netDir)/http/ssl/SSLServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/ssl/SSLServer.cpp -o $(outtmp)/sslserver.o $(external)

$(outtmp)/sslinfo.o :$(netDir)/http/ssl/SSLInfo.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/ssl/SSLInfo.cpp -o $(outtmp)/sslinfo.o $(external)

$(outtmp)/sslmanager.o :$(netDir)/http/ssl/SSLManager.cpp
	$(cppcompiler) $(obotchacppflags) -c $(netDir)/http/ssl/SSLManager.cpp -o $(outtmp)/sslmanager.o $(external)
