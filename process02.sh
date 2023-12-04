#!/bin/bash

FILE=debug.dat

rm out/out02/*.dat

cat ${FILE} | grep embedding | awk -f awk/out02a.awk
cat ${FILE} | grep loss | awk -f awk/out02b.awk
