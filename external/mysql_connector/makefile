include ./external/mysql_connector/extlib/makefile

libmysql = ./external/mysql_connector

mysql_include += -I $(libmysql)/include \
				-I ./external/zlib/include \

mysql_build_flag = -Wno-pointer-to-int-cast \
									-Wno-int-to-pointer-cast

objs += $(outtmp)/mysql_client.o \
		$(outtmp)/mysql_errmsg.o \
		$(outtmp)/mysql_get_password.o \
		$(outtmp)/mysql_libmysql.o \
		$(outtmp)/mysql_my_time.o \
		$(outtmp)/mysql_net_serv.o \
		$(outtmp)/mysql_pack.o \
		$(outtmp)/mysql_password.o \
		$(outtmp)/mysql_strings_bchange.o\
		$(outtmp)/mysql_strings_bcmp.o\
		$(outtmp)/mysql_strings_bfill.o\
		$(outtmp)/mysql_strings_bmove.o\
		$(outtmp)/mysql_strings_bmove512.o\
		$(outtmp)/mysql_strings_bmove_upp.o\
		$(outtmp)/mysql_strings_conf_to_src.o\
		$(outtmp)/mysql_strings_ctype.o\
		$(outtmp)/mysql_strings_ctype-big5.o\
		$(outtmp)/mysql_strings_ctype-bin.o\
		$(outtmp)/mysql_strings_ctype-cp932.o\
		$(outtmp)/mysql_strings_ctype-czech.o\
		$(outtmp)/mysql_strings_ctype-eucjpms.o\
		$(outtmp)/mysql_strings_ctype-euc_kr.o\
		$(outtmp)/mysql_strings_ctype-extra.o\
		$(outtmp)/mysql_strings_ctype-gb2312.o\
		$(outtmp)/mysql_strings_ctype-latin1.o\
		$(outtmp)/mysql_strings_ctype-mb.o\
		$(outtmp)/mysql_strings_ctype-simple.o\
		$(outtmp)/mysql_strings_ctype-sjis.o\
		$(outtmp)/mysql_strings_ctype-tis620.o\
		$(outtmp)/mysql_strings_ctype-uca.o\
		$(outtmp)/mysql_strings_ctype-ucs2.o\
		$(outtmp)/mysql_strings_ctype-ujis.o\
		$(outtmp)/mysql_strings_ctype-utf8.o\
		$(outtmp)/mysql_strings_ctype-win1250ch.o\
		$(outtmp)/mysql_strings_ctype-gbk.o\
		$(outtmp)/mysql_strings_decimal.o\
		$(outtmp)/mysql_strings_do_ctype.o\
		$(outtmp)/mysql_strings_dtoa.o\
		$(outtmp)/mysql_strings_dump_map.o\
		$(outtmp)/mysql_strings_int2str.o\
		$(outtmp)/mysql_strings_is_prefix.o\
		$(outtmp)/mysql_strings_llstr.o\
		$(outtmp)/mysql_strings_longlong2str.o\
		$(outtmp)/mysql_strings_my_strchr.o\
		$(outtmp)/mysql_strings_my_strtoll10.o\
		$(outtmp)/mysql_strings_my_vsnprintf.o\
		$(outtmp)/mysql_strings_r_strinstr.o\
		$(outtmp)/mysql_strings_str2int.o\
		$(outtmp)/mysql_strings_str_alloc.o\
		$(outtmp)/mysql_strings_strappend.o\
		$(outtmp)/mysql_strings_strcend.o\
		$(outtmp)/mysql_strings_strcont.o\
		$(outtmp)/mysql_strings_strend.o\
		$(outtmp)/mysql_strings_strfill.o\
		$(outtmp)/mysql_strings_strinstr.o\
		$(outtmp)/mysql_strings_strmake.o\
		$(outtmp)/mysql_strings_strmov.o\
		$(outtmp)/mysql_strings_strnlen.o\
		$(outtmp)/mysql_strings_strnmov.o\
		$(outtmp)/mysql_strings_strstr.o\
		$(outtmp)/mysql_strings_strtol.o\
		$(outtmp)/mysql_strings_strtoll.o\
		$(outtmp)/mysql_strings_strtoul.o\
		$(outtmp)/mysql_strings_strtoull.o\
		$(outtmp)/mysql_strings_strxmov.o\
		$(outtmp)/mysql_strings_strxnmov.o\
		$(outtmp)/mysql_strings_xml.o\
		$(outtmp)/mysql_mysys_array.o\
		$(outtmp)/mysql_mysys_base64.o\
		$(outtmp)/mysql_mysys_charset.o\
		$(outtmp)/mysql_mysys_charset-def.o\
		$(outtmp)/mysql_mysys_checksum.o\
		$(outtmp)/mysql_mysys_default.o\
		$(outtmp)/mysql_mysys_default_modify.o\
		$(outtmp)/mysql_mysys_errors.o\
		$(outtmp)/mysql_mysys_hash.o\
		$(outtmp)/mysql_mysys_if_alloc-pin.o\
		$(outtmp)/mysql_mysys_if_dynarray.o\
		$(outtmp)/mysql_mysys_if_hash.o\
		$(outtmp)/mysql_mysys_list.o\
		$(outtmp)/mysql_mysys_md5.o\
		$(outtmp)/mysql_mysys_mf_arr_appstr.o\
		$(outtmp)/mysql_mysys_mf_brkhant.o\
		$(outtmp)/mysql_mysys_mf_cache.o\
		$(outtmp)/mysql_mysys_mf_dirname.o\
		$(outtmp)/mysql_mysys_mf_fn_ext.o\
		$(outtmp)/mysql_mysys_mf_format.o\
		$(outtmp)/mysql_mysys_mf_getdate.o\
		$(outtmp)/mysql_mysys_mf_iocache.o\
		$(outtmp)/mysql_mysys_mf_iocache2.o\
		$(outtmp)/mysql_mysys_mf_keycache.o\
		$(outtmp)/mysql_mysys_mf_keycaches.o\
		$(outtmp)/mysql_mysys_mf_loadpath.o\
		$(outtmp)/mysql_mysys_mf_pack.o\
		$(outtmp)/mysql_mysys_mf_path.o\
		$(outtmp)/mysql_mysys_mf_qsort.o\
		$(outtmp)/mysql_mysys_mf_qsort2.o\
		$(outtmp)/mysql_mysys_mf_radix.o\
		$(outtmp)/mysql_mysys_mf_same.o\
		$(outtmp)/mysql_mysys_mf_sort.o\
		$(outtmp)/mysql_mysys_mf_soundex.o\
		$(outtmp)/mysql_mysys_mf_strip.o\
		$(outtmp)/mysql_mysys_mf_tempdir.o\
		$(outtmp)/mysql_mysys_mf_tempfile.o\
		$(outtmp)/mysql_mysys_mf_unixpath.o\
		$(outtmp)/mysql_mysys_mf_util.o\
		$(outtmp)/mysql_mysys_mf_wcomp.o\
		$(outtmp)/mysql_mysys_mf_wfile.o\
		$(outtmp)/mysql_mysys_mulalloc.o\
		$(outtmp)/mysql_mysys_my_access.o\
		$(outtmp)/mysql_mysys_my_aes.o\
		$(outtmp)/mysql_mysys_my_alarm.o\
		$(outtmp)/mysql_mysys_my_alloc.o\
		$(outtmp)/mysql_mysys_my_append.o\
		$(outtmp)/mysql_mysys_my_bit.o\
		$(outtmp)/mysql_mysys_my_bitmap.o\
		$(outtmp)/mysql_mysys_my_chmod.o\
		$(outtmp)/mysql_mysys_my_chsize.o\
		$(outtmp)/mysql_mysys_my_clock.o\
		$(outtmp)/mysql_mysys_my_compress.o\
		$(outtmp)/mysql_mysys_my_conio.o\
		$(outtmp)/mysql_mysys_my_copy.o\
		$(outtmp)/mysql_mysys_my_create.o\
		$(outtmp)/mysql_mysys_my_delete.o\
		$(outtmp)/mysql_mysys_my_div.o\
		$(outtmp)/mysql_mysys_my_dup.o\
		$(outtmp)/mysql_mysys_my_error.o\
		$(outtmp)/mysql_mysys_my_file.o\
		$(outtmp)/mysql_mysys_my_fopen.o\
		$(outtmp)/mysql_mysys_my_fstream.o\
		$(outtmp)/mysql_mysys_my_gethostbyname.o\
		$(outtmp)/mysql_mysys_my_gethwaddr.o\
		$(outtmp)/mysql_mysys_my_getncpus.o\
		$(outtmp)/mysql_mysys_my_getopt.o\
		$(outtmp)/mysql_mysys_my_getpagesize.o\
		$(outtmp)/mysql_mysys_my_getsystime.o\
		$(outtmp)/mysql_mysys_my_getwd.o\
		$(outtmp)/mysql_mysys_my_init.o\
		$(outtmp)/mysql_mysys_my_largepage.o\
		$(outtmp)/mysql_mysys_my_lib.o\
		$(outtmp)/mysql_mysys_my_libwrap.o\
		$(outtmp)/mysql_mysys_my_lock.o\
		$(outtmp)/mysql_mysys_my_lockmem.o\
		$(outtmp)/mysql_mysys_my_malloc.o\
		$(outtmp)/mysql_mysys_my_memmem.o\
		$(outtmp)/mysql_mysys_my_messnc.o\
		$(outtmp)/mysql_mysys_my_mkdir.o\
		$(outtmp)/mysql_mysys_my_mmap.o\
		$(outtmp)/mysql_mysys_my_net.o\
		$(outtmp)/mysql_mysys_my_netware.o\
		$(outtmp)/mysql_mysys_my_new.o\
		$(outtmp)/mysql_mysys_my_once.o\
		$(outtmp)/mysql_mysys_my_open.o\
		$(outtmp)/mysql_mysys_my_port.o\
		$(outtmp)/mysql_mysys_my_pread.o\
		$(outtmp)/mysql_mysys_my_pthread.o\
		$(outtmp)/mysql_mysys_my_quick.o\
		$(outtmp)/mysql_mysys_my_read.o\
		$(outtmp)/mysql_mysys_my_realloc.o\
		$(outtmp)/mysql_mysys_my_redel.o\
		$(outtmp)/mysql_mysys_my_rename.o\
		$(outtmp)/mysql_mysys_my_rnd.o\
		$(outtmp)/mysql_mysys_my_safehash.o\
		$(outtmp)/mysql_mysys_my_seek.o\
		$(outtmp)/mysql_mysys_my_sleep.o\
		$(outtmp)/mysql_mysys_my_static.o\
		$(outtmp)/mysql_mysys_my_symlink.o\
		$(outtmp)/mysql_mysys_my_symlink2.o\
		$(outtmp)/mysql_mysys_my_sync.o\
		$(outtmp)/mysql_mysys_my_thr_init.o\
		$(outtmp)/mysql_mysys_my_uuid.o\
		$(outtmp)/mysql_mysys_my_vle.o\
		$(outtmp)/mysql_mysys_my_wincond.o\
		$(outtmp)/mysql_mysys_my_windac.o\
		$(outtmp)/mysql_mysys_my_winerr.o\
		$(outtmp)/mysql_mysys_my_winfile.o\
		$(outtmp)/mysql_mysys_my_winthread.o\
		$(outtmp)/mysql_mysys_my_write.o\
		$(outtmp)/mysql_mysys_ptr_cmp.o\
		$(outtmp)/mysql_mysys_queues.o\
		$(outtmp)/mysql_mysys_rijndael.o\
		$(outtmp)/mysql_mysys_safemalloc.o\
		$(outtmp)/mysql_mysys_sha1.o\
		$(outtmp)/mysql_mysys_stacktrace.o\
		$(outtmp)/mysql_mysys_string.o\
		$(outtmp)/mysql_mysys_thr_alarm.o\
		$(outtmp)/mysql_mysys_thr_lock.o\
		$(outtmp)/mysql_mysys_thr_mutex.o\
		$(outtmp)/mysql_mysys_thr_rwlock.o\
		$(outtmp)/mysql_mysys_tree.o\
		$(outtmp)/mysql_mysys_tie.o\
		$(outtmp)/mysql_mysys_typelib.o\
		$(outtmp)/mysql_mysys_waiting_threads.o\
		$(outtmp)/mysql_mysys_wqueue.o\
		$(outtmp)/mysql_vio_vio.o\
		$(outtmp)/mysql_vio_viosocket.o\
		$(outtmp)/mysql_vio_viossl.o\
		$(outtmp)/mysql_vio_viosslfactories.o\

