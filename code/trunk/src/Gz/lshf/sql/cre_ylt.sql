create table scence_xxb
(
scence_code	char(12), /* 景区代码 */
remark		char(60)  /* 景区名称 */
);

create table ylttrans
(
kh		char(21) , /* 卡号 */
rq		char(8)  , /* 日期 */
jym		char(6) ,  /* 交易码 */
jqdm		char(12) , /* 景区代码 */
jqmc		char(60) , /* 景区名称 */
mpdm		char(12) , /* 门票代码 */
mpmc		char(60) , /* 门票名称 */
dj		char(14),  /* 单价     */
sl		char(4) ,  /* 数量     */
jyje		char(14) , /* 交易金额 */
sjhm		char(14) , /* 手机号码 */
syrq		char(8) ,  /* 使用日期 */
ddbh		char(12) , /* 订单编号 */
zdbh		char(8) ,  /* 终端编号 */
fws		char(60) , /* 服务商   */
ydnr		char(60),   /* 预定内容 */
beizhu char(160),   /*备注*/
yx   char(3)
);
