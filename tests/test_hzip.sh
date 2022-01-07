#!/bin/sh
# Este archivo debe ser ejecutado desde el root del repositorio

hzip="./bin/hzip"
testfiles=( ./textos/simple.txt ./textos/quijote.txt ./textos/commedia.txt )

make $hzip

echo "Testing hzip: compression -> decompression -> diff"
for testfile in "${testfiles[@]}"; do
    $hzip c $testfile $testfile.huff
    $hzip d $testfile.huff $testfile.huff.txt
    diff -s $testfile $testfile.huff.txt
    rm $testfile.huff $testfile.huff.txt
done
