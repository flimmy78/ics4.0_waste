list=`ls *XML`

for i in $list
do
	echo $i
	diff $i ~/etc/$i 
done
