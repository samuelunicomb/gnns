#!/bin/bash

FILE=debug.dat

rm out/out01/*.dat

cat ${FILE} | awk -f awk/out01.awk
