cp *.XML ~/etc/
hishutdown -g pfte
sleep 10
hiboot -g pfte
sleep 10
icsps -g pfte

sleep 10
sh l.sh
