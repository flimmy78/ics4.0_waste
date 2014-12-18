#!/usr/bin/ksh
# $1: Զ������IP 182.53.201.46
# $2: Զ�������û� bcm
# $3: Զ������Ŀ¼ exchange
# $4: �����ļ�Ŀ¼ /app/ics/app/efek/tst/
# $5: �����ص��ļ��� PTFS_00301000306122014112900717.txt

if [ $# -ne 5 ]
then
    echo "Usage: $0 ip username remote-dir local-dir local-file\n"
    echo "Usage: $0 182.53.201.46 bcm exchange /app/ics/app/efek/tst/ PTFS_00301000306122014112900717.txt\n"
    exit -1
fi

tmpFileName=/app/ics/dat/efek/send/ftpRecvTmp

echo "cd $3" > $tmpFileName
echo "lcd $4"  >> $tmpFileName
echo "-get $5" >> $tmpFileName
echo "quit"    >> $tmpFileName

sftp -b $tmpFileName $2@$1

rm $tmpFileName

exit 0
