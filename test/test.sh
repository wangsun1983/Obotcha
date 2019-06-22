#!/bin/bash

function getdir(){
    for element in `ls $1`
    do  
        dir_or_file=$1"/"$element
        if [ -d $dir_or_file ]
        then 
            startTest $dir_or_file     
        else
            echo $dir_or_file
        fi  
    done
}

function startTest() {
    cd $1
    rm core
    rm mytest
    make
    ./mytest
    cd ..
}

ulimit -c unlimit
getdir "./"
