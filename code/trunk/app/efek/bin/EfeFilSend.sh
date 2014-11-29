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



echo "cd $3" > /app/ics/app/efek/dat/ftpTmp
echo "lcd $4"      >> /app/ics/app/efek/dat/ftpTmp
echo "-put $5"     >> /app/ics/app/efek/dat/ftpTmp
echo "quit"        >> /app/ics/app/efek/dat/ftpTmp

sftp -b /app/ics/app/efek/dat/ftpTmp $2@$1

exit 0
