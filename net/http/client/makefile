httpClientDir = $(netDir)/http/client

objs += $(outtmp)/httpget.o \
		$(outtmp)/httpclient.o \
		$(outtmp)/httpclientconnmanager.o \
		$(outtmp)/httpclientbaserequest.o 

$(outtmp)/httpget.o :$(httpClientDir)/HttpGet.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpGet.cpp -o $(outtmp)/httpget.o 

$(outtmp)/httpclient.o :$(httpClientDir)/HttpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpClient.cpp -o $(outtmp)/httpclient.o 

$(outtmp)/httpclientconnmanager.o :$(httpClientDir)/HttpClientConnManager.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpClientConnManager.cpp -o $(outtmp)/httpclientconnmanager.o 

$(outtmp)/httpclientbaserequest.o :$(httpClientDir)/HttpClientBaseRequest.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpClientBaseRequest.cpp -o $(outtmp)/httpclientbaserequest.o 
