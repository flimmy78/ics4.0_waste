struct basic_header {  /* ��������ͷ */
  char block_type[3] ;  /* ���ʶ {1�� */
  char version  ;       /* �汾�� */
  char datetime[14];    /* �������ں�ʱ�� */
  char packagelen[6];   /* ���ĳ��� */
  char processtype   ;  /* Ӧ��ϵͳ�������� C�����ļ���, F���ļ��� */
  char transtype   ;    /* ��������: 0����ʱ��Ӧ��, 1���洢ת����  */
  char msgformat   ;    /* ���������ݸ�ʽ��׼ 0���Զ���, 1��ISO8583  */
  char msgstruct[6];    /* ���Ľṹ ����֧����1245, ֪ͨ��/�����ࣺ145 */
  char systemnum[4];    /* ϵͳ�� */
  char msgserial[16];   /* ��Ϣ���: "ϵͳ��+��Ϣ���" ΪΨһ��ʶ */
  char transcode[4];    /* �������� */
  char msgpri    ;      /* ��Ϣ���ȼ� ��д0 */
  char msgid[4];        /* �������ͱ�ʶ�� */
  char maccode[4];      /* ��֤�� ��ո� */
  char reserved[16];    /* Ԥ��λ */
  char endflag[1]   ;      /* ������־ } */
};

struct single_header{  /* ����Ӧ�ñ���ͷ */
  char block_type[3] ;  /* ���ʶ {2�� */
  char sendcode[12]  ;  /* ���𷽴��� */
  char recvcode[12];    /* ���շ����� */
  char consigndate[8];  /* ί������ CCYYMMDD */
  char refernum[8];     /* ƾ֤�ύ�� */
  char currencycode[3]; /* ���׻��Ҵ��� CNY��HKD��USD */
  char money[15];       /* ���׽�� */
  char msgserial[16];   /* ������Ϣ���: ��Ӧ��ʱ��ԭ��Ϣ��� */
  char returncode[8];   /* ������ */
  char reserved[16];    /* Ԥ��λ */
  char endflag[1]   ;      /* ������־ } */
} ;

struct batch_header{  /* ����Ӧ�ñ���ͷ */
  char block_type[3] ;  /* ���ʶ {3�� */
  char date[8]  ;       /* �������� CCYYMMDD */
  char round[1];        /* ���㳡�� */
  char sendnum[4];      /* ����ϵͳ�� */
  char sendcode[12];    /* ���𷽴��� */
  char recvnum[4];      /* ���շ�ϵͳ�� */
  char recvcode[12];    /* ���շ����� */
  char transtype[4];    /* �������� */
  char filename[60];    /* �ļ��� */
  char referfile[60];   /* �����ļ��� */
  char batchserial[8];  /* ��������� */
  char referserial[8];  /* �ο���������� */
  char customserial[8]; /* �ͻ���������� */
  char transnum[10];    /* �����ܱ��� */
  char transmoney[16];  /* �����ܽ�� */
  char refusenum[10];   /* �ܾ�֧���ܱ��� */
  char refusemoney[16]; /* �ܾ�֧���ܽ�� */
  char returncode[8];   /* ������ */
  char reserved[16];    /* Ԥ��λ */
  char endflag[1]  ;      /* ������־ } */
} ;

struct batch_record_header{  /* ������¼Ӧ�ñ���ͷ */
  char block_type[3] ;  /* ���ʶ {R�� */
  char msgserial[16];   /* ��Ϣ��� */
  char referserial[16]; /* ������Ϣ��� */
  char recordlen[6];    /* ��¼�峤��:�����ʶ���������ݣ�������־���ĳ��� */
  char reserved[16];    /* Ԥ��λ */
  char endflag[1]   ;      /* ������־ } */
};

struct msg_tail {  /* ����β */
  char block_type[3];  /* ���ʶ {5: */
  char maccode[64];    /* У���� */
  char endflag[1]   ;     /* ������־ } */
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
 int fieldbitmap;  /* λԪ�� */
 int fieldbitidx;  /* ��� */
 int fieldlength;  /* ����Ԫ���� */
 int headlength;   /* ʵ�ʳ��� */ 
} pack_data_info[] =
{
  0,0,16,0,   /* ��Ϣ��� */
  0,0,16,0,   /* ��Ϣ��� */
  0,0,4,0,    /* �������ͱ�ʶ�� */
  3,0,6,0,    /* 3 ��������ϸ������ */
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
