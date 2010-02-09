/*************************************************************************/
/* Name   : libCbs8583.c          	  	                                 */
/* date   : 2006-02-14							                                     */	
/* author : Mr.Wu   	  					                                       */
/*  执行文件名：datapack                                                 */
/*            1.将"数据表bcp文件" 转换成 "8583包文件"                    */
/*            2.将"8583包文件" 转换成 "数据表bcp文件"                    */
/*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "Cbs8583.h"

char packdatainfo[MAX_DATA_NUM][300];
int fieldlength[MAX_DATA_NUM];

int CbsFilChg(char *func, char *srcfile, char *desfile)
{
/***********************************************************************/
   FILE *fp,*fp1;
   char	temp[8192],temp1[1024];
   int	len;
   char	source[128],target[128];
/***********************************************************************/
   char	filename[128];
   char	p8583filename[128];
/***********************************************************************/
   struct basic_header *p_basic;
   struct single_header *p_single;
   struct batch_header *p_batch;
   struct batch_record_header *p_batch_record;
   struct msg_tail *p_msg_tail;
   char	tmp[256+1];
   int	recordlen ;
   int	ii,jj,kk,ll;
   char	bitmap[128+1];
   char	buffer[8192];
   char mode[2];
   int  binary[129];
   char systemserial[32];
   char systemserial1[32];
/***********************************************************************/
/***********************************************************************/
   memset(packdatainfo,0,sizeof(packdatainfo));
   memset(source,0,sizeof(source));
   memset(target,0,sizeof(target));
/****
   if (argc<3 ) {
      printf("usages:\n  datapack mode sourcefile [targetfile]\n\n");
      printf("        mode=1 将'数据表bcp文件' 转换成 '8583包文件'\n");
      printf("             2 将'8583包文件' 转换成 '数据表bcp文件'\n\n");
      return(-1);
   }
   strcpy(mode,argv[1]);
   mode[1]=0;
   if ( (mode[0]!='1') && (mode[0]!='2') ) {
      printf("usages:\n  datapack mode sourcefile [targetfile]\n\n");
      printf("        mode=1 将'数据表bcp文件' 转换成 '8583包文件'\n");
      printf("             2 将'8583包文件' 转换成 '数据表bcp文件'\n\n");
      return(-1);
   }
   strcpy(source,argv[2]);
   if (argc>=4)
      strcpy(target,argv[3]);
   else {
      strcpy(target,source);
      strcat(target,".dat");
   }
   printf("source file =[%s]\n",source);
   printf("target file=[%s]\n\n",target);
*/
	strcpy( mode, func );
	strcpy( source, srcfile );
	strcpy( target, desfile );
Trace( "开始文件处理：参数方式【%s】源文件【%s】目标文件【%s】................",mode, source, target );
/***********************************************************************/
   memset(filename,0,sizeof(filename));
/***********************************************************************/
   memset(p8583filename,0,sizeof(p8583filename));
   sprintf(p8583filename,"%s",source);
   if ( (fp = fopen( p8583filename ,"r")) == NULL ) {
			ErrLog( __FILE__, __LINE__, "Open File【%s】Error!",source );
      return(-1);
   }
   memset(filename,0,sizeof(filename) );
   sprintf(filename,"%s",target);
   if( (fp1 = fopen( filename,"w"))==NULL ) {
			ErrLog( __FILE__, __LINE__, "Create File【%s】Error!",target );
      fclose(fp);
      return(-2);
   }
   recordlen = 0;
   if (mode[0]=='1') goto FILE2PACK;
