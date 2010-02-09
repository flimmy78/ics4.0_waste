#################################################################
#                                                               #
#                                                               #
#     该脚本用于回应结算中心产生的批量数据文件                  #
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

echo "生产CBS批量定期借记回应文件开始，时间【`date`】!" >> $LOGFIL
echo "IPADDR【$IPADDR】" >> $LOGFIL
echo "ACTDAT【$ACTDAT】" >> $LOGFIL
echo "CBSUSR【$CBSUSR】" >> $LOGFIL
echo "CBSPWD【$CBSPWD】" >> $LOGFIL
echo "ICSSNDDIR【$ICSSNDDIR】" >> $LOGFIL
echo "CBSRCVDIR【$CBSRCVDIR】" >> $LOGFIL
echo "ICSSNDFIL【$ICSSNDFIL】" >> $LOGFIL
echo "SNDFSIZE【$SNDFSIZE】" >> $LOGFIL
echo "LOGFIL【$LOGFIL】" >> $LOGFIL
echo "FIL8583NAM【$FIL8583NAM】" >> $LOGFIL

echo "1-正在传送定期借记回应文件【$FIL8583NAM】!" >> $LOGFIL
ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
	user $CBSUSR $CBSPWD
	bin
	cd $CBSRCVDIR
	lcd $ICSSNDDIR
	put $ICSSNDFIL $FIL8583NAM
	bye
END

echo "2-删除临时文件并做保留发送文件处理，时间【`date`】!" >> $LOGFIL
cd $ICSSNDDIR;rm -f $ICSSNDDIR/*XXXXXXXX
mv $ICSSNDDIR/$ICSSNDFIL $SNDBAKDIR
echo "传送CBS批量定期借记文件完成，时间【`date`】!\n\n\n" >>$LOGFIL
#exit 0
