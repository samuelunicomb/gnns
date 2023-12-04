set xrange[-0.25:0.25]
set yrange[-0.25:0.25]

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

p 'out/out01/out-l-0-0.dat' w p pt 7 ps 1 lt 1 title 'nonlinear',\
  'out/out01/out-l-0-1.dat' w p pt 7 ps 1 lt 2 notitle,\
  'out/out01/out-l-0-2.dat' w p pt 7 ps 1 lt 3 notitle,\
  'out/out01/out-l-0-3.dat' w p pt 7 ps 1 lt 4 notitle,\
  'out/out01/out-n-0-0.dat' w p pt 1 ps 2 lt 1 title 'linear',\
  'out/out01/out-n-0-1.dat' w p pt 1 ps 2 lt 2 notitle,\
  'out/out01/out-n-0-2.dat' w p pt 1 ps 2 lt 3 notitle,\
  'out/out01/out-n-0-3.dat' w p pt 1 ps 2 lt 4 notitle