Trace( "正在进行：8583文件【%s】转换为普通文件【%s】", source, target );
   while (1) {
      memset(temp,0,sizeof(temp));
/*
**	每次获取新数据前清理上次内容
*/
		  memset(packdatainfo,0,sizeof(packdatainfo));

      if( (len=fread(temp,sizeof(char),3,fp)) ==NULL ) {
         ErrLog( __FILE__, __LINE__, "Read File【%s】Error,Len【%d】",source,len );
         fclose(fp); 
         fclose(fp1);
         return(-3);
      }
      fseek(fp,-3,SEEK_CUR);
      if ( memcmp( temp,"{1:",3)==0 ) {  /* basic_header */
         p_basic=(struct basic_header *) temp;
         len=sizeof(struct basic_header) + 1;
         if (fgets( temp,len,fp)==NULL) {
            fclose(fp); 
            fclose(fp1);
            ErrLog( __FILE__, __LINE__, "FGets File【%s】Base_Header Error",source );
            return(-4);
         }

      } else
      if ( memcmp( temp,"{2:",3)==0 ) {  /* single_header */
         p_single=(struct single_header *) temp;
         len=sizeof(struct  single_header ) + 1;
         if (fgets( temp,len,fp)==NULL) {
            fclose(fp); 
            fclose(fp1);
            ErrLog( __FILE__, __LINE__, "FGets File【%s】Single_Header Error",source );
            return(-5);
         }
         
      } else
      if ( memcmp( temp,"{3:",3)==0 ) { /* batch_header */
         len=sizeof(struct batch_header) + 1;
         if (fgets( temp,len,fp)==NULL) {
            fclose(fp); 
            fclose(fp1);
            ErrLog( __FILE__, __LINE__, "FGets File【%s】Batch_Header Error",source );
            return(-6);
         }
         p_batch = (struct batch_header *) temp;
         len=0;
         for(ii=0;ii<MAX_BATCH_HEAD_NUM;ii++) {
            memset(temp1,0,sizeof(temp1));
            ll=batch_headerlen[ii].fieldlength;
            memcpy(temp1,temp+3+len,ll);
            len=len+ll;
            tmp[ll]=0;                        
            delspace(temp1);	 
            if( ( (pack_data_info[ii].fieldbitmap==112)||(pack_data_info[ii].fieldbitmap==66))&& (strlen(temp1)==0) )  /* 112 域作特殊处理，不删除空格 20060411 */
            {
               memcpy(temp1,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",26);
               temp1[26] = 0;
            }
            kk=strlen(temp1);
            if (kk>0)
               fputs(temp1,fp1);
            fputs("|",fp1);
         }
         fputs("\n",fp1);
         continue;
      } else 
      if ( memcmp( temp,"{R:",3)==0 ) { /* batch_record_header */
         len=sizeof(struct batch_record_header) + 1;
         if (fgets( temp,len,fp)==NULL) {
            fclose(fp); 
            fclose(fp1);
            ErrLog( __FILE__, __LINE__, "FGets File【%s】Batch_Record_Header Error",source );
            return(-7);
         }
         p_batch_record = (struct batch_record_header *) temp;
         memset(systemserial,0,sizeof(systemserial));
         memset(systemserial1,0,sizeof(systemserial1));
         memcpy(systemserial,p_batch_record->msgserial,16);
         memcpy(systemserial1,p_batch_record->referserial,16);
         memcpy(temp1,p_batch_record->recordlen,6);
         temp1[6]=0;
         recordlen=atol(temp1);
         continue;
      }  else 
      if (memcmp(temp,"{4:",3)==0 ) {  /* 正文体 text */
         if ( recordlen==0) {
            ErrLog( __FILE__, __LINE__, "File【%s】报文格式错误",source );
            break;
         }
         memset( temp ,0,sizeof(temp));
         recordlen=recordlen-3;
         fseek(fp,3,SEEK_CUR);
         if( fread(temp,sizeof(char),4,fp) == NULL ) {
            fclose(fp);
            fclose(fp1);
            printf("fread error 004 !\n");
            return(-8);
         }
         recordlen=recordlen-4;
         memcpy(packdatainfo[0],systemserial,16); /* 信息序号 */
         memcpy(packdatainfo[1],systemserial1,16); /* 参考信息序号 */
         memcpy(packdatainfo[2],temp,4);  /* 报文类型标识符 */
         memset(temp,0,sizeof(temp));
         if( fread(temp,sizeof(char),16,fp) == NULL ) {
            fclose(fp);
            fclose(fp1);
            ErrLog( __FILE__, __LINE__, "File【%s】信息序号错误",source );
            return(-9);
         }
         recordlen=recordlen-16;
         memcpy(tmp,temp,16);
         memset(bitmap,0,sizeof(bitmap));
         unp8583bitmap(tmp,bitmap);
         for ( ii=3;ii<128; ii++) {
            if( bitmap[ii-1]=='0' ) continue;
            memset(temp,0,sizeof(temp));
            for(jj=0;jj<MAX_DATA_NUM;jj++)
               if( pack_data_info[jj].fieldbitmap==ii) break;
            if( jj>127 ) {
               continue;
            }
            for (ll=0;ll<(MAX_DATA_NUM-jj);ll++ ) {
               if(pack_data_info[jj+ll].fieldbitmap!=ii) break;
               kk=pack_data_info[jj+ll].headlength;
               if ( kk>0 ) {
                  memset(temp,0,sizeof(temp));
                  if( fread(temp,sizeof(char),kk,fp)==NULL ) break;
                  recordlen=atoi(temp);
               }
               kk=pack_data_info[jj+ll].fieldlength;
               if ( (recordlen-kk)<0) {
                  kk=recordlen;
               }
               memset(temp,0,sizeof(temp));
               if( fread(temp,sizeof(char),kk,fp)==NULL ) break;
               recordlen=recordlen-kk;
               memcpy(packdatainfo[jj+ll],temp,kk);
               if( pack_data_info[jj].fieldbitidx ==0 ) break;
            }
         }
         kk = convertpackinfo(temp);
         fwrite(temp,sizeof(char),kk,fp1);      
         fputs("\n",fp1);
         fread(temp,sizeof(char),1,fp);  /*结束符 end symbol */
      } else 
      if ( memcmp( temp,"{5:",3)==0 ) { /* msg_tail  */
         len=sizeof(struct msg_tail) + 1;
         if (fgets( temp,len,fp)==NULL) {
            fclose(fp); 
            fclose(fp1);
            ErrLog( __FILE__, __LINE__, "File【%s】Msg_Tail Error",source );
            return(-10);
         }
         p_msg_tail = (struct msg_tail *) temp;
         break;
      } else {
         ErrLog( __FILE__, __LINE__, "File【%s】格式错误",source );
         fclose(fp);fclose(fp1);
         return(-11);
      }
   }
   fclose(fp);
   fclose(fp1);
   return(0);
FILE2PACK:
Trace( "正在进行：普通文件【%s】转换为8583文件【%s】", source, target );
   recordlen=0;
   if( fgets(buffer,8192,fp)==NULL) {
      ErrLog( __FILE__, __LINE__, "读文件【%s】错误", source );
      fclose(fp1);
      return(-12);
   }
   fputs("{3:",fp1);  /*填写批量应用报文头*/ 
   kk = 0;
   jj = 0;
   while(2) {
      len = 0;
      memset(temp,0,sizeof(temp));
      for(ii=jj;ii<8192;ii++) {
         if(buffer[ii]=='|') break;
         temp[len++] = buffer[ii];
      }
      jj=ii+1;
      memset(temp1,' ',sizeof(temp1));
      ll = strlen(temp);
      memcpy(temp1,temp,ll);
      fwrite(temp1,sizeof(char),batch_headerlen[kk].fieldlength,fp1);
      if(++kk>=MAX_BATCH_HEAD_NUM) break;
   }
   fputs("}",fp1);
   for (ii=0;ii<=8;ii++) binary[ii] = 1;
   for (ii=0;ii<=7;ii++)
     for (jj=7;jj>ii;jj--) binary[ii] = binary[ii]*2 ; /*128 64 32 16 8 4 2 1 */
   for(ii=0;ii<MAX_DATA_NUM;ii++) fieldlength[ii]=0;
   while(3) {   /*读文件一行记录*/
   	memset(packdatainfo,' ',sizeof(packdatainfo));
      if( fgets(buffer,8192,fp)==NULL) break;  /*默认一行记录不超过8192位 */
      kk = 0;
      jj = 0;
      while(4) {
         len = 0;
         memset(temp,0,sizeof(temp));
         for(ii=jj;ii<8192;ii++) {
            if(buffer[ii]=='|') break;
            temp[len++] = buffer[ii];
         }
         jj = ii+1;
Trace( "正在处理数据文件第【%d】项，值【%s】",kk,temp );
         if((pack_data_info[kk].fieldbitmap!=112)&&(pack_data_info[kk].fieldbitmap!=66))  /* 112 域作特殊处理，不删除空格 20060411 */
             delspace(temp);
         if (strlen(temp)==0 ) len = 0;     /*如果数据域为空（空格），则不取*/         
         fieldlength[kk] = len;
         if ( len > 0 )
             memcpy(packdatainfo[kk],temp,len);
/*         memset(&packdatainfo[kk][len],' ',300-len); 20060412将后面字符清空 */
         len=pack_data_info[kk].fieldlength;
         for(ll=0;ll<len;ll++)  /*去除非标准字符*/
            if( (packdatainfo[kk][ll] == 0 ) ||
                (packdatainfo[kk][ll] == '\n') ) packdatainfo[kk][ll] = ' ';
         if(++kk >= MAX_DATA_NUM) break;
      }
      kk = 0;
      memset(temp,0,sizeof(temp));
      recordlen = 0;
      for(ii=3;ii<MAX_DATA_NUM;ii++) {                /*组 正文体内容*/
      /* 第一、二位为"信息序号(16)",第三位为"报文类型标识符(4)",从第四位开始组包 */
          ll=fieldlength[ii];
          if(ll==0) continue;   /*如果数据域为空，则不要*/
          ll=pack_data_info[ii].fieldlength;
          len = pack_data_info[ii].headlength ;
          if( len > 0 ) {
             if( pack_data_info[ii].fieldbitidx > 0 ) {
                for(jj=(ii+1);jj<MAX_DATA_NUM;jj++) {
                   if( pack_data_info[jj].fieldbitmap !=
                       pack_data_info[ii].fieldbitmap ) break;
                       ll = ll + pack_data_info[jj].fieldlength; 
                }
             } else 
                if ( fieldlength[ii] > 0) ll=fieldlength[ii];
             memset(temp1,0,sizeof(temp1));
             if ( len == 1 ) sprintf(temp1,"%d",ll);
             if ( len == 2 ) sprintf(temp1,"%02d", ll);
             if ( len == 3 ) sprintf(temp1,"%03d", ll);
             if ( len == 4 ) sprintf(temp1,"%04d", ll);
             memcpy(temp+recordlen,temp1,len);
             recordlen=recordlen+len;
             if( pack_data_info[ii].fieldbitidx > 0 ) {
                for( jj =ii;jj<MAX_DATA_NUM;jj++) {
                   if( pack_data_info[jj].fieldbitmap !=
                       pack_data_info[ii].fieldbitmap ) break;
                   ll = pack_data_info[jj].fieldlength;
                   memcpy(temp+recordlen,packdatainfo[jj],ll);
                   recordlen = recordlen+ll;
Trace( "正在处理8583结构体【%d】域-第【%d】项-值【%s】",pack_data_info[jj].fieldbitmap,pack_data_info[jj].fieldbitidx,temp+recordlen-ll );
                }
                ii=jj-1; continue;
             } 
          }
          memcpy(temp+recordlen,packdatainfo[ii],ll);
          recordlen = recordlen+ll;
Trace( "正在处理8583结构体【%d】域-值【%s】",pack_data_info[ii].fieldbitmap,temp+recordlen-ll );
      }
      memcpy(systemserial,packdatainfo[0],16);
      memcpy(systemserial1,packdatainfo[1],16);
      fputs("{R:",fp1);  /*填写 批量记录应用报文头*/
      fwrite(systemserial,sizeof(char),16,fp1); /*信息序号*/
      memset(temp1,' ',sizeof(temp1));
      fwrite(systemserial1,sizeof(char),16,fp1); /*参照信息序号*/
      memset(temp1,0,sizeof(temp1));
      len = recordlen + 24;  
      sprintf(temp1,"%06d",len); 
      fwrite(temp1,sizeof(char),6,fp1);  /*记录体长度*/
      memset(temp1,' ',sizeof(temp1));
      memcpy(temp1,"RESERVE000000000",16);
      fwrite(temp1,sizeof(char),16,fp1); /*预留位*/
      fputs("}",fp1);
      fputs("{4:",fp1);  /*填写 报文体*/
      memset(bitmap,'0',sizeof(bitmap));
      for(ii=1;ii<MAX_DATA_NUM;ii++) {
         if( fieldlength[ii] > 0 ) {
            jj = pack_data_info[ii].fieldbitmap -1 ;
            bitmap[jj] = '1'; 
         }
      }
      bitmap[0] = '1';
      memset(tmp,0,sizeof(tmp));
      len =0;
      for(ii=0;ii<16;ii++) {
         kk = 0;
         for(ll = 0; ll<8; ll++ ) {
            jj = 0;
            if (bitmap[len+ll] == '1' ) jj = 1;
            kk = kk + jj * binary[ll];
         }
         len = len +8;
         tmp[ii] = kk;  /*生成"位元" */
      }
/*****可能吴SIR有误
      fwrite(packdatainfo[1],sizeof(char),4,fp1);
*****/
      fwrite(packdatainfo[2],sizeof(char),4,fp1); /*报文类型标识符*/
      fwrite(tmp,sizeof(char),16,fp1);   /*位元图*/
      fwrite(temp,sizeof(char),recordlen,fp1);  /*正文体*/
      fputs("}",fp1);
      recordlen++;
   }
   fputs("{5:",fp1); /*报文尾*/
   for(ii=0;ii<64;ii++) tmp[ii]=0x43;
   fwrite(tmp,sizeof(char),64,fp1); /*校验码*/
   fputs("}",fp1);
   fclose(fp);
   fclose(fp1);
Trace( "文件处理结束................................\n\n\n\n\n" );
   return(0);
}

