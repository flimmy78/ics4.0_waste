cp *.XML ~/etc/
hishutdown -s CTDEPFT2
hishutdown -s OFTEPFT1
sleep 2
hiboot -s CTDEPFT2
hiboot -s OFTEPFT1
sleep 2
icsps -g pfte

sleep 10
sh l.sh
