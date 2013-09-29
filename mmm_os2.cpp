/**********************************************
*   OS/2 CPP file for MMMX Editor             *
*   Contains OS/2 WARP specific functions     *
*    ( tested on Warp, Warp connect )         *
***********************************************/

#include "mmm_os2.h"

extern unsigned _stklen=8192;
int MonoAttrs[NAttr]={7,0x70,1,0x70,0x17,0x6f,0x11,0x70};

//&<<&mmm_Screen::mmm_Screen();
mmm_Screen::mmm_Screen(){
    VIOMODEINFO modedata;

    saveVideoConfig.cb = sizeof(saveVideoConfig);
    VioGetMode( &saveVideoConfig, 0 );
    if(! (saveVideoConfig.fbType & 0x01 )) Editor.attrs=MonoAttrs;

    modedata.cb=sizeof(modedata);
    if(Editor.attrs==MonoAttrs)
        modedata.fbType = 0x00;
    else
        modedata.fbType = 0x01;
    modedata.color = 4;
    modedata.col = 80;
    modedata.row = 30;
    modedata.hres = 640;
    modedata.vres = 480;
    VioSetMode( &modedata, 0 ) ;
    modedata.cb=sizeof(modedata);
    VioGetMode( &modedata, 0 );

    WIDTH=modedata.col;
    HEIGHT=modedata.row;

//&<<&    Change Cursor Type     //// comment is set
#if 0
         typedef struct _VIOCURSORINFO {  /* vioci */
           USHORT   yStart;               /*cursor start line */
           USHORT   cEnd;                 /* cursor end line */
           USHORT   cx;                   /* cursor width */
           USHORT   attr;                 /* -1=hidden cursor, any other=normal
                                                cursor */
         } VIOCURSORINFO;
 PVIOCURSORINFO   CursorData;    /* Cursor characteristics */

 VioSetCurType(CursorData, 0 );
#endif
//&>>&2 0 2 2C
}
//&>>&0 0 0 16
//&<<&mmm_Screen::~mmm_Screen();
mmm_Screen::~mmm_Screen(){
   saveVideoConfig.cb = sizeof(saveVideoConfig);
   VioSetMode( &saveVideoConfig, 0 );
}
//&>>&0 0 0 17
void mmm_Screen::ClrCursor(){}
//&<<&void mmm_Screen::SetCursor(int x,int y,int attr);
void mmm_Screen::SetCursor(int x,int y,int attr){
    VioSetCurPos(y,x,0);
}
//&>>&0 0 0 F
//&<<&void DrawLine(char *Str, int PosY, char Attr,int slen);
void DrawLine(char *Str, int PosY, char Attr,int slen){
   static char *PRTLINE=0;
   if(!PRTLINE)PRTLINE=new char[mmm_screen.GetW()+1];
   for(int i=0 ; i<mmm_screen.GetW(); i++) {
      PRTLINE[i]=(char)*Str;
      if(*Str) ++Str;
      }
   VioWrtCharStrAtt( PRTLINE, mmm_screen.GetW() , PosY, 0 , &Attr, 0);
}
//&>>&7 0 7 28
void SetTitle(char *,char *){}

//&<<&void ProcessShiftsStatus(USHORT stat);
//&<<&inline void setfix(){
inline void setfix(){
  mmm_f_FixShift^=mmm_f_Shift;
  mmm_f_FixAlt^=mmm_f_Alt;
}
//&>>&2 0 2 E
void ProcessShiftsStatus(USHORT stat){
    static USHORT oldstat;
    if( (stat & 0x4000) )
        { setfix(); mmm_f_Caps=1; }        /// CAPS pressed
    else mmm_f_Caps=0;

    if( stat & 0x3   ) mmm_f_Shift=1; else mmm_f_Shift=0; /// Shift pressed
    if( stat & 0x500 ) mmm_f_Ctrl=1; else mmm_f_Ctrl=0; /// Ctrl pressed
    if( stat & 0xA00 ) mmm_f_Alt=1; else mmm_f_Alt=0; /// Ctrl pressed
    if(oldstat!=stat) Redr();
    oldstat=stat;
}
//&>>&0 0 0 34

