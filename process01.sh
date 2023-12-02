#!/bin/bash

FILE=debug.dat

rm out/out01/*.dat

cat ${FILE} | grep type0 > out/out01/out-0.dat
cat ${FILE} | grep type1 > out/out01/out-1.dat
cat ${FILE} | grep type2 > out/out01/out-2.dat
cat ${FILE} | grep type3 > out/out01/out-3.dat
