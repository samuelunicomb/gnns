set key top center

set size ratio 1

unset xrange
unset yrange

set xlabel 'z_1'
set ylabel 'z_2'

set bmargin 5
set lmargin 12
set rmargin 5

c = 1.8

p 'out/out01/out-0.dat' w p pt 7 ps c title 'class 0',\
  'out/out01/out-1.dat' w p pt 7 ps c title 'class 1',\
  'out/out01/out-2.dat' w p pt 7 ps c title 'class 2',\
  'out/out01/out-3.dat' w p pt 7 ps c title 'class 3'
