{
  # file index
  fold = f
  f = $1

  # node class
  c = $5

  # close previous files, awk has a limit on number of files it can have open
  if(NR > 1 && f != fold){
    close("out/out02/out-e-"fold"-0.dat")
    close("out/out02/out-e-"fold"-1.dat")
    close("out/out02/out-e-"fold"-2.dat")
    close("out/out02/out-e-"fold"-3.dat")
  }

  print $3 " " $4 > ("out/out02/out-e-"f"-"c".dat")
}
