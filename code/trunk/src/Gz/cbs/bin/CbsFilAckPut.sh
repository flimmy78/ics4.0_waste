#################################################################
#                                                               #
#                                                               #
#     �ýű����ڻ�Ӧ�������Ĳ��������������ļ�                  #
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

echo "����CBS������Ӧ�ļ���ʼ��ʱ�䡾`date`��!" >> $LOGFIL
echo "IPADDR��$IPADDR��" >> $LOGFIL
echo "ACTDAT��$ACTDAT��" >> $LOGFIL
echo "CBSUSR��$CBSUSR��" >> $LOGFIL
echo "CBSPWD��$CBSPWD��" >> $LOGFIL
echo "CBSSNDDIR��$CBSSNDDIR��" >> $LOGFIL
echo "ICSSNDDIR��$ICSSNDDIR��" >> $LOGFIL
echo "CBSRCVDIR��$CBSRCVDIR��" >> $LOGFIL
echo "ICSRCVDIR��$ICSRCVDIR��" >> $LOGFIL
echo "LOGFIL��$LOGFIL��" >> $LOGFIL
echo "SNDLSTFIL��$SNDLSTFIL��" >> $LOGFIL
echo "RCVLSTFIL��$RCVLSTFIL��" >> $LOGFIL
echo "DELLSTFIL��$DELLSTFIL��" >> $LOGFIL

echo "1-ɾ���Ѵ���CBS�����ļ���ʼ��ʱ�䡾`date`��!" >> $LOGFIL
cd $ICSSNDDIR
for i in `cat $DELLSTFIL|grep TXNTYP`
do
  echo "����ɾ���ļ���$i��!" >> $LOGFIL
  mv $ICSRCVDIR/$i $RCVBAKDIR
  ftp -i -n $IPADDR <<END 1>>$LOGFIL 2>>$LOGFIL
    user $CBSUSR $CBSPWD
    bin
    cd $CBSSNDDIR
    delete $i
    bye
END
done

echo "2-��ʼ����CBS���׻�Ӧ�ļ���ʱ�䡾`date`��!" >> $LOGFIL
for i in `cat $SNDLSTFIL`
do
	echo "���ڴ����ļ���$i��!" >> $LOGFIL
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

echo "����CBS�����ļ���ɣ�ʱ�䡾`date`��!\n\n\n" >>$LOGFIL
#exit 0
