#################################################################
#                                                               #
#                                                               #
#     该脚本用于回应结算中心产生的批量数据文件                  #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
RCVBAKDIR=$HOME/dat/cbs/rcvbak
SNDBAKDIR=$HOME/dat/cbs/sndbak
IPADDR=$1
ACTDAT=$2
CBSUSR=$3
CBSPWD=$4
CBSSNDDIR=$5
ICSSNDDIR=$HOME/$6
CBSRCVDIR=$7
ICSRCVDIR=$HOME/$8
LOGFIL=$ICSSNDDIR/SndLogFil_$2
SNDLSTFIL=$ICSSNDDIR/SndFilLst_$2
RCVLSTFIL=$ICSRCVDIR/RcvFilLst_$2
DELLSTFIL=$ICSSNDDIR/DelFilLst_$2

echo "生产CBS批量回应文件开始，时间【`date`】!" >> $LOGFIL
echo "IPADDR【$IPADDR】" >> $LOGFIL
echo "ACTDAT【$ACTDAT】" >> $LOGFIL
echo "CBSUSR【$CBSUSR】" >> $LOGFIL
echo "CBSPWD【$CBSPWD】" >> $LOGFIL
echo "CBSSNDDIR【$CBSSNDDIR】" >> $LOGFIL
echo "ICSSNDDIR【$ICSSNDDIR】" >> $LOGFIL
echo "CBSRCVDIR【$CBSRCVDIR】" >> $LOGFIL
echo "ICSRCVDIR【$ICSRCVDIR】" >> $LOGFIL
echo "LOGFIL【$LOGFIL】" >> $LOGFIL
echo "SNDLSTFIL【$SNDLSTFIL】" >> $LOGFIL
echo "RCVLSTFIL【$RCVLSTFIL】" >> $LOGFIL
echo "DELLSTFIL【$DELLSTFIL】" >> $LOGFIL

echo "1-删除已处理CBS批量文件开始，时间【`date`】!" >> $LOGFIL
cd $ICSSNDDIR
for i in `cat $DELLSTFIL|grep TXNTYP`
do
  echo "正在删除文件【$i】!" >> $LOGFIL
  mv $ICSRCVDIR/$i $RCVBAKDIR
  ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
    user $CBSUSR $CBSPWD
    bin
    cd $CBSSNDDIR
    delete $i
    bye
END
done

echo "2-开始传送CBS收妥回应文件，时间【`date`】!" >> $LOGFIL
for i in `cat $SNDLSTFIL`
do
	echo "正在传送文件【$i】!" >> $LOGFIL
  ftp -i -n $IPADDR << END 1>>$LOGFIL 2>>$LOGFIL
    user $CBSUSR $CBSPWD
    bin
    cd $CBSRCVDIR
    lcd $ICSSNDDIR
  	put $i
    bye
END
  mv $ICSSNDDIR/$i $SNDBAKDIR
done

echo "传送CBS批量文件完成，时间【`date`】!\n\n\n" >>$LOGFIL
#exit 0