//&<<&mmm_KeyBoard::mmm_KeyBoard();
mmm_KeyBoard::mmm_KeyBoard(){
////    SaveKBD.cb = sizeof(KBDINFO);
////    if(KbdGetStatus( &SaveKBD, 0)){printf("KbdGetStatus error"); exit(0);}
    InitKeyboardLayout();
    AltCase=InitDefaultAltCase();
    }
//&>>&2 0 2 2F
//&<<&mmm_KeyBoard::~mmm_KeyBoard();
mmm_KeyBoard::~mmm_KeyBoard(){
////    SaveKBD.cb = sizeof(KBDINFO);
////    if(KbdSetStatus( &SaveKBD, 0)){printf("KbdSetStatus error"); exit(0);}
}
//&>>&2 0 2 2F
//&<<&void mmm_KeyBoard::InitKeyboardLayout();
void mmm_KeyBoard::InitKeyboardLayout(){
    int i,j;
    for(i=0;i<4;i++) for(j=0;j<108;j++) keys[i][j]='.';
    }
//&>>&0 0 0 17
//&<<&char *mmm_KeyBoard::InitDefaultAltCase(){
char *mmm_KeyBoard::InitDefaultAltCase(){
  char *AltCase=new char[256];
  for(int i=0;i<256;i++){
    AltCase[i]=
      i>='A' && i<='Z' ? i+('a'-'A') :
      i>='a' && i<='z' ? i-('a'-'A') :
//      i>='А' && i<='П' ? i+('а'-'А') :
//      i>='Р' && i<='Я' ? i+('р'-'Р') :
//      i>='а' && i<='п' ? i-('а'-'А') :
//      i>='р' && i<='я' ? i-('р'-'Р') :
      i;
  }
  return AltCase;
}
//&>>&0 0 0 12
//&<<&void mmm_KeyBoard::SetACode(int n){ 
void mmm_KeyBoard::SetACode(int n){
    acode=mmm_KBD.keys[n];
    }
//&>>&1 0 1 11
//&<<&int mmm_KeyBoard::GetScan();
int mmm_KeyBoard::GetScan(){
    View();
    if( retcode=KbdCharIn ( &keydata, IO_WAIT , 0 ) )
        {puts("KbdCharIn error!\n");exit(-1);}
    ProcessShiftsStatus( keydata.fsState );
    return keydata.chScan;
    }
//&>>&3 0 3 F
//&<<&void MkScan(int code);             

void MkScan(int code){
  mmm_KBD.LastScanCode=code;
  Command(code + (mmm_f_Shift<<8) +(mmm_f_Alt<<9)+(mmm_f_Ctrl<<10)+(mmm_f_Caps<<11) );
}
//&>>&0 0 0 0

//&<<&Keyboard Layouts    

char *mcode=mmm_KBD.keys[0],*acode=mmm_KBD.keys[2];

volatile int   mmm_f_Caps=0;
volatile int   mmm_f_FixShift=0,mmm_f_FixAlt=0;
volatile int   mmm_f_Shift=0,mmm_f_Alt=0,mmm_f_Ctrl=0;
//&>>&3 0 3 0

void Beep(){ DosBeep(1760,50); }

//&<<&void __EXIT();
/*
   EXECUTER_FILENAME=

   e:
   cd \amstex
   commands
   %comspec
   c:
   cd \
   i:\astr\mmm.bat -1 e:\mmm.dir -2 e:\amstex\astex.tex
*/

//&<<&void PutCurDir(FILE *f){   // prints current drive & directory into FILE *f
void PutCurDir(FILE *f){
  char *cd=getcurdir();                        // current disk
  int lcd=strlen(cd);
  if(lcd>3 && cd[lcd-1]=='\\') cd[--lcd]=0;
  unsigned int drv=SaveGetDrive(); // 1='A'
  fprintf(f,"%c:\ncd %s\n",drv+'a'-1,cd);
  delete cd;
}
//&>>&5 0 5 A

