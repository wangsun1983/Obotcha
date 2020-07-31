glogpath = ./external/glog

glog_include += -I $(glogpath)/include \

objs += $(outtmp)/glog_demangle.o \
        $(outtmp)/glog_logging.o \
        $(outtmp)/glog_raw_logging.o \
        $(outtmp)/glog_signalhandler.o \
        $(outtmp)/glog_symbolize.o \
        $(outtmp)/glog_utilities.o \
        $(outtmp)/glog_vlog_is_on.o

$(outtmp)/glog_demangle.o :$(glogpath)/demangle.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/demangle.cc -o $(outtmp)/glog_demangle.o

$(outtmp)/glog_logging.o :$(glogpath)/logging.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/logging.cc -o $(outtmp)/glog_logging.o

$(outtmp)/glog_raw_logging.o :$(glogpath)/raw_logging.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/raw_logging.cc -o $(outtmp)/glog_raw_logging.o

$(outtmp)/glog_signalhandler.o :$(glogpath)/signalhandler.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/signalhandler.cc -o $(outtmp)/glog_signalhandler.o

$(outtmp)/glog_symbolize.o :$(glogpath)/symbolize.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/symbolize.cc -o $(outtmp)/glog_symbolize.o

$(outtmp)/glog_utilities.o :$(glogpath)/utilities.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/utilities.cc -o $(outtmp)/glog_utilities.o

$(outtmp)/glog_vlog_is_on.o :$(glogpath)/vlog_is_on.cc
	$(ccompiler) $(cflags) $(glog_include) -c $(glogpath)/vlog_is_on.cc -o $(outtmp)/glog_vlog_is_on.o