#no compile：
#   mysql_strings_strappend-sparc
#		mysql_strings_strend-sparc.o
#	  mysql_strings_strinstr-sparc.o
#  	mysql_strings_strmake-sparc.o
#   mysql_strings_bmove-sparc.o
#  	mysql_strings_strmov-sparc.o
#		mysql_strings_strnmov-sparc.o
#  	mysql_strings_str-sparc.o
#   mysql_strings_longlong2str-x86.o
#   mysql_strings_longlong2str_asm.o
#   mysql_strings_my_strtoll10-x86.o
#  	mysql_strings_x86.o
#		mysql_strings_uca-dump.o
#		mysql_strings_uctypedum.o
#		mysql_strings_utr11-dump.o
#		mysql_mysys_make-conf.o
#		mysql_mysys_my_atomic.o
#		mysql_mysys_test_fn.o
#		mysql_mysys_test_xml.o

$(outtmp)/mysql_client.o :$(libmysql)/libmysql/client.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/client.c -o $(outtmp)/mysql_client.o

$(outtmp)/mysql_errmsg.o :$(libmysql)/libmysql/errmsg.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/errmsg.c -o $(outtmp)/mysql_errmsg.o

$(outtmp)/mysql_get_password.o :$(libmysql)/libmysql/get_password.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/get_password.c -o $(outtmp)/mysql_get_password.o

