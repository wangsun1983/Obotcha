httpDir = $(netDir)/http

include $(httpDir)/client/makefile

objs += $(outtmp)/httpchunk.o \
		$(outtmp)/httpchunkparser.o \
		$(outtmp)/crlfdector.o \
		$(outtmp)/httpoption.o \
		$(outtmp)/httpurl.o \
		$(outtmp)/httpstatus.o \
		$(outtmp)/httpentity.o \
		$(outtmp)/httpheaderversion.o \
		$(outtmp)/httpheadercontenttype.o \
		$(outtmp)/httpmime.o \
		$(outtmp)/httpconnection.o \
		$(outtmp)/httpmethod.o \
		$(outtmp)/httpheader.o \
		$(outtmp)/httpheaderlink.o \
		$(outtmp)/httpgeaderacceptencoding.o \
		$(outtmp)/httpheaderacceptlanguage.o \
		$(outtmp)/httpheaderacceptcharset.o \
		$(outtmp)/httpheaderxframeoptions.o \
		$(outtmp)/httpheaderaccept.o \
		$(outtmp)/httpgeaderstricttransportsecurity.o \
		$(outtmp)/httpheaderproxyauthorization.o \
		$(outtmp)/httpheaderproxyauthenticate.o \
		$(outtmp)/httpheaderforwarded.o \
		$(outtmp)/httpheaderacceptpatch.o \
		$(outtmp)/httpheaderdigest.o \
		$(outtmp)/httpheaderauthorization.o \
		$(outtmp)/HttpHeaderContentDisposition.o \
		$(outtmp)/httpheaderparser.o \
		$(outtmp)/httpheadercontentparser.o \
		$(outtmp)/httppacket.o \
		$(outtmp)/httptext.o \
		$(outtmp)/httphpack.o \
		$(outtmp)/HttpHeaderCacheControl.o \
		$(outtmp)/httppacketparserimpl.o \
		$(outtmp)/httpsession.o \
		$(outtmp)/httpsessionmanager.o \
		$(outtmp)/httpcookie.o \
		$(outtmp)/httpdate.o \
		$(outtmp)/httpmultipart.o \
		$(outtmp)/httpmultipartparser.o \
		$(outtmp)/httpserver.o \
		$(outtmp)/httpserverbuilder.o \
		$(outtmp)/httplinker.o \
		$(outtmp)/httpurlencodedvalue.o \
		$(outtmp)/httpcookieparser.o \
		$(outtmp)/httppricontentparser.o \
		$(outtmp)/httppacketwriterimpl.o \
		$(outtmp)/httpheaderallowcreditial.o \
		$(outtmp)/httpheaderallowheaders.o \
		$(outtmp)/httpheaderallowmethods.o \
		$(outtmp)/HttpHeaderAlloworigin.o \
		$(outtmp)/httpexposeheaders.o \
		$(outtmp)/httpcontrolmaxage.o \
		$(outtmp)/httprequestheaders.o \
		$(outtmp)/httprequestmethod.o \
		$(outtmp)/httpheaderage.o \
		$(outtmp)/HttpHeaderAllow.o \
		$(outtmp)/HttpHeaderClearSiteData.o \
		$(outtmp)/httpheaderconnection.o \
		$(outtmp)/httpheadercontentlocation.o \
		$(outtmp)/httpheadercontentlength.o \
		$(outtmp)/httpheadercontentlanguage.o \
		$(outtmp)/httpheadercontentencoding.o \
		$(outtmp)/httpheadermatch.o \
		$(outtmp)/httpheaderIfmodifiedsince.o \
		$(outtmp)/httpheaderifrange.o \
		$(outtmp)/httpheaderifunmodifiedsince.o \
		$(outtmp)/httpheaderkeepalive.o \
		$(outtmp)/httpheaderretryafter.o \
		$(outtmp)/httpheaderuseragent.o \
		$(outtmp)/httpheaderhost.o \
		$(outtmp)/httpheadertransferencoding.o \
		$(outtmp)/httpheaderupgrade.o \
		$(outtmp)/httpheadersecwebsocketversion.o \
		$(outtmp)/httpheaderorigin.o \
		$(outtmp)/httpheaderextensions.o \
		$(outtmp)/httpheaderwsprotocol.o \
		$(outtmp)/httpheaderwsorigin.o \
		$(outtmp)/httpheaderpragma.o \
		$(outtmp)/httpwsaccept.o \
		$(outtmp)/httpwskey.o \
		$(outtmp)/httpresponse.o \
		$(outtmp)/httprequest.o \
		$(outtmp)/httpheaderacceptranges.o \
		$(outtmp)/httpheaderaltsvc.o \
		$(outtmp)/httpheadercontentrange.o \
		$(outtmp)/httpcontentsepolicy.o \
		$(outtmp)/httpheaderdate.o \
		$(outtmp)/httpheaderexpect.o \
		$(outtmp)/httpheaderexpectct.o \
		$(outtmp)/httpheaderexpires.o \
		$(outtmp)/httpheaderfrom.o \
		$(outtmp)/httpheaderlastmodified.o \
		$(outtmp)/httpheaderlocation.o \
		$(outtmp)/httpheaderrange.o \
		$(outtmp)/httpheaderreferer.o \
		$(outtmp)/httpheaderreferrerpolicy.o \
		$(outtmp)/httpheadervary.o \
		$(outtmp)/httpheadervia.o \
		$(outtmp)/httpheaderwarning.o \
		$(outtmp)/httpheaderserver.o \
		$(outtmp)/httpheadercorssoriginopenerpolicy.o \
		$(outtmp)/httpheadercorssoriginembedderpolicy.o \
		$(outtmp)/httpheadercorssoriginresourcepolicy.o \
		$(outtmp)/httpheaderacceptch.o \
		$(outtmp)/httpheaderdnt.o \
		$(outtmp)/httpheadersavedata.o \
		$(outtmp)/httpheadersecfetchdest.o \
		$(outtmp)/httpheadersecfetchmode.o \
		$(outtmp)/httpheadersecfetchsite.o \
		$(outtmp)/httpheadersecfetchuser.o \
		$(outtmp)/httpheaderservertiming.o \
		$(outtmp)/httpheadersourcemap.o \
		$(outtmp)/hpackstatictable.o \
		$(outtmp)/hpackdynamictable.o \
		$(outtmp)/http2streamcontroller.o \
		$(outtmp)/http2stream.o \
		$(outtmp)/http2frame.o \
		$(outtmp)/http2protocol.o \
		$(outtmp)/http2packetwriterimpl.o \
		$(outtmp)/http2settingframe.o \
		$(outtmp)/http2headerframe.o \
		$(outtmp)/http2rstframe.o \
		$(outtmp)/http2dataframe.o \
		$(outtmp)/http2priorityframe.o \
		$(outtmp)/http2windowupdateframe.o \
		$(outtmp)/http2continuationframe.o \
		$(outtmp)/http2goawayframe.o \
		$(outtmp)/http2frameparser.o \
		$(outtmp)/http2responsewriter.o \
		$(outtmp)/http2pingframe.o \
		$(outtmp)/http2server.o \
		$(outtmp)/http2packet.o \
		$(outtmp)/http2pushpromiseframe.o \
		$(outtmp)/http2shakehandframe.o \
		$(outtmp)/http2errorcode.o \
		$(outtmp)/http2streamsender.o \
		$(outtmp)/http2framebytearray.o \
		$(outtmp)/http2streamstatistics.o \
		$(outtmp)/hpackhuffmanencoder.o \
		$(outtmp)/hpackhuffmandecoder.o \
		$(outtmp)/hpacktableitem.o \
		$(outtmp)/hpackencoder.o \
		$(outtmp)/hpackdecoder.o \
		$(outtmp)/hpacksensitivetable.o \
		$(outtmp)/httpsimplewriterimpl.o \


