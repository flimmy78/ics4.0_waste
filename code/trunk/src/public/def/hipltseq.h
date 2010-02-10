#ifndef _HIPLTSEQ_H_
#define _HIPLTSEQ_H_
#include <regex.h>
#include "hipubatl.h"

#define PLT_SEQ_NO_ONLINE_MODE  'O'
#define PLT_SEQ_NO_BATCH_MODE   'B'

struct __pltseqno
{
    char            SEQ_NAME[64+1]    ;       /*顺序号名称(主KEY)                  */  
    char            SEQ_LENGTH[15+1]    ;     /*序号长度*/                                                       
    char            SEQ_CUR_SEQ_NO[15+1];     /*当前使用顺序号                     */                                                           
    char            SEQ_OLD_SEQ_NO[15+1];     /*上一周期顺序号                     */                                                           
    char            SEQ_FIRST_NUM[15+1] ;     /*初始顺序号                         */
    char            SEQ_MAX_SEQ_NO[15+1];     /*最大顺序号                         */
    char            SEQ_FILTER[128+1] ;       /*筛选器                             */                                                 
    char            SEQ_INIT_ZERO[1+1];       /*归零周期，取值范围为               */
                                              /*D–日末清零，W–周末清零，M–月末清零 */
                                              /*Q-季末清零, Y–年末清零，N–不清零   */
    char            SEQ_SKIP_FLG[1+1] ;       /*特性标志(Y_允许跳号,N_不允许跳号,  */
                                              /*S_允许跳号且高效率)                */                          
    char            SEQ_OBL_FLG[1+1]  ;       /*是否允许预留(Y_允许,N_不允许)      */                                                           
    char            SEQ_VIP_FLG[1+1]  ;       /*是否允许选号(Y_允许,N_不允许)      */                                                           
    char            SEQ_VAL_DATE[8+1]      ;  /*生效日期                           */                                                                                      
    char            SEQ_MAX_FLAG[1+1] ;       /*达到最大顺序号后处理标志(E_ERROR,  */
                                              /*SPACE_重新从起始号开始)            */                          
    char            SEQ_WARN_SEQ_NO[15+1]   ; /*预警顺序号                         */
};
typedef struct  __pltseqno PLTSEQNO;

struct __pltoblseq
{
    char            SEQ_NAME[64+1]           ;  /*顺序号名称                */
    char            OBLIGATE_NAME[64+1]      ;  /*预留顺序号名称            */
    char            OBLIGATE_MIN_SEQ_NO[15+1];  /*预留起始顺序号            */
    char            OBLIGATE_MAX_SEQ_NO[15+1];  /*预留最大顺序号            */
    char			OBLIGATE_SEQ_LENGTH[15+1];  /*顺序号长度                */
    char            OBLIGATE_SEQ_NO[15+1]    ;  /*正在使用的顺序号          */
    char            OBLIGATE_VAL_DATE[8+1]   ;  /*生效日期                  */
    char            OBLIGATE_INIT_ZERO[1+1];    /*归零周期,取值范围为D–日末清零*/
                                                /*W–周末清零，M–月末清零，  */    
                                                /*Q_季末清零, Y–年末清零，  */    
                                                /*N–不清零                  */    

};
typedef struct __pltoblseq PLTOBLSEQ;   
    

struct __pltselseq
{
    char            OBLIGATE_NAME[64+1]     ;       /*顺序号名称     */
    char            OBLIGATE_SEQ_NO[15+1]   ;       /*被选择的顺序号 */
    char            OBLIGATE_VAL_DATE[15+1] ;       /*生效日期       */
};
typedef struct __pltselseq PLTSELSEQ;  

#endif
