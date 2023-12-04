set xrange[-1.1:1.1]
set yrange[-1.1:1.1]

set size ratio 1

set xlabel 'z_1'
set ylabel 'z_2'

set bmargin 7
set tmargin 7
set lmargin 12
set rmargin 10

c = 1.8

set linetype 1 lc rgb "#d27cce"
set linetype 2 lc rgb "#00b7da"
set linetype 3 lc rgb "#ff743e"
set linetype 4 lc rgb "#68ad36"

p 'out/out02/out-e-2000-0.dat' u 1:2 w p pt 7 ps c lt 1 notitle,\
  'out/out02/out-e-2000-1.dat' u 1:2 w p pt 7 ps c lt 2 notitle,\
  'out/out02/out-e-2000-2.dat' u 1:2 w p pt 7 ps c lt 3 notitle,\
  'out/out02/out-e-2000-3.dat' u 1:2 w p pt 7 ps c lt 4 notitle