$(outtmp)/httpchunk.o :$(httpDir)/HttpChunk.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpChunk.cpp -o $(outtmp)/httpchunk.o

$(outtmp)/httpchunkparser.o :$(httpDir)/HttpChunkParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpChunkParser.cpp -o $(outtmp)/httpchunkparser.o

$(outtmp)/crlfdector.o :$(httpDir)/CRLFDetector.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/CRLFDetector.cpp -o $(outtmp)/crlfdector.o

$(outtmp)/httpurlencodedvalue.o :$(httpDir)/HttpUrlEncodedValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpUrlEncodedValue.cpp -o $(outtmp)/httpurlencodedvalue.o

$(outtmp)/httpconnection.o :$(httpDir)/HttpConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpConnection.cpp -o $(outtmp)/httpconnection.o

$(outtmp)/httpmethod.o :$(httpDir)/HttpMethod.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpMethod.cpp -o $(outtmp)/httpmethod.o

#$(outtmp)/httpurlparser.o :$(httpDir)/HttpUrlParser.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpUrlParser.cpp -o $(outtmp)/httpurlparser.o

$(outtmp)/httpoption.o :$(httpDir)/HttpOption.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpOption.cpp -o $(outtmp)/httpoption.o

$(outtmp)/httpurl.o :$(httpDir)/HttpUrl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpUrl.cpp -o $(outtmp)/httpurl.o