$(outtmp)/mysql_libmysql.o :$(libmysql)/libmysql/libmysql.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/libmysql.c -o $(outtmp)/mysql_libmysql.o

$(outtmp)/mysql_my_time.o :$(libmysql)/libmysql/my_time.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/my_time.c -o $(outtmp)/mysql_my_time.o

$(outtmp)/mysql_net_serv.o :$(libmysql)/libmysql/net_serv.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/net_serv.c -o $(outtmp)/mysql_net_serv.o

$(outtmp)/mysql_pack.o :$(libmysql)/libmysql/pack.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/pack.c -o $(outtmp)/mysql_pack.o

$(outtmp)/mysql_password.o :$(libmysql)/libmysql/password.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/libmysql/password.c -o $(outtmp)/mysql_password.o

$(outtmp)/mysql_strings_bchange.o :$(libmysql)/strings/bchange.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/bchange.c -o $(outtmp)/mysql_strings_bchange.o

$(outtmp)/mysql_strings_bcmp.o :$(libmysql)/strings/bcmp.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/bcmp.c -o $(outtmp)/mysql_strings_bcmp.o

$(outtmp)/mysql_strings_bfill.o :$(libmysql)/strings/bfill.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/bfill.c -o $(outtmp)/mysql_strings_bfill.o

$(outtmp)/mysql_strings_bmove.o :$(libmysql)/strings/bmove.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/bmove.c -o $(outtmp)/mysql_strings_bmove.o

$(outtmp)/mysql_strings_bmove512.o :$(libmysql)/strings/bmove512.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/bmove512.c -o $(outtmp)/mysql_strings_bmove512.o

$(outtmp)/mysql_strings_bmove_upp.o :$(libmysql)/strings/bmove_upp.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/bmove_upp.c -o $(outtmp)/mysql_strings_bmove_upp.o

#$(outtmp)/mysql_strings_bmove-sparc.o :$(libmysql)/strings/conf_to_src.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/conf_to_src.c -o $(outtmp)/mysql_strings_bmove-sparc.o.o

$(outtmp)/mysql_strings_conf_to_src.o :$(libmysql)/strings/conf_to_src.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/conf_to_src.c -o $(outtmp)/mysql_strings_conf_to_src.o

$(outtmp)/mysql_strings_ctype.o :$(libmysql)/strings/ctype.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype.c -o $(outtmp)/mysql_strings_ctype.o

$(outtmp)/mysql_strings_ctype-big5.o :$(libmysql)/strings/ctype-big5.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-big5.c -o $(outtmp)/mysql_strings_ctype-big5.o

$(outtmp)/mysql_strings_ctype-bin.o :$(libmysql)/strings/ctype-bin.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-bin.c -o $(outtmp)/mysql_strings_ctype-bin.o

$(outtmp)/mysql_strings_ctype-cp932.o :$(libmysql)/strings/ctype-cp932.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-cp932.c -o $(outtmp)/mysql_strings_ctype-cp932.o

$(outtmp)/mysql_strings_ctype-czech.o :$(libmysql)/strings/ctype-czech.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-czech.c -o $(outtmp)/mysql_strings_ctype-czech.o

$(outtmp)/mysql_strings_ctype-eucjpms.o :$(libmysql)/strings/ctype-eucjpms.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-eucjpms.c -o $(outtmp)/mysql_strings_ctype-eucjpms.o

$(outtmp)/mysql_strings_ctype-euc_kr.o :$(libmysql)/strings/ctype-euc_kr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-euc_kr.c -o $(outtmp)/mysql_strings_ctype-euc_kr.o

$(outtmp)/mysql_strings_ctype-extra.o :$(libmysql)/strings/ctype-extra.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-extra.c -o $(outtmp)/mysql_strings_ctype-extra.o

$(outtmp)/mysql_strings_ctype-gb2312.o :$(libmysql)/strings/ctype-gb2312.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-gb2312.c -o $(outtmp)/mysql_strings_ctype-gb2312.o

$(outtmp)/mysql_strings_ctype-gbk.o :$(libmysql)/strings/ctype-gbk.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-gbk.c -o $(outtmp)/mysql_strings_ctype-gbk.o

$(outtmp)/mysql_strings_ctype-latin1.o :$(libmysql)/strings/ctype-latin1.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-latin1.c -o $(outtmp)/mysql_strings_ctype-latin1.o

$(outtmp)/mysql_strings_ctype-mb.o :$(libmysql)/strings/ctype-mb.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-mb.c -o $(outtmp)/mysql_strings_ctype-mb.o

$(outtmp)/mysql_strings_ctype-simple.o :$(libmysql)/strings/ctype-simple.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-simple.c -o $(outtmp)/mysql_strings_ctype-simple.o

$(outtmp)/mysql_strings_ctype-sjis.o :$(libmysql)/strings/ctype-sjis.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-sjis.c -o $(outtmp)/mysql_strings_ctype-sjis.o

$(outtmp)/mysql_strings_ctype-tis620.o :$(libmysql)/strings/ctype-tis620.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-tis620.c -o $(outtmp)/mysql_strings_ctype-tis620.o

$(outtmp)/mysql_strings_ctype-uca.o :$(libmysql)/strings/ctype-uca.c
		$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-uca.c -o $(outtmp)/mysql_strings_ctype-uca.o

$(outtmp)/mysql_strings_ctype-ucs2.o :$(libmysql)/strings/ctype-ucs2.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-ucs2.c -o $(outtmp)/mysql_strings_ctype-ucs2.o

$(outtmp)/mysql_strings_ctype-ujis.o :$(libmysql)/strings/ctype-ujis.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-ujis.c -o $(outtmp)/mysql_strings_ctype-ujis.o

$(outtmp)/mysql_strings_ctype-utf8.o :$(libmysql)/strings/ctype-utf8.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-utf8.c -o $(outtmp)/mysql_strings_ctype-utf8.o

$(outtmp)/mysql_strings_ctype-win1250ch.o :$(libmysql)/strings/ctype-win1250ch.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-win1250ch.c -o $(outtmp)/mysql_strings_ctype-win1250ch.o

#$(outtmp)/mysql_strings_ctype-gbk.o :$(libmysql)/strings/ctype-gbk.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/ctype-gbk.c -o $(outtmp)/mysql_strings_ctype-gbk.o

