#include	<stdio.h>



void	main(argc, argv)
int	argc;
char	**argv;
{
	unsigned char		tmp[128];
	char	tmp1[128];
  int i,len;

	memset(tmp,0,sizeof(tmp));
	memset(tmp1,'\0',sizeof(tmp1));
	if(argc>1)
          strcpy(tmp1,argv[1]);
        else
          strcpy(tmp1,"44011219222222");

  len = strlen(tmp1)%8;

  switch(len)
  {
    case 0: len = strlen(tmp1); break;
    case 1: len = strlen(tmp1) + 7;break;
    case 2: len = strlen(tmp1) + 6;break;
    case 3: len = strlen(tmp1) + 5;break;
    case 4: len = strlen(tmp1) + 4;break;
    case 5: len = strlen(tmp1) + 3;break;
    case 6: len = strlen(tmp1) + 2;break;
    case 7: len = strlen(tmp1) + 1;break;
  }


  /*
  while(len!=0)
  {
	  strcat(tmp1,"0");
	  len = strlen(tmp1)%8;
  }
  len = strlen(tmp1);
  */

 	TriDes("1122334455667788",tmp1,len);
  for (i=0;i<len;i++)
   printf("\ntmp[%d]=[%x]\n",i,tmp1[i]);

 	TriUNDes("1122334455667788",tmp1,len);
  for (i=0;i<len;i++)
   printf("\ntmp[%d]=[%x]\n",i,tmp1[i]);
}
