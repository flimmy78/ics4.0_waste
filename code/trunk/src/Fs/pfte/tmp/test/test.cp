main()
{
	char sOrgMsg[52]="SES20161         2009032561                12345678";
	char sMasterKey[9]="12345678";
	char sDestBody[1025];
  int iBool,iOrgLen=51, iDestLen, _IsEnc=1;	

	memset( sDestBody, 0x00, sizeof(sDestBody));
  iBool=rtss_code_proc_snd(sDestBody,&iDestLen,sOrgMsg,iOrgLen,_IsEnc,sMasterKey);
  if (iBool ==0)
  {
    prinft("Err_DoSignOn_1[%s]",sOrgMsg);
    return (0);
  }
  printf("sDestBody=[%s]",sDestBody);
}
