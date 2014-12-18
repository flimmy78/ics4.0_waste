# $1: 需要计算MD5值的文件,为避免文件找不到建议使用绝对路径
# 输出:将计算结果放置在/app/ics/efek/bin/md5文件里面

if [ $# -ne 1 ]
then
    echo "Usage: $0 filename \n"
    exit -1
fi

cat $1 |openssl md5 > /app/ics/dat/efek/send/md5

exit 0
