#!/bin/bash

OUT_DIR="out"

rm -rf $OUT_DIR
mkdir $OUT_DIR
mkdir $OUT_DIR/lib
mkdir $OUT_DIR/tmp

#build openssl
cd ./external/openssl/openssl-master
chmod 777 config
./config
make -j32

cd ../../../
cp external/openssl/openssl-master/libcrypto.so.3 out/lib/
cp external/openssl/openssl-master/libssl.so.3 out/lib/
cp external/openssl/openssl-master/libssl.a out/lib/
cp external/openssl/openssl-master/libcrypto.a out/lib/

cd out/lib/
ln -s libcrypto.so.3 libcrypto.so
ln -s libssl.so.3 libssl.so

cd ../../
#mkdir scanresult
#scan-build -o ./scanresult make -j32
#make -j32
