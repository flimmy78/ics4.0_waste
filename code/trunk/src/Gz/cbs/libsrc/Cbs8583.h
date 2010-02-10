struct basic_header {  /* 基本报文头 */
  char block_type[3] ;  /* 块标识 {1： */
  char version  ;       /* 版本号 */
  char datetime[14];    /* 发起日期和时间 */
  char packagelen[6];   /* 报文长度 */
  char processtype   ;  /* 应用系统处理类型 C：非文件类, F：文件类 */
  char transtype   ;    /* 传输类型: 0：即时回应类, 1：存储转发类  */
  char msgformat   ;    /* 正文体数据格式标准 0：自定义, 1：ISO8583  */
  char msgstruct[6];    /* 报文结构 单笔支付：1245, 通知类/管理类：145 */
  char systemnum[4];    /* 系统号 */
  char msgserial[16];   /* 信息序号: "系统号+信息序号" 为唯一标识 */
  char transcode[4];    /* 交易种类 */
  char msgpri    ;      /* 信息优先级 填写0 */
  char msgid[4];        /* 报文类型标识符 */
  char maccode[4];      /* 验证码 填空格 */
  char reserved[16];    /* 预留位 */
  char endflag[1]   ;      /* 结束标志 } */
};

struct single_header{  /* 单笔应用报文头 */
  char block_type[3] ;  /* 块标识 {2： */
  char sendcode[12]  ;  /* 发起方代码 */
  char recvcode[12];    /* 接收方代码 */
  char consigndate[8];  /* 委托日期 CCYYMMDD */
  char refernum[8];     /* 凭证提交号 */
  char currencycode[3]; /* 交易货币代码 CNY，HKD，USD */
  char money[15];       /* 交易金额 */
  char msgserial[16];   /* 参照信息序号: 在应答时的原信息序号 */
  char returncode[8];   /* 返回码 */
  char reserved[16];    /* 预留位 */
  char endflag[1]   ;      /* 结束标志 } */
} ;

struct batch_header{  /* 批量应用报文头 */
  char block_type[3] ;  /* 块标识 {3： */
  char date[8]  ;       /* 清算日期 CCYYMMDD */
  char round[1];        /* 清算场次 */
  char sendnum[4];      /* 发起方系统号 */
  char sendcode[12];    /* 发起方代码 */
  char recvnum[4];      /* 接收方系统号 */
  char recvcode[12];    /* 接收方代码 */
  char transtype[4];    /* 交易种类 */
  char filename[60];    /* 文件名 */
  char referfile[60];   /* 参照文件名 */
  char batchserial[8];  /* 批量包序号 */
  char referserial[8];  /* 参考批量包序号 */
  char customserial[8]; /* 客户批量包序号 */
  char transnum[10];    /* 交易总笔数 */
  char transmoney[16];  /* 交易总金额 */
  char refusenum[10];   /* 拒绝支付总笔数 */
  char refusemoney[16]; /* 拒绝支付总金额 */
  char returncode[8];   /* 返回码 */
  char reserved[16];    /* 预留位 */
  char endflag[1]  ;      /* 结束标志 } */
} ;

struct batch_record_header{  /* 批量记录应用报文头 */
  char block_type[3] ;  /* 块标识 {R： */
  char msgserial[16];   /* 信息序号 */
  char referserial[16]; /* 参照信息序号 */
  char recordlen[6];    /* 记录体长度:（块标识＋报文内容＋结束标志）的长度 */
  char reserved[16];    /* 预留位 */
  char endflag[1]   ;      /* 结束标志 } */
};

struct msg_tail {  /* 报文尾 */
  char block_type[3];  /* 块标识 {5: */
  char maccode[64];    /* 校验码 */
  char endflag[1]   ;     /* 结束标志 } */
}; 
struct batch_header_fieldlen {
  int fieldlength;
} batch_headerlen[]=
{ 8, 1, 4,12, 4,12,
  4,60,60, 8, 8, 8,
 10,16,10,16, 8,16
};
#define MAX_BATCH_HEAD_NUM 18

struct pack_info {
 int fieldbitmap;  /* 位元号 */
 int fieldbitidx;  /* 序号 */
 int fieldlength;  /* 数据元长度 */
 int headlength;   /* 实际长度 */ 
} pack_data_info[] =
{
  0,0,16,0,   /* 信息序号 */
  0,0,16,0,   /* 信息序号 */
  0,0,4,0,    /* 报文类型标识符 */
  3,0,6,0,    /* 3 交易种类细分类型 */
  4,0,15,0,
  7,0,10,0,
  11,0,12,0,
  12,0,14,0,
  15,0,8,0,
  24,0,3,0,
  26,0,4,0,
  30,0,32,0,
  40,0,3,0,
  43,1,18,4,
  43,2,18,0,
  44,1,14,4,
  44,2,16,0,
  44,3,14,0,
  44,4,16,0,
  44,5,8,0,
  48,1,1,3,
  48,2,4,0,
  48,3,3,0,
  48,4,1,0,
  48,5,1,0,
  48,6,5,0,
  48,7,2,0,
  48,8,1,0,
  48,9,3,0,
  48,10,3,0,
  48,11,6,0,
  48,12,1,0,
  56,0,32,2,
  62,1,12,3,
  62,2,12,0,
  62,3,9,0,
  62,4,35,0,
  62,5,60,0,
  62,6,8,0,
  63,1,12,3,
  63,2,12,0,
  63,3,9,0,
  63,4,35,0,
  63,5,60,0,
  66,0,60,3,
  67,0,2,0,
  74,1,15,0,
  74,2,10,0,
  74,7,15,0,
  74,8,10,0,
  93,0,4,2,
  102,0,20,0,
  103,0,20,0,
  111,0,300,4,
  112,0,40,4,
  113,0,12,4,
  115,1,1,4,
  115,2,30,0,
  115,3,20,0,
  115,4,60,0,
  115,5,2,0,
  115,6,12,0,
  115,7,11,0,
  115,8,8,0,
  124,0,80,4,
  125,0,60,4,
  126,0,80,4,
  127,0,60,4
};
#define MAX_DATA_NUM 68
