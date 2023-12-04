set key top center

set xrange[-1:1]
set yrange[-1.2:1.5]

set xlabel 'x'
set ylabel 't'

set bmargin 5
set lmargin 12
set rmargin 5

bind "q" "stop = 1"
stop = 0

dt = 1000
do for[i=dt:999000:dt]{
  j = i

  set title sprintf("timestep %d", i / 1000) font ',13'
  p 'out/out00/out-n-'.j.'.dat' u 3:4 w l lt 1 title 'f(x, w)',\
    'out/out00/out-n-'.j.'.dat' u 3:5 w l lt 2 dt 2 title 'hidden layers',\
    'out/out00/out-n-'.j.'.dat' u 3:6 w l lt 2 dt 2 notitle,\
    'out/out00/out-n-'.j.'.dat' u 3:7 w l lt 2 dt 2 notitle,\
    'out/out00/out-d-0.dat' u 3:4 w p pt 7 lt 1 notitle,\

  if(j == dt){
    pause 1
  }else{
    pause 0.03
  }

  if(stop){stop = i; break}
}
