set term qt size 1200,900 position 100,80

set key top center

set xrange[-0.25:0.25]
set yrange[-0.25:0.25]

set size ratio 1

set xlabel 'z_1'
set ylabel 'z_2'

set bmargin 7
set tmargin 10
set lmargin 10
set rmargin 10

bind "q" "stop = 1"
stop = 0

c = 1.8

set linetype 1 lc rgb "#d27cce"
set linetype 2 lc rgb "#00b7da"
set linetype 3 lc rgb "#ff743e"
set linetype 4 lc rgb "#68ad36"

dt = 1
do for[i=dt:1000:dt]{
  j = i % 30

  set title sprintf("realisation %d", j)
  p 'out/out01/out-n-'.j.'-0.dat' u 1:2 w p pt 7 ps c lt 1 notitle,\
    'out/out01/out-n-'.j.'-1.dat' u 1:2 w p pt 7 ps c lt 2 notitle,\
    'out/out01/out-n-'.j.'-2.dat' u 1:2 w p pt 7 ps c lt 3 notitle,\
    'out/out01/out-n-'.j.'-3.dat' u 1:2 w p pt 7 ps c lt 4 notitle

  pause 3

  if(stop){stop = i; break}
}