$(outtmp)/mysql_strings_decimal.o :$(libmysql)/strings/decimal.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/decimal.c -o $(outtmp)/mysql_strings_decimal.o

$(outtmp)/mysql_strings_do_ctype.o :$(libmysql)/strings/do_ctype.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/do_ctype.c -o $(outtmp)/mysql_strings_do_ctype.o

$(outtmp)/mysql_strings_dtoa.o :$(libmysql)/strings/dtoa.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/dtoa.c -o $(outtmp)/mysql_strings_dtoa.o

$(outtmp)/mysql_strings_dump_map.o :$(libmysql)/strings/dump_map.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/dump_map.c -o $(outtmp)/mysql_strings_dump_map.o

$(outtmp)/mysql_strings_int2str.o :$(libmysql)/strings/int2str.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/int2str.c -o $(outtmp)/mysql_strings_int2str.o

$(outtmp)/mysql_strings_is_prefix.o :$(libmysql)/strings/is_prefix.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/is_prefix.c -o $(outtmp)/mysql_strings_is_prefix.o

$(outtmp)/mysql_strings_llstr.o :$(libmysql)/strings/llstr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/llstr.c -o $(outtmp)/mysql_strings_llstr.o

$(outtmp)/mysql_strings_longlong2str.o :$(libmysql)/strings/longlong2str.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/longlong2str.c -o $(outtmp)/mysql_strings_longlong2str.o

#$(outtmp)/mysql_strings_longlong2str_asm.o :$(libmysql)/strings/longlong2str_asm.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/longlong2str_asm.c -o $(outtmp)/mysql_strings_longlong2str_asm.o

#$(outtmp)/mysql_strings_longlong2str-x86.o :$(libmysql)/strings/longlong2str-x86.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/longlong2str-x86.s -o $(outtmp)/mysql_strings_longlong2str-x86.o

$(outtmp)/mysql_strings_my_strchr.o :$(libmysql)/strings/my_strchr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/my_strchr.c -o $(outtmp)/mysql_strings_my_strchr.o

$(outtmp)/mysql_strings_my_strtoll10.o :$(libmysql)/strings/my_strtoll10.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/my_strtoll10.c -o $(outtmp)/mysql_strings_my_strtoll10.o

#$(outtmp)/mysql_strings_my_strtoll10-x86.o :$(libmysql)/strings/my_strtoll10-x86.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/my_strtoll10-x86.s -o $(outtmp)/mysql_strings_my_strtoll10-x86.o

$(outtmp)/mysql_strings_my_vsnprintf.o :$(libmysql)/strings/my_vsnprintf.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/my_vsnprintf.c -o $(outtmp)/mysql_strings_my_vsnprintf.o

$(outtmp)/mysql_strings_r_strinstr.o :$(libmysql)/strings/r_strinstr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/r_strinstr.c -o $(outtmp)/mysql_strings_r_strinstr.o

$(outtmp)/mysql_strings_str2int.o :$(libmysql)/strings/str2int.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/str2int.c -o $(outtmp)/mysql_strings_str2int.o

$(outtmp)/mysql_strings_str_alloc.o :$(libmysql)/strings/str_alloc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/str_alloc.c -o $(outtmp)/mysql_strings_str_alloc.o

$(outtmp)/mysql_strings_strappend.o :$(libmysql)/strings/strappend.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strappend.c -o $(outtmp)/mysql_strings_strappend.o

#$(outtmp)/mysql_strings_strappend-sparc.o :$(libmysql)/strings/strappend-sparc.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strappend-sparc.s -o $(outtmp)/mysql_strings_strappend-sparc.o

$(outtmp)/mysql_strings_strcont.o :$(libmysql)/strings/strcont.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strcont.c -o $(outtmp)/mysql_strings_strcont.o

$(outtmp)/mysql_strings_strcend.o :$(libmysql)/strings/strcend.c
		$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strcend.c -o $(outtmp)/mysql_strings_strcend.o

$(outtmp)/mysql_strings_strend.o :$(libmysql)/strings/strend.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strend.c -o $(outtmp)/mysql_strings_strend.o

#$(outtmp)/mysql_strings_strend-sparc.o :$(libmysql)/strings/strend-sparc.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strend-sparc.s -o $(outtmp)/mysql_strings_strend-sparc.o

$(outtmp)/mysql_strings_strfill.o :$(libmysql)/strings/strfill.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strfill.c -o $(outtmp)/mysql_strings_strfill.o

$(outtmp)/mysql_strings-x86.o :$(libmysql)/strings/strings-x86.s
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strings-x86.s -o $(outtmp)/mysql_strings-x86.o

$(outtmp)/mysql_strings_strinstr.o :$(libmysql)/strings/strinstr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strinstr.c -o $(outtmp)/mysql_strings_strinstr.o

#$(outtmp)/mysql_strings_x86.o :$(libmysql)/strings/strings-x86.s
#		$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strings-x86.s -o $(outtmp)/mysql_strings_x86.o

#$(outtmp)/mysql_strings_strinstr-sparc.o :$(libmysql)/strings/strinstr-sparc.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strinstr-sparc.s -o $(outtmp)/mysql_strings_strinstr-sparc.o

$(outtmp)/mysql_strings_strmake.o :$(libmysql)/strings/strmake.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strmake.c -o $(outtmp)/mysql_strings_strmake.o

$(outtmp)/mysql_strings_strmake-sparc.o.o :$(libmysql)/strings/strmake-sparc.s
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strmake-sparc.s -o $(outtmp)/mysql_strings_strmake-sparc.o.o

$(outtmp)/mysql_strings_strmov.o :$(libmysql)/strings/strmov.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strmov.c -o $(outtmp)/mysql_strings_strmov.o

#$(outtmp)/mysql_strings_strmov-sparc.o :$(libmysql)/strings/strmov-sparc.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strmov-sparc.s -o $(outtmp)/mysql_strings_strmov-sparc.o

$(outtmp)/mysql_strings_strnlen.o :$(libmysql)/strings/strnlen.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strnlen.c -o $(outtmp)/mysql_strings_strnlen.o

$(outtmp)/mysql_strings_strnmov.o :$(libmysql)/strings/strnmov.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strnmov.c -o $(outtmp)/mysql_strings_strnmov.o

#$(outtmp)/mysql_strings_strnmov-sparc.o :$(libmysql)/strings/strnmov-sparc.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strnmov-sparc.s -o $(outtmp)/mysql_strings_strnmov-sparc.o

$(outtmp)/mysql_strings_strstr.o :$(libmysql)/strings/strstr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strstr.c -o $(outtmp)/mysql_strings_strstr.o

