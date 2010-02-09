if [ $# -ne 1 ]
then
  echo "\n\t 语法：Clr 数据文件名 \n"
  exit
fi

./tcp_cli 182.53.15.200 35850 $1 1 0
