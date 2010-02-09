#################################################################
#                                                               #
#                                                               #
#     该脚本用于获取结算中心产生的批量数据文件                  #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
IPADDR=$1
ACTDAT=$2
CBSUSR=$3
CBSPWD=$4
CBSSNDDIR=$5
ICSRCVDIR=$HOME/$6
RCVFILLST=$7
LOGFIL=$ICSRCVDIR/RcvLogFil_$2
LSTFIL=$ICSRCVDIR/RcvFilLst_$2

echo "获取CBS批量文件开始，时间【`date`】!" >> $LOGFIL
echo "IPADDR【$IPADDR】" >> $LOGFIL
echo "ACTDAT【$ACTDAT】" >> $LOGFIL
echo "CBSUSR【$CBSUSR】" >> $LOGFIL
echo "CBSPWD【$CBSPWD】" >> $LOGFIL
echo "CBSSNDDIR【$CBSSNDDIR】" >> $LOGFIL
echo "ICSRCVDIR【$ICSRCVDIR】" >> $LOGFIL
echo "LSTFIL【$LSTFIL】" >> $LOGFIL

ftp -i -n $IPADDR << END 1>>$LOGFIL 2>>$LOGFIL
  user $CBSUSR $CBSPWD
  bin
  cd $CBSSNDDIR
  lcd $ICSRCVDIR
  mget $RCVFILLST
  bye
END

echo "开始生成CBS列表文件，时间【`date`】!" >> $LOGFIL
cd $ICSRCVDIR; ls TXNTYP*|grep -v dat > $LSTFIL

if [ -s $LSTFIL ]
then
  echo "获取CBS批量文件成功，时间【`date`】!\n\n\n" >>$LOGFIL
  exit 0
else
  echo "获取CBS批量文件失败，时间【`date`】!\n\n\n" >>$LOGFIL
  exit -1
fi
