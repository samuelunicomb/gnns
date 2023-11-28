{
  # file index
  fold = f
  f = $1
  s = $2

  # close previous files, awk has a limit on number of files it can have open
  if(NR > 1 && f != fold){
    close("out/out00/out-n-"fold".dat")
    close("out/out00/out-d-"fold".dat")
  }

  if(s == "nn"){
    print $0 > ("out/out00/out-n-"f".dat")
  }else if(s == "data"){
    print $0 > ("out/out00/out-d-"f".dat")
  }
}
