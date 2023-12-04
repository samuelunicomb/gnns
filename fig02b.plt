set xlabel 'training step' offset 0,-2
set ylabel 'cross-entropy loss' offset -3,0

unset key

set logscale y

set bmargin 3
set tmargin 5
set lmargin 15
set rmargin 10

set size ratio 1 / 1.618

p 'out/out02/out-l.dat' u ($1 / 10):2 w l