int delspace( char *buff)
{
  char tmp1[1024];
  int i,j,k;
  memset(tmp1,0,sizeof(tmp1));
  i=strlen(buff); 
  k=0;
  for(j=0;j<i;j++) 
    if( buff[j]!=' ' ) tmp1[k++]=buff[j];
  k=strlen(tmp1);
  strcpy(buff,tmp1);
  return 0;
}
int unp8583bitmap(char *map, char *bit )
{
  int i,j,k,len,value;
  char tmp[128+1],tmp1[128+1];
  int  binary[128+1];
  for (i=0;i<=8;i++) binary[i] = 1;
  for (i=1;i<=8;i++) 
    for (j=2;j<=i;j++) binary[i] = binary[i]*2 ;
  for (i=8;i>0;i--) {
    len = 0;
    for (j=1;j<i;j++) len = len+binary[j];
    binary[i] = binary[i] + len + 1;
  }

  memset(tmp1,0,sizeof(tmp1));
  memcpy(tmp,map,16);
  for(i=0;i<16;i++) {
    value = tmp[i];
    if(value<0 ) value = 256+value;
    len = 8 * i ;
    for (j=0;j<=7;j++) {
        if (value >= binary[7-j]) {
          tmp1[len+j]='1';
          value = value - binary[7-j];
        } else 
        tmp1[len+j]='0';
    }
  }
  memcpy(bit,tmp1,128);
}

int convertpackinfo(char *buff)
{
  int i,j,k,l,len;
  char buffer[1024],tmp[8192];
  memset(tmp,0,sizeof(tmp));
  len=0;
  for(i=0;i<MAX_DATA_NUM;i++)
  {
     memset(buffer,0,sizeof(buffer));
     k=pack_data_info[i].fieldlength;
     j=pack_data_info[i].fieldbitmap;
     l=pack_data_info[i].fieldbitidx;
     if (k>0)
     memcpy(buffer,packdatainfo[i],pack_data_info[i].fieldlength);
     delspace(buffer);
     j=strlen(buffer);
     if (j>0) {
        memcpy(tmp+len,buffer,j); 
        len=len+j;
     } 
     strcpy(tmp + len++,"|");
  }
  strcpy(buff,tmp);
  return len;
}
