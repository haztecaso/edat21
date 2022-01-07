#!/bin/sh
# Este archivo debe ser ejecutado desde el root del repositorio

hzip="./bin/hzip"

set -xe
make $hzip
$hzip c $1 $1.huff
$hzip d $1.huff $1.huff.txt
diff -s $1 $1.huff.txt
rm $1.huff $1.huff.txt