void __EXIT(){
//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("void __EXIT(){ \n");
  #endif
//&>>&2 0 2 7
    char *s;
    FILE *fRunScript,*filelist;

    s=MFileName(EXECUTER_FILENAME);
    fRunScript=fopen(s,"w"); MemTest(fRunScript!=0);
    delete s;

    fputs("@echo off\n",fRunScript);
    PutCurDir(fRunScript);
    while(mmm_LineClipboard && mmm_LineClipboard->prev)
        mmm_LineClipboard=mmm_LineClipboard->prev;
    while(mmm_LineClipboard && mmm_LineClipboard->next){
        mmm_LineClipboard->Write(fRunScript,FILE_ASCII);
        mmm_LineClipboard=mmm_LineClipboard->next;
        }
    PutCurDir(fRunScript);
    fclose(fRunScript);

    s=MFileName("__mmm__.mmm");
    filelist=fopen(s,"w"); MemTest(filelist!=0);
    delete s;
    PerformExitingFromFiles(filelist);
    fclose(filelist);

//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("    } exit(-1)...\n");
  #endif
//&>>&0 0 0 0
    execl(MFileName(EXECUTER_FILENAME),0);
    exit(-1);
}
///// mmm_os2.err mmm_os2.err mmm_os2.err mmm_os2.err mmm_os2.err
//&>>&1C 0 13 0
void MMMlib_Console    (int ccode){};

//&<<&void File::MkWild();
void File::MkWild(){
    char str[0x120];
    char *pcFileName;
//&<<&    CreateDirectoriesList
    {
    FILEFINDBUF  ff_buff;              /* определено в bsedos.h */
    ULONG handle=0xffff;            /* cтарт с этого значения */
    ULONG count=1;
    APIRET rc;

    rc=DosFindFirst( "*.*",&handle,
               FILE_DIRECTORY ,
               &ff_buff,sizeof(ff_buff),&count,FIL_STANDARD);
    while(rc==0){
        pcFileName=ff_buff.achName+6;
        pcFileName[0x60]=0;
        if( *(ff_buff.achName+1) & 0x10  &&  strcmp(pcFileName,".")){
            sprintf(str,"%s\\%s",pcFileName,buf);
            NewLine(str)->LinkBefore(pos);
            }
        rc=DosFindNext( handle,&ff_buff,sizeof(ff_buff),&count);
        }
    DosFindClose( handle );
    }
//&>>&D 0 D 2B
//&<<&    Create FileList
    NewLine("->")->LinkBefore(pos);

    FILEFINDBUF  ff_buff;              /* определено в bsedos.h */
    ULONG handle=0xffff;            /* cтарт с этого значения */
    ULONG count=1;
    APIRET rc;

    handle=0xffff;
    rc=DosFindFirst( buf ,&handle,
               FILE_DIRECTORY | FILE_ARCHIVED ,
               &ff_buff,sizeof(ff_buff),&count,FIL_STANDARD);
    while(rc==0){
        if( (*(ff_buff.achName+1) & 0x10 ) == 0 )
            {
            pcFileName=ff_buff.achName+6;
            pcFileName[0x60]=0;
            sprintf(str,"%-35s%10ld   %c%c%c%c",
                pcFileName, ff_buff.cbFileAlloc,
                *(ff_buff.achName+1)& 1   ? 'r' : '.',
                *(ff_buff.achName+1)& 2   ? 'h' : '.',
                *(ff_buff.achName+1)& 4   ? 's' : '.',
                *(ff_buff.achName+1)&0x20 ? 'a' : '.');
            NewLine(str)->LinkBefore(pos);
            }
        rc=DosFindNext( handle,&ff_buff,sizeof(ff_buff),&count);
        }
    DosFindClose( handle );
    NewLine("")->LinkBefore(pos);
//&>>&1C 0 17 1A
  while(pos->prev) pos=pos->prev;
}

/////// os2api\findnext.cpp

//&>>&4 0 4 14
///// mmm_os2.err mmm_os2.err mmm_os2.err mmm_os2.err mmm_os2.err
//&>>&1A 0 1A 11
