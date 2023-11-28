#!/bin/bash

FILE=debug.dat

rm out/out00/*.dat

cat ${FILE} | awk -f awk/out00.awk