$(outtmp)/httprequest.o :$(httpDir)/HttpRequest.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpRequest.cpp -o $(outtmp)/httprequest.o

$(outtmp)/httpresponse.o :$(httpDir)/HttpResponse.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpResponse.cpp -o $(outtmp)/httpresponse.o

#$(outtmp)/httpfile.o :$(httpDir)/HttpFile.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpFile.cpp -o $(outtmp)/httpfile.o

$(outtmp)/httpheaderallowcreditial.o :$(httpDir)/headers/HttpHeaderAccessControlAllowCredentials.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlAllowCredentials.cpp -o $(outtmp)/httpheaderallowcreditial.o

$(outtmp)/httpwsaccept.o :$(httpDir)/headers/HttpHeaderSecWebSocketAccept.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecWebSocketAccept.cpp -o $(outtmp)/httpwsaccept.o

$(outtmp)/httpwskey.o :$(httpDir)/headers/HttpHeaderSecWebSocketKey.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecWebSocketKey.cpp -o $(outtmp)/httpwskey.o

$(outtmp)/httpheaderallowheaders.o :$(httpDir)/headers/HttpHeaderAccessControlAllowHeaders.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlAllowHeaders.cpp -o $(outtmp)/httpheaderallowheaders.o

$(outtmp)/httpheaderacceptranges.o :$(httpDir)/headers/HttpHeaderAcceptRanges.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAcceptRanges.cpp -o $(outtmp)/httpheaderacceptranges.o

$(outtmp)/httpheaderaltsvc.o :$(httpDir)/headers/HttpHeaderAltSvc.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAltSvc.cpp -o $(outtmp)/httpheaderaltsvc.o

$(outtmp)/httpheadercontentrange.o :$(httpDir)/headers/HttpHeaderContentRange.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentRange.cpp -o $(outtmp)/httpheadercontentrange.o

$(outtmp)/httpcontentsepolicy.o :$(httpDir)/headers/HttpHeaderContentSecurityPolicy.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentSecurityPolicy.cpp -o $(outtmp)/httpcontentsepolicy.o

$(outtmp)/httpheaderdate.o :$(httpDir)/headers/HttpHeaderDate.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderDate.cpp -o $(outtmp)/httpheaderdate.o

$(outtmp)/httpheaderexpect.o :$(httpDir)/headers/HttpHeaderExpect.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderExpect.cpp -o $(outtmp)/httpheaderexpect.o

$(outtmp)/httpheaderexpectct.o :$(httpDir)/headers/HttpHeaderExpectCT.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderExpectCT.cpp -o $(outtmp)/httpheaderexpectct.o

$(outtmp)/httpheaderexpires.o :$(httpDir)/headers/HttpHeaderExpires.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderExpires.cpp -o $(outtmp)/httpheaderexpires.o

$(outtmp)/httpheaderfrom.o :$(httpDir)/headers/HttpHeaderFrom.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderFrom.cpp -o $(outtmp)/httpheaderfrom.o

$(outtmp)/httpheaderlastmodified.o :$(httpDir)/headers/HttpHeaderLastModified.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderLastModified.cpp -o $(outtmp)/httpheaderlastmodified.o

$(outtmp)/httpheaderlocation.o :$(httpDir)/headers/HttpHeaderLocation.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderLocation.cpp -o $(outtmp)/httpheaderlocation.o

$(outtmp)/httpheaderrange.o :$(httpDir)/headers/HttpHeaderRange.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderRange.cpp -o $(outtmp)/httpheaderrange.o

$(outtmp)/httpheaderreferer.o :$(httpDir)/headers/HttpHeaderReferer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderReferer.cpp -o $(outtmp)/httpheaderreferer.o

$(outtmp)/httpheaderreferrerpolicy.o :$(httpDir)/headers/HttpHeaderReferrerPolicy.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderReferrerPolicy.cpp -o $(outtmp)/httpheaderreferrerpolicy.o

$(outtmp)/httpheadervary.o :$(httpDir)/headers/HttpHeaderVary.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderVary.cpp -o $(outtmp)/httpheadervary.o

