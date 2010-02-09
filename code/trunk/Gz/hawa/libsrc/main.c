#include	<stdio.h>

void	main(argc, argv)
int	argc;
char	**argv;
{
	unsigned char		tmp[128];
	char	tmp1[128];

	memset(tmp,0,sizeof(tmp));
	memset(tmp1,0,sizeof(tmp1));
	if(argc>1)
          strcpy(tmp1,argv[1]);
        else
          strcpy(tmp1,"123456789012345678");

	MD5X(tmp1,tmp);
	printf("\ntmp=[%s]\n",tmp);
}
