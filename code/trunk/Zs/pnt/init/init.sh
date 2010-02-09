db2 connect to db2front;
db2 "select distinct brno from pubnodinf" |grep 999 > BrLst;
for i in `cat BrLst`
do
  echo "正在维护分行【$i】数据.............................."
  for j in `ls *sql |grep -v pubdumtlr|grep -v ftp`
  do
      echo "正在维护分行【$i】表【$j】数据..................."
      sed -e "s/XXXXXX/$i/g" $j > $j.$i
      db2 -tvf $j.$i
      rm -f $j.$i
  done
  echo "分行【$i】数据维护完毕，请检查!!!!!!!!!!!!!!!!!!!!!!"
done
db2 disconnect db2front;