$(outtmp)/httpheadervia.o :$(httpDir)/headers/HttpHeaderVia.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderVia.cpp -o $(outtmp)/httpheadervia.o

$(outtmp)/httpheaderwarning.o :$(httpDir)/headers/HttpHeaderWarning.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderWarning.cpp -o $(outtmp)/httpheaderwarning.o

$(outtmp)/httpheaderserver.o :$(httpDir)/headers/HttpHeaderServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderServer.cpp -o $(outtmp)/httpheaderserver.o

$(outtmp)/httpheadercorssoriginopenerpolicy.o :$(httpDir)/headers/HttpHeaderCrossOriginOpenerPolicy.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderCrossOriginOpenerPolicy.cpp -o $(outtmp)/httpheadercorssoriginopenerpolicy.o

$(outtmp)/httpheadercorssoriginresourcepolicy.o :$(httpDir)/headers/HttpHeaderCrossOriginResourcePolicy.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderCrossOriginResourcePolicy.cpp -o $(outtmp)/httpheadercorssoriginresourcepolicy.o

$(outtmp)/httpheaderacceptch.o :$(httpDir)/headers/HttpHeaderAcceptCh.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAcceptCh.cpp -o $(outtmp)/httpheaderacceptch.o

$(outtmp)/httpheaderdnt.o :$(httpDir)/headers/HttpHeaderDnt.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderDnt.cpp -o $(outtmp)/httpheaderdnt.o

$(outtmp)/httpheadersavedata.o :$(httpDir)/headers/HttpHeaderSaveData.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSaveData.cpp -o $(outtmp)/httpheadersavedata.o

$(outtmp)/httpheadersecfetchdest.o :$(httpDir)/headers/HttpHeaderSecFetchDest.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecFetchDest.cpp -o $(outtmp)/httpheadersecfetchdest.o

$(outtmp)/httpheadersecfetchmode.o :$(httpDir)/headers/HttpHeaderSecFetchMode.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecFetchMode.cpp -o $(outtmp)/httpheadersecfetchmode.o

$(outtmp)/httpheadersecfetchsite.o :$(httpDir)/headers/HttpHeaderSecFetchSite.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecFetchSite.cpp -o $(outtmp)/httpheadersecfetchsite.o

$(outtmp)/httpheadersecfetchuser.o :$(httpDir)/headers/HttpHeaderSecFetchUser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecFetchUser.cpp -o $(outtmp)/httpheadersecfetchuser.o

$(outtmp)/httpheaderservertiming.o :$(httpDir)/headers/HttpHeaderServerTiming.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderServerTiming.cpp -o $(outtmp)/httpheaderservertiming.o

$(outtmp)/httpheadersourcemap.o :$(httpDir)/headers/HttpHeaderSourceMap.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSourceMap.cpp -o $(outtmp)/httpheadersourcemap.o

$(outtmp)/httpheadercorssoriginembedderpolicy.o :$(httpDir)/headers/HttpHeaderCrossOriginEmbedderPolicy.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderCrossOriginEmbedderPolicy.cpp -o $(outtmp)/httpheadercorssoriginembedderpolicy.o

$(outtmp)/httpheaderallowmethods.o :$(httpDir)/headers/HttpHeaderAccessControlAllowMethods.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlAllowMethods.cpp -o $(outtmp)/httpheaderallowmethods.o

$(outtmp)/HttpHeaderAlloworigin.o :$(httpDir)/headers/HttpHeaderAccessControlAllowOrigin.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlAllowOrigin.cpp -o $(outtmp)/HttpHeaderAlloworigin.o

$(outtmp)/httpexposeheaders.o :$(httpDir)/headers/HttpHeaderAccessControlExposeHeaders.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlExposeHeaders.cpp -o $(outtmp)/httpexposeheaders.o

$(outtmp)/httpcontrolmaxage.o :$(httpDir)/headers/HttpHeaderAccessControlMaxAge.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlMaxAge.cpp -o $(outtmp)/httpcontrolmaxage.o

$(outtmp)/httprequestheaders.o :$(httpDir)/headers/HttpHeaderAccessControlRequestHeaders.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlRequestHeaders.cpp -o $(outtmp)/httprequestheaders.o

$(outtmp)/httprequestmethod.o :$(httpDir)/headers/HttpHeaderAccessControlRequestMethod.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccessControlRequestMethod.cpp -o $(outtmp)/httprequestmethod.o

$(outtmp)/httpheaderage.o :$(httpDir)/headers/HttpHeaderAge.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAge.cpp -o $(outtmp)/httpheaderage.o

