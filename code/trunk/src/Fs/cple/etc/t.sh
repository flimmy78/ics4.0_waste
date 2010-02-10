list=`ls *.XML`

for i in $list
do
	echo "-------------------------------------------------"
	testxml $i 
done
