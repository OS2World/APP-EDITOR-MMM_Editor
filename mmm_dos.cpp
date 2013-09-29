/***************************************************
*   DOS CPP file for MMMX Editor                   *
*   Contains MS-DOS/PHARLAP specific functions     *
****************************************************/

#include "mmm_dos.h"

extern unsigned _stklen=8192;
int MonoAttrs[NAttr]={7,0x70,1,0x70,0x17,0x6f,0x11,0x70};


//&<<&mmm_Screen::mmm_Screen();
#ifdef __386__
//&<<&Watcom+Pharlap version
#include"d:/pharlap/include/pharlap.h"

mmm_Screen::mmm_Screen(){
  unsigned char X[64];
  unsigned char far *D=X;
  need=1;
  char res;
  struct fp{
    int off;
    short seg;
  }kkk;
  kkk.off=0xb8000;
  kkk.seg=SS_DOSMEM;
  OldCurs=0;

  union REGS __r;
  struct SREGS __s;
  __r.h.ah=0xF;
  int386(0x10,&__r,&__r);
  OldScr=__r.h.al;

  __r.h.ah=3;
  __r.h.bh=0;
  int386(0x10,&__r,&__r);
  OldCl=__r.w.cx;
  __r.h.ah=1;
  __r.w.cx=0x2020;
  int386(0x10,&__r,&__r);

  __r.x.edi=(int)X;
  __s.es=((fp*)&D)->seg;
  __r.h.ah=0x1b;
  __r.w.bx=0;
  int386x(0x10,&__r,&__r,&__s);
  res=__r.h.al;

  if(res!=27 || OldScr==7){
    WIDTH=80; HEIGHT=25;
    switch(OldScr){
    case 2:
    case 3:
      break;
    case 7:
      kkk.off=0xb0000;
      Editor.attrs=MonoAttrs;
      break;
    default:
      __r.w.ax=0x3;
      int386(0x10,&__r,&__r);
    }
  }else{
    WIDTH=*(short*)(X+5);
    HEIGHT=X[0x22];
  }
  VMem=*(unsigned short far **)&kkk;
}
//&>>&2 0 0 16
#else
//&<<&Borland+DOS version
mmm_Screen::mmm_Screen(){
  unsigned char X[64];
  unsigned char far *D=X;
  need=1;
  char res;
  struct fp{
    int off;
    short seg;
  }kkk;
  kkk.off=0; kkk.seg=0xb800;
  OldCurs=0;

  union REGS __r;
  __r.h.ah=0xF;
  int86(0x10,&__r,&__r);
  OldScr=__r.h.al;

  __r.h.ah=3;
  __r.h.bh=0;
  int86(0x10,&__r,&__r);
  OldCl=__r.x.cx;
  __r.h.ah=1;
  __r.x.cx=0x2020;
  int86(0x10,&__r,&__r);

  struct SREGS __s;
  __r.x.di=(int)X;
  __s.es=((fp*)&D)->seg;
  __r.h.ah=0x1b;
  __r.x.bx=0;
  int86x(0x10,&__r,&__r,&__s);
  res=__r.h.al;

  if(res!=27 || OldScr==7){
    WIDTH=80; HEIGHT=25;
    switch(OldScr){
    case 2:
    case 3:
      break;
    case 7:
      kkk.seg=0xb000;
      Editor.attrs=MonoAttrs;
      break;
    default:
      __r.x.ax=0x3;
      int86(0x10,&__r,&__r);
    }
  }else{
    WIDTH=*(short*)(X+5);
    HEIGHT=X[0x22];
  }
  VMem=*(unsigned short far **)&kkk;
}
//&>>&0 0 0 16
#endif
//&>>&3 0 3 0
//&<<&mmm_Screen::~mmm_Screen();
#ifdef __386__
//&<<&Watcom+Pharlap version
mmm_Screen::~mmm_Screen(){
  union REGS __r;
  __r.h.al=OldScr;
  __r.h.ah=0;
  int386(0x10,&__r,&__r);
  __r.w.cx=OldCl;
  __r.h.ah=1;
  int386(0x10,&__r,&__r);
}
//&>>&0 0 0 17
#else
//&<<&Borland+DOS version
mmm_Screen::~mmm_Screen(){
  union REGS __r;
  __r.h.al=OldScr;
  __r.h.ah=0;
  int86(0x10,&__r,&__r);
  __r.x.cx=OldCl;
  __r.h.ah=1;
  int86(0x10,&__r,&__r);
}
//&>>&0 0 0 17
#endif
//&>>&3 0 3 0
//&<<&void mmm_Screen::ClrCursor();
void mmm_Screen::ClrCursor(){
   if(OldCurs) *OldCurs=OldAttr;
   OldCurs=0;
}
//&>>&0 0 0 F
//&<<&void mmm_Screen::SetCursor(int x,int y,int attr);
void mmm_Screen::SetCursor(int x,int y,int attr){
   if(OldCurs) ClrCursor();
   OldCurs=(char far *)(VMem+WIDTH*y+x)+1;
   OldAttr=*OldCurs;
   *OldCurs=attr;
}
//&>>&0 0 0 F