$(outtmp)/httpheaderorigin.o :$(httpDir)/headers/HttpHeaderOrigin.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderOrigin.cpp -o $(outtmp)/httpheaderorigin.o

$(outtmp)/httpheaderpragma.o :$(httpDir)/headers/HttpHeaderPragma.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderPragma.cpp -o $(outtmp)/httpheaderpragma.o

$(outtmp)/httpheaderIfmodifiedsince.o :$(httpDir)/headers/HttpHeaderIfModifiedSince.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderIfModifiedSince.cpp -o $(outtmp)/httpheaderIfmodifiedsince.o

$(outtmp)/httpheaderifrange.o :$(httpDir)/headers/HttpHeaderIfRange.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderIfRange.cpp -o $(outtmp)/httpheaderifrange.o

$(outtmp)/httpheaderifunmodifiedsince.o :$(httpDir)/headers/HttpHeaderIfUnmodifiedSince.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderIfUnmodifiedSince.cpp -o $(outtmp)/httpheaderifunmodifiedsince.o

$(outtmp)/httpheaderkeepalive.o :$(httpDir)/headers/HttpHeaderKeepAlive.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderKeepAlive.cpp -o $(outtmp)/httpheaderkeepalive.o

$(outtmp)/httpheaderretryafter.o :$(httpDir)/headers/HttpHeaderRetryAfter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderRetryAfter.cpp -o $(outtmp)/httpheaderretryafter.o

$(outtmp)/httpheaderuseragent.o :$(httpDir)/headers/HttpHeaderUserAgent.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderUserAgent.cpp -o $(outtmp)/httpheaderuseragent.o

$(outtmp)/httpheaderhost.o :$(httpDir)/headers/HttpHeaderHost.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderHost.cpp -o $(outtmp)/httpheaderhost.o

$(outtmp)/httpheadertransferencoding.o :$(httpDir)/headers/HttpHeaderTransferEncoding.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderTransferEncoding.cpp -o $(outtmp)/httpheadertransferencoding.o

$(outtmp)/httpheaderupgrade.o :$(httpDir)/headers/HttpHeaderUpgrade.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderUpgrade.cpp -o $(outtmp)/httpheaderupgrade.o

$(outtmp)/httpheadersecwebsocketversion.o :$(httpDir)/headers/HttpHeaderSecWebSocketVersion.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecWebSocketVersion.cpp -o $(outtmp)/httpheadersecwebsocketversion.o

$(outtmp)/httpheaderwsorigin.o :$(httpDir)/headers/HttpHeaderSecWebSocketOrigin.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecWebSocketOrigin.cpp -o $(outtmp)/httpheaderwsorigin.o

$(outtmp)/httpheaderextensions.o :$(httpDir)/headers/HttpHeaderSecWebSocketExtensions.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecWebSocketExtensions.cpp -o $(outtmp)/httpheaderextensions.o

$(outtmp)/httpheaderwsprotocol.o :$(httpDir)/headers/HttpHeaderSecWebSocketProtocol.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderSecWebSocketProtocol.cpp -o $(outtmp)/httpheaderwsprotocol.o

$(outtmp)/HttpHeaderAllow.o :$(httpDir)/headers/HttpHeaderAllow.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAllow.cpp -o $(outtmp)/HttpHeaderAllow.o

$(outtmp)/HttpHeaderClearSiteData.o :$(httpDir)/headers/HttpHeaderClearSiteData.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderClearSiteData.cpp -o $(outtmp)/HttpHeaderClearSiteData.o

$(outtmp)/httpheaderconnection.o :$(httpDir)/headers/HttpHeaderConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderConnection.cpp -o $(outtmp)/httpheaderconnection.o

$(outtmp)/httpheadercontentlocation.o :$(httpDir)/headers/HttpHeaderContentLocation.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentLocation.cpp -o $(outtmp)/httpheadercontentlocation.o

$(outtmp)/httpheadercontentlength.o :$(httpDir)/headers/HttpHeaderContentLength.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentLength.cpp -o $(outtmp)/httpheadercontentlength.o

$(outtmp)/httpheadercontentlanguage.o :$(httpDir)/headers/HttpHeaderContentLanguage.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentLanguage.cpp -o $(outtmp)/httpheadercontentlanguage.o

$(outtmp)/httpheadercontentencoding.o :$(httpDir)/headers/HttpHeaderContentEncoding.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentEncoding.cpp -o $(outtmp)/httpheadercontentencoding.o

