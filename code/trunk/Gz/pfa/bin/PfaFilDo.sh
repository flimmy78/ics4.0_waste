#################################################################
#                                                               #
#                                                               #
#     该脚本用于获取或删除财政系统产生的信息文件                #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
IPADDR=$1
ACTDAT=$2
PFAUSR=$3
PFAPWD=$4
PFAIDIR=$5
PFAODIR=$6
ICSDIR=$HOME/$7
DATFIL=$8
BUSMOD=$9
LOGFIL=$ICSDIR/RcvLog_$2
LSTFIL=$ICSDIR/$DATFIL

echo "==========================================================" >> $LOGFIL
echo "处理PFA信息文件开始，时间【`date`】!" >> $LOGFIL
echo "IPADDR 【$IPADDR】 " >> $LOGFIL
echo "ACTDAT 【$ACTDAT】 " >> $LOGFIL
echo "PFAUSR 【$PFAUSR】 " >> $LOGFIL
echo "PFAPWD 【$PFAPWD】 " >> $LOGFIL
echo "PFAIDIR【$PFAIDIR】" >> $LOGFIL
echo "PFAODIR【$PFAODIR】" >> $LOGFIL
echo "ICSDIR 【$ICSDIR】 " >> $LOGFIL
echo "DATFIL 【$DATFIL】 " >> $LOGFIL
echo "BUSMOD 【$BUSMOD】 " >> $LOGFIL
echo "LOGFIL 【$LOGFIL】 " >> $LOGFIL
echo "LSTFIL 【$LSTFIL】 " >> $LOGFIL

if [ $BUSMOD = 0 ]
  then
    for i in `cat $LSTFIL`
    do
      echo "正在获取文件【$i】!" >> $LOGFIL
      ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
        user $PFAUSR $PFAPWD
        bin
        lcd $ICSDIR
        cd $PFAIDIR
        get $i
        bye
END
      if [ $? != 0 ]
        then
          exit -1
      fi
    done
  else
#for i in `cat $LSTFIL`
#do
      echo "正在删除文件【$DATFIL】!" >> $LOGFIL
      ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
        user $PFAUSR $PFAPWD
        bin
        lcd $ICSDIR
        cd $PFAIDIR
        delete $DATFIL
        bye
END
#done
fi
echo "处理PFA信息文件结束，时间【`date`】!\n" >> $LOGFIL
echo "==========================================================" >> $LOGFIL
exit 0