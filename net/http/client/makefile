httpClientDir = $(netDir)/http/client

objs += $(outtmp)/httpget.o \
		$(outtmp)/httpdelete.o \
		$(outtmp)/httppost.o \
		$(outtmp)/httpput.o \
		$(outtmp)/httpclient.o \
		$(outtmp)/httpclientconnmanager.o \
		$(outtmp)/httpclientbaserequest.o \

$(outtmp)/httpget.o :$(httpClientDir)/HttpGet.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpGet.cpp -o $(outtmp)/httpget.o 

$(outtmp)/httpdelete.o :$(httpClientDir)/HttpDelete.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpDelete.cpp -o $(outtmp)/httpdelete.o 

$(outtmp)/httppost.o :$(httpClientDir)/HttpPost.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpPost.cpp -o $(outtmp)/httppost.o 

$(outtmp)/httpput.o :$(httpClientDir)/HttpPut.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpPut.cpp -o $(outtmp)/httpput.o 

$(outtmp)/httpclient.o :$(httpClientDir)/HttpClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpClient.cpp -o $(outtmp)/httpclient.o 

$(outtmp)/httpclientconnmanager.o :$(httpClientDir)/HttpClientConnManager.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpClientConnManager.cpp -o $(outtmp)/httpclientconnmanager.o 

$(outtmp)/httpclientbaserequest.o :$(httpClientDir)/HttpClientBaseRequest.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpClientBaseRequest.cpp -o $(outtmp)/httpclientbaserequest.o 
