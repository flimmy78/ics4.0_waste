#################################################################
#                                                               #
#                                                               #
#     �ýű����ڻ�ȡ�������Ĳ������������ļ�                    #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
SrcDir=$1
DesDir=$2
SrcFil=$3
DesFil=$4
LOGFIL=$HOME/$SrcDir/MovFil.Log

echo "\n\n\n����CBS�������ļ���ʼ��ʱ�䡾`date`��!" >> $LOGFIL
echo "SrcDir��$SrcDir��" >> $LOGFIL
echo "DesDir��$DesDir��" >> $LOGFIL
echo "SrcFil��$SrcFil��" >> $LOGFIL
echo "DesFil��$DesFil��" >> $LOGFIL
cp $HOME/$SrcDir/$SrcFil $HOME/$DesDir/$DesFil
if [ -s $HOME/$DesDir/$DesFIL ]
  then
    echo "��ȡCBS�������ļ��ɹ���ʱ�䡾`date`��!" >>$LOGFIL
    exit 0
  else
    echo "��ȡCBS��Ϣ�ļ�ʧ�ܣ�ʱ�䡾`date`��!" >>$LOGFIL
    exit -1
fi
