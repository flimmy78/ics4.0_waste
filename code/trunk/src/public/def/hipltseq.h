#ifndef _HIPLTSEQ_H_
#define _HIPLTSEQ_H_
#include <regex.h>
#include "hipubatl.h"

#define PLT_SEQ_NO_ONLINE_MODE  'O'
#define PLT_SEQ_NO_BATCH_MODE   'B'

struct __pltseqno
{
    char            SEQ_NAME[64+1]    ;       /*˳�������(��KEY)                  */  
    char            SEQ_LENGTH[15+1]    ;     /*��ų���*/                                                       
    char            SEQ_CUR_SEQ_NO[15+1];     /*��ǰʹ��˳���                     */                                                           
    char            SEQ_OLD_SEQ_NO[15+1];     /*��һ����˳���                     */                                                           
    char            SEQ_FIRST_NUM[15+1] ;     /*��ʼ˳���                         */
    char            SEQ_MAX_SEQ_NO[15+1];     /*���˳���                         */
    char            SEQ_FILTER[128+1] ;       /*ɸѡ��                             */                                                 
    char            SEQ_INIT_ZERO[1+1];       /*�������ڣ�ȡֵ��ΧΪ               */
                                              /*D�C��ĩ���㣬W�C��ĩ���㣬M�C��ĩ���� */
                                              /*Q-��ĩ����, Y�C��ĩ���㣬N�C������   */
    char            SEQ_SKIP_FLG[1+1] ;       /*���Ա�־(Y_��������,N_����������,  */
                                              /*S_���������Ҹ�Ч��)                */                          
    char            SEQ_OBL_FLG[1+1]  ;       /*�Ƿ�����Ԥ��(Y_����,N_������)      */                                                           
    char            SEQ_VIP_FLG[1+1]  ;       /*�Ƿ�����ѡ��(Y_����,N_������)      */                                                           
    char            SEQ_VAL_DATE[8+1]      ;  /*��Ч����                           */                                                                                      
    char            SEQ_MAX_FLAG[1+1] ;       /*�ﵽ���˳��ź����־(E_ERROR,  */
                                              /*SPACE_���´���ʼ�ſ�ʼ)            */                          
    char            SEQ_WARN_SEQ_NO[15+1]   ; /*Ԥ��˳���                         */
};
typedef struct  __pltseqno PLTSEQNO;

struct __pltoblseq
{
    char            SEQ_NAME[64+1]           ;  /*˳�������                */
    char            OBLIGATE_NAME[64+1]      ;  /*Ԥ��˳�������            */
    char            OBLIGATE_MIN_SEQ_NO[15+1];  /*Ԥ����ʼ˳���            */
    char            OBLIGATE_MAX_SEQ_NO[15+1];  /*Ԥ�����˳���            */
    char			OBLIGATE_SEQ_LENGTH[15+1];  /*˳��ų���                */
    char            OBLIGATE_SEQ_NO[15+1]    ;  /*����ʹ�õ�˳���          */
    char            OBLIGATE_VAL_DATE[8+1]   ;  /*��Ч����                  */
    char            OBLIGATE_INIT_ZERO[1+1];    /*��������,ȡֵ��ΧΪD�C��ĩ����*/
                                                /*W�C��ĩ���㣬M�C��ĩ���㣬  */    
                                                /*Q_��ĩ����, Y�C��ĩ���㣬  */    
                                                /*N�C������                  */    

};
typedef struct __pltoblseq PLTOBLSEQ;   
    

struct __pltselseq
{
    char            OBLIGATE_NAME[64+1]     ;       /*˳�������     */
    char            OBLIGATE_SEQ_NO[15+1]   ;       /*��ѡ���˳��� */
    char            OBLIGATE_VAL_DATE[15+1] ;       /*��Ч����       */
};
typedef struct __pltselseq PLTSELSEQ;  

#endif
