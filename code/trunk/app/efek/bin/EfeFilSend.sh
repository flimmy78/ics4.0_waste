#!/usr/bin/ksh
# $1: 远程主机IP 182.53.201.46
# $2: 远程主机用户 bcm
# $3: 远程主机目录 exchange
# $4: 本地文件目录 /app/ics/app/efek/tst/
# $5: 本地文件名 HDXY03010301121520141125001.test

if [ $# -ne 5 ]
then
    echo "Usage: $0 ip username remote-dir local-dir local-file\n"
    echo "Usage: $0 182.53.201.46 bcm exchange /app/ics/app/efek/tst/ HDXY03010301121520141125001.test\n"
    exit -1
fi

tmpFileName=/app/ics/dat/efek/ftpSendTmp

echo "cd $3"    >  $tmpFileName
echo "lcd $4"   >> $tmpFileName
echo "-put $5"  >> $tmpFileName
echo "quit"     >> $tmpFileName

sftp -b $tmpFileName $2@$1

rm $tmpFileName
exit 0
