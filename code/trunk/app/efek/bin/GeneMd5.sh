# $1: ��Ҫ����MD5ֵ���ļ�
# ���:��������������/app/ics/efek/bin/md5�ļ�����

if [ $# -ne 1 ]
then
    echo "Usage: $0 filename \n"
    exit -1
fi

cat $1 |openssl md5 > /app/ics/efek/bin/md5

exit 0
