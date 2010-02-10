#include    "hiafp.h"
#include    <stdlib.h>
#define		DP_FAIL  		-1
#define		DP_SUCC  		0
#define		PATH_LEN 		1024
#define		FILENAME_LEN 	512
#define		PASSWDLEN  		512

/* “‘œ¬Œ™÷–…Ω…Á±£≤Œ ˝ */
#define     LOG_SSA        "SSA.log"
#define     KEY_FILE       "/app/ics/etc/ZS_SSA_484999.KEY"     /* MAC_KEYŒƒº˛ */
#define     MMKEY_SSA      "jypt4321"
#define     CHK_MAC        1                    /* Ω” ’œÏ”¶∞¸ ± «∑Ò–£—ÈMAC£∫ 0≤ª–£—È 1–£—È */

/* “‘œ¬Œ™÷–…Ω“∆∂Ø≤Œ ˝ */
#define     LOG_OPF        "OPF.log"
#define     MMKEY_OPF      "12345678"           /* ÷˜√‹‘ø */
#define     RNDKEY_OPF     "12345678"           /* ∑÷…¢√‹‘ø */
#define     OPF_RPCHK      1                    /* Ω” ’œÏ”¶∞¸ ± «∑Ò–£—ÈMAC£∫ 0≤ª–£—È 1–£—È */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void GenMac(unsigned char *in_data,int in_len,unsigned char *mmKey,
     unsigned char *MAC_Key,unsigned char *mac);
void Cal_MACDATA(unsigned char * in_data, int in_len, unsigned char *MAC_DATA);
void dec_masterKey(unsigned char des_key[8], unsigned char *in, unsigned char *out);
void des_encode(unsigned char des_key[8], unsigned char *in, unsigned char *out);
void des_decode(unsigned char des_key[8], unsigned char *in, unsigned char *out);
     

/******************************************************************
* Function : pre_opf
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ÷–…Ω…Á±£±®ŒƒΩ‚Œˆ‘§¥¶¿Ì∫Ø ˝æ›
* Others   : ÷–…Ω…Á±£±®Œƒ∏Ò Ω∫‹Ãÿ ‚£∫
        1.±®Œƒ√ª”–«∞÷√≥§∂»£ª
        2.≤…”√XML±®Œƒ◊È÷ØΩª“◊ ˝æ›
        3.‘⁄XML±®Œƒ÷Æ∫Û∑≈÷√32ŒªMAC–£—È ˝æ›
        4.Ωª“◊¬ÎŒ™0001,¥´µ›√‹‘øΩª“◊ ±£¨√ª”–MAC–£—È ˝æ›
        5.±®Œƒµƒ∏Ò ΩŒ™£∫Ωª“◊ ˝æ›£´MAC¥Æ£´\r\n
*******************************************************************/
int pre_ssa( CurrInf * curr_inf,  char * in_data, int in_len, char ** out_data, int * out_len)
{
   char	* tmp = NULL;
   char  in_mac[33];     /* Õ®—∂ ‰»Îµƒ–£—È ˝æ› */
   unsigned char  cal_mac[33];    /* ∏˘æ›µ±«∞ ˝æ›º∆À„≥ˆ¿¥µƒMAC */
   unsigned char  mmKey[1024],MAC_Key[1024]; /* ¥”Œƒº˛÷–ªÒ»° */
   unsigned char  *op_DATA;       /* ¥˝º∆À„MACµƒ ˝æ›÷∏’Î */
   int   ret;

   herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]’˝‘⁄Ω¯––‘§¥¶¿Ì>>>>----",curr_inf->req_id);
   herrlog(LOG_SSA, " ’µΩ±®Œƒ:[%d][%s]", in_len, in_data);
   herrlog(LOG_SSA, "Step 1: ≈–∂œ «∑Ò’˝≥£±®Œƒ");
   if(in_data[in_len-1]!=0x0A||in_data[in_len-2]!=0x0D) {
      /* ∑«÷–…Ω…Á±£±®Œƒ∏Ò Ω */
      herrlog(LOG_SSA,"∑«’˝≥£±®Œƒ[%s],±®ŒƒΩ· ¯[%02x%02x]∑«ªÿ≥µªª––±Í÷æ!\n",in_data,in_data[in_len-2],in_data[in_len-1]);
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return(DP_FAIL);
   }
      
   *out_data = (char *)malloc(in_len+1);
   if(*out_data == NULL){
      herrlog(LOG_SSA, "∑÷≈‰ƒ⁄¥Ê ß∞‹");
      return(DP_FAIL);
   }
   memset( *out_data, 0x00, in_len+1);
   
   herrlog(LOG_SSA, "Step 2: ≈–∂œ «∑Ò”–MAC");
   if(0==strncmp(in_data+in_len-5-2,"</AP>",5)) {
      /* ∏√Ωª“◊Œﬁ–£—È¬Î,»œŒ™ «√‹‘ø¥´ ‰Ωª“◊£¨∞¥’˝»∑∑µªÿ */
      *out_len  = in_len-2;
      memcpy(*out_data,in_data, *out_len);
      herrlog(LOG_SSA, "ŒﬁMAC, ‰≥ˆ±®Œƒ[%d][%s]",*out_len, *out_data);
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return(DP_SUCC);
   }
   else {
      /* ”––£—È¬Î */
      memset(in_mac, 0x00, 33);
      *out_len = in_len-2-32;
      memcpy(*out_data, in_data, *out_len);
      memcpy(in_mac, in_data+(*out_len),32);
      herrlog(LOG_SSA,"”–MAC[%s]",in_mac);
   }
   
   herrlog(LOG_SSA, "Step 3: »∑∂® «∑Ò–£—ÈMAC");
   if(curr_inf->rq_or_rp==2) {
      /* ±®Œƒ «µ⁄»˝∑Ω∑µªÿœÏ”¶∞¸ ± */
      if(!CHK_MAC) {
         /* ≤ª–£—ÈMAC */
         herrlog(LOG_SSA, "  Ωª“◊œÏ”¶∞¸£¨«“≤ª“™«Û–£—È£¨’˝≥£∑µªÿ!!! ");
         herrlog(LOG_SSA," ‰≥ˆ±®Œƒ[%d][%s]",*out_len, *out_data);
         herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
         return(DP_SUCC);
      }
   }   
   
   herrlog(LOG_SSA, "Step 4: –£—ÈMAC");
   memset(mmKey, 0x00, 1024);
   memset(MAC_Key, 0x00, 1024);
   ret=Read_Key(mmKey,MAC_Key);
   if(ret!=0){
      hfree((void **)out_data);
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return(DP_FAIL);
   }
   memset(cal_mac, 0x00, 33);
   
   op_DATA=(unsigned char*)(*out_data);
   GenMac(op_DATA,*out_len,mmKey,MAC_Key,cal_mac);
   if(0!=strncmp(in_mac, (char *)cal_mac, 32)) {
      herrlog(LOG_SSA, "MAC–£—È¥Ì: in [%s]!=cal [%s]", in_mac, cal_mac);
      hfree((void **)out_data);
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return(DP_FAIL);
   }
   herrlog(LOG_SSA, "MAC–£—È’˝»∑£¨ ‰≥ˆ±®Œƒ[%d][%s]",*out_len, *out_data);
   herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}

