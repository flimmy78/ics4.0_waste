#################################################################
#                                                               #
#                                                               #
#     �ýű����ڴ��͵�����ҵ�������ļ�                          #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
SNDBAKDIR=$HOME/dat/cbs/sndbak
IPADDR=$1
ACTDAT=$2
CBSUSR=$3
CBSPWD=$4
ICSSNDDIR=$HOME/$5
CBSRCVDIR=$6
ICSSNDFIL=$7
SNDFSIZE=$8
FIL8583NAM=$7$8
LOGFIL=$ICSSNDDIR/SndLogFil_$2

echo "��ʼ��������ҵ�������ļ���ʱ�䡾`date`��!" >> $LOGFIL
echo "IPADDR��$IPADDR��" >> $LOGFIL
echo "ACTDAT��$ACTDAT��" >> $LOGFIL
echo "CBSUSR��$CBSUSR��" >> $LOGFIL
echo "CBSPWD��$CBSPWD��" >> $LOGFIL
echo "ICSSNDDIR��$ICSSNDDIR��" >> $LOGFIL
echo "CBSRCVDIR��$CBSRCVDIR��" >> $LOGFIL
echo "ICSSNDFIL��$ICSSNDFIL��" >> $LOGFIL
echo "SNDFSIZE��$SNDFSIZE��" >> $LOGFIL
echo "LOGFIL��$LOGFIL��" >> $LOGFIL
echo "FIL8583NAM��$FIL8583NAM��" >> $LOGFIL

echo "1-���ڴ�������ҵ�������ļ���$FIL8583NAM��!" >> $LOGFIL
ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
	user $CBSUSR $CBSPWD
	bin
	cd $CBSRCVDIR
	lcd $ICSSNDDIR
	put $ICSSNDFIL $FIL8583NAM
	bye
END

echo "2-ɾ����ʱ�ļ��������������ļ�����ʱ�䡾`date`��!" >> $LOGFIL
cd $ICSSNDDIR;rm -f $ICSSNDDIR/*XXXXXXXX
mv $ICSSNDDIR/$ICSSNDFIL $SNDBAKDIR
echo "��������ҵ�������ļ���ɣ�ʱ�䡾`date`��!\n\n\n" >>$LOGFIL
#exit 0