//&<<&void DrawLine(char *Str, int PosY, char Attr,int slen);
void DrawLine(char *Str, int PosY, char Attr,int slen){
   unsigned short far *vmem=mmm_screen.Vmem()+PosY*mmm_screen.GetW();
   for(int i=0 ; i<mmm_screen.GetW(); i++) {
      vmem[i]=(((int)Attr)<<8)+(unsigned int)(unsigned char)*Str;
      if(*Str) ++Str;
   }
}
//&>>&2 0 2 17
void SetTitle(char *,char *){}

//&<<&mmm_KeyBoard::mmm_KeyBoard();
mmm_KeyBoard::mmm_KeyBoard(){
  code=0x666;
  OldInt9=_dos_getvect(9);
  _dos_setvect(9,NewInt9);
  InitKeyboardLayout();
  AltCase=InitDefaultAltCase();
}
//&>>&4 0 4 6
//&<<&mmm_KeyBoard::~mmm_KeyBoard();
mmm_KeyBoard::~mmm_KeyBoard(){
  _dos_setvect(9,OldInt9);
}

//&>>&0 0 0 1B
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
//      i>='Ä' && i<='è' ? i+('†'-'Ä') :
//      i>='ê' && i<='ü' ? i+('‡'-'ê') :
//      i>='†' && i<='Ø' ? i-('†'-'Ä') :
//      i>='‡' && i<='Ô' ? i-('‡'-'ê') :
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
//&<<&static void interrupt mmm_KeyBoard::NewInt9(...);
void interrupt mmm_KeyBoard::NewInt9(IntArg){
  unsigned char k=inp(0x60);
  int l=inp(0x61); outp(0x61,l|0x80); outp(0x61,l); outp(0x20,0x20);
  mmm_KBD.AddScan(k);
}
//&>>&3 0 3 9
//&<<&int mmm_KeyBoard::GetScan();
int mmm_KeyBoard::GetScan(){
  if(bbuf==ebuf) View();
  while(bbuf==ebuf) ;
  return keybuf[bbuf++];
}
//&>>&0 0 0 10
//&<<&void MkScan(int scancode);             

int cvE0(int sc){
  switch(sc){
    case 0x1C: return 0x61;     // R-[Enter]
    case 0x1D: return 0x62;     // R-CTRL
    case 0x35: return 0x63;     // [/]
    case 0x37: return 0x64;     // CTRL-PrintScreen
    case 0x38: return 0x65;     // R-ALT
    case 0x46: return 0x66;     // PAUSE
    case 0x47: return 0x67;     // [HOME]
    case 0x48: return 0x68;     // [Up]
    case 0x49: return 0x69;     // [PgUp]
    case 0x4B: return 0x6A;     // [Left]
    case 0x4D: return 0x6B;     // [Right]
    case 0x4F: return 0x6C;     // [End]
    case 0x50: return 0x6D;     // [Down]
    case 0x51: return 0x6E;     // [PgDn]
    case 0x52: return 0x6F;     // [Ins]
    case 0x53: return 0x70;     // [Del]
  }
  return 0;
}

void setfix(){
  mmm_f_FixShift^=mmm_f_Shift;
  mmm_f_FixAlt^=mmm_f_Alt;
}