#$(outtmp)/mysql_strings_str-sparc.o :$(libmysql)/strings/strstr-sparc.s
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strstr-sparc.s -o $(outtmp)/mysql_strings_str-sparc.o

#$(outtmp)/mysql_strings_strto.o :$(libmysql)/strings/strto.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strto.c -o $(outtmp)/mysql_strings_strto.o

$(outtmp)/mysql_strings_strtol.o :$(libmysql)/strings/strtol.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strtol.c -o $(outtmp)/mysql_strings_strtol.o

$(outtmp)/mysql_strings_strtoll.o :$(libmysql)/strings/strtoll.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strtoll.c -o $(outtmp)/mysql_strings_strtoll.o

$(outtmp)/mysql_strings_strtoul.o :$(libmysql)/strings/strtoul.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strtoul.c -o $(outtmp)/mysql_strings_strtoul.o

$(outtmp)/mysql_strings_strtoull.o :$(libmysql)/strings/strtoull.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strtoull.c -o $(outtmp)/mysql_strings_strtoull.o

$(outtmp)/mysql_strings_strxmov.o :$(libmysql)/strings/strxmov.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strxmov.c -o $(outtmp)/mysql_strings_strxmov.o

$(outtmp)/mysql_strings_strxnmov.o :$(libmysql)/strings/strxnmov.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/strxnmov.c -o $(outtmp)/mysql_strings_strxnmov.o

#$(outtmp)/mysql_strings_uca-dump.o :$(libmysql)/strings/uca-dump.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/uca-dump.c -o $(outtmp)/mysql_strings_uca-dump.o

#$(outtmp)/mysql_strings_uctypedum.o :$(libmysql)/strings/uctypedump.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/uctypedump.c -o $(outtmp)/mysql_strings_uctypedum.o

#$(outtmp)/mysql_strings_utr11-dump.o :$(libmysql)/strings/utr11-dump.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/utr11-dump.c -o $(outtmp)/mysql_strings_utr11-dump.o

$(outtmp)/mysql_strings_xml.o :$(libmysql)/strings/xml.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/strings/xml.c -o $(outtmp)/mysql_strings_xml.o

$(outtmp)/mysql_mysys_array.o :$(libmysql)/mysys/array.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/array.c -o $(outtmp)/mysql_mysys_array.o

$(outtmp)/mysql_mysys_base64.o :$(libmysql)/mysys/base64.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/base64.c -o $(outtmp)/mysql_mysys_base64.o

$(outtmp)/mysql_mysys_charset.o :$(libmysql)/mysys/charset.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/charset.c -o $(outtmp)/mysql_mysys_charset.o

$(outtmp)/mysql_mysys_charset-def.o :$(libmysql)/mysys/charset-def.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/charset-def.c -o $(outtmp)/mysql_mysys_charset-def.o

$(outtmp)/mysql_mysys_checksum.o :$(libmysql)/mysys/checksum.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/checksum.c -o $(outtmp)/mysql_mysys_checksum.o

$(outtmp)/mysql_mysys_default.o :$(libmysql)/mysys/default.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/default.c -o $(outtmp)/mysql_mysys_default.o

$(outtmp)/mysql_mysys_default_modify.o :$(libmysql)/mysys/default_modify.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/default_modify.c -o $(outtmp)/mysql_mysys_default_modify.o

$(outtmp)/mysql_mysys_errors.o :$(libmysql)/mysys/errors.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/errors.c -o $(outtmp)/mysql_mysys_errors.o

$(outtmp)/mysql_mysys_hash.o :$(libmysql)/mysys/hash.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/hash.c -o $(outtmp)/mysql_mysys_hash.o

$(outtmp)/mysql_mysys_if_alloc-pin.o :$(libmysql)/mysys/lf_alloc-pin.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/lf_alloc-pin.c -o $(outtmp)/mysql_mysys_if_alloc-pin.o

$(outtmp)/mysql_mysys_if_dynarray.o :$(libmysql)/mysys/lf_dynarray.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/lf_dynarray.c -o $(outtmp)/mysql_mysys_if_dynarray.o

$(outtmp)/mysql_mysys_if_hash.o :$(libmysql)/mysys/lf_hash.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/lf_hash.c -o $(outtmp)/mysql_mysys_if_hash.o

$(outtmp)/mysql_mysys_list.o :$(libmysql)/mysys/list.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/list.c -o $(outtmp)/mysql_mysys_list.o

#$(outtmp)/mysql_mysys_make-conf.o :$(libmysql)/mysys/make-conf.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/make-conf.c -o $(outtmp)/mysql_mysys_make-conf.o

$(outtmp)/mysql_mysys_md5.o :$(libmysql)/mysys/md5.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/md5.c -o $(outtmp)/mysql_mysys_md5.o

$(outtmp)/mysql_mysys_mf_arr_appstr.o :$(libmysql)/mysys/mf_arr_appstr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_arr_appstr.c -o $(outtmp)/mysql_mysys_mf_arr_appstr.o

$(outtmp)/mysql_mysys_mf_brkhant.o :$(libmysql)/mysys/mf_brkhant.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_brkhant.c -o $(outtmp)/mysql_mysys_mf_brkhant.o

$(outtmp)/mysql_mysys_mf_cache.o :$(libmysql)/mysys/mf_cache.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_cache.c -o $(outtmp)/mysql_mysys_mf_cache.o

$(outtmp)/mysql_mysys_mf_dirname.o :$(libmysql)/mysys/mf_dirname.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_dirname.c -o $(outtmp)/mysql_mysys_mf_dirname.o

$(outtmp)/mysql_mysys_mf_fn_ext.o :$(libmysql)/mysys/mf_fn_ext.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_fn_ext.c -o $(outtmp)/mysql_mysys_mf_fn_ext.o

$(outtmp)/mysql_mysys_mf_format.o :$(libmysql)/mysys/mf_format.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_format.c -o $(outtmp)/mysql_mysys_mf_format.o

$(outtmp)/mysql_mysys_mf_getdate.o :$(libmysql)/mysys/mf_getdate.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_getdate.c -o $(outtmp)/mysql_mysys_mf_getdate.o

$(outtmp)/mysql_mysys_mf_iocache.o :$(libmysql)/mysys/mf_iocache.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_iocache.c -o $(outtmp)/mysql_mysys_mf_iocache.o

$(outtmp)/mysql_mysys_mf_iocache2.o :$(libmysql)/mysys/mf_iocache2.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_iocache2.c -o $(outtmp)/mysql_mysys_mf_iocache2.o

$(outtmp)/mysql_mysys_mf_keycache.o :$(libmysql)/mysys/mf_keycache.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_keycache.c -o $(outtmp)/mysql_mysys_mf_keycache.o

$(outtmp)/mysql_mysys_mf_keycaches.o :$(libmysql)/mysys/mf_keycaches.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_keycaches.c -o $(outtmp)/mysql_mysys_mf_keycaches.o

