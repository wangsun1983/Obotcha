confparser = ./external/ccl

ccl_include += -I $(confparser)/include \

objs += $(outtmp)/extconfbst.o \
        $(outtmp)/extconfcclget.o \
        $(outtmp)/extconfccliterate.o \
        $(outtmp)/extconfcclparse.o \
        $(outtmp)/extconfcclrelease.o \
        $(outtmp)/extconfcclreset.o

$(outtmp)/extconfbst.o :$(confparser)/src/bst.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/bst.c -o $(outtmp)/extconfbst.o

$(outtmp)/extconfcclget.o :$(confparser)/src/ccl_get.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_get.c -o $(outtmp)/extconfcclget.o

$(outtmp)/extconfccliterate.o :$(confparser)/src/ccl_iterate.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_iterate.c -o $(outtmp)/extconfccliterate.o

$(outtmp)/extconfcclparse.o :$(confparser)/src/ccl_parse.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_parse.c -o $(outtmp)/extconfcclparse.o

$(outtmp)/extconfcclrelease.o :$(confparser)/src/ccl_release.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_release.c -o $(outtmp)/extconfcclrelease.o

$(outtmp)/extconfcclreset.o :$(confparser)/src/ccl_reset.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_reset.c -o $(outtmp)/extconfcclreset.o
