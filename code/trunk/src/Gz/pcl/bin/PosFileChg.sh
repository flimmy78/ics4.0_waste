#################################################################
#                                                               #
#                                                               #
#     �ýű����ڽ�����POS�ļ��е� "^M" �ַ�ȥ��                 #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
FILEDIR=$HOME/dat/term/recv
POSFILE=$FILEDIR/$1
TMPFILE=$POSFILE.tmp

#####�����ļ�
cp -f $POSFILE $TMPFILE
if [ $? -ne 0 ]
then
	exit 1
fi
#####�滻�Ƿ��ַ�
sed -e "s///g" $TMPFILE > $POSFILE
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
