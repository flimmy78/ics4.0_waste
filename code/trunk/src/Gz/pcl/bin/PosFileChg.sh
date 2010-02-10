#################################################################
#                                                               #
#                                                               #
#     该脚本用于将银联POS文件中的 "^M" 字符去掉                 #
#                                                               #
#                                                               #
#################################################################
HOME=/app/ics
FILEDIR=$HOME/dat/term/recv
POSFILE=$FILEDIR/$1
TMPFILE=$POSFILE.tmp

#####备份文件
cp -f $POSFILE $TMPFILE
if [ $? -ne 0 ]
then
	exit 1
fi
#####替换非法字符
sed -e "s///g" $TMPFILE > $POSFILE
if [ $? -ne 0 ]
then
	exit 2
fi
#####删除临时文件
rm -f $TMPFILE
if [ $? -ne 0 ]
then
	exit 3
fi
