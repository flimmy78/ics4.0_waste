#################################################################
#                                                               #
#                                                               #
#     该脚本用于获取结算中心产生的手续费文件                    #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
SrcDir=$1
DesDir=$2
SrcFil=$3
DesFil=$4
LOGFIL=$HOME/$SrcDir/MovFil.Log

echo "\n\n\n处理CBS手续费文件开始，时间【`date`】!" >> $LOGFIL
echo "SrcDir【$SrcDir】" >> $LOGFIL
echo "DesDir【$DesDir】" >> $LOGFIL
echo "SrcFil【$SrcFil】" >> $LOGFIL
echo "DesFil【$DesFil】" >> $LOGFIL
cp $HOME/$SrcDir/$SrcFil $HOME/$DesDir/$DesFil
if [ -s $HOME/$DesDir/$DesFIL ]
  then
    echo "获取CBS手续费文件成功，时间【`date`】!" >>$LOGFIL
    exit 0
  else
    echo "获取CBS信息文件失败，时间【`date`】!" >>$LOGFIL
    exit -1
fi
