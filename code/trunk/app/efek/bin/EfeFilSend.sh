#!/usr/bin/ksh
# $1: Զ������IP 182.53.201.46
# $2: Զ�������û� bcm
# $3: Զ������Ŀ¼ exchange
# $4: �����ļ�Ŀ¼ /app/ics/app/efek/tst/
# $5: �����ļ��� HDXY03010301121520141125001.test

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
