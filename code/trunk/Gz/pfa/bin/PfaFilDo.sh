#################################################################
#                                                               #
#                                                               #
#     �ýű����ڻ�ȡ��ɾ������ϵͳ��������Ϣ�ļ�                #
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
echo "����PFA��Ϣ�ļ���ʼ��ʱ�䡾`date`��!" >> $LOGFIL
echo "IPADDR ��$IPADDR�� " >> $LOGFIL
echo "ACTDAT ��$ACTDAT�� " >> $LOGFIL
echo "PFAUSR ��$PFAUSR�� " >> $LOGFIL
echo "PFAPWD ��$PFAPWD�� " >> $LOGFIL
echo "PFAIDIR��$PFAIDIR��" >> $LOGFIL
echo "PFAODIR��$PFAODIR��" >> $LOGFIL
echo "ICSDIR ��$ICSDIR�� " >> $LOGFIL
echo "DATFIL ��$DATFIL�� " >> $LOGFIL
echo "BUSMOD ��$BUSMOD�� " >> $LOGFIL
echo "LOGFIL ��$LOGFIL�� " >> $LOGFIL
echo "LSTFIL ��$LSTFIL�� " >> $LOGFIL

if [ $BUSMOD = 0 ]
  then
    for i in `cat $LSTFIL`
    do
      echo "���ڻ�ȡ�ļ���$i��!" >> $LOGFIL
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
      echo "����ɾ���ļ���$DATFIL��!" >> $LOGFIL
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
echo "����PFA��Ϣ�ļ�������ʱ�䡾`date`��!\n" >> $LOGFIL
echo "==========================================================" >> $LOGFIL
exit 0