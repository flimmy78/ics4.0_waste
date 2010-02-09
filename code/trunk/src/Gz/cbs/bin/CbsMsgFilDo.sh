#################################################################
#                                                               #
#                                                               #
#     该脚本用于获取结算中心产生的信息文件                      #
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
MODE=$7
FILNAM=$8
LOGFIL=$ICSRCVDIR/RcvLogFil_$2
LSTFIL=$ICSRCVDIR/FilLst_$2

echo "处理CBS信息文件开始，时间【`date`】!" >> $LOGFIL
echo "IPADDR【$IPADDR】" >> $LOGFIL
echo "ACTDAT【$ACTDAT】" >> $LOGFIL
echo "CBSUSR【$CBSUSR】" >> $LOGFIL
echo "CBSPWD【$CBSPWD】" >> $LOGFIL
echo "CBSSNDDIR【$CBSSNDDIR】" >> $LOGFIL
echo "ICSRCVDIR【$ICSRCVDIR】" >> $LOGFIL
echo "LSTFIL【$LSTFIL】" >> $LOGFIL
echo "FILNAM【$FILNAM】" >> $LOGFIL

if [ $MODE = 0 ]
  then
    rm -f $ICSRCVDIR/$FILNAM
    ftp -i -n $IPADDR << END 1>>$LOGFIL 2>>$LOGFIL
      user $CBSUSR $CBSPWD
      bin
      cd $CBSSNDDIR
      lcd $ICSRCVDIR
      mget $FILNAM
      bye
END
    echo "开始生成CBS信息文件列表，时间【`date`】!" >> $LOGFIL
    cd $ICSRCVDIR; ls $FILNAM|grep -v FEERPT|sort > $LSTFIL

    if [ -s $LSTFIL ]
      then
        echo "获取CBS信息文件成功，时间【`date`】!\n\n\n" >>$LOGFIL
        exit 0
      else
        echo "获取CBS信息文件失败，时间【`date`】!\n\n\n" >>$LOGFIL
        exit -1
    fi
  else
    for i in `cat $LSTFIL`
    do
      echo "正在删除文件【$i】!" >> $LOGFIL
      ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
        user $CBSUSR $CBSPWD
        bin
        cd $CBSSNDDIR
        delete $i
        bye
END
    done
fi
