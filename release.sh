#!/bin/bash

RELEASE_DIR="release"
OUT_DIR="out"

rm -rf ./$RELEASE_DIR
mkdir $RELEASE_DIR

#./build.sh

#cp so
cp $OUT_DIR/lib/libobotcha.so ./$RELEASE_DIR/

mkdir ./$RELEASE_DIR/include/
mkdir ./$RELEASE_DIR/include/util
mkdir ./$RELEASE_DIR/include/util/concurrent
cp -rf ./util/concurrent/include/*.* ./$RELEASE_DIR/include/util/concurrent/

#-I ./util/coroutine/include/ \
mkdir ./$RELEASE_DIR/include/util/coroutine
cp -rf ./util/coroutine/include/*.* ./$RELEASE_DIR/include/util/coroutine/

#-I ./util/text/include/ \
mkdir ./$RELEASE_DIR/include/util/text
cp -rf ./util/text/include/*.* ./$RELEASE_DIR/include/util/text/

#-I ./sql/include/ \
mkdir ./$RELEASE_DIR/include/sql
cp -rf ./sql/include/*.* ./$RELEASE_DIR/include/sql/

#-I ./lang/include \
mkdir ./$RELEASE_DIR/include/lang
cp -rf ./lang/include/*.* ./$RELEASE_DIR/include/lang/

#-I ./io/include \
mkdir ./$RELEASE_DIR/include/io
cp -rf ./io/include/*.* ./$RELEASE_DIR/include/io/


#-I ./util/include/ \
cp -rf ./util/include/*.* ./$RELEASE_DIR/include/util/

#-I ./net/include \
mkdir ./$RELEASE_DIR/include/net
cp -rf ./net/include/*.* ./$RELEASE_DIR/include/net/


#-I ./security/include \
mkdir ./$RELEASE_DIR/include/security
cp -rf ./security/include/*.* ./$RELEASE_DIR/include/security/

#-I ./process/include \
mkdir ./$RELEASE_DIR/include/process
cp -rf ./process/include/*.* ./$RELEASE_DIR/include/process/


#-I ./external/iniparser/include \
mkdir ./$RELEASE_DIR/include/external
mkdir ./$RELEASE_DIR/include/external/iniparser
cp -rf ./external/iniparser/include/*.* ./$RELEASE_DIR/include/external/iniparser/


#-I ./external/glog/include \
mkdir ./$RELEASE_DIR/include/external/glog
cp -rf ./external/glog/include/*.* ./$RELEASE_DIR/include/external/glog/

#-I ./external/jsoncpp/include \
mkdir ./$RELEASE_DIR/include/external/jsoncpp
cp -rf ./external/jsoncpp/include/json/ ./$RELEASE_DIR/include/external/jsoncpp/


#-I ./external/rapidxml/include \
mkdir ./$RELEASE_DIR/include/external/rapidxml
cp -rf ./external/rapidxml/include/*.* ./$RELEASE_DIR/include/external/rapidxml/


#-I ./external/zlib/include \
mkdir ./$RELEASE_DIR/include/external/zlib
cp -rf ./external/zlib/include/*.* ./$RELEASE_DIR/include/external/zlib/


#-I ./external/ccl/include \
mkdir ./$RELEASE_DIR/include/external/ccl
cp -rf ./external/ccl/include/*.* ./$RELEASE_DIR/include/external/ccl/


#-I ./external/yaml/include \
mkdir ./$RELEASE_DIR/include/external/yaml
cp -rf ./external/yaml/include/yaml-cpp/*.* ./$RELEASE_DIR/include/external/yaml/


#-I ./external/openssl/include \
mkdir ./$RELEASE_DIR/include/external/openssl
cp -rf ./external/openssl/include/* ./$RELEASE_DIR/include/external/openssl/


#-I ./external/sqlite3/include \
mkdir ./$RELEASE_DIR/include/external/sqlite3
cp -rf ./external/sqlite3/include/*.* ./$RELEASE_DIR/include/external/sqlite3/


#-I ./external/libco \
mkdir ./$RELEASE_DIR/include/external/libco
cp -rf ./external/libco/*.* ./$RELEASE_DIR/include/external/libco/


#-I ./external/mysql_connector/include \
mkdir ./$RELEASE_DIR/include/external/mysql_connector
cp -rf ./external/mysql_connector/include/*.* ./$RELEASE_DIR/include/external/mysql_connector/


#-I ./external/uuid/include \
mkdir ./$RELEASE_DIR/include/external/uuid
cp -rf ./external/uuid/include/*.* ./$RELEASE_DIR/include/external/uuid/

#-I ./external/hiredis/include \
mkdir ./$RELEASE_DIR/include/external/hiredis
cp -rf ./external/hiredis/include/*.* ./$RELEASE_DIR/include/external/hiredis/
