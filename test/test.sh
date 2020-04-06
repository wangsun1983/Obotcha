#!/bin/bash

UnitTestCase=(
#lang
testBoolean testByteArray testByte testDouble
testFloat testInteger testLong testString
testUint16 testUint32 testUint64 testUint8
testList testByteRingArray
#util
testArrayList testCalendar)

function start(){
    echo -----------------------
    echo -----Start Prebuild----
    echo -----------------------
    for element in ${UnitTestCase[@]};
    do
        dir_or_file=$element
        if [ -d $dir_or_file ]
        then
            prebuild $dir_or_file
        else
            echo ------------No build $dir_or_file !!!!!!!!------------
        fi
    done

    echo -----------------------
    echo -----Start Test----
    echo -----------------------
    for element in ${UnitTestCase[@]};
    do
        dir_or_file=$element
        if [ -d $dir_or_file ]
        then
            test $dir_or_file
        else
            echo ------------No Test $dir_or_file !!!!!!!!------------
        fi
    done
}

function prebuild() {
    cd $1
    rm core
    rm mytest
    echo StartBuild $1
    make -j32
    cd ..
}

function test() {
  cd $1
  ./mytest
  cd ..
}

ulimit -c unlimited
start
