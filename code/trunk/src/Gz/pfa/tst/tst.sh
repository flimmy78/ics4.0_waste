if [ $# -ne 1 ]
then
  echo "\n\t 语法：Clr 数据文件名 \n"
  exit
fi

./tcp_cli 182.53.1.6 30520 $1 1 8
