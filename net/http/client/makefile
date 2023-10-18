httpClientDir = $(netDir)/http/client

objs += $(outtmp)/httpget.o \
		$(outtmp)/httpdelete.o \
		$(outtmp)/httppost.o \
		$(outtmp)/httpput.o 
		
$(outtmp)/httpget.o :$(httpClientDir)/HttpGet.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpGet.cpp -o $(outtmp)/httpget.o 

$(outtmp)/httpdelete.o :$(httpClientDir)/HttpDelete.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpDelete.cpp -o $(outtmp)/httpdelete.o 

$(outtmp)/httppost.o :$(httpClientDir)/HttpPost.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpPost.cpp -o $(outtmp)/httppost.o 

$(outtmp)/httpput.o :$(httpClientDir)/HttpPut.cpp
	$(cppcompiler) $(obotchacppflags) -c $(httpClientDir)/HttpPut.cpp -o $(outtmp)/httpput.o 