$(outtmp)/mysql_mysys_mf_loadpath.o :$(libmysql)/mysys/mf_loadpath.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_loadpath.c -o $(outtmp)/mysql_mysys_mf_loadpath.o

$(outtmp)/mysql_mysys_mf_pack.o :$(libmysql)/mysys/mf_pack.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_pack.c -o $(outtmp)/mysql_mysys_mf_pack.o

$(outtmp)/mysql_mysys_mf_path.o :$(libmysql)/mysys/mf_path.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_path.c -o $(outtmp)/mysql_mysys_mf_path.o

$(outtmp)/mysql_mysys_mf_qsort.o :$(libmysql)/mysys/mf_qsort.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_qsort.c -o $(outtmp)/mysql_mysys_mf_qsort.o

$(outtmp)/mysql_mysys_mf_qsort2.o :$(libmysql)/mysys/mf_qsort2.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_qsort2.c -o $(outtmp)/mysql_mysys_mf_qsort2.o

$(outtmp)/mysql_mysys_mf_radix.o :$(libmysql)/mysys/mf_radix.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_radix.c -o $(outtmp)/mysql_mysys_mf_radix.o

$(outtmp)/mysql_mysys_mf_same.o :$(libmysql)/mysys/mf_same.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_same.c -o $(outtmp)/mysql_mysys_mf_same.o

$(outtmp)/mysql_mysys_mf_sort.o :$(libmysql)/mysys/mf_sort.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_sort.c -o $(outtmp)/mysql_mysys_mf_sort.o

$(outtmp)/mysql_mysys_mf_soundex.o :$(libmysql)/mysys/mf_soundex.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_soundex.c -o $(outtmp)/mysql_mysys_mf_soundex.o

$(outtmp)/mysql_mysys_mf_strip.o :$(libmysql)/mysys/mf_strip.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_strip.c -o $(outtmp)/mysql_mysys_mf_strip.o

$(outtmp)/mysql_mysys_mf_tempdir.o :$(libmysql)/mysys/mf_tempdir.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_tempdir.c -o $(outtmp)/mysql_mysys_mf_tempdir.o

$(outtmp)/mysql_mysys_mf_tempfile.o :$(libmysql)/mysys/mf_tempfile.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_tempfile.c -o $(outtmp)/mysql_mysys_mf_tempfile.o

$(outtmp)/mysql_mysys_mf_unixpath.o :$(libmysql)/mysys/mf_unixpath.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_unixpath.c -o $(outtmp)/mysql_mysys_mf_unixpath.o

$(outtmp)/mysql_mysys_mf_util.o :$(libmysql)/mysys/mf_util.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_util.c -o $(outtmp)/mysql_mysys_mf_util.o

$(outtmp)/mysql_mysys_mf_wcomp.o :$(libmysql)/mysys/mf_wcomp.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_wcomp.c -o $(outtmp)/mysql_mysys_mf_wcomp.o

$(outtmp)/mysql_mysys_mf_wfile.o :$(libmysql)/mysys/mf_wfile.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mf_wfile.c -o $(outtmp)/mysql_mysys_mf_wfile.o

$(outtmp)/mysql_mysys_mulalloc.o :$(libmysql)/mysys/mulalloc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/mulalloc.c -o $(outtmp)/mysql_mysys_mulalloc.o

$(outtmp)/mysql_mysys_my_access.o :$(libmysql)/mysys/my_access.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_access.c -o $(outtmp)/mysql_mysys_my_access.o

$(outtmp)/mysql_mysys_my_aes.o :$(libmysql)/mysys/my_aes.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_aes.c -o $(outtmp)/mysql_mysys_my_aes.o

$(outtmp)/mysql_mysys_my_alarm.o :$(libmysql)/mysys/my_alarm.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_alarm.c -o $(outtmp)/mysql_mysys_my_alarm.o

$(outtmp)/mysql_mysys_my_alloc.o :$(libmysql)/mysys/my_alloc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_alloc.c -o $(outtmp)/mysql_mysys_my_alloc.o

$(outtmp)/mysql_mysys_my_append.o :$(libmysql)/mysys/my_append.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_append.c -o $(outtmp)/mysql_mysys_my_append.o

#$(outtmp)/mysql_mysys_my_atomic.o :$(libmysql)/mysys/my_atomic.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_atomic.c -o $(outtmp)/mysql_mysys_my_atomic.o

$(outtmp)/mysql_mysys_my_bit.o :$(libmysql)/mysys/my_bit.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_bit.c -o $(outtmp)/mysql_mysys_my_bit.o

$(outtmp)/mysql_mysys_my_bitmap.o :$(libmysql)/mysys/my_bitmap.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_bitmap.c -o $(outtmp)/mysql_mysys_my_bitmap.o

$(outtmp)/mysql_mysys_my_chmod.o :$(libmysql)/mysys/my_chmod.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_chmod.c -o $(outtmp)/mysql_mysys_my_chmod.o

$(outtmp)/mysql_mysys_my_chsize.o :$(libmysql)/mysys/my_chsize.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_chsize.c -o $(outtmp)/mysql_mysys_my_chsize.o

$(outtmp)/mysql_mysys_my_clock.o :$(libmysql)/mysys/my_clock.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_clock.c -o $(outtmp)/mysql_mysys_my_clock.o

$(outtmp)/mysql_mysys_my_compress.o :$(libmysql)/mysys/my_compress.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_compress.c -o $(outtmp)/mysql_mysys_my_compress.o

$(outtmp)/mysql_mysys_my_conio.o :$(libmysql)/mysys/my_conio.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_conio.c -o $(outtmp)/mysql_mysys_my_conio.o

$(outtmp)/mysql_mysys_my_copy.o :$(libmysql)/mysys/my_copy.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_copy.c -o $(outtmp)/mysql_mysys_my_copy.o

$(outtmp)/mysql_mysys_my_create.o :$(libmysql)/mysys/my_create.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_create.c -o $(outtmp)/mysql_mysys_my_create.o

$(outtmp)/mysql_mysys_my_delete.o :$(libmysql)/mysys/my_delete.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_delete.c -o $(outtmp)/mysql_mysys_my_delete.o

$(outtmp)/mysql_mysys_my_div.o :$(libmysql)/mysys/my_div.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_div.c -o $(outtmp)/mysql_mysys_my_div.o

$(outtmp)/mysql_mysys_my_dup.o :$(libmysql)/mysys/my_dup.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_dup.c -o $(outtmp)/mysql_mysys_my_dup.o

$(outtmp)/mysql_mysys_my_error.o :$(libmysql)/mysys/my_error.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_error.c -o $(outtmp)/mysql_mysys_my_error.o

