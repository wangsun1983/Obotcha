confparser = ./external/ccl

ccl_include += -I $(confparser)/include \

link += external_conf_bst \
		external_conf_ccl_get \
		external_conf_ccl_iterate \
		external_conf_ccl_parse \
		external_conf_ccl_release \
		external_conf_ccl_reset \

objs += $(outtmp)/extconfbst.o \
        $(outtmp)/extconfcclget.o \
        $(outtmp)/extconfccliterate.o \
        $(outtmp)/extconfcclparse.o \
        $(outtmp)/extconfcclrelease.o \
        $(outtmp)/extconfcclreset.o 

external_conf_bst :$(confparser)/src/bst.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/bst.c -o $(outtmp)/extconfbst.o

external_conf_ccl_get :$(confparser)/src/ccl_get.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_get.c -o $(outtmp)/extconfcclget.o

external_conf_ccl_iterate :$(confparser)/src/ccl_iterate.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_iterate.c -o $(outtmp)/extconfccliterate.o

external_conf_ccl_parse :$(confparser)/src/ccl_parse.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_parse.c -o $(outtmp)/extconfcclparse.o

external_conf_ccl_release :$(confparser)/src/ccl_release.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_release.c -o $(outtmp)/extconfcclrelease.o

external_conf_ccl_reset :$(confparser)/src/ccl_reset.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(confparser)/src/ccl_reset.c -o $(outtmp)/extconfcclreset.o