$(outtmp)/httpheadermatch.o :$(httpDir)/headers/HttpHeaderMatch.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderMatch.cpp -o $(outtmp)/httpheadermatch.o

$(outtmp)/httpstatus.o :$(httpDir)/HttpStatus.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpStatus.cpp -o $(outtmp)/httpstatus.o

$(outtmp)/httpheaderversion.o :$(httpDir)/headers/HttpHeaderVersion.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderVersion.cpp -o $(outtmp)/httpheaderversion.o

$(outtmp)/httpentity.o :$(httpDir)/HttpEntity.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpEntity.cpp -o $(outtmp)/httpentity.o

$(outtmp)/httpheadercontenttype.o :$(httpDir)/headers/HttpHeaderContentType.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentType.cpp -o $(outtmp)/httpheadercontenttype.o

$(outtmp)/httpmime.o :$(httpDir)/HttpMime.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpMime.cpp -o $(outtmp)/httpmime.o

#$(outtmp)/httpurlbuilder.o :$(httpDir)/HttpUrlBuilder.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpUrlBuilder.cpp -o $(outtmp)/httpurlbuilder.o

$(outtmp)/httpcookie.o :$(httpDir)/HttpCookie.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpCookie.cpp -o $(outtmp)/httpcookie.o

$(outtmp)/httpheaderauthorization.o :$(httpDir)/headers/HttpHeaderAuthorization.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAuthorization.cpp -o $(outtmp)/httpheaderauthorization.o

$(outtmp)/HttpHeaderContentDisposition.o :$(httpDir)/headers/HttpHeaderContentDisposition.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentDisposition.cpp -o $(outtmp)/HttpHeaderContentDisposition.o

$(outtmp)/httpdate.o :$(httpDir)/HttpDate.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpDate.cpp -o $(outtmp)/httpdate.o

$(outtmp)/httpmultipart.o :$(httpDir)/HttpMultiPart.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpMultiPart.cpp -o $(outtmp)/httpmultipart.o

$(outtmp)/httpmultipartparser.o :$(httpDir)/HttpMultiPartParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpMultiPartParser.cpp -o $(outtmp)/httpmultipartparser.o

$(outtmp)/httpserver.o :$(httpDir)/HttpServer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpServer.cpp -o $(outtmp)/httpserver.o

$(outtmp)/httpserverbuilder.o :$(httpDir)/HttpServerBuilder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpServerBuilder.cpp -o $(outtmp)/httpserverbuilder.o

$(outtmp)/httplinker.o :$(httpDir)/HttpLinker.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpLinker.cpp -o $(outtmp)/httplinker.o

$(outtmp)/httpheader.o :$(httpDir)/HttpHeader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpHeader.cpp -o $(outtmp)/httpheader.o

$(outtmp)/httpheaderlink.o :$(httpDir)/headers/HttpHeaderLink.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderLink.cpp -o $(outtmp)/httpheaderlink.o

$(outtmp)/httpgeaderacceptencoding.o :$(httpDir)/headers/HttpHeaderAcceptEncoding.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAcceptEncoding.cpp -o $(outtmp)/httpgeaderacceptencoding.o

$(outtmp)/httpheaderacceptlanguage.o :$(httpDir)/headers/HttpHeaderAcceptLanguage.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAcceptLanguage.cpp -o $(outtmp)/httpheaderacceptlanguage.o

$(outtmp)/httpheaderacceptcharset.o :$(httpDir)/headers/HttpHeaderAcceptCharSet.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAcceptCharSet.cpp -o $(outtmp)/httpheaderacceptcharset.o

$(outtmp)/httpheaderaccept.o :$(httpDir)/headers/HttpHeaderAccept.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAccept.cpp -o $(outtmp)/httpheaderaccept.o

$(outtmp)/httpgeaderstricttransportsecurity.o :$(httpDir)/headers/HttpHeaderStrictTransportSecurity.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderStrictTransportSecurity.cpp -o $(outtmp)/httpgeaderstricttransportsecurity.o

$(outtmp)/httpheaderforwarded.o :$(httpDir)/headers/HttpHeaderForwarded.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderForwarded.cpp -o $(outtmp)/httpheaderforwarded.o

$(outtmp)/httpheaderacceptpatch.o :$(httpDir)/headers/HttpHeaderAcceptPatch.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderAcceptPatch.cpp -o $(outtmp)/httpheaderacceptpatch.o

