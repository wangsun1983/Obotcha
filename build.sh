#!/bin/bash

OUT_DIR="out"

rm -rf $OUT_DIR
mkdir $OUT_DIR
mkdir $OUT_DIR/lib
mkdir $OUT_DIR/tmp


make
