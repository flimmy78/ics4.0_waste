list=`ls *RPT.XML`

for i in $list
do
	FN=`echo $i | cut -d. -f1`
	cp $i ../${FN}_446999.XML
done