/******************************************************************
* Function : spe_opf
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ÷–…Ω…Á±£±®ŒƒΩ‚ŒˆÃÿ ‚¥¶¿Ì∫Ø ˝æ›
* Others   : ÷–…Ω…Á±£±®Œƒ∏Ò Ω∫‹Ãÿ ‚£∫
        1.±®Œƒ√ª”–«∞÷√≥§∂»£ª
        2.≤…”√XML±®Œƒ◊È÷ØΩª“◊ ˝æ›
        3.‘⁄XML±®Œƒ÷Æ∫Û∑≈÷√32ŒªMAC–£—È ˝æ›
        4.Ωª“◊¬ÎŒ™0001,¥´µ›√‹‘øΩª“◊ ±£¨√ª”–MAC–£—È ˝æ›
    Ãÿ ‚¥¶¿ÌµƒƒøµƒæÕ «‘⁄Õ®—∂±®Œƒµƒ◊Ó∫Ûº”…œMAC–£—È¬Î
*******************************************************************/
int spe_ssa(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{
   XmlNode	* tmpNode = NULL;
   char * txncod = NULL;
   unsigned char  cal_mac[33];    /* ∏˘æ›µ±«∞ ˝æ›º∆À„≥ˆ¿¥µƒMAC */
   unsigned char  mmKey[1024],MAC_Key[1024]; /* ¥”Œƒº˛÷–ªÒ»° */
   unsigned char  *op_DATA;       /* ¥˝º∆À„MACµƒ ˝æ›÷∏’Î */
   int   ret;

   herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]’˝‘⁄Ω¯––±®ŒƒÃÿ ‚¥¶¿Ì>>>>----",curr_inf->req_id);
   herrlog(LOG_SSA," ’µΩ¥˝¥¶¿Ì±®Œƒ[%s]",in_data);
   herrlog(LOG_SSA, "spe:Step 1: »°Ωª“◊¬Î");
   tmpNode = xmlStringToTree(in_data, in_len);
   if ( tmpNode == NULL ){
      herrlog(LOG_SSA, "spe: ˜ªØxml±®Œƒ[%s] ß∞‹", in_data);
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]±®ŒƒÃÿ ‚¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return DP_FAIL;
   }
   txncod = xmlGetValue(xmlGetNode(tmpNode, NULL, "Trans_Code"));
   if ( txncod == NULL ){
      herrlog(LOG_SSA, "spe:»°Ωª“◊¬Î ß∞‹");
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]±®ŒƒÃÿ ‚¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return DP_FAIL;
   }
   herrlog(LOG_SSA, "spe:Step 2: ≈–Ωª“◊¬Î «∑Ò0001[%s]",txncod);
   if(0==strncmp(txncod, "0001", 4)) {
      /* ¥´ ‰√‹‘øΩª“◊£¨≤ª“™MAC¥Æ */
      *out_data = (char *)malloc(in_len+1);
      if(*out_data == NULL){
         herrlog(LOG_OPF, "∑÷≈‰ƒ⁄¥Ê ß∞‹");
         return(DP_FAIL);
      }
      *out_len = in_len;
      memset(*out_data, 0x00, (*out_len)+1);
      memcpy(*out_data, in_data, in_len);   
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]±®ŒƒÃÿ ‚¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return(DP_SUCC);
   }
   
   /* º∆À„MAC£¨≤¢º”µΩ ‰≥ˆ ˝æ›µƒ◊Ó∫Û */
   herrlog(LOG_SSA, "spe:Step 3: º∆À„Ωª“◊MAC");
	*out_data = (char *)malloc(in_len+32+1);
   if(*out_data == NULL){
      herrlog(LOG_OPF, "∑÷≈‰ƒ⁄¥Ê ß∞‹");
      return(DP_FAIL);
   }
	*out_len = in_len+32;
	memset(*out_data, 0x00, (*out_len)+1);
   memcpy(*out_data, in_data, in_len);   /* œ»∞— ‰»Î ˝æ›◊™¥¢µΩ ‰≥ˆ ˝æ› */

   memset(cal_mac, 0x00, 33);
   
   memset(mmKey, 0x00, 1024);
   memset(MAC_Key, 0x00, 1024);
   /*
   herrlog(LOG_SSA, "spe_opf:∂¡√‹‘øŒƒº˛MAC: [%s]", KEY_FILE);
   */
   ret=Read_Key(mmKey,MAC_Key);
   if(ret!=0){
      hfree((void **)out_data);
      herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]±®ŒƒÃÿ ‚¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      return(DP_FAIL);
   }
   memset(cal_mac, 0x00, 33);
   op_DATA=(unsigned char *)in_data;
   GenMac(op_DATA,in_len,mmKey,MAC_Key,cal_mac);   
   herrlog(LOG_SSA, "spe:∑¢≥ˆ±®ŒƒMAC: [%s]", cal_mac);
      
   memcpy(*out_data+in_len, cal_mac, 32);
   *(*out_data+*out_len) = 0x0D;
   *(*out_data+*out_len+1) = 0x0A;
   *(*out_data+*out_len+2) = '\0';
   *out_len+=2;
   herrlog(LOG_SSA, "spe:Step 3:  ‰≥ˆ±®Œƒ[%s]",*out_data);
   herrlog(LOG_SSA, "---->>>>Ωª“◊[%s]±®ŒƒÃÿ ‚¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}

/***************************************************
 * “‘œ¬Œ™÷–…Ω…Á±£MACº∆À„…Êº∞µƒ“ª–©∫Ø ˝
 ***************************************************/
 
/**************************************************************
 * ∂¡»°±£¥Ê‘⁄Œƒº˛÷–µƒKEY
 * Œƒº˛∏Ò Ω£∫  mmKey MAC_Key
 *      “‘ø’∏Ò∑÷ø™£¨mmKey≥§∂»Œ™◊Ó¥Û8∏ˆ◊÷∑˚£¨MAC_Key◊Ó¥Û16◊÷∑˚
 **************************************************************/
int Read_Key(unsigned char *mmKey, unsigned char *MAC_Key)
{
   
   FILE *f_key;
   int   ret;
   
   memset(mmKey, 0x00, 9);
   memset(MAC_Key, 0x00, 17);
   herrlog(LOG_SSA, "Read_KEY:¥Úø™MAC_KEYŒƒº˛[%s]",KEY_FILE);
   if((f_key=fopen(KEY_FILE,"r"))==NULL){
      herrlog(LOG_SSA, "¥Úø™MAC_KEYŒƒº˛[%s]¥Ì£°",KEY_FILE);
      return(DP_FAIL);
   }
   ret=fscanf(f_key,"%s",MAC_Key);
   fclose(f_key);   
   if(1!=ret){
      herrlog(LOG_SSA, "∂¡»°MAC_KEYŒƒº˛[%s]¥Ì£°",KEY_FILE);
      return(DP_FAIL);
   }
   
   strcpy((char *)mmKey,MMKEY_SSA);      /* mmKeyŒ™±æŒƒº˛µƒ∫Í∂®“Â */
   mmKey[8]=0x00;             /* ≥¨≥§≤ø∑÷…·∆˙ */
   MAC_Key[16]=0x00;          /* ≥¨≥§≤ø∑÷…·∆˙ */
   
   return(0);
}

/**************************************************************
 * ÷–…Ω…Á±££¨Õ®—∂MAC…˙≥…
 * À„∑®∑÷»˝≤Ω£∫ 
 * 1. À„≥ˆ8◊÷Ω⁄µƒMACDATA∫Û£¨µ˜”√±Í◊ºdesÀ„∑®º”√‹£¨◊™ªªŒ™16Ω¯÷∆◊÷∑˚¥ÆStr1(16∏ˆ◊÷∑˚)
 * 2. ∂‘8∏ˆchr(8)µƒ8◊÷Ω⁄µ˜”√±Í◊ºdesÀ„∑®º”√‹£¨◊™ªªŒ™16Ω¯÷∆◊÷∑˚¥ÆStr2(16∏ˆ◊÷∑˚)
 * 3. Str1+Str2µ√µΩ32∏ˆ◊÷∑˚◊˜Œ™MAC¥´ ‰
 * ≤Œ ˝£∫ in_data       ¥˝¥¶¿Ìµƒ◊÷∑˚¥Æ
 *        in_len        ¥˝¥¶¿Ì◊÷∑˚¥Æ≥§∂»
 *        mmKey         DES÷˜√‹‘ø
 *        MAC_Key       ”√”⁄º∆À„∑÷…¢√‹‘øµƒMAC_Key
 *        mac           º∆À„Ω·π˚
 **************************************************************/
void GenMac(unsigned char *in_data,int in_len,unsigned char *mmKey,
     unsigned char *MAC_Key,unsigned char *mac)
{
   unsigned char masterKey[33];
   unsigned char MAC_DATA[9];
   unsigned char mac_add[33];
   int i;
   

   /* º∆À„masterKey */
   memset(masterKey, 0x00, 33);
   dec_masterKey(mmKey, MAC_Key, masterKey);
   /*
   printf("masterKey [%s]\n",masterKey);
   */
   
   /* º∆À„MACDATA */
   memset(MAC_DATA, 0x00, 9);
   Cal_MACDATA(in_data,in_len,MAC_DATA);
   
   /* º∆À„mac */
   memset(mac, 0x00, 9);
   des_encode(masterKey, MAC_DATA, mac);
   
   String2Hex(mac, 16);
   /*
   printf("MAC_1: [%s                ]", mac);
   */
   
   /* “‘8Œª0x08ÃÓ≥‰µƒ◊÷∑˚¥Æ◊˜Œ™MAC_DATA£¨º∆À„≤π≥‰mac */
   memset(mac_add, 0x00, 33);
   memset(MAC_DATA, 0x00, 9);
   memset(MAC_DATA, 0x08, 8);
   des_encode(masterKey, MAC_DATA, mac_add);
   
   String2Hex(mac_add, 16);
   /*
   printf("\nMAC_2: [                %s]", mac_add);
   */
   
   
   strncat((char *)mac,(char *)mac_add,16);

   return;
}

/**************************************************************
 * ∞—MAC_KeyΩ‚√‹≥…masterKey
 * ≤Œ ˝£∫ des_key      DES÷˜√‹‘ø
 *        in           MAC_Key
 *        out          Ω‚√‹∫ÛµƒmasterKey
 * Ãÿ ‚÷Æ¥¶£∫ masterKeyº”√‹≥…MAC_Key ±»Ù≥§∂»≤ª◊„8Œª£¨“‘0x04≤π◊„ 
 **************************************************************/
void dec_masterKey(unsigned char des_key[8], unsigned char *in, unsigned char *out)
{
   int i;
   
   /* ”√±Í◊ºDESÀ„∑®Ω‚√‹masterKey */
   des_decode(des_key, in, out);
   
   /* »•µÙƒ©Œ≤µƒ0x04 */
   for(i=7;i>=0;i--) {
      if(0x04==out[i]) out[i]=0x00;
   }
   return;
}

/************************************************************
 * º∆À„ ˝æ›µƒMAC_DATA
 * À„∑®£∫ ¥”±®ŒƒµƒΩª“◊∞¸ ˝æ›–≈œ¢µƒµ⁄“ª∏ˆ◊÷Ω⁄ø™ º£¨
 *     Ω´≤Œ”Îµƒ ˝æ›∑÷≥…8∏ˆ◊÷Ω⁄µƒ–°∑›£¨D1£¨D2£¨D3°≠°≠Dn£¨
 *     »Áπ˚±®Œƒ≤ª «8µƒ±∂ ˝£¨∫Û≤π16Ω¯÷∆µƒ0£®0x00£©£¨≤π◊„8µƒ±∂ ˝°£
 *     ”√8∏ˆ◊÷Ω⁄µƒ16Ω¯÷∆0µƒ≥ı÷µD0∫Õ ˝æ›øÈD1£¨D2£¨°≠°≠DnΩ¯––“ÏªÚ£¨
 *     Ω·π˚Œ™8∏ˆ◊÷Ω⁄µƒMACDATA£ª
 * ≤Œ ˝£∫  in_data            ¥˝¥¶¿Ìµƒ ˝æ›¥Æ
 *         in_len              ˝æ›≥§∂»
 *         MAC_DATA           MAC_DATA
 ************************************************************/
void Cal_MACDATA(unsigned char * in_data, int in_len, unsigned char *MAC_DATA)
{
   unsigned char D0[9];
   unsigned char Dn[9];
   int  dn_start;
   int  i;
   
   memset(D0, 0x00, 9);
   dn_start=0;
   while(in_len>0){
      memset(Dn, 0x00, 9);
      if(in_len>=8) {
         memcpy(Dn, in_data+dn_start, 8);
      }
      else {
         memcpy(Dn, in_data+dn_start, in_len);
      }
      for(i=0;i<9;i++) D0[i]^=Dn[i];
      in_len-=8;
      dn_start+=8;
   }
   memcpy(MAC_DATA, D0, 8);
   return;
}

/**************************************************************
 * “‘œ¬Œ™“∆∂ØMAC‘§¥¶¿Ì∫Ø ˝
 **************************************************************/

/******************************************************************
* Function : pre_mob
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ÷–…Ω/∑…Ω“∆∂Ø±®ŒƒΩ‚Œˆ‘§¥¶¿Ì∫Ø ˝æ›
* Others   : ÷–…Ω/∑…Ω“∆∂Ø±®Œƒ∏Ò Ω£∫
        1.±®Œƒ”–«∞÷√≥§∂»6£ª
        2.8ŒªMAC÷µ∑≈‘⁄≥§∂»÷Æ∫Û£¨ ˝æ›÷Æ«∞£ª
        3.MACÀ„∑®£∫ ¥”±®ŒƒµƒΩª“◊∞¸ ˝æ›–≈œ¢µƒµ⁄“ª∏ˆ◊÷Ω⁄ø™ º£¨
          Ω´≤Œ”Îµƒ ˝æ›∑÷≥…8∏ˆ◊÷Ω⁄µƒ–°∑›£¨D1£¨D2£¨D3°≠°≠Dn£¨
          »Áπ˚±®Œƒ≤ª «8µƒ±∂ ˝£¨∫Û≤π16Ω¯÷∆µƒ0£®0x00£©£¨≤π◊„8µƒ±∂ ˝°£
          ”√8∏ˆ◊÷Ω⁄µƒ16Ω¯÷∆0µƒ≥ı÷µD0∫Õ ˝æ›øÈD1£¨D2£¨°≠°≠DnΩ¯––“ÏªÚ£¨
          Ω·π˚Œ™8∏ˆ◊÷Ω⁄µƒMACDATA£ª◊Ó∫ÛΩ´º∆À„≥ˆµƒMACDATA”√±Í◊ºDESÀ„∑®º”√‹º¥≥…°£
        4.º∆À„DES ±”√µΩµƒ÷˜√‹‘ø∫Õ∑÷…¢√‹‘øæ˘Œ™‘º∂®÷µ.
        5.±®Œƒµƒ∏Ò ΩŒ™£∫ ˝æ›≥§∂»6Œª(≤ª∫¨¡˘Œª±æ…Ì£´MAC¥Æ)£´Ωª“◊ ˝æ›
        6.±æ∫Ø ˝Ωˆ∂‘±®ŒƒMACΩ¯–––£—È£¨≤ª∂‘±®ŒƒΩ¯––À˚¥¶¿Ì
*******************************************************************/
int pre_mob( CurrInf * curr_inf,  char * in_data, int in_len, char ** out_data, int * out_len)
{
   char	* tmp = NULL;
   char  in_mac[33];     /* Õ®—∂ ‰»Îµƒ–£—È ˝æ› */
   unsigned char  cal_mac[33];    /* ∏˘æ›µ±«∞ ˝æ›º∆À„≥ˆ¿¥µƒMAC */
   unsigned char  *op_DATA;       /* ¥˝º∆À„MACµƒ ˝æ›÷∏’Î */
   unsigned char  MAC_DATA[33];   /* ±£¥ÊMACDATA */
   unsigned char  MAC_key[33];    /* ±£¥Ê¡Ÿ ±MACKEY */
   int   ret;

	 system("date >> /tmp/date.tmp");

   herrlog(LOG_OPF, "---->>>>Ωª“◊[%s]’˝‘⁄Ω¯––‘§¥¶¿Ì>>>>----",curr_inf->req_id);
   herrlog(LOG_OPF, " ’µΩ±®Œƒ:[%d][%s]", in_len, in_data);
   herrlog(LOG_OPF, "Step 1: ◊™¥¢±®Œƒ");      
   *out_data = (char *)malloc(in_len+1);
   if(*out_data == NULL){
      herrlog(LOG_OPF, "∑÷≈‰ƒ⁄¥Ê ß∞‹");
      return(DP_FAIL);
   }
   memset( *out_data, 0x00, in_len+1);
   memcpy( *out_data, in_data, in_len);
   
   herrlog(LOG_OPF, "Step 2: »∑∂® «∑Ò–£—ÈMAC");
   if(curr_inf->rq_or_rp==2) {
      /* ±®Œƒ «µ⁄»˝∑Ω∑µªÿœÏ”¶∞¸ ± */
      if(!OPF_RPCHK) {
         /* ≤ª–£—ÈMAC */
         herrlog(LOG_OPF, "  Ωª“◊œÏ”¶∞¸£¨«“≤ª“™«Û–£—È£¨’˝≥£∑µªÿ!!! ");
         herrlog(LOG_OPF," ‰≥ˆ±®Œƒ[%d][%s]",*out_len, *out_data);
         herrlog(LOG_OPF, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
         return(DP_SUCC);
      }
   }
   
   herrlog(LOG_OPF, "Step 3: º∆À„MAC");
   op_DATA=(unsigned char *)(in_data+8);
   memset(MAC_DATA, 0x00, 33);
   Cal_MACDATA(op_DATA,in_len-8,MAC_DATA);
   /*
   herrlog(LOG_OPF, "–Ë“™º∆À„MACDATAµƒ÷µ£∫[%s]",op_DATA);
   */
   /* º∆À„mac */
   memset(cal_mac, 0x00, 33);   
   memset(MAC_key, 0x00, 33);   
   des_encode((unsigned char *)MMKEY_OPF, (unsigned char *)RNDKEY_OPF, MAC_key);
   des_encode(MAC_key, MAC_DATA, cal_mac);
   
   herrlog(LOG_OPF, "Step 4: –£—ÈMAC");
   memset(MAC_key, 0x00, 33);
   memcpy(MAC_key, in_data, 8);
   if(0!=strncmp((char *)MAC_key, (char *)cal_mac, 8)) {
      /* –£—È¬Î¥ÌŒÛ */
      String2Hex(MAC_key, 16);
      String2Hex(cal_mac, 16);
      herrlog(LOG_OPF, "–£—ÈMAC¥ÌŒÛ in[%s]!=cal[%s]",MAC_key,cal_mac);
      herrlog(LOG_OPF, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
      hfree((void **)out_data);
      return(DP_FAIL);
   }
   
   herrlog(LOG_OPF, "MAC–£—È’˝»∑£¨ ‰≥ˆ±®Œƒ[%d]\n[%s]",*out_len, *out_data);
   herrlog(LOG_OPF, "---->>>>Ωª“◊[%s]‘§¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}

/******************************************************************
* Function : spe_opf
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ÷–…Ω…Á±£±®ŒƒΩ‚ŒˆÃÿ ‚¥¶¿Ì∫Ø ˝æ›
* Others   : ÷–…Ω/∑…Ω“∆∂Ø±®Œƒ∏Ò Ω£∫
        1.±®Œƒ”–«∞÷√≥§∂»6£ª
        2.8ŒªMAC÷µ∑≈‘⁄≥§∂»÷Æ∫Û£¨ ˝æ›÷Æ«∞£ª
        3.MACÀ„∑®£∫ ¥”±®ŒƒµƒΩª“◊∞¸ ˝æ›–≈œ¢µƒµ⁄“ª∏ˆ◊÷Ω⁄ø™ º£¨
          Ω´≤Œ”Îµƒ ˝æ›∑÷≥…8∏ˆ◊÷Ω⁄µƒ–°∑›£¨D1£¨D2£¨D3°≠°≠Dn£¨
          »Áπ˚±®Œƒ≤ª «8µƒ±∂ ˝£¨∫Û≤π16Ω¯÷∆µƒ0£®0x00£©£¨≤π◊„8µƒ±∂ ˝°£
          ”√8∏ˆ◊÷Ω⁄µƒ16Ω¯÷∆0µƒ≥ı÷µD0∫Õ ˝æ›øÈD1£¨D2£¨°≠°≠DnΩ¯––“ÏªÚ£¨
          Ω·π˚Œ™8∏ˆ◊÷Ω⁄µƒMACDATA£ª◊Ó∫ÛΩ´º∆À„≥ˆµƒMACDATA”√±Í◊ºDESÀ„∑®º”√‹º¥≥…°£
        4.º∆À„DES ±”√µΩµƒ÷˜√‹‘ø∫Õ∑÷…¢√‹‘øæ˘Œ™‘º∂®÷µ.
        5.±®Œƒµƒ∏Ò ΩŒ™£∫ ˝æ›≥§∂»6Œª(≤ª∫¨¡˘Œª±æ…Ì£´MAC¥Æ)£´Ωª“◊ ˝æ›
        6.±æÃÿ ‚¥¶¿ÌΩˆ∂‘±®Œƒ‘ˆº”MAC£¨≤ª∂‘±®ŒƒΩ¯––∆‰À˚¥¶¿Ì
*******************************************************************/
int spe_mob(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{
   XmlNode	* tmpNode = NULL;
   char * txncod = NULL;
   unsigned char  cal_mac[33];    /* ∏˘æ›µ±«∞ ˝æ›º∆À„≥ˆ¿¥µƒMAC */
   unsigned char  MAC_DATA[33];   /* ±£¥ÊMACDATA */
   unsigned char  MAC_key[33];    /* ±£¥Ê¡Ÿ ±MACKEY */
   unsigned char  *op_DATA;       /* ¥˝º∆À„MACµƒ ˝æ›÷∏’Î */
   int   ret;

   herrlog(LOG_OPF, "---->>>>Ωª“◊[%s]’˝‘⁄Ω¯––±®ŒƒÃÿ ‚¥¶¿Ì>>>>----",curr_inf->req_id);
   herrlog(LOG_OPF," ’µΩ¥˝¥¶¿Ì±®Œƒ[%s]",in_data);

   herrlog(LOG_OPF, "spe_mob:STEP_1 ‘§¡ÙMACø’º‰£¨◊™¥¢Ωª“◊ ˝æ›");
	*out_data = (char *)malloc(in_len+8+1);
   if(*out_data == NULL){
      herrlog(LOG_OPF, "∑÷≈‰ƒ⁄¥Ê ß∞‹");
      return(DP_FAIL);
   }
	*out_len = in_len+8;
	memset(*out_data, 0x00, (*out_len)+1);
   memcpy(*out_data+8, in_data, in_len);   /* œ»∞— ‰»Î ˝æ›◊™¥¢µΩ ‰≥ˆ ˝æ› */

   herrlog(LOG_OPF, "spe_mob:STEP_2 º∆À„MAC");
   memset(MAC_DATA, 0x00, 33);
   op_DATA=(unsigned char *)in_data;
   Cal_MACDATA(op_DATA,in_len,MAC_DATA);
   
   /* º∆À„mac */
   memset(cal_mac, 0x00, 33);    
   memset(MAC_key, 0x00, 33);  
   des_encode((unsigned char *)MMKEY_OPF, (unsigned char *)RNDKEY_OPF, MAC_key);
   des_encode(MAC_key, MAC_DATA, cal_mac);
   
   memset(MAC_DATA, 0x00, 33);
   memcpy(MAC_DATA, cal_mac, 8);
   String2Hex(MAC_DATA, 16);
   herrlog(LOG_OPF, "spe_mob:STEP_3 ±£¥ÊMAC [%s][%s]",cal_mac,MAC_DATA);
   
   memcpy(*out_data, cal_mac, 8);
   herrlog(LOG_OPF, "spe:Step 3:  ‰≥ˆ±®Œƒ[%s]",*out_data);
   herrlog(LOG_OPF, "---->>>>Ωª“◊[%s]±®ŒƒÃÿ ‚¥¶¿ÌΩ· ¯>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}

/**************************************************************
 * “‘œ¬Œ™±Í◊ºDESÀ„∑®∫Ø ˝
 **************************************************************/
 
/*des.c*/
#include <stdio.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

struct parm {
   char keya[8];
   int  ekey[16][48];
   int  dkey[16][48];
} *parmp;

static int desargorithm(unsigned char *inparm, unsigned char *outparm,
struct parm *pmp, int encrypt);
static void morioip(char *inarea);
static void moriof(int j);
static void morioe();
static void morios();
static void moriop();
static void morioiip();
static void AUOC050(unsigned char *getkey, struct parm *pmp);
static void moriomkey(char *key64, struct parm *pmp);
static void moriopc1(char *key64, int *l28, int *r28);
static void moriolshift(int *l28, int *r28, int j);
static void moriopc2(struct parm *pmp, int *l28, int *r28, int jj);
static void morioinparam(char *getkey, char *key64);

static int tabip_t[64] = {
   58, 50, 42, 34, 26, 18, 10,  2,
   60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6,
   64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1,
   59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5,
   63, 55, 47, 39, 31, 23, 15,  7
};

static int tabllP_t[64] = {
   40,  8, 48, 16, 56, 24, 64, 32,
   39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30,
   37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28,
   35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26,
   33,  1, 41,  9, 49, 17, 57, 25
};

static int tabe_t[48] = {
   32,  1,  2,  3,  4,  5,
   4,  5,  6,  7,  8,  9,
   8,  9, 10, 11, 12, 13,
   12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21,
   20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29,
   28, 29, 30, 31, 32,  1
};

static int tabs_t[8][4][16] = {
   {
      {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
   },
   {
      {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
      {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
      {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
      {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
   },
   {
      {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
      {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
      {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
      {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
   },
   {
      {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
      {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
      {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
      {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
   },
   {
      {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
      {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
      {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
      {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
   },
   {
      {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
      {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
      {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
      {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
   },
   {
      {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
      {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
      {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
      {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
   },
   {
      {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
      {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
      {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
      {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
   }
};

static int tabp_t[32] = {
   16,  7, 20, 21,
   29, 12, 28, 17,
   1, 15, 23, 26,
   5, 18, 31, 10,
   2,  8, 24, 14,
   32, 27,  3,  9,
   19, 13, 30,  6,
   22, 11,  4, 25
};

static int tabpc1_t[56] = {
   57, 49, 41, 33, 25, 17,  9,
   1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

static int tabnls_t[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

static int tabtabpc2_t[48] = {
   14, 17, 11, 24,  1,  5,
   3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};


static int l_[32],r_[32],frk_[32],e_[48],srk_[48],so_[8];

static int tttpc1_t[56] = {
   57, 49, 41, 33, 25, 17,  9,
   1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

static int tttnls_t[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

static int ttttabpc2_t[48] = {
   14, 17, 11, 24,  1,  5,
   3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

static char *outarea;

int desargorithm(unsigned char *inparm, unsigned char *outparm,
struct parm *pmp, int encrypt)
{

   int count=0;
   int count2=0;
   int w, j, k;

   parmp = pmp;

   outarea = (char*)outparm;

   morioip((char*)inparm);
   for (j=0; j<16; j++) {
      if(encrypt) moriof(j);
      else moriof(15-j);
      for (k=0; k<32; k++) {
         w = l_[k];
         l_[k] = r_[k];
         r_[k] = w ^ frk_[k];
      }
   }
   morioiip();
   return 0;
}

void morioip(char *inarea)
{
   int j,k,dl,wk[64];

   for (j=0; j<8; j++) {
      dl = inarea[j];
      for (k=0; k<8; k++) {
         wk[8*j+k] = dl>>(7-k) & 1;
      }
   }
   for (j=0; j<64; j++) {
      dl = tabip_t[j]-1;
      if (j<32)
      l_[j] = wk[dl];
      else
      r_[j-32] = wk[dl];
   }
   return;
}
void moriof(int j)
{
   int k;

   morioe();
   for (k=0; k<48; k++) {
      srk_[k] = e_[k] ^ parmp->ekey[j][k];
   }

   morios();
   moriop();

   return;
}

void morioe()
{
   int k, el;
   for (k=0; k<48; k++) {
      el = tabe_t[k] - 1;
      e_[k] = r_[el];
   }
   return;
}

void morios()
{
   int j, k, l, x, y;
   for (j=0; j<8; j++) {
      k = j * 6;
      y = srk_[k] << 1 | srk_[k+5];
      x = 0;
      for (l=1; l<=4; l++) {
         x |= srk_[k+l]<<(4-l);
      }
      so_[j] = tabs_t[j][y][x];
   }

   return;
}

void moriop()
{
   int wk[32], j, k, pl;

   for (j=0; j<8; j++) {
      pl = so_[j];
      for (k=0; k<4; k++) {
         wk[4*j+k] = pl>>(3-k) & 1;
      }
   }

   for (j=0; j<32; j++) {
      pl = tabp_t[j] - 1;
      frk_[j] = wk[pl];
   }

   return;
}

void morioiip()
{
   int lr_[64], wk[64], j, k, dl;

   for (k=0; k<64; k++) {
      if (k<32)
      lr_[k] = r_[k];
      else
      lr_[k] = l_[k-32];
   }

   for (k=0; k<64; k++) {
      dl = tabllP_t[k]-1;
      wk[k] = lr_[dl];
   }

   for (j=0; j<8; j++) {
      outarea[j] = 0;
      for (k=0; k<8; k++) {
         outarea[j] |= wk[8*j+k] << (7-k);
      }
   }

   return;
}

void AUOC050(unsigned char *getkey, struct parm *pmp)
{
   char key64[64];
   memcpy(pmp->keya,getkey,8);
   morioinparam((char*)getkey, key64);
   moriomkey(key64, pmp);
   return;
}

void moriomkey(char *key64, struct parm *pmp)
{
   int j;
   int l28[30], r28[30];

   moriopc1(key64,l28, r28);
   for(j=0; j<16; j++) {
      moriolshift(l28, r28, j);
      moriopc2(pmp, l28, r28, j);
   }

   return;
}

void moriopc1(char *key64, int *l28, int *r28)
{
   int j, k;

   for(j=0; j<56; j++) {
      k = tttpc1_t[j] -1;
      if (j < 28) {
         l28[j] = (int)key64[k];
      }
      else {
         r28[j-28] = (int)key64[k];
      }
   }

   return;
}

void moriolshift(int *l28, int *r28, int j)
{
   int k, s;
   s = tttnls_t[j];
   l28[28] = l28[0];
   r28[28] = r28[0];
   l28[29] = l28[1];
   r28[29] = r28[1];

   for(k=0; k<28; k++) {
      l28[k] = l28[k+s];
      r28[k] = r28[k+s];
   }
   return;
}

void moriopc2(struct parm *pmp, int *l28, int *r28, int jj)
{
   int wk[56], k, p2;
   for(k=0; k<56; k++) {
      if (k < 28)
      wk[k] = l28[k];
      else
      wk[k] = r28[k-28];
   }
   for(k=0; k<48; k++) {
      p2 = ttttabpc2_t[k] - 1;
      pmp->ekey[jj][k] = wk[p2];
   }
   return;
}

void morioinparam(char *getkey, char *key64)
{
   int i, k, k1;
   for (i=0; i<8; i++) {
      k1 = getkey[i];
      for (k=0; k<8; k++) {
         key64[8*i+k] = k1 >>(7-k) & 1;
      }
   }
   return;
}

/*****************************************************************************
* Name : des_encode
* Descripe:
*   ∂‘inΩ¯––DESº”√‹‘ÀÀ„£¨≤¢∑µªÿ‘ÀÀ„Ω·π
* Paramater:
*   [in]des_key    : º”√‹µƒ√‹‘ø
*   [in]in            : “™º”√‹µƒ ˝æ›
*   [out]out        : º”√‹∫Ûµƒ ˝æ›
* Return value:Œﬁ
*****************************************************************************/
void des_encode(unsigned char des_key[8], unsigned char *in, unsigned char *out)
{
   struct parm key_area;

   pthread_mutex_lock(&lock);

   AUOC050(des_key, &key_area);
   desargorithm(in, out, &key_area, TRUE);

   pthread_mutex_unlock(&lock);

   return;
}

/*****************************************************************************
* Name : des_decode
* Descripe:
*   ∂‘inΩ¯––DESΩ‚√‹‘ÀÀ„£¨≤¢∑µªÿ‘ÀÀ„Ω·π
* Paramater:
*   [in]des_key    : Ω‚√‹µƒ√‹‘ø
*   [in]in            : “™Ω‚√‹µƒ ˝æ›
*   [out]out        : Ω‚√‹∫Ûµƒ ˝æ›
* Return value:Œﬁ
*****************************************************************************/
void des_decode(unsigned char des_key[8], unsigned char *in, unsigned char *out)
{
   struct parm key_area;

   pthread_mutex_lock(&lock);

   AUOC050(des_key, &key_area);
   desargorithm(in, out, &key_area, FALSE);

   pthread_mutex_unlock(&lock);

   return;
}

/***********************************************
 * Ω´16Ω¯÷∆±Ì æµƒ◊÷∑˚¥Æ◊™ªª≥…≥£πÊ◊÷∑˚¥Æ
 * ≤Œ ˝£∫ s        ¥˝◊™ªª‘¥◊÷∑˚¥Æ
 ***********************************************/
int   Hex2String(char*   s)
{
   char   a,b;
   int   i,j;
   char*   p=s;
   
   for(i=0;*s!=0;i++)
   {
      a=*s;
      if(a>0x29   &&   a<0x3A)  /*'0'-'9'*/
      a-=0x30;
      else   if(a>0x40   &&   a<0x47) /* 'A'-'F'*/
      a-=0x37;
      else   if(a>0x60   &&   a<0x67) /* 'a'-'f'*/
      a-=0x57;
      else  /* error*/
      break;
      *s=0x00;
      s++;
      b=*s;
      if(b>0x29   &&   b<0x3A) /* '0'-'9'*/
      b-=0x30;
      else   if(b>0x40   &&   b<0x47) /* 'A'-'F'*/
      b-=0x37;
      else   if(b>0x60   &&   b<0x67) /* 'a'-'f'*/
      b-=0x57;
      else  /* error*/
      break;
      p[i]=(a<<4)   |   b;
      *s=0x00;
      s++;
   }
   p[i]=0;
   return   i;
}

/***********************************************
 * Ω´◊÷∑˚¥Æ◊™ªª≥…16Ω¯÷∆±Ì æµƒ◊÷∑˚¥Æ
 * ≤Œ ˝£∫ s        ¥˝◊™ªª‘¥◊÷∑˚¥Æ
 *        out_len  ◊™ªª∫Ûµƒ◊Ó¥Û≥§∂»
 * Àµ√˜£∫µ˜”√’ﬂ–Î‘§œ»Œ™s∑÷≈‰◊„πªø’º‰(÷¡…Ÿout_len+1)!!!
 ***********************************************/
int   String2Hex(char* s,int out_len)
{
   int slen;
   int   i;
   char tmp[30];
   char *out_data;
   char *p;
   
   p=s;
   slen=out_len/2;
   memset(tmp,0x00,30);
   if(slen>strlen(s)) slen=strlen(s);
   out_data = (char *)malloc(out_len+1);
   if(out_data == NULL){
      return(-1);
   }
   memset(out_data, 0x00, out_len+1);
   for(i=0;i<slen;i++) {
      sprintf(tmp, "%02x", *p);
      strncat(out_data, tmp, 2);
      p++;
   }
   memset(s, 0x00, out_len+1);
   memcpy(s,out_data,slen*2);
   for(i=slen*2;i<out_len;i++) s[i]=0x30;
   free(out_data);
   return   i;
}

