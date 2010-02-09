db2 connect to db2front;
db2 -tvf init_mngaplinf_spe.sql;
db2 -tvf init_pubaplbus_spe.sql;
db2 -tvf init_pubaplmng_spe.sql;
db2 disconnect db2front;
