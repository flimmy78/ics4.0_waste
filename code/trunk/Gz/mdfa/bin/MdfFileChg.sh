#################################################################
#                                                               #
#                                                               #
#     �ýű����ڽ�ҽ��Mdf�ļ��е� "^M" �ַ�ȥ��                 #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
FILEDIR=$HOME/dat/mdf/recv
MDFFILE=$FILEDIR/$1
TMPFILE=$MDFFILE.tmp

#####�����ļ�
cp -f $MDFFILE $TMPFILE
if [ $? -ne 0 ]
then
	exit 1
fi
#####�滻�Ƿ��ַ�
sed -e "s///g" $TMPFILE > $MDFFILE
if [ $? -ne 0 ]
then
	exit 2
fi
#####ɾ����ʱ�ļ�
rm -f $TMPFILE
if [ $? -ne 0 ]
then
	exit 3
fi
