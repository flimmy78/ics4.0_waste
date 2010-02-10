ftp -n $1 << !
user cadftp Asdf1234
cd $2
lcd $3
bin
prompt
mput $4
bye
!