$(outtmp)/mysql_mysys_my_file.o :$(libmysql)/mysys/my_file.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_file.c -o $(outtmp)/mysql_mysys_my_file.o

$(outtmp)/mysql_mysys_my_fopen.o :$(libmysql)/mysys/my_fopen.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_fopen.c -o $(outtmp)/mysql_mysys_my_fopen.o

$(outtmp)/mysql_mysys_my_fstream.o :$(libmysql)/mysys/my_fstream.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_fstream.c -o $(outtmp)/mysql_mysys_my_fstream.o

$(outtmp)/mysql_mysys_my_gethostbyname.o :$(libmysql)/mysys/my_gethostbyname.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_gethostbyname.c -o $(outtmp)/mysql_mysys_my_gethostbyname.o

$(outtmp)/mysql_mysys_my_gethwaddr.o :$(libmysql)/mysys/my_gethwaddr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_gethwaddr.c -o $(outtmp)/mysql_mysys_my_gethwaddr.o

$(outtmp)/mysql_mysys_my_getncpus.o :$(libmysql)/mysys/my_getncpus.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_getncpus.c -o $(outtmp)/mysql_mysys_my_getncpus.o

$(outtmp)/mysql_mysys_my_getopt.o :$(libmysql)/mysys/my_getopt.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_getopt.c -o $(outtmp)/mysql_mysys_my_getopt.o

$(outtmp)/mysql_mysys_my_getpagesize.o :$(libmysql)/mysys/my_getpagesize.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_getpagesize.c -o $(outtmp)/mysql_mysys_my_getpagesize.o

$(outtmp)/mysql_mysys_my_getsystime.o :$(libmysql)/mysys/my_getsystime.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_getsystime.c -o $(outtmp)/mysql_mysys_my_getsystime.o

$(outtmp)/mysql_mysys_my_getwd.o :$(libmysql)/mysys/my_getwd.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_getwd.c -o $(outtmp)/mysql_mysys_my_getwd.o

$(outtmp)/mysql_mysys_my_init.o :$(libmysql)/mysys/my_init.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_init.c -o $(outtmp)/mysql_mysys_my_init.o

$(outtmp)/mysql_mysys_my_largepage.o :$(libmysql)/mysys/my_largepage.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_largepage.c -o $(outtmp)/mysql_mysys_my_largepage.o

$(outtmp)/mysql_mysys_my_lib.o :$(libmysql)/mysys/my_lib.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_lib.c -o $(outtmp)/mysql_mysys_my_lib.o

$(outtmp)/mysql_mysys_my_libwrap.o :$(libmysql)/mysys/my_libwrap.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_libwrap.c -o $(outtmp)/mysql_mysys_my_libwrap.o

$(outtmp)/mysql_mysys_my_lock.o :$(libmysql)/mysys/my_lock.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_lock.c -o $(outtmp)/mysql_mysys_my_lock.o

$(outtmp)/mysql_mysys_my_lockmem.o :$(libmysql)/mysys/my_lockmem.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_lockmem.c -o $(outtmp)/mysql_mysys_my_lockmem.o

$(outtmp)/mysql_mysys_my_malloc.o :$(libmysql)/mysys/my_malloc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_malloc.c -o $(outtmp)/mysql_mysys_my_malloc.o

$(outtmp)/mysql_mysys_my_memmem.o :$(libmysql)/mysys/my_memmem.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_memmem.c -o $(outtmp)/mysql_mysys_my_memmem.o

$(outtmp)/mysql_mysys_my_messnc.o :$(libmysql)/mysys/my_messnc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_messnc.c -o $(outtmp)/mysql_mysys_my_messnc.o

$(outtmp)/mysql_mysys_my_mkdir.o :$(libmysql)/mysys/my_mkdir.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_mkdir.c -o $(outtmp)/mysql_mysys_my_mkdir.o

$(outtmp)/mysql_mysys_my_mmap.o :$(libmysql)/mysys/my_mmap.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_mmap.c -o $(outtmp)/mysql_mysys_my_mmap.o

$(outtmp)/mysql_mysys_my_net.o :$(libmysql)/mysys/my_net.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_net.c -o $(outtmp)/mysql_mysys_my_net.o

$(outtmp)/mysql_mysys_my_netware.o :$(libmysql)/mysys/my_netware.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_netware.c -o $(outtmp)/mysql_mysys_my_netware.o

