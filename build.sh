#!/bin/bash

OUT_DIR="out"

rm -rf $OUT_DIR
mkdir $OUT_DIR
mkdir $OUT_DIR/lib
mkdir $OUT_DIR/tmp

#build openssl
cd ./external/openssl/openssl-master
./config
make -j32

cd ../../../
cp external/openssl/openssl-master/libcrypto.so.3 out/lib/
cp external/openssl/openssl-master/libssl.so.3 out/lib/

cd out/lib/
ln -s libcrypto.so.3 libcrypto.so
ln -s libssl.so.3 libssl.so

cd ../../
make -j32