$(outtmp)/httpheaderproxyauthenticate.o :$(httpDir)/headers/HttpHeaderProxyAuthenticate.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderProxyAuthenticate.cpp -o $(outtmp)/httpheaderproxyauthenticate.o

$(outtmp)/httpheaderproxyauthorization.o :$(httpDir)/headers/HttpHeaderProxyAuthorization.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderProxyAuthorization.cpp -o $(outtmp)/httpheaderproxyauthorization.o

$(outtmp)/httpheaderxframeoptions.o :$(httpDir)/headers/HttpHeaderXFrameOptions.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderXFrameOptions.cpp -o $(outtmp)/httpheaderxframeoptions.o

$(outtmp)/httpheaderdigest.o :$(httpDir)/headers/HttpHeaderDigest.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderDigest.cpp -o $(outtmp)/httpheaderdigest.o

$(outtmp)/httpheaderparser.o :$(httpDir)/HttpHeaderParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpHeaderParser.cpp -o $(outtmp)/httpheaderparser.o

$(outtmp)/httpheadercontentparser.o :$(httpDir)/headers/HttpHeaderContentParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderContentParser.cpp -o $(outtmp)/httpheadercontentparser.o

$(outtmp)/httppacket.o :$(httpDir)/HttpPacket.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpPacket.cpp -o $(outtmp)/httppacket.o

$(outtmp)/httptext.o :$(httpDir)/HttpText.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpText.cpp -o $(outtmp)/httptext.o

#$(outtmp)/httprequest.o :$(httpDir)/HttpRequest.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpRequest.cpp -o $(outtmp)/httprequest.o

#$(outtmp)/httprequestwriter.o :$(httpDir)/HttpRequestWriter.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpRequestWriter.cpp -o $(outtmp)/httprequestwriter.o

$(outtmp)/HttpHeaderCacheControl.o :$(httpDir)/headers/HttpHeaderCacheControl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/headers/HttpHeaderCacheControl.cpp -o $(outtmp)/HttpHeaderCacheControl.o

$(outtmp)/httppacketwriterimpl.o :$(httpDir)/HttpPacketWriterImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpPacketWriterImpl.cpp -o $(outtmp)/httppacketwriterimpl.o

$(outtmp)/httppacketparserimpl.o :$(httpDir)/HttpPacketParserImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpPacketParserImpl.cpp -o $(outtmp)/httppacketparserimpl.o

$(outtmp)/httpcookieparser.o :$(httpDir)/HttpCookieParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpCookieParser.cpp -o $(outtmp)/httpcookieparser.o

$(outtmp)/httppricontentparser.o :$(httpDir)/HttpPriContentParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpPriContentParser.cpp -o $(outtmp)/httppricontentparser.o

$(outtmp)/httpsession.o :$(httpDir)/HttpSession.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpSession.cpp -o $(outtmp)/httpsession.o

$(outtmp)/httpsessionmanager.o :$(httpDir)/HttpSessionManager.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpSessionManager.cpp -o $(outtmp)/httpsessionmanager.o

$(outtmp)/hpackstatictable.o :$(httpDir)/v2/HPackStaticTable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackStaticTable.cpp -o $(outtmp)/hpackstatictable.o

$(outtmp)/hpackdynamictable.o :$(httpDir)/v2/HPackDynamicTable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackDynamicTable.cpp -o $(outtmp)/hpackdynamictable.o

$(outtmp)/http2frame.o :$(httpDir)/v2/Http2Frame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2Frame.cpp -o $(outtmp)/http2frame.o

$(outtmp)/http2frameparser.o :$(httpDir)/v2/Http2FrameParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2FrameParser.cpp -o $(outtmp)/http2frameparser.o

$(outtmp)/http2responsewriter.o :$(httpDir)/v2/Http2ResponseWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2ResponseWriter.cpp -o $(outtmp)/http2responsewriter.o

$(outtmp)/http2pingframe.o :$(httpDir)/v2/Http2PingFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2PingFrame.cpp -o $(outtmp)/http2pingframe.o

$(outtmp)/http2packet.o :$(httpDir)/v2/Http2Packet.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2Packet.cpp -o $(outtmp)/http2packet.o

$(outtmp)/http2streamcontroller.o :$(httpDir)/v2/Http2StreamController.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2StreamController.cpp -o $(outtmp)/http2streamcontroller.o

$(outtmp)/http2stream.o :$(httpDir)/v2/Http2Stream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2Stream.cpp -o $(outtmp)/http2stream.o