$(outtmp)/mysql_mysys_my_new.o :$(libmysql)/mysys/my_new.cc
	$(cppcompiler) $(cppflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_new.cc -o $(outtmp)/mysql_mysys_my_new.o

$(outtmp)/mysql_mysys_my_once.o :$(libmysql)/mysys/my_once.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_once.c -o $(outtmp)/mysql_mysys_my_once.o

$(outtmp)/mysql_mysys_my_open.o :$(libmysql)/mysys/my_open.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_open.c -o $(outtmp)/mysql_mysys_my_open.o

$(outtmp)/mysql_mysys_my_port.o :$(libmysql)/mysys/my_port.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_port.c -o $(outtmp)/mysql_mysys_my_port.o

$(outtmp)/mysql_mysys_my_pread.o :$(libmysql)/mysys/my_pread.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_pread.c -o $(outtmp)/mysql_mysys_my_pread.o

$(outtmp)/mysql_mysys_my_pthread.o :$(libmysql)/mysys/my_pthread.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_pthread.c -o $(outtmp)/mysql_mysys_my_pthread.o

$(outtmp)/mysql_mysys_my_quick.o :$(libmysql)/mysys/my_quick.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_quick.c -o $(outtmp)/mysql_mysys_my_quick.o

$(outtmp)/mysql_mysys_my_read.o :$(libmysql)/mysys/my_read.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_read.c -o $(outtmp)/mysql_mysys_my_read.o

$(outtmp)/mysql_mysys_my_realloc.o :$(libmysql)/mysys/my_realloc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_realloc.c -o $(outtmp)/mysql_mysys_my_realloc.o

$(outtmp)/mysql_mysys_my_redel.o :$(libmysql)/mysys/my_redel.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_redel.c -o $(outtmp)/mysql_mysys_my_redel.o

$(outtmp)/mysql_mysys_my_rename.o :$(libmysql)/mysys/my_rename.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_rename.c -o $(outtmp)/mysql_mysys_my_rename.o

$(outtmp)/mysql_mysys_my_rnd.o :$(libmysql)/mysys/my_rnd.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_rnd.c -o $(outtmp)/mysql_mysys_my_rnd.o

$(outtmp)/mysql_mysys_my_safehash.o :$(libmysql)/mysys/my_safehash.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_safehash.c -o $(outtmp)/mysql_mysys_my_safehash.o

$(outtmp)/mysql_mysys_my_seek.o :$(libmysql)/mysys/my_seek.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_seek.c -o $(outtmp)/mysql_mysys_my_seek.o

$(outtmp)/mysql_mysys_my_sleep.o :$(libmysql)/mysys/my_sleep.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_sleep.c -o $(outtmp)/mysql_mysys_my_sleep.o

$(outtmp)/mysql_mysys_my_static.o :$(libmysql)/mysys/my_static.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_static.c -o $(outtmp)/mysql_mysys_my_static.o

$(outtmp)/mysql_mysys_my_symlink.o :$(libmysql)/mysys/my_symlink.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_symlink.c -o $(outtmp)/mysql_mysys_my_symlink.o

$(outtmp)/mysql_mysys_my_symlink2.o :$(libmysql)/mysys/my_symlink2.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_symlink2.c -o $(outtmp)/mysql_mysys_my_symlink2.o

$(outtmp)/mysql_mysys_my_sync.o :$(libmysql)/mysys/my_sync.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_sync.c -o $(outtmp)/mysql_mysys_my_sync.o

$(outtmp)/mysql_mysys_my_thr_init.o :$(libmysql)/mysys/my_thr_init.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_thr_init.c -o $(outtmp)/mysql_mysys_my_thr_init.o

$(outtmp)/mysql_mysys_my_uuid.o :$(libmysql)/mysys/my_uuid.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_uuid.c -o $(outtmp)/mysql_mysys_my_uuid.o

$(outtmp)/mysql_mysys_my_vle.o :$(libmysql)/mysys/my_vle.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_vle.c -o $(outtmp)/mysql_mysys_my_vle.o

$(outtmp)/mysql_mysys_my_wincond.o :$(libmysql)/mysys/my_wincond.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_wincond.c -o $(outtmp)/mysql_mysys_my_wincond.o

$(outtmp)/mysql_mysys_my_windac.o :$(libmysql)/mysys/my_windac.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_windac.c -o $(outtmp)/mysql_mysys_my_windac.o

$(outtmp)/mysql_mysys_my_winerr.o :$(libmysql)/mysys/my_winerr.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_winerr.c -o $(outtmp)/mysql_mysys_my_winerr.o

$(outtmp)/mysql_mysys_my_winfile.o :$(libmysql)/mysys/my_winfile.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_winfile.c -o $(outtmp)/mysql_mysys_my_winfile.o

$(outtmp)/mysql_mysys_my_winthread.o :$(libmysql)/mysys/my_winthread.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_winthread.c -o $(outtmp)/mysql_mysys_my_winthread.o

$(outtmp)/mysql_mysys_my_write.o :$(libmysql)/mysys/my_write.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/my_write.c -o $(outtmp)/mysql_mysys_my_write.o

$(outtmp)/mysql_mysys_ptr_cmp.o :$(libmysql)/mysys/ptr_cmp.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/ptr_cmp.c -o $(outtmp)/mysql_mysys_ptr_cmp.o

$(outtmp)/mysql_mysys_queues.o :$(libmysql)/mysys/queues.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/queues.c -o $(outtmp)/mysql_mysys_queues.o

$(outtmp)/mysql_mysys_rijndael.o :$(libmysql)/mysys/rijndael.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/rijndael.c -o $(outtmp)/mysql_mysys_rijndael.o

$(outtmp)/mysql_mysys_safemalloc.o :$(libmysql)/mysys/safemalloc.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/safemalloc.c -o $(outtmp)/mysql_mysys_safemalloc.o

$(outtmp)/mysql_mysys_sha1.o :$(libmysql)/mysys/sha1.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/sha1.c -o $(outtmp)/mysql_mysys_sha1.o

$(outtmp)/mysql_mysys_stacktrace.o :$(libmysql)/mysys/stacktrace.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/stacktrace.c -o $(outtmp)/mysql_mysys_stacktrace.o

$(outtmp)/mysql_mysys_string.o :$(libmysql)/mysys/string.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/string.c -o $(outtmp)/mysql_mysys_string.o

#$(outtmp)/mysql_mysys_test_fn.o :$(libmysql)/mysys/test_fn.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/test_fn.c -o $(outtmp)/mysql_mysys_test_fn.o

#$(outtmp)/mysql_mysys_test_xml.o :$(libmysql)/mysys/test_xml.c
#	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/test_xml.c -o $(outtmp)/mysql_mysys_test_xml.o

$(outtmp)/mysql_mysys_thr_alarm.o :$(libmysql)/mysys/thr_alarm.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/thr_alarm.c -o $(outtmp)/mysql_mysys_thr_alarm.o

$(outtmp)/mysql_mysys_thr_lock.o :$(libmysql)/mysys/thr_lock.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/thr_lock.c -o $(outtmp)/mysql_mysys_thr_lock.o

$(outtmp)/mysql_mysys_thr_mutex.o :$(libmysql)/mysys/thr_mutex.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/thr_mutex.c -o $(outtmp)/mysql_mysys_thr_mutex.o

$(outtmp)/mysql_mysys_thr_rwlock.o :$(libmysql)/mysys/thr_rwlock.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/thr_rwlock.c -o $(outtmp)/mysql_mysys_thr_rwlock.o

$(outtmp)/mysql_mysys_tree.o :$(libmysql)/mysys/tree.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/tree.c -o $(outtmp)/mysql_mysys_tree.o

$(outtmp)/mysql_mysys_tie.o :$(libmysql)/mysys/trie.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/trie.c -o $(outtmp)/mysql_mysys_tie.o

$(outtmp)/mysql_mysys_typelib.o :$(libmysql)/mysys/typelib.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/typelib.c -o $(outtmp)/mysql_mysys_typelib.o

$(outtmp)/mysql_mysys_waiting_threads.o :$(libmysql)/mysys/waiting_threads.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/waiting_threads.c -o $(outtmp)/mysql_mysys_waiting_threads.o

$(outtmp)/mysql_mysys_wqueue.o :$(libmysql)/mysys/wqueue.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/mysys/wqueue.c -o $(outtmp)/mysql_mysys_wqueue.o

$(outtmp)/mysql_vio_vio.o :$(libmysql)/vio/vio.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/vio/vio.c -o $(outtmp)/mysql_vio_vio.o

$(outtmp)/mysql_vio_viosocket.o :$(libmysql)/vio/viosocket.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/vio/viosocket.c -o $(outtmp)/mysql_vio_viosocket.o

$(outtmp)/mysql_vio_viossl.o :$(libmysql)/vio/viossl.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/vio/viossl.c -o $(outtmp)/mysql_vio_viossl.o

$(outtmp)/mysql_vio_viosslfactories.o :$(libmysql)/vio/viosslfactories.c
	$(ccompiler) $(cflags) $(mysql_build_flag) $(mysql_include) -c $(libmysql)/vio/viosslfactories.c -o $(outtmp)/mysql_vio_viosslfactories.o