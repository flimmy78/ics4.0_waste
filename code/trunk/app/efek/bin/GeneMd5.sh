# $1: ��Ҫ����MD5ֵ���ļ�,Ϊ�����ļ��Ҳ�������ʹ�þ���·��
# ���:��������������/app/ics/efek/bin/md5�ļ�����

if [ $# -ne 1 ]
then
    echo "Usage: $0 filename \n"
    exit -1
fi

cat $1 |openssl md5 > /app/ics/dat/efek/send/md5

exit 0
