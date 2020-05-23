#! /usr/bin/env perl

package configdata;

use strict;
use warnings;

use Exporter;
#use vars qw(@ISA @EXPORT);
our @ISA = qw(Exporter);
our @EXPORT = qw(%config %target %disabled %withargs %unified_info @disablables);

our %config = (
  AR => "ar",
  ARFLAGS => [ "r" ],
  CC => "gcc",
  CFLAGS => [ "-Wall -O3" ],
  CPPDEFINES => [  ],
  CPPFLAGS => [  ],
  CPPINCLUDES => [  ],
  CXX => "g++",
  CXXFLAGS => [ "-Wall -O3" ],
  HASHBANGPERL => "/usr/bin/env perl",
  LDFLAGS => [  ],
  LDLIBS => [  ],
  PERL => "/usr/bin/perl",
  RANLIB => "ranlib",
  RC => "windres",
  afalgeng => "",
  b32 => "0",
  b64 => "0",
  b64l => "1",
  bn_ll => "0",
  build_file => "Makefile",
  build_file_templates => [ "Configurations/common0.tmpl", "Configurations/unix-Makefile.tmpl", "Configurations/common.tmpl" ],
  build_infos => [ "./build.info", "crypto/build.info", "ssl/build.info", "apps/build.info", "test/build.info", "util/build.info", "tools/build.info", "fuzz/build.info", "engines/build.info", "providers/build.info", "crypto/objects/build.info", "crypto/buffer/build.info", "crypto/bio/build.info", "crypto/stack/build.info", "crypto/lhash/build.info", "crypto/rand/build.info", "crypto/evp/build.info", "crypto/asn1/build.info", "crypto/pem/build.info", "crypto/x509/build.info", "crypto/x509v3/build.info", "crypto/conf/build.info", "crypto/txt_db/build.info", "crypto/pkcs7/build.info", "crypto/pkcs12/build.info", "crypto/ui/build.info", "crypto/kdf/build.info", "crypto/store/build.info", "crypto/property/build.info", "crypto/md4/build.info", "crypto/md5/build.info", "crypto/sha/build.info", "crypto/mdc2/build.info", "crypto/gmac/build.info", "crypto/hmac/build.info", "crypto/ripemd/build.info", "crypto/whrlpool/build.info", "crypto/poly1305/build.info", "crypto/blake2/build.info", "crypto/siphash/build.info", "crypto/sm3/build.info", "crypto/des/build.info", "crypto/aes/build.info", "crypto/rc2/build.info", "crypto/rc4/build.info", "crypto/idea/build.info", "crypto/aria/build.info", "crypto/bf/build.info", "crypto/cast/build.info", "crypto/camellia/build.info", "crypto/seed/build.info", "crypto/sm4/build.info", "crypto/chacha/build.info", "crypto/modes/build.info", "crypto/bn/build.info", "crypto/ec/build.info", "crypto/rsa/build.info", "crypto/dsa/build.info", "crypto/dh/build.info", "crypto/sm2/build.info", "crypto/dso/build.info", "crypto/engine/build.info", "crypto/err/build.info", "crypto/comp/build.info", "crypto/ocsp/build.info", "crypto/cms/build.info", "crypto/ts/build.info", "crypto/srp/build.info", "crypto/cmac/build.info", "crypto/ct/build.info", "crypto/async/build.info", "crypto/kmac/build.info", "crypto/ess/build.info", "crypto/crmf/build.info", "test/ossl_shim/build.info", "providers/common/build.info", "providers/default/build.info", "providers/fips/build.info", "providers/common/digests/build.info" ],
  build_metadata => "",
  build_type => "release",
  builddir => ".",
  cflags => [ "-Wa,--noexecstack" ],
  conf_files => [ "Configurations/00-base-templates.conf", "Configurations/10-main.conf", "Configurations/shared-info.pl" ],
  cppflags => [  ],
  cxxflags => [  ],
  defines => [ "NDEBUG" ],
  dso_defines => [ "PADLOCK_ASM" ],
  dynamic_engines => "1",
  engdirs => [ "afalg" ],
  ex_libs => [  ],
  export_var_as_fn => "0",
  full_version => "3.0.0-dev",
  includes => [  ],
  lflags => [  ],
  lib_defines => [ "OPENSSL_PIC", "OPENSSL_CPUID_OBJ", "OPENSSL_IA32_SSE2", "OPENSSL_BN_ASM_MONT", "OPENSSL_BN_ASM_MONT5", "OPENSSL_BN_ASM_GF2m", "SHA1_ASM", "SHA256_ASM", "SHA512_ASM", "KECCAK1600_ASM", "RC4_ASM", "MD5_ASM", "AES_ASM", "VPAES_ASM", "BSAES_ASM", "GHASH_ASM", "ECP_NISTZ256_ASM", "X25519_ASM", "POLY1305_ASM" ],
  libdir => "",
  major => "3",
  makedepprog => "\$(CROSS_COMPILE)gcc",
  minor => "0",
  openssl_api_defines => [ "OPENSSL_MIN_API=-1" ],
  openssl_feature_defines => [ "OPENSSL_RAND_SEED_OS", "OPENSSL_NO_ASAN", "OPENSSL_NO_CRYPTO_MDEBUG", "OPENSSL_NO_CRYPTO_MDEBUG_BACKTRACE", "OPENSSL_NO_DEVCRYPTOENG", "OPENSSL_NO_EC_NISTP_64_GCC_128", "OPENSSL_NO_EGD", "OPENSSL_NO_EXTERNAL_TESTS", "OPENSSL_NO_FUZZ_AFL", "OPENSSL_NO_FUZZ_LIBFUZZER", "OPENSSL_NO_KTLS", "OPENSSL_NO_MD2", "OPENSSL_NO_MSAN", "OPENSSL_NO_RC5", "OPENSSL_NO_SCTP", "OPENSSL_NO_SSL_TRACE", "OPENSSL_NO_SSL3", "OPENSSL_NO_SSL3_METHOD", "OPENSSL_NO_TRACE", "OPENSSL_NO_UBSAN", "OPENSSL_NO_UNIT_TEST", "OPENSSL_NO_WEAK_SSL_CIPHERS", "OPENSSL_THREADS", "OPENSSL_NO_STATIC_ENGINE" ],
  openssl_other_defines => [ "OPENSSL_NO_KTLS" ],
  openssl_sys_defines => [  ],
  openssldir => "",
  options => " no-asan no-buildtest-c++ no-crypto-mdebug no-crypto-mdebug-backtrace no-devcryptoeng no-ec_nistp_64_gcc_128 no-egd no-external-tests no-fuzz-afl no-fuzz-libfuzzer no-ktls no-md2 no-msan no-rc5 no-sctp no-ssl-trace no-ssl3 no-ssl3-method no-trace no-ubsan no-unit-test no-weak-ssl-ciphers no-zlib no-zlib-dynamic",
  patch => "0",
  perl_archname => "x86_64-linux-gnu-thread-multi",
  perl_cmd => "/usr/bin/perl",
  perl_version => "5.26.1",
  perlargv => [ "linux-x86_64" ],
  perlenv => {
      "AR" => undef,
      "ARFLAGS" => undef,
      "AS" => undef,
      "ASFLAGS" => undef,
      "BUILDFILE" => undef,
      "CC" => undef,
      "CFLAGS" => undef,
      "CPP" => undef,
      "CPPDEFINES" => undef,
      "CPPFLAGS" => undef,
      "CPPINCLUDES" => undef,
      "CROSS_COMPILE" => undef,
      "CXX" => undef,
      "CXXFLAGS" => undef,
      "HASHBANGPERL" => undef,
      "LD" => undef,
      "LDFLAGS" => undef,
      "LDLIBS" => undef,
      "MT" => undef,
      "MTFLAGS" => undef,
      "OPENSSL_LOCAL_CONFIG_DIR" => undef,
      "PERL" => undef,
      "RANLIB" => undef,
      "RC" => undef,
      "RCFLAGS" => undef,
      "RM" => undef,
      "WINDRES" => undef,
      "__CNF_CFLAGS" => "",
      "__CNF_CPPDEFINES" => "",
      "__CNF_CPPFLAGS" => "",
      "__CNF_CPPINCLUDES" => "",
      "__CNF_CXXFLAGS" => "",
      "__CNF_LDFLAGS" => "",
      "__CNF_LDLIBS" => "",
  },
  prefix => "",
  prerelease => "-dev",
  processor => "",
  rc4_int => "unsigned int",
  shlib_version => "3",
  sourcedir => ".",
  target => "linux-x86_64",
  version => "3.0.0",
);

our %target = (
  AR => "ar",
  ARFLAGS => "r",
  CC => "gcc",
  CFLAGS => "-Wall -O3",
  CXX => "g++",
  CXXFLAGS => "-Wall -O3",
  HASHBANGPERL => "/usr/bin/env perl",
  RANLIB => "ranlib",
  RC => "windres",
  _conf_fname_int => [ "Configurations/00-base-templates.conf", "Configurations/00-base-templates.conf", "Configurations/10-main.conf", "Configurations/10-main.conf", "Configurations/00-base-templates.conf", "Configurations/10-main.conf", "Configurations/shared-info.pl" ],
  aes_asm_src => "aes-x86_64.s vpaes-x86_64.s bsaes-x86_64.s aesni-x86_64.s aesni-sha1-x86_64.s aesni-sha256-x86_64.s aesni-mb-x86_64.s",
  aes_obj => "aes-x86_64.o vpaes-x86_64.o bsaes-x86_64.o aesni-x86_64.o aesni-sha1-x86_64.o aesni-sha256-x86_64.o aesni-mb-x86_64.o",
  apps_aux_src => "",
  apps_init_src => "",
  apps_obj => "",
  bf_asm_src => "bf_enc.c",
  bf_obj => "bf_enc.o",
  bn_asm_src => "asm/x86_64-gcc.c x86_64-mont.s x86_64-mont5.s x86_64-gf2m.s rsaz_exp.c rsaz-x86_64.s rsaz-avx2.s",
  bn_obj => "asm/x86_64-gcc.o x86_64-mont.o x86_64-mont5.o x86_64-gf2m.o rsaz_exp.o rsaz-x86_64.o rsaz-avx2.o",
  bn_ops => "SIXTY_FOUR_BIT_LONG",
  build_file => "Makefile",
  build_scheme => [ "unified", "unix" ],
  cast_asm_src => "c_enc.c",
  cast_obj => "c_enc.o",
  cflags => "-pthread -m64",
  chacha_asm_src => "chacha-x86_64.s",
  chacha_obj => "chacha-x86_64.o",
  cmll_asm_src => "cmll-x86_64.s cmll_misc.c",
  cmll_obj => "cmll-x86_64.o cmll_misc.o",
  cppflags => "",
  cpuid_asm_src => "x86_64cpuid.s",
  cpuid_obj => "x86_64cpuid.o",
  cxxflags => "-std=c++11 -pthread -m64",
  defines => [  ],
  des_asm_src => "des_enc.c fcrypt_b.c",
  des_obj => "des_enc.o fcrypt_b.o",
  disable => [  ],
  dso_ldflags => "-z defs",
  dso_scheme => "dlfcn",
  ec_asm_src => "ecp_nistz256.c ecp_nistz256-x86_64.s x25519-x86_64.s",
  ec_obj => "ecp_nistz256.o ecp_nistz256-x86_64.o x25519-x86_64.o",
  enable => [ "afalgeng" ],
  ex_libs => "-ldl -pthread",
  includes => [  ],
  keccak1600_asm_src => "keccak1600-x86_64.s",
  keccak1600_obj => "keccak1600-x86_64.o",
  lflags => "",
  lib_cflags => "",
  lib_cppflags => "-DOPENSSL_USE_NODELETE -DL_ENDIAN",
  lib_defines => [  ],
  md5_asm_src => "md5-x86_64.s",
  md5_obj => "md5-x86_64.o",
  modes_asm_src => "ghash-x86_64.s aesni-gcm-x86_64.s",
  modes_obj => "ghash-x86_64.o aesni-gcm-x86_64.o",
  module_cflags => "-fPIC",
  module_cxxflags => "",
  module_ldflags => "-Wl,-znodelete -shared -Wl,-Bsymbolic",
  multilib => "64",
  padlock_asm_src => "e_padlock-x86_64.s",
  padlock_obj => "e_padlock-x86_64.o",
  perl_platform => "Unix",
  perlasm_scheme => "elf",
  poly1305_asm_src => "poly1305-x86_64.s",
  poly1305_obj => "poly1305-x86_64.o",
  rc4_asm_src => "rc4-x86_64.s rc4-md5-x86_64.s",
  rc4_obj => "rc4-x86_64.o rc4-md5-x86_64.o",
  rc5_asm_src => "rc5_enc.c",
  rc5_obj => "rc5_enc.o",
  rmd160_asm_src => "",
  rmd160_obj => "",
  sha1_asm_src => "sha1-x86_64.s sha256-x86_64.s sha512-x86_64.s sha1-mb-x86_64.s sha256-mb-x86_64.s",
  sha1_obj => "sha1-x86_64.o sha256-x86_64.o sha512-x86_64.o sha1-mb-x86_64.o sha256-mb-x86_64.o",
  shared_cflag => "-fPIC",
  shared_defflag => "-Wl,--version-script=",
  shared_defines => [  ],
  shared_ldflag => "-Wl,-znodelete -shared -Wl,-Bsymbolic",
  shared_rcflag => "",
  shared_sonameflag => "-Wl,-soname=",
  shared_target => "linux-shared",
  template => "1",
  thread_defines => [  ],
  thread_scheme => "pthreads",
  unistd => "<unistd.h>",
  uplink_aux_src => "",
  uplink_obj => "",
  wp_asm_src => "wp-x86_64.s",
  wp_obj => "wp-x86_64.o",
);

our %available_protocols = (
  tls => [ "ssl3", "tls1", "tls1_1", "tls1_2", "tls1_3" ],
  dtls => [ "dtls1", "dtls1_2" ],
);

our @disablables = (
  "ktls",
  "afalgeng",
  "aria",
  "asan",
  "asm",
  "async",
  "autoalginit",
  "autoerrinit",
  "autoload-config",
  "bf",
  "blake2",
  "buildtest-c++",
  "camellia",
  "capieng",
  "cast",
  "chacha",
  "cmac",
  "cms",
  "comp",
  "crmf",
  "crypto-mdebug",
  "crypto-mdebug-backtrace",
  "ct",
  "deprecated",
  "des",
  "devcryptoeng",
  "dgram",
  "dh",
  "dsa",
  "dtls",
  "dynamic-engine",
  "ec",
  "ec2m",
  "ecdh",
  "ecdsa",
  "ec_nistp_64_gcc_128",
  "egd",
  "engine",
  "err",
  "external-tests",
  "filenames",
  "fips",
  "fuzz-libfuzzer",
  "fuzz-afl",
  "gost",
  "idea",
  "makedepend",
  "md2",
  "md4",
  "mdc2",
  "module",
  "msan",
  "multiblock",
  "nextprotoneg",
  "pinshared",
  "ocb",
  "ocsp",
  "padlockeng",
  "pic",
  "poly1305",
  "posix-io",
  "psk",
  "rc2",
  "rc4",
  "rc5",
  "rdrand",
  "rfc3779",
  "rmd160",
  "scrypt",
  "sctp",
  "seed",
  "shared",
  "siphash",
  "siv",
  "sm2",
  "sm3",
  "sm4",
  "sock",
  "srp",
  "srtp",
  "sse2",
  "ssl",
  "ssl-trace",
  "static-engine",
  "stdio",
  "tests",
  "threads",
  "tls",
  "trace",
  "ts",
  "ubsan",
  "ui-console",
  "unit-test",
  "whirlpool",
  "weak-ssl-ciphers",
  "zlib",
  "zlib-dynamic",
  "ssl3",
  "ssl3-method",
  "tls1",
  "tls1-method",
  "tls1_1",
  "tls1_1-method",
  "tls1_2",
  "tls1_2-method",
  "tls1_3",
  "dtls1",
  "dtls1-method",
  "dtls1_2",
  "dtls1_2-method",
);

our %disabled = (
  "asan" => "default",
  "buildtest-c++" => "default",
  "crypto-mdebug" => "default",
  "crypto-mdebug-backtrace" => "default",
  "devcryptoeng" => "default",
  "ec_nistp_64_gcc_128" => "default",
  "egd" => "default",
  "external-tests" => "default",
  "fuzz-afl" => "default",
  "fuzz-libfuzzer" => "default",
  "ktls" => "default",
  "md2" => "default",
  "msan" => "default",
  "rc5" => "default",
  "sctp" => "default",
  "ssl-trace" => "default",
  "ssl3" => "default",
  "ssl3-method" => "default",
  "trace" => "default",
  "ubsan" => "default",
  "unit-test" => "default",
  "weak-ssl-ciphers" => "default",
  "zlib" => "default",
  "zlib-dynamic" => "default",
);

our %withargs = (
);

our %unified_info = (
    "attributes" =>
        {
            "apps/CA.pl" =>
                {
                    "misc" => "1",
                },
            "apps/libapps.a" =>
                {
                    "noinst" => "1",
                },
            "apps/tsget.pl" =>
                {
                    "linkname" => "tsget",
                    "misc" => "1",
                },
            "engines/afalg" =>
                {
                    "engine" => "1",
                },
            "engines/capi" =>
                {
                    "engine" => "1",
                },
            "engines/dasync" =>
                {
                    "engine" => "1",
                    "noinst" => "1",
                },
            "engines/ossltest" =>
                {
                    "engine" => "1",
                    "noinst" => "1",
                },
            "engines/padlock" =>
                {
                    "engine" => "1",
                },
            "fuzz/asn1-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/asn1parse-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/bignum-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/bndiv-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/client-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/cms-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/conf-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/crl-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/ct-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/server-test" =>
                {
                    "noinst" => "1",
                },
            "fuzz/x509-test" =>
                {
                    "noinst" => "1",
                },
            "test/aborttest" =>
                {
                    "noinst" => "1",
                },
            "test/aesgcmtest" =>
                {
                    "noinst" => "1",
                },
            "test/afalgtest" =>
                {
                    "noinst" => "1",
                },
            "test/asn1_decode_test" =>
                {
                    "noinst" => "1",
                },
            "test/asn1_encode_test" =>
                {
                    "noinst" => "1",
                },
            "test/asn1_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/asn1_string_table_test" =>
                {
                    "noinst" => "1",
                },
            "test/asn1_time_test" =>
                {
                    "noinst" => "1",
                },
            "test/asynciotest" =>
                {
                    "noinst" => "1",
                },
            "test/asynctest" =>
                {
                    "noinst" => "1",
                },
            "test/bad_dtls_test" =>
                {
                    "noinst" => "1",
                },
            "test/bftest" =>
                {
                    "noinst" => "1",
                },
            "test/bio_callback_test" =>
                {
                    "noinst" => "1",
                },
            "test/bio_enc_test" =>
                {
                    "noinst" => "1",
                },
            "test/bio_memleak_test" =>
                {
                    "noinst" => "1",
                },
            "test/bioprinttest" =>
                {
                    "noinst" => "1",
                },
            "test/bn_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/bntest" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_aes" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_asn1" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_asn1t" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_async" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_bio" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_blowfish" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_bn" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_buffer" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_camellia" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_cast" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_cmac" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_cms" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_comp" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_conf" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_conf_api" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_core" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_core_names" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_core_numbers" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_crmf" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_crypto" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ct" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_des" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_dh" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_dsa" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_dtls1" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_e_os2" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ebcdic" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ec" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ecdh" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ecdsa" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_engine" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ess" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_evp" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_hmac" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_idea" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_kdf" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_lhash" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_md4" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_md5" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_mdc2" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_modes" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_obj_mac" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_objects" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ocsp" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_opensslv" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ossl_typ" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_params" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_pem" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_pem2" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_pkcs12" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_pkcs7" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_provider" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_rand" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_rand_drbg" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_rc2" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_rc4" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ripemd" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_rsa" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_safestack" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_seed" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_sha" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_srp" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_srtp" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ssl" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ssl2" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_stack" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_store" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_symhacks" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_tls1" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ts" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_txt_db" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_ui" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_whrlpool" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_x509" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_x509_vfy" =>
                {
                    "noinst" => "1",
                },
            "test/buildtest_c_x509v3" =>
                {
                    "noinst" => "1",
                },
            "test/casttest" =>
                {
                    "noinst" => "1",
                },
            "test/chacha_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/cipherbytes_test" =>
                {
                    "noinst" => "1",
                },
            "test/cipherlist_test" =>
                {
                    "noinst" => "1",
                },
            "test/ciphername_test" =>
                {
                    "noinst" => "1",
                },
            "test/clienthellotest" =>
                {
                    "noinst" => "1",
                },
            "test/cmsapitest" =>
                {
                    "noinst" => "1",
                },
            "test/conf_include_test" =>
                {
                    "noinst" => "1",
                },
            "test/constant_time_test" =>
                {
                    "noinst" => "1",
                },
            "test/context_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/crltest" =>
                {
                    "noinst" => "1",
                },
            "test/ct_test" =>
                {
                    "noinst" => "1",
                },
            "test/ctype_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/curve448_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/d2i_test" =>
                {
                    "noinst" => "1",
                },
            "test/danetest" =>
                {
                    "noinst" => "1",
                },
            "test/destest" =>
                {
                    "noinst" => "1",
                },
            "test/dhtest" =>
                {
                    "noinst" => "1",
                },
            "test/drbg_cavs_test" =>
                {
                    "noinst" => "1",
                },
            "test/drbgtest" =>
                {
                    "noinst" => "1",
                },
            "test/dsa_no_digest_size_test" =>
                {
                    "noinst" => "1",
                },
            "test/dsatest" =>
                {
                    "noinst" => "1",
                },
            "test/dtls_mtu_test" =>
                {
                    "noinst" => "1",
                },
            "test/dtlstest" =>
                {
                    "noinst" => "1",
                },
            "test/dtlsv1listentest" =>
                {
                    "noinst" => "1",
                },
            "test/ec_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/ecdsatest" =>
                {
                    "noinst" => "1",
                },
            "test/ecstresstest" =>
                {
                    "noinst" => "1",
                },
            "test/ectest" =>
                {
                    "noinst" => "1",
                },
            "test/enginetest" =>
                {
                    "noinst" => "1",
                },
            "test/errtest" =>
                {
                    "noinst" => "1",
                },
            "test/evp_extra_test" =>
                {
                    "noinst" => "1",
                },
            "test/evp_kdf_test" =>
                {
                    "noinst" => "1",
                },
            "test/evp_test" =>
                {
                    "noinst" => "1",
                },
            "test/exdatatest" =>
                {
                    "noinst" => "1",
                },
            "test/exptest" =>
                {
                    "noinst" => "1",
                },
            "test/fatalerrtest" =>
                {
                    "noinst" => "1",
                },
            "test/gmdifftest" =>
                {
                    "noinst" => "1",
                },
            "test/gosttest" =>
                {
                    "noinst" => "1",
                },
            "test/hmactest" =>
                {
                    "noinst" => "1",
                },
            "test/ideatest" =>
                {
                    "noinst" => "1",
                },
            "test/igetest" =>
                {
                    "noinst" => "1",
                },
            "test/lhash_test" =>
                {
                    "noinst" => "1",
                },
            "test/libtestutil.a" =>
                {
                    "has_main" => "1",
                    "noinst" => "1",
                },
            "test/md2test" =>
                {
                    "noinst" => "1",
                },
            "test/mdc2_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/mdc2test" =>
                {
                    "noinst" => "1",
                },
            "test/memleaktest" =>
                {
                    "noinst" => "1",
                },
            "test/modes_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/ocspapitest" =>
                {
                    "noinst" => "1",
                },
            "test/p_test" =>
                {
                    "noinst" => "1",
                },
            "test/packettest" =>
                {
                    "noinst" => "1",
                },
            "test/params_api_test" =>
                {
                    "noinst" => "1",
                },
            "test/params_test" =>
                {
                    "noinst" => "1",
                },
            "test/pbelutest" =>
                {
                    "noinst" => "1",
                },
            "test/pemtest" =>
                {
                    "noinst" => "1",
                },
            "test/pkey_meth_kdf_test" =>
                {
                    "noinst" => "1",
                },
            "test/pkey_meth_test" =>
                {
                    "noinst" => "1",
                },
            "test/poly1305_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/property_test" =>
                {
                    "noinst" => "1",
                },
            "test/provider_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/provider_test" =>
                {
                    "noinst" => "1",
                },
            "test/rc2test" =>
                {
                    "noinst" => "1",
                },
            "test/rc4test" =>
                {
                    "noinst" => "1",
                },
            "test/rc5test" =>
                {
                    "noinst" => "1",
                },
            "test/rdrand_sanitytest" =>
                {
                    "noinst" => "1",
                },
            "test/recordlentest" =>
                {
                    "noinst" => "1",
                },
            "test/rsa_complex" =>
                {
                    "noinst" => "1",
                },
            "test/rsa_mp_test" =>
                {
                    "noinst" => "1",
                },
            "test/rsa_sp800_56b_test" =>
                {
                    "noinst" => "1",
                },
            "test/rsa_test" =>
                {
                    "noinst" => "1",
                },
            "test/sanitytest" =>
                {
                    "noinst" => "1",
                },
            "test/secmemtest" =>
                {
                    "noinst" => "1",
                },
            "test/servername_test" =>
                {
                    "noinst" => "1",
                },
            "test/shlibloadtest" =>
                {
                    "noinst" => "1",
                },
            "test/siphash_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/sm2_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/sm4_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/sparse_array_test" =>
                {
                    "noinst" => "1",
                },
            "test/srptest" =>
                {
                    "noinst" => "1",
                },
            "test/ssl_cert_table_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/ssl_test" =>
                {
                    "noinst" => "1",
                },
            "test/ssl_test_ctx_test" =>
                {
                    "noinst" => "1",
                },
            "test/sslapitest" =>
                {
                    "noinst" => "1",
                },
            "test/sslbuffertest" =>
                {
                    "noinst" => "1",
                },
            "test/sslcorrupttest" =>
                {
                    "noinst" => "1",
                },
            "test/ssltest_old" =>
                {
                    "noinst" => "1",
                },
            "test/stack_test" =>
                {
                    "noinst" => "1",
                },
            "test/sysdefaulttest" =>
                {
                    "noinst" => "1",
                },
            "test/test_test" =>
                {
                    "noinst" => "1",
                },
            "test/threadstest" =>
                {
                    "noinst" => "1",
                },
            "test/time_offset_test" =>
                {
                    "noinst" => "1",
                },
            "test/tls13ccstest" =>
                {
                    "noinst" => "1",
                },
            "test/tls13encryptiontest" =>
                {
                    "noinst" => "1",
                },
            "test/tls13secretstest" =>
                {
                    "noinst" => "1",
                },
            "test/uitest" =>
                {
                    "noinst" => "1",
                },
            "test/v3ext" =>
                {
                    "noinst" => "1",
                },
            "test/v3nametest" =>
                {
                    "noinst" => "1",
                },
            "test/verify_extra_test" =>
                {
                    "noinst" => "1",
                },
            "test/versions" =>
                {
                    "noinst" => "1",
                },
            "test/wpackettest" =>
                {
                    "noinst" => "1",
                },
            "test/x509_check_cert_pkey_test" =>
                {
                    "noinst" => "1",
                },
            "test/x509_dup_cert_test" =>
                {
                    "noinst" => "1",
                },
            "test/x509_internal_test" =>
                {
                    "noinst" => "1",
                },
            "test/x509_time_test" =>
                {
                    "noinst" => "1",
                },
            "test/x509aux" =>
                {
                    "noinst" => "1",
                },
            "util/shlib_wrap.sh" =>
                {
                    "noinst" => "1",
                },
        },
    "defines" =>
        {
            "providers/fips" =>
                [
                    "FIPS_MODE",
                ],
            "test/provider_internal_test" =>
                [
                    "PROVIDER_INIT_FUNCTION_NAME=p_test_init",
                ],
            "test/provider_test" =>
                [
                    "PROVIDER_INIT_FUNCTION_NAME=p_test_init",
                ],
        },
    "depends" =>
        {
            "" =>
                [
                    "crypto/include/internal/bn_conf.h",
                    "crypto/include/internal/dso_conf.h",
                    "doc/man7/openssl_user_macros.pod",
                    "include/openssl/opensslconf.h",
                    "test/provider_internal_test.conf",
                ],
            "apps/openssl" =>
                [
                    "apps/libapps.a",
                    "libssl",
                ],
            "apps/openssl-bin-asn1pars.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-ca.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-ciphers.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-cms.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-crl.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-crl2p7.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-dgst.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-dhparam.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-dsa.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-dsaparam.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-ec.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-ecparam.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-enc.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-engine.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-errstr.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-gendsa.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-genpkey.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-genrsa.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-mac.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-nseq.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-ocsp.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-openssl.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-passwd.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-pkcs12.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-pkcs7.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-pkcs8.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-pkey.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-pkeyparam.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-pkeyutl.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-prime.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-rand.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-rehash.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-req.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-rsa.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-rsautl.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-s_client.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-s_server.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-s_time.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-sess_id.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-smime.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-speed.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-spkac.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-srp.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-storeutl.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-ts.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-verify.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-version.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/openssl-bin-x509.o" =>
                [
                    "apps/progs.h",
                ],
            "apps/progs.h" =>
                [
                    "configdata.pm",
                ],
            "crypto/aes/aes-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/aes/aesni-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/aes/aest4-sparcv9.S" =>
                [
                    "crypto/perlasm/sparcv9_modes.pl",
                ],
            "crypto/aes/vpaes-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/bf/bf-586.s" =>
                [
                    "crypto/perlasm/cbc.pl",
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/bn/bn-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/bn/co-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/bn/x86-gf2m.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/bn/x86-mont.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/buildinf.h" =>
                [
                    "configdata.pm",
                ],
            "crypto/camellia/cmll-x86.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/camellia/cmllt4-sparcv9.S" =>
                [
                    "crypto/perlasm/sparcv9_modes.pl",
                ],
            "crypto/cast/cast-586.s" =>
                [
                    "crypto/perlasm/cbc.pl",
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/des/crypt586.s" =>
                [
                    "crypto/perlasm/cbc.pl",
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/des/des-586.s" =>
                [
                    "crypto/perlasm/cbc.pl",
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/include/internal/bn_conf.h" =>
                [
                    "configdata.pm",
                ],
            "crypto/include/internal/dso_conf.h" =>
                [
                    "configdata.pm",
                ],
            "crypto/libcrypto-lib-cversion.o" =>
                [
                    "crypto/buildinf.h",
                ],
            "crypto/libcrypto-shlib-cversion.o" =>
                [
                    "crypto/buildinf.h",
                ],
            "crypto/rc4/rc4-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/ripemd/rmd-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/sha/sha1-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/sha/sha256-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/sha/sha512-586.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/whrlpool/wp-mmx.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "crypto/x86cpuid.s" =>
                [
                    "crypto/perlasm/x86asm.pl",
                ],
            "doc/man7/openssl_user_macros.pod" =>
                [
                    "configdata.pm",
                ],
            "engines/afalg" =>
                [
                    "libcrypto",
                ],
            "engines/capi" =>
                [
                    "libcrypto",
                ],
            "engines/dasync" =>
                [
                    "libcrypto",
                ],
            "engines/ossltest" =>
                [
                    "libcrypto",
                ],
            "engines/padlock" =>
                [
                    "libcrypto",
                ],
            "fuzz/asn1-test" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "fuzz/asn1parse-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/bignum-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/bndiv-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/client-test" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "fuzz/cms-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/conf-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/crl-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/ct-test" =>
                [
                    "libcrypto",
                ],
            "fuzz/server-test" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "fuzz/x509-test" =>
                [
                    "libcrypto",
                ],
            "include/openssl/opensslconf.h" =>
                [
                    "configdata.pm",
                ],
            "libssl" =>
                [
                    "libcrypto",
                ],
            "test/aborttest" =>
                [
                    "libcrypto",
                ],
            "test/aesgcmtest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/afalgtest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/asn1_decode_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/asn1_encode_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/asn1_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/asn1_string_table_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/asn1_time_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/asynciotest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/asynctest" =>
                [
                    "libcrypto",
                ],
            "test/bad_dtls_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/bftest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/bio_callback_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/bio_enc_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/bio_memleak_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/bioprinttest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/bn_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/bntest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/buildtest_c_aes" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_asn1" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_asn1t" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_async" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_bio" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_blowfish" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_bn" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_buffer" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_camellia" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_cast" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_cmac" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_cms" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_comp" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_conf" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_conf_api" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_core" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_core_names" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_core_numbers" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_crmf" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_crypto" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ct" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_des" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_dh" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_dsa" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_dtls1" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_e_os2" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ebcdic" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ec" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ecdh" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ecdsa" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_engine" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ess" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_evp" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_hmac" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_idea" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_kdf" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_lhash" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_md4" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_md5" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_mdc2" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_modes" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_obj_mac" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_objects" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ocsp" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_opensslv" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ossl_typ" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_params" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_pem" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_pem2" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_pkcs12" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_pkcs7" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_provider" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_rand" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_rand_drbg" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_rc2" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_rc4" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ripemd" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_rsa" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_safestack" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_seed" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_sha" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_srp" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_srtp" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ssl" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ssl2" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_stack" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_store" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_symhacks" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_tls1" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ts" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_txt_db" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_ui" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_whrlpool" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_x509" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_x509_vfy" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/buildtest_c_x509v3" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/casttest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/chacha_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/cipherbytes_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/cipherlist_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/ciphername_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/clienthellotest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/cmsapitest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/conf_include_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/constant_time_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/context_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/crltest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ct_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ctype_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/curve448_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/d2i_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/danetest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/destest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/dhtest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/drbg_cavs_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/drbgtest" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/dsa_no_digest_size_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/dsatest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/dtls_mtu_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/dtlstest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/dtlsv1listentest" =>
                [
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/ec_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/ecdsatest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ecstresstest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ectest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/enginetest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/errtest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/evp_extra_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/evp_kdf_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/evp_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/exdatatest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/exptest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/fatalerrtest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/gmdifftest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/gosttest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/hmactest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ideatest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/igetest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/lhash_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/libtestutil.a" =>
                [
                    "libcrypto",
                ],
            "test/md2test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/mdc2_internal_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/mdc2test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/memleaktest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/modes_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/ocspapitest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/packettest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/params_api_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/params_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/pbelutest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/pemtest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/pkey_meth_kdf_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/pkey_meth_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/poly1305_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/property_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/provider_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/provider_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/rc2test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/rc4test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/rc5test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/rdrand_sanitytest" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/recordlentest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/rsa_mp_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/rsa_sp800_56b_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/rsa_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/sanitytest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/secmemtest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/servername_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/siphash_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/sm2_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/sm4_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/sparse_array_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/srptest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ssl_cert_table_internal_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/ssl_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/ssl_test_ctx_test" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/sslapitest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/sslbuffertest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/sslcorrupttest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/ssltest_old" =>
                [
                    "libcrypto",
                    "libssl",
                ],
            "test/stack_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/sysdefaulttest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/test_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/threadstest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/time_offset_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/tls13ccstest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/tls13encryptiontest" =>
                [
                    "libcrypto",
                    "libssl.a",
                    "test/libtestutil.a",
                ],
            "test/tls13secretstest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/uitest" =>
                [
                    "libcrypto",
                    "libssl",
                    "test/libtestutil.a",
                ],
            "test/v3ext" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/v3nametest" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/verify_extra_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/versions" =>
                [
                    "libcrypto",
                ],
            "test/wpackettest" =>
                [
                    "libcrypto",
                    "libssl.a",
                    "test/libtestutil.a",
                ],
            "test/x509_check_cert_pkey_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/x509_dup_cert_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/x509_internal_test" =>
                [
                    "libcrypto.a",
                    "test/libtestutil.a",
                ],
            "test/x509_time_test" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
            "test/x509aux" =>
                [
                    "libcrypto",
                    "test/libtestutil.a",
                ],
        },
    "dirinfo" =>
        {
            "apps" =>
                {
                    "deps" =>
                        [
                            "apps/uitest-bin-apps_ui.o",
                            "apps/libtestutil-lib-opt.o",
                        ],
                    "products" =>
                        {
                            "bin" =>
                                [
                                    "apps/openssl",
                                    "test/uitest",
                                ],
                            "lib" =>
                                [
                                    "apps/libapps.a",
                                    "test/libtestutil.a",
                                ],
                            "script" =>
                                [
                                    "apps/CA.pl",
                                    "apps/tsget.pl",
                                ],
                        },
                },
            "crypto" =>
                {
                    "deps" =>
                        [
                            "crypto/fips-dso-cryptlib.o",
                            "crypto/fips-dso-mem.o",
                            "crypto/fips-dso-mem_clr.o",
                            "crypto/fips-dso-params.o",
                            "crypto/libcrypto-lib-context.o",
                            "crypto/libcrypto-lib-core_fetch.o",
                            "crypto/libcrypto-lib-cpt_err.o",
                            "crypto/libcrypto-lib-cryptlib.o",
                            "crypto/libcrypto-lib-ctype.o",
                            "crypto/libcrypto-lib-cversion.o",
                            "crypto/libcrypto-lib-ebcdic.o",
                            "crypto/libcrypto-lib-ex_data.o",
                            "crypto/libcrypto-lib-getenv.o",
                            "crypto/libcrypto-lib-init.o",
                            "crypto/libcrypto-lib-mem.o",
                            "crypto/libcrypto-lib-mem_dbg.o",
                            "crypto/libcrypto-lib-mem_sec.o",
                            "crypto/libcrypto-lib-o_dir.o",
                            "crypto/libcrypto-lib-o_fips.o",
                            "crypto/libcrypto-lib-o_fopen.o",
                            "crypto/libcrypto-lib-o_init.o",
                            "crypto/libcrypto-lib-o_str.o",
                            "crypto/libcrypto-lib-o_time.o",
                            "crypto/libcrypto-lib-params.o",
                            "crypto/libcrypto-lib-provider.o",
                            "crypto/libcrypto-lib-provider_conf.o",
                            "crypto/libcrypto-lib-provider_core.o",
                            "crypto/libcrypto-lib-provider_predefined.o",
                            "crypto/libcrypto-lib-sparse_array.o",
                            "crypto/libcrypto-lib-threads_none.o",
                            "crypto/libcrypto-lib-threads_pthread.o",
                            "crypto/libcrypto-lib-threads_win.o",
                            "crypto/libcrypto-lib-trace.o",
                            "crypto/libcrypto-lib-uid.o",
                            "crypto/libcrypto-lib-x86_64cpuid.o",
                            "crypto/libcrypto-shlib-context.o",
                            "crypto/libcrypto-shlib-core_fetch.o",
                            "crypto/libcrypto-shlib-cpt_err.o",
                            "crypto/libcrypto-shlib-cryptlib.o",
                            "crypto/libcrypto-shlib-ctype.o",
                            "crypto/libcrypto-shlib-cversion.o",
                            "crypto/libcrypto-shlib-ebcdic.o",
                            "crypto/libcrypto-shlib-ex_data.o",
                            "crypto/libcrypto-shlib-getenv.o",
                            "crypto/libcrypto-shlib-init.o",
                            "crypto/libcrypto-shlib-mem.o",
                            "crypto/libcrypto-shlib-mem_dbg.o",
                            "crypto/libcrypto-shlib-mem_sec.o",
                            "crypto/libcrypto-shlib-o_dir.o",
                            "crypto/libcrypto-shlib-o_fips.o",
                            "crypto/libcrypto-shlib-o_fopen.o",
                            "crypto/libcrypto-shlib-o_init.o",
                            "crypto/libcrypto-shlib-o_str.o",
                            "crypto/libcrypto-shlib-o_time.o",
                            "crypto/libcrypto-shlib-params.o",
                            "crypto/libcrypto-shlib-provider.o",
                            "crypto/libcrypto-shlib-provider_conf.o",
                            "crypto/libcrypto-shlib-provider_core.o",
                            "crypto/libcrypto-shlib-provider_predefined.o",
                            "crypto/libcrypto-shlib-sparse_array.o",
                            "crypto/libcrypto-shlib-threads_none.o",
                            "crypto/libcrypto-shlib-threads_pthread.o",
                            "crypto/libcrypto-shlib-threads_win.o",
                            "crypto/libcrypto-shlib-trace.o",
                            "crypto/libcrypto-shlib-uid.o",
                            "crypto/libcrypto-shlib-x86_64cpuid.o",
                        ],
                    "products" =>
                        {
                            "dso" =>
                                [
                                    "providers/fips",
                                ],
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/aes" =>
                {
                    "deps" =>
                        [
                            "crypto/aes/libcrypto-lib-aes-x86_64.o",
                            "crypto/aes/libcrypto-lib-aes_cfb.o",
                            "crypto/aes/libcrypto-lib-aes_ecb.o",
                            "crypto/aes/libcrypto-lib-aes_ige.o",
                            "crypto/aes/libcrypto-lib-aes_misc.o",
                            "crypto/aes/libcrypto-lib-aes_ofb.o",
                            "crypto/aes/libcrypto-lib-aes_wrap.o",
                            "crypto/aes/libcrypto-lib-aesni-mb-x86_64.o",
                            "crypto/aes/libcrypto-lib-aesni-sha1-x86_64.o",
                            "crypto/aes/libcrypto-lib-aesni-sha256-x86_64.o",
                            "crypto/aes/libcrypto-lib-aesni-x86_64.o",
                            "crypto/aes/libcrypto-lib-bsaes-x86_64.o",
                            "crypto/aes/libcrypto-lib-vpaes-x86_64.o",
                            "crypto/aes/libcrypto-shlib-aes-x86_64.o",
                            "crypto/aes/libcrypto-shlib-aes_cfb.o",
                            "crypto/aes/libcrypto-shlib-aes_ecb.o",
                            "crypto/aes/libcrypto-shlib-aes_ige.o",
                            "crypto/aes/libcrypto-shlib-aes_misc.o",
                            "crypto/aes/libcrypto-shlib-aes_ofb.o",
                            "crypto/aes/libcrypto-shlib-aes_wrap.o",
                            "crypto/aes/libcrypto-shlib-aesni-mb-x86_64.o",
                            "crypto/aes/libcrypto-shlib-aesni-sha1-x86_64.o",
                            "crypto/aes/libcrypto-shlib-aesni-sha256-x86_64.o",
                            "crypto/aes/libcrypto-shlib-aesni-x86_64.o",
                            "crypto/aes/libcrypto-shlib-bsaes-x86_64.o",
                            "crypto/aes/libcrypto-shlib-vpaes-x86_64.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/aria" =>
                {
                    "deps" =>
                        [
                            "crypto/aria/libcrypto-lib-aria.o",
                            "crypto/aria/libcrypto-shlib-aria.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/asn1" =>
                {
                    "deps" =>
                        [
                            "crypto/asn1/libcrypto-lib-a_bitstr.o",
                            "crypto/asn1/libcrypto-lib-a_d2i_fp.o",
                            "crypto/asn1/libcrypto-lib-a_digest.o",
                            "crypto/asn1/libcrypto-lib-a_dup.o",
                            "crypto/asn1/libcrypto-lib-a_gentm.o",
                            "crypto/asn1/libcrypto-lib-a_i2d_fp.o",
                            "crypto/asn1/libcrypto-lib-a_int.o",
                            "crypto/asn1/libcrypto-lib-a_mbstr.o",
                            "crypto/asn1/libcrypto-lib-a_object.o",
                            "crypto/asn1/libcrypto-lib-a_octet.o",
                            "crypto/asn1/libcrypto-lib-a_print.o",
                            "crypto/asn1/libcrypto-lib-a_sign.o",
                            "crypto/asn1/libcrypto-lib-a_strex.o",
                            "crypto/asn1/libcrypto-lib-a_strnid.o",
                            "crypto/asn1/libcrypto-lib-a_time.o",
                            "crypto/asn1/libcrypto-lib-a_type.o",
                            "crypto/asn1/libcrypto-lib-a_utctm.o",
                            "crypto/asn1/libcrypto-lib-a_utf8.o",
                            "crypto/asn1/libcrypto-lib-a_verify.o",
                            "crypto/asn1/libcrypto-lib-ameth_lib.o",
                            "crypto/asn1/libcrypto-lib-asn1_err.o",
                            "crypto/asn1/libcrypto-lib-asn1_gen.o",
                            "crypto/asn1/libcrypto-lib-asn1_item_list.o",
                            "crypto/asn1/libcrypto-lib-asn1_lib.o",
                            "crypto/asn1/libcrypto-lib-asn1_par.o",
                            "crypto/asn1/libcrypto-lib-asn_mime.o",
                            "crypto/asn1/libcrypto-lib-asn_moid.o",
                            "crypto/asn1/libcrypto-lib-asn_mstbl.o",
                            "crypto/asn1/libcrypto-lib-asn_pack.o",
                            "crypto/asn1/libcrypto-lib-bio_asn1.o",
                            "crypto/asn1/libcrypto-lib-bio_ndef.o",
                            "crypto/asn1/libcrypto-lib-d2i_pr.o",
                            "crypto/asn1/libcrypto-lib-d2i_pu.o",
                            "crypto/asn1/libcrypto-lib-evp_asn1.o",
                            "crypto/asn1/libcrypto-lib-f_int.o",
                            "crypto/asn1/libcrypto-lib-f_string.o",
                            "crypto/asn1/libcrypto-lib-i2d_pr.o",
                            "crypto/asn1/libcrypto-lib-i2d_pu.o",
                            "crypto/asn1/libcrypto-lib-n_pkey.o",
                            "crypto/asn1/libcrypto-lib-nsseq.o",
                            "crypto/asn1/libcrypto-lib-p5_pbe.o",
                            "crypto/asn1/libcrypto-lib-p5_pbev2.o",
                            "crypto/asn1/libcrypto-lib-p5_scrypt.o",
                            "crypto/asn1/libcrypto-lib-p8_pkey.o",
                            "crypto/asn1/libcrypto-lib-t_bitst.o",
                            "crypto/asn1/libcrypto-lib-t_pkey.o",
                            "crypto/asn1/libcrypto-lib-t_spki.o",
                            "crypto/asn1/libcrypto-lib-tasn_dec.o",
                            "crypto/asn1/libcrypto-lib-tasn_enc.o",
                            "crypto/asn1/libcrypto-lib-tasn_fre.o",
                            "crypto/asn1/libcrypto-lib-tasn_new.o",
                            "crypto/asn1/libcrypto-lib-tasn_prn.o",
                            "crypto/asn1/libcrypto-lib-tasn_scn.o",
                            "crypto/asn1/libcrypto-lib-tasn_typ.o",
                            "crypto/asn1/libcrypto-lib-tasn_utl.o",
                            "crypto/asn1/libcrypto-lib-x_algor.o",
                            "crypto/asn1/libcrypto-lib-x_bignum.o",
                            "crypto/asn1/libcrypto-lib-x_info.o",
                            "crypto/asn1/libcrypto-lib-x_int64.o",
                            "crypto/asn1/libcrypto-lib-x_long.o",
                            "crypto/asn1/libcrypto-lib-x_pkey.o",
                            "crypto/asn1/libcrypto-lib-x_sig.o",
                            "crypto/asn1/libcrypto-lib-x_spki.o",
                            "crypto/asn1/libcrypto-lib-x_val.o",
                            "crypto/asn1/libcrypto-shlib-a_bitstr.o",
                            "crypto/asn1/libcrypto-shlib-a_d2i_fp.o",
                            "crypto/asn1/libcrypto-shlib-a_digest.o",
                            "crypto/asn1/libcrypto-shlib-a_dup.o",
                            "crypto/asn1/libcrypto-shlib-a_gentm.o",
                            "crypto/asn1/libcrypto-shlib-a_i2d_fp.o",
                            "crypto/asn1/libcrypto-shlib-a_int.o",
                            "crypto/asn1/libcrypto-shlib-a_mbstr.o",
                            "crypto/asn1/libcrypto-shlib-a_object.o",
                            "crypto/asn1/libcrypto-shlib-a_octet.o",
                            "crypto/asn1/libcrypto-shlib-a_print.o",
                            "crypto/asn1/libcrypto-shlib-a_sign.o",
                            "crypto/asn1/libcrypto-shlib-a_strex.o",
                            "crypto/asn1/libcrypto-shlib-a_strnid.o",
                            "crypto/asn1/libcrypto-shlib-a_time.o",
                            "crypto/asn1/libcrypto-shlib-a_type.o",
                            "crypto/asn1/libcrypto-shlib-a_utctm.o",
                            "crypto/asn1/libcrypto-shlib-a_utf8.o",
                            "crypto/asn1/libcrypto-shlib-a_verify.o",
                            "crypto/asn1/libcrypto-shlib-ameth_lib.o",
                            "crypto/asn1/libcrypto-shlib-asn1_err.o",
                            "crypto/asn1/libcrypto-shlib-asn1_gen.o",
                            "crypto/asn1/libcrypto-shlib-asn1_item_list.o",
                            "crypto/asn1/libcrypto-shlib-asn1_lib.o",
                            "crypto/asn1/libcrypto-shlib-asn1_par.o",
                            "crypto/asn1/libcrypto-shlib-asn_mime.o",
                            "crypto/asn1/libcrypto-shlib-asn_moid.o",
                            "crypto/asn1/libcrypto-shlib-asn_mstbl.o",
                            "crypto/asn1/libcrypto-shlib-asn_pack.o",
                            "crypto/asn1/libcrypto-shlib-bio_asn1.o",
                            "crypto/asn1/libcrypto-shlib-bio_ndef.o",
                            "crypto/asn1/libcrypto-shlib-d2i_pr.o",
                            "crypto/asn1/libcrypto-shlib-d2i_pu.o",
                            "crypto/asn1/libcrypto-shlib-evp_asn1.o",
                            "crypto/asn1/libcrypto-shlib-f_int.o",
                            "crypto/asn1/libcrypto-shlib-f_string.o",
                            "crypto/asn1/libcrypto-shlib-i2d_pr.o",
                            "crypto/asn1/libcrypto-shlib-i2d_pu.o",
                            "crypto/asn1/libcrypto-shlib-n_pkey.o",
                            "crypto/asn1/libcrypto-shlib-nsseq.o",
                            "crypto/asn1/libcrypto-shlib-p5_pbe.o",
                            "crypto/asn1/libcrypto-shlib-p5_pbev2.o",
                            "crypto/asn1/libcrypto-shlib-p5_scrypt.o",
                            "crypto/asn1/libcrypto-shlib-p8_pkey.o",
                            "crypto/asn1/libcrypto-shlib-t_bitst.o",
                            "crypto/asn1/libcrypto-shlib-t_pkey.o",
                            "crypto/asn1/libcrypto-shlib-t_spki.o",
                            "crypto/asn1/libcrypto-shlib-tasn_dec.o",
                            "crypto/asn1/libcrypto-shlib-tasn_enc.o",
                            "crypto/asn1/libcrypto-shlib-tasn_fre.o",
                            "crypto/asn1/libcrypto-shlib-tasn_new.o",
                            "crypto/asn1/libcrypto-shlib-tasn_prn.o",
                            "crypto/asn1/libcrypto-shlib-tasn_scn.o",
                            "crypto/asn1/libcrypto-shlib-tasn_typ.o",
                            "crypto/asn1/libcrypto-shlib-tasn_utl.o",
                            "crypto/asn1/libcrypto-shlib-x_algor.o",
                            "crypto/asn1/libcrypto-shlib-x_bignum.o",
                            "crypto/asn1/libcrypto-shlib-x_info.o",
                            "crypto/asn1/libcrypto-shlib-x_int64.o",
                            "crypto/asn1/libcrypto-shlib-x_long.o",
                            "crypto/asn1/libcrypto-shlib-x_pkey.o",
                            "crypto/asn1/libcrypto-shlib-x_sig.o",
                            "crypto/asn1/libcrypto-shlib-x_spki.o",
                            "crypto/asn1/libcrypto-shlib-x_val.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/async" =>
                {
                    "deps" =>
                        [
                            "crypto/async/libcrypto-lib-async.o",
                            "crypto/async/libcrypto-lib-async_err.o",
                            "crypto/async/libcrypto-lib-async_wait.o",
                            "crypto/async/libcrypto-shlib-async.o",
                            "crypto/async/libcrypto-shlib-async_err.o",
                            "crypto/async/libcrypto-shlib-async_wait.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/async/arch" =>
                {
                    "deps" =>
                        [
                            "crypto/async/arch/libcrypto-lib-async_null.o",
                            "crypto/async/arch/libcrypto-lib-async_posix.o",
                            "crypto/async/arch/libcrypto-lib-async_win.o",
                            "crypto/async/arch/libcrypto-shlib-async_null.o",
                            "crypto/async/arch/libcrypto-shlib-async_posix.o",
                            "crypto/async/arch/libcrypto-shlib-async_win.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/bf" =>
                {
                    "deps" =>
                        [
                            "crypto/bf/libcrypto-lib-bf_cfb64.o",
                            "crypto/bf/libcrypto-lib-bf_ecb.o",
                            "crypto/bf/libcrypto-lib-bf_enc.o",
                            "crypto/bf/libcrypto-lib-bf_ofb64.o",
                            "crypto/bf/libcrypto-lib-bf_skey.o",
                            "crypto/bf/libcrypto-shlib-bf_cfb64.o",
                            "crypto/bf/libcrypto-shlib-bf_ecb.o",
                            "crypto/bf/libcrypto-shlib-bf_enc.o",
                            "crypto/bf/libcrypto-shlib-bf_ofb64.o",
                            "crypto/bf/libcrypto-shlib-bf_skey.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/bio" =>
                {
                    "deps" =>
                        [
                            "crypto/bio/libcrypto-lib-b_addr.o",
                            "crypto/bio/libcrypto-lib-b_dump.o",
                            "crypto/bio/libcrypto-lib-b_print.o",
                            "crypto/bio/libcrypto-lib-b_sock.o",
                            "crypto/bio/libcrypto-lib-b_sock2.o",
                            "crypto/bio/libcrypto-lib-bf_buff.o",
                            "crypto/bio/libcrypto-lib-bf_lbuf.o",
                            "crypto/bio/libcrypto-lib-bf_nbio.o",
                            "crypto/bio/libcrypto-lib-bf_null.o",
                            "crypto/bio/libcrypto-lib-bio_cb.o",
                            "crypto/bio/libcrypto-lib-bio_err.o",
                            "crypto/bio/libcrypto-lib-bio_lib.o",
                            "crypto/bio/libcrypto-lib-bio_meth.o",
                            "crypto/bio/libcrypto-lib-bss_acpt.o",
                            "crypto/bio/libcrypto-lib-bss_bio.o",
                            "crypto/bio/libcrypto-lib-bss_conn.o",
                            "crypto/bio/libcrypto-lib-bss_dgram.o",
                            "crypto/bio/libcrypto-lib-bss_fd.o",
                            "crypto/bio/libcrypto-lib-bss_file.o",
                            "crypto/bio/libcrypto-lib-bss_log.o",
                            "crypto/bio/libcrypto-lib-bss_mem.o",
                            "crypto/bio/libcrypto-lib-bss_null.o",
                            "crypto/bio/libcrypto-lib-bss_sock.o",
                            "crypto/bio/libcrypto-shlib-b_addr.o",
                            "crypto/bio/libcrypto-shlib-b_dump.o",
                            "crypto/bio/libcrypto-shlib-b_print.o",
                            "crypto/bio/libcrypto-shlib-b_sock.o",
                            "crypto/bio/libcrypto-shlib-b_sock2.o",
                            "crypto/bio/libcrypto-shlib-bf_buff.o",
                            "crypto/bio/libcrypto-shlib-bf_lbuf.o",
                            "crypto/bio/libcrypto-shlib-bf_nbio.o",
                            "crypto/bio/libcrypto-shlib-bf_null.o",
                            "crypto/bio/libcrypto-shlib-bio_cb.o",
                            "crypto/bio/libcrypto-shlib-bio_err.o",
                            "crypto/bio/libcrypto-shlib-bio_lib.o",
                            "crypto/bio/libcrypto-shlib-bio_meth.o",
                            "crypto/bio/libcrypto-shlib-bss_acpt.o",
                            "crypto/bio/libcrypto-shlib-bss_bio.o",
                            "crypto/bio/libcrypto-shlib-bss_conn.o",
                            "crypto/bio/libcrypto-shlib-bss_dgram.o",
                            "crypto/bio/libcrypto-shlib-bss_fd.o",
                            "crypto/bio/libcrypto-shlib-bss_file.o",
                            "crypto/bio/libcrypto-shlib-bss_log.o",
                            "crypto/bio/libcrypto-shlib-bss_mem.o",
                            "crypto/bio/libcrypto-shlib-bss_null.o",
                            "crypto/bio/libcrypto-shlib-bss_sock.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/blake2" =>
                {
                    "deps" =>
                        [
                            "crypto/blake2/libcrypto-lib-blake2b.o",
                            "crypto/blake2/libcrypto-lib-blake2b_mac.o",
                            "crypto/blake2/libcrypto-lib-blake2s.o",
                            "crypto/blake2/libcrypto-lib-blake2s_mac.o",
                            "crypto/blake2/libcrypto-lib-m_blake2b.o",
                            "crypto/blake2/libcrypto-lib-m_blake2s.o",
                            "crypto/blake2/libcrypto-shlib-blake2b.o",
                            "crypto/blake2/libcrypto-shlib-blake2b_mac.o",
                            "crypto/blake2/libcrypto-shlib-blake2s.o",
                            "crypto/blake2/libcrypto-shlib-blake2s_mac.o",
                            "crypto/blake2/libcrypto-shlib-m_blake2b.o",
                            "crypto/blake2/libcrypto-shlib-m_blake2s.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/bn" =>
                {
                    "deps" =>
                        [
                            "crypto/bn/libcrypto-lib-bn_add.o",
                            "crypto/bn/libcrypto-lib-bn_blind.o",
                            "crypto/bn/libcrypto-lib-bn_const.o",
                            "crypto/bn/libcrypto-lib-bn_ctx.o",
                            "crypto/bn/libcrypto-lib-bn_depr.o",
                            "crypto/bn/libcrypto-lib-bn_dh.o",
                            "crypto/bn/libcrypto-lib-bn_div.o",
                            "crypto/bn/libcrypto-lib-bn_err.o",
                            "crypto/bn/libcrypto-lib-bn_exp.o",
                            "crypto/bn/libcrypto-lib-bn_exp2.o",
                            "crypto/bn/libcrypto-lib-bn_gcd.o",
                            "crypto/bn/libcrypto-lib-bn_gf2m.o",
                            "crypto/bn/libcrypto-lib-bn_intern.o",
                            "crypto/bn/libcrypto-lib-bn_kron.o",
                            "crypto/bn/libcrypto-lib-bn_lib.o",
                            "crypto/bn/libcrypto-lib-bn_mod.o",
                            "crypto/bn/libcrypto-lib-bn_mont.o",
                            "crypto/bn/libcrypto-lib-bn_mpi.o",
                            "crypto/bn/libcrypto-lib-bn_mul.o",
                            "crypto/bn/libcrypto-lib-bn_nist.o",
                            "crypto/bn/libcrypto-lib-bn_prime.o",
                            "crypto/bn/libcrypto-lib-bn_print.o",
                            "crypto/bn/libcrypto-lib-bn_rand.o",
                            "crypto/bn/libcrypto-lib-bn_recp.o",
                            "crypto/bn/libcrypto-lib-bn_rsa_fips186_4.o",
                            "crypto/bn/libcrypto-lib-bn_shift.o",
                            "crypto/bn/libcrypto-lib-bn_sqr.o",
                            "crypto/bn/libcrypto-lib-bn_sqrt.o",
                            "crypto/bn/libcrypto-lib-bn_srp.o",
                            "crypto/bn/libcrypto-lib-bn_word.o",
                            "crypto/bn/libcrypto-lib-bn_x931p.o",
                            "crypto/bn/libcrypto-lib-rsaz-avx2.o",
                            "crypto/bn/libcrypto-lib-rsaz-x86_64.o",
                            "crypto/bn/libcrypto-lib-rsaz_exp.o",
                            "crypto/bn/libcrypto-lib-x86_64-gf2m.o",
                            "crypto/bn/libcrypto-lib-x86_64-mont.o",
                            "crypto/bn/libcrypto-lib-x86_64-mont5.o",
                            "crypto/bn/libcrypto-shlib-bn_add.o",
                            "crypto/bn/libcrypto-shlib-bn_blind.o",
                            "crypto/bn/libcrypto-shlib-bn_const.o",
                            "crypto/bn/libcrypto-shlib-bn_ctx.o",
                            "crypto/bn/libcrypto-shlib-bn_depr.o",
                            "crypto/bn/libcrypto-shlib-bn_dh.o",
                            "crypto/bn/libcrypto-shlib-bn_div.o",
                            "crypto/bn/libcrypto-shlib-bn_err.o",
                            "crypto/bn/libcrypto-shlib-bn_exp.o",
                            "crypto/bn/libcrypto-shlib-bn_exp2.o",
                            "crypto/bn/libcrypto-shlib-bn_gcd.o",
                            "crypto/bn/libcrypto-shlib-bn_gf2m.o",
                            "crypto/bn/libcrypto-shlib-bn_intern.o",
                            "crypto/bn/libcrypto-shlib-bn_kron.o",
                            "crypto/bn/libcrypto-shlib-bn_lib.o",
                            "crypto/bn/libcrypto-shlib-bn_mod.o",
                            "crypto/bn/libcrypto-shlib-bn_mont.o",
                            "crypto/bn/libcrypto-shlib-bn_mpi.o",
                            "crypto/bn/libcrypto-shlib-bn_mul.o",
                            "crypto/bn/libcrypto-shlib-bn_nist.o",
                            "crypto/bn/libcrypto-shlib-bn_prime.o",
                            "crypto/bn/libcrypto-shlib-bn_print.o",
                            "crypto/bn/libcrypto-shlib-bn_rand.o",
                            "crypto/bn/libcrypto-shlib-bn_recp.o",
                            "crypto/bn/libcrypto-shlib-bn_rsa_fips186_4.o",
                            "crypto/bn/libcrypto-shlib-bn_shift.o",
                            "crypto/bn/libcrypto-shlib-bn_sqr.o",
                            "crypto/bn/libcrypto-shlib-bn_sqrt.o",
                            "crypto/bn/libcrypto-shlib-bn_srp.o",
                            "crypto/bn/libcrypto-shlib-bn_word.o",
                            "crypto/bn/libcrypto-shlib-bn_x931p.o",
                            "crypto/bn/libcrypto-shlib-rsaz-avx2.o",
                            "crypto/bn/libcrypto-shlib-rsaz-x86_64.o",
                            "crypto/bn/libcrypto-shlib-rsaz_exp.o",
                            "crypto/bn/libcrypto-shlib-x86_64-gf2m.o",
                            "crypto/bn/libcrypto-shlib-x86_64-mont.o",
                            "crypto/bn/libcrypto-shlib-x86_64-mont5.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/bn/asm" =>
                {
                    "deps" =>
                        [
                            "crypto/bn/asm/libcrypto-lib-x86_64-gcc.o",
                            "crypto/bn/asm/libcrypto-shlib-x86_64-gcc.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/buffer" =>
                {
                    "deps" =>
                        [
                            "crypto/buffer/libcrypto-lib-buf_err.o",
                            "crypto/buffer/libcrypto-lib-buffer.o",
                            "crypto/buffer/libcrypto-shlib-buf_err.o",
                            "crypto/buffer/libcrypto-shlib-buffer.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/camellia" =>
                {
                    "deps" =>
                        [
                            "crypto/camellia/libcrypto-lib-cmll-x86_64.o",
                            "crypto/camellia/libcrypto-lib-cmll_cfb.o",
                            "crypto/camellia/libcrypto-lib-cmll_ctr.o",
                            "crypto/camellia/libcrypto-lib-cmll_ecb.o",
                            "crypto/camellia/libcrypto-lib-cmll_misc.o",
                            "crypto/camellia/libcrypto-lib-cmll_ofb.o",
                            "crypto/camellia/libcrypto-shlib-cmll-x86_64.o",
                            "crypto/camellia/libcrypto-shlib-cmll_cfb.o",
                            "crypto/camellia/libcrypto-shlib-cmll_ctr.o",
                            "crypto/camellia/libcrypto-shlib-cmll_ecb.o",
                            "crypto/camellia/libcrypto-shlib-cmll_misc.o",
                            "crypto/camellia/libcrypto-shlib-cmll_ofb.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/cast" =>
                {
                    "deps" =>
                        [
                            "crypto/cast/libcrypto-lib-c_cfb64.o",
                            "crypto/cast/libcrypto-lib-c_ecb.o",
                            "crypto/cast/libcrypto-lib-c_enc.o",
                            "crypto/cast/libcrypto-lib-c_ofb64.o",
                            "crypto/cast/libcrypto-lib-c_skey.o",
                            "crypto/cast/libcrypto-shlib-c_cfb64.o",
                            "crypto/cast/libcrypto-shlib-c_ecb.o",
                            "crypto/cast/libcrypto-shlib-c_enc.o",
                            "crypto/cast/libcrypto-shlib-c_ofb64.o",
                            "crypto/cast/libcrypto-shlib-c_skey.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/chacha" =>
                {
                    "deps" =>
                        [
                            "crypto/chacha/libcrypto-lib-chacha-x86_64.o",
                            "crypto/chacha/libcrypto-shlib-chacha-x86_64.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/cmac" =>
                {
                    "deps" =>
                        [
                            "crypto/cmac/libcrypto-lib-cm_ameth.o",
                            "crypto/cmac/libcrypto-lib-cm_meth.o",
                            "crypto/cmac/libcrypto-lib-cmac.o",
                            "crypto/cmac/libcrypto-shlib-cm_ameth.o",
                            "crypto/cmac/libcrypto-shlib-cm_meth.o",
                            "crypto/cmac/libcrypto-shlib-cmac.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/cms" =>
                {
                    "deps" =>
                        [
                            "crypto/cms/libcrypto-lib-cms_asn1.o",
                            "crypto/cms/libcrypto-lib-cms_att.o",
                            "crypto/cms/libcrypto-lib-cms_cd.o",
                            "crypto/cms/libcrypto-lib-cms_dd.o",
                            "crypto/cms/libcrypto-lib-cms_enc.o",
                            "crypto/cms/libcrypto-lib-cms_env.o",
                            "crypto/cms/libcrypto-lib-cms_err.o",
                            "crypto/cms/libcrypto-lib-cms_ess.o",
                            "crypto/cms/libcrypto-lib-cms_io.o",
                            "crypto/cms/libcrypto-lib-cms_kari.o",
                            "crypto/cms/libcrypto-lib-cms_lib.o",
                            "crypto/cms/libcrypto-lib-cms_pwri.o",
                            "crypto/cms/libcrypto-lib-cms_sd.o",
                            "crypto/cms/libcrypto-lib-cms_smime.o",
                            "crypto/cms/libcrypto-shlib-cms_asn1.o",
                            "crypto/cms/libcrypto-shlib-cms_att.o",
                            "crypto/cms/libcrypto-shlib-cms_cd.o",
                            "crypto/cms/libcrypto-shlib-cms_dd.o",
                            "crypto/cms/libcrypto-shlib-cms_enc.o",
                            "crypto/cms/libcrypto-shlib-cms_env.o",
                            "crypto/cms/libcrypto-shlib-cms_err.o",
                            "crypto/cms/libcrypto-shlib-cms_ess.o",
                            "crypto/cms/libcrypto-shlib-cms_io.o",
                            "crypto/cms/libcrypto-shlib-cms_kari.o",
                            "crypto/cms/libcrypto-shlib-cms_lib.o",
                            "crypto/cms/libcrypto-shlib-cms_pwri.o",
                            "crypto/cms/libcrypto-shlib-cms_sd.o",
                            "crypto/cms/libcrypto-shlib-cms_smime.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/comp" =>
                {
                    "deps" =>
                        [
                            "crypto/comp/libcrypto-lib-c_zlib.o",
                            "crypto/comp/libcrypto-lib-comp_err.o",
                            "crypto/comp/libcrypto-lib-comp_lib.o",
                            "crypto/comp/libcrypto-shlib-c_zlib.o",
                            "crypto/comp/libcrypto-shlib-comp_err.o",
                            "crypto/comp/libcrypto-shlib-comp_lib.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/conf" =>
                {
                    "deps" =>
                        [
                            "crypto/conf/libcrypto-lib-conf_api.o",
                            "crypto/conf/libcrypto-lib-conf_def.o",
                            "crypto/conf/libcrypto-lib-conf_err.o",
                            "crypto/conf/libcrypto-lib-conf_lib.o",
                            "crypto/conf/libcrypto-lib-conf_mall.o",
                            "crypto/conf/libcrypto-lib-conf_mod.o",
                            "crypto/conf/libcrypto-lib-conf_sap.o",
                            "crypto/conf/libcrypto-lib-conf_ssl.o",
                            "crypto/conf/libcrypto-shlib-conf_api.o",
                            "crypto/conf/libcrypto-shlib-conf_def.o",
                            "crypto/conf/libcrypto-shlib-conf_err.o",
                            "crypto/conf/libcrypto-shlib-conf_lib.o",
                            "crypto/conf/libcrypto-shlib-conf_mall.o",
                            "crypto/conf/libcrypto-shlib-conf_mod.o",
                            "crypto/conf/libcrypto-shlib-conf_sap.o",
                            "crypto/conf/libcrypto-shlib-conf_ssl.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/crmf" =>
                {
                    "deps" =>
                        [
                            "crypto/crmf/libcrypto-lib-crmf_asn.o",
                            "crypto/crmf/libcrypto-lib-crmf_err.o",
                            "crypto/crmf/libcrypto-lib-crmf_lib.o",
                            "crypto/crmf/libcrypto-lib-crmf_pbm.o",
                            "crypto/crmf/libcrypto-shlib-crmf_asn.o",
                            "crypto/crmf/libcrypto-shlib-crmf_err.o",
                            "crypto/crmf/libcrypto-shlib-crmf_lib.o",
                            "crypto/crmf/libcrypto-shlib-crmf_pbm.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ct" =>
                {
                    "deps" =>
                        [
                            "crypto/ct/libcrypto-lib-ct_b64.o",
                            "crypto/ct/libcrypto-lib-ct_err.o",
                            "crypto/ct/libcrypto-lib-ct_log.o",
                            "crypto/ct/libcrypto-lib-ct_oct.o",
                            "crypto/ct/libcrypto-lib-ct_policy.o",
                            "crypto/ct/libcrypto-lib-ct_prn.o",
                            "crypto/ct/libcrypto-lib-ct_sct.o",
                            "crypto/ct/libcrypto-lib-ct_sct_ctx.o",
                            "crypto/ct/libcrypto-lib-ct_vfy.o",
                            "crypto/ct/libcrypto-lib-ct_x509v3.o",
                            "crypto/ct/libcrypto-shlib-ct_b64.o",
                            "crypto/ct/libcrypto-shlib-ct_err.o",
                            "crypto/ct/libcrypto-shlib-ct_log.o",
                            "crypto/ct/libcrypto-shlib-ct_oct.o",
                            "crypto/ct/libcrypto-shlib-ct_policy.o",
                            "crypto/ct/libcrypto-shlib-ct_prn.o",
                            "crypto/ct/libcrypto-shlib-ct_sct.o",
                            "crypto/ct/libcrypto-shlib-ct_sct_ctx.o",
                            "crypto/ct/libcrypto-shlib-ct_vfy.o",
                            "crypto/ct/libcrypto-shlib-ct_x509v3.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/des" =>
                {
                    "deps" =>
                        [
                            "crypto/des/libcrypto-lib-cbc_cksm.o",
                            "crypto/des/libcrypto-lib-cbc_enc.o",
                            "crypto/des/libcrypto-lib-cfb64ede.o",
                            "crypto/des/libcrypto-lib-cfb64enc.o",
                            "crypto/des/libcrypto-lib-cfb_enc.o",
                            "crypto/des/libcrypto-lib-des_enc.o",
                            "crypto/des/libcrypto-lib-ecb3_enc.o",
                            "crypto/des/libcrypto-lib-ecb_enc.o",
                            "crypto/des/libcrypto-lib-fcrypt.o",
                            "crypto/des/libcrypto-lib-fcrypt_b.o",
                            "crypto/des/libcrypto-lib-ofb64ede.o",
                            "crypto/des/libcrypto-lib-ofb64enc.o",
                            "crypto/des/libcrypto-lib-ofb_enc.o",
                            "crypto/des/libcrypto-lib-pcbc_enc.o",
                            "crypto/des/libcrypto-lib-qud_cksm.o",
                            "crypto/des/libcrypto-lib-rand_key.o",
                            "crypto/des/libcrypto-lib-set_key.o",
                            "crypto/des/libcrypto-lib-str2key.o",
                            "crypto/des/libcrypto-lib-xcbc_enc.o",
                            "crypto/des/libcrypto-shlib-cbc_cksm.o",
                            "crypto/des/libcrypto-shlib-cbc_enc.o",
                            "crypto/des/libcrypto-shlib-cfb64ede.o",
                            "crypto/des/libcrypto-shlib-cfb64enc.o",
                            "crypto/des/libcrypto-shlib-cfb_enc.o",
                            "crypto/des/libcrypto-shlib-des_enc.o",
                            "crypto/des/libcrypto-shlib-ecb3_enc.o",
                            "crypto/des/libcrypto-shlib-ecb_enc.o",
                            "crypto/des/libcrypto-shlib-fcrypt.o",
                            "crypto/des/libcrypto-shlib-fcrypt_b.o",
                            "crypto/des/libcrypto-shlib-ofb64ede.o",
                            "crypto/des/libcrypto-shlib-ofb64enc.o",
                            "crypto/des/libcrypto-shlib-ofb_enc.o",
                            "crypto/des/libcrypto-shlib-pcbc_enc.o",
                            "crypto/des/libcrypto-shlib-qud_cksm.o",
                            "crypto/des/libcrypto-shlib-rand_key.o",
                            "crypto/des/libcrypto-shlib-set_key.o",
                            "crypto/des/libcrypto-shlib-str2key.o",
                            "crypto/des/libcrypto-shlib-xcbc_enc.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/dh" =>
                {
                    "deps" =>
                        [
                            "crypto/dh/libcrypto-lib-dh_ameth.o",
                            "crypto/dh/libcrypto-lib-dh_asn1.o",
                            "crypto/dh/libcrypto-lib-dh_check.o",
                            "crypto/dh/libcrypto-lib-dh_depr.o",
                            "crypto/dh/libcrypto-lib-dh_err.o",
                            "crypto/dh/libcrypto-lib-dh_gen.o",
                            "crypto/dh/libcrypto-lib-dh_kdf.o",
                            "crypto/dh/libcrypto-lib-dh_key.o",
                            "crypto/dh/libcrypto-lib-dh_lib.o",
                            "crypto/dh/libcrypto-lib-dh_meth.o",
                            "crypto/dh/libcrypto-lib-dh_pmeth.o",
                            "crypto/dh/libcrypto-lib-dh_prn.o",
                            "crypto/dh/libcrypto-lib-dh_rfc5114.o",
                            "crypto/dh/libcrypto-lib-dh_rfc7919.o",
                            "crypto/dh/libcrypto-shlib-dh_ameth.o",
                            "crypto/dh/libcrypto-shlib-dh_asn1.o",
                            "crypto/dh/libcrypto-shlib-dh_check.o",
                            "crypto/dh/libcrypto-shlib-dh_depr.o",
                            "crypto/dh/libcrypto-shlib-dh_err.o",
                            "crypto/dh/libcrypto-shlib-dh_gen.o",
                            "crypto/dh/libcrypto-shlib-dh_kdf.o",
                            "crypto/dh/libcrypto-shlib-dh_key.o",
                            "crypto/dh/libcrypto-shlib-dh_lib.o",
                            "crypto/dh/libcrypto-shlib-dh_meth.o",
                            "crypto/dh/libcrypto-shlib-dh_pmeth.o",
                            "crypto/dh/libcrypto-shlib-dh_prn.o",
                            "crypto/dh/libcrypto-shlib-dh_rfc5114.o",
                            "crypto/dh/libcrypto-shlib-dh_rfc7919.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/dsa" =>
                {
                    "deps" =>
                        [
                            "crypto/dsa/libcrypto-lib-dsa_ameth.o",
                            "crypto/dsa/libcrypto-lib-dsa_asn1.o",
                            "crypto/dsa/libcrypto-lib-dsa_depr.o",
                            "crypto/dsa/libcrypto-lib-dsa_err.o",
                            "crypto/dsa/libcrypto-lib-dsa_gen.o",
                            "crypto/dsa/libcrypto-lib-dsa_key.o",
                            "crypto/dsa/libcrypto-lib-dsa_lib.o",
                            "crypto/dsa/libcrypto-lib-dsa_meth.o",
                            "crypto/dsa/libcrypto-lib-dsa_ossl.o",
                            "crypto/dsa/libcrypto-lib-dsa_pmeth.o",
                            "crypto/dsa/libcrypto-lib-dsa_prn.o",
                            "crypto/dsa/libcrypto-lib-dsa_sign.o",
                            "crypto/dsa/libcrypto-lib-dsa_vrf.o",
                            "crypto/dsa/libcrypto-shlib-dsa_ameth.o",
                            "crypto/dsa/libcrypto-shlib-dsa_asn1.o",
                            "crypto/dsa/libcrypto-shlib-dsa_depr.o",
                            "crypto/dsa/libcrypto-shlib-dsa_err.o",
                            "crypto/dsa/libcrypto-shlib-dsa_gen.o",
                            "crypto/dsa/libcrypto-shlib-dsa_key.o",
                            "crypto/dsa/libcrypto-shlib-dsa_lib.o",
                            "crypto/dsa/libcrypto-shlib-dsa_meth.o",
                            "crypto/dsa/libcrypto-shlib-dsa_ossl.o",
                            "crypto/dsa/libcrypto-shlib-dsa_pmeth.o",
                            "crypto/dsa/libcrypto-shlib-dsa_prn.o",
                            "crypto/dsa/libcrypto-shlib-dsa_sign.o",
                            "crypto/dsa/libcrypto-shlib-dsa_vrf.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/dso" =>
                {
                    "deps" =>
                        [
                            "crypto/dso/libcrypto-lib-dso_dl.o",
                            "crypto/dso/libcrypto-lib-dso_dlfcn.o",
                            "crypto/dso/libcrypto-lib-dso_err.o",
                            "crypto/dso/libcrypto-lib-dso_lib.o",
                            "crypto/dso/libcrypto-lib-dso_openssl.o",
                            "crypto/dso/libcrypto-lib-dso_vms.o",
                            "crypto/dso/libcrypto-lib-dso_win32.o",
                            "crypto/dso/libcrypto-shlib-dso_dl.o",
                            "crypto/dso/libcrypto-shlib-dso_dlfcn.o",
                            "crypto/dso/libcrypto-shlib-dso_err.o",
                            "crypto/dso/libcrypto-shlib-dso_lib.o",
                            "crypto/dso/libcrypto-shlib-dso_openssl.o",
                            "crypto/dso/libcrypto-shlib-dso_vms.o",
                            "crypto/dso/libcrypto-shlib-dso_win32.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ec" =>
                {
                    "deps" =>
                        [
                            "crypto/ec/libcrypto-lib-curve25519.o",
                            "crypto/ec/libcrypto-lib-ec2_oct.o",
                            "crypto/ec/libcrypto-lib-ec2_smpl.o",
                            "crypto/ec/libcrypto-lib-ec_ameth.o",
                            "crypto/ec/libcrypto-lib-ec_asn1.o",
                            "crypto/ec/libcrypto-lib-ec_check.o",
                            "crypto/ec/libcrypto-lib-ec_curve.o",
                            "crypto/ec/libcrypto-lib-ec_cvt.o",
                            "crypto/ec/libcrypto-lib-ec_err.o",
                            "crypto/ec/libcrypto-lib-ec_key.o",
                            "crypto/ec/libcrypto-lib-ec_kmeth.o",
                            "crypto/ec/libcrypto-lib-ec_lib.o",
                            "crypto/ec/libcrypto-lib-ec_mult.o",
                            "crypto/ec/libcrypto-lib-ec_oct.o",
                            "crypto/ec/libcrypto-lib-ec_pmeth.o",
                            "crypto/ec/libcrypto-lib-ec_print.o",
                            "crypto/ec/libcrypto-lib-ecdh_kdf.o",
                            "crypto/ec/libcrypto-lib-ecdh_ossl.o",
                            "crypto/ec/libcrypto-lib-ecdsa_ossl.o",
                            "crypto/ec/libcrypto-lib-ecdsa_sign.o",
                            "crypto/ec/libcrypto-lib-ecdsa_vrf.o",
                            "crypto/ec/libcrypto-lib-eck_prn.o",
                            "crypto/ec/libcrypto-lib-ecp_mont.o",
                            "crypto/ec/libcrypto-lib-ecp_nist.o",
                            "crypto/ec/libcrypto-lib-ecp_nistp224.o",
                            "crypto/ec/libcrypto-lib-ecp_nistp256.o",
                            "crypto/ec/libcrypto-lib-ecp_nistp521.o",
                            "crypto/ec/libcrypto-lib-ecp_nistputil.o",
                            "crypto/ec/libcrypto-lib-ecp_nistz256-x86_64.o",
                            "crypto/ec/libcrypto-lib-ecp_nistz256.o",
                            "crypto/ec/libcrypto-lib-ecp_oct.o",
                            "crypto/ec/libcrypto-lib-ecp_smpl.o",
                            "crypto/ec/libcrypto-lib-ecx_meth.o",
                            "crypto/ec/libcrypto-lib-x25519-x86_64.o",
                            "crypto/ec/libcrypto-shlib-curve25519.o",
                            "crypto/ec/libcrypto-shlib-ec2_oct.o",
                            "crypto/ec/libcrypto-shlib-ec2_smpl.o",
                            "crypto/ec/libcrypto-shlib-ec_ameth.o",
                            "crypto/ec/libcrypto-shlib-ec_asn1.o",
                            "crypto/ec/libcrypto-shlib-ec_check.o",
                            "crypto/ec/libcrypto-shlib-ec_curve.o",
                            "crypto/ec/libcrypto-shlib-ec_cvt.o",
                            "crypto/ec/libcrypto-shlib-ec_err.o",
                            "crypto/ec/libcrypto-shlib-ec_key.o",
                            "crypto/ec/libcrypto-shlib-ec_kmeth.o",
                            "crypto/ec/libcrypto-shlib-ec_lib.o",
                            "crypto/ec/libcrypto-shlib-ec_mult.o",
                            "crypto/ec/libcrypto-shlib-ec_oct.o",
                            "crypto/ec/libcrypto-shlib-ec_pmeth.o",
                            "crypto/ec/libcrypto-shlib-ec_print.o",
                            "crypto/ec/libcrypto-shlib-ecdh_kdf.o",
                            "crypto/ec/libcrypto-shlib-ecdh_ossl.o",
                            "crypto/ec/libcrypto-shlib-ecdsa_ossl.o",
                            "crypto/ec/libcrypto-shlib-ecdsa_sign.o",
                            "crypto/ec/libcrypto-shlib-ecdsa_vrf.o",
                            "crypto/ec/libcrypto-shlib-eck_prn.o",
                            "crypto/ec/libcrypto-shlib-ecp_mont.o",
                            "crypto/ec/libcrypto-shlib-ecp_nist.o",
                            "crypto/ec/libcrypto-shlib-ecp_nistp224.o",
                            "crypto/ec/libcrypto-shlib-ecp_nistp256.o",
                            "crypto/ec/libcrypto-shlib-ecp_nistp521.o",
                            "crypto/ec/libcrypto-shlib-ecp_nistputil.o",
                            "crypto/ec/libcrypto-shlib-ecp_nistz256-x86_64.o",
                            "crypto/ec/libcrypto-shlib-ecp_nistz256.o",
                            "crypto/ec/libcrypto-shlib-ecp_oct.o",
                            "crypto/ec/libcrypto-shlib-ecp_smpl.o",
                            "crypto/ec/libcrypto-shlib-ecx_meth.o",
                            "crypto/ec/libcrypto-shlib-x25519-x86_64.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ec/curve448" =>
                {
                    "deps" =>
                        [
                            "crypto/ec/curve448/libcrypto-lib-curve448.o",
                            "crypto/ec/curve448/libcrypto-lib-curve448_tables.o",
                            "crypto/ec/curve448/libcrypto-lib-eddsa.o",
                            "crypto/ec/curve448/libcrypto-lib-f_generic.o",
                            "crypto/ec/curve448/libcrypto-lib-scalar.o",
                            "crypto/ec/curve448/libcrypto-shlib-curve448.o",
                            "crypto/ec/curve448/libcrypto-shlib-curve448_tables.o",
                            "crypto/ec/curve448/libcrypto-shlib-eddsa.o",
                            "crypto/ec/curve448/libcrypto-shlib-f_generic.o",
                            "crypto/ec/curve448/libcrypto-shlib-scalar.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ec/curve448/arch_32" =>
                {
                    "deps" =>
                        [
                            "crypto/ec/curve448/arch_32/libcrypto-lib-f_impl.o",
                            "crypto/ec/curve448/arch_32/libcrypto-shlib-f_impl.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/engine" =>
                {
                    "deps" =>
                        [
                            "crypto/engine/libcrypto-lib-eng_all.o",
                            "crypto/engine/libcrypto-lib-eng_cnf.o",
                            "crypto/engine/libcrypto-lib-eng_ctrl.o",
                            "crypto/engine/libcrypto-lib-eng_dyn.o",
                            "crypto/engine/libcrypto-lib-eng_err.o",
                            "crypto/engine/libcrypto-lib-eng_fat.o",
                            "crypto/engine/libcrypto-lib-eng_init.o",
                            "crypto/engine/libcrypto-lib-eng_lib.o",
                            "crypto/engine/libcrypto-lib-eng_list.o",
                            "crypto/engine/libcrypto-lib-eng_openssl.o",
                            "crypto/engine/libcrypto-lib-eng_pkey.o",
                            "crypto/engine/libcrypto-lib-eng_rdrand.o",
                            "crypto/engine/libcrypto-lib-eng_table.o",
                            "crypto/engine/libcrypto-lib-tb_asnmth.o",
                            "crypto/engine/libcrypto-lib-tb_cipher.o",
                            "crypto/engine/libcrypto-lib-tb_dh.o",
                            "crypto/engine/libcrypto-lib-tb_digest.o",
                            "crypto/engine/libcrypto-lib-tb_dsa.o",
                            "crypto/engine/libcrypto-lib-tb_eckey.o",
                            "crypto/engine/libcrypto-lib-tb_pkmeth.o",
                            "crypto/engine/libcrypto-lib-tb_rand.o",
                            "crypto/engine/libcrypto-lib-tb_rsa.o",
                            "crypto/engine/libcrypto-shlib-eng_all.o",
                            "crypto/engine/libcrypto-shlib-eng_cnf.o",
                            "crypto/engine/libcrypto-shlib-eng_ctrl.o",
                            "crypto/engine/libcrypto-shlib-eng_dyn.o",
                            "crypto/engine/libcrypto-shlib-eng_err.o",
                            "crypto/engine/libcrypto-shlib-eng_fat.o",
                            "crypto/engine/libcrypto-shlib-eng_init.o",
                            "crypto/engine/libcrypto-shlib-eng_lib.o",
                            "crypto/engine/libcrypto-shlib-eng_list.o",
                            "crypto/engine/libcrypto-shlib-eng_openssl.o",
                            "crypto/engine/libcrypto-shlib-eng_pkey.o",
                            "crypto/engine/libcrypto-shlib-eng_rdrand.o",
                            "crypto/engine/libcrypto-shlib-eng_table.o",
                            "crypto/engine/libcrypto-shlib-tb_asnmth.o",
                            "crypto/engine/libcrypto-shlib-tb_cipher.o",
                            "crypto/engine/libcrypto-shlib-tb_dh.o",
                            "crypto/engine/libcrypto-shlib-tb_digest.o",
                            "crypto/engine/libcrypto-shlib-tb_dsa.o",
                            "crypto/engine/libcrypto-shlib-tb_eckey.o",
                            "crypto/engine/libcrypto-shlib-tb_pkmeth.o",
                            "crypto/engine/libcrypto-shlib-tb_rand.o",
                            "crypto/engine/libcrypto-shlib-tb_rsa.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/err" =>
                {
                    "deps" =>
                        [
                            "crypto/err/libcrypto-lib-err.o",
                            "crypto/err/libcrypto-lib-err_all.o",
                            "crypto/err/libcrypto-lib-err_prn.o",
                            "crypto/err/libcrypto-shlib-err.o",
                            "crypto/err/libcrypto-shlib-err_all.o",
                            "crypto/err/libcrypto-shlib-err_prn.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ess" =>
                {
                    "deps" =>
                        [
                            "crypto/ess/libcrypto-lib-ess_asn1.o",
                            "crypto/ess/libcrypto-lib-ess_err.o",
                            "crypto/ess/libcrypto-lib-ess_lib.o",
                            "crypto/ess/libcrypto-shlib-ess_asn1.o",
                            "crypto/ess/libcrypto-shlib-ess_err.o",
                            "crypto/ess/libcrypto-shlib-ess_lib.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/evp" =>
                {
                    "deps" =>
                        [
                            "crypto/evp/libcrypto-lib-bio_b64.o",
                            "crypto/evp/libcrypto-lib-bio_enc.o",
                            "crypto/evp/libcrypto-lib-bio_md.o",
                            "crypto/evp/libcrypto-lib-bio_ok.o",
                            "crypto/evp/libcrypto-lib-c_allc.o",
                            "crypto/evp/libcrypto-lib-c_alld.o",
                            "crypto/evp/libcrypto-lib-c_allm.o",
                            "crypto/evp/libcrypto-lib-cmeth_lib.o",
                            "crypto/evp/libcrypto-lib-digest.o",
                            "crypto/evp/libcrypto-lib-e_aes.o",
                            "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha1.o",
                            "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha256.o",
                            "crypto/evp/libcrypto-lib-e_aria.o",
                            "crypto/evp/libcrypto-lib-e_bf.o",
                            "crypto/evp/libcrypto-lib-e_camellia.o",
                            "crypto/evp/libcrypto-lib-e_cast.o",
                            "crypto/evp/libcrypto-lib-e_chacha20_poly1305.o",
                            "crypto/evp/libcrypto-lib-e_des.o",
                            "crypto/evp/libcrypto-lib-e_des3.o",
                            "crypto/evp/libcrypto-lib-e_idea.o",
                            "crypto/evp/libcrypto-lib-e_null.o",
                            "crypto/evp/libcrypto-lib-e_old.o",
                            "crypto/evp/libcrypto-lib-e_rc2.o",
                            "crypto/evp/libcrypto-lib-e_rc4.o",
                            "crypto/evp/libcrypto-lib-e_rc4_hmac_md5.o",
                            "crypto/evp/libcrypto-lib-e_rc5.o",
                            "crypto/evp/libcrypto-lib-e_seed.o",
                            "crypto/evp/libcrypto-lib-e_sm4.o",
                            "crypto/evp/libcrypto-lib-e_xcbc_d.o",
                            "crypto/evp/libcrypto-lib-encode.o",
                            "crypto/evp/libcrypto-lib-evp_cnf.o",
                            "crypto/evp/libcrypto-lib-evp_enc.o",
                            "crypto/evp/libcrypto-lib-evp_err.o",
                            "crypto/evp/libcrypto-lib-evp_fetch.o",
                            "crypto/evp/libcrypto-lib-evp_key.o",
                            "crypto/evp/libcrypto-lib-evp_lib.o",
                            "crypto/evp/libcrypto-lib-evp_pbe.o",
                            "crypto/evp/libcrypto-lib-evp_pkey.o",
                            "crypto/evp/libcrypto-lib-kdf_lib.o",
                            "crypto/evp/libcrypto-lib-m_md2.o",
                            "crypto/evp/libcrypto-lib-m_md4.o",
                            "crypto/evp/libcrypto-lib-m_md5.o",
                            "crypto/evp/libcrypto-lib-m_md5_sha1.o",
                            "crypto/evp/libcrypto-lib-m_mdc2.o",
                            "crypto/evp/libcrypto-lib-m_null.o",
                            "crypto/evp/libcrypto-lib-m_ripemd.o",
                            "crypto/evp/libcrypto-lib-m_sha1.o",
                            "crypto/evp/libcrypto-lib-m_sha3.o",
                            "crypto/evp/libcrypto-lib-m_sigver.o",
                            "crypto/evp/libcrypto-lib-m_wp.o",
                            "crypto/evp/libcrypto-lib-mac_lib.o",
                            "crypto/evp/libcrypto-lib-names.o",
                            "crypto/evp/libcrypto-lib-p5_crpt.o",
                            "crypto/evp/libcrypto-lib-p5_crpt2.o",
                            "crypto/evp/libcrypto-lib-p_dec.o",
                            "crypto/evp/libcrypto-lib-p_enc.o",
                            "crypto/evp/libcrypto-lib-p_lib.o",
                            "crypto/evp/libcrypto-lib-p_open.o",
                            "crypto/evp/libcrypto-lib-p_seal.o",
                            "crypto/evp/libcrypto-lib-p_sign.o",
                            "crypto/evp/libcrypto-lib-p_verify.o",
                            "crypto/evp/libcrypto-lib-pbe_scrypt.o",
                            "crypto/evp/libcrypto-lib-pkey_kdf.o",
                            "crypto/evp/libcrypto-lib-pkey_mac.o",
                            "crypto/evp/libcrypto-lib-pmeth_fn.o",
                            "crypto/evp/libcrypto-lib-pmeth_gn.o",
                            "crypto/evp/libcrypto-lib-pmeth_lib.o",
                            "crypto/evp/libcrypto-shlib-bio_b64.o",
                            "crypto/evp/libcrypto-shlib-bio_enc.o",
                            "crypto/evp/libcrypto-shlib-bio_md.o",
                            "crypto/evp/libcrypto-shlib-bio_ok.o",
                            "crypto/evp/libcrypto-shlib-c_allc.o",
                            "crypto/evp/libcrypto-shlib-c_alld.o",
                            "crypto/evp/libcrypto-shlib-c_allm.o",
                            "crypto/evp/libcrypto-shlib-cmeth_lib.o",
                            "crypto/evp/libcrypto-shlib-digest.o",
                            "crypto/evp/libcrypto-shlib-e_aes.o",
                            "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha1.o",
                            "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha256.o",
                            "crypto/evp/libcrypto-shlib-e_aria.o",
                            "crypto/evp/libcrypto-shlib-e_bf.o",
                            "crypto/evp/libcrypto-shlib-e_camellia.o",
                            "crypto/evp/libcrypto-shlib-e_cast.o",
                            "crypto/evp/libcrypto-shlib-e_chacha20_poly1305.o",
                            "crypto/evp/libcrypto-shlib-e_des.o",
                            "crypto/evp/libcrypto-shlib-e_des3.o",
                            "crypto/evp/libcrypto-shlib-e_idea.o",
                            "crypto/evp/libcrypto-shlib-e_null.o",
                            "crypto/evp/libcrypto-shlib-e_old.o",
                            "crypto/evp/libcrypto-shlib-e_rc2.o",
                            "crypto/evp/libcrypto-shlib-e_rc4.o",
                            "crypto/evp/libcrypto-shlib-e_rc4_hmac_md5.o",
                            "crypto/evp/libcrypto-shlib-e_rc5.o",
                            "crypto/evp/libcrypto-shlib-e_seed.o",
                            "crypto/evp/libcrypto-shlib-e_sm4.o",
                            "crypto/evp/libcrypto-shlib-e_xcbc_d.o",
                            "crypto/evp/libcrypto-shlib-encode.o",
                            "crypto/evp/libcrypto-shlib-evp_cnf.o",
                            "crypto/evp/libcrypto-shlib-evp_enc.o",
                            "crypto/evp/libcrypto-shlib-evp_err.o",
                            "crypto/evp/libcrypto-shlib-evp_fetch.o",
                            "crypto/evp/libcrypto-shlib-evp_key.o",
                            "crypto/evp/libcrypto-shlib-evp_lib.o",
                            "crypto/evp/libcrypto-shlib-evp_pbe.o",
                            "crypto/evp/libcrypto-shlib-evp_pkey.o",
                            "crypto/evp/libcrypto-shlib-kdf_lib.o",
                            "crypto/evp/libcrypto-shlib-m_md2.o",
                            "crypto/evp/libcrypto-shlib-m_md4.o",
                            "crypto/evp/libcrypto-shlib-m_md5.o",
                            "crypto/evp/libcrypto-shlib-m_md5_sha1.o",
                            "crypto/evp/libcrypto-shlib-m_mdc2.o",
                            "crypto/evp/libcrypto-shlib-m_null.o",
                            "crypto/evp/libcrypto-shlib-m_ripemd.o",
                            "crypto/evp/libcrypto-shlib-m_sha1.o",
                            "crypto/evp/libcrypto-shlib-m_sha3.o",
                            "crypto/evp/libcrypto-shlib-m_sigver.o",
                            "crypto/evp/libcrypto-shlib-m_wp.o",
                            "crypto/evp/libcrypto-shlib-mac_lib.o",
                            "crypto/evp/libcrypto-shlib-names.o",
                            "crypto/evp/libcrypto-shlib-p5_crpt.o",
                            "crypto/evp/libcrypto-shlib-p5_crpt2.o",
                            "crypto/evp/libcrypto-shlib-p_dec.o",
                            "crypto/evp/libcrypto-shlib-p_enc.o",
                            "crypto/evp/libcrypto-shlib-p_lib.o",
                            "crypto/evp/libcrypto-shlib-p_open.o",
                            "crypto/evp/libcrypto-shlib-p_seal.o",
                            "crypto/evp/libcrypto-shlib-p_sign.o",
                            "crypto/evp/libcrypto-shlib-p_verify.o",
                            "crypto/evp/libcrypto-shlib-pbe_scrypt.o",
                            "crypto/evp/libcrypto-shlib-pkey_kdf.o",
                            "crypto/evp/libcrypto-shlib-pkey_mac.o",
                            "crypto/evp/libcrypto-shlib-pmeth_fn.o",
                            "crypto/evp/libcrypto-shlib-pmeth_gn.o",
                            "crypto/evp/libcrypto-shlib-pmeth_lib.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/gmac" =>
                {
                    "deps" =>
                        [
                            "crypto/gmac/libcrypto-lib-gmac.o",
                            "crypto/gmac/libcrypto-shlib-gmac.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/hmac" =>
                {
                    "deps" =>
                        [
                            "crypto/hmac/libcrypto-lib-hm_ameth.o",
                            "crypto/hmac/libcrypto-lib-hm_meth.o",
                            "crypto/hmac/libcrypto-lib-hmac.o",
                            "crypto/hmac/libcrypto-shlib-hm_ameth.o",
                            "crypto/hmac/libcrypto-shlib-hm_meth.o",
                            "crypto/hmac/libcrypto-shlib-hmac.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/idea" =>
                {
                    "deps" =>
                        [
                            "crypto/idea/libcrypto-lib-i_cbc.o",
                            "crypto/idea/libcrypto-lib-i_cfb64.o",
                            "crypto/idea/libcrypto-lib-i_ecb.o",
                            "crypto/idea/libcrypto-lib-i_ofb64.o",
                            "crypto/idea/libcrypto-lib-i_skey.o",
                            "crypto/idea/libcrypto-shlib-i_cbc.o",
                            "crypto/idea/libcrypto-shlib-i_cfb64.o",
                            "crypto/idea/libcrypto-shlib-i_ecb.o",
                            "crypto/idea/libcrypto-shlib-i_ofb64.o",
                            "crypto/idea/libcrypto-shlib-i_skey.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/kdf" =>
                {
                    "deps" =>
                        [
                            "crypto/kdf/libcrypto-lib-hkdf.o",
                            "crypto/kdf/libcrypto-lib-kdf_err.o",
                            "crypto/kdf/libcrypto-lib-kdf_util.o",
                            "crypto/kdf/libcrypto-lib-pbkdf2.o",
                            "crypto/kdf/libcrypto-lib-scrypt.o",
                            "crypto/kdf/libcrypto-lib-sshkdf.o",
                            "crypto/kdf/libcrypto-lib-sskdf.o",
                            "crypto/kdf/libcrypto-lib-tls1_prf.o",
                            "crypto/kdf/libcrypto-shlib-hkdf.o",
                            "crypto/kdf/libcrypto-shlib-kdf_err.o",
                            "crypto/kdf/libcrypto-shlib-kdf_util.o",
                            "crypto/kdf/libcrypto-shlib-pbkdf2.o",
                            "crypto/kdf/libcrypto-shlib-scrypt.o",
                            "crypto/kdf/libcrypto-shlib-sshkdf.o",
                            "crypto/kdf/libcrypto-shlib-sskdf.o",
                            "crypto/kdf/libcrypto-shlib-tls1_prf.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/kmac" =>
                {
                    "deps" =>
                        [
                            "crypto/kmac/libcrypto-lib-kmac.o",
                            "crypto/kmac/libcrypto-shlib-kmac.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/lhash" =>
                {
                    "deps" =>
                        [
                            "crypto/lhash/libcrypto-lib-lh_stats.o",
                            "crypto/lhash/libcrypto-lib-lhash.o",
                            "crypto/lhash/libcrypto-shlib-lh_stats.o",
                            "crypto/lhash/libcrypto-shlib-lhash.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/md4" =>
                {
                    "deps" =>
                        [
                            "crypto/md4/libcrypto-lib-md4_dgst.o",
                            "crypto/md4/libcrypto-lib-md4_one.o",
                            "crypto/md4/libcrypto-shlib-md4_dgst.o",
                            "crypto/md4/libcrypto-shlib-md4_one.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/md5" =>
                {
                    "deps" =>
                        [
                            "crypto/md5/libcrypto-lib-md5-x86_64.o",
                            "crypto/md5/libcrypto-lib-md5_dgst.o",
                            "crypto/md5/libcrypto-lib-md5_one.o",
                            "crypto/md5/libcrypto-shlib-md5-x86_64.o",
                            "crypto/md5/libcrypto-shlib-md5_dgst.o",
                            "crypto/md5/libcrypto-shlib-md5_one.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/mdc2" =>
                {
                    "deps" =>
                        [
                            "crypto/mdc2/libcrypto-lib-mdc2_one.o",
                            "crypto/mdc2/libcrypto-lib-mdc2dgst.o",
                            "crypto/mdc2/libcrypto-shlib-mdc2_one.o",
                            "crypto/mdc2/libcrypto-shlib-mdc2dgst.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/modes" =>
                {
                    "deps" =>
                        [
                            "crypto/modes/libcrypto-lib-aesni-gcm-x86_64.o",
                            "crypto/modes/libcrypto-lib-cbc128.o",
                            "crypto/modes/libcrypto-lib-ccm128.o",
                            "crypto/modes/libcrypto-lib-cfb128.o",
                            "crypto/modes/libcrypto-lib-ctr128.o",
                            "crypto/modes/libcrypto-lib-cts128.o",
                            "crypto/modes/libcrypto-lib-gcm128.o",
                            "crypto/modes/libcrypto-lib-ghash-x86_64.o",
                            "crypto/modes/libcrypto-lib-ocb128.o",
                            "crypto/modes/libcrypto-lib-ofb128.o",
                            "crypto/modes/libcrypto-lib-siv128.o",
                            "crypto/modes/libcrypto-lib-wrap128.o",
                            "crypto/modes/libcrypto-lib-xts128.o",
                            "crypto/modes/libcrypto-shlib-aesni-gcm-x86_64.o",
                            "crypto/modes/libcrypto-shlib-cbc128.o",
                            "crypto/modes/libcrypto-shlib-ccm128.o",
                            "crypto/modes/libcrypto-shlib-cfb128.o",
                            "crypto/modes/libcrypto-shlib-ctr128.o",
                            "crypto/modes/libcrypto-shlib-cts128.o",
                            "crypto/modes/libcrypto-shlib-gcm128.o",
                            "crypto/modes/libcrypto-shlib-ghash-x86_64.o",
                            "crypto/modes/libcrypto-shlib-ocb128.o",
                            "crypto/modes/libcrypto-shlib-ofb128.o",
                            "crypto/modes/libcrypto-shlib-siv128.o",
                            "crypto/modes/libcrypto-shlib-wrap128.o",
                            "crypto/modes/libcrypto-shlib-xts128.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/objects" =>
                {
                    "deps" =>
                        [
                            "crypto/objects/libcrypto-lib-o_names.o",
                            "crypto/objects/libcrypto-lib-obj_dat.o",
                            "crypto/objects/libcrypto-lib-obj_err.o",
                            "crypto/objects/libcrypto-lib-obj_lib.o",
                            "crypto/objects/libcrypto-lib-obj_xref.o",
                            "crypto/objects/libcrypto-shlib-o_names.o",
                            "crypto/objects/libcrypto-shlib-obj_dat.o",
                            "crypto/objects/libcrypto-shlib-obj_err.o",
                            "crypto/objects/libcrypto-shlib-obj_lib.o",
                            "crypto/objects/libcrypto-shlib-obj_xref.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ocsp" =>
                {
                    "deps" =>
                        [
                            "crypto/ocsp/libcrypto-lib-ocsp_asn.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_cl.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_err.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_ext.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_ht.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_lib.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_prn.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_srv.o",
                            "crypto/ocsp/libcrypto-lib-ocsp_vfy.o",
                            "crypto/ocsp/libcrypto-lib-v3_ocsp.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_asn.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_cl.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_err.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_ext.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_ht.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_lib.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_prn.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_srv.o",
                            "crypto/ocsp/libcrypto-shlib-ocsp_vfy.o",
                            "crypto/ocsp/libcrypto-shlib-v3_ocsp.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/pem" =>
                {
                    "deps" =>
                        [
                            "crypto/pem/libcrypto-lib-pem_all.o",
                            "crypto/pem/libcrypto-lib-pem_err.o",
                            "crypto/pem/libcrypto-lib-pem_info.o",
                            "crypto/pem/libcrypto-lib-pem_lib.o",
                            "crypto/pem/libcrypto-lib-pem_oth.o",
                            "crypto/pem/libcrypto-lib-pem_pk8.o",
                            "crypto/pem/libcrypto-lib-pem_pkey.o",
                            "crypto/pem/libcrypto-lib-pem_sign.o",
                            "crypto/pem/libcrypto-lib-pem_x509.o",
                            "crypto/pem/libcrypto-lib-pem_xaux.o",
                            "crypto/pem/libcrypto-lib-pvkfmt.o",
                            "crypto/pem/libcrypto-shlib-pem_all.o",
                            "crypto/pem/libcrypto-shlib-pem_err.o",
                            "crypto/pem/libcrypto-shlib-pem_info.o",
                            "crypto/pem/libcrypto-shlib-pem_lib.o",
                            "crypto/pem/libcrypto-shlib-pem_oth.o",
                            "crypto/pem/libcrypto-shlib-pem_pk8.o",
                            "crypto/pem/libcrypto-shlib-pem_pkey.o",
                            "crypto/pem/libcrypto-shlib-pem_sign.o",
                            "crypto/pem/libcrypto-shlib-pem_x509.o",
                            "crypto/pem/libcrypto-shlib-pem_xaux.o",
                            "crypto/pem/libcrypto-shlib-pvkfmt.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/pkcs12" =>
                {
                    "deps" =>
                        [
                            "crypto/pkcs12/libcrypto-lib-p12_add.o",
                            "crypto/pkcs12/libcrypto-lib-p12_asn.o",
                            "crypto/pkcs12/libcrypto-lib-p12_attr.o",
                            "crypto/pkcs12/libcrypto-lib-p12_crpt.o",
                            "crypto/pkcs12/libcrypto-lib-p12_crt.o",
                            "crypto/pkcs12/libcrypto-lib-p12_decr.o",
                            "crypto/pkcs12/libcrypto-lib-p12_init.o",
                            "crypto/pkcs12/libcrypto-lib-p12_key.o",
                            "crypto/pkcs12/libcrypto-lib-p12_kiss.o",
                            "crypto/pkcs12/libcrypto-lib-p12_mutl.o",
                            "crypto/pkcs12/libcrypto-lib-p12_npas.o",
                            "crypto/pkcs12/libcrypto-lib-p12_p8d.o",
                            "crypto/pkcs12/libcrypto-lib-p12_p8e.o",
                            "crypto/pkcs12/libcrypto-lib-p12_sbag.o",
                            "crypto/pkcs12/libcrypto-lib-p12_utl.o",
                            "crypto/pkcs12/libcrypto-lib-pk12err.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_add.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_asn.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_attr.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_crpt.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_crt.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_decr.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_init.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_key.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_kiss.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_mutl.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_npas.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_p8d.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_p8e.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_sbag.o",
                            "crypto/pkcs12/libcrypto-shlib-p12_utl.o",
                            "crypto/pkcs12/libcrypto-shlib-pk12err.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/pkcs7" =>
                {
                    "deps" =>
                        [
                            "crypto/pkcs7/libcrypto-lib-bio_pk7.o",
                            "crypto/pkcs7/libcrypto-lib-pk7_asn1.o",
                            "crypto/pkcs7/libcrypto-lib-pk7_attr.o",
                            "crypto/pkcs7/libcrypto-lib-pk7_doit.o",
                            "crypto/pkcs7/libcrypto-lib-pk7_lib.o",
                            "crypto/pkcs7/libcrypto-lib-pk7_mime.o",
                            "crypto/pkcs7/libcrypto-lib-pk7_smime.o",
                            "crypto/pkcs7/libcrypto-lib-pkcs7err.o",
                            "crypto/pkcs7/libcrypto-shlib-bio_pk7.o",
                            "crypto/pkcs7/libcrypto-shlib-pk7_asn1.o",
                            "crypto/pkcs7/libcrypto-shlib-pk7_attr.o",
                            "crypto/pkcs7/libcrypto-shlib-pk7_doit.o",
                            "crypto/pkcs7/libcrypto-shlib-pk7_lib.o",
                            "crypto/pkcs7/libcrypto-shlib-pk7_mime.o",
                            "crypto/pkcs7/libcrypto-shlib-pk7_smime.o",
                            "crypto/pkcs7/libcrypto-shlib-pkcs7err.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/poly1305" =>
                {
                    "deps" =>
                        [
                            "crypto/poly1305/libcrypto-lib-poly1305-x86_64.o",
                            "crypto/poly1305/libcrypto-lib-poly1305.o",
                            "crypto/poly1305/libcrypto-lib-poly1305_ameth.o",
                            "crypto/poly1305/libcrypto-lib-poly1305_meth.o",
                            "crypto/poly1305/libcrypto-shlib-poly1305-x86_64.o",
                            "crypto/poly1305/libcrypto-shlib-poly1305.o",
                            "crypto/poly1305/libcrypto-shlib-poly1305_ameth.o",
                            "crypto/poly1305/libcrypto-shlib-poly1305_meth.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/property" =>
                {
                    "deps" =>
                        [
                            "crypto/property/libcrypto-lib-defn_cache.o",
                            "crypto/property/libcrypto-lib-property.o",
                            "crypto/property/libcrypto-lib-property_err.o",
                            "crypto/property/libcrypto-lib-property_parse.o",
                            "crypto/property/libcrypto-lib-property_string.o",
                            "crypto/property/libcrypto-shlib-defn_cache.o",
                            "crypto/property/libcrypto-shlib-property.o",
                            "crypto/property/libcrypto-shlib-property_err.o",
                            "crypto/property/libcrypto-shlib-property_parse.o",
                            "crypto/property/libcrypto-shlib-property_string.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/rand" =>
                {
                    "deps" =>
                        [
                            "crypto/rand/libcrypto-lib-drbg_ctr.o",
                            "crypto/rand/libcrypto-lib-drbg_hash.o",
                            "crypto/rand/libcrypto-lib-drbg_hmac.o",
                            "crypto/rand/libcrypto-lib-drbg_lib.o",
                            "crypto/rand/libcrypto-lib-rand_crng_test.o",
                            "crypto/rand/libcrypto-lib-rand_egd.o",
                            "crypto/rand/libcrypto-lib-rand_err.o",
                            "crypto/rand/libcrypto-lib-rand_lib.o",
                            "crypto/rand/libcrypto-lib-rand_unix.o",
                            "crypto/rand/libcrypto-lib-rand_vms.o",
                            "crypto/rand/libcrypto-lib-rand_win.o",
                            "crypto/rand/libcrypto-lib-randfile.o",
                            "crypto/rand/libcrypto-shlib-drbg_ctr.o",
                            "crypto/rand/libcrypto-shlib-drbg_hash.o",
                            "crypto/rand/libcrypto-shlib-drbg_hmac.o",
                            "crypto/rand/libcrypto-shlib-drbg_lib.o",
                            "crypto/rand/libcrypto-shlib-rand_crng_test.o",
                            "crypto/rand/libcrypto-shlib-rand_egd.o",
                            "crypto/rand/libcrypto-shlib-rand_err.o",
                            "crypto/rand/libcrypto-shlib-rand_lib.o",
                            "crypto/rand/libcrypto-shlib-rand_unix.o",
                            "crypto/rand/libcrypto-shlib-rand_vms.o",
                            "crypto/rand/libcrypto-shlib-rand_win.o",
                            "crypto/rand/libcrypto-shlib-randfile.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/rc2" =>
                {
                    "deps" =>
                        [
                            "crypto/rc2/libcrypto-lib-rc2_cbc.o",
                            "crypto/rc2/libcrypto-lib-rc2_ecb.o",
                            "crypto/rc2/libcrypto-lib-rc2_skey.o",
                            "crypto/rc2/libcrypto-lib-rc2cfb64.o",
                            "crypto/rc2/libcrypto-lib-rc2ofb64.o",
                            "crypto/rc2/libcrypto-shlib-rc2_cbc.o",
                            "crypto/rc2/libcrypto-shlib-rc2_ecb.o",
                            "crypto/rc2/libcrypto-shlib-rc2_skey.o",
                            "crypto/rc2/libcrypto-shlib-rc2cfb64.o",
                            "crypto/rc2/libcrypto-shlib-rc2ofb64.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/rc4" =>
                {
                    "deps" =>
                        [
                            "crypto/rc4/libcrypto-lib-rc4-md5-x86_64.o",
                            "crypto/rc4/libcrypto-lib-rc4-x86_64.o",
                            "crypto/rc4/libcrypto-shlib-rc4-md5-x86_64.o",
                            "crypto/rc4/libcrypto-shlib-rc4-x86_64.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ripemd" =>
                {
                    "deps" =>
                        [
                            "crypto/ripemd/libcrypto-lib-rmd_dgst.o",
                            "crypto/ripemd/libcrypto-lib-rmd_one.o",
                            "crypto/ripemd/libcrypto-shlib-rmd_dgst.o",
                            "crypto/ripemd/libcrypto-shlib-rmd_one.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/rsa" =>
                {
                    "deps" =>
                        [
                            "crypto/rsa/libcrypto-lib-rsa_ameth.o",
                            "crypto/rsa/libcrypto-lib-rsa_asn1.o",
                            "crypto/rsa/libcrypto-lib-rsa_chk.o",
                            "crypto/rsa/libcrypto-lib-rsa_crpt.o",
                            "crypto/rsa/libcrypto-lib-rsa_depr.o",
                            "crypto/rsa/libcrypto-lib-rsa_err.o",
                            "crypto/rsa/libcrypto-lib-rsa_gen.o",
                            "crypto/rsa/libcrypto-lib-rsa_lib.o",
                            "crypto/rsa/libcrypto-lib-rsa_meth.o",
                            "crypto/rsa/libcrypto-lib-rsa_mp.o",
                            "crypto/rsa/libcrypto-lib-rsa_none.o",
                            "crypto/rsa/libcrypto-lib-rsa_oaep.o",
                            "crypto/rsa/libcrypto-lib-rsa_ossl.o",
                            "crypto/rsa/libcrypto-lib-rsa_pk1.o",
                            "crypto/rsa/libcrypto-lib-rsa_pmeth.o",
                            "crypto/rsa/libcrypto-lib-rsa_prn.o",
                            "crypto/rsa/libcrypto-lib-rsa_pss.o",
                            "crypto/rsa/libcrypto-lib-rsa_saos.o",
                            "crypto/rsa/libcrypto-lib-rsa_sign.o",
                            "crypto/rsa/libcrypto-lib-rsa_sp800_56b_check.o",
                            "crypto/rsa/libcrypto-lib-rsa_sp800_56b_gen.o",
                            "crypto/rsa/libcrypto-lib-rsa_ssl.o",
                            "crypto/rsa/libcrypto-lib-rsa_x931.o",
                            "crypto/rsa/libcrypto-lib-rsa_x931g.o",
                            "crypto/rsa/libcrypto-shlib-rsa_ameth.o",
                            "crypto/rsa/libcrypto-shlib-rsa_asn1.o",
                            "crypto/rsa/libcrypto-shlib-rsa_chk.o",
                            "crypto/rsa/libcrypto-shlib-rsa_crpt.o",
                            "crypto/rsa/libcrypto-shlib-rsa_depr.o",
                            "crypto/rsa/libcrypto-shlib-rsa_err.o",
                            "crypto/rsa/libcrypto-shlib-rsa_gen.o",
                            "crypto/rsa/libcrypto-shlib-rsa_lib.o",
                            "crypto/rsa/libcrypto-shlib-rsa_meth.o",
                            "crypto/rsa/libcrypto-shlib-rsa_mp.o",
                            "crypto/rsa/libcrypto-shlib-rsa_none.o",
                            "crypto/rsa/libcrypto-shlib-rsa_oaep.o",
                            "crypto/rsa/libcrypto-shlib-rsa_ossl.o",
                            "crypto/rsa/libcrypto-shlib-rsa_pk1.o",
                            "crypto/rsa/libcrypto-shlib-rsa_pmeth.o",
                            "crypto/rsa/libcrypto-shlib-rsa_prn.o",
                            "crypto/rsa/libcrypto-shlib-rsa_pss.o",
                            "crypto/rsa/libcrypto-shlib-rsa_saos.o",
                            "crypto/rsa/libcrypto-shlib-rsa_sign.o",
                            "crypto/rsa/libcrypto-shlib-rsa_sp800_56b_check.o",
                            "crypto/rsa/libcrypto-shlib-rsa_sp800_56b_gen.o",
                            "crypto/rsa/libcrypto-shlib-rsa_ssl.o",
                            "crypto/rsa/libcrypto-shlib-rsa_x931.o",
                            "crypto/rsa/libcrypto-shlib-rsa_x931g.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/seed" =>
                {
                    "deps" =>
                        [
                            "crypto/seed/libcrypto-lib-seed.o",
                            "crypto/seed/libcrypto-lib-seed_cbc.o",
                            "crypto/seed/libcrypto-lib-seed_cfb.o",
                            "crypto/seed/libcrypto-lib-seed_ecb.o",
                            "crypto/seed/libcrypto-lib-seed_ofb.o",
                            "crypto/seed/libcrypto-shlib-seed.o",
                            "crypto/seed/libcrypto-shlib-seed_cbc.o",
                            "crypto/seed/libcrypto-shlib-seed_cfb.o",
                            "crypto/seed/libcrypto-shlib-seed_ecb.o",
                            "crypto/seed/libcrypto-shlib-seed_ofb.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/sha" =>
                {
                    "deps" =>
                        [
                            "crypto/sha/fips-dso-sha256.o",
                            "crypto/sha/libcrypto-lib-keccak1600-x86_64.o",
                            "crypto/sha/libcrypto-lib-sha1-mb-x86_64.o",
                            "crypto/sha/libcrypto-lib-sha1-x86_64.o",
                            "crypto/sha/libcrypto-lib-sha1_one.o",
                            "crypto/sha/libcrypto-lib-sha1dgst.o",
                            "crypto/sha/libcrypto-lib-sha256-mb-x86_64.o",
                            "crypto/sha/libcrypto-lib-sha256-x86_64.o",
                            "crypto/sha/libcrypto-lib-sha256.o",
                            "crypto/sha/libcrypto-lib-sha512-x86_64.o",
                            "crypto/sha/libcrypto-lib-sha512.o",
                            "crypto/sha/libcrypto-shlib-keccak1600-x86_64.o",
                            "crypto/sha/libcrypto-shlib-sha1-mb-x86_64.o",
                            "crypto/sha/libcrypto-shlib-sha1-x86_64.o",
                            "crypto/sha/libcrypto-shlib-sha1_one.o",
                            "crypto/sha/libcrypto-shlib-sha1dgst.o",
                            "crypto/sha/libcrypto-shlib-sha256-mb-x86_64.o",
                            "crypto/sha/libcrypto-shlib-sha256-x86_64.o",
                            "crypto/sha/libcrypto-shlib-sha256.o",
                            "crypto/sha/libcrypto-shlib-sha512-x86_64.o",
                            "crypto/sha/libcrypto-shlib-sha512.o",
                        ],
                    "products" =>
                        {
                            "dso" =>
                                [
                                    "providers/fips",
                                ],
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/siphash" =>
                {
                    "deps" =>
                        [
                            "crypto/siphash/libcrypto-lib-siphash.o",
                            "crypto/siphash/libcrypto-lib-siphash_ameth.o",
                            "crypto/siphash/libcrypto-lib-siphash_meth.o",
                            "crypto/siphash/libcrypto-shlib-siphash.o",
                            "crypto/siphash/libcrypto-shlib-siphash_ameth.o",
                            "crypto/siphash/libcrypto-shlib-siphash_meth.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/sm2" =>
                {
                    "deps" =>
                        [
                            "crypto/sm2/libcrypto-lib-sm2_crypt.o",
                            "crypto/sm2/libcrypto-lib-sm2_err.o",
                            "crypto/sm2/libcrypto-lib-sm2_pmeth.o",
                            "crypto/sm2/libcrypto-lib-sm2_sign.o",
                            "crypto/sm2/libcrypto-shlib-sm2_crypt.o",
                            "crypto/sm2/libcrypto-shlib-sm2_err.o",
                            "crypto/sm2/libcrypto-shlib-sm2_pmeth.o",
                            "crypto/sm2/libcrypto-shlib-sm2_sign.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/sm3" =>
                {
                    "deps" =>
                        [
                            "crypto/sm3/libcrypto-lib-m_sm3.o",
                            "crypto/sm3/libcrypto-lib-sm3.o",
                            "crypto/sm3/libcrypto-shlib-m_sm3.o",
                            "crypto/sm3/libcrypto-shlib-sm3.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/sm4" =>
                {
                    "deps" =>
                        [
                            "crypto/sm4/libcrypto-lib-sm4.o",
                            "crypto/sm4/libcrypto-shlib-sm4.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/srp" =>
                {
                    "deps" =>
                        [
                            "crypto/srp/libcrypto-lib-srp_lib.o",
                            "crypto/srp/libcrypto-lib-srp_vfy.o",
                            "crypto/srp/libcrypto-shlib-srp_lib.o",
                            "crypto/srp/libcrypto-shlib-srp_vfy.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/stack" =>
                {
                    "deps" =>
                        [
                            "crypto/stack/libcrypto-lib-stack.o",
                            "crypto/stack/libcrypto-shlib-stack.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/store" =>
                {
                    "deps" =>
                        [
                            "crypto/store/libcrypto-lib-loader_file.o",
                            "crypto/store/libcrypto-lib-store_err.o",
                            "crypto/store/libcrypto-lib-store_init.o",
                            "crypto/store/libcrypto-lib-store_lib.o",
                            "crypto/store/libcrypto-lib-store_register.o",
                            "crypto/store/libcrypto-lib-store_strings.o",
                            "crypto/store/libcrypto-shlib-loader_file.o",
                            "crypto/store/libcrypto-shlib-store_err.o",
                            "crypto/store/libcrypto-shlib-store_init.o",
                            "crypto/store/libcrypto-shlib-store_lib.o",
                            "crypto/store/libcrypto-shlib-store_register.o",
                            "crypto/store/libcrypto-shlib-store_strings.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ts" =>
                {
                    "deps" =>
                        [
                            "crypto/ts/libcrypto-lib-ts_asn1.o",
                            "crypto/ts/libcrypto-lib-ts_conf.o",
                            "crypto/ts/libcrypto-lib-ts_err.o",
                            "crypto/ts/libcrypto-lib-ts_lib.o",
                            "crypto/ts/libcrypto-lib-ts_req_print.o",
                            "crypto/ts/libcrypto-lib-ts_req_utils.o",
                            "crypto/ts/libcrypto-lib-ts_rsp_print.o",
                            "crypto/ts/libcrypto-lib-ts_rsp_sign.o",
                            "crypto/ts/libcrypto-lib-ts_rsp_utils.o",
                            "crypto/ts/libcrypto-lib-ts_rsp_verify.o",
                            "crypto/ts/libcrypto-lib-ts_verify_ctx.o",
                            "crypto/ts/libcrypto-shlib-ts_asn1.o",
                            "crypto/ts/libcrypto-shlib-ts_conf.o",
                            "crypto/ts/libcrypto-shlib-ts_err.o",
                            "crypto/ts/libcrypto-shlib-ts_lib.o",
                            "crypto/ts/libcrypto-shlib-ts_req_print.o",
                            "crypto/ts/libcrypto-shlib-ts_req_utils.o",
                            "crypto/ts/libcrypto-shlib-ts_rsp_print.o",
                            "crypto/ts/libcrypto-shlib-ts_rsp_sign.o",
                            "crypto/ts/libcrypto-shlib-ts_rsp_utils.o",
                            "crypto/ts/libcrypto-shlib-ts_rsp_verify.o",
                            "crypto/ts/libcrypto-shlib-ts_verify_ctx.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/txt_db" =>
                {
                    "deps" =>
                        [
                            "crypto/txt_db/libcrypto-lib-txt_db.o",
                            "crypto/txt_db/libcrypto-shlib-txt_db.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/ui" =>
                {
                    "deps" =>
                        [
                            "crypto/ui/libcrypto-lib-ui_err.o",
                            "crypto/ui/libcrypto-lib-ui_lib.o",
                            "crypto/ui/libcrypto-lib-ui_null.o",
                            "crypto/ui/libcrypto-lib-ui_openssl.o",
                            "crypto/ui/libcrypto-lib-ui_util.o",
                            "crypto/ui/libcrypto-shlib-ui_err.o",
                            "crypto/ui/libcrypto-shlib-ui_lib.o",
                            "crypto/ui/libcrypto-shlib-ui_null.o",
                            "crypto/ui/libcrypto-shlib-ui_openssl.o",
                            "crypto/ui/libcrypto-shlib-ui_util.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/whrlpool" =>
                {
                    "deps" =>
                        [
                            "crypto/whrlpool/libcrypto-lib-wp-x86_64.o",
                            "crypto/whrlpool/libcrypto-lib-wp_dgst.o",
                            "crypto/whrlpool/libcrypto-shlib-wp-x86_64.o",
                            "crypto/whrlpool/libcrypto-shlib-wp_dgst.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/x509" =>
                {
                    "deps" =>
                        [
                            "crypto/x509/libcrypto-lib-by_dir.o",
                            "crypto/x509/libcrypto-lib-by_file.o",
                            "crypto/x509/libcrypto-lib-t_crl.o",
                            "crypto/x509/libcrypto-lib-t_req.o",
                            "crypto/x509/libcrypto-lib-t_x509.o",
                            "crypto/x509/libcrypto-lib-x509_att.o",
                            "crypto/x509/libcrypto-lib-x509_cmp.o",
                            "crypto/x509/libcrypto-lib-x509_d2.o",
                            "crypto/x509/libcrypto-lib-x509_def.o",
                            "crypto/x509/libcrypto-lib-x509_err.o",
                            "crypto/x509/libcrypto-lib-x509_ext.o",
                            "crypto/x509/libcrypto-lib-x509_lu.o",
                            "crypto/x509/libcrypto-lib-x509_meth.o",
                            "crypto/x509/libcrypto-lib-x509_obj.o",
                            "crypto/x509/libcrypto-lib-x509_r2x.o",
                            "crypto/x509/libcrypto-lib-x509_req.o",
                            "crypto/x509/libcrypto-lib-x509_set.o",
                            "crypto/x509/libcrypto-lib-x509_trs.o",
                            "crypto/x509/libcrypto-lib-x509_txt.o",
                            "crypto/x509/libcrypto-lib-x509_v3.o",
                            "crypto/x509/libcrypto-lib-x509_vfy.o",
                            "crypto/x509/libcrypto-lib-x509_vpm.o",
                            "crypto/x509/libcrypto-lib-x509cset.o",
                            "crypto/x509/libcrypto-lib-x509name.o",
                            "crypto/x509/libcrypto-lib-x509rset.o",
                            "crypto/x509/libcrypto-lib-x509spki.o",
                            "crypto/x509/libcrypto-lib-x509type.o",
                            "crypto/x509/libcrypto-lib-x_all.o",
                            "crypto/x509/libcrypto-lib-x_attrib.o",
                            "crypto/x509/libcrypto-lib-x_crl.o",
                            "crypto/x509/libcrypto-lib-x_exten.o",
                            "crypto/x509/libcrypto-lib-x_name.o",
                            "crypto/x509/libcrypto-lib-x_pubkey.o",
                            "crypto/x509/libcrypto-lib-x_req.o",
                            "crypto/x509/libcrypto-lib-x_x509.o",
                            "crypto/x509/libcrypto-lib-x_x509a.o",
                            "crypto/x509/libcrypto-shlib-by_dir.o",
                            "crypto/x509/libcrypto-shlib-by_file.o",
                            "crypto/x509/libcrypto-shlib-t_crl.o",
                            "crypto/x509/libcrypto-shlib-t_req.o",
                            "crypto/x509/libcrypto-shlib-t_x509.o",
                            "crypto/x509/libcrypto-shlib-x509_att.o",
                            "crypto/x509/libcrypto-shlib-x509_cmp.o",
                            "crypto/x509/libcrypto-shlib-x509_d2.o",
                            "crypto/x509/libcrypto-shlib-x509_def.o",
                            "crypto/x509/libcrypto-shlib-x509_err.o",
                            "crypto/x509/libcrypto-shlib-x509_ext.o",
                            "crypto/x509/libcrypto-shlib-x509_lu.o",
                            "crypto/x509/libcrypto-shlib-x509_meth.o",
                            "crypto/x509/libcrypto-shlib-x509_obj.o",
                            "crypto/x509/libcrypto-shlib-x509_r2x.o",
                            "crypto/x509/libcrypto-shlib-x509_req.o",
                            "crypto/x509/libcrypto-shlib-x509_set.o",
                            "crypto/x509/libcrypto-shlib-x509_trs.o",
                            "crypto/x509/libcrypto-shlib-x509_txt.o",
                            "crypto/x509/libcrypto-shlib-x509_v3.o",
                            "crypto/x509/libcrypto-shlib-x509_vfy.o",
                            "crypto/x509/libcrypto-shlib-x509_vpm.o",
                            "crypto/x509/libcrypto-shlib-x509cset.o",
                            "crypto/x509/libcrypto-shlib-x509name.o",
                            "crypto/x509/libcrypto-shlib-x509rset.o",
                            "crypto/x509/libcrypto-shlib-x509spki.o",
                            "crypto/x509/libcrypto-shlib-x509type.o",
                            "crypto/x509/libcrypto-shlib-x_all.o",
                            "crypto/x509/libcrypto-shlib-x_attrib.o",
                            "crypto/x509/libcrypto-shlib-x_crl.o",
                            "crypto/x509/libcrypto-shlib-x_exten.o",
                            "crypto/x509/libcrypto-shlib-x_name.o",
                            "crypto/x509/libcrypto-shlib-x_pubkey.o",
                            "crypto/x509/libcrypto-shlib-x_req.o",
                            "crypto/x509/libcrypto-shlib-x_x509.o",
                            "crypto/x509/libcrypto-shlib-x_x509a.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "crypto/x509v3" =>
                {
                    "deps" =>
                        [
                            "crypto/x509v3/libcrypto-lib-pcy_cache.o",
                            "crypto/x509v3/libcrypto-lib-pcy_data.o",
                            "crypto/x509v3/libcrypto-lib-pcy_lib.o",
                            "crypto/x509v3/libcrypto-lib-pcy_map.o",
                            "crypto/x509v3/libcrypto-lib-pcy_node.o",
                            "crypto/x509v3/libcrypto-lib-pcy_tree.o",
                            "crypto/x509v3/libcrypto-lib-v3_addr.o",
                            "crypto/x509v3/libcrypto-lib-v3_admis.o",
                            "crypto/x509v3/libcrypto-lib-v3_akey.o",
                            "crypto/x509v3/libcrypto-lib-v3_akeya.o",
                            "crypto/x509v3/libcrypto-lib-v3_alt.o",
                            "crypto/x509v3/libcrypto-lib-v3_asid.o",
                            "crypto/x509v3/libcrypto-lib-v3_bcons.o",
                            "crypto/x509v3/libcrypto-lib-v3_bitst.o",
                            "crypto/x509v3/libcrypto-lib-v3_conf.o",
                            "crypto/x509v3/libcrypto-lib-v3_cpols.o",
                            "crypto/x509v3/libcrypto-lib-v3_crld.o",
                            "crypto/x509v3/libcrypto-lib-v3_enum.o",
                            "crypto/x509v3/libcrypto-lib-v3_extku.o",
                            "crypto/x509v3/libcrypto-lib-v3_genn.o",
                            "crypto/x509v3/libcrypto-lib-v3_ia5.o",
                            "crypto/x509v3/libcrypto-lib-v3_info.o",
                            "crypto/x509v3/libcrypto-lib-v3_int.o",
                            "crypto/x509v3/libcrypto-lib-v3_lib.o",
                            "crypto/x509v3/libcrypto-lib-v3_ncons.o",
                            "crypto/x509v3/libcrypto-lib-v3_pci.o",
                            "crypto/x509v3/libcrypto-lib-v3_pcia.o",
                            "crypto/x509v3/libcrypto-lib-v3_pcons.o",
                            "crypto/x509v3/libcrypto-lib-v3_pku.o",
                            "crypto/x509v3/libcrypto-lib-v3_pmaps.o",
                            "crypto/x509v3/libcrypto-lib-v3_prn.o",
                            "crypto/x509v3/libcrypto-lib-v3_purp.o",
                            "crypto/x509v3/libcrypto-lib-v3_skey.o",
                            "crypto/x509v3/libcrypto-lib-v3_sxnet.o",
                            "crypto/x509v3/libcrypto-lib-v3_tlsf.o",
                            "crypto/x509v3/libcrypto-lib-v3_utl.o",
                            "crypto/x509v3/libcrypto-lib-v3err.o",
                            "crypto/x509v3/libcrypto-shlib-pcy_cache.o",
                            "crypto/x509v3/libcrypto-shlib-pcy_data.o",
                            "crypto/x509v3/libcrypto-shlib-pcy_lib.o",
                            "crypto/x509v3/libcrypto-shlib-pcy_map.o",
                            "crypto/x509v3/libcrypto-shlib-pcy_node.o",
                            "crypto/x509v3/libcrypto-shlib-pcy_tree.o",
                            "crypto/x509v3/libcrypto-shlib-v3_addr.o",
                            "crypto/x509v3/libcrypto-shlib-v3_admis.o",
                            "crypto/x509v3/libcrypto-shlib-v3_akey.o",
                            "crypto/x509v3/libcrypto-shlib-v3_akeya.o",
                            "crypto/x509v3/libcrypto-shlib-v3_alt.o",
                            "crypto/x509v3/libcrypto-shlib-v3_asid.o",
                            "crypto/x509v3/libcrypto-shlib-v3_bcons.o",
                            "crypto/x509v3/libcrypto-shlib-v3_bitst.o",
                            "crypto/x509v3/libcrypto-shlib-v3_conf.o",
                            "crypto/x509v3/libcrypto-shlib-v3_cpols.o",
                            "crypto/x509v3/libcrypto-shlib-v3_crld.o",
                            "crypto/x509v3/libcrypto-shlib-v3_enum.o",
                            "crypto/x509v3/libcrypto-shlib-v3_extku.o",
                            "crypto/x509v3/libcrypto-shlib-v3_genn.o",
                            "crypto/x509v3/libcrypto-shlib-v3_ia5.o",
                            "crypto/x509v3/libcrypto-shlib-v3_info.o",
                            "crypto/x509v3/libcrypto-shlib-v3_int.o",
                            "crypto/x509v3/libcrypto-shlib-v3_lib.o",
                            "crypto/x509v3/libcrypto-shlib-v3_ncons.o",
                            "crypto/x509v3/libcrypto-shlib-v3_pci.o",
                            "crypto/x509v3/libcrypto-shlib-v3_pcia.o",
                            "crypto/x509v3/libcrypto-shlib-v3_pcons.o",
                            "crypto/x509v3/libcrypto-shlib-v3_pku.o",
                            "crypto/x509v3/libcrypto-shlib-v3_pmaps.o",
                            "crypto/x509v3/libcrypto-shlib-v3_prn.o",
                            "crypto/x509v3/libcrypto-shlib-v3_purp.o",
                            "crypto/x509v3/libcrypto-shlib-v3_skey.o",
                            "crypto/x509v3/libcrypto-shlib-v3_sxnet.o",
                            "crypto/x509v3/libcrypto-shlib-v3_tlsf.o",
                            "crypto/x509v3/libcrypto-shlib-v3_utl.o",
                            "crypto/x509v3/libcrypto-shlib-v3err.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "engines" =>
                {
                    "products" =>
                        {
                            "dso" =>
                                [
                                    "engines/afalg",
                                    "engines/capi",
                                    "engines/dasync",
                                    "engines/ossltest",
                                    "engines/padlock",
                                ],
                        },
                },
            "fuzz" =>
                {
                    "products" =>
                        {
                            "bin" =>
                                [
                                    "fuzz/asn1-test",
                                    "fuzz/asn1parse-test",
                                    "fuzz/bignum-test",
                                    "fuzz/bndiv-test",
                                    "fuzz/client-test",
                                    "fuzz/cms-test",
                                    "fuzz/conf-test",
                                    "fuzz/crl-test",
                                    "fuzz/ct-test",
                                    "fuzz/server-test",
                                    "fuzz/x509-test",
                                ],
                        },
                },
            "providers" =>
                {
                    "products" =>
                        {
                            "dso" =>
                                [
                                    "providers/fips",
                                ],
                        },
                },
            "providers/common/digests" =>
                {
                    "deps" =>
                        [
                            "providers/common/digests/fips-dso-sha2.o",
                            "providers/common/digests/libcrypto-lib-sha2.o",
                            "providers/common/digests/libcrypto-shlib-sha2.o",
                        ],
                    "products" =>
                        {
                            "dso" =>
                                [
                                    "providers/fips",
                                ],
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "providers/default" =>
                {
                    "deps" =>
                        [
                            "providers/default/libcrypto-lib-defltprov.o",
                            "providers/default/libcrypto-shlib-defltprov.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libcrypto",
                                ],
                        },
                },
            "providers/fips" =>
                {
                    "deps" =>
                        [
                            "providers/fips/fips-dso-fipsprov.o",
                        ],
                    "products" =>
                        {
                            "dso" =>
                                [
                                    "providers/fips",
                                ],
                        },
                },
            "ssl" =>
                {
                    "deps" =>
                        [
                            "ssl/tls13secretstest-bin-packet.o",
                            "ssl/tls13secretstest-bin-tls13_enc.o",
                            "ssl/libssl-lib-bio_ssl.o",
                            "ssl/libssl-lib-d1_lib.o",
                            "ssl/libssl-lib-d1_msg.o",
                            "ssl/libssl-lib-d1_srtp.o",
                            "ssl/libssl-lib-methods.o",
                            "ssl/libssl-lib-packet.o",
                            "ssl/libssl-lib-pqueue.o",
                            "ssl/libssl-lib-s3_cbc.o",
                            "ssl/libssl-lib-s3_enc.o",
                            "ssl/libssl-lib-s3_lib.o",
                            "ssl/libssl-lib-s3_msg.o",
                            "ssl/libssl-lib-ssl_asn1.o",
                            "ssl/libssl-lib-ssl_cert.o",
                            "ssl/libssl-lib-ssl_ciph.o",
                            "ssl/libssl-lib-ssl_conf.o",
                            "ssl/libssl-lib-ssl_err.o",
                            "ssl/libssl-lib-ssl_init.o",
                            "ssl/libssl-lib-ssl_lib.o",
                            "ssl/libssl-lib-ssl_mcnf.o",
                            "ssl/libssl-lib-ssl_rsa.o",
                            "ssl/libssl-lib-ssl_sess.o",
                            "ssl/libssl-lib-ssl_stat.o",
                            "ssl/libssl-lib-ssl_txt.o",
                            "ssl/libssl-lib-ssl_utst.o",
                            "ssl/libssl-lib-t1_enc.o",
                            "ssl/libssl-lib-t1_lib.o",
                            "ssl/libssl-lib-t1_trce.o",
                            "ssl/libssl-lib-tls13_enc.o",
                            "ssl/libssl-lib-tls_srp.o",
                            "ssl/libssl-shlib-bio_ssl.o",
                            "ssl/libssl-shlib-d1_lib.o",
                            "ssl/libssl-shlib-d1_msg.o",
                            "ssl/libssl-shlib-d1_srtp.o",
                            "ssl/libssl-shlib-methods.o",
                            "ssl/libssl-shlib-packet.o",
                            "ssl/libssl-shlib-pqueue.o",
                            "ssl/libssl-shlib-s3_cbc.o",
                            "ssl/libssl-shlib-s3_enc.o",
                            "ssl/libssl-shlib-s3_lib.o",
                            "ssl/libssl-shlib-s3_msg.o",
                            "ssl/libssl-shlib-ssl_asn1.o",
                            "ssl/libssl-shlib-ssl_cert.o",
                            "ssl/libssl-shlib-ssl_ciph.o",
                            "ssl/libssl-shlib-ssl_conf.o",
                            "ssl/libssl-shlib-ssl_err.o",
                            "ssl/libssl-shlib-ssl_init.o",
                            "ssl/libssl-shlib-ssl_lib.o",
                            "ssl/libssl-shlib-ssl_mcnf.o",
                            "ssl/libssl-shlib-ssl_rsa.o",
                            "ssl/libssl-shlib-ssl_sess.o",
                            "ssl/libssl-shlib-ssl_stat.o",
                            "ssl/libssl-shlib-ssl_txt.o",
                            "ssl/libssl-shlib-ssl_utst.o",
                            "ssl/libssl-shlib-t1_enc.o",
                            "ssl/libssl-shlib-t1_lib.o",
                            "ssl/libssl-shlib-t1_trce.o",
                            "ssl/libssl-shlib-tls13_enc.o",
                            "ssl/libssl-shlib-tls_srp.o",
                        ],
                    "products" =>
                        {
                            "bin" =>
                                [
                                    "test/tls13secretstest",
                                ],
                            "lib" =>
                                [
                                    "libssl",
                                ],
                        },
                },
            "ssl/record" =>
                {
                    "deps" =>
                        [
                            "ssl/record/libssl-lib-dtls1_bitmap.o",
                            "ssl/record/libssl-lib-rec_layer_d1.o",
                            "ssl/record/libssl-lib-rec_layer_s3.o",
                            "ssl/record/libssl-lib-ssl3_buffer.o",
                            "ssl/record/libssl-lib-ssl3_record.o",
                            "ssl/record/libssl-lib-ssl3_record_tls13.o",
                            "ssl/record/libssl-shlib-dtls1_bitmap.o",
                            "ssl/record/libssl-shlib-rec_layer_d1.o",
                            "ssl/record/libssl-shlib-rec_layer_s3.o",
                            "ssl/record/libssl-shlib-ssl3_buffer.o",
                            "ssl/record/libssl-shlib-ssl3_record.o",
                            "ssl/record/libssl-shlib-ssl3_record_tls13.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libssl",
                                ],
                        },
                },
            "ssl/statem" =>
                {
                    "deps" =>
                        [
                            "ssl/statem/libssl-lib-extensions.o",
                            "ssl/statem/libssl-lib-extensions_clnt.o",
                            "ssl/statem/libssl-lib-extensions_cust.o",
                            "ssl/statem/libssl-lib-extensions_srvr.o",
                            "ssl/statem/libssl-lib-statem.o",
                            "ssl/statem/libssl-lib-statem_clnt.o",
                            "ssl/statem/libssl-lib-statem_dtls.o",
                            "ssl/statem/libssl-lib-statem_lib.o",
                            "ssl/statem/libssl-lib-statem_srvr.o",
                            "ssl/statem/libssl-shlib-extensions.o",
                            "ssl/statem/libssl-shlib-extensions_clnt.o",
                            "ssl/statem/libssl-shlib-extensions_cust.o",
                            "ssl/statem/libssl-shlib-extensions_srvr.o",
                            "ssl/statem/libssl-shlib-statem.o",
                            "ssl/statem/libssl-shlib-statem_clnt.o",
                            "ssl/statem/libssl-shlib-statem_dtls.o",
                            "ssl/statem/libssl-shlib-statem_lib.o",
                            "ssl/statem/libssl-shlib-statem_srvr.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "libssl",
                                ],
                        },
                },
            "test/testutil" =>
                {
                    "deps" =>
                        [
                            "test/testutil/libtestutil-lib-apps_mem.o",
                            "test/testutil/libtestutil-lib-basic_output.o",
                            "test/testutil/libtestutil-lib-cb.o",
                            "test/testutil/libtestutil-lib-driver.o",
                            "test/testutil/libtestutil-lib-format_output.o",
                            "test/testutil/libtestutil-lib-init.o",
                            "test/testutil/libtestutil-lib-main.o",
                            "test/testutil/libtestutil-lib-options.o",
                            "test/testutil/libtestutil-lib-output_helpers.o",
                            "test/testutil/libtestutil-lib-stanza.o",
                            "test/testutil/libtestutil-lib-tap_bio.o",
                            "test/testutil/libtestutil-lib-test_cleanup.o",
                            "test/testutil/libtestutil-lib-test_options.o",
                            "test/testutil/libtestutil-lib-tests.o",
                        ],
                    "products" =>
                        {
                            "lib" =>
                                [
                                    "test/libtestutil.a",
                                ],
                        },
                },
            "tools" =>
                {
                    "products" =>
                        {
                            "script" =>
                                [
                                    "tools/c_rehash",
                                ],
                        },
                },
            "util" =>
                {
                    "products" =>
                        {
                            "script" =>
                                [
                                    "util/shlib_wrap.sh",
                                ],
                        },
                },
        },
    "generate" =>
        {
            "apps/progs.h" =>
                [
                    "apps/progs.pl",
                    "\$(APPS_OPENSSL)",
                ],
            "crypto/aes/aes-586.s" =>
                [
                    "crypto/aes/asm/aes-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/aes/aes-armv4.S" =>
                [
                    "crypto/aes/asm/aes-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-c64xplus.S" =>
                [
                    "crypto/aes/asm/aes-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-ia64.s" =>
                [
                    "crypto/aes/asm/aes-ia64.S",
                ],
            "crypto/aes/aes-mips.S" =>
                [
                    "crypto/aes/asm/aes-mips.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-parisc.s" =>
                [
                    "crypto/aes/asm/aes-parisc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-ppc.s" =>
                [
                    "crypto/aes/asm/aes-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-s390x.S" =>
                [
                    "crypto/aes/asm/aes-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-sparcv9.S" =>
                [
                    "crypto/aes/asm/aes-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aes-x86_64.s" =>
                [
                    "crypto/aes/asm/aes-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesfx-sparcv9.S" =>
                [
                    "crypto/aes/asm/aesfx-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesni-mb-x86_64.s" =>
                [
                    "crypto/aes/asm/aesni-mb-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesni-sha1-x86_64.s" =>
                [
                    "crypto/aes/asm/aesni-sha1-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesni-sha256-x86_64.s" =>
                [
                    "crypto/aes/asm/aesni-sha256-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesni-x86.s" =>
                [
                    "crypto/aes/asm/aesni-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/aes/aesni-x86_64.s" =>
                [
                    "crypto/aes/asm/aesni-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesp8-ppc.s" =>
                [
                    "crypto/aes/asm/aesp8-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aest4-sparcv9.S" =>
                [
                    "crypto/aes/asm/aest4-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/aesv8-armx.S" =>
                [
                    "crypto/aes/asm/aesv8-armx.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/bsaes-armv7.S" =>
                [
                    "crypto/aes/asm/bsaes-armv7.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/bsaes-x86_64.s" =>
                [
                    "crypto/aes/asm/bsaes-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/vpaes-armv8.S" =>
                [
                    "crypto/aes/asm/vpaes-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/vpaes-ppc.s" =>
                [
                    "crypto/aes/asm/vpaes-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/aes/vpaes-x86.s" =>
                [
                    "crypto/aes/asm/vpaes-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/aes/vpaes-x86_64.s" =>
                [
                    "crypto/aes/asm/vpaes-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/alphacpuid.s" =>
                [
                    "crypto/alphacpuid.pl",
                ],
            "crypto/arm64cpuid.S" =>
                [
                    "crypto/arm64cpuid.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/armv4cpuid.S" =>
                [
                    "crypto/armv4cpuid.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bf/bf-586.s" =>
                [
                    "crypto/bf/asm/bf-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/bn/alpha-mont.S" =>
                [
                    "crypto/bn/asm/alpha-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/armv4-gf2m.S" =>
                [
                    "crypto/bn/asm/armv4-gf2m.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/armv4-mont.S" =>
                [
                    "crypto/bn/asm/armv4-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/armv8-mont.S" =>
                [
                    "crypto/bn/asm/armv8-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/bn-586.s" =>
                [
                    "crypto/bn/asm/bn-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/bn/bn-ia64.s" =>
                [
                    "crypto/bn/asm/ia64.S",
                ],
            "crypto/bn/bn-mips.S" =>
                [
                    "crypto/bn/asm/mips.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/bn-ppc.s" =>
                [
                    "crypto/bn/asm/ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/co-586.s" =>
                [
                    "crypto/bn/asm/co-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/bn/ia64-mont.s" =>
                [
                    "crypto/bn/asm/ia64-mont.pl",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/bn/mips-mont.S" =>
                [
                    "crypto/bn/asm/mips-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/parisc-mont.s" =>
                [
                    "crypto/bn/asm/parisc-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/ppc-mont.s" =>
                [
                    "crypto/bn/asm/ppc-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/ppc64-mont.s" =>
                [
                    "crypto/bn/asm/ppc64-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/rsaz-avx2.s" =>
                [
                    "crypto/bn/asm/rsaz-avx2.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/rsaz-x86_64.s" =>
                [
                    "crypto/bn/asm/rsaz-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/s390x-gf2m.s" =>
                [
                    "crypto/bn/asm/s390x-gf2m.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/s390x-mont.S" =>
                [
                    "crypto/bn/asm/s390x-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/sparct4-mont.S" =>
                [
                    "crypto/bn/asm/sparct4-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/sparcv9-gf2m.S" =>
                [
                    "crypto/bn/asm/sparcv9-gf2m.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/sparcv9-mont.S" =>
                [
                    "crypto/bn/asm/sparcv9-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/sparcv9a-mont.S" =>
                [
                    "crypto/bn/asm/sparcv9a-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/vis3-mont.S" =>
                [
                    "crypto/bn/asm/vis3-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/x86-gf2m.s" =>
                [
                    "crypto/bn/asm/x86-gf2m.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/bn/x86-mont.s" =>
                [
                    "crypto/bn/asm/x86-mont.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/bn/x86_64-gf2m.s" =>
                [
                    "crypto/bn/asm/x86_64-gf2m.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/x86_64-mont.s" =>
                [
                    "crypto/bn/asm/x86_64-mont.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/bn/x86_64-mont5.s" =>
                [
                    "crypto/bn/asm/x86_64-mont5.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/buildinf.h" =>
                [
                    "util/mkbuildinf.pl",
                    "\"\$(CC)",
                    "\$(LIB_CFLAGS)",
                    "\$(CPPFLAGS_Q)\"",
                    "\"\$(PLATFORM)\"",
                ],
            "crypto/camellia/cmll-x86.s" =>
                [
                    "crypto/camellia/asm/cmll-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/camellia/cmll-x86_64.s" =>
                [
                    "crypto/camellia/asm/cmll-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/camellia/cmllt4-sparcv9.S" =>
                [
                    "crypto/camellia/asm/cmllt4-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/cast/cast-586.s" =>
                [
                    "crypto/cast/asm/cast-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/chacha/chacha-armv4.S" =>
                [
                    "crypto/chacha/asm/chacha-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/chacha/chacha-armv8.S" =>
                [
                    "crypto/chacha/asm/chacha-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/chacha/chacha-c64xplus.S" =>
                [
                    "crypto/chacha/asm/chacha-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/chacha/chacha-ia64.S" =>
                [
                    "crypto/chacha/asm/chacha-ia64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/chacha/chacha-ppc.s" =>
                [
                    "crypto/chacha/asm/chacha-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/chacha/chacha-s390x.S" =>
                [
                    "crypto/chacha/asm/chacha-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/chacha/chacha-x86.s" =>
                [
                    "crypto/chacha/asm/chacha-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/chacha/chacha-x86_64.s" =>
                [
                    "crypto/chacha/asm/chacha-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/des/crypt586.s" =>
                [
                    "crypto/des/asm/crypt586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/des/des-586.s" =>
                [
                    "crypto/des/asm/des-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/des/des_enc-sparc.S" =>
                [
                    "crypto/des/asm/des_enc.m4",
                ],
            "crypto/des/dest4-sparcv9.S" =>
                [
                    "crypto/des/asm/dest4-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/ecp_nistz256-armv4.S" =>
                [
                    "crypto/ec/asm/ecp_nistz256-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/ecp_nistz256-armv8.S" =>
                [
                    "crypto/ec/asm/ecp_nistz256-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/ecp_nistz256-avx2.s" =>
                [
                    "crypto/ec/asm/ecp_nistz256-avx2.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/ecp_nistz256-ppc64.s" =>
                [
                    "crypto/ec/asm/ecp_nistz256-ppc64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/ecp_nistz256-sparcv9.S" =>
                [
                    "crypto/ec/asm/ecp_nistz256-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/ecp_nistz256-x86.s" =>
                [
                    "crypto/ec/asm/ecp_nistz256-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/ec/ecp_nistz256-x86_64.s" =>
                [
                    "crypto/ec/asm/ecp_nistz256-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/x25519-ppc64.s" =>
                [
                    "crypto/ec/asm/x25519-ppc64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ec/x25519-x86_64.s" =>
                [
                    "crypto/ec/asm/x25519-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ia64cpuid.s" =>
                [
                    "crypto/ia64cpuid.S",
                ],
            "crypto/include/internal/bn_conf.h" =>
                [
                    "crypto/include/internal/bn_conf.h.in",
                ],
            "crypto/include/internal/dso_conf.h" =>
                [
                    "crypto/include/internal/dso_conf.h.in",
                ],
            "crypto/md5/md5-586.s" =>
                [
                    "crypto/md5/asm/md5-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/md5/md5-sparcv9.S" =>
                [
                    "crypto/md5/asm/md5-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/md5/md5-x86_64.s" =>
                [
                    "crypto/md5/asm/md5-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/aesni-gcm-x86_64.s" =>
                [
                    "crypto/modes/asm/aesni-gcm-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-alpha.S" =>
                [
                    "crypto/modes/asm/ghash-alpha.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-armv4.S" =>
                [
                    "crypto/modes/asm/ghash-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-c64xplus.S" =>
                [
                    "crypto/modes/asm/ghash-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-ia64.s" =>
                [
                    "crypto/modes/asm/ghash-ia64.pl",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/modes/ghash-parisc.s" =>
                [
                    "crypto/modes/asm/ghash-parisc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-s390x.S" =>
                [
                    "crypto/modes/asm/ghash-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-sparcv9.S" =>
                [
                    "crypto/modes/asm/ghash-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghash-x86.s" =>
                [
                    "crypto/modes/asm/ghash-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/modes/ghash-x86_64.s" =>
                [
                    "crypto/modes/asm/ghash-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghashp8-ppc.s" =>
                [
                    "crypto/modes/asm/ghashp8-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/modes/ghashv8-armx.S" =>
                [
                    "crypto/modes/asm/ghashv8-armx.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/pariscid.s" =>
                [
                    "crypto/pariscid.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-armv4.S" =>
                [
                    "crypto/poly1305/asm/poly1305-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-armv8.S" =>
                [
                    "crypto/poly1305/asm/poly1305-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-c64xplus.S" =>
                [
                    "crypto/poly1305/asm/poly1305-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-mips.S" =>
                [
                    "crypto/poly1305/asm/poly1305-mips.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-ppc.s" =>
                [
                    "crypto/poly1305/asm/poly1305-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-ppcfp.s" =>
                [
                    "crypto/poly1305/asm/poly1305-ppcfp.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-s390x.S" =>
                [
                    "crypto/poly1305/asm/poly1305-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-sparcv9.S" =>
                [
                    "crypto/poly1305/asm/poly1305-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/poly1305/poly1305-x86.s" =>
                [
                    "crypto/poly1305/asm/poly1305-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/poly1305/poly1305-x86_64.s" =>
                [
                    "crypto/poly1305/asm/poly1305-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ppccpuid.s" =>
                [
                    "crypto/ppccpuid.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/rc4/rc4-586.s" =>
                [
                    "crypto/rc4/asm/rc4-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/rc4/rc4-c64xplus.s" =>
                [
                    "crypto/rc4/asm/rc4-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/rc4/rc4-md5-x86_64.s" =>
                [
                    "crypto/rc4/asm/rc4-md5-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/rc4/rc4-parisc.s" =>
                [
                    "crypto/rc4/asm/rc4-parisc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/rc4/rc4-s390x.s" =>
                [
                    "crypto/rc4/asm/rc4-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/rc4/rc4-x86_64.s" =>
                [
                    "crypto/rc4/asm/rc4-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/ripemd/rmd-586.s" =>
                [
                    "crypto/ripemd/asm/rmd-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/s390xcpuid.S" =>
                [
                    "crypto/s390xcpuid.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-armv4.S" =>
                [
                    "crypto/sha/asm/keccak1600-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-armv8.S" =>
                [
                    "crypto/sha/asm/keccak1600-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-avx2.S" =>
                [
                    "crypto/sha/asm/keccak1600-avx2.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-avx512.S" =>
                [
                    "crypto/sha/asm/keccak1600-avx512.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-avx512vl.S" =>
                [
                    "crypto/sha/asm/keccak1600-avx512vl.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-c64x.S" =>
                [
                    "crypto/sha/asm/keccak1600-c64x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-mmx.S" =>
                [
                    "crypto/sha/asm/keccak1600-mmx.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-ppc64.s" =>
                [
                    "crypto/sha/asm/keccak1600-ppc64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-s390x.S" =>
                [
                    "crypto/sha/asm/keccak1600-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600-x86_64.s" =>
                [
                    "crypto/sha/asm/keccak1600-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/keccak1600p8-ppc.S" =>
                [
                    "crypto/sha/asm/keccak1600p8-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-586.s" =>
                [
                    "crypto/sha/asm/sha1-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/sha/sha1-alpha.S" =>
                [
                    "crypto/sha/asm/sha1-alpha.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-armv4-large.S" =>
                [
                    "crypto/sha/asm/sha1-armv4-large.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-armv8.S" =>
                [
                    "crypto/sha/asm/sha1-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-c64xplus.S" =>
                [
                    "crypto/sha/asm/sha1-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-ia64.s" =>
                [
                    "crypto/sha/asm/sha1-ia64.pl",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/sha/sha1-mb-x86_64.s" =>
                [
                    "crypto/sha/asm/sha1-mb-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-mips.S" =>
                [
                    "crypto/sha/asm/sha1-mips.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-parisc.s" =>
                [
                    "crypto/sha/asm/sha1-parisc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-ppc.s" =>
                [
                    "crypto/sha/asm/sha1-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-s390x.S" =>
                [
                    "crypto/sha/asm/sha1-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-sparcv9.S" =>
                [
                    "crypto/sha/asm/sha1-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-sparcv9a.S" =>
                [
                    "crypto/sha/asm/sha1-sparcv9a.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-thumb.S" =>
                [
                    "crypto/sha/asm/sha1-thumb.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha1-x86_64.s" =>
                [
                    "crypto/sha/asm/sha1-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-586.s" =>
                [
                    "crypto/sha/asm/sha256-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/sha/sha256-armv4.S" =>
                [
                    "crypto/sha/asm/sha256-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-armv8.S" =>
                [
                    "crypto/sha/asm/sha512-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-c64xplus.S" =>
                [
                    "crypto/sha/asm/sha256-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-ia64.s" =>
                [
                    "crypto/sha/asm/sha512-ia64.pl",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/sha/sha256-mb-x86_64.s" =>
                [
                    "crypto/sha/asm/sha256-mb-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-mips.S" =>
                [
                    "crypto/sha/asm/sha512-mips.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-parisc.s" =>
                [
                    "crypto/sha/asm/sha512-parisc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-ppc.s" =>
                [
                    "crypto/sha/asm/sha512-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-s390x.S" =>
                [
                    "crypto/sha/asm/sha512-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-sparcv9.S" =>
                [
                    "crypto/sha/asm/sha512-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256-x86_64.s" =>
                [
                    "crypto/sha/asm/sha512-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha256p8-ppc.s" =>
                [
                    "crypto/sha/asm/sha512p8-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-586.s" =>
                [
                    "crypto/sha/asm/sha512-586.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/sha/sha512-armv4.S" =>
                [
                    "crypto/sha/asm/sha512-armv4.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-armv8.S" =>
                [
                    "crypto/sha/asm/sha512-armv8.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-c64xplus.S" =>
                [
                    "crypto/sha/asm/sha512-c64xplus.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-ia64.s" =>
                [
                    "crypto/sha/asm/sha512-ia64.pl",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                ],
            "crypto/sha/sha512-mips.S" =>
                [
                    "crypto/sha/asm/sha512-mips.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-parisc.s" =>
                [
                    "crypto/sha/asm/sha512-parisc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-ppc.s" =>
                [
                    "crypto/sha/asm/sha512-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-s390x.S" =>
                [
                    "crypto/sha/asm/sha512-s390x.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-sparcv9.S" =>
                [
                    "crypto/sha/asm/sha512-sparcv9.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512-x86_64.s" =>
                [
                    "crypto/sha/asm/sha512-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/sha/sha512p8-ppc.s" =>
                [
                    "crypto/sha/asm/sha512p8-ppc.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/uplink-ia64.s" =>
                [
                    "ms/uplink-ia64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/uplink-x86.s" =>
                [
                    "ms/uplink-x86.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/uplink-x86_64.s" =>
                [
                    "ms/uplink-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/whrlpool/wp-mmx.s" =>
                [
                    "crypto/whrlpool/asm/wp-mmx.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "crypto/whrlpool/wp-x86_64.s" =>
                [
                    "crypto/whrlpool/asm/wp-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/x86_64cpuid.s" =>
                [
                    "crypto/x86_64cpuid.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "crypto/x86cpuid.s" =>
                [
                    "crypto/x86cpuid.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "doc/man7/openssl_user_macros.pod" =>
                [
                    "doc/man7/openssl_user_macros.pod.in",
                ],
            "engines/afalg.ld" =>
                [
                    "util/engines.num",
                ],
            "engines/capi.ld" =>
                [
                    "util/engines.num",
                ],
            "engines/dasync.ld" =>
                [
                    "util/engines.num",
                ],
            "engines/e_padlock-x86.s" =>
                [
                    "engines/asm/e_padlock-x86.pl",
                    "\$(PERLASM_SCHEME)",
                    "\$(LIB_CFLAGS)",
                    "\$(LIB_CPPFLAGS)",
                    "\$(PROCESSOR)",
                ],
            "engines/e_padlock-x86_64.s" =>
                [
                    "engines/asm/e_padlock-x86_64.pl",
                    "\$(PERLASM_SCHEME)",
                ],
            "engines/ossltest.ld" =>
                [
                    "util/engines.num",
                ],
            "engines/padlock.ld" =>
                [
                    "util/engines.num",
                ],
            "include/openssl/opensslconf.h" =>
                [
                    "include/openssl/opensslconf.h.in",
                ],
            "libcrypto.ld" =>
                [
                    "util/libcrypto.num",
                    "libcrypto",
                ],
            "libssl.ld" =>
                [
                    "util/libssl.num",
                    "libssl",
                ],
            "providers/fips.ld" =>
                [
                    "util/providers.num",
                ],
            "test/buildtest_aes.c" =>
                [
                    "test/generate_buildtest.pl",
                    "aes",
                ],
            "test/buildtest_asn1.c" =>
                [
                    "test/generate_buildtest.pl",
                    "asn1",
                ],
            "test/buildtest_asn1t.c" =>
                [
                    "test/generate_buildtest.pl",
                    "asn1t",
                ],
            "test/buildtest_async.c" =>
                [
                    "test/generate_buildtest.pl",
                    "async",
                ],
            "test/buildtest_bio.c" =>
                [
                    "test/generate_buildtest.pl",
                    "bio",
                ],
            "test/buildtest_blowfish.c" =>
                [
                    "test/generate_buildtest.pl",
                    "blowfish",
                ],
            "test/buildtest_bn.c" =>
                [
                    "test/generate_buildtest.pl",
                    "bn",
                ],
            "test/buildtest_buffer.c" =>
                [
                    "test/generate_buildtest.pl",
                    "buffer",
                ],
            "test/buildtest_camellia.c" =>
                [
                    "test/generate_buildtest.pl",
                    "camellia",
                ],
            "test/buildtest_cast.c" =>
                [
                    "test/generate_buildtest.pl",
                    "cast",
                ],
            "test/buildtest_cmac.c" =>
                [
                    "test/generate_buildtest.pl",
                    "cmac",
                ],
            "test/buildtest_cms.c" =>
                [
                    "test/generate_buildtest.pl",
                    "cms",
                ],
            "test/buildtest_comp.c" =>
                [
                    "test/generate_buildtest.pl",
                    "comp",
                ],
            "test/buildtest_conf.c" =>
                [
                    "test/generate_buildtest.pl",
                    "conf",
                ],
            "test/buildtest_conf_api.c" =>
                [
                    "test/generate_buildtest.pl",
                    "conf_api",
                ],
            "test/buildtest_core.c" =>
                [
                    "test/generate_buildtest.pl",
                    "core",
                ],
            "test/buildtest_core_names.c" =>
                [
                    "test/generate_buildtest.pl",
                    "core_names",
                ],
            "test/buildtest_core_numbers.c" =>
                [
                    "test/generate_buildtest.pl",
                    "core_numbers",
                ],
            "test/buildtest_crmf.c" =>
                [
                    "test/generate_buildtest.pl",
                    "crmf",
                ],
            "test/buildtest_crypto.c" =>
                [
                    "test/generate_buildtest.pl",
                    "crypto",
                ],
            "test/buildtest_ct.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ct",
                ],
            "test/buildtest_des.c" =>
                [
                    "test/generate_buildtest.pl",
                    "des",
                ],
            "test/buildtest_dh.c" =>
                [
                    "test/generate_buildtest.pl",
                    "dh",
                ],
            "test/buildtest_dsa.c" =>
                [
                    "test/generate_buildtest.pl",
                    "dsa",
                ],
            "test/buildtest_dtls1.c" =>
                [
                    "test/generate_buildtest.pl",
                    "dtls1",
                ],
            "test/buildtest_e_os2.c" =>
                [
                    "test/generate_buildtest.pl",
                    "e_os2",
                ],
            "test/buildtest_ebcdic.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ebcdic",
                ],
            "test/buildtest_ec.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ec",
                ],
            "test/buildtest_ecdh.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ecdh",
                ],
            "test/buildtest_ecdsa.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ecdsa",
                ],
            "test/buildtest_engine.c" =>
                [
                    "test/generate_buildtest.pl",
                    "engine",
                ],
            "test/buildtest_ess.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ess",
                ],
            "test/buildtest_evp.c" =>
                [
                    "test/generate_buildtest.pl",
                    "evp",
                ],
            "test/buildtest_hmac.c" =>
                [
                    "test/generate_buildtest.pl",
                    "hmac",
                ],
            "test/buildtest_idea.c" =>
                [
                    "test/generate_buildtest.pl",
                    "idea",
                ],
            "test/buildtest_kdf.c" =>
                [
                    "test/generate_buildtest.pl",
                    "kdf",
                ],
            "test/buildtest_lhash.c" =>
                [
                    "test/generate_buildtest.pl",
                    "lhash",
                ],
            "test/buildtest_md4.c" =>
                [
                    "test/generate_buildtest.pl",
                    "md4",
                ],
            "test/buildtest_md5.c" =>
                [
                    "test/generate_buildtest.pl",
                    "md5",
                ],
            "test/buildtest_mdc2.c" =>
                [
                    "test/generate_buildtest.pl",
                    "mdc2",
                ],
            "test/buildtest_modes.c" =>
                [
                    "test/generate_buildtest.pl",
                    "modes",
                ],
            "test/buildtest_obj_mac.c" =>
                [
                    "test/generate_buildtest.pl",
                    "obj_mac",
                ],
            "test/buildtest_objects.c" =>
                [
                    "test/generate_buildtest.pl",
                    "objects",
                ],
            "test/buildtest_ocsp.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ocsp",
                ],
            "test/buildtest_opensslv.c" =>
                [
                    "test/generate_buildtest.pl",
                    "opensslv",
                ],
            "test/buildtest_ossl_typ.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ossl_typ",
                ],
            "test/buildtest_params.c" =>
                [
                    "test/generate_buildtest.pl",
                    "params",
                ],
            "test/buildtest_pem.c" =>
                [
                    "test/generate_buildtest.pl",
                    "pem",
                ],
            "test/buildtest_pem2.c" =>
                [
                    "test/generate_buildtest.pl",
                    "pem2",
                ],
            "test/buildtest_pkcs12.c" =>
                [
                    "test/generate_buildtest.pl",
                    "pkcs12",
                ],
            "test/buildtest_pkcs7.c" =>
                [
                    "test/generate_buildtest.pl",
                    "pkcs7",
                ],
            "test/buildtest_provider.c" =>
                [
                    "test/generate_buildtest.pl",
                    "provider",
                ],
            "test/buildtest_rand.c" =>
                [
                    "test/generate_buildtest.pl",
                    "rand",
                ],
            "test/buildtest_rand_drbg.c" =>
                [
                    "test/generate_buildtest.pl",
                    "rand_drbg",
                ],
            "test/buildtest_rc2.c" =>
                [
                    "test/generate_buildtest.pl",
                    "rc2",
                ],
            "test/buildtest_rc4.c" =>
                [
                    "test/generate_buildtest.pl",
                    "rc4",
                ],
            "test/buildtest_ripemd.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ripemd",
                ],
            "test/buildtest_rsa.c" =>
                [
                    "test/generate_buildtest.pl",
                    "rsa",
                ],
            "test/buildtest_safestack.c" =>
                [
                    "test/generate_buildtest.pl",
                    "safestack",
                ],
            "test/buildtest_seed.c" =>
                [
                    "test/generate_buildtest.pl",
                    "seed",
                ],
            "test/buildtest_sha.c" =>
                [
                    "test/generate_buildtest.pl",
                    "sha",
                ],
            "test/buildtest_srp.c" =>
                [
                    "test/generate_buildtest.pl",
                    "srp",
                ],
            "test/buildtest_srtp.c" =>
                [
                    "test/generate_buildtest.pl",
                    "srtp",
                ],
            "test/buildtest_ssl.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ssl",
                ],
            "test/buildtest_ssl2.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ssl2",
                ],
            "test/buildtest_stack.c" =>
                [
                    "test/generate_buildtest.pl",
                    "stack",
                ],
            "test/buildtest_store.c" =>
                [
                    "test/generate_buildtest.pl",
                    "store",
                ],
            "test/buildtest_symhacks.c" =>
                [
                    "test/generate_buildtest.pl",
                    "symhacks",
                ],
            "test/buildtest_tls1.c" =>
                [
                    "test/generate_buildtest.pl",
                    "tls1",
                ],
            "test/buildtest_ts.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ts",
                ],
            "test/buildtest_txt_db.c" =>
                [
                    "test/generate_buildtest.pl",
                    "txt_db",
                ],
            "test/buildtest_ui.c" =>
                [
                    "test/generate_buildtest.pl",
                    "ui",
                ],
            "test/buildtest_whrlpool.c" =>
                [
                    "test/generate_buildtest.pl",
                    "whrlpool",
                ],
            "test/buildtest_x509.c" =>
                [
                    "test/generate_buildtest.pl",
                    "x509",
                ],
            "test/buildtest_x509_vfy.c" =>
                [
                    "test/generate_buildtest.pl",
                    "x509_vfy",
                ],
            "test/buildtest_x509v3.c" =>
                [
                    "test/generate_buildtest.pl",
                    "x509v3",
                ],
            "test/p_test.ld" =>
                [
                    "util/providers.num",
                ],
            "test/provider_internal_test.conf" =>
                [
                    "test/provider_internal_test.conf.in",
                ],
        },
    "includes" =>
        {
            "apps/asn1pars.o" =>
                [
                    "apps",
                ],
            "apps/ca.o" =>
                [
                    "apps",
                ],
            "apps/ciphers.o" =>
                [
                    "apps",
                ],
            "apps/cms.o" =>
                [
                    "apps",
                ],
            "apps/crl.o" =>
                [
                    "apps",
                ],
            "apps/crl2p7.o" =>
                [
                    "apps",
                ],
            "apps/dgst.o" =>
                [
                    "apps",
                ],
            "apps/dhparam.o" =>
                [
                    "apps",
                ],
            "apps/dsa.o" =>
                [
                    "apps",
                ],
            "apps/dsaparam.o" =>
                [
                    "apps",
                ],
            "apps/ec.o" =>
                [
                    "apps",
                ],
            "apps/ecparam.o" =>
                [
                    "apps",
                ],
            "apps/enc.o" =>
                [
                    "apps",
                ],
            "apps/engine.o" =>
                [
                    "apps",
                ],
            "apps/errstr.o" =>
                [
                    "apps",
                ],
            "apps/gendsa.o" =>
                [
                    "apps",
                ],
            "apps/genpkey.o" =>
                [
                    "apps",
                ],
            "apps/genrsa.o" =>
                [
                    "apps",
                ],
            "apps/libapps.a" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "apps/mac.o" =>
                [
                    "apps",
                ],
            "apps/nseq.o" =>
                [
                    "apps",
                ],
            "apps/ocsp.o" =>
                [
                    "apps",
                ],
            "apps/openssl" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "apps/openssl-bin-asn1pars.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-ca.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-ciphers.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-cms.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-crl.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-crl2p7.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-dgst.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-dhparam.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-dsa.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-dsaparam.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-ec.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-ecparam.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-enc.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-engine.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-errstr.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-gendsa.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-genpkey.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-genrsa.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-mac.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-nseq.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-ocsp.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-openssl.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-passwd.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-pkcs12.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-pkcs7.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-pkcs8.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-pkey.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-pkeyparam.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-pkeyutl.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-prime.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-rand.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-rehash.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-req.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-rsa.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-rsautl.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-s_client.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-s_server.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-s_time.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-sess_id.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-smime.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-speed.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-spkac.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-srp.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-storeutl.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-ts.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-verify.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-version.o" =>
                [
                    "apps",
                ],
            "apps/openssl-bin-x509.o" =>
                [
                    "apps",
                ],
            "apps/openssl.o" =>
                [
                    "apps",
                ],
            "apps/passwd.o" =>
                [
                    "apps",
                ],
            "apps/pkcs12.o" =>
                [
                    "apps",
                ],
            "apps/pkcs7.o" =>
                [
                    "apps",
                ],
            "apps/pkcs8.o" =>
                [
                    "apps",
                ],
            "apps/pkey.o" =>
                [
                    "apps",
                ],
            "apps/pkeyparam.o" =>
                [
                    "apps",
                ],
            "apps/pkeyutl.o" =>
                [
                    "apps",
                ],
            "apps/prime.o" =>
                [
                    "apps",
                ],
            "apps/progs.h" =>
                [
                    ".",
                ],
            "apps/rand.o" =>
                [
                    "apps",
                ],
            "apps/rehash.o" =>
                [
                    "apps",
                ],
            "apps/req.o" =>
                [
                    "apps",
                ],
            "apps/rsa.o" =>
                [
                    "apps",
                ],
            "apps/rsautl.o" =>
                [
                    "apps",
                ],
            "apps/s_client.o" =>
                [
                    "apps",
                ],
            "apps/s_server.o" =>
                [
                    "apps",
                ],
            "apps/s_time.o" =>
                [
                    "apps",
                ],
            "apps/sess_id.o" =>
                [
                    "apps",
                ],
            "apps/smime.o" =>
                [
                    "apps",
                ],
            "apps/speed.o" =>
                [
                    "apps",
                ],
            "apps/spkac.o" =>
                [
                    "apps",
                ],
            "apps/srp.o" =>
                [
                    "apps",
                ],
            "apps/storeutl.o" =>
                [
                    "apps",
                ],
            "apps/ts.o" =>
                [
                    "apps",
                ],
            "apps/verify.o" =>
                [
                    "apps",
                ],
            "apps/version.o" =>
                [
                    "apps",
                ],
            "apps/x509.o" =>
                [
                    "apps",
                ],
            "crypto/aes/aes-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/aes-mips.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/aes-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/aes-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/aesfx-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/aest4-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/aesv8-armx.o" =>
                [
                    "crypto",
                ],
            "crypto/aes/bsaes-armv7.o" =>
                [
                    "crypto",
                ],
            "crypto/arm64cpuid.o" =>
                [
                    "crypto",
                ],
            "crypto/armv4cpuid.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/armv4-gf2m.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/armv4-mont.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/bn-mips.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/bn_exp.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/libcrypto-lib-bn_exp.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/libcrypto-shlib-bn_exp.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/mips-mont.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/sparct4-mont.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/sparcv9-gf2m.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/sparcv9-mont.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/sparcv9a-mont.o" =>
                [
                    "crypto",
                ],
            "crypto/bn/vis3-mont.o" =>
                [
                    "crypto",
                ],
            "crypto/buildinf.h" =>
                [
                    ".",
                ],
            "crypto/camellia/cmllt4-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/chacha/chacha-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/chacha/chacha-armv8.o" =>
                [
                    "crypto",
                ],
            "crypto/chacha/chacha-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/cversion.o" =>
                [
                    "crypto",
                ],
            "crypto/des/dest4-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/ec/curve448/arch_32/f_impl.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/arch_32/libcrypto-lib-f_impl.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/arch_32/libcrypto-shlib-f_impl.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/curve448.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/curve448_tables.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/eddsa.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/f_generic.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-lib-curve448.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-lib-curve448_tables.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-lib-eddsa.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-lib-f_generic.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-lib-scalar.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-shlib-curve448.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-shlib-curve448_tables.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-shlib-eddsa.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-shlib-f_generic.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/libcrypto-shlib-scalar.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/curve448/scalar.o" =>
                [
                    "crypto/ec/curve448/arch_32",
                    "crypto/ec/curve448",
                ],
            "crypto/ec/ecp_nistz256-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/ec/ecp_nistz256-armv8.o" =>
                [
                    "crypto",
                ],
            "crypto/ec/ecp_nistz256-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/e_aes.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/e_aes_cbc_hmac_sha1.o" =>
                [
                    "crypto/modes",
                ],
            "crypto/evp/e_aes_cbc_hmac_sha256.o" =>
                [
                    "crypto/modes",
                ],
            "crypto/evp/e_aria.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/e_camellia.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/e_des.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/e_des3.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/e_sm4.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-e_aes.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha1.o" =>
                [
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha256.o" =>
                [
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-e_aria.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-e_camellia.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-e_des.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/libcrypto-lib-e_des3.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/libcrypto-lib-e_sm4.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-lib-m_sha3.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/libcrypto-shlib-e_aes.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha1.o" =>
                [
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha256.o" =>
                [
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-shlib-e_aria.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-shlib-e_camellia.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-shlib-e_des.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/libcrypto-shlib-e_des3.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/libcrypto-shlib-e_sm4.o" =>
                [
                    "crypto",
                    "crypto/modes",
                ],
            "crypto/evp/libcrypto-shlib-m_sha3.o" =>
                [
                    "crypto",
                ],
            "crypto/evp/m_sha3.o" =>
                [
                    "crypto",
                ],
            "crypto/include/internal/bn_conf.h" =>
                [
                    ".",
                ],
            "crypto/include/internal/dso_conf.h" =>
                [
                    ".",
                ],
            "crypto/libcrypto-lib-cversion.o" =>
                [
                    "crypto",
                ],
            "crypto/libcrypto-shlib-cversion.o" =>
                [
                    "crypto",
                ],
            "crypto/md5/md5-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/gcm128.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/ghash-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/ghash-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/ghash-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/ghashv8-armx.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/libcrypto-lib-gcm128.o" =>
                [
                    "crypto",
                ],
            "crypto/modes/libcrypto-shlib-gcm128.o" =>
                [
                    "crypto",
                ],
            "crypto/poly1305/poly1305-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/poly1305/poly1305-armv8.o" =>
                [
                    "crypto",
                ],
            "crypto/poly1305/poly1305-mips.o" =>
                [
                    "crypto",
                ],
            "crypto/poly1305/poly1305-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/poly1305/poly1305-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/s390xcpuid.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/keccak1600-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha1-armv4-large.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha1-armv8.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha1-mips.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha1-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha1-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha256-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha256-armv8.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha256-mips.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha256-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha256-sparcv9.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha512-armv4.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha512-armv8.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha512-mips.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha512-s390x.o" =>
                [
                    "crypto",
                ],
            "crypto/sha/sha512-sparcv9.o" =>
                [
                    "crypto",
                ],
            "doc/man7/openssl_user_macros.pod" =>
                [
                    ".",
                ],
            "engines/afalg" =>
                [
                    "include",
                ],
            "engines/capi" =>
                [
                    "include",
                ],
            "engines/dasync" =>
                [
                    "include",
                ],
            "engines/ossltest" =>
                [
                    "include",
                ],
            "engines/padlock" =>
                [
                    "include",
                ],
            "fuzz/asn1-test" =>
                [
                    "include",
                ],
            "fuzz/asn1parse-test" =>
                [
                    "include",
                ],
            "fuzz/bignum-test" =>
                [
                    "include",
                ],
            "fuzz/bndiv-test" =>
                [
                    "include",
                ],
            "fuzz/client-test" =>
                [
                    "include",
                ],
            "fuzz/cms-test" =>
                [
                    "include",
                ],
            "fuzz/conf-test" =>
                [
                    "include",
                ],
            "fuzz/crl-test" =>
                [
                    "include",
                ],
            "fuzz/ct-test" =>
                [
                    "include",
                ],
            "fuzz/server-test" =>
                [
                    "include",
                ],
            "fuzz/x509-test" =>
                [
                    "include",
                ],
            "include/openssl/opensslconf.h" =>
                [
                    ".",
                ],
            "libcrypto" =>
                [
                    ".",
                    "crypto/include",
                    "include",
                ],
            "libssl" =>
                [
                    ".",
                    "include",
                ],
            "providers/fips" =>
                [
                    ".",
                    "include",
                    "crypto/include",
                ],
            "test/aborttest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/aesgcmtest" =>
                [
                    "include",
                    "apps/include",
                    ".",
                ],
            "test/afalgtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/asn1_decode_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/asn1_encode_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/asn1_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/asn1_string_table_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/asn1_time_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/asynciotest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/asynciotest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/asynctest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bad_dtls_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bftest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bio_callback_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bio_enc_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bio_memleak_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bioprinttest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/bn_internal_test" =>
                [
                    ".",
                    "include",
                    "crypto/include",
                    "crypto/bn",
                    "apps/include",
                ],
            "test/bntest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/buildtest_c_aes" =>
                [
                    "include",
                ],
            "test/buildtest_c_asn1" =>
                [
                    "include",
                ],
            "test/buildtest_c_asn1t" =>
                [
                    "include",
                ],
            "test/buildtest_c_async" =>
                [
                    "include",
                ],
            "test/buildtest_c_bio" =>
                [
                    "include",
                ],
            "test/buildtest_c_blowfish" =>
                [
                    "include",
                ],
            "test/buildtest_c_bn" =>
                [
                    "include",
                ],
            "test/buildtest_c_buffer" =>
                [
                    "include",
                ],
            "test/buildtest_c_camellia" =>
                [
                    "include",
                ],
            "test/buildtest_c_cast" =>
                [
                    "include",
                ],
            "test/buildtest_c_cmac" =>
                [
                    "include",
                ],
            "test/buildtest_c_cms" =>
                [
                    "include",
                ],
            "test/buildtest_c_comp" =>
                [
                    "include",
                ],
            "test/buildtest_c_conf" =>
                [
                    "include",
                ],
            "test/buildtest_c_conf_api" =>
                [
                    "include",
                ],
            "test/buildtest_c_core" =>
                [
                    "include",
                ],
            "test/buildtest_c_core_names" =>
                [
                    "include",
                ],
            "test/buildtest_c_core_numbers" =>
                [
                    "include",
                ],
            "test/buildtest_c_crmf" =>
                [
                    "include",
                ],
            "test/buildtest_c_crypto" =>
                [
                    "include",
                ],
            "test/buildtest_c_ct" =>
                [
                    "include",
                ],
            "test/buildtest_c_des" =>
                [
                    "include",
                ],
            "test/buildtest_c_dh" =>
                [
                    "include",
                ],
            "test/buildtest_c_dsa" =>
                [
                    "include",
                ],
            "test/buildtest_c_dtls1" =>
                [
                    "include",
                ],
            "test/buildtest_c_e_os2" =>
                [
                    "include",
                ],
            "test/buildtest_c_ebcdic" =>
                [
                    "include",
                ],
            "test/buildtest_c_ec" =>
                [
                    "include",
                ],
            "test/buildtest_c_ecdh" =>
                [
                    "include",
                ],
            "test/buildtest_c_ecdsa" =>
                [
                    "include",
                ],
            "test/buildtest_c_engine" =>
                [
                    "include",
                ],
            "test/buildtest_c_ess" =>
                [
                    "include",
                ],
            "test/buildtest_c_evp" =>
                [
                    "include",
                ],
            "test/buildtest_c_hmac" =>
                [
                    "include",
                ],
            "test/buildtest_c_idea" =>
                [
                    "include",
                ],
            "test/buildtest_c_kdf" =>
                [
                    "include",
                ],
            "test/buildtest_c_lhash" =>
                [
                    "include",
                ],
            "test/buildtest_c_md4" =>
                [
                    "include",
                ],
            "test/buildtest_c_md5" =>
                [
                    "include",
                ],
            "test/buildtest_c_mdc2" =>
                [
                    "include",
                ],
            "test/buildtest_c_modes" =>
                [
                    "include",
                ],
            "test/buildtest_c_obj_mac" =>
                [
                    "include",
                ],
            "test/buildtest_c_objects" =>
                [
                    "include",
                ],
            "test/buildtest_c_ocsp" =>
                [
                    "include",
                ],
            "test/buildtest_c_opensslv" =>
                [
                    "include",
                ],
            "test/buildtest_c_ossl_typ" =>
                [
                    "include",
                ],
            "test/buildtest_c_params" =>
                [
                    "include",
                ],
            "test/buildtest_c_pem" =>
                [
                    "include",
                ],
            "test/buildtest_c_pem2" =>
                [
                    "include",
                ],
            "test/buildtest_c_pkcs12" =>
                [
                    "include",
                ],
            "test/buildtest_c_pkcs7" =>
                [
                    "include",
                ],
            "test/buildtest_c_provider" =>
                [
                    "include",
                ],
            "test/buildtest_c_rand" =>
                [
                    "include",
                ],
            "test/buildtest_c_rand_drbg" =>
                [
                    "include",
                ],
            "test/buildtest_c_rc2" =>
                [
                    "include",
                ],
            "test/buildtest_c_rc4" =>
                [
                    "include",
                ],
            "test/buildtest_c_ripemd" =>
                [
                    "include",
                ],
            "test/buildtest_c_rsa" =>
                [
                    "include",
                ],
            "test/buildtest_c_safestack" =>
                [
                    "include",
                ],
            "test/buildtest_c_seed" =>
                [
                    "include",
                ],
            "test/buildtest_c_sha" =>
                [
                    "include",
                ],
            "test/buildtest_c_srp" =>
                [
                    "include",
                ],
            "test/buildtest_c_srtp" =>
                [
                    "include",
                ],
            "test/buildtest_c_ssl" =>
                [
                    "include",
                ],
            "test/buildtest_c_ssl2" =>
                [
                    "include",
                ],
            "test/buildtest_c_stack" =>
                [
                    "include",
                ],
            "test/buildtest_c_store" =>
                [
                    "include",
                ],
            "test/buildtest_c_symhacks" =>
                [
                    "include",
                ],
            "test/buildtest_c_tls1" =>
                [
                    "include",
                ],
            "test/buildtest_c_ts" =>
                [
                    "include",
                ],
            "test/buildtest_c_txt_db" =>
                [
                    "include",
                ],
            "test/buildtest_c_ui" =>
                [
                    "include",
                ],
            "test/buildtest_c_whrlpool" =>
                [
                    "include",
                ],
            "test/buildtest_c_x509" =>
                [
                    "include",
                ],
            "test/buildtest_c_x509_vfy" =>
                [
                    "include",
                ],
            "test/buildtest_c_x509v3" =>
                [
                    "include",
                ],
            "test/casttest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/chacha_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/cipherbytes_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/cipherlist_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ciphername_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/clienthellotest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/cmsapitest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/conf_include_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/constant_time_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/context_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/crltest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ct_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ctype_internal_test" =>
                [
                    ".",
                    "crypto/include",
                    "include",
                    "apps/include",
                ],
            "test/curve448_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                    "crypto/ec/curve448",
                ],
            "test/d2i_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/danetest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/destest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/dhtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/drbg_cavs_test" =>
                [
                    "include",
                    "apps/include",
                    "test",
                    ".",
                ],
            "test/drbgtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/dsa_no_digest_size_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/dsatest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/dtls_mtu_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/dtls_mtu_test-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/dtlstest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/dtlstest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/dtlsv1listentest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ec_internal_test" =>
                [
                    "include",
                    "crypto/ec",
                    "apps/include",
                    "crypto/include",
                ],
            "test/ecdsatest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ecstresstest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ectest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/enginetest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/errtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/evp_extra_test" =>
                [
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/evp_kdf_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/evp_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/exdatatest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/exptest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/fatalerrtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/fatalerrtest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/gmdifftest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/gosttest" =>
                [
                    "include",
                    "apps/include",
                    ".",
                ],
            "test/gosttest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/handshake_helper.o" =>
                [
                    ".",
                    "include",
                ],
            "test/hmactest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ideatest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/igetest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/lhash_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/libtestutil.a" =>
                [
                    "include",
                    "apps/include",
                    ".",
                ],
            "test/md2test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/mdc2_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/mdc2test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/memleaktest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/modes_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/ocspapitest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/p_test" =>
                [
                    "include",
                ],
            "test/packettest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/params_api_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/params_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/pbelutest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/pemtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/pkey_meth_kdf_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/pkey_meth_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/poly1305_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/property_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/provider_internal_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/provider_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/rc2test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/rc4test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/rc5test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/rdrand_sanitytest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/recordlentest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/recordlentest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/rsa_complex" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/rsa_mp_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/rsa_sp800_56b_test" =>
                [
                    ".",
                    "include",
                    "crypto/include",
                    "crypto/rsa",
                    "apps/include",
                ],
            "test/rsa_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/sanitytest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/secmemtest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/servername_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/servername_test-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/shlibloadtest" =>
                [
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/siphash_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/sm2_internal_test" =>
                [
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/sm4_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                    "crypto/include",
                ],
            "test/sparse_array_test" =>
                [
                    "crypto/include",
                    "include",
                    "apps/include",
                ],
            "test/srptest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ssl_cert_table_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/ssl_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ssl_test-bin-handshake_helper.o" =>
                [
                    ".",
                    "include",
                ],
            "test/ssl_test-bin-ssl_test_ctx.o" =>
                [
                    "include",
                ],
            "test/ssl_test_ctx.o" =>
                [
                    "include",
                ],
            "test/ssl_test_ctx_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/ssl_test_ctx_test-bin-ssl_test_ctx.o" =>
                [
                    "include",
                ],
            "test/sslapitest" =>
                [
                    "include",
                    "apps/include",
                    ".",
                ],
            "test/sslapitest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/sslbuffertest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/sslbuffertest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/sslcorrupttest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/sslcorrupttest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/ssltest_old" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/stack_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/sysdefaulttest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/test_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/threadstest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/time_offset_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/tls13ccstest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/tls13ccstest-bin-ssltestlib.o" =>
                [
                    ".",
                    "include",
                ],
            "test/tls13encryptiontest" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/tls13secretstest" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/uitest" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/v3ext" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/v3nametest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/verify_extra_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/versions" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/wpackettest" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/x509_check_cert_pkey_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/x509_dup_cert_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/x509_internal_test" =>
                [
                    ".",
                    "include",
                    "apps/include",
                ],
            "test/x509_time_test" =>
                [
                    "include",
                    "apps/include",
                ],
            "test/x509aux" =>
                [
                    "include",
                    "apps/include",
                ],
        },
    "ldadd" =>
        {
        },
    "libraries" =>
        [
            "apps/libapps.a",
            "libcrypto",
            "libssl",
            "test/libtestutil.a",
        ],
    "modules" =>
        [
            "engines/afalg",
            "engines/capi",
            "engines/dasync",
            "engines/ossltest",
            "engines/padlock",
            "providers/fips",
            "test/p_test",
        ],
    "programs" =>
        [
            "apps/openssl",
            "fuzz/asn1-test",
            "fuzz/asn1parse-test",
            "fuzz/bignum-test",
            "fuzz/bndiv-test",
            "fuzz/client-test",
            "fuzz/cms-test",
            "fuzz/conf-test",
            "fuzz/crl-test",
            "fuzz/ct-test",
            "fuzz/server-test",
            "fuzz/x509-test",
            "test/aborttest",
            "test/aesgcmtest",
            "test/afalgtest",
            "test/asn1_decode_test",
            "test/asn1_encode_test",
            "test/asn1_internal_test",
            "test/asn1_string_table_test",
            "test/asn1_time_test",
            "test/asynciotest",
            "test/asynctest",
            "test/bad_dtls_test",
            "test/bftest",
            "test/bio_callback_test",
            "test/bio_enc_test",
            "test/bio_memleak_test",
            "test/bioprinttest",
            "test/bn_internal_test",
            "test/bntest",
            "test/buildtest_c_aes",
            "test/buildtest_c_asn1",
            "test/buildtest_c_asn1t",
            "test/buildtest_c_async",
            "test/buildtest_c_bio",
            "test/buildtest_c_blowfish",
            "test/buildtest_c_bn",
            "test/buildtest_c_buffer",
            "test/buildtest_c_camellia",
            "test/buildtest_c_cast",
            "test/buildtest_c_cmac",
            "test/buildtest_c_cms",
            "test/buildtest_c_comp",
            "test/buildtest_c_conf",
            "test/buildtest_c_conf_api",
            "test/buildtest_c_core",
            "test/buildtest_c_core_names",
            "test/buildtest_c_core_numbers",
            "test/buildtest_c_crmf",
            "test/buildtest_c_crypto",
            "test/buildtest_c_ct",
            "test/buildtest_c_des",
            "test/buildtest_c_dh",
            "test/buildtest_c_dsa",
            "test/buildtest_c_dtls1",
            "test/buildtest_c_e_os2",
            "test/buildtest_c_ebcdic",
            "test/buildtest_c_ec",
            "test/buildtest_c_ecdh",
            "test/buildtest_c_ecdsa",
            "test/buildtest_c_engine",
            "test/buildtest_c_ess",
            "test/buildtest_c_evp",
            "test/buildtest_c_hmac",
            "test/buildtest_c_idea",
            "test/buildtest_c_kdf",
            "test/buildtest_c_lhash",
            "test/buildtest_c_md4",
            "test/buildtest_c_md5",
            "test/buildtest_c_mdc2",
            "test/buildtest_c_modes",
            "test/buildtest_c_obj_mac",
            "test/buildtest_c_objects",
            "test/buildtest_c_ocsp",
            "test/buildtest_c_opensslv",
            "test/buildtest_c_ossl_typ",
            "test/buildtest_c_params",
            "test/buildtest_c_pem",
            "test/buildtest_c_pem2",
            "test/buildtest_c_pkcs12",
            "test/buildtest_c_pkcs7",
            "test/buildtest_c_provider",
            "test/buildtest_c_rand",
            "test/buildtest_c_rand_drbg",
            "test/buildtest_c_rc2",
            "test/buildtest_c_rc4",
            "test/buildtest_c_ripemd",
            "test/buildtest_c_rsa",
            "test/buildtest_c_safestack",
            "test/buildtest_c_seed",
            "test/buildtest_c_sha",
            "test/buildtest_c_srp",
            "test/buildtest_c_srtp",
            "test/buildtest_c_ssl",
            "test/buildtest_c_ssl2",
            "test/buildtest_c_stack",
            "test/buildtest_c_store",
            "test/buildtest_c_symhacks",
            "test/buildtest_c_tls1",
            "test/buildtest_c_ts",
            "test/buildtest_c_txt_db",
            "test/buildtest_c_ui",
            "test/buildtest_c_whrlpool",
            "test/buildtest_c_x509",
            "test/buildtest_c_x509_vfy",
            "test/buildtest_c_x509v3",
            "test/casttest",
            "test/chacha_internal_test",
            "test/cipherbytes_test",
            "test/cipherlist_test",
            "test/ciphername_test",
            "test/clienthellotest",
            "test/cmsapitest",
            "test/conf_include_test",
            "test/constant_time_test",
            "test/context_internal_test",
            "test/crltest",
            "test/ct_test",
            "test/ctype_internal_test",
            "test/curve448_internal_test",
            "test/d2i_test",
            "test/danetest",
            "test/destest",
            "test/dhtest",
            "test/drbg_cavs_test",
            "test/drbgtest",
            "test/dsa_no_digest_size_test",
            "test/dsatest",
            "test/dtls_mtu_test",
            "test/dtlstest",
            "test/dtlsv1listentest",
            "test/ec_internal_test",
            "test/ecdsatest",
            "test/ecstresstest",
            "test/ectest",
            "test/enginetest",
            "test/errtest",
            "test/evp_extra_test",
            "test/evp_kdf_test",
            "test/evp_test",
            "test/exdatatest",
            "test/exptest",
            "test/fatalerrtest",
            "test/gmdifftest",
            "test/gosttest",
            "test/hmactest",
            "test/ideatest",
            "test/igetest",
            "test/lhash_test",
            "test/md2test",
            "test/mdc2_internal_test",
            "test/mdc2test",
            "test/memleaktest",
            "test/modes_internal_test",
            "test/ocspapitest",
            "test/packettest",
            "test/params_api_test",
            "test/params_test",
            "test/pbelutest",
            "test/pemtest",
            "test/pkey_meth_kdf_test",
            "test/pkey_meth_test",
            "test/poly1305_internal_test",
            "test/property_test",
            "test/provider_internal_test",
            "test/provider_test",
            "test/rc2test",
            "test/rc4test",
            "test/rc5test",
            "test/rdrand_sanitytest",
            "test/recordlentest",
            "test/rsa_complex",
            "test/rsa_mp_test",
            "test/rsa_sp800_56b_test",
            "test/rsa_test",
            "test/sanitytest",
            "test/secmemtest",
            "test/servername_test",
            "test/shlibloadtest",
            "test/siphash_internal_test",
            "test/sm2_internal_test",
            "test/sm4_internal_test",
            "test/sparse_array_test",
            "test/srptest",
            "test/ssl_cert_table_internal_test",
            "test/ssl_test",
            "test/ssl_test_ctx_test",
            "test/sslapitest",
            "test/sslbuffertest",
            "test/sslcorrupttest",
            "test/ssltest_old",
            "test/stack_test",
            "test/sysdefaulttest",
            "test/test_test",
            "test/threadstest",
            "test/time_offset_test",
            "test/tls13ccstest",
            "test/tls13encryptiontest",
            "test/tls13secretstest",
            "test/uitest",
            "test/v3ext",
            "test/v3nametest",
            "test/verify_extra_test",
            "test/versions",
            "test/wpackettest",
            "test/x509_check_cert_pkey_test",
            "test/x509_dup_cert_test",
            "test/x509_internal_test",
            "test/x509_time_test",
            "test/x509aux",
        ],
    "rename" =>
        {
        },
    "scripts" =>
        [
            "apps/CA.pl",
            "apps/tsget.pl",
            "tools/c_rehash",
            "util/shlib_wrap.sh",
        ],
    "shared_sources" =>
        {
            "libcrypto" =>
                [
                    "crypto/aes/libcrypto-shlib-aes-x86_64.o",
                    "crypto/aes/libcrypto-shlib-aes_cfb.o",
                    "crypto/aes/libcrypto-shlib-aes_ecb.o",
                    "crypto/aes/libcrypto-shlib-aes_ige.o",
                    "crypto/aes/libcrypto-shlib-aes_misc.o",
                    "crypto/aes/libcrypto-shlib-aes_ofb.o",
                    "crypto/aes/libcrypto-shlib-aes_wrap.o",
                    "crypto/aes/libcrypto-shlib-aesni-mb-x86_64.o",
                    "crypto/aes/libcrypto-shlib-aesni-sha1-x86_64.o",
                    "crypto/aes/libcrypto-shlib-aesni-sha256-x86_64.o",
                    "crypto/aes/libcrypto-shlib-aesni-x86_64.o",
                    "crypto/aes/libcrypto-shlib-bsaes-x86_64.o",
                    "crypto/aes/libcrypto-shlib-vpaes-x86_64.o",
                    "crypto/aria/libcrypto-shlib-aria.o",
                    "crypto/asn1/libcrypto-shlib-a_bitstr.o",
                    "crypto/asn1/libcrypto-shlib-a_d2i_fp.o",
                    "crypto/asn1/libcrypto-shlib-a_digest.o",
                    "crypto/asn1/libcrypto-shlib-a_dup.o",
                    "crypto/asn1/libcrypto-shlib-a_gentm.o",
                    "crypto/asn1/libcrypto-shlib-a_i2d_fp.o",
                    "crypto/asn1/libcrypto-shlib-a_int.o",
                    "crypto/asn1/libcrypto-shlib-a_mbstr.o",
                    "crypto/asn1/libcrypto-shlib-a_object.o",
                    "crypto/asn1/libcrypto-shlib-a_octet.o",
                    "crypto/asn1/libcrypto-shlib-a_print.o",
                    "crypto/asn1/libcrypto-shlib-a_sign.o",
                    "crypto/asn1/libcrypto-shlib-a_strex.o",
                    "crypto/asn1/libcrypto-shlib-a_strnid.o",
                    "crypto/asn1/libcrypto-shlib-a_time.o",
                    "crypto/asn1/libcrypto-shlib-a_type.o",
                    "crypto/asn1/libcrypto-shlib-a_utctm.o",
                    "crypto/asn1/libcrypto-shlib-a_utf8.o",
                    "crypto/asn1/libcrypto-shlib-a_verify.o",
                    "crypto/asn1/libcrypto-shlib-ameth_lib.o",
                    "crypto/asn1/libcrypto-shlib-asn1_err.o",
                    "crypto/asn1/libcrypto-shlib-asn1_gen.o",
                    "crypto/asn1/libcrypto-shlib-asn1_item_list.o",
                    "crypto/asn1/libcrypto-shlib-asn1_lib.o",
                    "crypto/asn1/libcrypto-shlib-asn1_par.o",
                    "crypto/asn1/libcrypto-shlib-asn_mime.o",
                    "crypto/asn1/libcrypto-shlib-asn_moid.o",
                    "crypto/asn1/libcrypto-shlib-asn_mstbl.o",
                    "crypto/asn1/libcrypto-shlib-asn_pack.o",
                    "crypto/asn1/libcrypto-shlib-bio_asn1.o",
                    "crypto/asn1/libcrypto-shlib-bio_ndef.o",
                    "crypto/asn1/libcrypto-shlib-d2i_pr.o",
                    "crypto/asn1/libcrypto-shlib-d2i_pu.o",
                    "crypto/asn1/libcrypto-shlib-evp_asn1.o",
                    "crypto/asn1/libcrypto-shlib-f_int.o",
                    "crypto/asn1/libcrypto-shlib-f_string.o",
                    "crypto/asn1/libcrypto-shlib-i2d_pr.o",
                    "crypto/asn1/libcrypto-shlib-i2d_pu.o",
                    "crypto/asn1/libcrypto-shlib-n_pkey.o",
                    "crypto/asn1/libcrypto-shlib-nsseq.o",
                    "crypto/asn1/libcrypto-shlib-p5_pbe.o",
                    "crypto/asn1/libcrypto-shlib-p5_pbev2.o",
                    "crypto/asn1/libcrypto-shlib-p5_scrypt.o",
                    "crypto/asn1/libcrypto-shlib-p8_pkey.o",
                    "crypto/asn1/libcrypto-shlib-t_bitst.o",
                    "crypto/asn1/libcrypto-shlib-t_pkey.o",
                    "crypto/asn1/libcrypto-shlib-t_spki.o",
                    "crypto/asn1/libcrypto-shlib-tasn_dec.o",
                    "crypto/asn1/libcrypto-shlib-tasn_enc.o",
                    "crypto/asn1/libcrypto-shlib-tasn_fre.o",
                    "crypto/asn1/libcrypto-shlib-tasn_new.o",
                    "crypto/asn1/libcrypto-shlib-tasn_prn.o",
                    "crypto/asn1/libcrypto-shlib-tasn_scn.o",
                    "crypto/asn1/libcrypto-shlib-tasn_typ.o",
                    "crypto/asn1/libcrypto-shlib-tasn_utl.o",
                    "crypto/asn1/libcrypto-shlib-x_algor.o",
                    "crypto/asn1/libcrypto-shlib-x_bignum.o",
                    "crypto/asn1/libcrypto-shlib-x_info.o",
                    "crypto/asn1/libcrypto-shlib-x_int64.o",
                    "crypto/asn1/libcrypto-shlib-x_long.o",
                    "crypto/asn1/libcrypto-shlib-x_pkey.o",
                    "crypto/asn1/libcrypto-shlib-x_sig.o",
                    "crypto/asn1/libcrypto-shlib-x_spki.o",
                    "crypto/asn1/libcrypto-shlib-x_val.o",
                    "crypto/async/arch/libcrypto-shlib-async_null.o",
                    "crypto/async/arch/libcrypto-shlib-async_posix.o",
                    "crypto/async/arch/libcrypto-shlib-async_win.o",
                    "crypto/async/libcrypto-shlib-async.o",
                    "crypto/async/libcrypto-shlib-async_err.o",
                    "crypto/async/libcrypto-shlib-async_wait.o",
                    "crypto/bf/libcrypto-shlib-bf_cfb64.o",
                    "crypto/bf/libcrypto-shlib-bf_ecb.o",
                    "crypto/bf/libcrypto-shlib-bf_enc.o",
                    "crypto/bf/libcrypto-shlib-bf_ofb64.o",
                    "crypto/bf/libcrypto-shlib-bf_skey.o",
                    "crypto/bio/libcrypto-shlib-b_addr.o",
                    "crypto/bio/libcrypto-shlib-b_dump.o",
                    "crypto/bio/libcrypto-shlib-b_print.o",
                    "crypto/bio/libcrypto-shlib-b_sock.o",
                    "crypto/bio/libcrypto-shlib-b_sock2.o",
                    "crypto/bio/libcrypto-shlib-bf_buff.o",
                    "crypto/bio/libcrypto-shlib-bf_lbuf.o",
                    "crypto/bio/libcrypto-shlib-bf_nbio.o",
                    "crypto/bio/libcrypto-shlib-bf_null.o",
                    "crypto/bio/libcrypto-shlib-bio_cb.o",
                    "crypto/bio/libcrypto-shlib-bio_err.o",
                    "crypto/bio/libcrypto-shlib-bio_lib.o",
                    "crypto/bio/libcrypto-shlib-bio_meth.o",
                    "crypto/bio/libcrypto-shlib-bss_acpt.o",
                    "crypto/bio/libcrypto-shlib-bss_bio.o",
                    "crypto/bio/libcrypto-shlib-bss_conn.o",
                    "crypto/bio/libcrypto-shlib-bss_dgram.o",
                    "crypto/bio/libcrypto-shlib-bss_fd.o",
                    "crypto/bio/libcrypto-shlib-bss_file.o",
                    "crypto/bio/libcrypto-shlib-bss_log.o",
                    "crypto/bio/libcrypto-shlib-bss_mem.o",
                    "crypto/bio/libcrypto-shlib-bss_null.o",
                    "crypto/bio/libcrypto-shlib-bss_sock.o",
                    "crypto/blake2/libcrypto-shlib-blake2b.o",
                    "crypto/blake2/libcrypto-shlib-blake2b_mac.o",
                    "crypto/blake2/libcrypto-shlib-blake2s.o",
                    "crypto/blake2/libcrypto-shlib-blake2s_mac.o",
                    "crypto/blake2/libcrypto-shlib-m_blake2b.o",
                    "crypto/blake2/libcrypto-shlib-m_blake2s.o",
                    "crypto/bn/asm/libcrypto-shlib-x86_64-gcc.o",
                    "crypto/bn/libcrypto-shlib-bn_add.o",
                    "crypto/bn/libcrypto-shlib-bn_blind.o",
                    "crypto/bn/libcrypto-shlib-bn_const.o",
                    "crypto/bn/libcrypto-shlib-bn_ctx.o",
                    "crypto/bn/libcrypto-shlib-bn_depr.o",
                    "crypto/bn/libcrypto-shlib-bn_dh.o",
                    "crypto/bn/libcrypto-shlib-bn_div.o",
                    "crypto/bn/libcrypto-shlib-bn_err.o",
                    "crypto/bn/libcrypto-shlib-bn_exp.o",
                    "crypto/bn/libcrypto-shlib-bn_exp2.o",
                    "crypto/bn/libcrypto-shlib-bn_gcd.o",
                    "crypto/bn/libcrypto-shlib-bn_gf2m.o",
                    "crypto/bn/libcrypto-shlib-bn_intern.o",
                    "crypto/bn/libcrypto-shlib-bn_kron.o",
                    "crypto/bn/libcrypto-shlib-bn_lib.o",
                    "crypto/bn/libcrypto-shlib-bn_mod.o",
                    "crypto/bn/libcrypto-shlib-bn_mont.o",
                    "crypto/bn/libcrypto-shlib-bn_mpi.o",
                    "crypto/bn/libcrypto-shlib-bn_mul.o",
                    "crypto/bn/libcrypto-shlib-bn_nist.o",
                    "crypto/bn/libcrypto-shlib-bn_prime.o",
                    "crypto/bn/libcrypto-shlib-bn_print.o",
                    "crypto/bn/libcrypto-shlib-bn_rand.o",
                    "crypto/bn/libcrypto-shlib-bn_recp.o",
                    "crypto/bn/libcrypto-shlib-bn_rsa_fips186_4.o",
                    "crypto/bn/libcrypto-shlib-bn_shift.o",
                    "crypto/bn/libcrypto-shlib-bn_sqr.o",
                    "crypto/bn/libcrypto-shlib-bn_sqrt.o",
                    "crypto/bn/libcrypto-shlib-bn_srp.o",
                    "crypto/bn/libcrypto-shlib-bn_word.o",
                    "crypto/bn/libcrypto-shlib-bn_x931p.o",
                    "crypto/bn/libcrypto-shlib-rsaz-avx2.o",
                    "crypto/bn/libcrypto-shlib-rsaz-x86_64.o",
                    "crypto/bn/libcrypto-shlib-rsaz_exp.o",
                    "crypto/bn/libcrypto-shlib-x86_64-gf2m.o",
                    "crypto/bn/libcrypto-shlib-x86_64-mont.o",
                    "crypto/bn/libcrypto-shlib-x86_64-mont5.o",
                    "crypto/buffer/libcrypto-shlib-buf_err.o",
                    "crypto/buffer/libcrypto-shlib-buffer.o",
                    "crypto/camellia/libcrypto-shlib-cmll-x86_64.o",
                    "crypto/camellia/libcrypto-shlib-cmll_cfb.o",
                    "crypto/camellia/libcrypto-shlib-cmll_ctr.o",
                    "crypto/camellia/libcrypto-shlib-cmll_ecb.o",
                    "crypto/camellia/libcrypto-shlib-cmll_misc.o",
                    "crypto/camellia/libcrypto-shlib-cmll_ofb.o",
                    "crypto/cast/libcrypto-shlib-c_cfb64.o",
                    "crypto/cast/libcrypto-shlib-c_ecb.o",
                    "crypto/cast/libcrypto-shlib-c_enc.o",
                    "crypto/cast/libcrypto-shlib-c_ofb64.o",
                    "crypto/cast/libcrypto-shlib-c_skey.o",
                    "crypto/chacha/libcrypto-shlib-chacha-x86_64.o",
                    "crypto/cmac/libcrypto-shlib-cm_ameth.o",
                    "crypto/cmac/libcrypto-shlib-cm_meth.o",
                    "crypto/cmac/libcrypto-shlib-cmac.o",
                    "crypto/cms/libcrypto-shlib-cms_asn1.o",
                    "crypto/cms/libcrypto-shlib-cms_att.o",
                    "crypto/cms/libcrypto-shlib-cms_cd.o",
                    "crypto/cms/libcrypto-shlib-cms_dd.o",
                    "crypto/cms/libcrypto-shlib-cms_enc.o",
                    "crypto/cms/libcrypto-shlib-cms_env.o",
                    "crypto/cms/libcrypto-shlib-cms_err.o",
                    "crypto/cms/libcrypto-shlib-cms_ess.o",
                    "crypto/cms/libcrypto-shlib-cms_io.o",
                    "crypto/cms/libcrypto-shlib-cms_kari.o",
                    "crypto/cms/libcrypto-shlib-cms_lib.o",
                    "crypto/cms/libcrypto-shlib-cms_pwri.o",
                    "crypto/cms/libcrypto-shlib-cms_sd.o",
                    "crypto/cms/libcrypto-shlib-cms_smime.o",
                    "crypto/comp/libcrypto-shlib-c_zlib.o",
                    "crypto/comp/libcrypto-shlib-comp_err.o",
                    "crypto/comp/libcrypto-shlib-comp_lib.o",
                    "crypto/conf/libcrypto-shlib-conf_api.o",
                    "crypto/conf/libcrypto-shlib-conf_def.o",
                    "crypto/conf/libcrypto-shlib-conf_err.o",
                    "crypto/conf/libcrypto-shlib-conf_lib.o",
                    "crypto/conf/libcrypto-shlib-conf_mall.o",
                    "crypto/conf/libcrypto-shlib-conf_mod.o",
                    "crypto/conf/libcrypto-shlib-conf_sap.o",
                    "crypto/conf/libcrypto-shlib-conf_ssl.o",
                    "crypto/crmf/libcrypto-shlib-crmf_asn.o",
                    "crypto/crmf/libcrypto-shlib-crmf_err.o",
                    "crypto/crmf/libcrypto-shlib-crmf_lib.o",
                    "crypto/crmf/libcrypto-shlib-crmf_pbm.o",
                    "crypto/ct/libcrypto-shlib-ct_b64.o",
                    "crypto/ct/libcrypto-shlib-ct_err.o",
                    "crypto/ct/libcrypto-shlib-ct_log.o",
                    "crypto/ct/libcrypto-shlib-ct_oct.o",
                    "crypto/ct/libcrypto-shlib-ct_policy.o",
                    "crypto/ct/libcrypto-shlib-ct_prn.o",
                    "crypto/ct/libcrypto-shlib-ct_sct.o",
                    "crypto/ct/libcrypto-shlib-ct_sct_ctx.o",
                    "crypto/ct/libcrypto-shlib-ct_vfy.o",
                    "crypto/ct/libcrypto-shlib-ct_x509v3.o",
                    "crypto/des/libcrypto-shlib-cbc_cksm.o",
                    "crypto/des/libcrypto-shlib-cbc_enc.o",
                    "crypto/des/libcrypto-shlib-cfb64ede.o",
                    "crypto/des/libcrypto-shlib-cfb64enc.o",
                    "crypto/des/libcrypto-shlib-cfb_enc.o",
                    "crypto/des/libcrypto-shlib-des_enc.o",
                    "crypto/des/libcrypto-shlib-ecb3_enc.o",
                    "crypto/des/libcrypto-shlib-ecb_enc.o",
                    "crypto/des/libcrypto-shlib-fcrypt.o",
                    "crypto/des/libcrypto-shlib-fcrypt_b.o",
                    "crypto/des/libcrypto-shlib-ofb64ede.o",
                    "crypto/des/libcrypto-shlib-ofb64enc.o",
                    "crypto/des/libcrypto-shlib-ofb_enc.o",
                    "crypto/des/libcrypto-shlib-pcbc_enc.o",
                    "crypto/des/libcrypto-shlib-qud_cksm.o",
                    "crypto/des/libcrypto-shlib-rand_key.o",
                    "crypto/des/libcrypto-shlib-set_key.o",
                    "crypto/des/libcrypto-shlib-str2key.o",
                    "crypto/des/libcrypto-shlib-xcbc_enc.o",
                    "crypto/dh/libcrypto-shlib-dh_ameth.o",
                    "crypto/dh/libcrypto-shlib-dh_asn1.o",
                    "crypto/dh/libcrypto-shlib-dh_check.o",
                    "crypto/dh/libcrypto-shlib-dh_depr.o",
                    "crypto/dh/libcrypto-shlib-dh_err.o",
                    "crypto/dh/libcrypto-shlib-dh_gen.o",
                    "crypto/dh/libcrypto-shlib-dh_kdf.o",
                    "crypto/dh/libcrypto-shlib-dh_key.o",
                    "crypto/dh/libcrypto-shlib-dh_lib.o",
                    "crypto/dh/libcrypto-shlib-dh_meth.o",
                    "crypto/dh/libcrypto-shlib-dh_pmeth.o",
                    "crypto/dh/libcrypto-shlib-dh_prn.o",
                    "crypto/dh/libcrypto-shlib-dh_rfc5114.o",
                    "crypto/dh/libcrypto-shlib-dh_rfc7919.o",
                    "crypto/dsa/libcrypto-shlib-dsa_ameth.o",
                    "crypto/dsa/libcrypto-shlib-dsa_asn1.o",
                    "crypto/dsa/libcrypto-shlib-dsa_depr.o",
                    "crypto/dsa/libcrypto-shlib-dsa_err.o",
                    "crypto/dsa/libcrypto-shlib-dsa_gen.o",
                    "crypto/dsa/libcrypto-shlib-dsa_key.o",
                    "crypto/dsa/libcrypto-shlib-dsa_lib.o",
                    "crypto/dsa/libcrypto-shlib-dsa_meth.o",
                    "crypto/dsa/libcrypto-shlib-dsa_ossl.o",
                    "crypto/dsa/libcrypto-shlib-dsa_pmeth.o",
                    "crypto/dsa/libcrypto-shlib-dsa_prn.o",
                    "crypto/dsa/libcrypto-shlib-dsa_sign.o",
                    "crypto/dsa/libcrypto-shlib-dsa_vrf.o",
                    "crypto/dso/libcrypto-shlib-dso_dl.o",
                    "crypto/dso/libcrypto-shlib-dso_dlfcn.o",
                    "crypto/dso/libcrypto-shlib-dso_err.o",
                    "crypto/dso/libcrypto-shlib-dso_lib.o",
                    "crypto/dso/libcrypto-shlib-dso_openssl.o",
                    "crypto/dso/libcrypto-shlib-dso_vms.o",
                    "crypto/dso/libcrypto-shlib-dso_win32.o",
                    "crypto/ec/curve448/arch_32/libcrypto-shlib-f_impl.o",
                    "crypto/ec/curve448/libcrypto-shlib-curve448.o",
                    "crypto/ec/curve448/libcrypto-shlib-curve448_tables.o",
                    "crypto/ec/curve448/libcrypto-shlib-eddsa.o",
                    "crypto/ec/curve448/libcrypto-shlib-f_generic.o",
                    "crypto/ec/curve448/libcrypto-shlib-scalar.o",
                    "crypto/ec/libcrypto-shlib-curve25519.o",
                    "crypto/ec/libcrypto-shlib-ec2_oct.o",
                    "crypto/ec/libcrypto-shlib-ec2_smpl.o",
                    "crypto/ec/libcrypto-shlib-ec_ameth.o",
                    "crypto/ec/libcrypto-shlib-ec_asn1.o",
                    "crypto/ec/libcrypto-shlib-ec_check.o",
                    "crypto/ec/libcrypto-shlib-ec_curve.o",
                    "crypto/ec/libcrypto-shlib-ec_cvt.o",
                    "crypto/ec/libcrypto-shlib-ec_err.o",
                    "crypto/ec/libcrypto-shlib-ec_key.o",
                    "crypto/ec/libcrypto-shlib-ec_kmeth.o",
                    "crypto/ec/libcrypto-shlib-ec_lib.o",
                    "crypto/ec/libcrypto-shlib-ec_mult.o",
                    "crypto/ec/libcrypto-shlib-ec_oct.o",
                    "crypto/ec/libcrypto-shlib-ec_pmeth.o",
                    "crypto/ec/libcrypto-shlib-ec_print.o",
                    "crypto/ec/libcrypto-shlib-ecdh_kdf.o",
                    "crypto/ec/libcrypto-shlib-ecdh_ossl.o",
                    "crypto/ec/libcrypto-shlib-ecdsa_ossl.o",
                    "crypto/ec/libcrypto-shlib-ecdsa_sign.o",
                    "crypto/ec/libcrypto-shlib-ecdsa_vrf.o",
                    "crypto/ec/libcrypto-shlib-eck_prn.o",
                    "crypto/ec/libcrypto-shlib-ecp_mont.o",
                    "crypto/ec/libcrypto-shlib-ecp_nist.o",
                    "crypto/ec/libcrypto-shlib-ecp_nistp224.o",
                    "crypto/ec/libcrypto-shlib-ecp_nistp256.o",
                    "crypto/ec/libcrypto-shlib-ecp_nistp521.o",
                    "crypto/ec/libcrypto-shlib-ecp_nistputil.o",
                    "crypto/ec/libcrypto-shlib-ecp_nistz256-x86_64.o",
                    "crypto/ec/libcrypto-shlib-ecp_nistz256.o",
                    "crypto/ec/libcrypto-shlib-ecp_oct.o",
                    "crypto/ec/libcrypto-shlib-ecp_smpl.o",
                    "crypto/ec/libcrypto-shlib-ecx_meth.o",
                    "crypto/ec/libcrypto-shlib-x25519-x86_64.o",
                    "crypto/engine/libcrypto-shlib-eng_all.o",
                    "crypto/engine/libcrypto-shlib-eng_cnf.o",
                    "crypto/engine/libcrypto-shlib-eng_ctrl.o",
                    "crypto/engine/libcrypto-shlib-eng_dyn.o",
                    "crypto/engine/libcrypto-shlib-eng_err.o",
                    "crypto/engine/libcrypto-shlib-eng_fat.o",
                    "crypto/engine/libcrypto-shlib-eng_init.o",
                    "crypto/engine/libcrypto-shlib-eng_lib.o",
                    "crypto/engine/libcrypto-shlib-eng_list.o",
                    "crypto/engine/libcrypto-shlib-eng_openssl.o",
                    "crypto/engine/libcrypto-shlib-eng_pkey.o",
                    "crypto/engine/libcrypto-shlib-eng_rdrand.o",
                    "crypto/engine/libcrypto-shlib-eng_table.o",
                    "crypto/engine/libcrypto-shlib-tb_asnmth.o",
                    "crypto/engine/libcrypto-shlib-tb_cipher.o",
                    "crypto/engine/libcrypto-shlib-tb_dh.o",
                    "crypto/engine/libcrypto-shlib-tb_digest.o",
                    "crypto/engine/libcrypto-shlib-tb_dsa.o",
                    "crypto/engine/libcrypto-shlib-tb_eckey.o",
                    "crypto/engine/libcrypto-shlib-tb_pkmeth.o",
                    "crypto/engine/libcrypto-shlib-tb_rand.o",
                    "crypto/engine/libcrypto-shlib-tb_rsa.o",
                    "crypto/err/libcrypto-shlib-err.o",
                    "crypto/err/libcrypto-shlib-err_all.o",
                    "crypto/err/libcrypto-shlib-err_prn.o",
                    "crypto/ess/libcrypto-shlib-ess_asn1.o",
                    "crypto/ess/libcrypto-shlib-ess_err.o",
                    "crypto/ess/libcrypto-shlib-ess_lib.o",
                    "crypto/evp/libcrypto-shlib-bio_b64.o",
                    "crypto/evp/libcrypto-shlib-bio_enc.o",
                    "crypto/evp/libcrypto-shlib-bio_md.o",
                    "crypto/evp/libcrypto-shlib-bio_ok.o",
                    "crypto/evp/libcrypto-shlib-c_allc.o",
                    "crypto/evp/libcrypto-shlib-c_alld.o",
                    "crypto/evp/libcrypto-shlib-c_allm.o",
                    "crypto/evp/libcrypto-shlib-cmeth_lib.o",
                    "crypto/evp/libcrypto-shlib-digest.o",
                    "crypto/evp/libcrypto-shlib-e_aes.o",
                    "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha1.o",
                    "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha256.o",
                    "crypto/evp/libcrypto-shlib-e_aria.o",
                    "crypto/evp/libcrypto-shlib-e_bf.o",
                    "crypto/evp/libcrypto-shlib-e_camellia.o",
                    "crypto/evp/libcrypto-shlib-e_cast.o",
                    "crypto/evp/libcrypto-shlib-e_chacha20_poly1305.o",
                    "crypto/evp/libcrypto-shlib-e_des.o",
                    "crypto/evp/libcrypto-shlib-e_des3.o",
                    "crypto/evp/libcrypto-shlib-e_idea.o",
                    "crypto/evp/libcrypto-shlib-e_null.o",
                    "crypto/evp/libcrypto-shlib-e_old.o",
                    "crypto/evp/libcrypto-shlib-e_rc2.o",
                    "crypto/evp/libcrypto-shlib-e_rc4.o",
                    "crypto/evp/libcrypto-shlib-e_rc4_hmac_md5.o",
                    "crypto/evp/libcrypto-shlib-e_rc5.o",
                    "crypto/evp/libcrypto-shlib-e_seed.o",
                    "crypto/evp/libcrypto-shlib-e_sm4.o",
                    "crypto/evp/libcrypto-shlib-e_xcbc_d.o",
                    "crypto/evp/libcrypto-shlib-encode.o",
                    "crypto/evp/libcrypto-shlib-evp_cnf.o",
                    "crypto/evp/libcrypto-shlib-evp_enc.o",
                    "crypto/evp/libcrypto-shlib-evp_err.o",
                    "crypto/evp/libcrypto-shlib-evp_fetch.o",
                    "crypto/evp/libcrypto-shlib-evp_key.o",
                    "crypto/evp/libcrypto-shlib-evp_lib.o",
                    "crypto/evp/libcrypto-shlib-evp_pbe.o",
                    "crypto/evp/libcrypto-shlib-evp_pkey.o",
                    "crypto/evp/libcrypto-shlib-kdf_lib.o",
                    "crypto/evp/libcrypto-shlib-m_md2.o",
                    "crypto/evp/libcrypto-shlib-m_md4.o",
                    "crypto/evp/libcrypto-shlib-m_md5.o",
                    "crypto/evp/libcrypto-shlib-m_md5_sha1.o",
                    "crypto/evp/libcrypto-shlib-m_mdc2.o",
                    "crypto/evp/libcrypto-shlib-m_null.o",
                    "crypto/evp/libcrypto-shlib-m_ripemd.o",
                    "crypto/evp/libcrypto-shlib-m_sha1.o",
                    "crypto/evp/libcrypto-shlib-m_sha3.o",
                    "crypto/evp/libcrypto-shlib-m_sigver.o",
                    "crypto/evp/libcrypto-shlib-m_wp.o",
                    "crypto/evp/libcrypto-shlib-mac_lib.o",
                    "crypto/evp/libcrypto-shlib-names.o",
                    "crypto/evp/libcrypto-shlib-p5_crpt.o",
                    "crypto/evp/libcrypto-shlib-p5_crpt2.o",
                    "crypto/evp/libcrypto-shlib-p_dec.o",
                    "crypto/evp/libcrypto-shlib-p_enc.o",
                    "crypto/evp/libcrypto-shlib-p_lib.o",
                    "crypto/evp/libcrypto-shlib-p_open.o",
                    "crypto/evp/libcrypto-shlib-p_seal.o",
                    "crypto/evp/libcrypto-shlib-p_sign.o",
                    "crypto/evp/libcrypto-shlib-p_verify.o",
                    "crypto/evp/libcrypto-shlib-pbe_scrypt.o",
                    "crypto/evp/libcrypto-shlib-pkey_kdf.o",
                    "crypto/evp/libcrypto-shlib-pkey_mac.o",
                    "crypto/evp/libcrypto-shlib-pmeth_fn.o",
                    "crypto/evp/libcrypto-shlib-pmeth_gn.o",
                    "crypto/evp/libcrypto-shlib-pmeth_lib.o",
                    "crypto/gmac/libcrypto-shlib-gmac.o",
                    "crypto/hmac/libcrypto-shlib-hm_ameth.o",
                    "crypto/hmac/libcrypto-shlib-hm_meth.o",
                    "crypto/hmac/libcrypto-shlib-hmac.o",
                    "crypto/idea/libcrypto-shlib-i_cbc.o",
                    "crypto/idea/libcrypto-shlib-i_cfb64.o",
                    "crypto/idea/libcrypto-shlib-i_ecb.o",
                    "crypto/idea/libcrypto-shlib-i_ofb64.o",
                    "crypto/idea/libcrypto-shlib-i_skey.o",
                    "crypto/kdf/libcrypto-shlib-hkdf.o",
                    "crypto/kdf/libcrypto-shlib-kdf_err.o",
                    "crypto/kdf/libcrypto-shlib-kdf_util.o",
                    "crypto/kdf/libcrypto-shlib-pbkdf2.o",
                    "crypto/kdf/libcrypto-shlib-scrypt.o",
                    "crypto/kdf/libcrypto-shlib-sshkdf.o",
                    "crypto/kdf/libcrypto-shlib-sskdf.o",
                    "crypto/kdf/libcrypto-shlib-tls1_prf.o",
                    "crypto/kmac/libcrypto-shlib-kmac.o",
                    "crypto/lhash/libcrypto-shlib-lh_stats.o",
                    "crypto/lhash/libcrypto-shlib-lhash.o",
                    "crypto/libcrypto-shlib-context.o",
                    "crypto/libcrypto-shlib-core_fetch.o",
                    "crypto/libcrypto-shlib-cpt_err.o",
                    "crypto/libcrypto-shlib-cryptlib.o",
                    "crypto/libcrypto-shlib-ctype.o",
                    "crypto/libcrypto-shlib-cversion.o",
                    "crypto/libcrypto-shlib-ebcdic.o",
                    "crypto/libcrypto-shlib-ex_data.o",
                    "crypto/libcrypto-shlib-getenv.o",
                    "crypto/libcrypto-shlib-init.o",
                    "crypto/libcrypto-shlib-mem.o",
                    "crypto/libcrypto-shlib-mem_dbg.o",
                    "crypto/libcrypto-shlib-mem_sec.o",
                    "crypto/libcrypto-shlib-o_dir.o",
                    "crypto/libcrypto-shlib-o_fips.o",
                    "crypto/libcrypto-shlib-o_fopen.o",
                    "crypto/libcrypto-shlib-o_init.o",
                    "crypto/libcrypto-shlib-o_str.o",
                    "crypto/libcrypto-shlib-o_time.o",
                    "crypto/libcrypto-shlib-params.o",
                    "crypto/libcrypto-shlib-provider.o",
                    "crypto/libcrypto-shlib-provider_conf.o",
                    "crypto/libcrypto-shlib-provider_core.o",
                    "crypto/libcrypto-shlib-provider_predefined.o",
                    "crypto/libcrypto-shlib-sparse_array.o",
                    "crypto/libcrypto-shlib-threads_none.o",
                    "crypto/libcrypto-shlib-threads_pthread.o",
                    "crypto/libcrypto-shlib-threads_win.o",
                    "crypto/libcrypto-shlib-trace.o",
                    "crypto/libcrypto-shlib-uid.o",
                    "crypto/libcrypto-shlib-x86_64cpuid.o",
                    "crypto/md4/libcrypto-shlib-md4_dgst.o",
                    "crypto/md4/libcrypto-shlib-md4_one.o",
                    "crypto/md5/libcrypto-shlib-md5-x86_64.o",
                    "crypto/md5/libcrypto-shlib-md5_dgst.o",
                    "crypto/md5/libcrypto-shlib-md5_one.o",
                    "crypto/mdc2/libcrypto-shlib-mdc2_one.o",
                    "crypto/mdc2/libcrypto-shlib-mdc2dgst.o",
                    "crypto/modes/libcrypto-shlib-aesni-gcm-x86_64.o",
                    "crypto/modes/libcrypto-shlib-cbc128.o",
                    "crypto/modes/libcrypto-shlib-ccm128.o",
                    "crypto/modes/libcrypto-shlib-cfb128.o",
                    "crypto/modes/libcrypto-shlib-ctr128.o",
                    "crypto/modes/libcrypto-shlib-cts128.o",
                    "crypto/modes/libcrypto-shlib-gcm128.o",
                    "crypto/modes/libcrypto-shlib-ghash-x86_64.o",
                    "crypto/modes/libcrypto-shlib-ocb128.o",
                    "crypto/modes/libcrypto-shlib-ofb128.o",
                    "crypto/modes/libcrypto-shlib-siv128.o",
                    "crypto/modes/libcrypto-shlib-wrap128.o",
                    "crypto/modes/libcrypto-shlib-xts128.o",
                    "crypto/objects/libcrypto-shlib-o_names.o",
                    "crypto/objects/libcrypto-shlib-obj_dat.o",
                    "crypto/objects/libcrypto-shlib-obj_err.o",
                    "crypto/objects/libcrypto-shlib-obj_lib.o",
                    "crypto/objects/libcrypto-shlib-obj_xref.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_asn.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_cl.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_err.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_ext.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_ht.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_lib.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_prn.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_srv.o",
                    "crypto/ocsp/libcrypto-shlib-ocsp_vfy.o",
                    "crypto/ocsp/libcrypto-shlib-v3_ocsp.o",
                    "crypto/pem/libcrypto-shlib-pem_all.o",
                    "crypto/pem/libcrypto-shlib-pem_err.o",
                    "crypto/pem/libcrypto-shlib-pem_info.o",
                    "crypto/pem/libcrypto-shlib-pem_lib.o",
                    "crypto/pem/libcrypto-shlib-pem_oth.o",
                    "crypto/pem/libcrypto-shlib-pem_pk8.o",
                    "crypto/pem/libcrypto-shlib-pem_pkey.o",
                    "crypto/pem/libcrypto-shlib-pem_sign.o",
                    "crypto/pem/libcrypto-shlib-pem_x509.o",
                    "crypto/pem/libcrypto-shlib-pem_xaux.o",
                    "crypto/pem/libcrypto-shlib-pvkfmt.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_add.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_asn.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_attr.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_crpt.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_crt.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_decr.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_init.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_key.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_kiss.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_mutl.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_npas.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_p8d.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_p8e.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_sbag.o",
                    "crypto/pkcs12/libcrypto-shlib-p12_utl.o",
                    "crypto/pkcs12/libcrypto-shlib-pk12err.o",
                    "crypto/pkcs7/libcrypto-shlib-bio_pk7.o",
                    "crypto/pkcs7/libcrypto-shlib-pk7_asn1.o",
                    "crypto/pkcs7/libcrypto-shlib-pk7_attr.o",
                    "crypto/pkcs7/libcrypto-shlib-pk7_doit.o",
                    "crypto/pkcs7/libcrypto-shlib-pk7_lib.o",
                    "crypto/pkcs7/libcrypto-shlib-pk7_mime.o",
                    "crypto/pkcs7/libcrypto-shlib-pk7_smime.o",
                    "crypto/pkcs7/libcrypto-shlib-pkcs7err.o",
                    "crypto/poly1305/libcrypto-shlib-poly1305-x86_64.o",
                    "crypto/poly1305/libcrypto-shlib-poly1305.o",
                    "crypto/poly1305/libcrypto-shlib-poly1305_ameth.o",
                    "crypto/poly1305/libcrypto-shlib-poly1305_meth.o",
                    "crypto/property/libcrypto-shlib-defn_cache.o",
                    "crypto/property/libcrypto-shlib-property.o",
                    "crypto/property/libcrypto-shlib-property_err.o",
                    "crypto/property/libcrypto-shlib-property_parse.o",
                    "crypto/property/libcrypto-shlib-property_string.o",
                    "crypto/rand/libcrypto-shlib-drbg_ctr.o",
                    "crypto/rand/libcrypto-shlib-drbg_hash.o",
                    "crypto/rand/libcrypto-shlib-drbg_hmac.o",
                    "crypto/rand/libcrypto-shlib-drbg_lib.o",
                    "crypto/rand/libcrypto-shlib-rand_crng_test.o",
                    "crypto/rand/libcrypto-shlib-rand_egd.o",
                    "crypto/rand/libcrypto-shlib-rand_err.o",
                    "crypto/rand/libcrypto-shlib-rand_lib.o",
                    "crypto/rand/libcrypto-shlib-rand_unix.o",
                    "crypto/rand/libcrypto-shlib-rand_vms.o",
                    "crypto/rand/libcrypto-shlib-rand_win.o",
                    "crypto/rand/libcrypto-shlib-randfile.o",
                    "crypto/rc2/libcrypto-shlib-rc2_cbc.o",
                    "crypto/rc2/libcrypto-shlib-rc2_ecb.o",
                    "crypto/rc2/libcrypto-shlib-rc2_skey.o",
                    "crypto/rc2/libcrypto-shlib-rc2cfb64.o",
                    "crypto/rc2/libcrypto-shlib-rc2ofb64.o",
                    "crypto/rc4/libcrypto-shlib-rc4-md5-x86_64.o",
                    "crypto/rc4/libcrypto-shlib-rc4-x86_64.o",
                    "crypto/ripemd/libcrypto-shlib-rmd_dgst.o",
                    "crypto/ripemd/libcrypto-shlib-rmd_one.o",
                    "crypto/rsa/libcrypto-shlib-rsa_ameth.o",
                    "crypto/rsa/libcrypto-shlib-rsa_asn1.o",
                    "crypto/rsa/libcrypto-shlib-rsa_chk.o",
                    "crypto/rsa/libcrypto-shlib-rsa_crpt.o",
                    "crypto/rsa/libcrypto-shlib-rsa_depr.o",
                    "crypto/rsa/libcrypto-shlib-rsa_err.o",
                    "crypto/rsa/libcrypto-shlib-rsa_gen.o",
                    "crypto/rsa/libcrypto-shlib-rsa_lib.o",
                    "crypto/rsa/libcrypto-shlib-rsa_meth.o",
                    "crypto/rsa/libcrypto-shlib-rsa_mp.o",
                    "crypto/rsa/libcrypto-shlib-rsa_none.o",
                    "crypto/rsa/libcrypto-shlib-rsa_oaep.o",
                    "crypto/rsa/libcrypto-shlib-rsa_ossl.o",
                    "crypto/rsa/libcrypto-shlib-rsa_pk1.o",
                    "crypto/rsa/libcrypto-shlib-rsa_pmeth.o",
                    "crypto/rsa/libcrypto-shlib-rsa_prn.o",
                    "crypto/rsa/libcrypto-shlib-rsa_pss.o",
                    "crypto/rsa/libcrypto-shlib-rsa_saos.o",
                    "crypto/rsa/libcrypto-shlib-rsa_sign.o",
                    "crypto/rsa/libcrypto-shlib-rsa_sp800_56b_check.o",
                    "crypto/rsa/libcrypto-shlib-rsa_sp800_56b_gen.o",
                    "crypto/rsa/libcrypto-shlib-rsa_ssl.o",
                    "crypto/rsa/libcrypto-shlib-rsa_x931.o",
                    "crypto/rsa/libcrypto-shlib-rsa_x931g.o",
                    "crypto/seed/libcrypto-shlib-seed.o",
                    "crypto/seed/libcrypto-shlib-seed_cbc.o",
                    "crypto/seed/libcrypto-shlib-seed_cfb.o",
                    "crypto/seed/libcrypto-shlib-seed_ecb.o",
                    "crypto/seed/libcrypto-shlib-seed_ofb.o",
                    "crypto/sha/libcrypto-shlib-keccak1600-x86_64.o",
                    "crypto/sha/libcrypto-shlib-sha1-mb-x86_64.o",
                    "crypto/sha/libcrypto-shlib-sha1-x86_64.o",
                    "crypto/sha/libcrypto-shlib-sha1_one.o",
                    "crypto/sha/libcrypto-shlib-sha1dgst.o",
                    "crypto/sha/libcrypto-shlib-sha256-mb-x86_64.o",
                    "crypto/sha/libcrypto-shlib-sha256-x86_64.o",
                    "crypto/sha/libcrypto-shlib-sha256.o",
                    "crypto/sha/libcrypto-shlib-sha512-x86_64.o",
                    "crypto/sha/libcrypto-shlib-sha512.o",
                    "crypto/siphash/libcrypto-shlib-siphash.o",
                    "crypto/siphash/libcrypto-shlib-siphash_ameth.o",
                    "crypto/siphash/libcrypto-shlib-siphash_meth.o",
                    "crypto/sm2/libcrypto-shlib-sm2_crypt.o",
                    "crypto/sm2/libcrypto-shlib-sm2_err.o",
                    "crypto/sm2/libcrypto-shlib-sm2_pmeth.o",
                    "crypto/sm2/libcrypto-shlib-sm2_sign.o",
                    "crypto/sm3/libcrypto-shlib-m_sm3.o",
                    "crypto/sm3/libcrypto-shlib-sm3.o",
                    "crypto/sm4/libcrypto-shlib-sm4.o",
                    "crypto/srp/libcrypto-shlib-srp_lib.o",
                    "crypto/srp/libcrypto-shlib-srp_vfy.o",
                    "crypto/stack/libcrypto-shlib-stack.o",
                    "crypto/store/libcrypto-shlib-loader_file.o",
                    "crypto/store/libcrypto-shlib-store_err.o",
                    "crypto/store/libcrypto-shlib-store_init.o",
                    "crypto/store/libcrypto-shlib-store_lib.o",
                    "crypto/store/libcrypto-shlib-store_register.o",
                    "crypto/store/libcrypto-shlib-store_strings.o",
                    "crypto/ts/libcrypto-shlib-ts_asn1.o",
                    "crypto/ts/libcrypto-shlib-ts_conf.o",
                    "crypto/ts/libcrypto-shlib-ts_err.o",
                    "crypto/ts/libcrypto-shlib-ts_lib.o",
                    "crypto/ts/libcrypto-shlib-ts_req_print.o",
                    "crypto/ts/libcrypto-shlib-ts_req_utils.o",
                    "crypto/ts/libcrypto-shlib-ts_rsp_print.o",
                    "crypto/ts/libcrypto-shlib-ts_rsp_sign.o",
                    "crypto/ts/libcrypto-shlib-ts_rsp_utils.o",
                    "crypto/ts/libcrypto-shlib-ts_rsp_verify.o",
                    "crypto/ts/libcrypto-shlib-ts_verify_ctx.o",
                    "crypto/txt_db/libcrypto-shlib-txt_db.o",
                    "crypto/ui/libcrypto-shlib-ui_err.o",
                    "crypto/ui/libcrypto-shlib-ui_lib.o",
                    "crypto/ui/libcrypto-shlib-ui_null.o",
                    "crypto/ui/libcrypto-shlib-ui_openssl.o",
                    "crypto/ui/libcrypto-shlib-ui_util.o",
                    "crypto/whrlpool/libcrypto-shlib-wp-x86_64.o",
                    "crypto/whrlpool/libcrypto-shlib-wp_dgst.o",
                    "crypto/x509/libcrypto-shlib-by_dir.o",
                    "crypto/x509/libcrypto-shlib-by_file.o",
                    "crypto/x509/libcrypto-shlib-t_crl.o",
                    "crypto/x509/libcrypto-shlib-t_req.o",
                    "crypto/x509/libcrypto-shlib-t_x509.o",
                    "crypto/x509/libcrypto-shlib-x509_att.o",
                    "crypto/x509/libcrypto-shlib-x509_cmp.o",
                    "crypto/x509/libcrypto-shlib-x509_d2.o",
                    "crypto/x509/libcrypto-shlib-x509_def.o",
                    "crypto/x509/libcrypto-shlib-x509_err.o",
                    "crypto/x509/libcrypto-shlib-x509_ext.o",
                    "crypto/x509/libcrypto-shlib-x509_lu.o",
                    "crypto/x509/libcrypto-shlib-x509_meth.o",
                    "crypto/x509/libcrypto-shlib-x509_obj.o",
                    "crypto/x509/libcrypto-shlib-x509_r2x.o",
                    "crypto/x509/libcrypto-shlib-x509_req.o",
                    "crypto/x509/libcrypto-shlib-x509_set.o",
                    "crypto/x509/libcrypto-shlib-x509_trs.o",
                    "crypto/x509/libcrypto-shlib-x509_txt.o",
                    "crypto/x509/libcrypto-shlib-x509_v3.o",
                    "crypto/x509/libcrypto-shlib-x509_vfy.o",
                    "crypto/x509/libcrypto-shlib-x509_vpm.o",
                    "crypto/x509/libcrypto-shlib-x509cset.o",
                    "crypto/x509/libcrypto-shlib-x509name.o",
                    "crypto/x509/libcrypto-shlib-x509rset.o",
                    "crypto/x509/libcrypto-shlib-x509spki.o",
                    "crypto/x509/libcrypto-shlib-x509type.o",
                    "crypto/x509/libcrypto-shlib-x_all.o",
                    "crypto/x509/libcrypto-shlib-x_attrib.o",
                    "crypto/x509/libcrypto-shlib-x_crl.o",
                    "crypto/x509/libcrypto-shlib-x_exten.o",
                    "crypto/x509/libcrypto-shlib-x_name.o",
                    "crypto/x509/libcrypto-shlib-x_pubkey.o",
                    "crypto/x509/libcrypto-shlib-x_req.o",
                    "crypto/x509/libcrypto-shlib-x_x509.o",
                    "crypto/x509/libcrypto-shlib-x_x509a.o",
                    "crypto/x509v3/libcrypto-shlib-pcy_cache.o",
                    "crypto/x509v3/libcrypto-shlib-pcy_data.o",
                    "crypto/x509v3/libcrypto-shlib-pcy_lib.o",
                    "crypto/x509v3/libcrypto-shlib-pcy_map.o",
                    "crypto/x509v3/libcrypto-shlib-pcy_node.o",
                    "crypto/x509v3/libcrypto-shlib-pcy_tree.o",
                    "crypto/x509v3/libcrypto-shlib-v3_addr.o",
                    "crypto/x509v3/libcrypto-shlib-v3_admis.o",
                    "crypto/x509v3/libcrypto-shlib-v3_akey.o",
                    "crypto/x509v3/libcrypto-shlib-v3_akeya.o",
                    "crypto/x509v3/libcrypto-shlib-v3_alt.o",
                    "crypto/x509v3/libcrypto-shlib-v3_asid.o",
                    "crypto/x509v3/libcrypto-shlib-v3_bcons.o",
                    "crypto/x509v3/libcrypto-shlib-v3_bitst.o",
                    "crypto/x509v3/libcrypto-shlib-v3_conf.o",
                    "crypto/x509v3/libcrypto-shlib-v3_cpols.o",
                    "crypto/x509v3/libcrypto-shlib-v3_crld.o",
                    "crypto/x509v3/libcrypto-shlib-v3_enum.o",
                    "crypto/x509v3/libcrypto-shlib-v3_extku.o",
                    "crypto/x509v3/libcrypto-shlib-v3_genn.o",
                    "crypto/x509v3/libcrypto-shlib-v3_ia5.o",
                    "crypto/x509v3/libcrypto-shlib-v3_info.o",
                    "crypto/x509v3/libcrypto-shlib-v3_int.o",
                    "crypto/x509v3/libcrypto-shlib-v3_lib.o",
                    "crypto/x509v3/libcrypto-shlib-v3_ncons.o",
                    "crypto/x509v3/libcrypto-shlib-v3_pci.o",
                    "crypto/x509v3/libcrypto-shlib-v3_pcia.o",
                    "crypto/x509v3/libcrypto-shlib-v3_pcons.o",
                    "crypto/x509v3/libcrypto-shlib-v3_pku.o",
                    "crypto/x509v3/libcrypto-shlib-v3_pmaps.o",
                    "crypto/x509v3/libcrypto-shlib-v3_prn.o",
                    "crypto/x509v3/libcrypto-shlib-v3_purp.o",
                    "crypto/x509v3/libcrypto-shlib-v3_skey.o",
                    "crypto/x509v3/libcrypto-shlib-v3_sxnet.o",
                    "crypto/x509v3/libcrypto-shlib-v3_tlsf.o",
                    "crypto/x509v3/libcrypto-shlib-v3_utl.o",
                    "crypto/x509v3/libcrypto-shlib-v3err.o",
                    "libcrypto.ld",
                    "providers/common/digests/libcrypto-shlib-sha2.o",
                    "providers/default/libcrypto-shlib-defltprov.o",
                ],
            "libssl" =>
                [
                    "libssl.ld",
                    "ssl/libssl-shlib-bio_ssl.o",
                    "ssl/libssl-shlib-d1_lib.o",
                    "ssl/libssl-shlib-d1_msg.o",
                    "ssl/libssl-shlib-d1_srtp.o",
                    "ssl/libssl-shlib-methods.o",
                    "ssl/libssl-shlib-packet.o",
                    "ssl/libssl-shlib-pqueue.o",
                    "ssl/libssl-shlib-s3_cbc.o",
                    "ssl/libssl-shlib-s3_enc.o",
                    "ssl/libssl-shlib-s3_lib.o",
                    "ssl/libssl-shlib-s3_msg.o",
                    "ssl/libssl-shlib-ssl_asn1.o",
                    "ssl/libssl-shlib-ssl_cert.o",
                    "ssl/libssl-shlib-ssl_ciph.o",
                    "ssl/libssl-shlib-ssl_conf.o",
                    "ssl/libssl-shlib-ssl_err.o",
                    "ssl/libssl-shlib-ssl_init.o",
                    "ssl/libssl-shlib-ssl_lib.o",
                    "ssl/libssl-shlib-ssl_mcnf.o",
                    "ssl/libssl-shlib-ssl_rsa.o",
                    "ssl/libssl-shlib-ssl_sess.o",
                    "ssl/libssl-shlib-ssl_stat.o",
                    "ssl/libssl-shlib-ssl_txt.o",
                    "ssl/libssl-shlib-ssl_utst.o",
                    "ssl/libssl-shlib-t1_enc.o",
                    "ssl/libssl-shlib-t1_lib.o",
                    "ssl/libssl-shlib-t1_trce.o",
                    "ssl/libssl-shlib-tls13_enc.o",
                    "ssl/libssl-shlib-tls_srp.o",
                    "ssl/record/libssl-shlib-dtls1_bitmap.o",
                    "ssl/record/libssl-shlib-rec_layer_d1.o",
                    "ssl/record/libssl-shlib-rec_layer_s3.o",
                    "ssl/record/libssl-shlib-ssl3_buffer.o",
                    "ssl/record/libssl-shlib-ssl3_record.o",
                    "ssl/record/libssl-shlib-ssl3_record_tls13.o",
                    "ssl/statem/libssl-shlib-extensions.o",
                    "ssl/statem/libssl-shlib-extensions_clnt.o",
                    "ssl/statem/libssl-shlib-extensions_cust.o",
                    "ssl/statem/libssl-shlib-extensions_srvr.o",
                    "ssl/statem/libssl-shlib-statem.o",
                    "ssl/statem/libssl-shlib-statem_clnt.o",
                    "ssl/statem/libssl-shlib-statem_dtls.o",
                    "ssl/statem/libssl-shlib-statem_lib.o",
                    "ssl/statem/libssl-shlib-statem_srvr.o",
                ],
        },
    "sources" =>
        {
            "apps/CA.pl" =>
                [
                    "apps/CA.pl.in",
                ],
            "apps/libapps-lib-app_rand.o" =>
                [
                    "apps/app_rand.c",
                ],
            "apps/libapps-lib-apps.o" =>
                [
                    "apps/apps.c",
                ],
            "apps/libapps-lib-apps_ui.o" =>
                [
                    "apps/apps_ui.c",
                ],
            "apps/libapps-lib-bf_prefix.o" =>
                [
                    "apps/bf_prefix.c",
                ],
            "apps/libapps-lib-fmt.o" =>
                [
                    "apps/fmt.c",
                ],
            "apps/libapps-lib-opt.o" =>
                [
                    "apps/opt.c",
                ],
            "apps/libapps-lib-s_cb.o" =>
                [
                    "apps/s_cb.c",
                ],
            "apps/libapps-lib-s_socket.o" =>
                [
                    "apps/s_socket.c",
                ],
            "apps/libapps.a" =>
                [
                    "apps/libapps-lib-app_rand.o",
                    "apps/libapps-lib-apps.o",
                    "apps/libapps-lib-apps_ui.o",
                    "apps/libapps-lib-bf_prefix.o",
                    "apps/libapps-lib-fmt.o",
                    "apps/libapps-lib-opt.o",
                    "apps/libapps-lib-s_cb.o",
                    "apps/libapps-lib-s_socket.o",
                ],
            "apps/libtestutil-lib-opt.o" =>
                [
                    "apps/opt.c",
                ],
            "apps/openssl" =>
                [
                    "apps/openssl-bin-asn1pars.o",
                    "apps/openssl-bin-ca.o",
                    "apps/openssl-bin-ciphers.o",
                    "apps/openssl-bin-cms.o",
                    "apps/openssl-bin-crl.o",
                    "apps/openssl-bin-crl2p7.o",
                    "apps/openssl-bin-dgst.o",
                    "apps/openssl-bin-dhparam.o",
                    "apps/openssl-bin-dsa.o",
                    "apps/openssl-bin-dsaparam.o",
                    "apps/openssl-bin-ec.o",
                    "apps/openssl-bin-ecparam.o",
                    "apps/openssl-bin-enc.o",
                    "apps/openssl-bin-engine.o",
                    "apps/openssl-bin-errstr.o",
                    "apps/openssl-bin-gendsa.o",
                    "apps/openssl-bin-genpkey.o",
                    "apps/openssl-bin-genrsa.o",
                    "apps/openssl-bin-mac.o",
                    "apps/openssl-bin-nseq.o",
                    "apps/openssl-bin-ocsp.o",
                    "apps/openssl-bin-openssl.o",
                    "apps/openssl-bin-passwd.o",
                    "apps/openssl-bin-pkcs12.o",
                    "apps/openssl-bin-pkcs7.o",
                    "apps/openssl-bin-pkcs8.o",
                    "apps/openssl-bin-pkey.o",
                    "apps/openssl-bin-pkeyparam.o",
                    "apps/openssl-bin-pkeyutl.o",
                    "apps/openssl-bin-prime.o",
                    "apps/openssl-bin-rand.o",
                    "apps/openssl-bin-rehash.o",
                    "apps/openssl-bin-req.o",
                    "apps/openssl-bin-rsa.o",
                    "apps/openssl-bin-rsautl.o",
                    "apps/openssl-bin-s_client.o",
                    "apps/openssl-bin-s_server.o",
                    "apps/openssl-bin-s_time.o",
                    "apps/openssl-bin-sess_id.o",
                    "apps/openssl-bin-smime.o",
                    "apps/openssl-bin-speed.o",
                    "apps/openssl-bin-spkac.o",
                    "apps/openssl-bin-srp.o",
                    "apps/openssl-bin-storeutl.o",
                    "apps/openssl-bin-ts.o",
                    "apps/openssl-bin-verify.o",
                    "apps/openssl-bin-version.o",
                    "apps/openssl-bin-x509.o",
                ],
            "apps/openssl-bin-asn1pars.o" =>
                [
                    "apps/asn1pars.c",
                ],
            "apps/openssl-bin-ca.o" =>
                [
                    "apps/ca.c",
                ],
            "apps/openssl-bin-ciphers.o" =>
                [
                    "apps/ciphers.c",
                ],
            "apps/openssl-bin-cms.o" =>
                [
                    "apps/cms.c",
                ],
            "apps/openssl-bin-crl.o" =>
                [
                    "apps/crl.c",
                ],
            "apps/openssl-bin-crl2p7.o" =>
                [
                    "apps/crl2p7.c",
                ],
            "apps/openssl-bin-dgst.o" =>
                [
                    "apps/dgst.c",
                ],
            "apps/openssl-bin-dhparam.o" =>
                [
                    "apps/dhparam.c",
                ],
            "apps/openssl-bin-dsa.o" =>
                [
                    "apps/dsa.c",
                ],
            "apps/openssl-bin-dsaparam.o" =>
                [
                    "apps/dsaparam.c",
                ],
            "apps/openssl-bin-ec.o" =>
                [
                    "apps/ec.c",
                ],
            "apps/openssl-bin-ecparam.o" =>
                [
                    "apps/ecparam.c",
                ],
            "apps/openssl-bin-enc.o" =>
                [
                    "apps/enc.c",
                ],
            "apps/openssl-bin-engine.o" =>
                [
                    "apps/engine.c",
                ],
            "apps/openssl-bin-errstr.o" =>
                [
                    "apps/errstr.c",
                ],
            "apps/openssl-bin-gendsa.o" =>
                [
                    "apps/gendsa.c",
                ],
            "apps/openssl-bin-genpkey.o" =>
                [
                    "apps/genpkey.c",
                ],
            "apps/openssl-bin-genrsa.o" =>
                [
                    "apps/genrsa.c",
                ],
            "apps/openssl-bin-mac.o" =>
                [
                    "apps/mac.c",
                ],
            "apps/openssl-bin-nseq.o" =>
                [
                    "apps/nseq.c",
                ],
            "apps/openssl-bin-ocsp.o" =>
                [
                    "apps/ocsp.c",
                ],
            "apps/openssl-bin-openssl.o" =>
                [
                    "apps/openssl.c",
                ],
            "apps/openssl-bin-passwd.o" =>
                [
                    "apps/passwd.c",
                ],
            "apps/openssl-bin-pkcs12.o" =>
                [
                    "apps/pkcs12.c",
                ],
            "apps/openssl-bin-pkcs7.o" =>
                [
                    "apps/pkcs7.c",
                ],
            "apps/openssl-bin-pkcs8.o" =>
                [
                    "apps/pkcs8.c",
                ],
            "apps/openssl-bin-pkey.o" =>
                [
                    "apps/pkey.c",
                ],
            "apps/openssl-bin-pkeyparam.o" =>
                [
                    "apps/pkeyparam.c",
                ],
            "apps/openssl-bin-pkeyutl.o" =>
                [
                    "apps/pkeyutl.c",
                ],
            "apps/openssl-bin-prime.o" =>
                [
                    "apps/prime.c",
                ],
            "apps/openssl-bin-rand.o" =>
                [
                    "apps/rand.c",
                ],
            "apps/openssl-bin-rehash.o" =>
                [
                    "apps/rehash.c",
                ],
            "apps/openssl-bin-req.o" =>
                [
                    "apps/req.c",
                ],
            "apps/openssl-bin-rsa.o" =>
                [
                    "apps/rsa.c",
                ],
            "apps/openssl-bin-rsautl.o" =>
                [
                    "apps/rsautl.c",
                ],
            "apps/openssl-bin-s_client.o" =>
                [
                    "apps/s_client.c",
                ],
            "apps/openssl-bin-s_server.o" =>
                [
                    "apps/s_server.c",
                ],
            "apps/openssl-bin-s_time.o" =>
                [
                    "apps/s_time.c",
                ],
            "apps/openssl-bin-sess_id.o" =>
                [
                    "apps/sess_id.c",
                ],
            "apps/openssl-bin-smime.o" =>
                [
                    "apps/smime.c",
                ],
            "apps/openssl-bin-speed.o" =>
                [
                    "apps/speed.c",
                ],
            "apps/openssl-bin-spkac.o" =>
                [
                    "apps/spkac.c",
                ],
            "apps/openssl-bin-srp.o" =>
                [
                    "apps/srp.c",
                ],
            "apps/openssl-bin-storeutl.o" =>
                [
                    "apps/storeutl.c",
                ],
            "apps/openssl-bin-ts.o" =>
                [
                    "apps/ts.c",
                ],
            "apps/openssl-bin-verify.o" =>
                [
                    "apps/verify.c",
                ],
            "apps/openssl-bin-version.o" =>
                [
                    "apps/version.c",
                ],
            "apps/openssl-bin-x509.o" =>
                [
                    "apps/x509.c",
                ],
            "apps/tsget.pl" =>
                [
                    "apps/tsget.in",
                ],
            "apps/uitest-bin-apps_ui.o" =>
                [
                    "apps/apps_ui.c",
                ],
            "crypto/aes/libcrypto-lib-aes-x86_64.o" =>
                [
                    "crypto/aes/aes-x86_64.s",
                ],
            "crypto/aes/libcrypto-lib-aes_cfb.o" =>
                [
                    "crypto/aes/aes_cfb.c",
                ],
            "crypto/aes/libcrypto-lib-aes_ecb.o" =>
                [
                    "crypto/aes/aes_ecb.c",
                ],
            "crypto/aes/libcrypto-lib-aes_ige.o" =>
                [
                    "crypto/aes/aes_ige.c",
                ],
            "crypto/aes/libcrypto-lib-aes_misc.o" =>
                [
                    "crypto/aes/aes_misc.c",
                ],
            "crypto/aes/libcrypto-lib-aes_ofb.o" =>
                [
                    "crypto/aes/aes_ofb.c",
                ],
            "crypto/aes/libcrypto-lib-aes_wrap.o" =>
                [
                    "crypto/aes/aes_wrap.c",
                ],
            "crypto/aes/libcrypto-lib-aesni-mb-x86_64.o" =>
                [
                    "crypto/aes/aesni-mb-x86_64.s",
                ],
            "crypto/aes/libcrypto-lib-aesni-sha1-x86_64.o" =>
                [
                    "crypto/aes/aesni-sha1-x86_64.s",
                ],
            "crypto/aes/libcrypto-lib-aesni-sha256-x86_64.o" =>
                [
                    "crypto/aes/aesni-sha256-x86_64.s",
                ],
            "crypto/aes/libcrypto-lib-aesni-x86_64.o" =>
                [
                    "crypto/aes/aesni-x86_64.s",
                ],
            "crypto/aes/libcrypto-lib-bsaes-x86_64.o" =>
                [
                    "crypto/aes/bsaes-x86_64.s",
                ],
            "crypto/aes/libcrypto-lib-vpaes-x86_64.o" =>
                [
                    "crypto/aes/vpaes-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-aes-x86_64.o" =>
                [
                    "crypto/aes/aes-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-aes_cfb.o" =>
                [
                    "crypto/aes/aes_cfb.c",
                ],
            "crypto/aes/libcrypto-shlib-aes_ecb.o" =>
                [
                    "crypto/aes/aes_ecb.c",
                ],
            "crypto/aes/libcrypto-shlib-aes_ige.o" =>
                [
                    "crypto/aes/aes_ige.c",
                ],
            "crypto/aes/libcrypto-shlib-aes_misc.o" =>
                [
                    "crypto/aes/aes_misc.c",
                ],
            "crypto/aes/libcrypto-shlib-aes_ofb.o" =>
                [
                    "crypto/aes/aes_ofb.c",
                ],
            "crypto/aes/libcrypto-shlib-aes_wrap.o" =>
                [
                    "crypto/aes/aes_wrap.c",
                ],
            "crypto/aes/libcrypto-shlib-aesni-mb-x86_64.o" =>
                [
                    "crypto/aes/aesni-mb-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-aesni-sha1-x86_64.o" =>
                [
                    "crypto/aes/aesni-sha1-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-aesni-sha256-x86_64.o" =>
                [
                    "crypto/aes/aesni-sha256-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-aesni-x86_64.o" =>
                [
                    "crypto/aes/aesni-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-bsaes-x86_64.o" =>
                [
                    "crypto/aes/bsaes-x86_64.s",
                ],
            "crypto/aes/libcrypto-shlib-vpaes-x86_64.o" =>
                [
                    "crypto/aes/vpaes-x86_64.s",
                ],
            "crypto/aria/libcrypto-lib-aria.o" =>
                [
                    "crypto/aria/aria.c",
                ],
            "crypto/aria/libcrypto-shlib-aria.o" =>
                [
                    "crypto/aria/aria.c",
                ],
            "crypto/asn1/libcrypto-lib-a_bitstr.o" =>
                [
                    "crypto/asn1/a_bitstr.c",
                ],
            "crypto/asn1/libcrypto-lib-a_d2i_fp.o" =>
                [
                    "crypto/asn1/a_d2i_fp.c",
                ],
            "crypto/asn1/libcrypto-lib-a_digest.o" =>
                [
                    "crypto/asn1/a_digest.c",
                ],
            "crypto/asn1/libcrypto-lib-a_dup.o" =>
                [
                    "crypto/asn1/a_dup.c",
                ],
            "crypto/asn1/libcrypto-lib-a_gentm.o" =>
                [
                    "crypto/asn1/a_gentm.c",
                ],
            "crypto/asn1/libcrypto-lib-a_i2d_fp.o" =>
                [
                    "crypto/asn1/a_i2d_fp.c",
                ],
            "crypto/asn1/libcrypto-lib-a_int.o" =>
                [
                    "crypto/asn1/a_int.c",
                ],
            "crypto/asn1/libcrypto-lib-a_mbstr.o" =>
                [
                    "crypto/asn1/a_mbstr.c",
                ],
            "crypto/asn1/libcrypto-lib-a_object.o" =>
                [
                    "crypto/asn1/a_object.c",
                ],
            "crypto/asn1/libcrypto-lib-a_octet.o" =>
                [
                    "crypto/asn1/a_octet.c",
                ],
            "crypto/asn1/libcrypto-lib-a_print.o" =>
                [
                    "crypto/asn1/a_print.c",
                ],
            "crypto/asn1/libcrypto-lib-a_sign.o" =>
                [
                    "crypto/asn1/a_sign.c",
                ],
            "crypto/asn1/libcrypto-lib-a_strex.o" =>
                [
                    "crypto/asn1/a_strex.c",
                ],
            "crypto/asn1/libcrypto-lib-a_strnid.o" =>
                [
                    "crypto/asn1/a_strnid.c",
                ],
            "crypto/asn1/libcrypto-lib-a_time.o" =>
                [
                    "crypto/asn1/a_time.c",
                ],
            "crypto/asn1/libcrypto-lib-a_type.o" =>
                [
                    "crypto/asn1/a_type.c",
                ],
            "crypto/asn1/libcrypto-lib-a_utctm.o" =>
                [
                    "crypto/asn1/a_utctm.c",
                ],
            "crypto/asn1/libcrypto-lib-a_utf8.o" =>
                [
                    "crypto/asn1/a_utf8.c",
                ],
            "crypto/asn1/libcrypto-lib-a_verify.o" =>
                [
                    "crypto/asn1/a_verify.c",
                ],
            "crypto/asn1/libcrypto-lib-ameth_lib.o" =>
                [
                    "crypto/asn1/ameth_lib.c",
                ],
            "crypto/asn1/libcrypto-lib-asn1_err.o" =>
                [
                    "crypto/asn1/asn1_err.c",
                ],
            "crypto/asn1/libcrypto-lib-asn1_gen.o" =>
                [
                    "crypto/asn1/asn1_gen.c",
                ],
            "crypto/asn1/libcrypto-lib-asn1_item_list.o" =>
                [
                    "crypto/asn1/asn1_item_list.c",
                ],
            "crypto/asn1/libcrypto-lib-asn1_lib.o" =>
                [
                    "crypto/asn1/asn1_lib.c",
                ],
            "crypto/asn1/libcrypto-lib-asn1_par.o" =>
                [
                    "crypto/asn1/asn1_par.c",
                ],
            "crypto/asn1/libcrypto-lib-asn_mime.o" =>
                [
                    "crypto/asn1/asn_mime.c",
                ],
            "crypto/asn1/libcrypto-lib-asn_moid.o" =>
                [
                    "crypto/asn1/asn_moid.c",
                ],
            "crypto/asn1/libcrypto-lib-asn_mstbl.o" =>
                [
                    "crypto/asn1/asn_mstbl.c",
                ],
            "crypto/asn1/libcrypto-lib-asn_pack.o" =>
                [
                    "crypto/asn1/asn_pack.c",
                ],
            "crypto/asn1/libcrypto-lib-bio_asn1.o" =>
                [
                    "crypto/asn1/bio_asn1.c",
                ],
            "crypto/asn1/libcrypto-lib-bio_ndef.o" =>
                [
                    "crypto/asn1/bio_ndef.c",
                ],
            "crypto/asn1/libcrypto-lib-d2i_pr.o" =>
                [
                    "crypto/asn1/d2i_pr.c",
                ],
            "crypto/asn1/libcrypto-lib-d2i_pu.o" =>
                [
                    "crypto/asn1/d2i_pu.c",
                ],
            "crypto/asn1/libcrypto-lib-evp_asn1.o" =>
                [
                    "crypto/asn1/evp_asn1.c",
                ],
            "crypto/asn1/libcrypto-lib-f_int.o" =>
                [
                    "crypto/asn1/f_int.c",
                ],
            "crypto/asn1/libcrypto-lib-f_string.o" =>
                [
                    "crypto/asn1/f_string.c",
                ],
            "crypto/asn1/libcrypto-lib-i2d_pr.o" =>
                [
                    "crypto/asn1/i2d_pr.c",
                ],
            "crypto/asn1/libcrypto-lib-i2d_pu.o" =>
                [
                    "crypto/asn1/i2d_pu.c",
                ],
            "crypto/asn1/libcrypto-lib-n_pkey.o" =>
                [
                    "crypto/asn1/n_pkey.c",
                ],
            "crypto/asn1/libcrypto-lib-nsseq.o" =>
                [
                    "crypto/asn1/nsseq.c",
                ],
            "crypto/asn1/libcrypto-lib-p5_pbe.o" =>
                [
                    "crypto/asn1/p5_pbe.c",
                ],
            "crypto/asn1/libcrypto-lib-p5_pbev2.o" =>
                [
                    "crypto/asn1/p5_pbev2.c",
                ],
            "crypto/asn1/libcrypto-lib-p5_scrypt.o" =>
                [
                    "crypto/asn1/p5_scrypt.c",
                ],
            "crypto/asn1/libcrypto-lib-p8_pkey.o" =>
                [
                    "crypto/asn1/p8_pkey.c",
                ],
            "crypto/asn1/libcrypto-lib-t_bitst.o" =>
                [
                    "crypto/asn1/t_bitst.c",
                ],
            "crypto/asn1/libcrypto-lib-t_pkey.o" =>
                [
                    "crypto/asn1/t_pkey.c",
                ],
            "crypto/asn1/libcrypto-lib-t_spki.o" =>
                [
                    "crypto/asn1/t_spki.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_dec.o" =>
                [
                    "crypto/asn1/tasn_dec.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_enc.o" =>
                [
                    "crypto/asn1/tasn_enc.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_fre.o" =>
                [
                    "crypto/asn1/tasn_fre.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_new.o" =>
                [
                    "crypto/asn1/tasn_new.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_prn.o" =>
                [
                    "crypto/asn1/tasn_prn.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_scn.o" =>
                [
                    "crypto/asn1/tasn_scn.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_typ.o" =>
                [
                    "crypto/asn1/tasn_typ.c",
                ],
            "crypto/asn1/libcrypto-lib-tasn_utl.o" =>
                [
                    "crypto/asn1/tasn_utl.c",
                ],
            "crypto/asn1/libcrypto-lib-x_algor.o" =>
                [
                    "crypto/asn1/x_algor.c",
                ],
            "crypto/asn1/libcrypto-lib-x_bignum.o" =>
                [
                    "crypto/asn1/x_bignum.c",
                ],
            "crypto/asn1/libcrypto-lib-x_info.o" =>
                [
                    "crypto/asn1/x_info.c",
                ],
            "crypto/asn1/libcrypto-lib-x_int64.o" =>
                [
                    "crypto/asn1/x_int64.c",
                ],
            "crypto/asn1/libcrypto-lib-x_long.o" =>
                [
                    "crypto/asn1/x_long.c",
                ],
            "crypto/asn1/libcrypto-lib-x_pkey.o" =>
                [
                    "crypto/asn1/x_pkey.c",
                ],
            "crypto/asn1/libcrypto-lib-x_sig.o" =>
                [
                    "crypto/asn1/x_sig.c",
                ],
            "crypto/asn1/libcrypto-lib-x_spki.o" =>
                [
                    "crypto/asn1/x_spki.c",
                ],
            "crypto/asn1/libcrypto-lib-x_val.o" =>
                [
                    "crypto/asn1/x_val.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_bitstr.o" =>
                [
                    "crypto/asn1/a_bitstr.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_d2i_fp.o" =>
                [
                    "crypto/asn1/a_d2i_fp.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_digest.o" =>
                [
                    "crypto/asn1/a_digest.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_dup.o" =>
                [
                    "crypto/asn1/a_dup.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_gentm.o" =>
                [
                    "crypto/asn1/a_gentm.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_i2d_fp.o" =>
                [
                    "crypto/asn1/a_i2d_fp.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_int.o" =>
                [
                    "crypto/asn1/a_int.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_mbstr.o" =>
                [
                    "crypto/asn1/a_mbstr.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_object.o" =>
                [
                    "crypto/asn1/a_object.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_octet.o" =>
                [
                    "crypto/asn1/a_octet.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_print.o" =>
                [
                    "crypto/asn1/a_print.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_sign.o" =>
                [
                    "crypto/asn1/a_sign.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_strex.o" =>
                [
                    "crypto/asn1/a_strex.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_strnid.o" =>
                [
                    "crypto/asn1/a_strnid.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_time.o" =>
                [
                    "crypto/asn1/a_time.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_type.o" =>
                [
                    "crypto/asn1/a_type.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_utctm.o" =>
                [
                    "crypto/asn1/a_utctm.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_utf8.o" =>
                [
                    "crypto/asn1/a_utf8.c",
                ],
            "crypto/asn1/libcrypto-shlib-a_verify.o" =>
                [
                    "crypto/asn1/a_verify.c",
                ],
            "crypto/asn1/libcrypto-shlib-ameth_lib.o" =>
                [
                    "crypto/asn1/ameth_lib.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn1_err.o" =>
                [
                    "crypto/asn1/asn1_err.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn1_gen.o" =>
                [
                    "crypto/asn1/asn1_gen.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn1_item_list.o" =>
                [
                    "crypto/asn1/asn1_item_list.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn1_lib.o" =>
                [
                    "crypto/asn1/asn1_lib.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn1_par.o" =>
                [
                    "crypto/asn1/asn1_par.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn_mime.o" =>
                [
                    "crypto/asn1/asn_mime.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn_moid.o" =>
                [
                    "crypto/asn1/asn_moid.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn_mstbl.o" =>
                [
                    "crypto/asn1/asn_mstbl.c",
                ],
            "crypto/asn1/libcrypto-shlib-asn_pack.o" =>
                [
                    "crypto/asn1/asn_pack.c",
                ],
            "crypto/asn1/libcrypto-shlib-bio_asn1.o" =>
                [
                    "crypto/asn1/bio_asn1.c",
                ],
            "crypto/asn1/libcrypto-shlib-bio_ndef.o" =>
                [
                    "crypto/asn1/bio_ndef.c",
                ],
            "crypto/asn1/libcrypto-shlib-d2i_pr.o" =>
                [
                    "crypto/asn1/d2i_pr.c",
                ],
            "crypto/asn1/libcrypto-shlib-d2i_pu.o" =>
                [
                    "crypto/asn1/d2i_pu.c",
                ],
            "crypto/asn1/libcrypto-shlib-evp_asn1.o" =>
                [
                    "crypto/asn1/evp_asn1.c",
                ],
            "crypto/asn1/libcrypto-shlib-f_int.o" =>
                [
                    "crypto/asn1/f_int.c",
                ],
            "crypto/asn1/libcrypto-shlib-f_string.o" =>
                [
                    "crypto/asn1/f_string.c",
                ],
            "crypto/asn1/libcrypto-shlib-i2d_pr.o" =>
                [
                    "crypto/asn1/i2d_pr.c",
                ],
            "crypto/asn1/libcrypto-shlib-i2d_pu.o" =>
                [
                    "crypto/asn1/i2d_pu.c",
                ],
            "crypto/asn1/libcrypto-shlib-n_pkey.o" =>
                [
                    "crypto/asn1/n_pkey.c",
                ],
            "crypto/asn1/libcrypto-shlib-nsseq.o" =>
                [
                    "crypto/asn1/nsseq.c",
                ],
            "crypto/asn1/libcrypto-shlib-p5_pbe.o" =>
                [
                    "crypto/asn1/p5_pbe.c",
                ],
            "crypto/asn1/libcrypto-shlib-p5_pbev2.o" =>
                [
                    "crypto/asn1/p5_pbev2.c",
                ],
            "crypto/asn1/libcrypto-shlib-p5_scrypt.o" =>
                [
                    "crypto/asn1/p5_scrypt.c",
                ],
            "crypto/asn1/libcrypto-shlib-p8_pkey.o" =>
                [
                    "crypto/asn1/p8_pkey.c",
                ],
            "crypto/asn1/libcrypto-shlib-t_bitst.o" =>
                [
                    "crypto/asn1/t_bitst.c",
                ],
            "crypto/asn1/libcrypto-shlib-t_pkey.o" =>
                [
                    "crypto/asn1/t_pkey.c",
                ],
            "crypto/asn1/libcrypto-shlib-t_spki.o" =>
                [
                    "crypto/asn1/t_spki.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_dec.o" =>
                [
                    "crypto/asn1/tasn_dec.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_enc.o" =>
                [
                    "crypto/asn1/tasn_enc.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_fre.o" =>
                [
                    "crypto/asn1/tasn_fre.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_new.o" =>
                [
                    "crypto/asn1/tasn_new.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_prn.o" =>
                [
                    "crypto/asn1/tasn_prn.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_scn.o" =>
                [
                    "crypto/asn1/tasn_scn.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_typ.o" =>
                [
                    "crypto/asn1/tasn_typ.c",
                ],
            "crypto/asn1/libcrypto-shlib-tasn_utl.o" =>
                [
                    "crypto/asn1/tasn_utl.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_algor.o" =>
                [
                    "crypto/asn1/x_algor.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_bignum.o" =>
                [
                    "crypto/asn1/x_bignum.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_info.o" =>
                [
                    "crypto/asn1/x_info.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_int64.o" =>
                [
                    "crypto/asn1/x_int64.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_long.o" =>
                [
                    "crypto/asn1/x_long.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_pkey.o" =>
                [
                    "crypto/asn1/x_pkey.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_sig.o" =>
                [
                    "crypto/asn1/x_sig.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_spki.o" =>
                [
                    "crypto/asn1/x_spki.c",
                ],
            "crypto/asn1/libcrypto-shlib-x_val.o" =>
                [
                    "crypto/asn1/x_val.c",
                ],
            "crypto/async/arch/libcrypto-lib-async_null.o" =>
                [
                    "crypto/async/arch/async_null.c",
                ],
            "crypto/async/arch/libcrypto-lib-async_posix.o" =>
                [
                    "crypto/async/arch/async_posix.c",
                ],
            "crypto/async/arch/libcrypto-lib-async_win.o" =>
                [
                    "crypto/async/arch/async_win.c",
                ],
            "crypto/async/arch/libcrypto-shlib-async_null.o" =>
                [
                    "crypto/async/arch/async_null.c",
                ],
            "crypto/async/arch/libcrypto-shlib-async_posix.o" =>
                [
                    "crypto/async/arch/async_posix.c",
                ],
            "crypto/async/arch/libcrypto-shlib-async_win.o" =>
                [
                    "crypto/async/arch/async_win.c",
                ],
            "crypto/async/libcrypto-lib-async.o" =>
                [
                    "crypto/async/async.c",
                ],
            "crypto/async/libcrypto-lib-async_err.o" =>
                [
                    "crypto/async/async_err.c",
                ],
            "crypto/async/libcrypto-lib-async_wait.o" =>
                [
                    "crypto/async/async_wait.c",
                ],
            "crypto/async/libcrypto-shlib-async.o" =>
                [
                    "crypto/async/async.c",
                ],
            "crypto/async/libcrypto-shlib-async_err.o" =>
                [
                    "crypto/async/async_err.c",
                ],
            "crypto/async/libcrypto-shlib-async_wait.o" =>
                [
                    "crypto/async/async_wait.c",
                ],
            "crypto/bf/libcrypto-lib-bf_cfb64.o" =>
                [
                    "crypto/bf/bf_cfb64.c",
                ],
            "crypto/bf/libcrypto-lib-bf_ecb.o" =>
                [
                    "crypto/bf/bf_ecb.c",
                ],
            "crypto/bf/libcrypto-lib-bf_enc.o" =>
                [
                    "crypto/bf/bf_enc.c",
                ],
            "crypto/bf/libcrypto-lib-bf_ofb64.o" =>
                [
                    "crypto/bf/bf_ofb64.c",
                ],
            "crypto/bf/libcrypto-lib-bf_skey.o" =>
                [
                    "crypto/bf/bf_skey.c",
                ],
            "crypto/bf/libcrypto-shlib-bf_cfb64.o" =>
                [
                    "crypto/bf/bf_cfb64.c",
                ],
            "crypto/bf/libcrypto-shlib-bf_ecb.o" =>
                [
                    "crypto/bf/bf_ecb.c",
                ],
            "crypto/bf/libcrypto-shlib-bf_enc.o" =>
                [
                    "crypto/bf/bf_enc.c",
                ],
            "crypto/bf/libcrypto-shlib-bf_ofb64.o" =>
                [
                    "crypto/bf/bf_ofb64.c",
                ],
            "crypto/bf/libcrypto-shlib-bf_skey.o" =>
                [
                    "crypto/bf/bf_skey.c",
                ],
            "crypto/bio/libcrypto-lib-b_addr.o" =>
                [
                    "crypto/bio/b_addr.c",
                ],
            "crypto/bio/libcrypto-lib-b_dump.o" =>
                [
                    "crypto/bio/b_dump.c",
                ],
            "crypto/bio/libcrypto-lib-b_print.o" =>
                [
                    "crypto/bio/b_print.c",
                ],
            "crypto/bio/libcrypto-lib-b_sock.o" =>
                [
                    "crypto/bio/b_sock.c",
                ],
            "crypto/bio/libcrypto-lib-b_sock2.o" =>
                [
                    "crypto/bio/b_sock2.c",
                ],
            "crypto/bio/libcrypto-lib-bf_buff.o" =>
                [
                    "crypto/bio/bf_buff.c",
                ],
            "crypto/bio/libcrypto-lib-bf_lbuf.o" =>
                [
                    "crypto/bio/bf_lbuf.c",
                ],
            "crypto/bio/libcrypto-lib-bf_nbio.o" =>
                [
                    "crypto/bio/bf_nbio.c",
                ],
            "crypto/bio/libcrypto-lib-bf_null.o" =>
                [
                    "crypto/bio/bf_null.c",
                ],
            "crypto/bio/libcrypto-lib-bio_cb.o" =>
                [
                    "crypto/bio/bio_cb.c",
                ],
            "crypto/bio/libcrypto-lib-bio_err.o" =>
                [
                    "crypto/bio/bio_err.c",
                ],
            "crypto/bio/libcrypto-lib-bio_lib.o" =>
                [
                    "crypto/bio/bio_lib.c",
                ],
            "crypto/bio/libcrypto-lib-bio_meth.o" =>
                [
                    "crypto/bio/bio_meth.c",
                ],
            "crypto/bio/libcrypto-lib-bss_acpt.o" =>
                [
                    "crypto/bio/bss_acpt.c",
                ],
            "crypto/bio/libcrypto-lib-bss_bio.o" =>
                [
                    "crypto/bio/bss_bio.c",
                ],
            "crypto/bio/libcrypto-lib-bss_conn.o" =>
                [
                    "crypto/bio/bss_conn.c",
                ],
            "crypto/bio/libcrypto-lib-bss_dgram.o" =>
                [
                    "crypto/bio/bss_dgram.c",
                ],
            "crypto/bio/libcrypto-lib-bss_fd.o" =>
                [
                    "crypto/bio/bss_fd.c",
                ],
            "crypto/bio/libcrypto-lib-bss_file.o" =>
                [
                    "crypto/bio/bss_file.c",
                ],
            "crypto/bio/libcrypto-lib-bss_log.o" =>
                [
                    "crypto/bio/bss_log.c",
                ],
            "crypto/bio/libcrypto-lib-bss_mem.o" =>
                [
                    "crypto/bio/bss_mem.c",
                ],
            "crypto/bio/libcrypto-lib-bss_null.o" =>
                [
                    "crypto/bio/bss_null.c",
                ],
            "crypto/bio/libcrypto-lib-bss_sock.o" =>
                [
                    "crypto/bio/bss_sock.c",
                ],
            "crypto/bio/libcrypto-shlib-b_addr.o" =>
                [
                    "crypto/bio/b_addr.c",
                ],
            "crypto/bio/libcrypto-shlib-b_dump.o" =>
                [
                    "crypto/bio/b_dump.c",
                ],
            "crypto/bio/libcrypto-shlib-b_print.o" =>
                [
                    "crypto/bio/b_print.c",
                ],
            "crypto/bio/libcrypto-shlib-b_sock.o" =>
                [
                    "crypto/bio/b_sock.c",
                ],
            "crypto/bio/libcrypto-shlib-b_sock2.o" =>
                [
                    "crypto/bio/b_sock2.c",
                ],
            "crypto/bio/libcrypto-shlib-bf_buff.o" =>
                [
                    "crypto/bio/bf_buff.c",
                ],
            "crypto/bio/libcrypto-shlib-bf_lbuf.o" =>
                [
                    "crypto/bio/bf_lbuf.c",
                ],
            "crypto/bio/libcrypto-shlib-bf_nbio.o" =>
                [
                    "crypto/bio/bf_nbio.c",
                ],
            "crypto/bio/libcrypto-shlib-bf_null.o" =>
                [
                    "crypto/bio/bf_null.c",
                ],
            "crypto/bio/libcrypto-shlib-bio_cb.o" =>
                [
                    "crypto/bio/bio_cb.c",
                ],
            "crypto/bio/libcrypto-shlib-bio_err.o" =>
                [
                    "crypto/bio/bio_err.c",
                ],
            "crypto/bio/libcrypto-shlib-bio_lib.o" =>
                [
                    "crypto/bio/bio_lib.c",
                ],
            "crypto/bio/libcrypto-shlib-bio_meth.o" =>
                [
                    "crypto/bio/bio_meth.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_acpt.o" =>
                [
                    "crypto/bio/bss_acpt.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_bio.o" =>
                [
                    "crypto/bio/bss_bio.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_conn.o" =>
                [
                    "crypto/bio/bss_conn.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_dgram.o" =>
                [
                    "crypto/bio/bss_dgram.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_fd.o" =>
                [
                    "crypto/bio/bss_fd.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_file.o" =>
                [
                    "crypto/bio/bss_file.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_log.o" =>
                [
                    "crypto/bio/bss_log.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_mem.o" =>
                [
                    "crypto/bio/bss_mem.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_null.o" =>
                [
                    "crypto/bio/bss_null.c",
                ],
            "crypto/bio/libcrypto-shlib-bss_sock.o" =>
                [
                    "crypto/bio/bss_sock.c",
                ],
            "crypto/blake2/libcrypto-lib-blake2b.o" =>
                [
                    "crypto/blake2/blake2b.c",
                ],
            "crypto/blake2/libcrypto-lib-blake2b_mac.o" =>
                [
                    "crypto/blake2/blake2b_mac.c",
                ],
            "crypto/blake2/libcrypto-lib-blake2s.o" =>
                [
                    "crypto/blake2/blake2s.c",
                ],
            "crypto/blake2/libcrypto-lib-blake2s_mac.o" =>
                [
                    "crypto/blake2/blake2s_mac.c",
                ],
            "crypto/blake2/libcrypto-lib-m_blake2b.o" =>
                [
                    "crypto/blake2/m_blake2b.c",
                ],
            "crypto/blake2/libcrypto-lib-m_blake2s.o" =>
                [
                    "crypto/blake2/m_blake2s.c",
                ],
            "crypto/blake2/libcrypto-shlib-blake2b.o" =>
                [
                    "crypto/blake2/blake2b.c",
                ],
            "crypto/blake2/libcrypto-shlib-blake2b_mac.o" =>
                [
                    "crypto/blake2/blake2b_mac.c",
                ],
            "crypto/blake2/libcrypto-shlib-blake2s.o" =>
                [
                    "crypto/blake2/blake2s.c",
                ],
            "crypto/blake2/libcrypto-shlib-blake2s_mac.o" =>
                [
                    "crypto/blake2/blake2s_mac.c",
                ],
            "crypto/blake2/libcrypto-shlib-m_blake2b.o" =>
                [
                    "crypto/blake2/m_blake2b.c",
                ],
            "crypto/blake2/libcrypto-shlib-m_blake2s.o" =>
                [
                    "crypto/blake2/m_blake2s.c",
                ],
            "crypto/bn/asm/libcrypto-lib-x86_64-gcc.o" =>
                [
                    "crypto/bn/asm/x86_64-gcc.c",
                ],
            "crypto/bn/asm/libcrypto-shlib-x86_64-gcc.o" =>
                [
                    "crypto/bn/asm/x86_64-gcc.c",
                ],
            "crypto/bn/libcrypto-lib-bn_add.o" =>
                [
                    "crypto/bn/bn_add.c",
                ],
            "crypto/bn/libcrypto-lib-bn_blind.o" =>
                [
                    "crypto/bn/bn_blind.c",
                ],
            "crypto/bn/libcrypto-lib-bn_const.o" =>
                [
                    "crypto/bn/bn_const.c",
                ],
            "crypto/bn/libcrypto-lib-bn_ctx.o" =>
                [
                    "crypto/bn/bn_ctx.c",
                ],
            "crypto/bn/libcrypto-lib-bn_depr.o" =>
                [
                    "crypto/bn/bn_depr.c",
                ],
            "crypto/bn/libcrypto-lib-bn_dh.o" =>
                [
                    "crypto/bn/bn_dh.c",
                ],
            "crypto/bn/libcrypto-lib-bn_div.o" =>
                [
                    "crypto/bn/bn_div.c",
                ],
            "crypto/bn/libcrypto-lib-bn_err.o" =>
                [
                    "crypto/bn/bn_err.c",
                ],
            "crypto/bn/libcrypto-lib-bn_exp.o" =>
                [
                    "crypto/bn/bn_exp.c",
                ],
            "crypto/bn/libcrypto-lib-bn_exp2.o" =>
                [
                    "crypto/bn/bn_exp2.c",
                ],
            "crypto/bn/libcrypto-lib-bn_gcd.o" =>
                [
                    "crypto/bn/bn_gcd.c",
                ],
            "crypto/bn/libcrypto-lib-bn_gf2m.o" =>
                [
                    "crypto/bn/bn_gf2m.c",
                ],
            "crypto/bn/libcrypto-lib-bn_intern.o" =>
                [
                    "crypto/bn/bn_intern.c",
                ],
            "crypto/bn/libcrypto-lib-bn_kron.o" =>
                [
                    "crypto/bn/bn_kron.c",
                ],
            "crypto/bn/libcrypto-lib-bn_lib.o" =>
                [
                    "crypto/bn/bn_lib.c",
                ],
            "crypto/bn/libcrypto-lib-bn_mod.o" =>
                [
                    "crypto/bn/bn_mod.c",
                ],
            "crypto/bn/libcrypto-lib-bn_mont.o" =>
                [
                    "crypto/bn/bn_mont.c",
                ],
            "crypto/bn/libcrypto-lib-bn_mpi.o" =>
                [
                    "crypto/bn/bn_mpi.c",
                ],
            "crypto/bn/libcrypto-lib-bn_mul.o" =>
                [
                    "crypto/bn/bn_mul.c",
                ],
            "crypto/bn/libcrypto-lib-bn_nist.o" =>
                [
                    "crypto/bn/bn_nist.c",
                ],
            "crypto/bn/libcrypto-lib-bn_prime.o" =>
                [
                    "crypto/bn/bn_prime.c",
                ],
            "crypto/bn/libcrypto-lib-bn_print.o" =>
                [
                    "crypto/bn/bn_print.c",
                ],
            "crypto/bn/libcrypto-lib-bn_rand.o" =>
                [
                    "crypto/bn/bn_rand.c",
                ],
            "crypto/bn/libcrypto-lib-bn_recp.o" =>
                [
                    "crypto/bn/bn_recp.c",
                ],
            "crypto/bn/libcrypto-lib-bn_rsa_fips186_4.o" =>
                [
                    "crypto/bn/bn_rsa_fips186_4.c",
                ],
            "crypto/bn/libcrypto-lib-bn_shift.o" =>
                [
                    "crypto/bn/bn_shift.c",
                ],
            "crypto/bn/libcrypto-lib-bn_sqr.o" =>
                [
                    "crypto/bn/bn_sqr.c",
                ],
            "crypto/bn/libcrypto-lib-bn_sqrt.o" =>
                [
                    "crypto/bn/bn_sqrt.c",
                ],
            "crypto/bn/libcrypto-lib-bn_srp.o" =>
                [
                    "crypto/bn/bn_srp.c",
                ],
            "crypto/bn/libcrypto-lib-bn_word.o" =>
                [
                    "crypto/bn/bn_word.c",
                ],
            "crypto/bn/libcrypto-lib-bn_x931p.o" =>
                [
                    "crypto/bn/bn_x931p.c",
                ],
            "crypto/bn/libcrypto-lib-rsaz-avx2.o" =>
                [
                    "crypto/bn/rsaz-avx2.s",
                ],
            "crypto/bn/libcrypto-lib-rsaz-x86_64.o" =>
                [
                    "crypto/bn/rsaz-x86_64.s",
                ],
            "crypto/bn/libcrypto-lib-rsaz_exp.o" =>
                [
                    "crypto/bn/rsaz_exp.c",
                ],
            "crypto/bn/libcrypto-lib-x86_64-gf2m.o" =>
                [
                    "crypto/bn/x86_64-gf2m.s",
                ],
            "crypto/bn/libcrypto-lib-x86_64-mont.o" =>
                [
                    "crypto/bn/x86_64-mont.s",
                ],
            "crypto/bn/libcrypto-lib-x86_64-mont5.o" =>
                [
                    "crypto/bn/x86_64-mont5.s",
                ],
            "crypto/bn/libcrypto-shlib-bn_add.o" =>
                [
                    "crypto/bn/bn_add.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_blind.o" =>
                [
                    "crypto/bn/bn_blind.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_const.o" =>
                [
                    "crypto/bn/bn_const.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_ctx.o" =>
                [
                    "crypto/bn/bn_ctx.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_depr.o" =>
                [
                    "crypto/bn/bn_depr.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_dh.o" =>
                [
                    "crypto/bn/bn_dh.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_div.o" =>
                [
                    "crypto/bn/bn_div.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_err.o" =>
                [
                    "crypto/bn/bn_err.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_exp.o" =>
                [
                    "crypto/bn/bn_exp.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_exp2.o" =>
                [
                    "crypto/bn/bn_exp2.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_gcd.o" =>
                [
                    "crypto/bn/bn_gcd.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_gf2m.o" =>
                [
                    "crypto/bn/bn_gf2m.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_intern.o" =>
                [
                    "crypto/bn/bn_intern.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_kron.o" =>
                [
                    "crypto/bn/bn_kron.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_lib.o" =>
                [
                    "crypto/bn/bn_lib.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_mod.o" =>
                [
                    "crypto/bn/bn_mod.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_mont.o" =>
                [
                    "crypto/bn/bn_mont.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_mpi.o" =>
                [
                    "crypto/bn/bn_mpi.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_mul.o" =>
                [
                    "crypto/bn/bn_mul.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_nist.o" =>
                [
                    "crypto/bn/bn_nist.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_prime.o" =>
                [
                    "crypto/bn/bn_prime.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_print.o" =>
                [
                    "crypto/bn/bn_print.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_rand.o" =>
                [
                    "crypto/bn/bn_rand.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_recp.o" =>
                [
                    "crypto/bn/bn_recp.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_rsa_fips186_4.o" =>
                [
                    "crypto/bn/bn_rsa_fips186_4.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_shift.o" =>
                [
                    "crypto/bn/bn_shift.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_sqr.o" =>
                [
                    "crypto/bn/bn_sqr.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_sqrt.o" =>
                [
                    "crypto/bn/bn_sqrt.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_srp.o" =>
                [
                    "crypto/bn/bn_srp.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_word.o" =>
                [
                    "crypto/bn/bn_word.c",
                ],
            "crypto/bn/libcrypto-shlib-bn_x931p.o" =>
                [
                    "crypto/bn/bn_x931p.c",
                ],
            "crypto/bn/libcrypto-shlib-rsaz-avx2.o" =>
                [
                    "crypto/bn/rsaz-avx2.s",
                ],
            "crypto/bn/libcrypto-shlib-rsaz-x86_64.o" =>
                [
                    "crypto/bn/rsaz-x86_64.s",
                ],
            "crypto/bn/libcrypto-shlib-rsaz_exp.o" =>
                [
                    "crypto/bn/rsaz_exp.c",
                ],
            "crypto/bn/libcrypto-shlib-x86_64-gf2m.o" =>
                [
                    "crypto/bn/x86_64-gf2m.s",
                ],
            "crypto/bn/libcrypto-shlib-x86_64-mont.o" =>
                [
                    "crypto/bn/x86_64-mont.s",
                ],
            "crypto/bn/libcrypto-shlib-x86_64-mont5.o" =>
                [
                    "crypto/bn/x86_64-mont5.s",
                ],
            "crypto/buffer/libcrypto-lib-buf_err.o" =>
                [
                    "crypto/buffer/buf_err.c",
                ],
            "crypto/buffer/libcrypto-lib-buffer.o" =>
                [
                    "crypto/buffer/buffer.c",
                ],
            "crypto/buffer/libcrypto-shlib-buf_err.o" =>
                [
                    "crypto/buffer/buf_err.c",
                ],
            "crypto/buffer/libcrypto-shlib-buffer.o" =>
                [
                    "crypto/buffer/buffer.c",
                ],
            "crypto/camellia/libcrypto-lib-cmll-x86_64.o" =>
                [
                    "crypto/camellia/cmll-x86_64.s",
                ],
            "crypto/camellia/libcrypto-lib-cmll_cfb.o" =>
                [
                    "crypto/camellia/cmll_cfb.c",
                ],
            "crypto/camellia/libcrypto-lib-cmll_ctr.o" =>
                [
                    "crypto/camellia/cmll_ctr.c",
                ],
            "crypto/camellia/libcrypto-lib-cmll_ecb.o" =>
                [
                    "crypto/camellia/cmll_ecb.c",
                ],
            "crypto/camellia/libcrypto-lib-cmll_misc.o" =>
                [
                    "crypto/camellia/cmll_misc.c",
                ],
            "crypto/camellia/libcrypto-lib-cmll_ofb.o" =>
                [
                    "crypto/camellia/cmll_ofb.c",
                ],
            "crypto/camellia/libcrypto-shlib-cmll-x86_64.o" =>
                [
                    "crypto/camellia/cmll-x86_64.s",
                ],
            "crypto/camellia/libcrypto-shlib-cmll_cfb.o" =>
                [
                    "crypto/camellia/cmll_cfb.c",
                ],
            "crypto/camellia/libcrypto-shlib-cmll_ctr.o" =>
                [
                    "crypto/camellia/cmll_ctr.c",
                ],
            "crypto/camellia/libcrypto-shlib-cmll_ecb.o" =>
                [
                    "crypto/camellia/cmll_ecb.c",
                ],
            "crypto/camellia/libcrypto-shlib-cmll_misc.o" =>
                [
                    "crypto/camellia/cmll_misc.c",
                ],
            "crypto/camellia/libcrypto-shlib-cmll_ofb.o" =>
                [
                    "crypto/camellia/cmll_ofb.c",
                ],
            "crypto/cast/libcrypto-lib-c_cfb64.o" =>
                [
                    "crypto/cast/c_cfb64.c",
                ],
            "crypto/cast/libcrypto-lib-c_ecb.o" =>
                [
                    "crypto/cast/c_ecb.c",
                ],
            "crypto/cast/libcrypto-lib-c_enc.o" =>
                [
                    "crypto/cast/c_enc.c",
                ],
            "crypto/cast/libcrypto-lib-c_ofb64.o" =>
                [
                    "crypto/cast/c_ofb64.c",
                ],
            "crypto/cast/libcrypto-lib-c_skey.o" =>
                [
                    "crypto/cast/c_skey.c",
                ],
            "crypto/cast/libcrypto-shlib-c_cfb64.o" =>
                [
                    "crypto/cast/c_cfb64.c",
                ],
            "crypto/cast/libcrypto-shlib-c_ecb.o" =>
                [
                    "crypto/cast/c_ecb.c",
                ],
            "crypto/cast/libcrypto-shlib-c_enc.o" =>
                [
                    "crypto/cast/c_enc.c",
                ],
            "crypto/cast/libcrypto-shlib-c_ofb64.o" =>
                [
                    "crypto/cast/c_ofb64.c",
                ],
            "crypto/cast/libcrypto-shlib-c_skey.o" =>
                [
                    "crypto/cast/c_skey.c",
                ],
            "crypto/chacha/libcrypto-lib-chacha-x86_64.o" =>
                [
                    "crypto/chacha/chacha-x86_64.s",
                ],
            "crypto/chacha/libcrypto-shlib-chacha-x86_64.o" =>
                [
                    "crypto/chacha/chacha-x86_64.s",
                ],
            "crypto/cmac/libcrypto-lib-cm_ameth.o" =>
                [
                    "crypto/cmac/cm_ameth.c",
                ],
            "crypto/cmac/libcrypto-lib-cm_meth.o" =>
                [
                    "crypto/cmac/cm_meth.c",
                ],
            "crypto/cmac/libcrypto-lib-cmac.o" =>
                [
                    "crypto/cmac/cmac.c",
                ],
            "crypto/cmac/libcrypto-shlib-cm_ameth.o" =>
                [
                    "crypto/cmac/cm_ameth.c",
                ],
            "crypto/cmac/libcrypto-shlib-cm_meth.o" =>
                [
                    "crypto/cmac/cm_meth.c",
                ],
            "crypto/cmac/libcrypto-shlib-cmac.o" =>
                [
                    "crypto/cmac/cmac.c",
                ],
            "crypto/cms/libcrypto-lib-cms_asn1.o" =>
                [
                    "crypto/cms/cms_asn1.c",
                ],
            "crypto/cms/libcrypto-lib-cms_att.o" =>
                [
                    "crypto/cms/cms_att.c",
                ],
            "crypto/cms/libcrypto-lib-cms_cd.o" =>
                [
                    "crypto/cms/cms_cd.c",
                ],
            "crypto/cms/libcrypto-lib-cms_dd.o" =>
                [
                    "crypto/cms/cms_dd.c",
                ],
            "crypto/cms/libcrypto-lib-cms_enc.o" =>
                [
                    "crypto/cms/cms_enc.c",
                ],
            "crypto/cms/libcrypto-lib-cms_env.o" =>
                [
                    "crypto/cms/cms_env.c",
                ],
            "crypto/cms/libcrypto-lib-cms_err.o" =>
                [
                    "crypto/cms/cms_err.c",
                ],
            "crypto/cms/libcrypto-lib-cms_ess.o" =>
                [
                    "crypto/cms/cms_ess.c",
                ],
            "crypto/cms/libcrypto-lib-cms_io.o" =>
                [
                    "crypto/cms/cms_io.c",
                ],
            "crypto/cms/libcrypto-lib-cms_kari.o" =>
                [
                    "crypto/cms/cms_kari.c",
                ],
            "crypto/cms/libcrypto-lib-cms_lib.o" =>
                [
                    "crypto/cms/cms_lib.c",
                ],
            "crypto/cms/libcrypto-lib-cms_pwri.o" =>
                [
                    "crypto/cms/cms_pwri.c",
                ],
            "crypto/cms/libcrypto-lib-cms_sd.o" =>
                [
                    "crypto/cms/cms_sd.c",
                ],
            "crypto/cms/libcrypto-lib-cms_smime.o" =>
                [
                    "crypto/cms/cms_smime.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_asn1.o" =>
                [
                    "crypto/cms/cms_asn1.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_att.o" =>
                [
                    "crypto/cms/cms_att.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_cd.o" =>
                [
                    "crypto/cms/cms_cd.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_dd.o" =>
                [
                    "crypto/cms/cms_dd.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_enc.o" =>
                [
                    "crypto/cms/cms_enc.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_env.o" =>
                [
                    "crypto/cms/cms_env.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_err.o" =>
                [
                    "crypto/cms/cms_err.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_ess.o" =>
                [
                    "crypto/cms/cms_ess.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_io.o" =>
                [
                    "crypto/cms/cms_io.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_kari.o" =>
                [
                    "crypto/cms/cms_kari.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_lib.o" =>
                [
                    "crypto/cms/cms_lib.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_pwri.o" =>
                [
                    "crypto/cms/cms_pwri.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_sd.o" =>
                [
                    "crypto/cms/cms_sd.c",
                ],
            "crypto/cms/libcrypto-shlib-cms_smime.o" =>
                [
                    "crypto/cms/cms_smime.c",
                ],
            "crypto/comp/libcrypto-lib-c_zlib.o" =>
                [
                    "crypto/comp/c_zlib.c",
                ],
            "crypto/comp/libcrypto-lib-comp_err.o" =>
                [
                    "crypto/comp/comp_err.c",
                ],
            "crypto/comp/libcrypto-lib-comp_lib.o" =>
                [
                    "crypto/comp/comp_lib.c",
                ],
            "crypto/comp/libcrypto-shlib-c_zlib.o" =>
                [
                    "crypto/comp/c_zlib.c",
                ],
            "crypto/comp/libcrypto-shlib-comp_err.o" =>
                [
                    "crypto/comp/comp_err.c",
                ],
            "crypto/comp/libcrypto-shlib-comp_lib.o" =>
                [
                    "crypto/comp/comp_lib.c",
                ],
            "crypto/conf/libcrypto-lib-conf_api.o" =>
                [
                    "crypto/conf/conf_api.c",
                ],
            "crypto/conf/libcrypto-lib-conf_def.o" =>
                [
                    "crypto/conf/conf_def.c",
                ],
            "crypto/conf/libcrypto-lib-conf_err.o" =>
                [
                    "crypto/conf/conf_err.c",
                ],
            "crypto/conf/libcrypto-lib-conf_lib.o" =>
                [
                    "crypto/conf/conf_lib.c",
                ],
            "crypto/conf/libcrypto-lib-conf_mall.o" =>
                [
                    "crypto/conf/conf_mall.c",
                ],
            "crypto/conf/libcrypto-lib-conf_mod.o" =>
                [
                    "crypto/conf/conf_mod.c",
                ],
            "crypto/conf/libcrypto-lib-conf_sap.o" =>
                [
                    "crypto/conf/conf_sap.c",
                ],
            "crypto/conf/libcrypto-lib-conf_ssl.o" =>
                [
                    "crypto/conf/conf_ssl.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_api.o" =>
                [
                    "crypto/conf/conf_api.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_def.o" =>
                [
                    "crypto/conf/conf_def.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_err.o" =>
                [
                    "crypto/conf/conf_err.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_lib.o" =>
                [
                    "crypto/conf/conf_lib.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_mall.o" =>
                [
                    "crypto/conf/conf_mall.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_mod.o" =>
                [
                    "crypto/conf/conf_mod.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_sap.o" =>
                [
                    "crypto/conf/conf_sap.c",
                ],
            "crypto/conf/libcrypto-shlib-conf_ssl.o" =>
                [
                    "crypto/conf/conf_ssl.c",
                ],
            "crypto/crmf/libcrypto-lib-crmf_asn.o" =>
                [
                    "crypto/crmf/crmf_asn.c",
                ],
            "crypto/crmf/libcrypto-lib-crmf_err.o" =>
                [
                    "crypto/crmf/crmf_err.c",
                ],
            "crypto/crmf/libcrypto-lib-crmf_lib.o" =>
                [
                    "crypto/crmf/crmf_lib.c",
                ],
            "crypto/crmf/libcrypto-lib-crmf_pbm.o" =>
                [
                    "crypto/crmf/crmf_pbm.c",
                ],
            "crypto/crmf/libcrypto-shlib-crmf_asn.o" =>
                [
                    "crypto/crmf/crmf_asn.c",
                ],
            "crypto/crmf/libcrypto-shlib-crmf_err.o" =>
                [
                    "crypto/crmf/crmf_err.c",
                ],
            "crypto/crmf/libcrypto-shlib-crmf_lib.o" =>
                [
                    "crypto/crmf/crmf_lib.c",
                ],
            "crypto/crmf/libcrypto-shlib-crmf_pbm.o" =>
                [
                    "crypto/crmf/crmf_pbm.c",
                ],
            "crypto/ct/libcrypto-lib-ct_b64.o" =>
                [
                    "crypto/ct/ct_b64.c",
                ],
            "crypto/ct/libcrypto-lib-ct_err.o" =>
                [
                    "crypto/ct/ct_err.c",
                ],
            "crypto/ct/libcrypto-lib-ct_log.o" =>
                [
                    "crypto/ct/ct_log.c",
                ],
            "crypto/ct/libcrypto-lib-ct_oct.o" =>
                [
                    "crypto/ct/ct_oct.c",
                ],
            "crypto/ct/libcrypto-lib-ct_policy.o" =>
                [
                    "crypto/ct/ct_policy.c",
                ],
            "crypto/ct/libcrypto-lib-ct_prn.o" =>
                [
                    "crypto/ct/ct_prn.c",
                ],
            "crypto/ct/libcrypto-lib-ct_sct.o" =>
                [
                    "crypto/ct/ct_sct.c",
                ],
            "crypto/ct/libcrypto-lib-ct_sct_ctx.o" =>
                [
                    "crypto/ct/ct_sct_ctx.c",
                ],
            "crypto/ct/libcrypto-lib-ct_vfy.o" =>
                [
                    "crypto/ct/ct_vfy.c",
                ],
            "crypto/ct/libcrypto-lib-ct_x509v3.o" =>
                [
                    "crypto/ct/ct_x509v3.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_b64.o" =>
                [
                    "crypto/ct/ct_b64.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_err.o" =>
                [
                    "crypto/ct/ct_err.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_log.o" =>
                [
                    "crypto/ct/ct_log.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_oct.o" =>
                [
                    "crypto/ct/ct_oct.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_policy.o" =>
                [
                    "crypto/ct/ct_policy.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_prn.o" =>
                [
                    "crypto/ct/ct_prn.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_sct.o" =>
                [
                    "crypto/ct/ct_sct.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_sct_ctx.o" =>
                [
                    "crypto/ct/ct_sct_ctx.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_vfy.o" =>
                [
                    "crypto/ct/ct_vfy.c",
                ],
            "crypto/ct/libcrypto-shlib-ct_x509v3.o" =>
                [
                    "crypto/ct/ct_x509v3.c",
                ],
            "crypto/des/libcrypto-lib-cbc_cksm.o" =>
                [
                    "crypto/des/cbc_cksm.c",
                ],
            "crypto/des/libcrypto-lib-cbc_enc.o" =>
                [
                    "crypto/des/cbc_enc.c",
                ],
            "crypto/des/libcrypto-lib-cfb64ede.o" =>
                [
                    "crypto/des/cfb64ede.c",
                ],
            "crypto/des/libcrypto-lib-cfb64enc.o" =>
                [
                    "crypto/des/cfb64enc.c",
                ],
            "crypto/des/libcrypto-lib-cfb_enc.o" =>
                [
                    "crypto/des/cfb_enc.c",
                ],
            "crypto/des/libcrypto-lib-des_enc.o" =>
                [
                    "crypto/des/des_enc.c",
                ],
            "crypto/des/libcrypto-lib-ecb3_enc.o" =>
                [
                    "crypto/des/ecb3_enc.c",
                ],
            "crypto/des/libcrypto-lib-ecb_enc.o" =>
                [
                    "crypto/des/ecb_enc.c",
                ],
            "crypto/des/libcrypto-lib-fcrypt.o" =>
                [
                    "crypto/des/fcrypt.c",
                ],
            "crypto/des/libcrypto-lib-fcrypt_b.o" =>
                [
                    "crypto/des/fcrypt_b.c",
                ],
            "crypto/des/libcrypto-lib-ofb64ede.o" =>
                [
                    "crypto/des/ofb64ede.c",
                ],
            "crypto/des/libcrypto-lib-ofb64enc.o" =>
                [
                    "crypto/des/ofb64enc.c",
                ],
            "crypto/des/libcrypto-lib-ofb_enc.o" =>
                [
                    "crypto/des/ofb_enc.c",
                ],
            "crypto/des/libcrypto-lib-pcbc_enc.o" =>
                [
                    "crypto/des/pcbc_enc.c",
                ],
            "crypto/des/libcrypto-lib-qud_cksm.o" =>
                [
                    "crypto/des/qud_cksm.c",
                ],
            "crypto/des/libcrypto-lib-rand_key.o" =>
                [
                    "crypto/des/rand_key.c",
                ],
            "crypto/des/libcrypto-lib-set_key.o" =>
                [
                    "crypto/des/set_key.c",
                ],
            "crypto/des/libcrypto-lib-str2key.o" =>
                [
                    "crypto/des/str2key.c",
                ],
            "crypto/des/libcrypto-lib-xcbc_enc.o" =>
                [
                    "crypto/des/xcbc_enc.c",
                ],
            "crypto/des/libcrypto-shlib-cbc_cksm.o" =>
                [
                    "crypto/des/cbc_cksm.c",
                ],
            "crypto/des/libcrypto-shlib-cbc_enc.o" =>
                [
                    "crypto/des/cbc_enc.c",
                ],
            "crypto/des/libcrypto-shlib-cfb64ede.o" =>
                [
                    "crypto/des/cfb64ede.c",
                ],
            "crypto/des/libcrypto-shlib-cfb64enc.o" =>
                [
                    "crypto/des/cfb64enc.c",
                ],
            "crypto/des/libcrypto-shlib-cfb_enc.o" =>
                [
                    "crypto/des/cfb_enc.c",
                ],
            "crypto/des/libcrypto-shlib-des_enc.o" =>
                [
                    "crypto/des/des_enc.c",
                ],
            "crypto/des/libcrypto-shlib-ecb3_enc.o" =>
                [
                    "crypto/des/ecb3_enc.c",
                ],
            "crypto/des/libcrypto-shlib-ecb_enc.o" =>
                [
                    "crypto/des/ecb_enc.c",
                ],
            "crypto/des/libcrypto-shlib-fcrypt.o" =>
                [
                    "crypto/des/fcrypt.c",
                ],
            "crypto/des/libcrypto-shlib-fcrypt_b.o" =>
                [
                    "crypto/des/fcrypt_b.c",
                ],
            "crypto/des/libcrypto-shlib-ofb64ede.o" =>
                [
                    "crypto/des/ofb64ede.c",
                ],
            "crypto/des/libcrypto-shlib-ofb64enc.o" =>
                [
                    "crypto/des/ofb64enc.c",
                ],
            "crypto/des/libcrypto-shlib-ofb_enc.o" =>
                [
                    "crypto/des/ofb_enc.c",
                ],
            "crypto/des/libcrypto-shlib-pcbc_enc.o" =>
                [
                    "crypto/des/pcbc_enc.c",
                ],
            "crypto/des/libcrypto-shlib-qud_cksm.o" =>
                [
                    "crypto/des/qud_cksm.c",
                ],
            "crypto/des/libcrypto-shlib-rand_key.o" =>
                [
                    "crypto/des/rand_key.c",
                ],
            "crypto/des/libcrypto-shlib-set_key.o" =>
                [
                    "crypto/des/set_key.c",
                ],
            "crypto/des/libcrypto-shlib-str2key.o" =>
                [
                    "crypto/des/str2key.c",
                ],
            "crypto/des/libcrypto-shlib-xcbc_enc.o" =>
                [
                    "crypto/des/xcbc_enc.c",
                ],
            "crypto/dh/libcrypto-lib-dh_ameth.o" =>
                [
                    "crypto/dh/dh_ameth.c",
                ],
            "crypto/dh/libcrypto-lib-dh_asn1.o" =>
                [
                    "crypto/dh/dh_asn1.c",
                ],
            "crypto/dh/libcrypto-lib-dh_check.o" =>
                [
                    "crypto/dh/dh_check.c",
                ],
            "crypto/dh/libcrypto-lib-dh_depr.o" =>
                [
                    "crypto/dh/dh_depr.c",
                ],
            "crypto/dh/libcrypto-lib-dh_err.o" =>
                [
                    "crypto/dh/dh_err.c",
                ],
            "crypto/dh/libcrypto-lib-dh_gen.o" =>
                [
                    "crypto/dh/dh_gen.c",
                ],
            "crypto/dh/libcrypto-lib-dh_kdf.o" =>
                [
                    "crypto/dh/dh_kdf.c",
                ],
            "crypto/dh/libcrypto-lib-dh_key.o" =>
                [
                    "crypto/dh/dh_key.c",
                ],
            "crypto/dh/libcrypto-lib-dh_lib.o" =>
                [
                    "crypto/dh/dh_lib.c",
                ],
            "crypto/dh/libcrypto-lib-dh_meth.o" =>
                [
                    "crypto/dh/dh_meth.c",
                ],
            "crypto/dh/libcrypto-lib-dh_pmeth.o" =>
                [
                    "crypto/dh/dh_pmeth.c",
                ],
            "crypto/dh/libcrypto-lib-dh_prn.o" =>
                [
                    "crypto/dh/dh_prn.c",
                ],
            "crypto/dh/libcrypto-lib-dh_rfc5114.o" =>
                [
                    "crypto/dh/dh_rfc5114.c",
                ],
            "crypto/dh/libcrypto-lib-dh_rfc7919.o" =>
                [
                    "crypto/dh/dh_rfc7919.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_ameth.o" =>
                [
                    "crypto/dh/dh_ameth.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_asn1.o" =>
                [
                    "crypto/dh/dh_asn1.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_check.o" =>
                [
                    "crypto/dh/dh_check.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_depr.o" =>
                [
                    "crypto/dh/dh_depr.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_err.o" =>
                [
                    "crypto/dh/dh_err.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_gen.o" =>
                [
                    "crypto/dh/dh_gen.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_kdf.o" =>
                [
                    "crypto/dh/dh_kdf.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_key.o" =>
                [
                    "crypto/dh/dh_key.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_lib.o" =>
                [
                    "crypto/dh/dh_lib.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_meth.o" =>
                [
                    "crypto/dh/dh_meth.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_pmeth.o" =>
                [
                    "crypto/dh/dh_pmeth.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_prn.o" =>
                [
                    "crypto/dh/dh_prn.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_rfc5114.o" =>
                [
                    "crypto/dh/dh_rfc5114.c",
                ],
            "crypto/dh/libcrypto-shlib-dh_rfc7919.o" =>
                [
                    "crypto/dh/dh_rfc7919.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_ameth.o" =>
                [
                    "crypto/dsa/dsa_ameth.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_asn1.o" =>
                [
                    "crypto/dsa/dsa_asn1.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_depr.o" =>
                [
                    "crypto/dsa/dsa_depr.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_err.o" =>
                [
                    "crypto/dsa/dsa_err.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_gen.o" =>
                [
                    "crypto/dsa/dsa_gen.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_key.o" =>
                [
                    "crypto/dsa/dsa_key.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_lib.o" =>
                [
                    "crypto/dsa/dsa_lib.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_meth.o" =>
                [
                    "crypto/dsa/dsa_meth.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_ossl.o" =>
                [
                    "crypto/dsa/dsa_ossl.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_pmeth.o" =>
                [
                    "crypto/dsa/dsa_pmeth.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_prn.o" =>
                [
                    "crypto/dsa/dsa_prn.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_sign.o" =>
                [
                    "crypto/dsa/dsa_sign.c",
                ],
            "crypto/dsa/libcrypto-lib-dsa_vrf.o" =>
                [
                    "crypto/dsa/dsa_vrf.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_ameth.o" =>
                [
                    "crypto/dsa/dsa_ameth.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_asn1.o" =>
                [
                    "crypto/dsa/dsa_asn1.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_depr.o" =>
                [
                    "crypto/dsa/dsa_depr.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_err.o" =>
                [
                    "crypto/dsa/dsa_err.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_gen.o" =>
                [
                    "crypto/dsa/dsa_gen.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_key.o" =>
                [
                    "crypto/dsa/dsa_key.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_lib.o" =>
                [
                    "crypto/dsa/dsa_lib.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_meth.o" =>
                [
                    "crypto/dsa/dsa_meth.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_ossl.o" =>
                [
                    "crypto/dsa/dsa_ossl.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_pmeth.o" =>
                [
                    "crypto/dsa/dsa_pmeth.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_prn.o" =>
                [
                    "crypto/dsa/dsa_prn.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_sign.o" =>
                [
                    "crypto/dsa/dsa_sign.c",
                ],
            "crypto/dsa/libcrypto-shlib-dsa_vrf.o" =>
                [
                    "crypto/dsa/dsa_vrf.c",
                ],
            "crypto/dso/libcrypto-lib-dso_dl.o" =>
                [
                    "crypto/dso/dso_dl.c",
                ],
            "crypto/dso/libcrypto-lib-dso_dlfcn.o" =>
                [
                    "crypto/dso/dso_dlfcn.c",
                ],
            "crypto/dso/libcrypto-lib-dso_err.o" =>
                [
                    "crypto/dso/dso_err.c",
                ],
            "crypto/dso/libcrypto-lib-dso_lib.o" =>
                [
                    "crypto/dso/dso_lib.c",
                ],
            "crypto/dso/libcrypto-lib-dso_openssl.o" =>
                [
                    "crypto/dso/dso_openssl.c",
                ],
            "crypto/dso/libcrypto-lib-dso_vms.o" =>
                [
                    "crypto/dso/dso_vms.c",
                ],
            "crypto/dso/libcrypto-lib-dso_win32.o" =>
                [
                    "crypto/dso/dso_win32.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_dl.o" =>
                [
                    "crypto/dso/dso_dl.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_dlfcn.o" =>
                [
                    "crypto/dso/dso_dlfcn.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_err.o" =>
                [
                    "crypto/dso/dso_err.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_lib.o" =>
                [
                    "crypto/dso/dso_lib.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_openssl.o" =>
                [
                    "crypto/dso/dso_openssl.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_vms.o" =>
                [
                    "crypto/dso/dso_vms.c",
                ],
            "crypto/dso/libcrypto-shlib-dso_win32.o" =>
                [
                    "crypto/dso/dso_win32.c",
                ],
            "crypto/ec/curve448/arch_32/libcrypto-lib-f_impl.o" =>
                [
                    "crypto/ec/curve448/arch_32/f_impl.c",
                ],
            "crypto/ec/curve448/arch_32/libcrypto-shlib-f_impl.o" =>
                [
                    "crypto/ec/curve448/arch_32/f_impl.c",
                ],
            "crypto/ec/curve448/libcrypto-lib-curve448.o" =>
                [
                    "crypto/ec/curve448/curve448.c",
                ],
            "crypto/ec/curve448/libcrypto-lib-curve448_tables.o" =>
                [
                    "crypto/ec/curve448/curve448_tables.c",
                ],
            "crypto/ec/curve448/libcrypto-lib-eddsa.o" =>
                [
                    "crypto/ec/curve448/eddsa.c",
                ],
            "crypto/ec/curve448/libcrypto-lib-f_generic.o" =>
                [
                    "crypto/ec/curve448/f_generic.c",
                ],
            "crypto/ec/curve448/libcrypto-lib-scalar.o" =>
                [
                    "crypto/ec/curve448/scalar.c",
                ],
            "crypto/ec/curve448/libcrypto-shlib-curve448.o" =>
                [
                    "crypto/ec/curve448/curve448.c",
                ],
            "crypto/ec/curve448/libcrypto-shlib-curve448_tables.o" =>
                [
                    "crypto/ec/curve448/curve448_tables.c",
                ],
            "crypto/ec/curve448/libcrypto-shlib-eddsa.o" =>
                [
                    "crypto/ec/curve448/eddsa.c",
                ],
            "crypto/ec/curve448/libcrypto-shlib-f_generic.o" =>
                [
                    "crypto/ec/curve448/f_generic.c",
                ],
            "crypto/ec/curve448/libcrypto-shlib-scalar.o" =>
                [
                    "crypto/ec/curve448/scalar.c",
                ],
            "crypto/ec/libcrypto-lib-curve25519.o" =>
                [
                    "crypto/ec/curve25519.c",
                ],
            "crypto/ec/libcrypto-lib-ec2_oct.o" =>
                [
                    "crypto/ec/ec2_oct.c",
                ],
            "crypto/ec/libcrypto-lib-ec2_smpl.o" =>
                [
                    "crypto/ec/ec2_smpl.c",
                ],
            "crypto/ec/libcrypto-lib-ec_ameth.o" =>
                [
                    "crypto/ec/ec_ameth.c",
                ],
            "crypto/ec/libcrypto-lib-ec_asn1.o" =>
                [
                    "crypto/ec/ec_asn1.c",
                ],
            "crypto/ec/libcrypto-lib-ec_check.o" =>
                [
                    "crypto/ec/ec_check.c",
                ],
            "crypto/ec/libcrypto-lib-ec_curve.o" =>
                [
                    "crypto/ec/ec_curve.c",
                ],
            "crypto/ec/libcrypto-lib-ec_cvt.o" =>
                [
                    "crypto/ec/ec_cvt.c",
                ],
            "crypto/ec/libcrypto-lib-ec_err.o" =>
                [
                    "crypto/ec/ec_err.c",
                ],
            "crypto/ec/libcrypto-lib-ec_key.o" =>
                [
                    "crypto/ec/ec_key.c",
                ],
            "crypto/ec/libcrypto-lib-ec_kmeth.o" =>
                [
                    "crypto/ec/ec_kmeth.c",
                ],
            "crypto/ec/libcrypto-lib-ec_lib.o" =>
                [
                    "crypto/ec/ec_lib.c",
                ],
            "crypto/ec/libcrypto-lib-ec_mult.o" =>
                [
                    "crypto/ec/ec_mult.c",
                ],
            "crypto/ec/libcrypto-lib-ec_oct.o" =>
                [
                    "crypto/ec/ec_oct.c",
                ],
            "crypto/ec/libcrypto-lib-ec_pmeth.o" =>
                [
                    "crypto/ec/ec_pmeth.c",
                ],
            "crypto/ec/libcrypto-lib-ec_print.o" =>
                [
                    "crypto/ec/ec_print.c",
                ],
            "crypto/ec/libcrypto-lib-ecdh_kdf.o" =>
                [
                    "crypto/ec/ecdh_kdf.c",
                ],
            "crypto/ec/libcrypto-lib-ecdh_ossl.o" =>
                [
                    "crypto/ec/ecdh_ossl.c",
                ],
            "crypto/ec/libcrypto-lib-ecdsa_ossl.o" =>
                [
                    "crypto/ec/ecdsa_ossl.c",
                ],
            "crypto/ec/libcrypto-lib-ecdsa_sign.o" =>
                [
                    "crypto/ec/ecdsa_sign.c",
                ],
            "crypto/ec/libcrypto-lib-ecdsa_vrf.o" =>
                [
                    "crypto/ec/ecdsa_vrf.c",
                ],
            "crypto/ec/libcrypto-lib-eck_prn.o" =>
                [
                    "crypto/ec/eck_prn.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_mont.o" =>
                [
                    "crypto/ec/ecp_mont.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_nist.o" =>
                [
                    "crypto/ec/ecp_nist.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_nistp224.o" =>
                [
                    "crypto/ec/ecp_nistp224.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_nistp256.o" =>
                [
                    "crypto/ec/ecp_nistp256.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_nistp521.o" =>
                [
                    "crypto/ec/ecp_nistp521.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_nistputil.o" =>
                [
                    "crypto/ec/ecp_nistputil.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_nistz256-x86_64.o" =>
                [
                    "crypto/ec/ecp_nistz256-x86_64.s",
                ],
            "crypto/ec/libcrypto-lib-ecp_nistz256.o" =>
                [
                    "crypto/ec/ecp_nistz256.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_oct.o" =>
                [
                    "crypto/ec/ecp_oct.c",
                ],
            "crypto/ec/libcrypto-lib-ecp_smpl.o" =>
                [
                    "crypto/ec/ecp_smpl.c",
                ],
            "crypto/ec/libcrypto-lib-ecx_meth.o" =>
                [
                    "crypto/ec/ecx_meth.c",
                ],
            "crypto/ec/libcrypto-lib-x25519-x86_64.o" =>
                [
                    "crypto/ec/x25519-x86_64.s",
                ],
            "crypto/ec/libcrypto-shlib-curve25519.o" =>
                [
                    "crypto/ec/curve25519.c",
                ],
            "crypto/ec/libcrypto-shlib-ec2_oct.o" =>
                [
                    "crypto/ec/ec2_oct.c",
                ],
            "crypto/ec/libcrypto-shlib-ec2_smpl.o" =>
                [
                    "crypto/ec/ec2_smpl.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_ameth.o" =>
                [
                    "crypto/ec/ec_ameth.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_asn1.o" =>
                [
                    "crypto/ec/ec_asn1.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_check.o" =>
                [
                    "crypto/ec/ec_check.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_curve.o" =>
                [
                    "crypto/ec/ec_curve.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_cvt.o" =>
                [
                    "crypto/ec/ec_cvt.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_err.o" =>
                [
                    "crypto/ec/ec_err.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_key.o" =>
                [
                    "crypto/ec/ec_key.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_kmeth.o" =>
                [
                    "crypto/ec/ec_kmeth.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_lib.o" =>
                [
                    "crypto/ec/ec_lib.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_mult.o" =>
                [
                    "crypto/ec/ec_mult.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_oct.o" =>
                [
                    "crypto/ec/ec_oct.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_pmeth.o" =>
                [
                    "crypto/ec/ec_pmeth.c",
                ],
            "crypto/ec/libcrypto-shlib-ec_print.o" =>
                [
                    "crypto/ec/ec_print.c",
                ],
            "crypto/ec/libcrypto-shlib-ecdh_kdf.o" =>
                [
                    "crypto/ec/ecdh_kdf.c",
                ],
            "crypto/ec/libcrypto-shlib-ecdh_ossl.o" =>
                [
                    "crypto/ec/ecdh_ossl.c",
                ],
            "crypto/ec/libcrypto-shlib-ecdsa_ossl.o" =>
                [
                    "crypto/ec/ecdsa_ossl.c",
                ],
            "crypto/ec/libcrypto-shlib-ecdsa_sign.o" =>
                [
                    "crypto/ec/ecdsa_sign.c",
                ],
            "crypto/ec/libcrypto-shlib-ecdsa_vrf.o" =>
                [
                    "crypto/ec/ecdsa_vrf.c",
                ],
            "crypto/ec/libcrypto-shlib-eck_prn.o" =>
                [
                    "crypto/ec/eck_prn.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_mont.o" =>
                [
                    "crypto/ec/ecp_mont.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nist.o" =>
                [
                    "crypto/ec/ecp_nist.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nistp224.o" =>
                [
                    "crypto/ec/ecp_nistp224.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nistp256.o" =>
                [
                    "crypto/ec/ecp_nistp256.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nistp521.o" =>
                [
                    "crypto/ec/ecp_nistp521.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nistputil.o" =>
                [
                    "crypto/ec/ecp_nistputil.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nistz256-x86_64.o" =>
                [
                    "crypto/ec/ecp_nistz256-x86_64.s",
                ],
            "crypto/ec/libcrypto-shlib-ecp_nistz256.o" =>
                [
                    "crypto/ec/ecp_nistz256.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_oct.o" =>
                [
                    "crypto/ec/ecp_oct.c",
                ],
            "crypto/ec/libcrypto-shlib-ecp_smpl.o" =>
                [
                    "crypto/ec/ecp_smpl.c",
                ],
            "crypto/ec/libcrypto-shlib-ecx_meth.o" =>
                [
                    "crypto/ec/ecx_meth.c",
                ],
            "crypto/ec/libcrypto-shlib-x25519-x86_64.o" =>
                [
                    "crypto/ec/x25519-x86_64.s",
                ],
            "crypto/engine/libcrypto-lib-eng_all.o" =>
                [
                    "crypto/engine/eng_all.c",
                ],
            "crypto/engine/libcrypto-lib-eng_cnf.o" =>
                [
                    "crypto/engine/eng_cnf.c",
                ],
            "crypto/engine/libcrypto-lib-eng_ctrl.o" =>
                [
                    "crypto/engine/eng_ctrl.c",
                ],
            "crypto/engine/libcrypto-lib-eng_dyn.o" =>
                [
                    "crypto/engine/eng_dyn.c",
                ],
            "crypto/engine/libcrypto-lib-eng_err.o" =>
                [
                    "crypto/engine/eng_err.c",
                ],
            "crypto/engine/libcrypto-lib-eng_fat.o" =>
                [
                    "crypto/engine/eng_fat.c",
                ],
            "crypto/engine/libcrypto-lib-eng_init.o" =>
                [
                    "crypto/engine/eng_init.c",
                ],
            "crypto/engine/libcrypto-lib-eng_lib.o" =>
                [
                    "crypto/engine/eng_lib.c",
                ],
            "crypto/engine/libcrypto-lib-eng_list.o" =>
                [
                    "crypto/engine/eng_list.c",
                ],
            "crypto/engine/libcrypto-lib-eng_openssl.o" =>
                [
                    "crypto/engine/eng_openssl.c",
                ],
            "crypto/engine/libcrypto-lib-eng_pkey.o" =>
                [
                    "crypto/engine/eng_pkey.c",
                ],
            "crypto/engine/libcrypto-lib-eng_rdrand.o" =>
                [
                    "crypto/engine/eng_rdrand.c",
                ],
            "crypto/engine/libcrypto-lib-eng_table.o" =>
                [
                    "crypto/engine/eng_table.c",
                ],
            "crypto/engine/libcrypto-lib-tb_asnmth.o" =>
                [
                    "crypto/engine/tb_asnmth.c",
                ],
            "crypto/engine/libcrypto-lib-tb_cipher.o" =>
                [
                    "crypto/engine/tb_cipher.c",
                ],
            "crypto/engine/libcrypto-lib-tb_dh.o" =>
                [
                    "crypto/engine/tb_dh.c",
                ],
            "crypto/engine/libcrypto-lib-tb_digest.o" =>
                [
                    "crypto/engine/tb_digest.c",
                ],
            "crypto/engine/libcrypto-lib-tb_dsa.o" =>
                [
                    "crypto/engine/tb_dsa.c",
                ],
            "crypto/engine/libcrypto-lib-tb_eckey.o" =>
                [
                    "crypto/engine/tb_eckey.c",
                ],
            "crypto/engine/libcrypto-lib-tb_pkmeth.o" =>
                [
                    "crypto/engine/tb_pkmeth.c",
                ],
            "crypto/engine/libcrypto-lib-tb_rand.o" =>
                [
                    "crypto/engine/tb_rand.c",
                ],
            "crypto/engine/libcrypto-lib-tb_rsa.o" =>
                [
                    "crypto/engine/tb_rsa.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_all.o" =>
                [
                    "crypto/engine/eng_all.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_cnf.o" =>
                [
                    "crypto/engine/eng_cnf.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_ctrl.o" =>
                [
                    "crypto/engine/eng_ctrl.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_dyn.o" =>
                [
                    "crypto/engine/eng_dyn.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_err.o" =>
                [
                    "crypto/engine/eng_err.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_fat.o" =>
                [
                    "crypto/engine/eng_fat.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_init.o" =>
                [
                    "crypto/engine/eng_init.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_lib.o" =>
                [
                    "crypto/engine/eng_lib.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_list.o" =>
                [
                    "crypto/engine/eng_list.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_openssl.o" =>
                [
                    "crypto/engine/eng_openssl.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_pkey.o" =>
                [
                    "crypto/engine/eng_pkey.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_rdrand.o" =>
                [
                    "crypto/engine/eng_rdrand.c",
                ],
            "crypto/engine/libcrypto-shlib-eng_table.o" =>
                [
                    "crypto/engine/eng_table.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_asnmth.o" =>
                [
                    "crypto/engine/tb_asnmth.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_cipher.o" =>
                [
                    "crypto/engine/tb_cipher.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_dh.o" =>
                [
                    "crypto/engine/tb_dh.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_digest.o" =>
                [
                    "crypto/engine/tb_digest.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_dsa.o" =>
                [
                    "crypto/engine/tb_dsa.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_eckey.o" =>
                [
                    "crypto/engine/tb_eckey.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_pkmeth.o" =>
                [
                    "crypto/engine/tb_pkmeth.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_rand.o" =>
                [
                    "crypto/engine/tb_rand.c",
                ],
            "crypto/engine/libcrypto-shlib-tb_rsa.o" =>
                [
                    "crypto/engine/tb_rsa.c",
                ],
            "crypto/err/libcrypto-lib-err.o" =>
                [
                    "crypto/err/err.c",
                ],
            "crypto/err/libcrypto-lib-err_all.o" =>
                [
                    "crypto/err/err_all.c",
                ],
            "crypto/err/libcrypto-lib-err_prn.o" =>
                [
                    "crypto/err/err_prn.c",
                ],
            "crypto/err/libcrypto-shlib-err.o" =>
                [
                    "crypto/err/err.c",
                ],
            "crypto/err/libcrypto-shlib-err_all.o" =>
                [
                    "crypto/err/err_all.c",
                ],
            "crypto/err/libcrypto-shlib-err_prn.o" =>
                [
                    "crypto/err/err_prn.c",
                ],
            "crypto/ess/libcrypto-lib-ess_asn1.o" =>
                [
                    "crypto/ess/ess_asn1.c",
                ],
            "crypto/ess/libcrypto-lib-ess_err.o" =>
                [
                    "crypto/ess/ess_err.c",
                ],
            "crypto/ess/libcrypto-lib-ess_lib.o" =>
                [
                    "crypto/ess/ess_lib.c",
                ],
            "crypto/ess/libcrypto-shlib-ess_asn1.o" =>
                [
                    "crypto/ess/ess_asn1.c",
                ],
            "crypto/ess/libcrypto-shlib-ess_err.o" =>
                [
                    "crypto/ess/ess_err.c",
                ],
            "crypto/ess/libcrypto-shlib-ess_lib.o" =>
                [
                    "crypto/ess/ess_lib.c",
                ],
            "crypto/evp/libcrypto-lib-bio_b64.o" =>
                [
                    "crypto/evp/bio_b64.c",
                ],
            "crypto/evp/libcrypto-lib-bio_enc.o" =>
                [
                    "crypto/evp/bio_enc.c",
                ],
            "crypto/evp/libcrypto-lib-bio_md.o" =>
                [
                    "crypto/evp/bio_md.c",
                ],
            "crypto/evp/libcrypto-lib-bio_ok.o" =>
                [
                    "crypto/evp/bio_ok.c",
                ],
            "crypto/evp/libcrypto-lib-c_allc.o" =>
                [
                    "crypto/evp/c_allc.c",
                ],
            "crypto/evp/libcrypto-lib-c_alld.o" =>
                [
                    "crypto/evp/c_alld.c",
                ],
            "crypto/evp/libcrypto-lib-c_allm.o" =>
                [
                    "crypto/evp/c_allm.c",
                ],
            "crypto/evp/libcrypto-lib-cmeth_lib.o" =>
                [
                    "crypto/evp/cmeth_lib.c",
                ],
            "crypto/evp/libcrypto-lib-digest.o" =>
                [
                    "crypto/evp/digest.c",
                ],
            "crypto/evp/libcrypto-lib-e_aes.o" =>
                [
                    "crypto/evp/e_aes.c",
                ],
            "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha1.o" =>
                [
                    "crypto/evp/e_aes_cbc_hmac_sha1.c",
                ],
            "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha256.o" =>
                [
                    "crypto/evp/e_aes_cbc_hmac_sha256.c",
                ],
            "crypto/evp/libcrypto-lib-e_aria.o" =>
                [
                    "crypto/evp/e_aria.c",
                ],
            "crypto/evp/libcrypto-lib-e_bf.o" =>
                [
                    "crypto/evp/e_bf.c",
                ],
            "crypto/evp/libcrypto-lib-e_camellia.o" =>
                [
                    "crypto/evp/e_camellia.c",
                ],
            "crypto/evp/libcrypto-lib-e_cast.o" =>
                [
                    "crypto/evp/e_cast.c",
                ],
            "crypto/evp/libcrypto-lib-e_chacha20_poly1305.o" =>
                [
                    "crypto/evp/e_chacha20_poly1305.c",
                ],
            "crypto/evp/libcrypto-lib-e_des.o" =>
                [
                    "crypto/evp/e_des.c",
                ],
            "crypto/evp/libcrypto-lib-e_des3.o" =>
                [
                    "crypto/evp/e_des3.c",
                ],
            "crypto/evp/libcrypto-lib-e_idea.o" =>
                [
                    "crypto/evp/e_idea.c",
                ],
            "crypto/evp/libcrypto-lib-e_null.o" =>
                [
                    "crypto/evp/e_null.c",
                ],
            "crypto/evp/libcrypto-lib-e_old.o" =>
                [
                    "crypto/evp/e_old.c",
                ],
            "crypto/evp/libcrypto-lib-e_rc2.o" =>
                [
                    "crypto/evp/e_rc2.c",
                ],
            "crypto/evp/libcrypto-lib-e_rc4.o" =>
                [
                    "crypto/evp/e_rc4.c",
                ],
            "crypto/evp/libcrypto-lib-e_rc4_hmac_md5.o" =>
                [
                    "crypto/evp/e_rc4_hmac_md5.c",
                ],
            "crypto/evp/libcrypto-lib-e_rc5.o" =>
                [
                    "crypto/evp/e_rc5.c",
                ],
            "crypto/evp/libcrypto-lib-e_seed.o" =>
                [
                    "crypto/evp/e_seed.c",
                ],
            "crypto/evp/libcrypto-lib-e_sm4.o" =>
                [
                    "crypto/evp/e_sm4.c",
                ],
            "crypto/evp/libcrypto-lib-e_xcbc_d.o" =>
                [
                    "crypto/evp/e_xcbc_d.c",
                ],
            "crypto/evp/libcrypto-lib-encode.o" =>
                [
                    "crypto/evp/encode.c",
                ],
            "crypto/evp/libcrypto-lib-evp_cnf.o" =>
                [
                    "crypto/evp/evp_cnf.c",
                ],
            "crypto/evp/libcrypto-lib-evp_enc.o" =>
                [
                    "crypto/evp/evp_enc.c",
                ],
            "crypto/evp/libcrypto-lib-evp_err.o" =>
                [
                    "crypto/evp/evp_err.c",
                ],
            "crypto/evp/libcrypto-lib-evp_fetch.o" =>
                [
                    "crypto/evp/evp_fetch.c",
                ],
            "crypto/evp/libcrypto-lib-evp_key.o" =>
                [
                    "crypto/evp/evp_key.c",
                ],
            "crypto/evp/libcrypto-lib-evp_lib.o" =>
                [
                    "crypto/evp/evp_lib.c",
                ],
            "crypto/evp/libcrypto-lib-evp_pbe.o" =>
                [
                    "crypto/evp/evp_pbe.c",
                ],
            "crypto/evp/libcrypto-lib-evp_pkey.o" =>
                [
                    "crypto/evp/evp_pkey.c",
                ],
            "crypto/evp/libcrypto-lib-kdf_lib.o" =>
                [
                    "crypto/evp/kdf_lib.c",
                ],
            "crypto/evp/libcrypto-lib-m_md2.o" =>
                [
                    "crypto/evp/m_md2.c",
                ],
            "crypto/evp/libcrypto-lib-m_md4.o" =>
                [
                    "crypto/evp/m_md4.c",
                ],
            "crypto/evp/libcrypto-lib-m_md5.o" =>
                [
                    "crypto/evp/m_md5.c",
                ],
            "crypto/evp/libcrypto-lib-m_md5_sha1.o" =>
                [
                    "crypto/evp/m_md5_sha1.c",
                ],
            "crypto/evp/libcrypto-lib-m_mdc2.o" =>
                [
                    "crypto/evp/m_mdc2.c",
                ],
            "crypto/evp/libcrypto-lib-m_null.o" =>
                [
                    "crypto/evp/m_null.c",
                ],
            "crypto/evp/libcrypto-lib-m_ripemd.o" =>
                [
                    "crypto/evp/m_ripemd.c",
                ],
            "crypto/evp/libcrypto-lib-m_sha1.o" =>
                [
                    "crypto/evp/m_sha1.c",
                ],
            "crypto/evp/libcrypto-lib-m_sha3.o" =>
                [
                    "crypto/evp/m_sha3.c",
                ],
            "crypto/evp/libcrypto-lib-m_sigver.o" =>
                [
                    "crypto/evp/m_sigver.c",
                ],
            "crypto/evp/libcrypto-lib-m_wp.o" =>
                [
                    "crypto/evp/m_wp.c",
                ],
            "crypto/evp/libcrypto-lib-mac_lib.o" =>
                [
                    "crypto/evp/mac_lib.c",
                ],
            "crypto/evp/libcrypto-lib-names.o" =>
                [
                    "crypto/evp/names.c",
                ],
            "crypto/evp/libcrypto-lib-p5_crpt.o" =>
                [
                    "crypto/evp/p5_crpt.c",
                ],
            "crypto/evp/libcrypto-lib-p5_crpt2.o" =>
                [
                    "crypto/evp/p5_crpt2.c",
                ],
            "crypto/evp/libcrypto-lib-p_dec.o" =>
                [
                    "crypto/evp/p_dec.c",
                ],
            "crypto/evp/libcrypto-lib-p_enc.o" =>
                [
                    "crypto/evp/p_enc.c",
                ],
            "crypto/evp/libcrypto-lib-p_lib.o" =>
                [
                    "crypto/evp/p_lib.c",
                ],
            "crypto/evp/libcrypto-lib-p_open.o" =>
                [
                    "crypto/evp/p_open.c",
                ],
            "crypto/evp/libcrypto-lib-p_seal.o" =>
                [
                    "crypto/evp/p_seal.c",
                ],
            "crypto/evp/libcrypto-lib-p_sign.o" =>
                [
                    "crypto/evp/p_sign.c",
                ],
            "crypto/evp/libcrypto-lib-p_verify.o" =>
                [
                    "crypto/evp/p_verify.c",
                ],
            "crypto/evp/libcrypto-lib-pbe_scrypt.o" =>
                [
                    "crypto/evp/pbe_scrypt.c",
                ],
            "crypto/evp/libcrypto-lib-pkey_kdf.o" =>
                [
                    "crypto/evp/pkey_kdf.c",
                ],
            "crypto/evp/libcrypto-lib-pkey_mac.o" =>
                [
                    "crypto/evp/pkey_mac.c",
                ],
            "crypto/evp/libcrypto-lib-pmeth_fn.o" =>
                [
                    "crypto/evp/pmeth_fn.c",
                ],
            "crypto/evp/libcrypto-lib-pmeth_gn.o" =>
                [
                    "crypto/evp/pmeth_gn.c",
                ],
            "crypto/evp/libcrypto-lib-pmeth_lib.o" =>
                [
                    "crypto/evp/pmeth_lib.c",
                ],
            "crypto/evp/libcrypto-shlib-bio_b64.o" =>
                [
                    "crypto/evp/bio_b64.c",
                ],
            "crypto/evp/libcrypto-shlib-bio_enc.o" =>
                [
                    "crypto/evp/bio_enc.c",
                ],
            "crypto/evp/libcrypto-shlib-bio_md.o" =>
                [
                    "crypto/evp/bio_md.c",
                ],
            "crypto/evp/libcrypto-shlib-bio_ok.o" =>
                [
                    "crypto/evp/bio_ok.c",
                ],
            "crypto/evp/libcrypto-shlib-c_allc.o" =>
                [
                    "crypto/evp/c_allc.c",
                ],
            "crypto/evp/libcrypto-shlib-c_alld.o" =>
                [
                    "crypto/evp/c_alld.c",
                ],
            "crypto/evp/libcrypto-shlib-c_allm.o" =>
                [
                    "crypto/evp/c_allm.c",
                ],
            "crypto/evp/libcrypto-shlib-cmeth_lib.o" =>
                [
                    "crypto/evp/cmeth_lib.c",
                ],
            "crypto/evp/libcrypto-shlib-digest.o" =>
                [
                    "crypto/evp/digest.c",
                ],
            "crypto/evp/libcrypto-shlib-e_aes.o" =>
                [
                    "crypto/evp/e_aes.c",
                ],
            "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha1.o" =>
                [
                    "crypto/evp/e_aes_cbc_hmac_sha1.c",
                ],
            "crypto/evp/libcrypto-shlib-e_aes_cbc_hmac_sha256.o" =>
                [
                    "crypto/evp/e_aes_cbc_hmac_sha256.c",
                ],
            "crypto/evp/libcrypto-shlib-e_aria.o" =>
                [
                    "crypto/evp/e_aria.c",
                ],
            "crypto/evp/libcrypto-shlib-e_bf.o" =>
                [
                    "crypto/evp/e_bf.c",
                ],
            "crypto/evp/libcrypto-shlib-e_camellia.o" =>
                [
                    "crypto/evp/e_camellia.c",
                ],
            "crypto/evp/libcrypto-shlib-e_cast.o" =>
                [
                    "crypto/evp/e_cast.c",
                ],
            "crypto/evp/libcrypto-shlib-e_chacha20_poly1305.o" =>
                [
                    "crypto/evp/e_chacha20_poly1305.c",
                ],
            "crypto/evp/libcrypto-shlib-e_des.o" =>
                [
                    "crypto/evp/e_des.c",
                ],
            "crypto/evp/libcrypto-shlib-e_des3.o" =>
                [
                    "crypto/evp/e_des3.c",
                ],
            "crypto/evp/libcrypto-shlib-e_idea.o" =>
                [
                    "crypto/evp/e_idea.c",
                ],
            "crypto/evp/libcrypto-shlib-e_null.o" =>
                [
                    "crypto/evp/e_null.c",
                ],
            "crypto/evp/libcrypto-shlib-e_old.o" =>
                [
                    "crypto/evp/e_old.c",
                ],
            "crypto/evp/libcrypto-shlib-e_rc2.o" =>
                [
                    "crypto/evp/e_rc2.c",
                ],
            "crypto/evp/libcrypto-shlib-e_rc4.o" =>
                [
                    "crypto/evp/e_rc4.c",
                ],
            "crypto/evp/libcrypto-shlib-e_rc4_hmac_md5.o" =>
                [
                    "crypto/evp/e_rc4_hmac_md5.c",
                ],
            "crypto/evp/libcrypto-shlib-e_rc5.o" =>
                [
                    "crypto/evp/e_rc5.c",
                ],
            "crypto/evp/libcrypto-shlib-e_seed.o" =>
                [
                    "crypto/evp/e_seed.c",
                ],
            "crypto/evp/libcrypto-shlib-e_sm4.o" =>
                [
                    "crypto/evp/e_sm4.c",
                ],
            "crypto/evp/libcrypto-shlib-e_xcbc_d.o" =>
                [
                    "crypto/evp/e_xcbc_d.c",
                ],
            "crypto/evp/libcrypto-shlib-encode.o" =>
                [
                    "crypto/evp/encode.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_cnf.o" =>
                [
                    "crypto/evp/evp_cnf.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_enc.o" =>
                [
                    "crypto/evp/evp_enc.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_err.o" =>
                [
                    "crypto/evp/evp_err.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_fetch.o" =>
                [
                    "crypto/evp/evp_fetch.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_key.o" =>
                [
                    "crypto/evp/evp_key.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_lib.o" =>
                [
                    "crypto/evp/evp_lib.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_pbe.o" =>
                [
                    "crypto/evp/evp_pbe.c",
                ],
            "crypto/evp/libcrypto-shlib-evp_pkey.o" =>
                [
                    "crypto/evp/evp_pkey.c",
                ],
            "crypto/evp/libcrypto-shlib-kdf_lib.o" =>
                [
                    "crypto/evp/kdf_lib.c",
                ],
            "crypto/evp/libcrypto-shlib-m_md2.o" =>
                [
                    "crypto/evp/m_md2.c",
                ],
            "crypto/evp/libcrypto-shlib-m_md4.o" =>
                [
                    "crypto/evp/m_md4.c",
                ],
            "crypto/evp/libcrypto-shlib-m_md5.o" =>
                [
                    "crypto/evp/m_md5.c",
                ],
            "crypto/evp/libcrypto-shlib-m_md5_sha1.o" =>
                [
                    "crypto/evp/m_md5_sha1.c",
                ],
            "crypto/evp/libcrypto-shlib-m_mdc2.o" =>
                [
                    "crypto/evp/m_mdc2.c",
                ],
            "crypto/evp/libcrypto-shlib-m_null.o" =>
                [
                    "crypto/evp/m_null.c",
                ],
            "crypto/evp/libcrypto-shlib-m_ripemd.o" =>
                [
                    "crypto/evp/m_ripemd.c",
                ],
            "crypto/evp/libcrypto-shlib-m_sha1.o" =>
                [
                    "crypto/evp/m_sha1.c",
                ],
            "crypto/evp/libcrypto-shlib-m_sha3.o" =>
                [
                    "crypto/evp/m_sha3.c",
                ],
            "crypto/evp/libcrypto-shlib-m_sigver.o" =>
                [
                    "crypto/evp/m_sigver.c",
                ],
            "crypto/evp/libcrypto-shlib-m_wp.o" =>
                [
                    "crypto/evp/m_wp.c",
                ],
            "crypto/evp/libcrypto-shlib-mac_lib.o" =>
                [
                    "crypto/evp/mac_lib.c",
                ],
            "crypto/evp/libcrypto-shlib-names.o" =>
                [
                    "crypto/evp/names.c",
                ],
            "crypto/evp/libcrypto-shlib-p5_crpt.o" =>
                [
                    "crypto/evp/p5_crpt.c",
                ],
            "crypto/evp/libcrypto-shlib-p5_crpt2.o" =>
                [
                    "crypto/evp/p5_crpt2.c",
                ],
            "crypto/evp/libcrypto-shlib-p_dec.o" =>
                [
                    "crypto/evp/p_dec.c",
                ],
            "crypto/evp/libcrypto-shlib-p_enc.o" =>
                [
                    "crypto/evp/p_enc.c",
                ],
            "crypto/evp/libcrypto-shlib-p_lib.o" =>
                [
                    "crypto/evp/p_lib.c",
                ],
            "crypto/evp/libcrypto-shlib-p_open.o" =>
                [
                    "crypto/evp/p_open.c",
                ],
            "crypto/evp/libcrypto-shlib-p_seal.o" =>
                [
                    "crypto/evp/p_seal.c",
                ],
            "crypto/evp/libcrypto-shlib-p_sign.o" =>
                [
                    "crypto/evp/p_sign.c",
                ],
            "crypto/evp/libcrypto-shlib-p_verify.o" =>
                [
                    "crypto/evp/p_verify.c",
                ],
            "crypto/evp/libcrypto-shlib-pbe_scrypt.o" =>
                [
                    "crypto/evp/pbe_scrypt.c",
                ],
            "crypto/evp/libcrypto-shlib-pkey_kdf.o" =>
                [
                    "crypto/evp/pkey_kdf.c",
                ],
            "crypto/evp/libcrypto-shlib-pkey_mac.o" =>
                [
                    "crypto/evp/pkey_mac.c",
                ],
            "crypto/evp/libcrypto-shlib-pmeth_fn.o" =>
                [
                    "crypto/evp/pmeth_fn.c",
                ],
            "crypto/evp/libcrypto-shlib-pmeth_gn.o" =>
                [
                    "crypto/evp/pmeth_gn.c",
                ],
            "crypto/evp/libcrypto-shlib-pmeth_lib.o" =>
                [
                    "crypto/evp/pmeth_lib.c",
                ],
            "crypto/fips-dso-cryptlib.o" =>
                [
                    "crypto/cryptlib.c",
                ],
            "crypto/fips-dso-mem.o" =>
                [
                    "crypto/mem.c",
                ],
            "crypto/fips-dso-mem_clr.o" =>
                [
                    "crypto/mem_clr.c",
                ],
            "crypto/fips-dso-params.o" =>
                [
                    "crypto/params.c",
                ],
            "crypto/gmac/libcrypto-lib-gmac.o" =>
                [
                    "crypto/gmac/gmac.c",
                ],
            "crypto/gmac/libcrypto-shlib-gmac.o" =>
                [
                    "crypto/gmac/gmac.c",
                ],
            "crypto/hmac/libcrypto-lib-hm_ameth.o" =>
                [
                    "crypto/hmac/hm_ameth.c",
                ],
            "crypto/hmac/libcrypto-lib-hm_meth.o" =>
                [
                    "crypto/hmac/hm_meth.c",
                ],
            "crypto/hmac/libcrypto-lib-hmac.o" =>
                [
                    "crypto/hmac/hmac.c",
                ],
            "crypto/hmac/libcrypto-shlib-hm_ameth.o" =>
                [
                    "crypto/hmac/hm_ameth.c",
                ],
            "crypto/hmac/libcrypto-shlib-hm_meth.o" =>
                [
                    "crypto/hmac/hm_meth.c",
                ],
            "crypto/hmac/libcrypto-shlib-hmac.o" =>
                [
                    "crypto/hmac/hmac.c",
                ],
            "crypto/idea/libcrypto-lib-i_cbc.o" =>
                [
                    "crypto/idea/i_cbc.c",
                ],
            "crypto/idea/libcrypto-lib-i_cfb64.o" =>
                [
                    "crypto/idea/i_cfb64.c",
                ],
            "crypto/idea/libcrypto-lib-i_ecb.o" =>
                [
                    "crypto/idea/i_ecb.c",
                ],
            "crypto/idea/libcrypto-lib-i_ofb64.o" =>
                [
                    "crypto/idea/i_ofb64.c",
                ],
            "crypto/idea/libcrypto-lib-i_skey.o" =>
                [
                    "crypto/idea/i_skey.c",
                ],
            "crypto/idea/libcrypto-shlib-i_cbc.o" =>
                [
                    "crypto/idea/i_cbc.c",
                ],
            "crypto/idea/libcrypto-shlib-i_cfb64.o" =>
                [
                    "crypto/idea/i_cfb64.c",
                ],
            "crypto/idea/libcrypto-shlib-i_ecb.o" =>
                [
                    "crypto/idea/i_ecb.c",
                ],
            "crypto/idea/libcrypto-shlib-i_ofb64.o" =>
                [
                    "crypto/idea/i_ofb64.c",
                ],
            "crypto/idea/libcrypto-shlib-i_skey.o" =>
                [
                    "crypto/idea/i_skey.c",
                ],
            "crypto/kdf/libcrypto-lib-hkdf.o" =>
                [
                    "crypto/kdf/hkdf.c",
                ],
            "crypto/kdf/libcrypto-lib-kdf_err.o" =>
                [
                    "crypto/kdf/kdf_err.c",
                ],
            "crypto/kdf/libcrypto-lib-kdf_util.o" =>
                [
                    "crypto/kdf/kdf_util.c",
                ],
            "crypto/kdf/libcrypto-lib-pbkdf2.o" =>
                [
                    "crypto/kdf/pbkdf2.c",
                ],
            "crypto/kdf/libcrypto-lib-scrypt.o" =>
                [
                    "crypto/kdf/scrypt.c",
                ],
            "crypto/kdf/libcrypto-lib-sshkdf.o" =>
                [
                    "crypto/kdf/sshkdf.c",
                ],
            "crypto/kdf/libcrypto-lib-sskdf.o" =>
                [
                    "crypto/kdf/sskdf.c",
                ],
            "crypto/kdf/libcrypto-lib-tls1_prf.o" =>
                [
                    "crypto/kdf/tls1_prf.c",
                ],
            "crypto/kdf/libcrypto-shlib-hkdf.o" =>
                [
                    "crypto/kdf/hkdf.c",
                ],
            "crypto/kdf/libcrypto-shlib-kdf_err.o" =>
                [
                    "crypto/kdf/kdf_err.c",
                ],
            "crypto/kdf/libcrypto-shlib-kdf_util.o" =>
                [
                    "crypto/kdf/kdf_util.c",
                ],
            "crypto/kdf/libcrypto-shlib-pbkdf2.o" =>
                [
                    "crypto/kdf/pbkdf2.c",
                ],
            "crypto/kdf/libcrypto-shlib-scrypt.o" =>
                [
                    "crypto/kdf/scrypt.c",
                ],
            "crypto/kdf/libcrypto-shlib-sshkdf.o" =>
                [
                    "crypto/kdf/sshkdf.c",
                ],
            "crypto/kdf/libcrypto-shlib-sskdf.o" =>
                [
                    "crypto/kdf/sskdf.c",
                ],
            "crypto/kdf/libcrypto-shlib-tls1_prf.o" =>
                [
                    "crypto/kdf/tls1_prf.c",
                ],
            "crypto/kmac/libcrypto-lib-kmac.o" =>
                [
                    "crypto/kmac/kmac.c",
                ],
            "crypto/kmac/libcrypto-shlib-kmac.o" =>
                [
                    "crypto/kmac/kmac.c",
                ],
            "crypto/lhash/libcrypto-lib-lh_stats.o" =>
                [
                    "crypto/lhash/lh_stats.c",
                ],
            "crypto/lhash/libcrypto-lib-lhash.o" =>
                [
                    "crypto/lhash/lhash.c",
                ],
            "crypto/lhash/libcrypto-shlib-lh_stats.o" =>
                [
                    "crypto/lhash/lh_stats.c",
                ],
            "crypto/lhash/libcrypto-shlib-lhash.o" =>
                [
                    "crypto/lhash/lhash.c",
                ],
            "crypto/libcrypto-lib-context.o" =>
                [
                    "crypto/context.c",
                ],
            "crypto/libcrypto-lib-core_fetch.o" =>
                [
                    "crypto/core_fetch.c",
                ],
            "crypto/libcrypto-lib-cpt_err.o" =>
                [
                    "crypto/cpt_err.c",
                ],
            "crypto/libcrypto-lib-cryptlib.o" =>
                [
                    "crypto/cryptlib.c",
                ],
            "crypto/libcrypto-lib-ctype.o" =>
                [
                    "crypto/ctype.c",
                ],
            "crypto/libcrypto-lib-cversion.o" =>
                [
                    "crypto/cversion.c",
                ],
            "crypto/libcrypto-lib-ebcdic.o" =>
                [
                    "crypto/ebcdic.c",
                ],
            "crypto/libcrypto-lib-ex_data.o" =>
                [
                    "crypto/ex_data.c",
                ],
            "crypto/libcrypto-lib-getenv.o" =>
                [
                    "crypto/getenv.c",
                ],
            "crypto/libcrypto-lib-init.o" =>
                [
                    "crypto/init.c",
                ],
            "crypto/libcrypto-lib-mem.o" =>
                [
                    "crypto/mem.c",
                ],
            "crypto/libcrypto-lib-mem_dbg.o" =>
                [
                    "crypto/mem_dbg.c",
                ],
            "crypto/libcrypto-lib-mem_sec.o" =>
                [
                    "crypto/mem_sec.c",
                ],
            "crypto/libcrypto-lib-o_dir.o" =>
                [
                    "crypto/o_dir.c",
                ],
            "crypto/libcrypto-lib-o_fips.o" =>
                [
                    "crypto/o_fips.c",
                ],
            "crypto/libcrypto-lib-o_fopen.o" =>
                [
                    "crypto/o_fopen.c",
                ],
            "crypto/libcrypto-lib-o_init.o" =>
                [
                    "crypto/o_init.c",
                ],
            "crypto/libcrypto-lib-o_str.o" =>
                [
                    "crypto/o_str.c",
                ],
            "crypto/libcrypto-lib-o_time.o" =>
                [
                    "crypto/o_time.c",
                ],
            "crypto/libcrypto-lib-params.o" =>
                [
                    "crypto/params.c",
                ],
            "crypto/libcrypto-lib-provider.o" =>
                [
                    "crypto/provider.c",
                ],
            "crypto/libcrypto-lib-provider_conf.o" =>
                [
                    "crypto/provider_conf.c",
                ],
            "crypto/libcrypto-lib-provider_core.o" =>
                [
                    "crypto/provider_core.c",
                ],
            "crypto/libcrypto-lib-provider_predefined.o" =>
                [
                    "crypto/provider_predefined.c",
                ],
            "crypto/libcrypto-lib-sparse_array.o" =>
                [
                    "crypto/sparse_array.c",
                ],
            "crypto/libcrypto-lib-threads_none.o" =>
                [
                    "crypto/threads_none.c",
                ],
            "crypto/libcrypto-lib-threads_pthread.o" =>
                [
                    "crypto/threads_pthread.c",
                ],
            "crypto/libcrypto-lib-threads_win.o" =>
                [
                    "crypto/threads_win.c",
                ],
            "crypto/libcrypto-lib-trace.o" =>
                [
                    "crypto/trace.c",
                ],
            "crypto/libcrypto-lib-uid.o" =>
                [
                    "crypto/uid.c",
                ],
            "crypto/libcrypto-lib-x86_64cpuid.o" =>
                [
                    "crypto/x86_64cpuid.s",
                ],
            "crypto/libcrypto-shlib-context.o" =>
                [
                    "crypto/context.c",
                ],
            "crypto/libcrypto-shlib-core_fetch.o" =>
                [
                    "crypto/core_fetch.c",
                ],
            "crypto/libcrypto-shlib-cpt_err.o" =>
                [
                    "crypto/cpt_err.c",
                ],
            "crypto/libcrypto-shlib-cryptlib.o" =>
                [
                    "crypto/cryptlib.c",
                ],
            "crypto/libcrypto-shlib-ctype.o" =>
                [
                    "crypto/ctype.c",
                ],
            "crypto/libcrypto-shlib-cversion.o" =>
                [
                    "crypto/cversion.c",
                ],
            "crypto/libcrypto-shlib-ebcdic.o" =>
                [
                    "crypto/ebcdic.c",
                ],
            "crypto/libcrypto-shlib-ex_data.o" =>
                [
                    "crypto/ex_data.c",
                ],
            "crypto/libcrypto-shlib-getenv.o" =>
                [
                    "crypto/getenv.c",
                ],
            "crypto/libcrypto-shlib-init.o" =>
                [
                    "crypto/init.c",
                ],
            "crypto/libcrypto-shlib-mem.o" =>
                [
                    "crypto/mem.c",
                ],
            "crypto/libcrypto-shlib-mem_dbg.o" =>
                [
                    "crypto/mem_dbg.c",
                ],
            "crypto/libcrypto-shlib-mem_sec.o" =>
                [
                    "crypto/mem_sec.c",
                ],
            "crypto/libcrypto-shlib-o_dir.o" =>
                [
                    "crypto/o_dir.c",
                ],
            "crypto/libcrypto-shlib-o_fips.o" =>
                [
                    "crypto/o_fips.c",
                ],
            "crypto/libcrypto-shlib-o_fopen.o" =>
                [
                    "crypto/o_fopen.c",
                ],
            "crypto/libcrypto-shlib-o_init.o" =>
                [
                    "crypto/o_init.c",
                ],
            "crypto/libcrypto-shlib-o_str.o" =>
                [
                    "crypto/o_str.c",
                ],
            "crypto/libcrypto-shlib-o_time.o" =>
                [
                    "crypto/o_time.c",
                ],
            "crypto/libcrypto-shlib-params.o" =>
                [
                    "crypto/params.c",
                ],
            "crypto/libcrypto-shlib-provider.o" =>
                [
                    "crypto/provider.c",
                ],
            "crypto/libcrypto-shlib-provider_conf.o" =>
                [
                    "crypto/provider_conf.c",
                ],
            "crypto/libcrypto-shlib-provider_core.o" =>
                [
                    "crypto/provider_core.c",
                ],
            "crypto/libcrypto-shlib-provider_predefined.o" =>
                [
                    "crypto/provider_predefined.c",
                ],
            "crypto/libcrypto-shlib-sparse_array.o" =>
                [
                    "crypto/sparse_array.c",
                ],
            "crypto/libcrypto-shlib-threads_none.o" =>
                [
                    "crypto/threads_none.c",
                ],
            "crypto/libcrypto-shlib-threads_pthread.o" =>
                [
                    "crypto/threads_pthread.c",
                ],
            "crypto/libcrypto-shlib-threads_win.o" =>
                [
                    "crypto/threads_win.c",
                ],
            "crypto/libcrypto-shlib-trace.o" =>
                [
                    "crypto/trace.c",
                ],
            "crypto/libcrypto-shlib-uid.o" =>
                [
                    "crypto/uid.c",
                ],
            "crypto/libcrypto-shlib-x86_64cpuid.o" =>
                [
                    "crypto/x86_64cpuid.s",
                ],
            "crypto/md4/libcrypto-lib-md4_dgst.o" =>
                [
                    "crypto/md4/md4_dgst.c",
                ],
            "crypto/md4/libcrypto-lib-md4_one.o" =>
                [
                    "crypto/md4/md4_one.c",
                ],
            "crypto/md4/libcrypto-shlib-md4_dgst.o" =>
                [
                    "crypto/md4/md4_dgst.c",
                ],
            "crypto/md4/libcrypto-shlib-md4_one.o" =>
                [
                    "crypto/md4/md4_one.c",
                ],
            "crypto/md5/libcrypto-lib-md5-x86_64.o" =>
                [
                    "crypto/md5/md5-x86_64.s",
                ],
            "crypto/md5/libcrypto-lib-md5_dgst.o" =>
                [
                    "crypto/md5/md5_dgst.c",
                ],
            "crypto/md5/libcrypto-lib-md5_one.o" =>
                [
                    "crypto/md5/md5_one.c",
                ],
            "crypto/md5/libcrypto-shlib-md5-x86_64.o" =>
                [
                    "crypto/md5/md5-x86_64.s",
                ],
            "crypto/md5/libcrypto-shlib-md5_dgst.o" =>
                [
                    "crypto/md5/md5_dgst.c",
                ],
            "crypto/md5/libcrypto-shlib-md5_one.o" =>
                [
                    "crypto/md5/md5_one.c",
                ],
            "crypto/mdc2/libcrypto-lib-mdc2_one.o" =>
                [
                    "crypto/mdc2/mdc2_one.c",
                ],
            "crypto/mdc2/libcrypto-lib-mdc2dgst.o" =>
                [
                    "crypto/mdc2/mdc2dgst.c",
                ],
            "crypto/mdc2/libcrypto-shlib-mdc2_one.o" =>
                [
                    "crypto/mdc2/mdc2_one.c",
                ],
            "crypto/mdc2/libcrypto-shlib-mdc2dgst.o" =>
                [
                    "crypto/mdc2/mdc2dgst.c",
                ],
            "crypto/modes/libcrypto-lib-aesni-gcm-x86_64.o" =>
                [
                    "crypto/modes/aesni-gcm-x86_64.s",
                ],
            "crypto/modes/libcrypto-lib-cbc128.o" =>
                [
                    "crypto/modes/cbc128.c",
                ],
            "crypto/modes/libcrypto-lib-ccm128.o" =>
                [
                    "crypto/modes/ccm128.c",
                ],
            "crypto/modes/libcrypto-lib-cfb128.o" =>
                [
                    "crypto/modes/cfb128.c",
                ],
            "crypto/modes/libcrypto-lib-ctr128.o" =>
                [
                    "crypto/modes/ctr128.c",
                ],
            "crypto/modes/libcrypto-lib-cts128.o" =>
                [
                    "crypto/modes/cts128.c",
                ],
            "crypto/modes/libcrypto-lib-gcm128.o" =>
                [
                    "crypto/modes/gcm128.c",
                ],
            "crypto/modes/libcrypto-lib-ghash-x86_64.o" =>
                [
                    "crypto/modes/ghash-x86_64.s",
                ],
            "crypto/modes/libcrypto-lib-ocb128.o" =>
                [
                    "crypto/modes/ocb128.c",
                ],
            "crypto/modes/libcrypto-lib-ofb128.o" =>
                [
                    "crypto/modes/ofb128.c",
                ],
            "crypto/modes/libcrypto-lib-siv128.o" =>
                [
                    "crypto/modes/siv128.c",
                ],
            "crypto/modes/libcrypto-lib-wrap128.o" =>
                [
                    "crypto/modes/wrap128.c",
                ],
            "crypto/modes/libcrypto-lib-xts128.o" =>
                [
                    "crypto/modes/xts128.c",
                ],
            "crypto/modes/libcrypto-shlib-aesni-gcm-x86_64.o" =>
                [
                    "crypto/modes/aesni-gcm-x86_64.s",
                ],
            "crypto/modes/libcrypto-shlib-cbc128.o" =>
                [
                    "crypto/modes/cbc128.c",
                ],
            "crypto/modes/libcrypto-shlib-ccm128.o" =>
                [
                    "crypto/modes/ccm128.c",
                ],
            "crypto/modes/libcrypto-shlib-cfb128.o" =>
                [
                    "crypto/modes/cfb128.c",
                ],
            "crypto/modes/libcrypto-shlib-ctr128.o" =>
                [
                    "crypto/modes/ctr128.c",
                ],
            "crypto/modes/libcrypto-shlib-cts128.o" =>
                [
                    "crypto/modes/cts128.c",
                ],
            "crypto/modes/libcrypto-shlib-gcm128.o" =>
                [
                    "crypto/modes/gcm128.c",
                ],
            "crypto/modes/libcrypto-shlib-ghash-x86_64.o" =>
                [
                    "crypto/modes/ghash-x86_64.s",
                ],
            "crypto/modes/libcrypto-shlib-ocb128.o" =>
                [
                    "crypto/modes/ocb128.c",
                ],
            "crypto/modes/libcrypto-shlib-ofb128.o" =>
                [
                    "crypto/modes/ofb128.c",
                ],
            "crypto/modes/libcrypto-shlib-siv128.o" =>
                [
                    "crypto/modes/siv128.c",
                ],
            "crypto/modes/libcrypto-shlib-wrap128.o" =>
                [
                    "crypto/modes/wrap128.c",
                ],
            "crypto/modes/libcrypto-shlib-xts128.o" =>
                [
                    "crypto/modes/xts128.c",
                ],
            "crypto/objects/libcrypto-lib-o_names.o" =>
                [
                    "crypto/objects/o_names.c",
                ],
            "crypto/objects/libcrypto-lib-obj_dat.o" =>
                [
                    "crypto/objects/obj_dat.c",
                ],
            "crypto/objects/libcrypto-lib-obj_err.o" =>
                [
                    "crypto/objects/obj_err.c",
                ],
            "crypto/objects/libcrypto-lib-obj_lib.o" =>
                [
                    "crypto/objects/obj_lib.c",
                ],
            "crypto/objects/libcrypto-lib-obj_xref.o" =>
                [
                    "crypto/objects/obj_xref.c",
                ],
            "crypto/objects/libcrypto-shlib-o_names.o" =>
                [
                    "crypto/objects/o_names.c",
                ],
            "crypto/objects/libcrypto-shlib-obj_dat.o" =>
                [
                    "crypto/objects/obj_dat.c",
                ],
            "crypto/objects/libcrypto-shlib-obj_err.o" =>
                [
                    "crypto/objects/obj_err.c",
                ],
            "crypto/objects/libcrypto-shlib-obj_lib.o" =>
                [
                    "crypto/objects/obj_lib.c",
                ],
            "crypto/objects/libcrypto-shlib-obj_xref.o" =>
                [
                    "crypto/objects/obj_xref.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_asn.o" =>
                [
                    "crypto/ocsp/ocsp_asn.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_cl.o" =>
                [
                    "crypto/ocsp/ocsp_cl.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_err.o" =>
                [
                    "crypto/ocsp/ocsp_err.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_ext.o" =>
                [
                    "crypto/ocsp/ocsp_ext.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_ht.o" =>
                [
                    "crypto/ocsp/ocsp_ht.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_lib.o" =>
                [
                    "crypto/ocsp/ocsp_lib.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_prn.o" =>
                [
                    "crypto/ocsp/ocsp_prn.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_srv.o" =>
                [
                    "crypto/ocsp/ocsp_srv.c",
                ],
            "crypto/ocsp/libcrypto-lib-ocsp_vfy.o" =>
                [
                    "crypto/ocsp/ocsp_vfy.c",
                ],
            "crypto/ocsp/libcrypto-lib-v3_ocsp.o" =>
                [
                    "crypto/ocsp/v3_ocsp.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_asn.o" =>
                [
                    "crypto/ocsp/ocsp_asn.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_cl.o" =>
                [
                    "crypto/ocsp/ocsp_cl.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_err.o" =>
                [
                    "crypto/ocsp/ocsp_err.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_ext.o" =>
                [
                    "crypto/ocsp/ocsp_ext.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_ht.o" =>
                [
                    "crypto/ocsp/ocsp_ht.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_lib.o" =>
                [
                    "crypto/ocsp/ocsp_lib.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_prn.o" =>
                [
                    "crypto/ocsp/ocsp_prn.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_srv.o" =>
                [
                    "crypto/ocsp/ocsp_srv.c",
                ],
            "crypto/ocsp/libcrypto-shlib-ocsp_vfy.o" =>
                [
                    "crypto/ocsp/ocsp_vfy.c",
                ],
            "crypto/ocsp/libcrypto-shlib-v3_ocsp.o" =>
                [
                    "crypto/ocsp/v3_ocsp.c",
                ],
            "crypto/pem/libcrypto-lib-pem_all.o" =>
                [
                    "crypto/pem/pem_all.c",
                ],
            "crypto/pem/libcrypto-lib-pem_err.o" =>
                [
                    "crypto/pem/pem_err.c",
                ],
            "crypto/pem/libcrypto-lib-pem_info.o" =>
                [
                    "crypto/pem/pem_info.c",
                ],
            "crypto/pem/libcrypto-lib-pem_lib.o" =>
                [
                    "crypto/pem/pem_lib.c",
                ],
            "crypto/pem/libcrypto-lib-pem_oth.o" =>
                [
                    "crypto/pem/pem_oth.c",
                ],
            "crypto/pem/libcrypto-lib-pem_pk8.o" =>
                [
                    "crypto/pem/pem_pk8.c",
                ],
            "crypto/pem/libcrypto-lib-pem_pkey.o" =>
                [
                    "crypto/pem/pem_pkey.c",
                ],
            "crypto/pem/libcrypto-lib-pem_sign.o" =>
                [
                    "crypto/pem/pem_sign.c",
                ],
            "crypto/pem/libcrypto-lib-pem_x509.o" =>
                [
                    "crypto/pem/pem_x509.c",
                ],
            "crypto/pem/libcrypto-lib-pem_xaux.o" =>
                [
                    "crypto/pem/pem_xaux.c",
                ],
            "crypto/pem/libcrypto-lib-pvkfmt.o" =>
                [
                    "crypto/pem/pvkfmt.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_all.o" =>
                [
                    "crypto/pem/pem_all.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_err.o" =>
                [
                    "crypto/pem/pem_err.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_info.o" =>
                [
                    "crypto/pem/pem_info.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_lib.o" =>
                [
                    "crypto/pem/pem_lib.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_oth.o" =>
                [
                    "crypto/pem/pem_oth.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_pk8.o" =>
                [
                    "crypto/pem/pem_pk8.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_pkey.o" =>
                [
                    "crypto/pem/pem_pkey.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_sign.o" =>
                [
                    "crypto/pem/pem_sign.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_x509.o" =>
                [
                    "crypto/pem/pem_x509.c",
                ],
            "crypto/pem/libcrypto-shlib-pem_xaux.o" =>
                [
                    "crypto/pem/pem_xaux.c",
                ],
            "crypto/pem/libcrypto-shlib-pvkfmt.o" =>
                [
                    "crypto/pem/pvkfmt.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_add.o" =>
                [
                    "crypto/pkcs12/p12_add.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_asn.o" =>
                [
                    "crypto/pkcs12/p12_asn.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_attr.o" =>
                [
                    "crypto/pkcs12/p12_attr.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_crpt.o" =>
                [
                    "crypto/pkcs12/p12_crpt.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_crt.o" =>
                [
                    "crypto/pkcs12/p12_crt.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_decr.o" =>
                [
                    "crypto/pkcs12/p12_decr.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_init.o" =>
                [
                    "crypto/pkcs12/p12_init.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_key.o" =>
                [
                    "crypto/pkcs12/p12_key.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_kiss.o" =>
                [
                    "crypto/pkcs12/p12_kiss.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_mutl.o" =>
                [
                    "crypto/pkcs12/p12_mutl.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_npas.o" =>
                [
                    "crypto/pkcs12/p12_npas.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_p8d.o" =>
                [
                    "crypto/pkcs12/p12_p8d.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_p8e.o" =>
                [
                    "crypto/pkcs12/p12_p8e.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_sbag.o" =>
                [
                    "crypto/pkcs12/p12_sbag.c",
                ],
            "crypto/pkcs12/libcrypto-lib-p12_utl.o" =>
                [
                    "crypto/pkcs12/p12_utl.c",
                ],
            "crypto/pkcs12/libcrypto-lib-pk12err.o" =>
                [
                    "crypto/pkcs12/pk12err.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_add.o" =>
                [
                    "crypto/pkcs12/p12_add.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_asn.o" =>
                [
                    "crypto/pkcs12/p12_asn.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_attr.o" =>
                [
                    "crypto/pkcs12/p12_attr.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_crpt.o" =>
                [
                    "crypto/pkcs12/p12_crpt.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_crt.o" =>
                [
                    "crypto/pkcs12/p12_crt.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_decr.o" =>
                [
                    "crypto/pkcs12/p12_decr.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_init.o" =>
                [
                    "crypto/pkcs12/p12_init.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_key.o" =>
                [
                    "crypto/pkcs12/p12_key.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_kiss.o" =>
                [
                    "crypto/pkcs12/p12_kiss.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_mutl.o" =>
                [
                    "crypto/pkcs12/p12_mutl.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_npas.o" =>
                [
                    "crypto/pkcs12/p12_npas.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_p8d.o" =>
                [
                    "crypto/pkcs12/p12_p8d.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_p8e.o" =>
                [
                    "crypto/pkcs12/p12_p8e.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_sbag.o" =>
                [
                    "crypto/pkcs12/p12_sbag.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-p12_utl.o" =>
                [
                    "crypto/pkcs12/p12_utl.c",
                ],
            "crypto/pkcs12/libcrypto-shlib-pk12err.o" =>
                [
                    "crypto/pkcs12/pk12err.c",
                ],
            "crypto/pkcs7/libcrypto-lib-bio_pk7.o" =>
                [
                    "crypto/pkcs7/bio_pk7.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pk7_asn1.o" =>
                [
                    "crypto/pkcs7/pk7_asn1.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pk7_attr.o" =>
                [
                    "crypto/pkcs7/pk7_attr.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pk7_doit.o" =>
                [
                    "crypto/pkcs7/pk7_doit.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pk7_lib.o" =>
                [
                    "crypto/pkcs7/pk7_lib.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pk7_mime.o" =>
                [
                    "crypto/pkcs7/pk7_mime.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pk7_smime.o" =>
                [
                    "crypto/pkcs7/pk7_smime.c",
                ],
            "crypto/pkcs7/libcrypto-lib-pkcs7err.o" =>
                [
                    "crypto/pkcs7/pkcs7err.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-bio_pk7.o" =>
                [
                    "crypto/pkcs7/bio_pk7.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pk7_asn1.o" =>
                [
                    "crypto/pkcs7/pk7_asn1.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pk7_attr.o" =>
                [
                    "crypto/pkcs7/pk7_attr.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pk7_doit.o" =>
                [
                    "crypto/pkcs7/pk7_doit.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pk7_lib.o" =>
                [
                    "crypto/pkcs7/pk7_lib.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pk7_mime.o" =>
                [
                    "crypto/pkcs7/pk7_mime.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pk7_smime.o" =>
                [
                    "crypto/pkcs7/pk7_smime.c",
                ],
            "crypto/pkcs7/libcrypto-shlib-pkcs7err.o" =>
                [
                    "crypto/pkcs7/pkcs7err.c",
                ],
            "crypto/poly1305/libcrypto-lib-poly1305-x86_64.o" =>
                [
                    "crypto/poly1305/poly1305-x86_64.s",
                ],
            "crypto/poly1305/libcrypto-lib-poly1305.o" =>
                [
                    "crypto/poly1305/poly1305.c",
                ],
            "crypto/poly1305/libcrypto-lib-poly1305_ameth.o" =>
                [
                    "crypto/poly1305/poly1305_ameth.c",
                ],
            "crypto/poly1305/libcrypto-lib-poly1305_meth.o" =>
                [
                    "crypto/poly1305/poly1305_meth.c",
                ],
            "crypto/poly1305/libcrypto-shlib-poly1305-x86_64.o" =>
                [
                    "crypto/poly1305/poly1305-x86_64.s",
                ],
            "crypto/poly1305/libcrypto-shlib-poly1305.o" =>
                [
                    "crypto/poly1305/poly1305.c",
                ],
            "crypto/poly1305/libcrypto-shlib-poly1305_ameth.o" =>
                [
                    "crypto/poly1305/poly1305_ameth.c",
                ],
            "crypto/poly1305/libcrypto-shlib-poly1305_meth.o" =>
                [
                    "crypto/poly1305/poly1305_meth.c",
                ],
            "crypto/property/libcrypto-lib-defn_cache.o" =>
                [
                    "crypto/property/defn_cache.c",
                ],
            "crypto/property/libcrypto-lib-property.o" =>
                [
                    "crypto/property/property.c",
                ],
            "crypto/property/libcrypto-lib-property_err.o" =>
                [
                    "crypto/property/property_err.c",
                ],
            "crypto/property/libcrypto-lib-property_parse.o" =>
                [
                    "crypto/property/property_parse.c",
                ],
            "crypto/property/libcrypto-lib-property_string.o" =>
                [
                    "crypto/property/property_string.c",
                ],
            "crypto/property/libcrypto-shlib-defn_cache.o" =>
                [
                    "crypto/property/defn_cache.c",
                ],
            "crypto/property/libcrypto-shlib-property.o" =>
                [
                    "crypto/property/property.c",
                ],
            "crypto/property/libcrypto-shlib-property_err.o" =>
                [
                    "crypto/property/property_err.c",
                ],
            "crypto/property/libcrypto-shlib-property_parse.o" =>
                [
                    "crypto/property/property_parse.c",
                ],
            "crypto/property/libcrypto-shlib-property_string.o" =>
                [
                    "crypto/property/property_string.c",
                ],
            "crypto/rand/libcrypto-lib-drbg_ctr.o" =>
                [
                    "crypto/rand/drbg_ctr.c",
                ],
            "crypto/rand/libcrypto-lib-drbg_hash.o" =>
                [
                    "crypto/rand/drbg_hash.c",
                ],
            "crypto/rand/libcrypto-lib-drbg_hmac.o" =>
                [
                    "crypto/rand/drbg_hmac.c",
                ],
            "crypto/rand/libcrypto-lib-drbg_lib.o" =>
                [
                    "crypto/rand/drbg_lib.c",
                ],
            "crypto/rand/libcrypto-lib-rand_crng_test.o" =>
                [
                    "crypto/rand/rand_crng_test.c",
                ],
            "crypto/rand/libcrypto-lib-rand_egd.o" =>
                [
                    "crypto/rand/rand_egd.c",
                ],
            "crypto/rand/libcrypto-lib-rand_err.o" =>
                [
                    "crypto/rand/rand_err.c",
                ],
            "crypto/rand/libcrypto-lib-rand_lib.o" =>
                [
                    "crypto/rand/rand_lib.c",
                ],
            "crypto/rand/libcrypto-lib-rand_unix.o" =>
                [
                    "crypto/rand/rand_unix.c",
                ],
            "crypto/rand/libcrypto-lib-rand_vms.o" =>
                [
                    "crypto/rand/rand_vms.c",
                ],
            "crypto/rand/libcrypto-lib-rand_win.o" =>
                [
                    "crypto/rand/rand_win.c",
                ],
            "crypto/rand/libcrypto-lib-randfile.o" =>
                [
                    "crypto/rand/randfile.c",
                ],
            "crypto/rand/libcrypto-shlib-drbg_ctr.o" =>
                [
                    "crypto/rand/drbg_ctr.c",
                ],
            "crypto/rand/libcrypto-shlib-drbg_hash.o" =>
                [
                    "crypto/rand/drbg_hash.c",
                ],
            "crypto/rand/libcrypto-shlib-drbg_hmac.o" =>
                [
                    "crypto/rand/drbg_hmac.c",
                ],
            "crypto/rand/libcrypto-shlib-drbg_lib.o" =>
                [
                    "crypto/rand/drbg_lib.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_crng_test.o" =>
                [
                    "crypto/rand/rand_crng_test.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_egd.o" =>
                [
                    "crypto/rand/rand_egd.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_err.o" =>
                [
                    "crypto/rand/rand_err.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_lib.o" =>
                [
                    "crypto/rand/rand_lib.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_unix.o" =>
                [
                    "crypto/rand/rand_unix.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_vms.o" =>
                [
                    "crypto/rand/rand_vms.c",
                ],
            "crypto/rand/libcrypto-shlib-rand_win.o" =>
                [
                    "crypto/rand/rand_win.c",
                ],
            "crypto/rand/libcrypto-shlib-randfile.o" =>
                [
                    "crypto/rand/randfile.c",
                ],
            "crypto/rc2/libcrypto-lib-rc2_cbc.o" =>
                [
                    "crypto/rc2/rc2_cbc.c",
                ],
            "crypto/rc2/libcrypto-lib-rc2_ecb.o" =>
                [
                    "crypto/rc2/rc2_ecb.c",
                ],
            "crypto/rc2/libcrypto-lib-rc2_skey.o" =>
                [
                    "crypto/rc2/rc2_skey.c",
                ],
            "crypto/rc2/libcrypto-lib-rc2cfb64.o" =>
                [
                    "crypto/rc2/rc2cfb64.c",
                ],
            "crypto/rc2/libcrypto-lib-rc2ofb64.o" =>
                [
                    "crypto/rc2/rc2ofb64.c",
                ],
            "crypto/rc2/libcrypto-shlib-rc2_cbc.o" =>
                [
                    "crypto/rc2/rc2_cbc.c",
                ],
            "crypto/rc2/libcrypto-shlib-rc2_ecb.o" =>
                [
                    "crypto/rc2/rc2_ecb.c",
                ],
            "crypto/rc2/libcrypto-shlib-rc2_skey.o" =>
                [
                    "crypto/rc2/rc2_skey.c",
                ],
            "crypto/rc2/libcrypto-shlib-rc2cfb64.o" =>
                [
                    "crypto/rc2/rc2cfb64.c",
                ],
            "crypto/rc2/libcrypto-shlib-rc2ofb64.o" =>
                [
                    "crypto/rc2/rc2ofb64.c",
                ],
            "crypto/rc4/libcrypto-lib-rc4-md5-x86_64.o" =>
                [
                    "crypto/rc4/rc4-md5-x86_64.s",
                ],
            "crypto/rc4/libcrypto-lib-rc4-x86_64.o" =>
                [
                    "crypto/rc4/rc4-x86_64.s",
                ],
            "crypto/rc4/libcrypto-shlib-rc4-md5-x86_64.o" =>
                [
                    "crypto/rc4/rc4-md5-x86_64.s",
                ],
            "crypto/rc4/libcrypto-shlib-rc4-x86_64.o" =>
                [
                    "crypto/rc4/rc4-x86_64.s",
                ],
            "crypto/ripemd/libcrypto-lib-rmd_dgst.o" =>
                [
                    "crypto/ripemd/rmd_dgst.c",
                ],
            "crypto/ripemd/libcrypto-lib-rmd_one.o" =>
                [
                    "crypto/ripemd/rmd_one.c",
                ],
            "crypto/ripemd/libcrypto-shlib-rmd_dgst.o" =>
                [
                    "crypto/ripemd/rmd_dgst.c",
                ],
            "crypto/ripemd/libcrypto-shlib-rmd_one.o" =>
                [
                    "crypto/ripemd/rmd_one.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_ameth.o" =>
                [
                    "crypto/rsa/rsa_ameth.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_asn1.o" =>
                [
                    "crypto/rsa/rsa_asn1.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_chk.o" =>
                [
                    "crypto/rsa/rsa_chk.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_crpt.o" =>
                [
                    "crypto/rsa/rsa_crpt.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_depr.o" =>
                [
                    "crypto/rsa/rsa_depr.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_err.o" =>
                [
                    "crypto/rsa/rsa_err.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_gen.o" =>
                [
                    "crypto/rsa/rsa_gen.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_lib.o" =>
                [
                    "crypto/rsa/rsa_lib.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_meth.o" =>
                [
                    "crypto/rsa/rsa_meth.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_mp.o" =>
                [
                    "crypto/rsa/rsa_mp.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_none.o" =>
                [
                    "crypto/rsa/rsa_none.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_oaep.o" =>
                [
                    "crypto/rsa/rsa_oaep.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_ossl.o" =>
                [
                    "crypto/rsa/rsa_ossl.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_pk1.o" =>
                [
                    "crypto/rsa/rsa_pk1.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_pmeth.o" =>
                [
                    "crypto/rsa/rsa_pmeth.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_prn.o" =>
                [
                    "crypto/rsa/rsa_prn.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_pss.o" =>
                [
                    "crypto/rsa/rsa_pss.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_saos.o" =>
                [
                    "crypto/rsa/rsa_saos.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_sign.o" =>
                [
                    "crypto/rsa/rsa_sign.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_sp800_56b_check.o" =>
                [
                    "crypto/rsa/rsa_sp800_56b_check.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_sp800_56b_gen.o" =>
                [
                    "crypto/rsa/rsa_sp800_56b_gen.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_ssl.o" =>
                [
                    "crypto/rsa/rsa_ssl.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_x931.o" =>
                [
                    "crypto/rsa/rsa_x931.c",
                ],
            "crypto/rsa/libcrypto-lib-rsa_x931g.o" =>
                [
                    "crypto/rsa/rsa_x931g.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_ameth.o" =>
                [
                    "crypto/rsa/rsa_ameth.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_asn1.o" =>
                [
                    "crypto/rsa/rsa_asn1.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_chk.o" =>
                [
                    "crypto/rsa/rsa_chk.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_crpt.o" =>
                [
                    "crypto/rsa/rsa_crpt.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_depr.o" =>
                [
                    "crypto/rsa/rsa_depr.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_err.o" =>
                [
                    "crypto/rsa/rsa_err.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_gen.o" =>
                [
                    "crypto/rsa/rsa_gen.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_lib.o" =>
                [
                    "crypto/rsa/rsa_lib.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_meth.o" =>
                [
                    "crypto/rsa/rsa_meth.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_mp.o" =>
                [
                    "crypto/rsa/rsa_mp.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_none.o" =>
                [
                    "crypto/rsa/rsa_none.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_oaep.o" =>
                [
                    "crypto/rsa/rsa_oaep.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_ossl.o" =>
                [
                    "crypto/rsa/rsa_ossl.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_pk1.o" =>
                [
                    "crypto/rsa/rsa_pk1.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_pmeth.o" =>
                [
                    "crypto/rsa/rsa_pmeth.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_prn.o" =>
                [
                    "crypto/rsa/rsa_prn.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_pss.o" =>
                [
                    "crypto/rsa/rsa_pss.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_saos.o" =>
                [
                    "crypto/rsa/rsa_saos.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_sign.o" =>
                [
                    "crypto/rsa/rsa_sign.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_sp800_56b_check.o" =>
                [
                    "crypto/rsa/rsa_sp800_56b_check.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_sp800_56b_gen.o" =>
                [
                    "crypto/rsa/rsa_sp800_56b_gen.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_ssl.o" =>
                [
                    "crypto/rsa/rsa_ssl.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_x931.o" =>
                [
                    "crypto/rsa/rsa_x931.c",
                ],
            "crypto/rsa/libcrypto-shlib-rsa_x931g.o" =>
                [
                    "crypto/rsa/rsa_x931g.c",
                ],
            "crypto/seed/libcrypto-lib-seed.o" =>
                [
                    "crypto/seed/seed.c",
                ],
            "crypto/seed/libcrypto-lib-seed_cbc.o" =>
                [
                    "crypto/seed/seed_cbc.c",
                ],
            "crypto/seed/libcrypto-lib-seed_cfb.o" =>
                [
                    "crypto/seed/seed_cfb.c",
                ],
            "crypto/seed/libcrypto-lib-seed_ecb.o" =>
                [
                    "crypto/seed/seed_ecb.c",
                ],
            "crypto/seed/libcrypto-lib-seed_ofb.o" =>
                [
                    "crypto/seed/seed_ofb.c",
                ],
            "crypto/seed/libcrypto-shlib-seed.o" =>
                [
                    "crypto/seed/seed.c",
                ],
            "crypto/seed/libcrypto-shlib-seed_cbc.o" =>
                [
                    "crypto/seed/seed_cbc.c",
                ],
            "crypto/seed/libcrypto-shlib-seed_cfb.o" =>
                [
                    "crypto/seed/seed_cfb.c",
                ],
            "crypto/seed/libcrypto-shlib-seed_ecb.o" =>
                [
                    "crypto/seed/seed_ecb.c",
                ],
            "crypto/seed/libcrypto-shlib-seed_ofb.o" =>
                [
                    "crypto/seed/seed_ofb.c",
                ],
            "crypto/sha/fips-dso-sha256.o" =>
                [
                    "crypto/sha/sha256.c",
                ],
            "crypto/sha/libcrypto-lib-keccak1600-x86_64.o" =>
                [
                    "crypto/sha/keccak1600-x86_64.s",
                ],
            "crypto/sha/libcrypto-lib-sha1-mb-x86_64.o" =>
                [
                    "crypto/sha/sha1-mb-x86_64.s",
                ],
            "crypto/sha/libcrypto-lib-sha1-x86_64.o" =>
                [
                    "crypto/sha/sha1-x86_64.s",
                ],
            "crypto/sha/libcrypto-lib-sha1_one.o" =>
                [
                    "crypto/sha/sha1_one.c",
                ],
            "crypto/sha/libcrypto-lib-sha1dgst.o" =>
                [
                    "crypto/sha/sha1dgst.c",
                ],
            "crypto/sha/libcrypto-lib-sha256-mb-x86_64.o" =>
                [
                    "crypto/sha/sha256-mb-x86_64.s",
                ],
            "crypto/sha/libcrypto-lib-sha256-x86_64.o" =>
                [
                    "crypto/sha/sha256-x86_64.s",
                ],
            "crypto/sha/libcrypto-lib-sha256.o" =>
                [
                    "crypto/sha/sha256.c",
                ],
            "crypto/sha/libcrypto-lib-sha512-x86_64.o" =>
                [
                    "crypto/sha/sha512-x86_64.s",
                ],
            "crypto/sha/libcrypto-lib-sha512.o" =>
                [
                    "crypto/sha/sha512.c",
                ],
            "crypto/sha/libcrypto-shlib-keccak1600-x86_64.o" =>
                [
                    "crypto/sha/keccak1600-x86_64.s",
                ],
            "crypto/sha/libcrypto-shlib-sha1-mb-x86_64.o" =>
                [
                    "crypto/sha/sha1-mb-x86_64.s",
                ],
            "crypto/sha/libcrypto-shlib-sha1-x86_64.o" =>
                [
                    "crypto/sha/sha1-x86_64.s",
                ],
            "crypto/sha/libcrypto-shlib-sha1_one.o" =>
                [
                    "crypto/sha/sha1_one.c",
                ],
            "crypto/sha/libcrypto-shlib-sha1dgst.o" =>
                [
                    "crypto/sha/sha1dgst.c",
                ],
            "crypto/sha/libcrypto-shlib-sha256-mb-x86_64.o" =>
                [
                    "crypto/sha/sha256-mb-x86_64.s",
                ],
            "crypto/sha/libcrypto-shlib-sha256-x86_64.o" =>
                [
                    "crypto/sha/sha256-x86_64.s",
                ],
            "crypto/sha/libcrypto-shlib-sha256.o" =>
                [
                    "crypto/sha/sha256.c",
                ],
            "crypto/sha/libcrypto-shlib-sha512-x86_64.o" =>
                [
                    "crypto/sha/sha512-x86_64.s",
                ],
            "crypto/sha/libcrypto-shlib-sha512.o" =>
                [
                    "crypto/sha/sha512.c",
                ],
            "crypto/siphash/libcrypto-lib-siphash.o" =>
                [
                    "crypto/siphash/siphash.c",
                ],
            "crypto/siphash/libcrypto-lib-siphash_ameth.o" =>
                [
                    "crypto/siphash/siphash_ameth.c",
                ],
            "crypto/siphash/libcrypto-lib-siphash_meth.o" =>
                [
                    "crypto/siphash/siphash_meth.c",
                ],
            "crypto/siphash/libcrypto-shlib-siphash.o" =>
                [
                    "crypto/siphash/siphash.c",
                ],
            "crypto/siphash/libcrypto-shlib-siphash_ameth.o" =>
                [
                    "crypto/siphash/siphash_ameth.c",
                ],
            "crypto/siphash/libcrypto-shlib-siphash_meth.o" =>
                [
                    "crypto/siphash/siphash_meth.c",
                ],
            "crypto/sm2/libcrypto-lib-sm2_crypt.o" =>
                [
                    "crypto/sm2/sm2_crypt.c",
                ],
            "crypto/sm2/libcrypto-lib-sm2_err.o" =>
                [
                    "crypto/sm2/sm2_err.c",
                ],
            "crypto/sm2/libcrypto-lib-sm2_pmeth.o" =>
                [
                    "crypto/sm2/sm2_pmeth.c",
                ],
            "crypto/sm2/libcrypto-lib-sm2_sign.o" =>
                [
                    "crypto/sm2/sm2_sign.c",
                ],
            "crypto/sm2/libcrypto-shlib-sm2_crypt.o" =>
                [
                    "crypto/sm2/sm2_crypt.c",
                ],
            "crypto/sm2/libcrypto-shlib-sm2_err.o" =>
                [
                    "crypto/sm2/sm2_err.c",
                ],
            "crypto/sm2/libcrypto-shlib-sm2_pmeth.o" =>
                [
                    "crypto/sm2/sm2_pmeth.c",
                ],
            "crypto/sm2/libcrypto-shlib-sm2_sign.o" =>
                [
                    "crypto/sm2/sm2_sign.c",
                ],
            "crypto/sm3/libcrypto-lib-m_sm3.o" =>
                [
                    "crypto/sm3/m_sm3.c",
                ],
            "crypto/sm3/libcrypto-lib-sm3.o" =>
                [
                    "crypto/sm3/sm3.c",
                ],
            "crypto/sm3/libcrypto-shlib-m_sm3.o" =>
                [
                    "crypto/sm3/m_sm3.c",
                ],
            "crypto/sm3/libcrypto-shlib-sm3.o" =>
                [
                    "crypto/sm3/sm3.c",
                ],
            "crypto/sm4/libcrypto-lib-sm4.o" =>
                [
                    "crypto/sm4/sm4.c",
                ],
            "crypto/sm4/libcrypto-shlib-sm4.o" =>
                [
                    "crypto/sm4/sm4.c",
                ],
            "crypto/srp/libcrypto-lib-srp_lib.o" =>
                [
                    "crypto/srp/srp_lib.c",
                ],
            "crypto/srp/libcrypto-lib-srp_vfy.o" =>
                [
                    "crypto/srp/srp_vfy.c",
                ],
            "crypto/srp/libcrypto-shlib-srp_lib.o" =>
                [
                    "crypto/srp/srp_lib.c",
                ],
            "crypto/srp/libcrypto-shlib-srp_vfy.o" =>
                [
                    "crypto/srp/srp_vfy.c",
                ],
            "crypto/stack/libcrypto-lib-stack.o" =>
                [
                    "crypto/stack/stack.c",
                ],
            "crypto/stack/libcrypto-shlib-stack.o" =>
                [
                    "crypto/stack/stack.c",
                ],
            "crypto/store/libcrypto-lib-loader_file.o" =>
                [
                    "crypto/store/loader_file.c",
                ],
            "crypto/store/libcrypto-lib-store_err.o" =>
                [
                    "crypto/store/store_err.c",
                ],
            "crypto/store/libcrypto-lib-store_init.o" =>
                [
                    "crypto/store/store_init.c",
                ],
            "crypto/store/libcrypto-lib-store_lib.o" =>
                [
                    "crypto/store/store_lib.c",
                ],
            "crypto/store/libcrypto-lib-store_register.o" =>
                [
                    "crypto/store/store_register.c",
                ],
            "crypto/store/libcrypto-lib-store_strings.o" =>
                [
                    "crypto/store/store_strings.c",
                ],
            "crypto/store/libcrypto-shlib-loader_file.o" =>
                [
                    "crypto/store/loader_file.c",
                ],
            "crypto/store/libcrypto-shlib-store_err.o" =>
                [
                    "crypto/store/store_err.c",
                ],
            "crypto/store/libcrypto-shlib-store_init.o" =>
                [
                    "crypto/store/store_init.c",
                ],
            "crypto/store/libcrypto-shlib-store_lib.o" =>
                [
                    "crypto/store/store_lib.c",
                ],
            "crypto/store/libcrypto-shlib-store_register.o" =>
                [
                    "crypto/store/store_register.c",
                ],
            "crypto/store/libcrypto-shlib-store_strings.o" =>
                [
                    "crypto/store/store_strings.c",
                ],
            "crypto/ts/libcrypto-lib-ts_asn1.o" =>
                [
                    "crypto/ts/ts_asn1.c",
                ],
            "crypto/ts/libcrypto-lib-ts_conf.o" =>
                [
                    "crypto/ts/ts_conf.c",
                ],
            "crypto/ts/libcrypto-lib-ts_err.o" =>
                [
                    "crypto/ts/ts_err.c",
                ],
            "crypto/ts/libcrypto-lib-ts_lib.o" =>
                [
                    "crypto/ts/ts_lib.c",
                ],
            "crypto/ts/libcrypto-lib-ts_req_print.o" =>
                [
                    "crypto/ts/ts_req_print.c",
                ],
            "crypto/ts/libcrypto-lib-ts_req_utils.o" =>
                [
                    "crypto/ts/ts_req_utils.c",
                ],
            "crypto/ts/libcrypto-lib-ts_rsp_print.o" =>
                [
                    "crypto/ts/ts_rsp_print.c",
                ],
            "crypto/ts/libcrypto-lib-ts_rsp_sign.o" =>
                [
                    "crypto/ts/ts_rsp_sign.c",
                ],
            "crypto/ts/libcrypto-lib-ts_rsp_utils.o" =>
                [
                    "crypto/ts/ts_rsp_utils.c",
                ],
            "crypto/ts/libcrypto-lib-ts_rsp_verify.o" =>
                [
                    "crypto/ts/ts_rsp_verify.c",
                ],
            "crypto/ts/libcrypto-lib-ts_verify_ctx.o" =>
                [
                    "crypto/ts/ts_verify_ctx.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_asn1.o" =>
                [
                    "crypto/ts/ts_asn1.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_conf.o" =>
                [
                    "crypto/ts/ts_conf.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_err.o" =>
                [
                    "crypto/ts/ts_err.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_lib.o" =>
                [
                    "crypto/ts/ts_lib.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_req_print.o" =>
                [
                    "crypto/ts/ts_req_print.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_req_utils.o" =>
                [
                    "crypto/ts/ts_req_utils.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_rsp_print.o" =>
                [
                    "crypto/ts/ts_rsp_print.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_rsp_sign.o" =>
                [
                    "crypto/ts/ts_rsp_sign.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_rsp_utils.o" =>
                [
                    "crypto/ts/ts_rsp_utils.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_rsp_verify.o" =>
                [
                    "crypto/ts/ts_rsp_verify.c",
                ],
            "crypto/ts/libcrypto-shlib-ts_verify_ctx.o" =>
                [
                    "crypto/ts/ts_verify_ctx.c",
                ],
            "crypto/txt_db/libcrypto-lib-txt_db.o" =>
                [
                    "crypto/txt_db/txt_db.c",
                ],
            "crypto/txt_db/libcrypto-shlib-txt_db.o" =>
                [
                    "crypto/txt_db/txt_db.c",
                ],
            "crypto/ui/libcrypto-lib-ui_err.o" =>
                [
                    "crypto/ui/ui_err.c",
                ],
            "crypto/ui/libcrypto-lib-ui_lib.o" =>
                [
                    "crypto/ui/ui_lib.c",
                ],
            "crypto/ui/libcrypto-lib-ui_null.o" =>
                [
                    "crypto/ui/ui_null.c",
                ],
            "crypto/ui/libcrypto-lib-ui_openssl.o" =>
                [
                    "crypto/ui/ui_openssl.c",
                ],
            "crypto/ui/libcrypto-lib-ui_util.o" =>
                [
                    "crypto/ui/ui_util.c",
                ],
            "crypto/ui/libcrypto-shlib-ui_err.o" =>
                [
                    "crypto/ui/ui_err.c",
                ],
            "crypto/ui/libcrypto-shlib-ui_lib.o" =>
                [
                    "crypto/ui/ui_lib.c",
                ],
            "crypto/ui/libcrypto-shlib-ui_null.o" =>
                [
                    "crypto/ui/ui_null.c",
                ],
            "crypto/ui/libcrypto-shlib-ui_openssl.o" =>
                [
                    "crypto/ui/ui_openssl.c",
                ],
            "crypto/ui/libcrypto-shlib-ui_util.o" =>
                [
                    "crypto/ui/ui_util.c",
                ],
            "crypto/whrlpool/libcrypto-lib-wp-x86_64.o" =>
                [
                    "crypto/whrlpool/wp-x86_64.s",
                ],
            "crypto/whrlpool/libcrypto-lib-wp_dgst.o" =>
                [
                    "crypto/whrlpool/wp_dgst.c",
                ],
            "crypto/whrlpool/libcrypto-shlib-wp-x86_64.o" =>
                [
                    "crypto/whrlpool/wp-x86_64.s",
                ],
            "crypto/whrlpool/libcrypto-shlib-wp_dgst.o" =>
                [
                    "crypto/whrlpool/wp_dgst.c",
                ],
            "crypto/x509/libcrypto-lib-by_dir.o" =>
                [
                    "crypto/x509/by_dir.c",
                ],
            "crypto/x509/libcrypto-lib-by_file.o" =>
                [
                    "crypto/x509/by_file.c",
                ],
            "crypto/x509/libcrypto-lib-t_crl.o" =>
                [
                    "crypto/x509/t_crl.c",
                ],
            "crypto/x509/libcrypto-lib-t_req.o" =>
                [
                    "crypto/x509/t_req.c",
                ],
            "crypto/x509/libcrypto-lib-t_x509.o" =>
                [
                    "crypto/x509/t_x509.c",
                ],
            "crypto/x509/libcrypto-lib-x509_att.o" =>
                [
                    "crypto/x509/x509_att.c",
                ],
            "crypto/x509/libcrypto-lib-x509_cmp.o" =>
                [
                    "crypto/x509/x509_cmp.c",
                ],
            "crypto/x509/libcrypto-lib-x509_d2.o" =>
                [
                    "crypto/x509/x509_d2.c",
                ],
            "crypto/x509/libcrypto-lib-x509_def.o" =>
                [
                    "crypto/x509/x509_def.c",
                ],
            "crypto/x509/libcrypto-lib-x509_err.o" =>
                [
                    "crypto/x509/x509_err.c",
                ],
            "crypto/x509/libcrypto-lib-x509_ext.o" =>
                [
                    "crypto/x509/x509_ext.c",
                ],
            "crypto/x509/libcrypto-lib-x509_lu.o" =>
                [
                    "crypto/x509/x509_lu.c",
                ],
            "crypto/x509/libcrypto-lib-x509_meth.o" =>
                [
                    "crypto/x509/x509_meth.c",
                ],
            "crypto/x509/libcrypto-lib-x509_obj.o" =>
                [
                    "crypto/x509/x509_obj.c",
                ],
            "crypto/x509/libcrypto-lib-x509_r2x.o" =>
                [
                    "crypto/x509/x509_r2x.c",
                ],
            "crypto/x509/libcrypto-lib-x509_req.o" =>
                [
                    "crypto/x509/x509_req.c",
                ],
            "crypto/x509/libcrypto-lib-x509_set.o" =>
                [
                    "crypto/x509/x509_set.c",
                ],
            "crypto/x509/libcrypto-lib-x509_trs.o" =>
                [
                    "crypto/x509/x509_trs.c",
                ],
            "crypto/x509/libcrypto-lib-x509_txt.o" =>
                [
                    "crypto/x509/x509_txt.c",
                ],
            "crypto/x509/libcrypto-lib-x509_v3.o" =>
                [
                    "crypto/x509/x509_v3.c",
                ],
            "crypto/x509/libcrypto-lib-x509_vfy.o" =>
                [
                    "crypto/x509/x509_vfy.c",
                ],
            "crypto/x509/libcrypto-lib-x509_vpm.o" =>
                [
                    "crypto/x509/x509_vpm.c",
                ],
            "crypto/x509/libcrypto-lib-x509cset.o" =>
                [
                    "crypto/x509/x509cset.c",
                ],
            "crypto/x509/libcrypto-lib-x509name.o" =>
                [
                    "crypto/x509/x509name.c",
                ],
            "crypto/x509/libcrypto-lib-x509rset.o" =>
                [
                    "crypto/x509/x509rset.c",
                ],
            "crypto/x509/libcrypto-lib-x509spki.o" =>
                [
                    "crypto/x509/x509spki.c",
                ],
            "crypto/x509/libcrypto-lib-x509type.o" =>
                [
                    "crypto/x509/x509type.c",
                ],
            "crypto/x509/libcrypto-lib-x_all.o" =>
                [
                    "crypto/x509/x_all.c",
                ],
            "crypto/x509/libcrypto-lib-x_attrib.o" =>
                [
                    "crypto/x509/x_attrib.c",
                ],
            "crypto/x509/libcrypto-lib-x_crl.o" =>
                [
                    "crypto/x509/x_crl.c",
                ],
            "crypto/x509/libcrypto-lib-x_exten.o" =>
                [
                    "crypto/x509/x_exten.c",
                ],
            "crypto/x509/libcrypto-lib-x_name.o" =>
                [
                    "crypto/x509/x_name.c",
                ],
            "crypto/x509/libcrypto-lib-x_pubkey.o" =>
                [
                    "crypto/x509/x_pubkey.c",
                ],
            "crypto/x509/libcrypto-lib-x_req.o" =>
                [
                    "crypto/x509/x_req.c",
                ],
            "crypto/x509/libcrypto-lib-x_x509.o" =>
                [
                    "crypto/x509/x_x509.c",
                ],
            "crypto/x509/libcrypto-lib-x_x509a.o" =>
                [
                    "crypto/x509/x_x509a.c",
                ],
            "crypto/x509/libcrypto-shlib-by_dir.o" =>
                [
                    "crypto/x509/by_dir.c",
                ],
            "crypto/x509/libcrypto-shlib-by_file.o" =>
                [
                    "crypto/x509/by_file.c",
                ],
            "crypto/x509/libcrypto-shlib-t_crl.o" =>
                [
                    "crypto/x509/t_crl.c",
                ],
            "crypto/x509/libcrypto-shlib-t_req.o" =>
                [
                    "crypto/x509/t_req.c",
                ],
            "crypto/x509/libcrypto-shlib-t_x509.o" =>
                [
                    "crypto/x509/t_x509.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_att.o" =>
                [
                    "crypto/x509/x509_att.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_cmp.o" =>
                [
                    "crypto/x509/x509_cmp.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_d2.o" =>
                [
                    "crypto/x509/x509_d2.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_def.o" =>
                [
                    "crypto/x509/x509_def.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_err.o" =>
                [
                    "crypto/x509/x509_err.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_ext.o" =>
                [
                    "crypto/x509/x509_ext.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_lu.o" =>
                [
                    "crypto/x509/x509_lu.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_meth.o" =>
                [
                    "crypto/x509/x509_meth.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_obj.o" =>
                [
                    "crypto/x509/x509_obj.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_r2x.o" =>
                [
                    "crypto/x509/x509_r2x.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_req.o" =>
                [
                    "crypto/x509/x509_req.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_set.o" =>
                [
                    "crypto/x509/x509_set.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_trs.o" =>
                [
                    "crypto/x509/x509_trs.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_txt.o" =>
                [
                    "crypto/x509/x509_txt.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_v3.o" =>
                [
                    "crypto/x509/x509_v3.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_vfy.o" =>
                [
                    "crypto/x509/x509_vfy.c",
                ],
            "crypto/x509/libcrypto-shlib-x509_vpm.o" =>
                [
                    "crypto/x509/x509_vpm.c",
                ],
            "crypto/x509/libcrypto-shlib-x509cset.o" =>
                [
                    "crypto/x509/x509cset.c",
                ],
            "crypto/x509/libcrypto-shlib-x509name.o" =>
                [
                    "crypto/x509/x509name.c",
                ],
            "crypto/x509/libcrypto-shlib-x509rset.o" =>
                [
                    "crypto/x509/x509rset.c",
                ],
            "crypto/x509/libcrypto-shlib-x509spki.o" =>
                [
                    "crypto/x509/x509spki.c",
                ],
            "crypto/x509/libcrypto-shlib-x509type.o" =>
                [
                    "crypto/x509/x509type.c",
                ],
            "crypto/x509/libcrypto-shlib-x_all.o" =>
                [
                    "crypto/x509/x_all.c",
                ],
            "crypto/x509/libcrypto-shlib-x_attrib.o" =>
                [
                    "crypto/x509/x_attrib.c",
                ],
            "crypto/x509/libcrypto-shlib-x_crl.o" =>
                [
                    "crypto/x509/x_crl.c",
                ],
            "crypto/x509/libcrypto-shlib-x_exten.o" =>
                [
                    "crypto/x509/x_exten.c",
                ],
            "crypto/x509/libcrypto-shlib-x_name.o" =>
                [
                    "crypto/x509/x_name.c",
                ],
            "crypto/x509/libcrypto-shlib-x_pubkey.o" =>
                [
                    "crypto/x509/x_pubkey.c",
                ],
            "crypto/x509/libcrypto-shlib-x_req.o" =>
                [
                    "crypto/x509/x_req.c",
                ],
            "crypto/x509/libcrypto-shlib-x_x509.o" =>
                [
                    "crypto/x509/x_x509.c",
                ],
            "crypto/x509/libcrypto-shlib-x_x509a.o" =>
                [
                    "crypto/x509/x_x509a.c",
                ],
            "crypto/x509v3/libcrypto-lib-pcy_cache.o" =>
                [
                    "crypto/x509v3/pcy_cache.c",
                ],
            "crypto/x509v3/libcrypto-lib-pcy_data.o" =>
                [
                    "crypto/x509v3/pcy_data.c",
                ],
            "crypto/x509v3/libcrypto-lib-pcy_lib.o" =>
                [
                    "crypto/x509v3/pcy_lib.c",
                ],
            "crypto/x509v3/libcrypto-lib-pcy_map.o" =>
                [
                    "crypto/x509v3/pcy_map.c",
                ],
            "crypto/x509v3/libcrypto-lib-pcy_node.o" =>
                [
                    "crypto/x509v3/pcy_node.c",
                ],
            "crypto/x509v3/libcrypto-lib-pcy_tree.o" =>
                [
                    "crypto/x509v3/pcy_tree.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_addr.o" =>
                [
                    "crypto/x509v3/v3_addr.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_admis.o" =>
                [
                    "crypto/x509v3/v3_admis.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_akey.o" =>
                [
                    "crypto/x509v3/v3_akey.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_akeya.o" =>
                [
                    "crypto/x509v3/v3_akeya.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_alt.o" =>
                [
                    "crypto/x509v3/v3_alt.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_asid.o" =>
                [
                    "crypto/x509v3/v3_asid.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_bcons.o" =>
                [
                    "crypto/x509v3/v3_bcons.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_bitst.o" =>
                [
                    "crypto/x509v3/v3_bitst.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_conf.o" =>
                [
                    "crypto/x509v3/v3_conf.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_cpols.o" =>
                [
                    "crypto/x509v3/v3_cpols.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_crld.o" =>
                [
                    "crypto/x509v3/v3_crld.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_enum.o" =>
                [
                    "crypto/x509v3/v3_enum.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_extku.o" =>
                [
                    "crypto/x509v3/v3_extku.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_genn.o" =>
                [
                    "crypto/x509v3/v3_genn.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_ia5.o" =>
                [
                    "crypto/x509v3/v3_ia5.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_info.o" =>
                [
                    "crypto/x509v3/v3_info.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_int.o" =>
                [
                    "crypto/x509v3/v3_int.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_lib.o" =>
                [
                    "crypto/x509v3/v3_lib.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_ncons.o" =>
                [
                    "crypto/x509v3/v3_ncons.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_pci.o" =>
                [
                    "crypto/x509v3/v3_pci.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_pcia.o" =>
                [
                    "crypto/x509v3/v3_pcia.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_pcons.o" =>
                [
                    "crypto/x509v3/v3_pcons.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_pku.o" =>
                [
                    "crypto/x509v3/v3_pku.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_pmaps.o" =>
                [
                    "crypto/x509v3/v3_pmaps.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_prn.o" =>
                [
                    "crypto/x509v3/v3_prn.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_purp.o" =>
                [
                    "crypto/x509v3/v3_purp.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_skey.o" =>
                [
                    "crypto/x509v3/v3_skey.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_sxnet.o" =>
                [
                    "crypto/x509v3/v3_sxnet.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_tlsf.o" =>
                [
                    "crypto/x509v3/v3_tlsf.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3_utl.o" =>
                [
                    "crypto/x509v3/v3_utl.c",
                ],
            "crypto/x509v3/libcrypto-lib-v3err.o" =>
                [
                    "crypto/x509v3/v3err.c",
                ],
            "crypto/x509v3/libcrypto-shlib-pcy_cache.o" =>
                [
                    "crypto/x509v3/pcy_cache.c",
                ],
            "crypto/x509v3/libcrypto-shlib-pcy_data.o" =>
                [
                    "crypto/x509v3/pcy_data.c",
                ],
            "crypto/x509v3/libcrypto-shlib-pcy_lib.o" =>
                [
                    "crypto/x509v3/pcy_lib.c",
                ],
            "crypto/x509v3/libcrypto-shlib-pcy_map.o" =>
                [
                    "crypto/x509v3/pcy_map.c",
                ],
            "crypto/x509v3/libcrypto-shlib-pcy_node.o" =>
                [
                    "crypto/x509v3/pcy_node.c",
                ],
            "crypto/x509v3/libcrypto-shlib-pcy_tree.o" =>
                [
                    "crypto/x509v3/pcy_tree.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_addr.o" =>
                [
                    "crypto/x509v3/v3_addr.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_admis.o" =>
                [
                    "crypto/x509v3/v3_admis.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_akey.o" =>
                [
                    "crypto/x509v3/v3_akey.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_akeya.o" =>
                [
                    "crypto/x509v3/v3_akeya.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_alt.o" =>
                [
                    "crypto/x509v3/v3_alt.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_asid.o" =>
                [
                    "crypto/x509v3/v3_asid.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_bcons.o" =>
                [
                    "crypto/x509v3/v3_bcons.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_bitst.o" =>
                [
                    "crypto/x509v3/v3_bitst.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_conf.o" =>
                [
                    "crypto/x509v3/v3_conf.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_cpols.o" =>
                [
                    "crypto/x509v3/v3_cpols.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_crld.o" =>
                [
                    "crypto/x509v3/v3_crld.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_enum.o" =>
                [
                    "crypto/x509v3/v3_enum.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_extku.o" =>
                [
                    "crypto/x509v3/v3_extku.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_genn.o" =>
                [
                    "crypto/x509v3/v3_genn.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_ia5.o" =>
                [
                    "crypto/x509v3/v3_ia5.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_info.o" =>
                [
                    "crypto/x509v3/v3_info.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_int.o" =>
                [
                    "crypto/x509v3/v3_int.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_lib.o" =>
                [
                    "crypto/x509v3/v3_lib.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_ncons.o" =>
                [
                    "crypto/x509v3/v3_ncons.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_pci.o" =>
                [
                    "crypto/x509v3/v3_pci.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_pcia.o" =>
                [
                    "crypto/x509v3/v3_pcia.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_pcons.o" =>
                [
                    "crypto/x509v3/v3_pcons.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_pku.o" =>
                [
                    "crypto/x509v3/v3_pku.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_pmaps.o" =>
                [
                    "crypto/x509v3/v3_pmaps.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_prn.o" =>
                [
                    "crypto/x509v3/v3_prn.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_purp.o" =>
                [
                    "crypto/x509v3/v3_purp.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_skey.o" =>
                [
                    "crypto/x509v3/v3_skey.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_sxnet.o" =>
                [
                    "crypto/x509v3/v3_sxnet.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_tlsf.o" =>
                [
                    "crypto/x509v3/v3_tlsf.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3_utl.o" =>
                [
                    "crypto/x509v3/v3_utl.c",
                ],
            "crypto/x509v3/libcrypto-shlib-v3err.o" =>
                [
                    "crypto/x509v3/v3err.c",
                ],
            "engines/afalg" =>
                [
                    "engines/afalg-dso-e_afalg.o",
                    "engines/afalg.ld",
                ],
            "engines/afalg-dso-e_afalg.o" =>
                [
                    "engines/e_afalg.c",
                ],
            "engines/capi" =>
                [
                    "engines/capi-dso-e_capi.o",
                    "engines/capi.ld",
                ],
            "engines/capi-dso-e_capi.o" =>
                [
                    "engines/e_capi.c",
                ],
            "engines/dasync" =>
                [
                    "engines/dasync-dso-e_dasync.o",
                    "engines/dasync.ld",
                ],
            "engines/dasync-dso-e_dasync.o" =>
                [
                    "engines/e_dasync.c",
                ],
            "engines/ossltest" =>
                [
                    "engines/ossltest-dso-e_ossltest.o",
                    "engines/ossltest.ld",
                ],
            "engines/ossltest-dso-e_ossltest.o" =>
                [
                    "engines/e_ossltest.c",
                ],
            "engines/padlock" =>
                [
                    "engines/padlock-dso-e_padlock-x86_64.o",
                    "engines/padlock-dso-e_padlock.o",
                    "engines/padlock.ld",
                ],
            "engines/padlock-dso-e_padlock-x86_64.o" =>
                [
                    "engines/e_padlock-x86_64.s",
                ],
            "engines/padlock-dso-e_padlock.o" =>
                [
                    "engines/e_padlock.c",
                ],
            "fuzz/asn1-test" =>
                [
                    "fuzz/asn1-test-bin-asn1.o",
                    "fuzz/asn1-test-bin-test-corpus.o",
                ],
            "fuzz/asn1-test-bin-asn1.o" =>
                [
                    "fuzz/asn1.c",
                ],
            "fuzz/asn1-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/asn1parse-test" =>
                [
                    "fuzz/asn1parse-test-bin-asn1parse.o",
                    "fuzz/asn1parse-test-bin-test-corpus.o",
                ],
            "fuzz/asn1parse-test-bin-asn1parse.o" =>
                [
                    "fuzz/asn1parse.c",
                ],
            "fuzz/asn1parse-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/bignum-test" =>
                [
                    "fuzz/bignum-test-bin-bignum.o",
                    "fuzz/bignum-test-bin-test-corpus.o",
                ],
            "fuzz/bignum-test-bin-bignum.o" =>
                [
                    "fuzz/bignum.c",
                ],
            "fuzz/bignum-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/bndiv-test" =>
                [
                    "fuzz/bndiv-test-bin-bndiv.o",
                    "fuzz/bndiv-test-bin-test-corpus.o",
                ],
            "fuzz/bndiv-test-bin-bndiv.o" =>
                [
                    "fuzz/bndiv.c",
                ],
            "fuzz/bndiv-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/client-test" =>
                [
                    "fuzz/client-test-bin-client.o",
                    "fuzz/client-test-bin-test-corpus.o",
                ],
            "fuzz/client-test-bin-client.o" =>
                [
                    "fuzz/client.c",
                ],
            "fuzz/client-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/cms-test" =>
                [
                    "fuzz/cms-test-bin-cms.o",
                    "fuzz/cms-test-bin-test-corpus.o",
                ],
            "fuzz/cms-test-bin-cms.o" =>
                [
                    "fuzz/cms.c",
                ],
            "fuzz/cms-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/conf-test" =>
                [
                    "fuzz/conf-test-bin-conf.o",
                    "fuzz/conf-test-bin-test-corpus.o",
                ],
            "fuzz/conf-test-bin-conf.o" =>
                [
                    "fuzz/conf.c",
                ],
            "fuzz/conf-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/crl-test" =>
                [
                    "fuzz/crl-test-bin-crl.o",
                    "fuzz/crl-test-bin-test-corpus.o",
                ],
            "fuzz/crl-test-bin-crl.o" =>
                [
                    "fuzz/crl.c",
                ],
            "fuzz/crl-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/ct-test" =>
                [
                    "fuzz/ct-test-bin-ct.o",
                    "fuzz/ct-test-bin-test-corpus.o",
                ],
            "fuzz/ct-test-bin-ct.o" =>
                [
                    "fuzz/ct.c",
                ],
            "fuzz/ct-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/server-test" =>
                [
                    "fuzz/server-test-bin-server.o",
                    "fuzz/server-test-bin-test-corpus.o",
                ],
            "fuzz/server-test-bin-server.o" =>
                [
                    "fuzz/server.c",
                ],
            "fuzz/server-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/x509-test" =>
                [
                    "fuzz/x509-test-bin-test-corpus.o",
                    "fuzz/x509-test-bin-x509.o",
                ],
            "fuzz/x509-test-bin-test-corpus.o" =>
                [
                    "fuzz/test-corpus.c",
                ],
            "fuzz/x509-test-bin-x509.o" =>
                [
                    "fuzz/x509.c",
                ],
            "libcrypto" =>
                [
                    "crypto/aes/libcrypto-lib-aes-x86_64.o",
                    "crypto/aes/libcrypto-lib-aes_cfb.o",
                    "crypto/aes/libcrypto-lib-aes_ecb.o",
                    "crypto/aes/libcrypto-lib-aes_ige.o",
                    "crypto/aes/libcrypto-lib-aes_misc.o",
                    "crypto/aes/libcrypto-lib-aes_ofb.o",
                    "crypto/aes/libcrypto-lib-aes_wrap.o",
                    "crypto/aes/libcrypto-lib-aesni-mb-x86_64.o",
                    "crypto/aes/libcrypto-lib-aesni-sha1-x86_64.o",
                    "crypto/aes/libcrypto-lib-aesni-sha256-x86_64.o",
                    "crypto/aes/libcrypto-lib-aesni-x86_64.o",
                    "crypto/aes/libcrypto-lib-bsaes-x86_64.o",
                    "crypto/aes/libcrypto-lib-vpaes-x86_64.o",
                    "crypto/aria/libcrypto-lib-aria.o",
                    "crypto/asn1/libcrypto-lib-a_bitstr.o",
                    "crypto/asn1/libcrypto-lib-a_d2i_fp.o",
                    "crypto/asn1/libcrypto-lib-a_digest.o",
                    "crypto/asn1/libcrypto-lib-a_dup.o",
                    "crypto/asn1/libcrypto-lib-a_gentm.o",
                    "crypto/asn1/libcrypto-lib-a_i2d_fp.o",
                    "crypto/asn1/libcrypto-lib-a_int.o",
                    "crypto/asn1/libcrypto-lib-a_mbstr.o",
                    "crypto/asn1/libcrypto-lib-a_object.o",
                    "crypto/asn1/libcrypto-lib-a_octet.o",
                    "crypto/asn1/libcrypto-lib-a_print.o",
                    "crypto/asn1/libcrypto-lib-a_sign.o",
                    "crypto/asn1/libcrypto-lib-a_strex.o",
                    "crypto/asn1/libcrypto-lib-a_strnid.o",
                    "crypto/asn1/libcrypto-lib-a_time.o",
                    "crypto/asn1/libcrypto-lib-a_type.o",
                    "crypto/asn1/libcrypto-lib-a_utctm.o",
                    "crypto/asn1/libcrypto-lib-a_utf8.o",
                    "crypto/asn1/libcrypto-lib-a_verify.o",
                    "crypto/asn1/libcrypto-lib-ameth_lib.o",
                    "crypto/asn1/libcrypto-lib-asn1_err.o",
                    "crypto/asn1/libcrypto-lib-asn1_gen.o",
                    "crypto/asn1/libcrypto-lib-asn1_item_list.o",
                    "crypto/asn1/libcrypto-lib-asn1_lib.o",
                    "crypto/asn1/libcrypto-lib-asn1_par.o",
                    "crypto/asn1/libcrypto-lib-asn_mime.o",
                    "crypto/asn1/libcrypto-lib-asn_moid.o",
                    "crypto/asn1/libcrypto-lib-asn_mstbl.o",
                    "crypto/asn1/libcrypto-lib-asn_pack.o",
                    "crypto/asn1/libcrypto-lib-bio_asn1.o",
                    "crypto/asn1/libcrypto-lib-bio_ndef.o",
                    "crypto/asn1/libcrypto-lib-d2i_pr.o",
                    "crypto/asn1/libcrypto-lib-d2i_pu.o",
                    "crypto/asn1/libcrypto-lib-evp_asn1.o",
                    "crypto/asn1/libcrypto-lib-f_int.o",
                    "crypto/asn1/libcrypto-lib-f_string.o",
                    "crypto/asn1/libcrypto-lib-i2d_pr.o",
                    "crypto/asn1/libcrypto-lib-i2d_pu.o",
                    "crypto/asn1/libcrypto-lib-n_pkey.o",
                    "crypto/asn1/libcrypto-lib-nsseq.o",
                    "crypto/asn1/libcrypto-lib-p5_pbe.o",
                    "crypto/asn1/libcrypto-lib-p5_pbev2.o",
                    "crypto/asn1/libcrypto-lib-p5_scrypt.o",
                    "crypto/asn1/libcrypto-lib-p8_pkey.o",
                    "crypto/asn1/libcrypto-lib-t_bitst.o",
                    "crypto/asn1/libcrypto-lib-t_pkey.o",
                    "crypto/asn1/libcrypto-lib-t_spki.o",
                    "crypto/asn1/libcrypto-lib-tasn_dec.o",
                    "crypto/asn1/libcrypto-lib-tasn_enc.o",
                    "crypto/asn1/libcrypto-lib-tasn_fre.o",
                    "crypto/asn1/libcrypto-lib-tasn_new.o",
                    "crypto/asn1/libcrypto-lib-tasn_prn.o",
                    "crypto/asn1/libcrypto-lib-tasn_scn.o",
                    "crypto/asn1/libcrypto-lib-tasn_typ.o",
                    "crypto/asn1/libcrypto-lib-tasn_utl.o",
                    "crypto/asn1/libcrypto-lib-x_algor.o",
                    "crypto/asn1/libcrypto-lib-x_bignum.o",
                    "crypto/asn1/libcrypto-lib-x_info.o",
                    "crypto/asn1/libcrypto-lib-x_int64.o",
                    "crypto/asn1/libcrypto-lib-x_long.o",
                    "crypto/asn1/libcrypto-lib-x_pkey.o",
                    "crypto/asn1/libcrypto-lib-x_sig.o",
                    "crypto/asn1/libcrypto-lib-x_spki.o",
                    "crypto/asn1/libcrypto-lib-x_val.o",
                    "crypto/async/arch/libcrypto-lib-async_null.o",
                    "crypto/async/arch/libcrypto-lib-async_posix.o",
                    "crypto/async/arch/libcrypto-lib-async_win.o",
                    "crypto/async/libcrypto-lib-async.o",
                    "crypto/async/libcrypto-lib-async_err.o",
                    "crypto/async/libcrypto-lib-async_wait.o",
                    "crypto/bf/libcrypto-lib-bf_cfb64.o",
                    "crypto/bf/libcrypto-lib-bf_ecb.o",
                    "crypto/bf/libcrypto-lib-bf_enc.o",
                    "crypto/bf/libcrypto-lib-bf_ofb64.o",
                    "crypto/bf/libcrypto-lib-bf_skey.o",
                    "crypto/bio/libcrypto-lib-b_addr.o",
                    "crypto/bio/libcrypto-lib-b_dump.o",
                    "crypto/bio/libcrypto-lib-b_print.o",
                    "crypto/bio/libcrypto-lib-b_sock.o",
                    "crypto/bio/libcrypto-lib-b_sock2.o",
                    "crypto/bio/libcrypto-lib-bf_buff.o",
                    "crypto/bio/libcrypto-lib-bf_lbuf.o",
                    "crypto/bio/libcrypto-lib-bf_nbio.o",
                    "crypto/bio/libcrypto-lib-bf_null.o",
                    "crypto/bio/libcrypto-lib-bio_cb.o",
                    "crypto/bio/libcrypto-lib-bio_err.o",
                    "crypto/bio/libcrypto-lib-bio_lib.o",
                    "crypto/bio/libcrypto-lib-bio_meth.o",
                    "crypto/bio/libcrypto-lib-bss_acpt.o",
                    "crypto/bio/libcrypto-lib-bss_bio.o",
                    "crypto/bio/libcrypto-lib-bss_conn.o",
                    "crypto/bio/libcrypto-lib-bss_dgram.o",
                    "crypto/bio/libcrypto-lib-bss_fd.o",
                    "crypto/bio/libcrypto-lib-bss_file.o",
                    "crypto/bio/libcrypto-lib-bss_log.o",
                    "crypto/bio/libcrypto-lib-bss_mem.o",
                    "crypto/bio/libcrypto-lib-bss_null.o",
                    "crypto/bio/libcrypto-lib-bss_sock.o",
                    "crypto/blake2/libcrypto-lib-blake2b.o",
                    "crypto/blake2/libcrypto-lib-blake2b_mac.o",
                    "crypto/blake2/libcrypto-lib-blake2s.o",
                    "crypto/blake2/libcrypto-lib-blake2s_mac.o",
                    "crypto/blake2/libcrypto-lib-m_blake2b.o",
                    "crypto/blake2/libcrypto-lib-m_blake2s.o",
                    "crypto/bn/asm/libcrypto-lib-x86_64-gcc.o",
                    "crypto/bn/libcrypto-lib-bn_add.o",
                    "crypto/bn/libcrypto-lib-bn_blind.o",
                    "crypto/bn/libcrypto-lib-bn_const.o",
                    "crypto/bn/libcrypto-lib-bn_ctx.o",
                    "crypto/bn/libcrypto-lib-bn_depr.o",
                    "crypto/bn/libcrypto-lib-bn_dh.o",
                    "crypto/bn/libcrypto-lib-bn_div.o",
                    "crypto/bn/libcrypto-lib-bn_err.o",
                    "crypto/bn/libcrypto-lib-bn_exp.o",
                    "crypto/bn/libcrypto-lib-bn_exp2.o",
                    "crypto/bn/libcrypto-lib-bn_gcd.o",
                    "crypto/bn/libcrypto-lib-bn_gf2m.o",
                    "crypto/bn/libcrypto-lib-bn_intern.o",
                    "crypto/bn/libcrypto-lib-bn_kron.o",
                    "crypto/bn/libcrypto-lib-bn_lib.o",
                    "crypto/bn/libcrypto-lib-bn_mod.o",
                    "crypto/bn/libcrypto-lib-bn_mont.o",
                    "crypto/bn/libcrypto-lib-bn_mpi.o",
                    "crypto/bn/libcrypto-lib-bn_mul.o",
                    "crypto/bn/libcrypto-lib-bn_nist.o",
                    "crypto/bn/libcrypto-lib-bn_prime.o",
                    "crypto/bn/libcrypto-lib-bn_print.o",
                    "crypto/bn/libcrypto-lib-bn_rand.o",
                    "crypto/bn/libcrypto-lib-bn_recp.o",
                    "crypto/bn/libcrypto-lib-bn_rsa_fips186_4.o",
                    "crypto/bn/libcrypto-lib-bn_shift.o",
                    "crypto/bn/libcrypto-lib-bn_sqr.o",
                    "crypto/bn/libcrypto-lib-bn_sqrt.o",
                    "crypto/bn/libcrypto-lib-bn_srp.o",
                    "crypto/bn/libcrypto-lib-bn_word.o",
                    "crypto/bn/libcrypto-lib-bn_x931p.o",
                    "crypto/bn/libcrypto-lib-rsaz-avx2.o",
                    "crypto/bn/libcrypto-lib-rsaz-x86_64.o",
                    "crypto/bn/libcrypto-lib-rsaz_exp.o",
                    "crypto/bn/libcrypto-lib-x86_64-gf2m.o",
                    "crypto/bn/libcrypto-lib-x86_64-mont.o",
                    "crypto/bn/libcrypto-lib-x86_64-mont5.o",
                    "crypto/buffer/libcrypto-lib-buf_err.o",
                    "crypto/buffer/libcrypto-lib-buffer.o",
                    "crypto/camellia/libcrypto-lib-cmll-x86_64.o",
                    "crypto/camellia/libcrypto-lib-cmll_cfb.o",
                    "crypto/camellia/libcrypto-lib-cmll_ctr.o",
                    "crypto/camellia/libcrypto-lib-cmll_ecb.o",
                    "crypto/camellia/libcrypto-lib-cmll_misc.o",
                    "crypto/camellia/libcrypto-lib-cmll_ofb.o",
                    "crypto/cast/libcrypto-lib-c_cfb64.o",
                    "crypto/cast/libcrypto-lib-c_ecb.o",
                    "crypto/cast/libcrypto-lib-c_enc.o",
                    "crypto/cast/libcrypto-lib-c_ofb64.o",
                    "crypto/cast/libcrypto-lib-c_skey.o",
                    "crypto/chacha/libcrypto-lib-chacha-x86_64.o",
                    "crypto/cmac/libcrypto-lib-cm_ameth.o",
                    "crypto/cmac/libcrypto-lib-cm_meth.o",
                    "crypto/cmac/libcrypto-lib-cmac.o",
                    "crypto/cms/libcrypto-lib-cms_asn1.o",
                    "crypto/cms/libcrypto-lib-cms_att.o",
                    "crypto/cms/libcrypto-lib-cms_cd.o",
                    "crypto/cms/libcrypto-lib-cms_dd.o",
                    "crypto/cms/libcrypto-lib-cms_enc.o",
                    "crypto/cms/libcrypto-lib-cms_env.o",
                    "crypto/cms/libcrypto-lib-cms_err.o",
                    "crypto/cms/libcrypto-lib-cms_ess.o",
                    "crypto/cms/libcrypto-lib-cms_io.o",
                    "crypto/cms/libcrypto-lib-cms_kari.o",
                    "crypto/cms/libcrypto-lib-cms_lib.o",
                    "crypto/cms/libcrypto-lib-cms_pwri.o",
                    "crypto/cms/libcrypto-lib-cms_sd.o",
                    "crypto/cms/libcrypto-lib-cms_smime.o",
                    "crypto/comp/libcrypto-lib-c_zlib.o",
                    "crypto/comp/libcrypto-lib-comp_err.o",
                    "crypto/comp/libcrypto-lib-comp_lib.o",
                    "crypto/conf/libcrypto-lib-conf_api.o",
                    "crypto/conf/libcrypto-lib-conf_def.o",
                    "crypto/conf/libcrypto-lib-conf_err.o",
                    "crypto/conf/libcrypto-lib-conf_lib.o",
                    "crypto/conf/libcrypto-lib-conf_mall.o",
                    "crypto/conf/libcrypto-lib-conf_mod.o",
                    "crypto/conf/libcrypto-lib-conf_sap.o",
                    "crypto/conf/libcrypto-lib-conf_ssl.o",
                    "crypto/crmf/libcrypto-lib-crmf_asn.o",
                    "crypto/crmf/libcrypto-lib-crmf_err.o",
                    "crypto/crmf/libcrypto-lib-crmf_lib.o",
                    "crypto/crmf/libcrypto-lib-crmf_pbm.o",
                    "crypto/ct/libcrypto-lib-ct_b64.o",
                    "crypto/ct/libcrypto-lib-ct_err.o",
                    "crypto/ct/libcrypto-lib-ct_log.o",
                    "crypto/ct/libcrypto-lib-ct_oct.o",
                    "crypto/ct/libcrypto-lib-ct_policy.o",
                    "crypto/ct/libcrypto-lib-ct_prn.o",
                    "crypto/ct/libcrypto-lib-ct_sct.o",
                    "crypto/ct/libcrypto-lib-ct_sct_ctx.o",
                    "crypto/ct/libcrypto-lib-ct_vfy.o",
                    "crypto/ct/libcrypto-lib-ct_x509v3.o",
                    "crypto/des/libcrypto-lib-cbc_cksm.o",
                    "crypto/des/libcrypto-lib-cbc_enc.o",
                    "crypto/des/libcrypto-lib-cfb64ede.o",
                    "crypto/des/libcrypto-lib-cfb64enc.o",
                    "crypto/des/libcrypto-lib-cfb_enc.o",
                    "crypto/des/libcrypto-lib-des_enc.o",
                    "crypto/des/libcrypto-lib-ecb3_enc.o",
                    "crypto/des/libcrypto-lib-ecb_enc.o",
                    "crypto/des/libcrypto-lib-fcrypt.o",
                    "crypto/des/libcrypto-lib-fcrypt_b.o",
                    "crypto/des/libcrypto-lib-ofb64ede.o",
                    "crypto/des/libcrypto-lib-ofb64enc.o",
                    "crypto/des/libcrypto-lib-ofb_enc.o",
                    "crypto/des/libcrypto-lib-pcbc_enc.o",
                    "crypto/des/libcrypto-lib-qud_cksm.o",
                    "crypto/des/libcrypto-lib-rand_key.o",
                    "crypto/des/libcrypto-lib-set_key.o",
                    "crypto/des/libcrypto-lib-str2key.o",
                    "crypto/des/libcrypto-lib-xcbc_enc.o",
                    "crypto/dh/libcrypto-lib-dh_ameth.o",
                    "crypto/dh/libcrypto-lib-dh_asn1.o",
                    "crypto/dh/libcrypto-lib-dh_check.o",
                    "crypto/dh/libcrypto-lib-dh_depr.o",
                    "crypto/dh/libcrypto-lib-dh_err.o",
                    "crypto/dh/libcrypto-lib-dh_gen.o",
                    "crypto/dh/libcrypto-lib-dh_kdf.o",
                    "crypto/dh/libcrypto-lib-dh_key.o",
                    "crypto/dh/libcrypto-lib-dh_lib.o",
                    "crypto/dh/libcrypto-lib-dh_meth.o",
                    "crypto/dh/libcrypto-lib-dh_pmeth.o",
                    "crypto/dh/libcrypto-lib-dh_prn.o",
                    "crypto/dh/libcrypto-lib-dh_rfc5114.o",
                    "crypto/dh/libcrypto-lib-dh_rfc7919.o",
                    "crypto/dsa/libcrypto-lib-dsa_ameth.o",
                    "crypto/dsa/libcrypto-lib-dsa_asn1.o",
                    "crypto/dsa/libcrypto-lib-dsa_depr.o",
                    "crypto/dsa/libcrypto-lib-dsa_err.o",
                    "crypto/dsa/libcrypto-lib-dsa_gen.o",
                    "crypto/dsa/libcrypto-lib-dsa_key.o",
                    "crypto/dsa/libcrypto-lib-dsa_lib.o",
                    "crypto/dsa/libcrypto-lib-dsa_meth.o",
                    "crypto/dsa/libcrypto-lib-dsa_ossl.o",
                    "crypto/dsa/libcrypto-lib-dsa_pmeth.o",
                    "crypto/dsa/libcrypto-lib-dsa_prn.o",
                    "crypto/dsa/libcrypto-lib-dsa_sign.o",
                    "crypto/dsa/libcrypto-lib-dsa_vrf.o",
                    "crypto/dso/libcrypto-lib-dso_dl.o",
                    "crypto/dso/libcrypto-lib-dso_dlfcn.o",
                    "crypto/dso/libcrypto-lib-dso_err.o",
                    "crypto/dso/libcrypto-lib-dso_lib.o",
                    "crypto/dso/libcrypto-lib-dso_openssl.o",
                    "crypto/dso/libcrypto-lib-dso_vms.o",
                    "crypto/dso/libcrypto-lib-dso_win32.o",
                    "crypto/ec/curve448/arch_32/libcrypto-lib-f_impl.o",
                    "crypto/ec/curve448/libcrypto-lib-curve448.o",
                    "crypto/ec/curve448/libcrypto-lib-curve448_tables.o",
                    "crypto/ec/curve448/libcrypto-lib-eddsa.o",
                    "crypto/ec/curve448/libcrypto-lib-f_generic.o",
                    "crypto/ec/curve448/libcrypto-lib-scalar.o",
                    "crypto/ec/libcrypto-lib-curve25519.o",
                    "crypto/ec/libcrypto-lib-ec2_oct.o",
                    "crypto/ec/libcrypto-lib-ec2_smpl.o",
                    "crypto/ec/libcrypto-lib-ec_ameth.o",
                    "crypto/ec/libcrypto-lib-ec_asn1.o",
                    "crypto/ec/libcrypto-lib-ec_check.o",
                    "crypto/ec/libcrypto-lib-ec_curve.o",
                    "crypto/ec/libcrypto-lib-ec_cvt.o",
                    "crypto/ec/libcrypto-lib-ec_err.o",
                    "crypto/ec/libcrypto-lib-ec_key.o",
                    "crypto/ec/libcrypto-lib-ec_kmeth.o",
                    "crypto/ec/libcrypto-lib-ec_lib.o",
                    "crypto/ec/libcrypto-lib-ec_mult.o",
                    "crypto/ec/libcrypto-lib-ec_oct.o",
                    "crypto/ec/libcrypto-lib-ec_pmeth.o",
                    "crypto/ec/libcrypto-lib-ec_print.o",
                    "crypto/ec/libcrypto-lib-ecdh_kdf.o",
                    "crypto/ec/libcrypto-lib-ecdh_ossl.o",
                    "crypto/ec/libcrypto-lib-ecdsa_ossl.o",
                    "crypto/ec/libcrypto-lib-ecdsa_sign.o",
                    "crypto/ec/libcrypto-lib-ecdsa_vrf.o",
                    "crypto/ec/libcrypto-lib-eck_prn.o",
                    "crypto/ec/libcrypto-lib-ecp_mont.o",
                    "crypto/ec/libcrypto-lib-ecp_nist.o",
                    "crypto/ec/libcrypto-lib-ecp_nistp224.o",
                    "crypto/ec/libcrypto-lib-ecp_nistp256.o",
                    "crypto/ec/libcrypto-lib-ecp_nistp521.o",
                    "crypto/ec/libcrypto-lib-ecp_nistputil.o",
                    "crypto/ec/libcrypto-lib-ecp_nistz256-x86_64.o",
                    "crypto/ec/libcrypto-lib-ecp_nistz256.o",
                    "crypto/ec/libcrypto-lib-ecp_oct.o",
                    "crypto/ec/libcrypto-lib-ecp_smpl.o",
                    "crypto/ec/libcrypto-lib-ecx_meth.o",
                    "crypto/ec/libcrypto-lib-x25519-x86_64.o",
                    "crypto/engine/libcrypto-lib-eng_all.o",
                    "crypto/engine/libcrypto-lib-eng_cnf.o",
                    "crypto/engine/libcrypto-lib-eng_ctrl.o",
                    "crypto/engine/libcrypto-lib-eng_dyn.o",
                    "crypto/engine/libcrypto-lib-eng_err.o",
                    "crypto/engine/libcrypto-lib-eng_fat.o",
                    "crypto/engine/libcrypto-lib-eng_init.o",
                    "crypto/engine/libcrypto-lib-eng_lib.o",
                    "crypto/engine/libcrypto-lib-eng_list.o",
                    "crypto/engine/libcrypto-lib-eng_openssl.o",
                    "crypto/engine/libcrypto-lib-eng_pkey.o",
                    "crypto/engine/libcrypto-lib-eng_rdrand.o",
                    "crypto/engine/libcrypto-lib-eng_table.o",
                    "crypto/engine/libcrypto-lib-tb_asnmth.o",
                    "crypto/engine/libcrypto-lib-tb_cipher.o",
                    "crypto/engine/libcrypto-lib-tb_dh.o",
                    "crypto/engine/libcrypto-lib-tb_digest.o",
                    "crypto/engine/libcrypto-lib-tb_dsa.o",
                    "crypto/engine/libcrypto-lib-tb_eckey.o",
                    "crypto/engine/libcrypto-lib-tb_pkmeth.o",
                    "crypto/engine/libcrypto-lib-tb_rand.o",
                    "crypto/engine/libcrypto-lib-tb_rsa.o",
                    "crypto/err/libcrypto-lib-err.o",
                    "crypto/err/libcrypto-lib-err_all.o",
                    "crypto/err/libcrypto-lib-err_prn.o",
                    "crypto/ess/libcrypto-lib-ess_asn1.o",
                    "crypto/ess/libcrypto-lib-ess_err.o",
                    "crypto/ess/libcrypto-lib-ess_lib.o",
                    "crypto/evp/libcrypto-lib-bio_b64.o",
                    "crypto/evp/libcrypto-lib-bio_enc.o",
                    "crypto/evp/libcrypto-lib-bio_md.o",
                    "crypto/evp/libcrypto-lib-bio_ok.o",
                    "crypto/evp/libcrypto-lib-c_allc.o",
                    "crypto/evp/libcrypto-lib-c_alld.o",
                    "crypto/evp/libcrypto-lib-c_allm.o",
                    "crypto/evp/libcrypto-lib-cmeth_lib.o",
                    "crypto/evp/libcrypto-lib-digest.o",
                    "crypto/evp/libcrypto-lib-e_aes.o",
                    "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha1.o",
                    "crypto/evp/libcrypto-lib-e_aes_cbc_hmac_sha256.o",
                    "crypto/evp/libcrypto-lib-e_aria.o",
                    "crypto/evp/libcrypto-lib-e_bf.o",
                    "crypto/evp/libcrypto-lib-e_camellia.o",
                    "crypto/evp/libcrypto-lib-e_cast.o",
                    "crypto/evp/libcrypto-lib-e_chacha20_poly1305.o",
                    "crypto/evp/libcrypto-lib-e_des.o",
                    "crypto/evp/libcrypto-lib-e_des3.o",
                    "crypto/evp/libcrypto-lib-e_idea.o",
                    "crypto/evp/libcrypto-lib-e_null.o",
                    "crypto/evp/libcrypto-lib-e_old.o",
                    "crypto/evp/libcrypto-lib-e_rc2.o",
                    "crypto/evp/libcrypto-lib-e_rc4.o",
                    "crypto/evp/libcrypto-lib-e_rc4_hmac_md5.o",
                    "crypto/evp/libcrypto-lib-e_rc5.o",
                    "crypto/evp/libcrypto-lib-e_seed.o",
                    "crypto/evp/libcrypto-lib-e_sm4.o",
                    "crypto/evp/libcrypto-lib-e_xcbc_d.o",
                    "crypto/evp/libcrypto-lib-encode.o",
                    "crypto/evp/libcrypto-lib-evp_cnf.o",
                    "crypto/evp/libcrypto-lib-evp_enc.o",
                    "crypto/evp/libcrypto-lib-evp_err.o",
                    "crypto/evp/libcrypto-lib-evp_fetch.o",
                    "crypto/evp/libcrypto-lib-evp_key.o",
                    "crypto/evp/libcrypto-lib-evp_lib.o",
                    "crypto/evp/libcrypto-lib-evp_pbe.o",
                    "crypto/evp/libcrypto-lib-evp_pkey.o",
                    "crypto/evp/libcrypto-lib-kdf_lib.o",
                    "crypto/evp/libcrypto-lib-m_md2.o",
                    "crypto/evp/libcrypto-lib-m_md4.o",
                    "crypto/evp/libcrypto-lib-m_md5.o",
                    "crypto/evp/libcrypto-lib-m_md5_sha1.o",
                    "crypto/evp/libcrypto-lib-m_mdc2.o",
                    "crypto/evp/libcrypto-lib-m_null.o",
                    "crypto/evp/libcrypto-lib-m_ripemd.o",
                    "crypto/evp/libcrypto-lib-m_sha1.o",
                    "crypto/evp/libcrypto-lib-m_sha3.o",
                    "crypto/evp/libcrypto-lib-m_sigver.o",
                    "crypto/evp/libcrypto-lib-m_wp.o",
                    "crypto/evp/libcrypto-lib-mac_lib.o",
                    "crypto/evp/libcrypto-lib-names.o",
                    "crypto/evp/libcrypto-lib-p5_crpt.o",
                    "crypto/evp/libcrypto-lib-p5_crpt2.o",
                    "crypto/evp/libcrypto-lib-p_dec.o",
                    "crypto/evp/libcrypto-lib-p_enc.o",
                    "crypto/evp/libcrypto-lib-p_lib.o",
                    "crypto/evp/libcrypto-lib-p_open.o",
                    "crypto/evp/libcrypto-lib-p_seal.o",
                    "crypto/evp/libcrypto-lib-p_sign.o",
                    "crypto/evp/libcrypto-lib-p_verify.o",
                    "crypto/evp/libcrypto-lib-pbe_scrypt.o",
                    "crypto/evp/libcrypto-lib-pkey_kdf.o",
                    "crypto/evp/libcrypto-lib-pkey_mac.o",
                    "crypto/evp/libcrypto-lib-pmeth_fn.o",
                    "crypto/evp/libcrypto-lib-pmeth_gn.o",
                    "crypto/evp/libcrypto-lib-pmeth_lib.o",
                    "crypto/gmac/libcrypto-lib-gmac.o",
                    "crypto/hmac/libcrypto-lib-hm_ameth.o",
                    "crypto/hmac/libcrypto-lib-hm_meth.o",
                    "crypto/hmac/libcrypto-lib-hmac.o",
                    "crypto/idea/libcrypto-lib-i_cbc.o",
                    "crypto/idea/libcrypto-lib-i_cfb64.o",
                    "crypto/idea/libcrypto-lib-i_ecb.o",
                    "crypto/idea/libcrypto-lib-i_ofb64.o",
                    "crypto/idea/libcrypto-lib-i_skey.o",
                    "crypto/kdf/libcrypto-lib-hkdf.o",
                    "crypto/kdf/libcrypto-lib-kdf_err.o",
                    "crypto/kdf/libcrypto-lib-kdf_util.o",
                    "crypto/kdf/libcrypto-lib-pbkdf2.o",
                    "crypto/kdf/libcrypto-lib-scrypt.o",
                    "crypto/kdf/libcrypto-lib-sshkdf.o",
                    "crypto/kdf/libcrypto-lib-sskdf.o",
                    "crypto/kdf/libcrypto-lib-tls1_prf.o",
                    "crypto/kmac/libcrypto-lib-kmac.o",
                    "crypto/lhash/libcrypto-lib-lh_stats.o",
                    "crypto/lhash/libcrypto-lib-lhash.o",
                    "crypto/libcrypto-lib-context.o",
                    "crypto/libcrypto-lib-core_fetch.o",
                    "crypto/libcrypto-lib-cpt_err.o",
                    "crypto/libcrypto-lib-cryptlib.o",
                    "crypto/libcrypto-lib-ctype.o",
                    "crypto/libcrypto-lib-cversion.o",
                    "crypto/libcrypto-lib-ebcdic.o",
                    "crypto/libcrypto-lib-ex_data.o",
                    "crypto/libcrypto-lib-getenv.o",
                    "crypto/libcrypto-lib-init.o",
                    "crypto/libcrypto-lib-mem.o",
                    "crypto/libcrypto-lib-mem_dbg.o",
                    "crypto/libcrypto-lib-mem_sec.o",
                    "crypto/libcrypto-lib-o_dir.o",
                    "crypto/libcrypto-lib-o_fips.o",
                    "crypto/libcrypto-lib-o_fopen.o",
                    "crypto/libcrypto-lib-o_init.o",
                    "crypto/libcrypto-lib-o_str.o",
                    "crypto/libcrypto-lib-o_time.o",
                    "crypto/libcrypto-lib-params.o",
                    "crypto/libcrypto-lib-provider.o",
                    "crypto/libcrypto-lib-provider_conf.o",
                    "crypto/libcrypto-lib-provider_core.o",
                    "crypto/libcrypto-lib-provider_predefined.o",
                    "crypto/libcrypto-lib-sparse_array.o",
                    "crypto/libcrypto-lib-threads_none.o",
                    "crypto/libcrypto-lib-threads_pthread.o",
                    "crypto/libcrypto-lib-threads_win.o",
                    "crypto/libcrypto-lib-trace.o",
                    "crypto/libcrypto-lib-uid.o",
                    "crypto/libcrypto-lib-x86_64cpuid.o",
                    "crypto/md4/libcrypto-lib-md4_dgst.o",
                    "crypto/md4/libcrypto-lib-md4_one.o",
                    "crypto/md5/libcrypto-lib-md5-x86_64.o",
                    "crypto/md5/libcrypto-lib-md5_dgst.o",
                    "crypto/md5/libcrypto-lib-md5_one.o",
                    "crypto/mdc2/libcrypto-lib-mdc2_one.o",
                    "crypto/mdc2/libcrypto-lib-mdc2dgst.o",
                    "crypto/modes/libcrypto-lib-aesni-gcm-x86_64.o",
                    "crypto/modes/libcrypto-lib-cbc128.o",
                    "crypto/modes/libcrypto-lib-ccm128.o",
                    "crypto/modes/libcrypto-lib-cfb128.o",
                    "crypto/modes/libcrypto-lib-ctr128.o",
                    "crypto/modes/libcrypto-lib-cts128.o",
                    "crypto/modes/libcrypto-lib-gcm128.o",
                    "crypto/modes/libcrypto-lib-ghash-x86_64.o",
                    "crypto/modes/libcrypto-lib-ocb128.o",
                    "crypto/modes/libcrypto-lib-ofb128.o",
                    "crypto/modes/libcrypto-lib-siv128.o",
                    "crypto/modes/libcrypto-lib-wrap128.o",
                    "crypto/modes/libcrypto-lib-xts128.o",
                    "crypto/objects/libcrypto-lib-o_names.o",
                    "crypto/objects/libcrypto-lib-obj_dat.o",
                    "crypto/objects/libcrypto-lib-obj_err.o",
                    "crypto/objects/libcrypto-lib-obj_lib.o",
                    "crypto/objects/libcrypto-lib-obj_xref.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_asn.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_cl.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_err.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_ext.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_ht.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_lib.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_prn.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_srv.o",
                    "crypto/ocsp/libcrypto-lib-ocsp_vfy.o",
                    "crypto/ocsp/libcrypto-lib-v3_ocsp.o",
                    "crypto/pem/libcrypto-lib-pem_all.o",
                    "crypto/pem/libcrypto-lib-pem_err.o",
                    "crypto/pem/libcrypto-lib-pem_info.o",
                    "crypto/pem/libcrypto-lib-pem_lib.o",
                    "crypto/pem/libcrypto-lib-pem_oth.o",
                    "crypto/pem/libcrypto-lib-pem_pk8.o",
                    "crypto/pem/libcrypto-lib-pem_pkey.o",
                    "crypto/pem/libcrypto-lib-pem_sign.o",
                    "crypto/pem/libcrypto-lib-pem_x509.o",
                    "crypto/pem/libcrypto-lib-pem_xaux.o",
                    "crypto/pem/libcrypto-lib-pvkfmt.o",
                    "crypto/pkcs12/libcrypto-lib-p12_add.o",
                    "crypto/pkcs12/libcrypto-lib-p12_asn.o",
                    "crypto/pkcs12/libcrypto-lib-p12_attr.o",
                    "crypto/pkcs12/libcrypto-lib-p12_crpt.o",
                    "crypto/pkcs12/libcrypto-lib-p12_crt.o",
                    "crypto/pkcs12/libcrypto-lib-p12_decr.o",
                    "crypto/pkcs12/libcrypto-lib-p12_init.o",
                    "crypto/pkcs12/libcrypto-lib-p12_key.o",
                    "crypto/pkcs12/libcrypto-lib-p12_kiss.o",
                    "crypto/pkcs12/libcrypto-lib-p12_mutl.o",
                    "crypto/pkcs12/libcrypto-lib-p12_npas.o",
                    "crypto/pkcs12/libcrypto-lib-p12_p8d.o",
                    "crypto/pkcs12/libcrypto-lib-p12_p8e.o",
                    "crypto/pkcs12/libcrypto-lib-p12_sbag.o",
                    "crypto/pkcs12/libcrypto-lib-p12_utl.o",
                    "crypto/pkcs12/libcrypto-lib-pk12err.o",
                    "crypto/pkcs7/libcrypto-lib-bio_pk7.o",
                    "crypto/pkcs7/libcrypto-lib-pk7_asn1.o",
                    "crypto/pkcs7/libcrypto-lib-pk7_attr.o",
                    "crypto/pkcs7/libcrypto-lib-pk7_doit.o",
                    "crypto/pkcs7/libcrypto-lib-pk7_lib.o",
                    "crypto/pkcs7/libcrypto-lib-pk7_mime.o",
                    "crypto/pkcs7/libcrypto-lib-pk7_smime.o",
                    "crypto/pkcs7/libcrypto-lib-pkcs7err.o",
                    "crypto/poly1305/libcrypto-lib-poly1305-x86_64.o",
                    "crypto/poly1305/libcrypto-lib-poly1305.o",
                    "crypto/poly1305/libcrypto-lib-poly1305_ameth.o",
                    "crypto/poly1305/libcrypto-lib-poly1305_meth.o",
                    "crypto/property/libcrypto-lib-defn_cache.o",
                    "crypto/property/libcrypto-lib-property.o",
                    "crypto/property/libcrypto-lib-property_err.o",
                    "crypto/property/libcrypto-lib-property_parse.o",
                    "crypto/property/libcrypto-lib-property_string.o",
                    "crypto/rand/libcrypto-lib-drbg_ctr.o",
                    "crypto/rand/libcrypto-lib-drbg_hash.o",
                    "crypto/rand/libcrypto-lib-drbg_hmac.o",
                    "crypto/rand/libcrypto-lib-drbg_lib.o",
                    "crypto/rand/libcrypto-lib-rand_crng_test.o",
                    "crypto/rand/libcrypto-lib-rand_egd.o",
                    "crypto/rand/libcrypto-lib-rand_err.o",
                    "crypto/rand/libcrypto-lib-rand_lib.o",
                    "crypto/rand/libcrypto-lib-rand_unix.o",
                    "crypto/rand/libcrypto-lib-rand_vms.o",
                    "crypto/rand/libcrypto-lib-rand_win.o",
                    "crypto/rand/libcrypto-lib-randfile.o",
                    "crypto/rc2/libcrypto-lib-rc2_cbc.o",
                    "crypto/rc2/libcrypto-lib-rc2_ecb.o",
                    "crypto/rc2/libcrypto-lib-rc2_skey.o",
                    "crypto/rc2/libcrypto-lib-rc2cfb64.o",
                    "crypto/rc2/libcrypto-lib-rc2ofb64.o",
                    "crypto/rc4/libcrypto-lib-rc4-md5-x86_64.o",
                    "crypto/rc4/libcrypto-lib-rc4-x86_64.o",
                    "crypto/ripemd/libcrypto-lib-rmd_dgst.o",
                    "crypto/ripemd/libcrypto-lib-rmd_one.o",
                    "crypto/rsa/libcrypto-lib-rsa_ameth.o",
                    "crypto/rsa/libcrypto-lib-rsa_asn1.o",
                    "crypto/rsa/libcrypto-lib-rsa_chk.o",
                    "crypto/rsa/libcrypto-lib-rsa_crpt.o",
                    "crypto/rsa/libcrypto-lib-rsa_depr.o",
                    "crypto/rsa/libcrypto-lib-rsa_err.o",
                    "crypto/rsa/libcrypto-lib-rsa_gen.o",
                    "crypto/rsa/libcrypto-lib-rsa_lib.o",
                    "crypto/rsa/libcrypto-lib-rsa_meth.o",
                    "crypto/rsa/libcrypto-lib-rsa_mp.o",
                    "crypto/rsa/libcrypto-lib-rsa_none.o",
                    "crypto/rsa/libcrypto-lib-rsa_oaep.o",
                    "crypto/rsa/libcrypto-lib-rsa_ossl.o",
                    "crypto/rsa/libcrypto-lib-rsa_pk1.o",
                    "crypto/rsa/libcrypto-lib-rsa_pmeth.o",
                    "crypto/rsa/libcrypto-lib-rsa_prn.o",
                    "crypto/rsa/libcrypto-lib-rsa_pss.o",
                    "crypto/rsa/libcrypto-lib-rsa_saos.o",
                    "crypto/rsa/libcrypto-lib-rsa_sign.o",
                    "crypto/rsa/libcrypto-lib-rsa_sp800_56b_check.o",
                    "crypto/rsa/libcrypto-lib-rsa_sp800_56b_gen.o",
                    "crypto/rsa/libcrypto-lib-rsa_ssl.o",
                    "crypto/rsa/libcrypto-lib-rsa_x931.o",
                    "crypto/rsa/libcrypto-lib-rsa_x931g.o",
                    "crypto/seed/libcrypto-lib-seed.o",
                    "crypto/seed/libcrypto-lib-seed_cbc.o",
                    "crypto/seed/libcrypto-lib-seed_cfb.o",
                    "crypto/seed/libcrypto-lib-seed_ecb.o",
                    "crypto/seed/libcrypto-lib-seed_ofb.o",
                    "crypto/sha/libcrypto-lib-keccak1600-x86_64.o",
                    "crypto/sha/libcrypto-lib-sha1-mb-x86_64.o",
                    "crypto/sha/libcrypto-lib-sha1-x86_64.o",
                    "crypto/sha/libcrypto-lib-sha1_one.o",
                    "crypto/sha/libcrypto-lib-sha1dgst.o",
                    "crypto/sha/libcrypto-lib-sha256-mb-x86_64.o",
                    "crypto/sha/libcrypto-lib-sha256-x86_64.o",
                    "crypto/sha/libcrypto-lib-sha256.o",
                    "crypto/sha/libcrypto-lib-sha512-x86_64.o",
                    "crypto/sha/libcrypto-lib-sha512.o",
                    "crypto/siphash/libcrypto-lib-siphash.o",
                    "crypto/siphash/libcrypto-lib-siphash_ameth.o",
                    "crypto/siphash/libcrypto-lib-siphash_meth.o",
                    "crypto/sm2/libcrypto-lib-sm2_crypt.o",
                    "crypto/sm2/libcrypto-lib-sm2_err.o",
                    "crypto/sm2/libcrypto-lib-sm2_pmeth.o",
                    "crypto/sm2/libcrypto-lib-sm2_sign.o",
                    "crypto/sm3/libcrypto-lib-m_sm3.o",
                    "crypto/sm3/libcrypto-lib-sm3.o",
                    "crypto/sm4/libcrypto-lib-sm4.o",
                    "crypto/srp/libcrypto-lib-srp_lib.o",
                    "crypto/srp/libcrypto-lib-srp_vfy.o",
                    "crypto/stack/libcrypto-lib-stack.o",
                    "crypto/store/libcrypto-lib-loader_file.o",
                    "crypto/store/libcrypto-lib-store_err.o",
                    "crypto/store/libcrypto-lib-store_init.o",
                    "crypto/store/libcrypto-lib-store_lib.o",
                    "crypto/store/libcrypto-lib-store_register.o",
                    "crypto/store/libcrypto-lib-store_strings.o",
                    "crypto/ts/libcrypto-lib-ts_asn1.o",
                    "crypto/ts/libcrypto-lib-ts_conf.o",
                    "crypto/ts/libcrypto-lib-ts_err.o",
                    "crypto/ts/libcrypto-lib-ts_lib.o",
                    "crypto/ts/libcrypto-lib-ts_req_print.o",
                    "crypto/ts/libcrypto-lib-ts_req_utils.o",
                    "crypto/ts/libcrypto-lib-ts_rsp_print.o",
                    "crypto/ts/libcrypto-lib-ts_rsp_sign.o",
                    "crypto/ts/libcrypto-lib-ts_rsp_utils.o",
                    "crypto/ts/libcrypto-lib-ts_rsp_verify.o",
                    "crypto/ts/libcrypto-lib-ts_verify_ctx.o",
                    "crypto/txt_db/libcrypto-lib-txt_db.o",
                    "crypto/ui/libcrypto-lib-ui_err.o",
                    "crypto/ui/libcrypto-lib-ui_lib.o",
                    "crypto/ui/libcrypto-lib-ui_null.o",
                    "crypto/ui/libcrypto-lib-ui_openssl.o",
                    "crypto/ui/libcrypto-lib-ui_util.o",
                    "crypto/whrlpool/libcrypto-lib-wp-x86_64.o",
                    "crypto/whrlpool/libcrypto-lib-wp_dgst.o",
                    "crypto/x509/libcrypto-lib-by_dir.o",
                    "crypto/x509/libcrypto-lib-by_file.o",
                    "crypto/x509/libcrypto-lib-t_crl.o",
                    "crypto/x509/libcrypto-lib-t_req.o",
                    "crypto/x509/libcrypto-lib-t_x509.o",
                    "crypto/x509/libcrypto-lib-x509_att.o",
                    "crypto/x509/libcrypto-lib-x509_cmp.o",
                    "crypto/x509/libcrypto-lib-x509_d2.o",
                    "crypto/x509/libcrypto-lib-x509_def.o",
                    "crypto/x509/libcrypto-lib-x509_err.o",
                    "crypto/x509/libcrypto-lib-x509_ext.o",
                    "crypto/x509/libcrypto-lib-x509_lu.o",
                    "crypto/x509/libcrypto-lib-x509_meth.o",
                    "crypto/x509/libcrypto-lib-x509_obj.o",
                    "crypto/x509/libcrypto-lib-x509_r2x.o",
                    "crypto/x509/libcrypto-lib-x509_req.o",
                    "crypto/x509/libcrypto-lib-x509_set.o",
                    "crypto/x509/libcrypto-lib-x509_trs.o",
                    "crypto/x509/libcrypto-lib-x509_txt.o",
                    "crypto/x509/libcrypto-lib-x509_v3.o",
                    "crypto/x509/libcrypto-lib-x509_vfy.o",
                    "crypto/x509/libcrypto-lib-x509_vpm.o",
                    "crypto/x509/libcrypto-lib-x509cset.o",
                    "crypto/x509/libcrypto-lib-x509name.o",
                    "crypto/x509/libcrypto-lib-x509rset.o",
                    "crypto/x509/libcrypto-lib-x509spki.o",
                    "crypto/x509/libcrypto-lib-x509type.o",
                    "crypto/x509/libcrypto-lib-x_all.o",
                    "crypto/x509/libcrypto-lib-x_attrib.o",
                    "crypto/x509/libcrypto-lib-x_crl.o",
                    "crypto/x509/libcrypto-lib-x_exten.o",
                    "crypto/x509/libcrypto-lib-x_name.o",
                    "crypto/x509/libcrypto-lib-x_pubkey.o",
                    "crypto/x509/libcrypto-lib-x_req.o",
                    "crypto/x509/libcrypto-lib-x_x509.o",
                    "crypto/x509/libcrypto-lib-x_x509a.o",
                    "crypto/x509v3/libcrypto-lib-pcy_cache.o",
                    "crypto/x509v3/libcrypto-lib-pcy_data.o",
                    "crypto/x509v3/libcrypto-lib-pcy_lib.o",
                    "crypto/x509v3/libcrypto-lib-pcy_map.o",
                    "crypto/x509v3/libcrypto-lib-pcy_node.o",
                    "crypto/x509v3/libcrypto-lib-pcy_tree.o",
                    "crypto/x509v3/libcrypto-lib-v3_addr.o",
                    "crypto/x509v3/libcrypto-lib-v3_admis.o",
                    "crypto/x509v3/libcrypto-lib-v3_akey.o",
                    "crypto/x509v3/libcrypto-lib-v3_akeya.o",
                    "crypto/x509v3/libcrypto-lib-v3_alt.o",
                    "crypto/x509v3/libcrypto-lib-v3_asid.o",
                    "crypto/x509v3/libcrypto-lib-v3_bcons.o",
                    "crypto/x509v3/libcrypto-lib-v3_bitst.o",
                    "crypto/x509v3/libcrypto-lib-v3_conf.o",
                    "crypto/x509v3/libcrypto-lib-v3_cpols.o",
                    "crypto/x509v3/libcrypto-lib-v3_crld.o",
                    "crypto/x509v3/libcrypto-lib-v3_enum.o",
                    "crypto/x509v3/libcrypto-lib-v3_extku.o",
                    "crypto/x509v3/libcrypto-lib-v3_genn.o",
                    "crypto/x509v3/libcrypto-lib-v3_ia5.o",
                    "crypto/x509v3/libcrypto-lib-v3_info.o",
                    "crypto/x509v3/libcrypto-lib-v3_int.o",
                    "crypto/x509v3/libcrypto-lib-v3_lib.o",
                    "crypto/x509v3/libcrypto-lib-v3_ncons.o",
                    "crypto/x509v3/libcrypto-lib-v3_pci.o",
                    "crypto/x509v3/libcrypto-lib-v3_pcia.o",
                    "crypto/x509v3/libcrypto-lib-v3_pcons.o",
                    "crypto/x509v3/libcrypto-lib-v3_pku.o",
                    "crypto/x509v3/libcrypto-lib-v3_pmaps.o",
                    "crypto/x509v3/libcrypto-lib-v3_prn.o",
                    "crypto/x509v3/libcrypto-lib-v3_purp.o",
                    "crypto/x509v3/libcrypto-lib-v3_skey.o",
                    "crypto/x509v3/libcrypto-lib-v3_sxnet.o",
                    "crypto/x509v3/libcrypto-lib-v3_tlsf.o",
                    "crypto/x509v3/libcrypto-lib-v3_utl.o",
                    "crypto/x509v3/libcrypto-lib-v3err.o",
                    "providers/common/digests/libcrypto-lib-sha2.o",
                    "providers/default/libcrypto-lib-defltprov.o",
                ],
            "libssl" =>
                [
                    "ssl/libssl-lib-bio_ssl.o",
                    "ssl/libssl-lib-d1_lib.o",
                    "ssl/libssl-lib-d1_msg.o",
                    "ssl/libssl-lib-d1_srtp.o",
                    "ssl/libssl-lib-methods.o",
                    "ssl/libssl-lib-packet.o",
                    "ssl/libssl-lib-pqueue.o",
                    "ssl/libssl-lib-s3_cbc.o",
                    "ssl/libssl-lib-s3_enc.o",
                    "ssl/libssl-lib-s3_lib.o",
                    "ssl/libssl-lib-s3_msg.o",
                    "ssl/libssl-lib-ssl_asn1.o",
                    "ssl/libssl-lib-ssl_cert.o",
                    "ssl/libssl-lib-ssl_ciph.o",
                    "ssl/libssl-lib-ssl_conf.o",
                    "ssl/libssl-lib-ssl_err.o",
                    "ssl/libssl-lib-ssl_init.o",
                    "ssl/libssl-lib-ssl_lib.o",
                    "ssl/libssl-lib-ssl_mcnf.o",
                    "ssl/libssl-lib-ssl_rsa.o",
                    "ssl/libssl-lib-ssl_sess.o",
                    "ssl/libssl-lib-ssl_stat.o",
                    "ssl/libssl-lib-ssl_txt.o",
                    "ssl/libssl-lib-ssl_utst.o",
                    "ssl/libssl-lib-t1_enc.o",
                    "ssl/libssl-lib-t1_lib.o",
                    "ssl/libssl-lib-t1_trce.o",
                    "ssl/libssl-lib-tls13_enc.o",
                    "ssl/libssl-lib-tls_srp.o",
                    "ssl/record/libssl-lib-dtls1_bitmap.o",
                    "ssl/record/libssl-lib-rec_layer_d1.o",
                    "ssl/record/libssl-lib-rec_layer_s3.o",
                    "ssl/record/libssl-lib-ssl3_buffer.o",
                    "ssl/record/libssl-lib-ssl3_record.o",
                    "ssl/record/libssl-lib-ssl3_record_tls13.o",
                    "ssl/statem/libssl-lib-extensions.o",
                    "ssl/statem/libssl-lib-extensions_clnt.o",
                    "ssl/statem/libssl-lib-extensions_cust.o",
                    "ssl/statem/libssl-lib-extensions_srvr.o",
                    "ssl/statem/libssl-lib-statem.o",
                    "ssl/statem/libssl-lib-statem_clnt.o",
                    "ssl/statem/libssl-lib-statem_dtls.o",
                    "ssl/statem/libssl-lib-statem_lib.o",
                    "ssl/statem/libssl-lib-statem_srvr.o",
                ],
            "providers/common/digests/fips-dso-sha2.o" =>
                [
                    "providers/common/digests/sha2.c",
                ],
            "providers/common/digests/libcrypto-lib-sha2.o" =>
                [
                    "providers/common/digests/sha2.c",
                ],
            "providers/common/digests/libcrypto-shlib-sha2.o" =>
                [
                    "providers/common/digests/sha2.c",
                ],
            "providers/default/libcrypto-lib-defltprov.o" =>
                [
                    "providers/default/defltprov.c",
                ],
            "providers/default/libcrypto-shlib-defltprov.o" =>
                [
                    "providers/default/defltprov.c",
                ],
            "providers/fips" =>
                [
                    "crypto/fips-dso-cryptlib.o",
                    "crypto/fips-dso-mem.o",
                    "crypto/fips-dso-mem_clr.o",
                    "crypto/fips-dso-params.o",
                    "crypto/sha/fips-dso-sha256.o",
                    "providers/common/digests/fips-dso-sha2.o",
                    "providers/fips.ld",
                    "providers/fips/fips-dso-fipsprov.o",
                ],
            "providers/fips/fips-dso-fipsprov.o" =>
                [
                    "providers/fips/fipsprov.c",
                ],
            "ssl/libssl-lib-bio_ssl.o" =>
                [
                    "ssl/bio_ssl.c",
                ],
            "ssl/libssl-lib-d1_lib.o" =>
                [
                    "ssl/d1_lib.c",
                ],
            "ssl/libssl-lib-d1_msg.o" =>
                [
                    "ssl/d1_msg.c",
                ],
            "ssl/libssl-lib-d1_srtp.o" =>
                [
                    "ssl/d1_srtp.c",
                ],
            "ssl/libssl-lib-methods.o" =>
                [
                    "ssl/methods.c",
                ],
            "ssl/libssl-lib-packet.o" =>
                [
                    "ssl/packet.c",
                ],
            "ssl/libssl-lib-pqueue.o" =>
                [
                    "ssl/pqueue.c",
                ],
            "ssl/libssl-lib-s3_cbc.o" =>
                [
                    "ssl/s3_cbc.c",
                ],
            "ssl/libssl-lib-s3_enc.o" =>
                [
                    "ssl/s3_enc.c",
                ],
            "ssl/libssl-lib-s3_lib.o" =>
                [
                    "ssl/s3_lib.c",
                ],
            "ssl/libssl-lib-s3_msg.o" =>
                [
                    "ssl/s3_msg.c",
                ],
            "ssl/libssl-lib-ssl_asn1.o" =>
                [
                    "ssl/ssl_asn1.c",
                ],
            "ssl/libssl-lib-ssl_cert.o" =>
                [
                    "ssl/ssl_cert.c",
                ],
            "ssl/libssl-lib-ssl_ciph.o" =>
                [
                    "ssl/ssl_ciph.c",
                ],
            "ssl/libssl-lib-ssl_conf.o" =>
                [
                    "ssl/ssl_conf.c",
                ],
            "ssl/libssl-lib-ssl_err.o" =>
                [
                    "ssl/ssl_err.c",
                ],
            "ssl/libssl-lib-ssl_init.o" =>
                [
                    "ssl/ssl_init.c",
                ],
            "ssl/libssl-lib-ssl_lib.o" =>
                [
                    "ssl/ssl_lib.c",
                ],
            "ssl/libssl-lib-ssl_mcnf.o" =>
                [
                    "ssl/ssl_mcnf.c",
                ],
            "ssl/libssl-lib-ssl_rsa.o" =>
                [
                    "ssl/ssl_rsa.c",
                ],
            "ssl/libssl-lib-ssl_sess.o" =>
                [
                    "ssl/ssl_sess.c",
                ],
            "ssl/libssl-lib-ssl_stat.o" =>
                [
                    "ssl/ssl_stat.c",
                ],
            "ssl/libssl-lib-ssl_txt.o" =>
                [
                    "ssl/ssl_txt.c",
                ],
            "ssl/libssl-lib-ssl_utst.o" =>
                [
                    "ssl/ssl_utst.c",
                ],
            "ssl/libssl-lib-t1_enc.o" =>
                [
                    "ssl/t1_enc.c",
                ],
            "ssl/libssl-lib-t1_lib.o" =>
                [
                    "ssl/t1_lib.c",
                ],
            "ssl/libssl-lib-t1_trce.o" =>
                [
                    "ssl/t1_trce.c",
                ],
            "ssl/libssl-lib-tls13_enc.o" =>
                [
                    "ssl/tls13_enc.c",
                ],
            "ssl/libssl-lib-tls_srp.o" =>
                [
                    "ssl/tls_srp.c",
                ],
            "ssl/libssl-shlib-bio_ssl.o" =>
                [
                    "ssl/bio_ssl.c",
                ],
            "ssl/libssl-shlib-d1_lib.o" =>
                [
                    "ssl/d1_lib.c",
                ],
            "ssl/libssl-shlib-d1_msg.o" =>
                [
                    "ssl/d1_msg.c",
                ],
            "ssl/libssl-shlib-d1_srtp.o" =>
                [
                    "ssl/d1_srtp.c",
                ],
            "ssl/libssl-shlib-methods.o" =>
                [
                    "ssl/methods.c",
                ],
            "ssl/libssl-shlib-packet.o" =>
                [
                    "ssl/packet.c",
                ],
            "ssl/libssl-shlib-pqueue.o" =>
                [
                    "ssl/pqueue.c",
                ],
            "ssl/libssl-shlib-s3_cbc.o" =>
                [
                    "ssl/s3_cbc.c",
                ],
            "ssl/libssl-shlib-s3_enc.o" =>
                [
                    "ssl/s3_enc.c",
                ],
            "ssl/libssl-shlib-s3_lib.o" =>
                [
                    "ssl/s3_lib.c",
                ],
            "ssl/libssl-shlib-s3_msg.o" =>
                [
                    "ssl/s3_msg.c",
                ],
            "ssl/libssl-shlib-ssl_asn1.o" =>
                [
                    "ssl/ssl_asn1.c",
                ],
            "ssl/libssl-shlib-ssl_cert.o" =>
                [
                    "ssl/ssl_cert.c",
                ],
            "ssl/libssl-shlib-ssl_ciph.o" =>
                [
                    "ssl/ssl_ciph.c",
                ],
            "ssl/libssl-shlib-ssl_conf.o" =>
                [
                    "ssl/ssl_conf.c",
                ],
            "ssl/libssl-shlib-ssl_err.o" =>
                [
                    "ssl/ssl_err.c",
                ],
            "ssl/libssl-shlib-ssl_init.o" =>
                [
                    "ssl/ssl_init.c",
                ],
            "ssl/libssl-shlib-ssl_lib.o" =>
                [
                    "ssl/ssl_lib.c",
                ],
            "ssl/libssl-shlib-ssl_mcnf.o" =>
                [
                    "ssl/ssl_mcnf.c",
                ],
            "ssl/libssl-shlib-ssl_rsa.o" =>
                [
                    "ssl/ssl_rsa.c",
                ],
            "ssl/libssl-shlib-ssl_sess.o" =>
                [
                    "ssl/ssl_sess.c",
                ],
            "ssl/libssl-shlib-ssl_stat.o" =>
                [
                    "ssl/ssl_stat.c",
                ],
            "ssl/libssl-shlib-ssl_txt.o" =>
                [
                    "ssl/ssl_txt.c",
                ],
            "ssl/libssl-shlib-ssl_utst.o" =>
                [
                    "ssl/ssl_utst.c",
                ],
            "ssl/libssl-shlib-t1_enc.o" =>
                [
                    "ssl/t1_enc.c",
                ],
            "ssl/libssl-shlib-t1_lib.o" =>
                [
                    "ssl/t1_lib.c",
                ],
            "ssl/libssl-shlib-t1_trce.o" =>
                [
                    "ssl/t1_trce.c",
                ],
            "ssl/libssl-shlib-tls13_enc.o" =>
                [
                    "ssl/tls13_enc.c",
                ],
            "ssl/libssl-shlib-tls_srp.o" =>
                [
                    "ssl/tls_srp.c",
                ],
            "ssl/record/libssl-lib-dtls1_bitmap.o" =>
                [
                    "ssl/record/dtls1_bitmap.c",
                ],
            "ssl/record/libssl-lib-rec_layer_d1.o" =>
                [
                    "ssl/record/rec_layer_d1.c",
                ],
            "ssl/record/libssl-lib-rec_layer_s3.o" =>
                [
                    "ssl/record/rec_layer_s3.c",
                ],
            "ssl/record/libssl-lib-ssl3_buffer.o" =>
                [
                    "ssl/record/ssl3_buffer.c",
                ],
            "ssl/record/libssl-lib-ssl3_record.o" =>
                [
                    "ssl/record/ssl3_record.c",
                ],
            "ssl/record/libssl-lib-ssl3_record_tls13.o" =>
                [
                    "ssl/record/ssl3_record_tls13.c",
                ],
            "ssl/record/libssl-shlib-dtls1_bitmap.o" =>
                [
                    "ssl/record/dtls1_bitmap.c",
                ],
            "ssl/record/libssl-shlib-rec_layer_d1.o" =>
                [
                    "ssl/record/rec_layer_d1.c",
                ],
            "ssl/record/libssl-shlib-rec_layer_s3.o" =>
                [
                    "ssl/record/rec_layer_s3.c",
                ],
            "ssl/record/libssl-shlib-ssl3_buffer.o" =>
                [
                    "ssl/record/ssl3_buffer.c",
                ],
            "ssl/record/libssl-shlib-ssl3_record.o" =>
                [
                    "ssl/record/ssl3_record.c",
                ],
            "ssl/record/libssl-shlib-ssl3_record_tls13.o" =>
                [
                    "ssl/record/ssl3_record_tls13.c",
                ],
            "ssl/statem/libssl-lib-extensions.o" =>
                [
                    "ssl/statem/extensions.c",
                ],
            "ssl/statem/libssl-lib-extensions_clnt.o" =>
                [
                    "ssl/statem/extensions_clnt.c",
                ],
            "ssl/statem/libssl-lib-extensions_cust.o" =>
                [
                    "ssl/statem/extensions_cust.c",
                ],
            "ssl/statem/libssl-lib-extensions_srvr.o" =>
                [
                    "ssl/statem/extensions_srvr.c",
                ],
            "ssl/statem/libssl-lib-statem.o" =>
                [
                    "ssl/statem/statem.c",
                ],
            "ssl/statem/libssl-lib-statem_clnt.o" =>
                [
                    "ssl/statem/statem_clnt.c",
                ],
            "ssl/statem/libssl-lib-statem_dtls.o" =>
                [
                    "ssl/statem/statem_dtls.c",
                ],
            "ssl/statem/libssl-lib-statem_lib.o" =>
                [
                    "ssl/statem/statem_lib.c",
                ],
            "ssl/statem/libssl-lib-statem_srvr.o" =>
                [
                    "ssl/statem/statem_srvr.c",
                ],
            "ssl/statem/libssl-shlib-extensions.o" =>
                [
                    "ssl/statem/extensions.c",
                ],
            "ssl/statem/libssl-shlib-extensions_clnt.o" =>
                [
                    "ssl/statem/extensions_clnt.c",
                ],
            "ssl/statem/libssl-shlib-extensions_cust.o" =>
                [
                    "ssl/statem/extensions_cust.c",
                ],
            "ssl/statem/libssl-shlib-extensions_srvr.o" =>
                [
                    "ssl/statem/extensions_srvr.c",
                ],
            "ssl/statem/libssl-shlib-statem.o" =>
                [
                    "ssl/statem/statem.c",
                ],
            "ssl/statem/libssl-shlib-statem_clnt.o" =>
                [
                    "ssl/statem/statem_clnt.c",
                ],
            "ssl/statem/libssl-shlib-statem_dtls.o" =>
                [
                    "ssl/statem/statem_dtls.c",
                ],
            "ssl/statem/libssl-shlib-statem_lib.o" =>
                [
                    "ssl/statem/statem_lib.c",
                ],
            "ssl/statem/libssl-shlib-statem_srvr.o" =>
                [
                    "ssl/statem/statem_srvr.c",
                ],
            "ssl/tls13secretstest-bin-packet.o" =>
                [
                    "ssl/packet.c",
                ],
            "ssl/tls13secretstest-bin-tls13_enc.o" =>
                [
                    "ssl/tls13_enc.c",
                ],
            "test/aborttest" =>
                [
                    "test/aborttest-bin-aborttest.o",
                ],
            "test/aborttest-bin-aborttest.o" =>
                [
                    "test/aborttest.c",
                ],
            "test/aesgcmtest" =>
                [
                    "test/aesgcmtest-bin-aesgcmtest.o",
                ],
            "test/aesgcmtest-bin-aesgcmtest.o" =>
                [
                    "test/aesgcmtest.c",
                ],
            "test/afalgtest" =>
                [
                    "test/afalgtest-bin-afalgtest.o",
                ],
            "test/afalgtest-bin-afalgtest.o" =>
                [
                    "test/afalgtest.c",
                ],
            "test/asn1_decode_test" =>
                [
                    "test/asn1_decode_test-bin-asn1_decode_test.o",
                ],
            "test/asn1_decode_test-bin-asn1_decode_test.o" =>
                [
                    "test/asn1_decode_test.c",
                ],
            "test/asn1_encode_test" =>
                [
                    "test/asn1_encode_test-bin-asn1_encode_test.o",
                ],
            "test/asn1_encode_test-bin-asn1_encode_test.o" =>
                [
                    "test/asn1_encode_test.c",
                ],
            "test/asn1_internal_test" =>
                [
                    "test/asn1_internal_test-bin-asn1_internal_test.o",
                ],
            "test/asn1_internal_test-bin-asn1_internal_test.o" =>
                [
                    "test/asn1_internal_test.c",
                ],
            "test/asn1_string_table_test" =>
                [
                    "test/asn1_string_table_test-bin-asn1_string_table_test.o",
                ],
            "test/asn1_string_table_test-bin-asn1_string_table_test.o" =>
                [
                    "test/asn1_string_table_test.c",
                ],
            "test/asn1_time_test" =>
                [
                    "test/asn1_time_test-bin-asn1_time_test.o",
                ],
            "test/asn1_time_test-bin-asn1_time_test.o" =>
                [
                    "test/asn1_time_test.c",
                ],
            "test/asynciotest" =>
                [
                    "test/asynciotest-bin-asynciotest.o",
                    "test/asynciotest-bin-ssltestlib.o",
                ],
            "test/asynciotest-bin-asynciotest.o" =>
                [
                    "test/asynciotest.c",
                ],
            "test/asynciotest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/asynctest" =>
                [
                    "test/asynctest-bin-asynctest.o",
                ],
            "test/asynctest-bin-asynctest.o" =>
                [
                    "test/asynctest.c",
                ],
            "test/bad_dtls_test" =>
                [
                    "test/bad_dtls_test-bin-bad_dtls_test.o",
                ],
            "test/bad_dtls_test-bin-bad_dtls_test.o" =>
                [
                    "test/bad_dtls_test.c",
                ],
            "test/bftest" =>
                [
                    "test/bftest-bin-bftest.o",
                ],
            "test/bftest-bin-bftest.o" =>
                [
                    "test/bftest.c",
                ],
            "test/bio_callback_test" =>
                [
                    "test/bio_callback_test-bin-bio_callback_test.o",
                ],
            "test/bio_callback_test-bin-bio_callback_test.o" =>
                [
                    "test/bio_callback_test.c",
                ],
            "test/bio_enc_test" =>
                [
                    "test/bio_enc_test-bin-bio_enc_test.o",
                ],
            "test/bio_enc_test-bin-bio_enc_test.o" =>
                [
                    "test/bio_enc_test.c",
                ],
            "test/bio_memleak_test" =>
                [
                    "test/bio_memleak_test-bin-bio_memleak_test.o",
                ],
            "test/bio_memleak_test-bin-bio_memleak_test.o" =>
                [
                    "test/bio_memleak_test.c",
                ],
            "test/bioprinttest" =>
                [
                    "test/bioprinttest-bin-bioprinttest.o",
                ],
            "test/bioprinttest-bin-bioprinttest.o" =>
                [
                    "test/bioprinttest.c",
                ],
            "test/bn_internal_test" =>
                [
                    "test/bn_internal_test-bin-bn_internal_test.o",
                ],
            "test/bn_internal_test-bin-bn_internal_test.o" =>
                [
                    "test/bn_internal_test.c",
                ],
            "test/bntest" =>
                [
                    "test/bntest-bin-bntest.o",
                ],
            "test/bntest-bin-bntest.o" =>
                [
                    "test/bntest.c",
                ],
            "test/buildtest_c_aes" =>
                [
                    "test/buildtest_c_aes-bin-buildtest_aes.o",
                ],
            "test/buildtest_c_aes-bin-buildtest_aes.o" =>
                [
                    "test/buildtest_aes.c",
                ],
            "test/buildtest_c_asn1" =>
                [
                    "test/buildtest_c_asn1-bin-buildtest_asn1.o",
                ],
            "test/buildtest_c_asn1-bin-buildtest_asn1.o" =>
                [
                    "test/buildtest_asn1.c",
                ],
            "test/buildtest_c_asn1t" =>
                [
                    "test/buildtest_c_asn1t-bin-buildtest_asn1t.o",
                ],
            "test/buildtest_c_asn1t-bin-buildtest_asn1t.o" =>
                [
                    "test/buildtest_asn1t.c",
                ],
            "test/buildtest_c_async" =>
                [
                    "test/buildtest_c_async-bin-buildtest_async.o",
                ],
            "test/buildtest_c_async-bin-buildtest_async.o" =>
                [
                    "test/buildtest_async.c",
                ],
            "test/buildtest_c_bio" =>
                [
                    "test/buildtest_c_bio-bin-buildtest_bio.o",
                ],
            "test/buildtest_c_bio-bin-buildtest_bio.o" =>
                [
                    "test/buildtest_bio.c",
                ],
            "test/buildtest_c_blowfish" =>
                [
                    "test/buildtest_c_blowfish-bin-buildtest_blowfish.o",
                ],
            "test/buildtest_c_blowfish-bin-buildtest_blowfish.o" =>
                [
                    "test/buildtest_blowfish.c",
                ],
            "test/buildtest_c_bn" =>
                [
                    "test/buildtest_c_bn-bin-buildtest_bn.o",
                ],
            "test/buildtest_c_bn-bin-buildtest_bn.o" =>
                [
                    "test/buildtest_bn.c",
                ],
            "test/buildtest_c_buffer" =>
                [
                    "test/buildtest_c_buffer-bin-buildtest_buffer.o",
                ],
            "test/buildtest_c_buffer-bin-buildtest_buffer.o" =>
                [
                    "test/buildtest_buffer.c",
                ],
            "test/buildtest_c_camellia" =>
                [
                    "test/buildtest_c_camellia-bin-buildtest_camellia.o",
                ],
            "test/buildtest_c_camellia-bin-buildtest_camellia.o" =>
                [
                    "test/buildtest_camellia.c",
                ],
            "test/buildtest_c_cast" =>
                [
                    "test/buildtest_c_cast-bin-buildtest_cast.o",
                ],
            "test/buildtest_c_cast-bin-buildtest_cast.o" =>
                [
                    "test/buildtest_cast.c",
                ],
            "test/buildtest_c_cmac" =>
                [
                    "test/buildtest_c_cmac-bin-buildtest_cmac.o",
                ],
            "test/buildtest_c_cmac-bin-buildtest_cmac.o" =>
                [
                    "test/buildtest_cmac.c",
                ],
            "test/buildtest_c_cms" =>
                [
                    "test/buildtest_c_cms-bin-buildtest_cms.o",
                ],
            "test/buildtest_c_cms-bin-buildtest_cms.o" =>
                [
                    "test/buildtest_cms.c",
                ],
            "test/buildtest_c_comp" =>
                [
                    "test/buildtest_c_comp-bin-buildtest_comp.o",
                ],
            "test/buildtest_c_comp-bin-buildtest_comp.o" =>
                [
                    "test/buildtest_comp.c",
                ],
            "test/buildtest_c_conf" =>
                [
                    "test/buildtest_c_conf-bin-buildtest_conf.o",
                ],
            "test/buildtest_c_conf-bin-buildtest_conf.o" =>
                [
                    "test/buildtest_conf.c",
                ],
            "test/buildtest_c_conf_api" =>
                [
                    "test/buildtest_c_conf_api-bin-buildtest_conf_api.o",
                ],
            "test/buildtest_c_conf_api-bin-buildtest_conf_api.o" =>
                [
                    "test/buildtest_conf_api.c",
                ],
            "test/buildtest_c_core" =>
                [
                    "test/buildtest_c_core-bin-buildtest_core.o",
                ],
            "test/buildtest_c_core-bin-buildtest_core.o" =>
                [
                    "test/buildtest_core.c",
                ],
            "test/buildtest_c_core_names" =>
                [
                    "test/buildtest_c_core_names-bin-buildtest_core_names.o",
                ],
            "test/buildtest_c_core_names-bin-buildtest_core_names.o" =>
                [
                    "test/buildtest_core_names.c",
                ],
            "test/buildtest_c_core_numbers" =>
                [
                    "test/buildtest_c_core_numbers-bin-buildtest_core_numbers.o",
                ],
            "test/buildtest_c_core_numbers-bin-buildtest_core_numbers.o" =>
                [
                    "test/buildtest_core_numbers.c",
                ],
            "test/buildtest_c_crmf" =>
                [
                    "test/buildtest_c_crmf-bin-buildtest_crmf.o",
                ],
            "test/buildtest_c_crmf-bin-buildtest_crmf.o" =>
                [
                    "test/buildtest_crmf.c",
                ],
            "test/buildtest_c_crypto" =>
                [
                    "test/buildtest_c_crypto-bin-buildtest_crypto.o",
                ],
            "test/buildtest_c_crypto-bin-buildtest_crypto.o" =>
                [
                    "test/buildtest_crypto.c",
                ],
            "test/buildtest_c_ct" =>
                [
                    "test/buildtest_c_ct-bin-buildtest_ct.o",
                ],
            "test/buildtest_c_ct-bin-buildtest_ct.o" =>
                [
                    "test/buildtest_ct.c",
                ],
            "test/buildtest_c_des" =>
                [
                    "test/buildtest_c_des-bin-buildtest_des.o",
                ],
            "test/buildtest_c_des-bin-buildtest_des.o" =>
                [
                    "test/buildtest_des.c",
                ],
            "test/buildtest_c_dh" =>
                [
                    "test/buildtest_c_dh-bin-buildtest_dh.o",
                ],
            "test/buildtest_c_dh-bin-buildtest_dh.o" =>
                [
                    "test/buildtest_dh.c",
                ],
            "test/buildtest_c_dsa" =>
                [
                    "test/buildtest_c_dsa-bin-buildtest_dsa.o",
                ],
            "test/buildtest_c_dsa-bin-buildtest_dsa.o" =>
                [
                    "test/buildtest_dsa.c",
                ],
            "test/buildtest_c_dtls1" =>
                [
                    "test/buildtest_c_dtls1-bin-buildtest_dtls1.o",
                ],
            "test/buildtest_c_dtls1-bin-buildtest_dtls1.o" =>
                [
                    "test/buildtest_dtls1.c",
                ],
            "test/buildtest_c_e_os2" =>
                [
                    "test/buildtest_c_e_os2-bin-buildtest_e_os2.o",
                ],
            "test/buildtest_c_e_os2-bin-buildtest_e_os2.o" =>
                [
                    "test/buildtest_e_os2.c",
                ],
            "test/buildtest_c_ebcdic" =>
                [
                    "test/buildtest_c_ebcdic-bin-buildtest_ebcdic.o",
                ],
            "test/buildtest_c_ebcdic-bin-buildtest_ebcdic.o" =>
                [
                    "test/buildtest_ebcdic.c",
                ],
            "test/buildtest_c_ec" =>
                [
                    "test/buildtest_c_ec-bin-buildtest_ec.o",
                ],
            "test/buildtest_c_ec-bin-buildtest_ec.o" =>
                [
                    "test/buildtest_ec.c",
                ],
            "test/buildtest_c_ecdh" =>
                [
                    "test/buildtest_c_ecdh-bin-buildtest_ecdh.o",
                ],
            "test/buildtest_c_ecdh-bin-buildtest_ecdh.o" =>
                [
                    "test/buildtest_ecdh.c",
                ],
            "test/buildtest_c_ecdsa" =>
                [
                    "test/buildtest_c_ecdsa-bin-buildtest_ecdsa.o",
                ],
            "test/buildtest_c_ecdsa-bin-buildtest_ecdsa.o" =>
                [
                    "test/buildtest_ecdsa.c",
                ],
            "test/buildtest_c_engine" =>
                [
                    "test/buildtest_c_engine-bin-buildtest_engine.o",
                ],
            "test/buildtest_c_engine-bin-buildtest_engine.o" =>
                [
                    "test/buildtest_engine.c",
                ],
            "test/buildtest_c_ess" =>
                [
                    "test/buildtest_c_ess-bin-buildtest_ess.o",
                ],
            "test/buildtest_c_ess-bin-buildtest_ess.o" =>
                [
                    "test/buildtest_ess.c",
                ],
            "test/buildtest_c_evp" =>
                [
                    "test/buildtest_c_evp-bin-buildtest_evp.o",
                ],
            "test/buildtest_c_evp-bin-buildtest_evp.o" =>
                [
                    "test/buildtest_evp.c",
                ],
            "test/buildtest_c_hmac" =>
                [
                    "test/buildtest_c_hmac-bin-buildtest_hmac.o",
                ],
            "test/buildtest_c_hmac-bin-buildtest_hmac.o" =>
                [
                    "test/buildtest_hmac.c",
                ],
            "test/buildtest_c_idea" =>
                [
                    "test/buildtest_c_idea-bin-buildtest_idea.o",
                ],
            "test/buildtest_c_idea-bin-buildtest_idea.o" =>
                [
                    "test/buildtest_idea.c",
                ],
            "test/buildtest_c_kdf" =>
                [
                    "test/buildtest_c_kdf-bin-buildtest_kdf.o",
                ],
            "test/buildtest_c_kdf-bin-buildtest_kdf.o" =>
                [
                    "test/buildtest_kdf.c",
                ],
            "test/buildtest_c_lhash" =>
                [
                    "test/buildtest_c_lhash-bin-buildtest_lhash.o",
                ],
            "test/buildtest_c_lhash-bin-buildtest_lhash.o" =>
                [
                    "test/buildtest_lhash.c",
                ],
            "test/buildtest_c_md4" =>
                [
                    "test/buildtest_c_md4-bin-buildtest_md4.o",
                ],
            "test/buildtest_c_md4-bin-buildtest_md4.o" =>
                [
                    "test/buildtest_md4.c",
                ],
            "test/buildtest_c_md5" =>
                [
                    "test/buildtest_c_md5-bin-buildtest_md5.o",
                ],
            "test/buildtest_c_md5-bin-buildtest_md5.o" =>
                [
                    "test/buildtest_md5.c",
                ],
            "test/buildtest_c_mdc2" =>
                [
                    "test/buildtest_c_mdc2-bin-buildtest_mdc2.o",
                ],
            "test/buildtest_c_mdc2-bin-buildtest_mdc2.o" =>
                [
                    "test/buildtest_mdc2.c",
                ],
            "test/buildtest_c_modes" =>
                [
                    "test/buildtest_c_modes-bin-buildtest_modes.o",
                ],
            "test/buildtest_c_modes-bin-buildtest_modes.o" =>
                [
                    "test/buildtest_modes.c",
                ],
            "test/buildtest_c_obj_mac" =>
                [
                    "test/buildtest_c_obj_mac-bin-buildtest_obj_mac.o",
                ],
            "test/buildtest_c_obj_mac-bin-buildtest_obj_mac.o" =>
                [
                    "test/buildtest_obj_mac.c",
                ],
            "test/buildtest_c_objects" =>
                [
                    "test/buildtest_c_objects-bin-buildtest_objects.o",
                ],
            "test/buildtest_c_objects-bin-buildtest_objects.o" =>
                [
                    "test/buildtest_objects.c",
                ],
            "test/buildtest_c_ocsp" =>
                [
                    "test/buildtest_c_ocsp-bin-buildtest_ocsp.o",
                ],
            "test/buildtest_c_ocsp-bin-buildtest_ocsp.o" =>
                [
                    "test/buildtest_ocsp.c",
                ],
            "test/buildtest_c_opensslv" =>
                [
                    "test/buildtest_c_opensslv-bin-buildtest_opensslv.o",
                ],
            "test/buildtest_c_opensslv-bin-buildtest_opensslv.o" =>
                [
                    "test/buildtest_opensslv.c",
                ],
            "test/buildtest_c_ossl_typ" =>
                [
                    "test/buildtest_c_ossl_typ-bin-buildtest_ossl_typ.o",
                ],
            "test/buildtest_c_ossl_typ-bin-buildtest_ossl_typ.o" =>
                [
                    "test/buildtest_ossl_typ.c",
                ],
            "test/buildtest_c_params" =>
                [
                    "test/buildtest_c_params-bin-buildtest_params.o",
                ],
            "test/buildtest_c_params-bin-buildtest_params.o" =>
                [
                    "test/buildtest_params.c",
                ],
            "test/buildtest_c_pem" =>
                [
                    "test/buildtest_c_pem-bin-buildtest_pem.o",
                ],
            "test/buildtest_c_pem-bin-buildtest_pem.o" =>
                [
                    "test/buildtest_pem.c",
                ],
            "test/buildtest_c_pem2" =>
                [
                    "test/buildtest_c_pem2-bin-buildtest_pem2.o",
                ],
            "test/buildtest_c_pem2-bin-buildtest_pem2.o" =>
                [
                    "test/buildtest_pem2.c",
                ],
            "test/buildtest_c_pkcs12" =>
                [
                    "test/buildtest_c_pkcs12-bin-buildtest_pkcs12.o",
                ],
            "test/buildtest_c_pkcs12-bin-buildtest_pkcs12.o" =>
                [
                    "test/buildtest_pkcs12.c",
                ],
            "test/buildtest_c_pkcs7" =>
                [
                    "test/buildtest_c_pkcs7-bin-buildtest_pkcs7.o",
                ],
            "test/buildtest_c_pkcs7-bin-buildtest_pkcs7.o" =>
                [
                    "test/buildtest_pkcs7.c",
                ],
            "test/buildtest_c_provider" =>
                [
                    "test/buildtest_c_provider-bin-buildtest_provider.o",
                ],
            "test/buildtest_c_provider-bin-buildtest_provider.o" =>
                [
                    "test/buildtest_provider.c",
                ],
            "test/buildtest_c_rand" =>
                [
                    "test/buildtest_c_rand-bin-buildtest_rand.o",
                ],
            "test/buildtest_c_rand-bin-buildtest_rand.o" =>
                [
                    "test/buildtest_rand.c",
                ],
            "test/buildtest_c_rand_drbg" =>
                [
                    "test/buildtest_c_rand_drbg-bin-buildtest_rand_drbg.o",
                ],
            "test/buildtest_c_rand_drbg-bin-buildtest_rand_drbg.o" =>
                [
                    "test/buildtest_rand_drbg.c",
                ],
            "test/buildtest_c_rc2" =>
                [
                    "test/buildtest_c_rc2-bin-buildtest_rc2.o",
                ],
            "test/buildtest_c_rc2-bin-buildtest_rc2.o" =>
                [
                    "test/buildtest_rc2.c",
                ],
            "test/buildtest_c_rc4" =>
                [
                    "test/buildtest_c_rc4-bin-buildtest_rc4.o",
                ],
            "test/buildtest_c_rc4-bin-buildtest_rc4.o" =>
                [
                    "test/buildtest_rc4.c",
                ],
            "test/buildtest_c_ripemd" =>
                [
                    "test/buildtest_c_ripemd-bin-buildtest_ripemd.o",
                ],
            "test/buildtest_c_ripemd-bin-buildtest_ripemd.o" =>
                [
                    "test/buildtest_ripemd.c",
                ],
            "test/buildtest_c_rsa" =>
                [
                    "test/buildtest_c_rsa-bin-buildtest_rsa.o",
                ],
            "test/buildtest_c_rsa-bin-buildtest_rsa.o" =>
                [
                    "test/buildtest_rsa.c",
                ],
            "test/buildtest_c_safestack" =>
                [
                    "test/buildtest_c_safestack-bin-buildtest_safestack.o",
                ],
            "test/buildtest_c_safestack-bin-buildtest_safestack.o" =>
                [
                    "test/buildtest_safestack.c",
                ],
            "test/buildtest_c_seed" =>
                [
                    "test/buildtest_c_seed-bin-buildtest_seed.o",
                ],
            "test/buildtest_c_seed-bin-buildtest_seed.o" =>
                [
                    "test/buildtest_seed.c",
                ],
            "test/buildtest_c_sha" =>
                [
                    "test/buildtest_c_sha-bin-buildtest_sha.o",
                ],
            "test/buildtest_c_sha-bin-buildtest_sha.o" =>
                [
                    "test/buildtest_sha.c",
                ],
            "test/buildtest_c_srp" =>
                [
                    "test/buildtest_c_srp-bin-buildtest_srp.o",
                ],
            "test/buildtest_c_srp-bin-buildtest_srp.o" =>
                [
                    "test/buildtest_srp.c",
                ],
            "test/buildtest_c_srtp" =>
                [
                    "test/buildtest_c_srtp-bin-buildtest_srtp.o",
                ],
            "test/buildtest_c_srtp-bin-buildtest_srtp.o" =>
                [
                    "test/buildtest_srtp.c",
                ],
            "test/buildtest_c_ssl" =>
                [
                    "test/buildtest_c_ssl-bin-buildtest_ssl.o",
                ],
            "test/buildtest_c_ssl-bin-buildtest_ssl.o" =>
                [
                    "test/buildtest_ssl.c",
                ],
            "test/buildtest_c_ssl2" =>
                [
                    "test/buildtest_c_ssl2-bin-buildtest_ssl2.o",
                ],
            "test/buildtest_c_ssl2-bin-buildtest_ssl2.o" =>
                [
                    "test/buildtest_ssl2.c",
                ],
            "test/buildtest_c_stack" =>
                [
                    "test/buildtest_c_stack-bin-buildtest_stack.o",
                ],
            "test/buildtest_c_stack-bin-buildtest_stack.o" =>
                [
                    "test/buildtest_stack.c",
                ],
            "test/buildtest_c_store" =>
                [
                    "test/buildtest_c_store-bin-buildtest_store.o",
                ],
            "test/buildtest_c_store-bin-buildtest_store.o" =>
                [
                    "test/buildtest_store.c",
                ],
            "test/buildtest_c_symhacks" =>
                [
                    "test/buildtest_c_symhacks-bin-buildtest_symhacks.o",
                ],
            "test/buildtest_c_symhacks-bin-buildtest_symhacks.o" =>
                [
                    "test/buildtest_symhacks.c",
                ],
            "test/buildtest_c_tls1" =>
                [
                    "test/buildtest_c_tls1-bin-buildtest_tls1.o",
                ],
            "test/buildtest_c_tls1-bin-buildtest_tls1.o" =>
                [
                    "test/buildtest_tls1.c",
                ],
            "test/buildtest_c_ts" =>
                [
                    "test/buildtest_c_ts-bin-buildtest_ts.o",
                ],
            "test/buildtest_c_ts-bin-buildtest_ts.o" =>
                [
                    "test/buildtest_ts.c",
                ],
            "test/buildtest_c_txt_db" =>
                [
                    "test/buildtest_c_txt_db-bin-buildtest_txt_db.o",
                ],
            "test/buildtest_c_txt_db-bin-buildtest_txt_db.o" =>
                [
                    "test/buildtest_txt_db.c",
                ],
            "test/buildtest_c_ui" =>
                [
                    "test/buildtest_c_ui-bin-buildtest_ui.o",
                ],
            "test/buildtest_c_ui-bin-buildtest_ui.o" =>
                [
                    "test/buildtest_ui.c",
                ],
            "test/buildtest_c_whrlpool" =>
                [
                    "test/buildtest_c_whrlpool-bin-buildtest_whrlpool.o",
                ],
            "test/buildtest_c_whrlpool-bin-buildtest_whrlpool.o" =>
                [
                    "test/buildtest_whrlpool.c",
                ],
            "test/buildtest_c_x509" =>
                [
                    "test/buildtest_c_x509-bin-buildtest_x509.o",
                ],
            "test/buildtest_c_x509-bin-buildtest_x509.o" =>
                [
                    "test/buildtest_x509.c",
                ],
            "test/buildtest_c_x509_vfy" =>
                [
                    "test/buildtest_c_x509_vfy-bin-buildtest_x509_vfy.o",
                ],
            "test/buildtest_c_x509_vfy-bin-buildtest_x509_vfy.o" =>
                [
                    "test/buildtest_x509_vfy.c",
                ],
            "test/buildtest_c_x509v3" =>
                [
                    "test/buildtest_c_x509v3-bin-buildtest_x509v3.o",
                ],
            "test/buildtest_c_x509v3-bin-buildtest_x509v3.o" =>
                [
                    "test/buildtest_x509v3.c",
                ],
            "test/casttest" =>
                [
                    "test/casttest-bin-casttest.o",
                ],
            "test/casttest-bin-casttest.o" =>
                [
                    "test/casttest.c",
                ],
            "test/chacha_internal_test" =>
                [
                    "test/chacha_internal_test-bin-chacha_internal_test.o",
                ],
            "test/chacha_internal_test-bin-chacha_internal_test.o" =>
                [
                    "test/chacha_internal_test.c",
                ],
            "test/cipherbytes_test" =>
                [
                    "test/cipherbytes_test-bin-cipherbytes_test.o",
                ],
            "test/cipherbytes_test-bin-cipherbytes_test.o" =>
                [
                    "test/cipherbytes_test.c",
                ],
            "test/cipherlist_test" =>
                [
                    "test/cipherlist_test-bin-cipherlist_test.o",
                ],
            "test/cipherlist_test-bin-cipherlist_test.o" =>
                [
                    "test/cipherlist_test.c",
                ],
            "test/ciphername_test" =>
                [
                    "test/ciphername_test-bin-ciphername_test.o",
                ],
            "test/ciphername_test-bin-ciphername_test.o" =>
                [
                    "test/ciphername_test.c",
                ],
            "test/clienthellotest" =>
                [
                    "test/clienthellotest-bin-clienthellotest.o",
                ],
            "test/clienthellotest-bin-clienthellotest.o" =>
                [
                    "test/clienthellotest.c",
                ],
            "test/cmsapitest" =>
                [
                    "test/cmsapitest-bin-cmsapitest.o",
                ],
            "test/cmsapitest-bin-cmsapitest.o" =>
                [
                    "test/cmsapitest.c",
                ],
            "test/conf_include_test" =>
                [
                    "test/conf_include_test-bin-conf_include_test.o",
                ],
            "test/conf_include_test-bin-conf_include_test.o" =>
                [
                    "test/conf_include_test.c",
                ],
            "test/constant_time_test" =>
                [
                    "test/constant_time_test-bin-constant_time_test.o",
                ],
            "test/constant_time_test-bin-constant_time_test.o" =>
                [
                    "test/constant_time_test.c",
                ],
            "test/context_internal_test" =>
                [
                    "test/context_internal_test-bin-context_internal_test.o",
                ],
            "test/context_internal_test-bin-context_internal_test.o" =>
                [
                    "test/context_internal_test.c",
                ],
            "test/crltest" =>
                [
                    "test/crltest-bin-crltest.o",
                ],
            "test/crltest-bin-crltest.o" =>
                [
                    "test/crltest.c",
                ],
            "test/ct_test" =>
                [
                    "test/ct_test-bin-ct_test.o",
                ],
            "test/ct_test-bin-ct_test.o" =>
                [
                    "test/ct_test.c",
                ],
            "test/ctype_internal_test" =>
                [
                    "test/ctype_internal_test-bin-ctype_internal_test.o",
                ],
            "test/ctype_internal_test-bin-ctype_internal_test.o" =>
                [
                    "test/ctype_internal_test.c",
                ],
            "test/curve448_internal_test" =>
                [
                    "test/curve448_internal_test-bin-curve448_internal_test.o",
                ],
            "test/curve448_internal_test-bin-curve448_internal_test.o" =>
                [
                    "test/curve448_internal_test.c",
                ],
            "test/d2i_test" =>
                [
                    "test/d2i_test-bin-d2i_test.o",
                ],
            "test/d2i_test-bin-d2i_test.o" =>
                [
                    "test/d2i_test.c",
                ],
            "test/danetest" =>
                [
                    "test/danetest-bin-danetest.o",
                ],
            "test/danetest-bin-danetest.o" =>
                [
                    "test/danetest.c",
                ],
            "test/destest" =>
                [
                    "test/destest-bin-destest.o",
                ],
            "test/destest-bin-destest.o" =>
                [
                    "test/destest.c",
                ],
            "test/dhtest" =>
                [
                    "test/dhtest-bin-dhtest.o",
                ],
            "test/dhtest-bin-dhtest.o" =>
                [
                    "test/dhtest.c",
                ],
            "test/drbg_cavs_test" =>
                [
                    "test/drbg_cavs_test-bin-drbg_cavs_data_ctr.o",
                    "test/drbg_cavs_test-bin-drbg_cavs_data_hash.o",
                    "test/drbg_cavs_test-bin-drbg_cavs_data_hmac.o",
                    "test/drbg_cavs_test-bin-drbg_cavs_test.o",
                ],
            "test/drbg_cavs_test-bin-drbg_cavs_data_ctr.o" =>
                [
                    "test/drbg_cavs_data_ctr.c",
                ],
            "test/drbg_cavs_test-bin-drbg_cavs_data_hash.o" =>
                [
                    "test/drbg_cavs_data_hash.c",
                ],
            "test/drbg_cavs_test-bin-drbg_cavs_data_hmac.o" =>
                [
                    "test/drbg_cavs_data_hmac.c",
                ],
            "test/drbg_cavs_test-bin-drbg_cavs_test.o" =>
                [
                    "test/drbg_cavs_test.c",
                ],
            "test/drbgtest" =>
                [
                    "test/drbgtest-bin-drbgtest.o",
                ],
            "test/drbgtest-bin-drbgtest.o" =>
                [
                    "test/drbgtest.c",
                ],
            "test/dsa_no_digest_size_test" =>
                [
                    "test/dsa_no_digest_size_test-bin-dsa_no_digest_size_test.o",
                ],
            "test/dsa_no_digest_size_test-bin-dsa_no_digest_size_test.o" =>
                [
                    "test/dsa_no_digest_size_test.c",
                ],
            "test/dsatest" =>
                [
                    "test/dsatest-bin-dsatest.o",
                ],
            "test/dsatest-bin-dsatest.o" =>
                [
                    "test/dsatest.c",
                ],
            "test/dtls_mtu_test" =>
                [
                    "test/dtls_mtu_test-bin-dtls_mtu_test.o",
                    "test/dtls_mtu_test-bin-ssltestlib.o",
                ],
            "test/dtls_mtu_test-bin-dtls_mtu_test.o" =>
                [
                    "test/dtls_mtu_test.c",
                ],
            "test/dtls_mtu_test-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/dtlstest" =>
                [
                    "test/dtlstest-bin-dtlstest.o",
                    "test/dtlstest-bin-ssltestlib.o",
                ],
            "test/dtlstest-bin-dtlstest.o" =>
                [
                    "test/dtlstest.c",
                ],
            "test/dtlstest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/dtlsv1listentest" =>
                [
                    "test/dtlsv1listentest-bin-dtlsv1listentest.o",
                ],
            "test/dtlsv1listentest-bin-dtlsv1listentest.o" =>
                [
                    "test/dtlsv1listentest.c",
                ],
            "test/ec_internal_test" =>
                [
                    "test/ec_internal_test-bin-ec_internal_test.o",
                ],
            "test/ec_internal_test-bin-ec_internal_test.o" =>
                [
                    "test/ec_internal_test.c",
                ],
            "test/ecdsatest" =>
                [
                    "test/ecdsatest-bin-ecdsatest.o",
                ],
            "test/ecdsatest-bin-ecdsatest.o" =>
                [
                    "test/ecdsatest.c",
                ],
            "test/ecstresstest" =>
                [
                    "test/ecstresstest-bin-ecstresstest.o",
                ],
            "test/ecstresstest-bin-ecstresstest.o" =>
                [
                    "test/ecstresstest.c",
                ],
            "test/ectest" =>
                [
                    "test/ectest-bin-ectest.o",
                ],
            "test/ectest-bin-ectest.o" =>
                [
                    "test/ectest.c",
                ],
            "test/enginetest" =>
                [
                    "test/enginetest-bin-enginetest.o",
                ],
            "test/enginetest-bin-enginetest.o" =>
                [
                    "test/enginetest.c",
                ],
            "test/errtest" =>
                [
                    "test/errtest-bin-errtest.o",
                ],
            "test/errtest-bin-errtest.o" =>
                [
                    "test/errtest.c",
                ],
            "test/evp_extra_test" =>
                [
                    "test/evp_extra_test-bin-evp_extra_test.o",
                ],
            "test/evp_extra_test-bin-evp_extra_test.o" =>
                [
                    "test/evp_extra_test.c",
                ],
            "test/evp_kdf_test" =>
                [
                    "test/evp_kdf_test-bin-evp_kdf_test.o",
                ],
            "test/evp_kdf_test-bin-evp_kdf_test.o" =>
                [
                    "test/evp_kdf_test.c",
                ],
            "test/evp_test" =>
                [
                    "test/evp_test-bin-evp_test.o",
                ],
            "test/evp_test-bin-evp_test.o" =>
                [
                    "test/evp_test.c",
                ],
            "test/exdatatest" =>
                [
                    "test/exdatatest-bin-exdatatest.o",
                ],
            "test/exdatatest-bin-exdatatest.o" =>
                [
                    "test/exdatatest.c",
                ],
            "test/exptest" =>
                [
                    "test/exptest-bin-exptest.o",
                ],
            "test/exptest-bin-exptest.o" =>
                [
                    "test/exptest.c",
                ],
            "test/fatalerrtest" =>
                [
                    "test/fatalerrtest-bin-fatalerrtest.o",
                    "test/fatalerrtest-bin-ssltestlib.o",
                ],
            "test/fatalerrtest-bin-fatalerrtest.o" =>
                [
                    "test/fatalerrtest.c",
                ],
            "test/fatalerrtest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/gmdifftest" =>
                [
                    "test/gmdifftest-bin-gmdifftest.o",
                ],
            "test/gmdifftest-bin-gmdifftest.o" =>
                [
                    "test/gmdifftest.c",
                ],
            "test/gosttest" =>
                [
                    "test/gosttest-bin-gosttest.o",
                    "test/gosttest-bin-ssltestlib.o",
                ],
            "test/gosttest-bin-gosttest.o" =>
                [
                    "test/gosttest.c",
                ],
            "test/gosttest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/hmactest" =>
                [
                    "test/hmactest-bin-hmactest.o",
                ],
            "test/hmactest-bin-hmactest.o" =>
                [
                    "test/hmactest.c",
                ],
            "test/ideatest" =>
                [
                    "test/ideatest-bin-ideatest.o",
                ],
            "test/ideatest-bin-ideatest.o" =>
                [
                    "test/ideatest.c",
                ],
            "test/igetest" =>
                [
                    "test/igetest-bin-igetest.o",
                ],
            "test/igetest-bin-igetest.o" =>
                [
                    "test/igetest.c",
                ],
            "test/lhash_test" =>
                [
                    "test/lhash_test-bin-lhash_test.o",
                ],
            "test/lhash_test-bin-lhash_test.o" =>
                [
                    "test/lhash_test.c",
                ],
            "test/libtestutil.a" =>
                [
                    "apps/libtestutil-lib-opt.o",
                    "test/testutil/libtestutil-lib-apps_mem.o",
                    "test/testutil/libtestutil-lib-basic_output.o",
                    "test/testutil/libtestutil-lib-cb.o",
                    "test/testutil/libtestutil-lib-driver.o",
                    "test/testutil/libtestutil-lib-format_output.o",
                    "test/testutil/libtestutil-lib-init.o",
                    "test/testutil/libtestutil-lib-main.o",
                    "test/testutil/libtestutil-lib-options.o",
                    "test/testutil/libtestutil-lib-output_helpers.o",
                    "test/testutil/libtestutil-lib-stanza.o",
                    "test/testutil/libtestutil-lib-tap_bio.o",
                    "test/testutil/libtestutil-lib-test_cleanup.o",
                    "test/testutil/libtestutil-lib-test_options.o",
                    "test/testutil/libtestutil-lib-tests.o",
                ],
            "test/md2test" =>
                [
                    "test/md2test-bin-md2test.o",
                ],
            "test/md2test-bin-md2test.o" =>
                [
                    "test/md2test.c",
                ],
            "test/mdc2_internal_test" =>
                [
                    "test/mdc2_internal_test-bin-mdc2_internal_test.o",
                ],
            "test/mdc2_internal_test-bin-mdc2_internal_test.o" =>
                [
                    "test/mdc2_internal_test.c",
                ],
            "test/mdc2test" =>
                [
                    "test/mdc2test-bin-mdc2test.o",
                ],
            "test/mdc2test-bin-mdc2test.o" =>
                [
                    "test/mdc2test.c",
                ],
            "test/memleaktest" =>
                [
                    "test/memleaktest-bin-memleaktest.o",
                ],
            "test/memleaktest-bin-memleaktest.o" =>
                [
                    "test/memleaktest.c",
                ],
            "test/modes_internal_test" =>
                [
                    "test/modes_internal_test-bin-modes_internal_test.o",
                ],
            "test/modes_internal_test-bin-modes_internal_test.o" =>
                [
                    "test/modes_internal_test.c",
                ],
            "test/ocspapitest" =>
                [
                    "test/ocspapitest-bin-ocspapitest.o",
                ],
            "test/ocspapitest-bin-ocspapitest.o" =>
                [
                    "test/ocspapitest.c",
                ],
            "test/p_test" =>
                [
                    "test/p_test-dso-p_test.o",
                    "test/p_test.ld",
                ],
            "test/p_test-dso-p_test.o" =>
                [
                    "test/p_test.c",
                ],
            "test/packettest" =>
                [
                    "test/packettest-bin-packettest.o",
                ],
            "test/packettest-bin-packettest.o" =>
                [
                    "test/packettest.c",
                ],
            "test/params_api_test" =>
                [
                    "test/params_api_test-bin-params_api_test.o",
                ],
            "test/params_api_test-bin-params_api_test.o" =>
                [
                    "test/params_api_test.c",
                ],
            "test/params_test" =>
                [
                    "test/params_test-bin-params_test.o",
                ],
            "test/params_test-bin-params_test.o" =>
                [
                    "test/params_test.c",
                ],
            "test/pbelutest" =>
                [
                    "test/pbelutest-bin-pbelutest.o",
                ],
            "test/pbelutest-bin-pbelutest.o" =>
                [
                    "test/pbelutest.c",
                ],
            "test/pemtest" =>
                [
                    "test/pemtest-bin-pemtest.o",
                ],
            "test/pemtest-bin-pemtest.o" =>
                [
                    "test/pemtest.c",
                ],
            "test/pkey_meth_kdf_test" =>
                [
                    "test/pkey_meth_kdf_test-bin-pkey_meth_kdf_test.o",
                ],
            "test/pkey_meth_kdf_test-bin-pkey_meth_kdf_test.o" =>
                [
                    "test/pkey_meth_kdf_test.c",
                ],
            "test/pkey_meth_test" =>
                [
                    "test/pkey_meth_test-bin-pkey_meth_test.o",
                ],
            "test/pkey_meth_test-bin-pkey_meth_test.o" =>
                [
                    "test/pkey_meth_test.c",
                ],
            "test/poly1305_internal_test" =>
                [
                    "test/poly1305_internal_test-bin-poly1305_internal_test.o",
                ],
            "test/poly1305_internal_test-bin-poly1305_internal_test.o" =>
                [
                    "test/poly1305_internal_test.c",
                ],
            "test/property_test" =>
                [
                    "test/property_test-bin-property_test.o",
                ],
            "test/property_test-bin-property_test.o" =>
                [
                    "test/property_test.c",
                ],
            "test/provider_internal_test" =>
                [
                    "test/provider_internal_test-bin-p_test.o",
                    "test/provider_internal_test-bin-provider_internal_test.o",
                ],
            "test/provider_internal_test-bin-p_test.o" =>
                [
                    "test/p_test.c",
                ],
            "test/provider_internal_test-bin-provider_internal_test.o" =>
                [
                    "test/provider_internal_test.c",
                ],
            "test/provider_test" =>
                [
                    "test/provider_test-bin-p_test.o",
                    "test/provider_test-bin-provider_test.o",
                ],
            "test/provider_test-bin-p_test.o" =>
                [
                    "test/p_test.c",
                ],
            "test/provider_test-bin-provider_test.o" =>
                [
                    "test/provider_test.c",
                ],
            "test/rc2test" =>
                [
                    "test/rc2test-bin-rc2test.o",
                ],
            "test/rc2test-bin-rc2test.o" =>
                [
                    "test/rc2test.c",
                ],
            "test/rc4test" =>
                [
                    "test/rc4test-bin-rc4test.o",
                ],
            "test/rc4test-bin-rc4test.o" =>
                [
                    "test/rc4test.c",
                ],
            "test/rc5test" =>
                [
                    "test/rc5test-bin-rc5test.o",
                ],
            "test/rc5test-bin-rc5test.o" =>
                [
                    "test/rc5test.c",
                ],
            "test/rdrand_sanitytest" =>
                [
                    "test/rdrand_sanitytest-bin-rdrand_sanitytest.o",
                ],
            "test/rdrand_sanitytest-bin-rdrand_sanitytest.o" =>
                [
                    "test/rdrand_sanitytest.c",
                ],
            "test/recordlentest" =>
                [
                    "test/recordlentest-bin-recordlentest.o",
                    "test/recordlentest-bin-ssltestlib.o",
                ],
            "test/recordlentest-bin-recordlentest.o" =>
                [
                    "test/recordlentest.c",
                ],
            "test/recordlentest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/rsa_complex" =>
                [
                    "test/rsa_complex-bin-rsa_complex.o",
                ],
            "test/rsa_complex-bin-rsa_complex.o" =>
                [
                    "test/rsa_complex.c",
                ],
            "test/rsa_mp_test" =>
                [
                    "test/rsa_mp_test-bin-rsa_mp_test.o",
                ],
            "test/rsa_mp_test-bin-rsa_mp_test.o" =>
                [
                    "test/rsa_mp_test.c",
                ],
            "test/rsa_sp800_56b_test" =>
                [
                    "test/rsa_sp800_56b_test-bin-rsa_sp800_56b_test.o",
                ],
            "test/rsa_sp800_56b_test-bin-rsa_sp800_56b_test.o" =>
                [
                    "test/rsa_sp800_56b_test.c",
                ],
            "test/rsa_test" =>
                [
                    "test/rsa_test-bin-rsa_test.o",
                ],
            "test/rsa_test-bin-rsa_test.o" =>
                [
                    "test/rsa_test.c",
                ],
            "test/sanitytest" =>
                [
                    "test/sanitytest-bin-sanitytest.o",
                ],
            "test/sanitytest-bin-sanitytest.o" =>
                [
                    "test/sanitytest.c",
                ],
            "test/secmemtest" =>
                [
                    "test/secmemtest-bin-secmemtest.o",
                ],
            "test/secmemtest-bin-secmemtest.o" =>
                [
                    "test/secmemtest.c",
                ],
            "test/servername_test" =>
                [
                    "test/servername_test-bin-servername_test.o",
                    "test/servername_test-bin-ssltestlib.o",
                ],
            "test/servername_test-bin-servername_test.o" =>
                [
                    "test/servername_test.c",
                ],
            "test/servername_test-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/shlibloadtest" =>
                [
                    "test/shlibloadtest-bin-shlibloadtest.o",
                ],
            "test/shlibloadtest-bin-shlibloadtest.o" =>
                [
                    "test/shlibloadtest.c",
                ],
            "test/siphash_internal_test" =>
                [
                    "test/siphash_internal_test-bin-siphash_internal_test.o",
                ],
            "test/siphash_internal_test-bin-siphash_internal_test.o" =>
                [
                    "test/siphash_internal_test.c",
                ],
            "test/sm2_internal_test" =>
                [
                    "test/sm2_internal_test-bin-sm2_internal_test.o",
                ],
            "test/sm2_internal_test-bin-sm2_internal_test.o" =>
                [
                    "test/sm2_internal_test.c",
                ],
            "test/sm4_internal_test" =>
                [
                    "test/sm4_internal_test-bin-sm4_internal_test.o",
                ],
            "test/sm4_internal_test-bin-sm4_internal_test.o" =>
                [
                    "test/sm4_internal_test.c",
                ],
            "test/sparse_array_test" =>
                [
                    "test/sparse_array_test-bin-sparse_array_test.o",
                ],
            "test/sparse_array_test-bin-sparse_array_test.o" =>
                [
                    "test/sparse_array_test.c",
                ],
            "test/srptest" =>
                [
                    "test/srptest-bin-srptest.o",
                ],
            "test/srptest-bin-srptest.o" =>
                [
                    "test/srptest.c",
                ],
            "test/ssl_cert_table_internal_test" =>
                [
                    "test/ssl_cert_table_internal_test-bin-ssl_cert_table_internal_test.o",
                ],
            "test/ssl_cert_table_internal_test-bin-ssl_cert_table_internal_test.o" =>
                [
                    "test/ssl_cert_table_internal_test.c",
                ],
            "test/ssl_test" =>
                [
                    "test/ssl_test-bin-handshake_helper.o",
                    "test/ssl_test-bin-ssl_test.o",
                    "test/ssl_test-bin-ssl_test_ctx.o",
                ],
            "test/ssl_test-bin-handshake_helper.o" =>
                [
                    "test/handshake_helper.c",
                ],
            "test/ssl_test-bin-ssl_test.o" =>
                [
                    "test/ssl_test.c",
                ],
            "test/ssl_test-bin-ssl_test_ctx.o" =>
                [
                    "test/ssl_test_ctx.c",
                ],
            "test/ssl_test_ctx_test" =>
                [
                    "test/ssl_test_ctx_test-bin-ssl_test_ctx.o",
                    "test/ssl_test_ctx_test-bin-ssl_test_ctx_test.o",
                ],
            "test/ssl_test_ctx_test-bin-ssl_test_ctx.o" =>
                [
                    "test/ssl_test_ctx.c",
                ],
            "test/ssl_test_ctx_test-bin-ssl_test_ctx_test.o" =>
                [
                    "test/ssl_test_ctx_test.c",
                ],
            "test/sslapitest" =>
                [
                    "test/sslapitest-bin-sslapitest.o",
                    "test/sslapitest-bin-ssltestlib.o",
                ],
            "test/sslapitest-bin-sslapitest.o" =>
                [
                    "test/sslapitest.c",
                ],
            "test/sslapitest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/sslbuffertest" =>
                [
                    "test/sslbuffertest-bin-sslbuffertest.o",
                    "test/sslbuffertest-bin-ssltestlib.o",
                ],
            "test/sslbuffertest-bin-sslbuffertest.o" =>
                [
                    "test/sslbuffertest.c",
                ],
            "test/sslbuffertest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/sslcorrupttest" =>
                [
                    "test/sslcorrupttest-bin-sslcorrupttest.o",
                    "test/sslcorrupttest-bin-ssltestlib.o",
                ],
            "test/sslcorrupttest-bin-sslcorrupttest.o" =>
                [
                    "test/sslcorrupttest.c",
                ],
            "test/sslcorrupttest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/ssltest_old" =>
                [
                    "test/ssltest_old-bin-ssltest_old.o",
                ],
            "test/ssltest_old-bin-ssltest_old.o" =>
                [
                    "test/ssltest_old.c",
                ],
            "test/stack_test" =>
                [
                    "test/stack_test-bin-stack_test.o",
                ],
            "test/stack_test-bin-stack_test.o" =>
                [
                    "test/stack_test.c",
                ],
            "test/sysdefaulttest" =>
                [
                    "test/sysdefaulttest-bin-sysdefaulttest.o",
                ],
            "test/sysdefaulttest-bin-sysdefaulttest.o" =>
                [
                    "test/sysdefaulttest.c",
                ],
            "test/test_test" =>
                [
                    "test/test_test-bin-test_test.o",
                ],
            "test/test_test-bin-test_test.o" =>
                [
                    "test/test_test.c",
                ],
            "test/testutil/libtestutil-lib-apps_mem.o" =>
                [
                    "test/testutil/apps_mem.c",
                ],
            "test/testutil/libtestutil-lib-basic_output.o" =>
                [
                    "test/testutil/basic_output.c",
                ],
            "test/testutil/libtestutil-lib-cb.o" =>
                [
                    "test/testutil/cb.c",
                ],
            "test/testutil/libtestutil-lib-driver.o" =>
                [
                    "test/testutil/driver.c",
                ],
            "test/testutil/libtestutil-lib-format_output.o" =>
                [
                    "test/testutil/format_output.c",
                ],
            "test/testutil/libtestutil-lib-init.o" =>
                [
                    "test/testutil/init.c",
                ],
            "test/testutil/libtestutil-lib-main.o" =>
                [
                    "test/testutil/main.c",
                ],
            "test/testutil/libtestutil-lib-options.o" =>
                [
                    "test/testutil/options.c",
                ],
            "test/testutil/libtestutil-lib-output_helpers.o" =>
                [
                    "test/testutil/output_helpers.c",
                ],
            "test/testutil/libtestutil-lib-stanza.o" =>
                [
                    "test/testutil/stanza.c",
                ],
            "test/testutil/libtestutil-lib-tap_bio.o" =>
                [
                    "test/testutil/tap_bio.c",
                ],
            "test/testutil/libtestutil-lib-test_cleanup.o" =>
                [
                    "test/testutil/test_cleanup.c",
                ],
            "test/testutil/libtestutil-lib-test_options.o" =>
                [
                    "test/testutil/test_options.c",
                ],
            "test/testutil/libtestutil-lib-tests.o" =>
                [
                    "test/testutil/tests.c",
                ],
            "test/threadstest" =>
                [
                    "test/threadstest-bin-threadstest.o",
                ],
            "test/threadstest-bin-threadstest.o" =>
                [
                    "test/threadstest.c",
                ],
            "test/time_offset_test" =>
                [
                    "test/time_offset_test-bin-time_offset_test.o",
                ],
            "test/time_offset_test-bin-time_offset_test.o" =>
                [
                    "test/time_offset_test.c",
                ],
            "test/tls13ccstest" =>
                [
                    "test/tls13ccstest-bin-ssltestlib.o",
                    "test/tls13ccstest-bin-tls13ccstest.o",
                ],
            "test/tls13ccstest-bin-ssltestlib.o" =>
                [
                    "test/ssltestlib.c",
                ],
            "test/tls13ccstest-bin-tls13ccstest.o" =>
                [
                    "test/tls13ccstest.c",
                ],
            "test/tls13encryptiontest" =>
                [
                    "test/tls13encryptiontest-bin-tls13encryptiontest.o",
                ],
            "test/tls13encryptiontest-bin-tls13encryptiontest.o" =>
                [
                    "test/tls13encryptiontest.c",
                ],
            "test/tls13secretstest" =>
                [
                    "ssl/tls13secretstest-bin-packet.o",
                    "ssl/tls13secretstest-bin-tls13_enc.o",
                    "test/tls13secretstest-bin-tls13secretstest.o",
                ],
            "test/tls13secretstest-bin-tls13secretstest.o" =>
                [
                    "test/tls13secretstest.c",
                ],
            "test/uitest" =>
                [
                    "apps/uitest-bin-apps_ui.o",
                    "test/uitest-bin-uitest.o",
                ],
            "test/uitest-bin-uitest.o" =>
                [
                    "test/uitest.c",
                ],
            "test/v3ext" =>
                [
                    "test/v3ext-bin-v3ext.o",
                ],
            "test/v3ext-bin-v3ext.o" =>
                [
                    "test/v3ext.c",
                ],
            "test/v3nametest" =>
                [
                    "test/v3nametest-bin-v3nametest.o",
                ],
            "test/v3nametest-bin-v3nametest.o" =>
                [
                    "test/v3nametest.c",
                ],
            "test/verify_extra_test" =>
                [
                    "test/verify_extra_test-bin-verify_extra_test.o",
                ],
            "test/verify_extra_test-bin-verify_extra_test.o" =>
                [
                    "test/verify_extra_test.c",
                ],
            "test/versions" =>
                [
                    "test/versions-bin-versions.o",
                ],
            "test/versions-bin-versions.o" =>
                [
                    "test/versions.c",
                ],
            "test/wpackettest" =>
                [
                    "test/wpackettest-bin-wpackettest.o",
                ],
            "test/wpackettest-bin-wpackettest.o" =>
                [
                    "test/wpackettest.c",
                ],
            "test/x509_check_cert_pkey_test" =>
                [
                    "test/x509_check_cert_pkey_test-bin-x509_check_cert_pkey_test.o",
                ],
            "test/x509_check_cert_pkey_test-bin-x509_check_cert_pkey_test.o" =>
                [
                    "test/x509_check_cert_pkey_test.c",
                ],
            "test/x509_dup_cert_test" =>
                [
                    "test/x509_dup_cert_test-bin-x509_dup_cert_test.o",
                ],
            "test/x509_dup_cert_test-bin-x509_dup_cert_test.o" =>
                [
                    "test/x509_dup_cert_test.c",
                ],
            "test/x509_internal_test" =>
                [
                    "test/x509_internal_test-bin-x509_internal_test.o",
                ],
            "test/x509_internal_test-bin-x509_internal_test.o" =>
                [
                    "test/x509_internal_test.c",
                ],
            "test/x509_time_test" =>
                [
                    "test/x509_time_test-bin-x509_time_test.o",
                ],
            "test/x509_time_test-bin-x509_time_test.o" =>
                [
                    "test/x509_time_test.c",
                ],
            "test/x509aux" =>
                [
                    "test/x509aux-bin-x509aux.o",
                ],
            "test/x509aux-bin-x509aux.o" =>
                [
                    "test/x509aux.c",
                ],
            "tools/c_rehash" =>
                [
                    "tools/c_rehash.in",
                ],
            "util/shlib_wrap.sh" =>
                [
                    "util/shlib_wrap.sh.in",
                ],
        },
);

# The following data is only used when this files is use as a script
my @makevars = (
    'AR',
    'ARFLAGS',
    'AS',
    'ASFLAGS',
    'CC',
    'CFLAGS',
    'CPP',
    'CPPDEFINES',
    'CPPFLAGS',
    'CPPINCLUDES',
    'CROSS_COMPILE',
    'CXX',
    'CXXFLAGS',
    'HASHBANGPERL',
    'LD',
    'LDFLAGS',
    'LDLIBS',
    'MT',
    'MTFLAGS',
    'PERL',
    'RANLIB',
    'RC',
    'RCFLAGS',
    'RM',
);
my %disabled_info = (
    'asan' => {
        macro => 'OPENSSL_NO_ASAN',
    },
    'crypto-mdebug' => {
        macro => 'OPENSSL_NO_CRYPTO_MDEBUG',
    },
    'crypto-mdebug-backtrace' => {
        macro => 'OPENSSL_NO_CRYPTO_MDEBUG_BACKTRACE',
    },
    'devcryptoeng' => {
        macro => 'OPENSSL_NO_DEVCRYPTOENG',
    },
    'ec_nistp_64_gcc_128' => {
        macro => 'OPENSSL_NO_EC_NISTP_64_GCC_128',
    },
    'egd' => {
        macro => 'OPENSSL_NO_EGD',
    },
    'external-tests' => {
        macro => 'OPENSSL_NO_EXTERNAL_TESTS',
    },
    'fuzz-afl' => {
        macro => 'OPENSSL_NO_FUZZ_AFL',
    },
    'fuzz-libfuzzer' => {
        macro => 'OPENSSL_NO_FUZZ_LIBFUZZER',
    },
    'ktls' => {
        macro => 'OPENSSL_NO_KTLS',
    },
    'md2' => {
        macro => 'OPENSSL_NO_MD2',
        skipped => [ 'crypto/md2' ],
    },
    'msan' => {
        macro => 'OPENSSL_NO_MSAN',
    },
    'rc5' => {
        macro => 'OPENSSL_NO_RC5',
        skipped => [ 'crypto/rc5' ],
    },
    'sctp' => {
        macro => 'OPENSSL_NO_SCTP',
    },
    'ssl-trace' => {
        macro => 'OPENSSL_NO_SSL_TRACE',
    },
    'ssl3' => {
        macro => 'OPENSSL_NO_SSL3',
    },
    'ssl3-method' => {
        macro => 'OPENSSL_NO_SSL3_METHOD',
    },
    'trace' => {
        macro => 'OPENSSL_NO_TRACE',
    },
    'ubsan' => {
        macro => 'OPENSSL_NO_UBSAN',
    },
    'unit-test' => {
        macro => 'OPENSSL_NO_UNIT_TEST',
    },
    'weak-ssl-ciphers' => {
        macro => 'OPENSSL_NO_WEAK_SSL_CIPHERS',
    },
);
my @user_crossable = qw( AR AS CC CXX CPP LD MT RANLIB RC );
# If run directly, we can give some answers, and even reconfigure
unless (caller) {
    use Getopt::Long;
    use File::Spec::Functions;
    use File::Basename;
    use Pod::Usage;

    my $here = dirname($0);

    my $dump = undef;
    my $cmdline = undef;
    my $options = undef;
    my $target = undef;
    my $envvars = undef;
    my $makevars = undef;
    my $buildparams = undef;
    my $reconf = undef;
    my $verbose = undef;
    my $help = undef;
    my $man = undef;
    GetOptions('dump|d'                 => \$dump,
               'command-line|c'         => \$cmdline,
               'options|o'              => \$options,
               'target|t'               => \$target,
               'environment|e'          => \$envvars,
               'make-variables|m'       => \$makevars,
               'build-parameters|b'     => \$buildparams,
               'reconfigure|reconf|r'   => \$reconf,
               'verbose|v'              => \$verbose,
               'help'                   => \$help,
               'man'                    => \$man)
        or die "Errors in command line arguments\n";

    unless ($dump || $cmdline || $options || $target || $envvars || $makevars
            || $buildparams || $reconf || $verbose || $help || $man) {
        print STDERR <<"_____";
You must give at least one option.
For more information, do '$0 --help'
_____
        exit(2);
    }

    if ($help) {
        pod2usage(-exitval => 0,
                  -verbose => 1);
    }
    if ($man) {
        pod2usage(-exitval => 0,
                  -verbose => 2);
    }
    if ($dump || $cmdline) {
        print "\nCommand line (with current working directory = $here):\n\n";
        print '    ',join(' ',
                          $config{PERL},
                          catfile($config{sourcedir}, 'Configure'),
                          @{$config{perlargv}}), "\n";
        print "\nPerl information:\n\n";
        print '    ',$config{perl_cmd},"\n";
        print '    ',$config{perl_version},' for ',$config{perl_archname},"\n";
    }
    if ($dump || $options) {
        my $longest = 0;
        my $longest2 = 0;
        foreach my $what (@disablables) {
            $longest = length($what) if $longest < length($what);
            $longest2 = length($disabled{$what})
                if $disabled{$what} && $longest2 < length($disabled{$what});
        }
        print "\nEnabled features:\n\n";
        foreach my $what (@disablables) {
            print "    $what\n" unless $disabled{$what};
        }
        print "\nDisabled features:\n\n";
        foreach my $what (@disablables) {
            if ($disabled{$what}) {
                print "    $what", ' ' x ($longest - length($what) + 1),
                    "[$disabled{$what}]", ' ' x ($longest2 - length($disabled{$what}) + 1);
                print $disabled_info{$what}->{macro}
                    if $disabled_info{$what}->{macro};
                print ' (skip ',
                    join(', ', @{$disabled_info{$what}->{skipped}}),
                    ')'
                    if $disabled_info{$what}->{skipped};
                print "\n";
            }
        }
    }
    if ($dump || $target) {
        print "\nConfig target attributes:\n\n";
        foreach (sort keys %target) {
            next if $_ =~ m|^_| || $_ eq 'template';
            my $quotify = sub {
                map { (my $x = $_) =~ s|([\\\$\@"])|\\$1|g; "\"$x\""} @_;
            };
            print '    ', $_, ' => ';
            if (ref($target{$_}) eq "ARRAY") {
                print '[ ', join(', ', $quotify->(@{$target{$_}})), " ],\n";
            } else {
                print $quotify->($target{$_}), ",\n"
            }
        }
    }
    if ($dump || $envvars) {
        print "\nRecorded environment:\n\n";
        foreach (sort keys %{$config{perlenv}}) {
            print '    ',$_,' = ',($config{perlenv}->{$_} || ''),"\n";
        }
    }
    if ($dump || $makevars) {
        print "\nMakevars:\n\n";
        foreach my $var (@makevars) {
            my $prefix = '';
            $prefix = $config{CROSS_COMPILE}
                if grep { $var eq $_ } @user_crossable;
            $prefix //= '';
            print '    ',$var,' ' x (16 - length $var),'= ',
                (ref $config{$var} eq 'ARRAY'
                 ? join(' ', @{$config{$var}})
                 : $prefix.$config{$var}),
                "\n"
                if defined $config{$var};
        }

        my @buildfile = ($config{builddir}, $config{build_file});
        unshift @buildfile, $here
            unless file_name_is_absolute($config{builddir});
        my $buildfile = canonpath(catdir(@buildfile));
        print <<"_____";

NOTE: These variables only represent the configuration view.  The build file
template may have processed these variables further, please have a look at the
build file for more exact data:
    $buildfile
_____
    }
    if ($dump || $buildparams) {
        my @buildfile = ($config{builddir}, $config{build_file});
        unshift @buildfile, $here
            unless file_name_is_absolute($config{builddir});
        print "\nbuild file:\n\n";
        print "    ", canonpath(catfile(@buildfile)),"\n";

        print "\nbuild file templates:\n\n";
        foreach (@{$config{build_file_templates}}) {
            my @tmpl = ($_);
            unshift @tmpl, $here
                unless file_name_is_absolute($config{sourcedir});
            print '    ',canonpath(catfile(@tmpl)),"\n";
        }
    }
    if ($reconf) {
        if ($verbose) {
            print 'Reconfiguring with: ', join(' ',@{$config{perlargv}}), "\n";
            foreach (sort keys %{$config{perlenv}}) {
                print '    ',$_,' = ',($config{perlenv}->{$_} || ""),"\n";
            }
        }

        chdir $here;
        exec $^X,catfile($config{sourcedir}, 'Configure'),'reconf';
    }
}

1;

__END__

=head1 NAME

configdata.pm - configuration data for OpenSSL builds

=head1 SYNOPSIS

Interactive:

  perl configdata.pm [options]

As data bank module:

  use configdata;

=head1 DESCRIPTION

This module can be used in two modes, interactively and as a module containing
all the data recorded by OpenSSL's Configure script.

When used interactively, simply run it as any perl script, with at least one
option, and you will get the information you ask for.  See L</OPTIONS> below.

When loaded as a module, you get a few databanks with useful information to
perform build related tasks.  The databanks are:

    %config             Configured things.
    %target             The OpenSSL config target with all inheritances
                        resolved.
    %disabled           The features that are disabled.
    @disablables        The list of features that can be disabled.
    %withargs           All data given through --with-THING options.
    %unified_info       All information that was computed from the build.info
                        files.

=head1 OPTIONS

=over 4

=item B<--help>

Print a brief help message and exit.

=item B<--man>

Print the manual page and exit.

=item B<--dump> | B<-d>

Print all relevant configuration data.  This is equivalent to B<--command-line>
B<--options> B<--target> B<--environment> B<--make-variables>
B<--build-parameters>.

=item B<--command-line> | B<-c>

Print the current configuration command line.

=item B<--options> | B<-o>

Print the features, both enabled and disabled, and display defined macro and
skipped directories where applicable.

=item B<--target> | B<-t>

Print the config attributes for this config target.

=item B<--environment> | B<-e>

Print the environment variables and their values at the time of configuration.

=item B<--make-variables> | B<-m>

Print the main make variables generated in the current configuration

=item B<--build-parameters> | B<-b>

Print the build parameters, i.e. build file and build file templates.

=item B<--reconfigure> | B<--reconf> | B<-r>

Redo the configuration.

=item B<--verbose> | B<-v>

Verbose output.

=back

=cut

