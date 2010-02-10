cp *.XML ~/etc/
#hishutdown -s CTDEPFT2
hishutdown -s OFTEPFT1
#hishutdown -s STDEPFT2
hishutdown -s CTMEPFT1

sleep 2
#hiboot -s CTDEPFT2
hiboot -s OFTEPFT1
#hiboot -s STDEPFT2
hiboot -s CTMEPFT1
sleep 2
icsps -g pfte

sleep 2
sh l.sh
