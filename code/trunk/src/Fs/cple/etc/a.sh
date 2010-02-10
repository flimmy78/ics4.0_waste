cp *.XML ~/etc
hishutdown -s S.SCHSVR
sleep 2 
hishutdown -g cple
sleep 2
hiboot -s S.SCHSVR
sleep 2
hiboot -g cple
sleep 10
icsps -s S.SCHVER
icsps -g cple