$(outtmp)/http2protocol.o :$(httpDir)/v2/Http2Protocol.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2Protocol.cpp -o $(outtmp)/http2protocol.o

$(outtmp)/http2packetwriterimpl.o :$(httpDir)/v2/Http2PacketWriterImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2PacketWriterImpl.cpp -o $(outtmp)/http2packetwriterimpl.o

$(outtmp)/http2settingframe.o :$(httpDir)/v2/Http2SettingFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2SettingFrame.cpp -o $(outtmp)/http2settingframe.o

$(outtmp)/http2headerframe.o :$(httpDir)/v2/Http2HeaderFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2HeaderFrame.cpp -o $(outtmp)/http2headerframe.o

$(outtmp)/http2rstframe.o :$(httpDir)/v2/Http2RstFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2RstFrame.cpp -o $(outtmp)/http2rstframe.o

$(outtmp)/http2dataframe.o :$(httpDir)/v2/Http2DataFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2DataFrame.cpp -o $(outtmp)/http2dataframe.o

$(outtmp)/http2priorityframe.o :$(httpDir)/v2/Http2PriorityFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2PriorityFrame.cpp -o $(outtmp)/http2priorityframe.o

$(outtmp)/http2windowupdateframe.o :$(httpDir)/v2/Http2WindowUpdateFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2WindowUpdateFrame.cpp -o $(outtmp)/http2windowupdateframe.o

$(outtmp)/http2pushpromiseframe.o :$(httpDir)/v2/Http2PushPromiseFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2PushPromiseFrame.cpp -o $(outtmp)/http2pushpromiseframe.o

$(outtmp)/http2shakehandframe.o :$(httpDir)/v2/Http2ShakeHandFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2ShakeHandFrame.cpp -o $(outtmp)/http2shakehandframe.o

$(outtmp)/http2errorcode.o :$(httpDir)/v2/Http2ErrorCode.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2ErrorCode.cpp -o $(outtmp)/http2errorcode.o

$(outtmp)/http2streamsender.o :$(httpDir)/v2/Http2StreamSender.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2StreamSender.cpp -o $(outtmp)/http2streamsender.o

$(outtmp)/http2framebytearray.o :$(httpDir)/v2/Http2FrameByteArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2FrameByteArray.cpp -o $(outtmp)/http2framebytearray.o

$(outtmp)/http2streamstatistics.o :$(httpDir)/v2/Http2StreamStatistics.cpp
		$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2StreamStatistics.cpp -o $(outtmp)/http2streamstatistics.o

$(outtmp)/http2continuationframe.o :$(httpDir)/v2/Http2ContinuationFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2ContinuationFrame.cpp -o $(outtmp)/http2continuationframe.o

$(outtmp)/http2goawayframe.o :$(httpDir)/v2/Http2GoAwayFrame.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2GoAwayFrame.cpp -o $(outtmp)/http2goawayframe.o

$(outtmp)/httphpack.o :$(httpDir)/v2/HPack.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPack.cpp -o $(outtmp)/httphpack.o

$(outtmp)/hpackhuffmanencoder.o :$(httpDir)/v2/HPackHuffmanEncoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackHuffmanEncoder.cpp -o $(outtmp)/hpackhuffmanencoder.o

$(outtmp)/hpackhuffmandecoder.o :$(httpDir)/v2/HPackHuffmanDecoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackHuffmanDecoder.cpp -o $(outtmp)/hpackhuffmandecoder.o

$(outtmp)/hpacktableitem.o :$(httpDir)/v2/HPackTableItem.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackTableItem.cpp -o $(outtmp)/hpacktableitem.o

$(outtmp)/hpackencoder.o :$(httpDir)/v2/HPackEncoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackEncoder.cpp -o $(outtmp)/hpackencoder.o

$(outtmp)/hpackdecoder.o :$(httpDir)/v2/HPackDecoder.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackDecoder.cpp -o $(outtmp)/hpackdecoder.o

$(outtmp)/hpacksensitivetable.o :$(httpDir)/v2/HPackSensitiveTable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/HPackSensitiveTable.cpp -o $(outtmp)/hpacksensitivetable.o

$(outtmp)/http2server.o :$(httpDir)/v2/Http2Server.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/v2/Http2Server.cpp -o $(outtmp)/http2server.o

$(outtmp)/httpsimplewriterimpl.o :$(httpDir)/HttpSimplePacketWriterImpl.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpDir)/HttpSimplePacketWriterImpl.cpp -o $(outtmp)/httpsimplewriterimpl.o
