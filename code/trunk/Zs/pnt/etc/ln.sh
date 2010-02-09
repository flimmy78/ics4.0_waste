filelst=`ls *XML`
objdir=$WORKDIR/etc
for i in $filelst
do
    rm $objdir/$i
    ln $i $objdir/$i
    echo "ln $i $objdir/$i             OK!"
done
