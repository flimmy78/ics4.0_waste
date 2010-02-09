db2 connect to db2front;
db2 "select distinct BrNo from puborginf" |grep 999 > BrLst
for i in `cat BrLst`
  do
    echo "正在维护分行【$i】数据.............................."
    for j in `ls *sql |grep -v pubdumtlr|grep -v pubftpcfg`
      do
       echo "正在维护分行【$i】表【$j】数据..................."
       sed -e "s/XXXXXX/$i/g" $j > $j.$i
       db2 -tvf $j.$i
       rm -f $j.$i
      done
    echo "分行【$i】数据维护完毕，请检查!!!!!!!!!!!!!!!!!!!!!!"
  done
rm -f BrLst
echo "提交业务数据......................"
#db2 -tvf init_pubdumtlr_pft.sql
#db2 -tvf init_pubftpcfg_pft.sql
