unset key

set format y '10^{%L}'

set size ratio 1 / 1.618

set lmargin 18
set rmargin 6
set bmargin 4

set xlabel 'sorted weight index' offset 0,-3
set ylabel 'relative error' offset -4,0

p 'out/out03/out.dat' u 0:3
