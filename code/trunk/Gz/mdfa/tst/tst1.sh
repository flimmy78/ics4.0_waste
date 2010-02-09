if [ $# -ne 1 ] 
then
  echo "\n\t ”Ô∑®£∫in.sh TstDat \n"
  exit
fi
tcp_cli 182.53.1.6 32410 $1 1 0
