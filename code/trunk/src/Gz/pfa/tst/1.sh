if [ $# -ne 1 ]
then
  echo "\n\t �﷨��Clr �����ļ��� \n"
  exit
fi

./tcp_cli 182.53.15.200 35850 $1 1 0