void MkScan(int code){
  assert(cur!=0);
  if(code==0xE0){ mmm_f_E0=1; return; }
  if(mmm_f_E0){
    mmm_f_E0=0;
    code=cvE0(code&0x7f)|(code&0x80);
  }

  switch(code){
  case 0x2A: mmm_f_LeftShift=mmm_f_Shift=1; return;
  case 0x1D: mmm_f_LeftCtrl=mmm_f_Ctrl=1; return;
  case 0x38: mmm_f_LeftAlt=mmm_f_Alt=1; return;
  case 0x36: mmm_f_RightShift=mmm_f_Shift=1; return;
  case 0x62: mmm_f_RightCtrl=mmm_f_Ctrl=1; return;
  case 0x65: mmm_f_RightAlt=mmm_f_Alt=1; return;
  case 0x3A: if(mmm_f_Caps==0) setfix(); mmm_f_Caps=1; return;

  case 0xAA: mmm_f_LeftShift=0; mmm_f_Shift=mmm_f_RightShift; return;
  case 0x9D: mmm_f_LeftCtrl=0; mmm_f_Ctrl=mmm_f_RightCtrl; return;
  case 0xB8: mmm_f_LeftAlt=0; mmm_f_Alt=mmm_f_RightAlt; return;
  case 0xB6: mmm_f_RightShift=0; mmm_f_Shift=mmm_f_LeftShift; return;
  case 0xE2: mmm_f_RightCtrl=0; mmm_f_Ctrl=mmm_f_LeftCtrl; return;
  case 0xE5: mmm_f_RightAlt=0; mmm_f_Alt=mmm_f_LeftAlt; return;
  case 0xBA: mmm_f_Caps=0; return;
  }

  Command(code + (mmm_f_Shift<<8) +(mmm_f_Alt<<9)+(mmm_f_Ctrl<<10)+(mmm_f_Caps<<11) );

}
//&>>&20 0 8 8

//&<<&KeyBoard Layouts 

char *mcode=mmm_KBD.keys[0],*acode=mmm_KBD.keys[2];

volatile int   mmm_f_E0=0;
volatile int   mmm_f_LeftShift=0,mmm_f_RightShift=0;
volatile int   mmm_f_LeftCtrl=0,mmm_f_RightCtrl=0;
volatile int   mmm_f_LeftAlt=0,mmm_f_RightAlt=0;
volatile int   mmm_f_Caps=0;
volatile int   mmm_f_FixShift=0,mmm_f_FixAlt=0;
volatile int   mmm_f_Shift=0,mmm_f_Alt=0,mmm_f_Ctrl=0;
//&>>&A 0 A 0

void Beep(){ sound(1760); delay(32); nosound(); delay(2); }

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
//&>>&6 0 6 11

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
    fputs("%COMSPEC%\n",fRunScript);
    fputs(MFileName("mmm.bat @"),fRunScript);
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
    exit(-1);
}
//&>>&1D 0 8 17
void MMMlib_Console    (int ccode){};

//&<<&void File::MkWild();
void File::MkWild(){
  find_t ff;
  char str[80];
  flg=FILE_LIST;

            /* Search for all directories */
  int c=_dos_findfirst("*.*", 0x1f , &ff);
  while(c==0){
    ff.name[12]=0;
    if((ff.attrib & _A_SUBDIR ) && strcmp(ff.name,".")){
      sprintf(str,"%s\\%s",ff.name,buf);
      NewLine(str)->LinkBefore(pos);
    }
    c=_dos_findnext(&ff);
  }

  c=_dos_findfirst(buf, 0x0f , &ff);
  while(c==0){
    ff.name[12]=0;
    sprintf(str,"%-15s%10ld  %02d-%02d-%04d  %02d:%02d:%02d  %c%c%c%c",
      ff.name, ff.size,
      ff.wr_date&31, (ff.wr_date>>5)&15, ((ff.wr_date>>9)&127)+1980,
      (ff.wr_time>>11)&15, (ff.wr_time>>5)&63,  (ff.wr_time&31)*2,
      ff.attrib&1 ? 'r' : '.',
      ff.attrib&2 ? 'h' : '.',
      ff.attrib&4 ? 's' : '.',
      ff.attrib&32 ? 'a' : '.');
      NewLine(str)->LinkBefore(pos);
    c=_dos_findnext(&ff);
  }

  while(pos->prev) pos=pos->prev;
}
//&>>&0 0 0 1
///// mmm_dos.err mmm_dos.err mmm_dos.err mmm_dos.err mmm_dos.err
//&>>&1C 0 1A B
