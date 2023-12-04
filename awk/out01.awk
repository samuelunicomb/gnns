{
  # file index
  fold = f
  f = $1

  # node class
  c = $5

  # close previous files, awk has a limit on number of files it can have open
  if(NR > 1 && f != fold){
    close("out/out01/out-n-"fold"-0.dat")
    close("out/out01/out-n-"fold"-1.dat")
    close("out/out01/out-n-"fold"-2.dat")
    close("out/out01/out-n-"fold"-3.dat")
    close("out/out01/out-l-"fold"-0.dat")
    close("out/out01/out-l-"fold"-1.dat")
    close("out/out01/out-l-"fold"-2.dat")
    close("out/out01/out-l-"fold"-3.dat")
  }

  if($2 == "nonlinear")
    print $3 " " $4 > ("out/out01/out-n-"f"-"c".dat")

  if($2 == "linear")
    print $3 " " $4 > ("out/out01/out-l-"f"-"c".dat")
}
