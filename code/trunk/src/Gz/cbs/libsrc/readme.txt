�ļ�ÿ���ֶ���"|"�ָ���
��һ�нṹ˵����
  1  char date[8]  ;       /* �������� CCYYMMDD */
  2  char round[1];        /* ���㳡�� */
  3  char sendnum[4];      /* ����ϵͳ�� */
  4  char sendcode[12];    /* ���𷽴��� */
  5  char recvnum[4];      /* ���շ�ϵͳ�� */
  6  char recvcode[12];    /* ���շ����� */
  7  char transtype[4];    /* �������� */
  8  char filename[60];    /* �ļ��� */
  9  char referfile[60];   /* �����ļ��� */
  10 char batchserial[8];  /* ��������� */
  11 char referserial[8];  /* �ο���������� */
  12 char customserial[8]; /* �ͻ���������� */
  13 char transnum[10];    /* �����ܱ��� */
  14 char transmoney[16];  /* �����ܽ�� */
  15 char refusenum[10];   /* �ܾ�֧���ܱ��� */
  16 char refusemoney[16]; /* �ܾ�֧���ܽ�� */
  17 char returncode[8];   /* ������ */
  18 char reserved[16];    /* Ԥ��λ */
  
�ڶ��У��������½ṹ˵����
 0  sysrefer char(16),       /* ��Ϣ���(R) */
 0  sysrefer1  char(16)      /* ���� */
 1  msgid  char(4) ,         /* �������ͱ�ʶ�� */
 2  transtype char(6) ,      /*  3 ��������ϸ������ */
 3  transmoney char(15) ,    /*  4 ���׽�� */
 4  datetime char(10) ,      /*  7 ���׷������ں�ʱ��  char(MMDDhhmmss)*/
 5  directbank char(12) ,    /* 11 ֱ�������� */
 6  wtdate char(14) ,        /* 12 ί������ char(CCYYMMDDhhmmss) */
 7  qsdate char(8) ,         /* 15 �������� char(CCYYMMDD) */
 8  kindid char(3) ,         /* 24 ��ѯ/֪ͨ�����ʶ 000�������ʻ������ѯ
                                                 001���ͻ���Ȩ����ѯ
                                                 002��������ѯ/�˶Բ�ѯ 
                                                 999��ͨ�ò�ѯ  */
 9  district char(4) ,       /* 26 ������ */ 
 10 currency char(32) ,      /* 30 ���׻��Ҵ��� CNY:����� HKD:�۱� USD:��Բ */
 11 inputmode char(3) ,      /* 40 ��������뷽ʽ�� 021 �������룬�Ҵ�PIN��
                                                022 �������룬�Ҳ���PIN��
                                                011 �ֹ���ʽ���Ҵ�PIN��
                                                012 �ֹ���ʽ���Ҳ���PIN */
 12 centercustomer char(18) , /*43.1 ���Ŀͻ��� */
 13 enterprise char(18) ,     /*43.2 ��ҵ�ͻ��� :�ͻ�����ҵ��Ψһ��ʶ */
 14 acceptdate char(14) ,    /* 44.1 ���Ľ�����������ʱ�� char(CCYYMMDDhhmmss)*/
 15 acceptno char(16) ,      /* 44.2 ���Ľ�������� */
 16 processdate char(14) ,  /* 44.3 ҵ������������ʱ��char(CCYYMMDDhhmmss)*/
 17 serial char(16) ,        /* 44.4 ҵ������ˮ�� */
 18 returncode char(8) ,     /* 44.5 ������ */
 19 ctflag char(1) ,         /* 48.1 �ֽ�/ת�˱�ʶ : 0-�ֽ�,1-ת�� */
 20 resume char(4) ,         /* 48.2 ժҪ���� */
 21 purpose char(3) ,        /* 48.3 �ʽ���;���� */
 22 retry char(1) ,          /* 48.4 �ط���ʶ */
 23 customer char(1) ,       /* 48.5 �Թ�/��˽��ʶ */
 24 bussinesskind char(5) ,  /* 48.6 ҵ������ :0-�Թ���1����˽ */
 25 accounttype char(2) ,    /* 48.7 ��/�۱�ʶ 01������,02���� */
 26 moneytype char(1) ,      /* 48.8 ����/�㻧��ʶ 0-�㻧��1������ */
 27 feemode char(3) ,        /* 48.9 �����ѷ�ʽ �̶���дSHA */
 28 deliver char(3) ,        /* 48.10 ֧������ */
 29 authcode char(6) ,       /* 48.11 ��Ȩ�� */
 30 deliverclass char(1) ,   /* 48.12 ֧�����ȼ� 0����ͨ  */
 31 oldbussid char(32),      /* 56 ԭ����ҵ��Ψһ��ʶ */
 32 sendbankid char(12) ,    /* 62.1 �������к� */
 33 sendopenbank char(12) ,  /* 62.2 �����˿������к� */
 34 sendbanknet char(9) ,    /* 62.3 ����������� */
 35 sendaccount char(35) ,   /* 62.4 �������˺� */
 36 sendername char(60) ,    /* 62.5 ���������� */
 37 referserial char(8) ,    /* 62.6 ƾ֤�ύ�ţ���������ţ� */
 38 recvbank char(12) ,      /* 63.1 �������к� */
 39 recvbankname char(12) ,  /* 63.2 �����˿������к� */
 40 recvnet char(9) ,        /* 63.3 ����������� */
 41 recvaccount char(35) ,   /* 63.4 �������˺� */
 42 recvcustomer char(60) ,  /* 63.5 ���������� */
 43 contractno char(60) ,   /* 66 �ۿ��ͬ�ţ��෽Э��ţ�,���ڶ��ڽ�Ǳ��ġ� */
 44 systemstat char(2) ,     /* 67 ϵͳ����״̬ */
 45 creditmoney char(15) ,   /* 74.1 ������� */
 46 creditcount char(10) ,   /* 74.2 �������� */
 47 debitmoney char(15) ,    /* 74.7 �跽��� */
 48 debitcount char(10) ,    /* 74.8 �跽���� */
 49 transkind char(4) ,      /* 93 �������� */
 50 oldid char(20) ,         /* 102 �ɵ�½��ʶ */
 51 newid char(20) ,         /* 103 �µ�½��ʶ */
 52 resumemsg char(255) ,    /* 111 ����ժҪ(300) */
 53 passcard char(40) ,      /* 112.1 ��Ѻ */
 54 enterpriseid char(12) ,  /* 113.1 ��ҵ�������� */
 55 servicemsgtype char(1) ,  /* 115.1 ������Ϣ���� */
 56 servicemsginfo char(255) ,  /* 115.2 ������Ϣ����(512) */
 57 appendsender char(80) ,  /* 124 ���ӷ��������� */
 58 sendaddr char(60) ,      /* 125 �����˵�ַ */
 59 appendrecver char(80) ,  /* 126 ���ӽ��������� */
 60 recvaddr char(60) ,    /* 127 �����˵�ַ */
