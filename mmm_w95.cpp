/**********************************************
*   WIN95 CPP file for MMMX Editor            *
*   Contains WIN95 specific functions         *
*     ( NT is untested )                      *
***********************************************/

#include "mmm_w95.h"
#include <io.h>
#include <time.h>

static HANDLE _confh,_coninpfh;


//&<<&void _dos_setdrive(unsigned int n,unsigned int *t);
void _dos_setdrive(unsigned int n,unsigned int *t){
  _chdrive(n);
}
//&>>&0 0 0 0
//&<<&void _dos_getdrive(unsigned int *res);
void _dos_getdrive(unsigned int *res){
  *res=_getdrive();
}
//&>>&0 0 0 0

//&<<&mmm_Screen::mmm_Screen();
mmm_Screen::mmm_Screen(){
  HEIGHT=45;
  Size.X=100;

#if 1
  scr=new CHAR_INFO[Size.X];
  strs=new char*[HEIGHT];
  lens=new int[HEIGHT];
#else
  scr=new char[Size.X];
#endif

  attrs=new WORD[HEIGHT];
  for(int i=0;i<HEIGHT;i++){ attrs[i]=0; strs[i]=0; lens[i]=0; }

  Rect.Left=0;
  Rect.Right=Size.X-1;
  Rect.Bottom=HEIGHT-1;
  Zero.X=Zero.Y=0;

  Init();
}
void mmm_Screen::Init(){
  _confh=GetStdHandle(STD_OUTPUT_HANDLE);
  _coninpfh=GetStdHandle(STD_INPUT_HANDLE);
  Size.Y=HEIGHT;
  SetConsoleScreenBufferSize(_confh,Size);
  Size.Y=1;
  CONSOLE_CURSOR_INFO p;
  GetConsoleCursorInfo(_confh,&p);
  p.bVisible=0;
  SetConsoleCursorInfo(_confh,&p);
}
//&>>&17 0 16 16
//&<<&mmm_Screen::~mmm_Screen();
mmm_Screen::~mmm_Screen(){
   delete scr;
}
//&>>&0 0 0 17
//&<<&void mmm_Screen::ClrCursor();
void mmm_Screen::ClrCursor(){
  DWORD tmp;
  WriteConsoleOutputAttribute(_confh,&CCurAttr,1,OldCur,&tmp);
}
//&>>&1 0 1 10
//&<<&void mmm_Screen::SetCursor(int x,int y,WORD attr);
void mmm_Screen::SetCursor(int x,int y,WORD attr){
  OldCur.X=x; OldCur.Y=y;
  CCurAttr=attrs[OldCur.Y];
  if(OldCur.X<lens[OldCur.Y] && byte(strs[OldCur.Y][OldCur.X])>=0xC0){ attr^=0x40; CCurAttr^=0x40; }
  DWORD tmp;
  WriteConsoleOutputAttribute(_confh,&attr,1,OldCur,&tmp);
}
//&>>&0 0 0 13
//&<<&void DrawLine(char *Str, int PosY, char Attr,int slen);
void DrawLine(char *Str, int PosY, char Attr,int slen){
  mmm_screen.DrawLine(Str,PosY,Attr,slen);
}

char const *const RUS_ALIAS=
"ABWGDEVZIJKLMNOPRSTUFHC^[]?YX\\@Qabwgdevzijklmnoprstufhc~{}_yx|`q";

void mmm_Screen::DrawLine(char *Str, int PosY, char Attr,int slen){
#if 0
  char *t=scr;
  for(int i=0;i<Size.X && *Str;i++){
    *t++=*Str++;
  }
  for(;i<Size.X;i++) *t++=' ';
  Zero.Y=PosY;
  DWORD nc;
  WriteConsoleOutputCharacter(_confh,scr,Size.X,Zero,&nc);
  if(attrs[PosY]!=Attr){
    attrs[PosY]=Attr;
    FillConsoleOutputAttribute(_confh,Attr,Size.X,Zero,&nc);
  }
  mmm_KBD.GetEvent(0);
#else
  attrs[PosY]=Attr;
  CHAR_INFO *t=scr;
  strs[PosY]=Str;
  for(int i=0;i<Size.X && *Str;i++){
    char c=*Str++;
    if(byte(c)>=0xC0){
      t->Char.AsciiChar=RUS_ALIAS[byte(c)-0xC0];
      t->Attributes=Attr^0x40;
 }else{
      t->Char.AsciiChar=c;
      t->Attributes=Attr;
    }
    t++;
  }
  lens[PosY]=i;
  for(;i<Size.X;i++){
    t->Char.AsciiChar=' ';
    t->Attributes=Attr;
    t++;
  }
  Rect.Top=Rect.Bottom=PosY;
  WriteConsoleOutput(_confh,scr,Size,Zero,&Rect);
#endif
}
//&>>&15 0 14 9
//&<<&void SetTitle(char *,char *name){
void SetTitle(char *,char *name){
  char tt[512];
  strcpy(tt,"MMM95 - ");
  strcat(tt,name);
  SetConsoleTitle(tt);
}
//&>>&0 0 0 0

//&<<&KeyRes &mmm_KeyBoard::GetScan();
KeyRes &mmm_KeyBoard::GetScan(){
  if(bch==ech){ View(); GetEvent(1); }
  KeyRes &k=buf[bch++];
  bch&=0xff;
  return k;
}

void mmm_KeyBoard::GetEvent(int f){
  INPUT_RECORD t;
  DWORD l;
  for(;;){
    GetNumberOfConsoleInputEvents(_coninpfh,&l);
//    PeekConsoleInput(_coninpfh,&t,1,&l);
    if(l==0 && (f==0 || bch!=ech)) return;
    ReadConsoleInput(_coninpfh,&t,1,&l);
    if(l==0 || t.EventType!=KEY_EVENT) continue;
    KEY_EVENT_RECORD &k=t.Event.KeyEvent;
    if(((ech+1)&0xff)==bch) return;
    KeyRes &kr=buf[ech++]; ech&=0xff;
    kr.keydown=k.bKeyDown;
    kr.scode=k.wVirtualScanCode;
    kr.ctrl=k.dwControlKeyState;
  }
}
//&>>&7 0 7 11
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

void MkScan(KeyRes &kres){
  assert(cur!=0);
  int code=kres.scode;
  if(kres.ctrl&ENHANCED_KEY) code=cvE0(code);
  if(code==0x3A){
    if(kres.keydown){
      if(mmm_f_Caps==0) setfix(); mmm_f_Caps=1;
    }else mmm_f_Caps=0;
    return;
  }

  mmm_f_Ctrl=kres.ctrl&(RIGHT_CTRL_PRESSED|LEFT_CTRL_PRESSED) ? 1 : 0;
  mmm_f_Alt=kres.ctrl&(RIGHT_ALT_PRESSED|LEFT_ALT_PRESSED) ? 1 : 0;
  mmm_f_Shift=kres.ctrl&(SHIFT_PRESSED) ? 1 : 0;
  int fsh=mmm_f_FixShift^mmm_f_Shift;
  int fal=mmm_f_FixAlt^mmm_f_Alt;

  if(kres.keydown==0) return;
  Command(code + (mmm_f_Shift<<8) +(mmm_f_Alt<<9)+(mmm_f_Ctrl<<10)+(mmm_f_Caps<<11) );
}
//&>>&2B 0 17 16

//&<<&mmm_KeyBoard::mmm_KeyBoard()
mmm_KeyBoard::mmm_KeyBoard(){
    buf=new KeyRes[0x100];
    InitKeyboardLayout();
    AltCase=InitDefaultAltCase();
    }
//&>>&2 0 2 8
//&<<&void mmm_KeyBoard::InitKeyBoardLayout();
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
      i>=byte('A') && i<=byte('Z') ? i+('a'-'A') :
      i>=byte('a') && i<=byte('z') ? i-('a'-'A') :
//      i>=byte('À') && i<=byte('ß') ? i+('à'-'À') :
//      i>=byte('à') && i<=byte('ÿ') ? i-('à'-'À') :
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
//&<<&KeyBoard Layouts 

char *mcode=mmm_KBD.keys[0],*acode=mmm_KBD.keys[2];

volatile int   mmm_mmm_f_E0=0;
volatile int   mmm_f_LeftShift=0,mmm_f_RightShift=0;
volatile int   mmm_f_LeftCtrl=0,mmm_f_RightCtrl=0;
volatile int   mmm_f_LeftAlt=0,mmm_f_RightAlt=0;
volatile int   mmm_f_Caps=0;
volatile int   mmm_f_FixShift=0,mmm_f_FixAlt=0;
volatile int   mmm_f_Shift=0,mmm_f_Alt=0,mmm_f_Ctrl=0;
//&>>&3 0 3 1B

//&<<&void __EXIT();
/*
   EXECUTER_FILENAME=

   commands
*/

void __EXIT(){
  int n=1;

  char *s=MFileName(EXECUTER_FILENAME);
  FILE *f=fopen(s,"w"); MemTest(f!=0);
  fputs("@echo off\ncls\n",f);

  while(mmm_LineClipboard && mmm_LineClipboard->prev)
      mmm_LineClipboard=mmm_LineClipboard->prev;
  Line *mmm_LineClipboard0=mmm_LineClipboard;
  while(mmm_LineClipboard && mmm_LineClipboard->next){
    mmm_LineClipboard->Write(f,FILE_ASCII);
    mmm_LineClipboard=mmm_LineClipboard->next;
  }
  mmm_LineClipboard=mmm_LineClipboard0;

  fclose(f);
  FreeConsole();
  system(s);
  delete s;
  AllocConsole();
  mmm_screen.Init();
  Redr();
}
//&>>&1E 0 1C 6
void MMMlib_Console    (int ccode){};
void Beep(){} // cputs("\007"); }

//&<<&void File::MkWild();
void File::MkWild(){
  flg=FILE_LIST;

  _finddata_t ff;
  char str[512];

  long id=_findfirst("*.*",&ff);
  if(id!=-1){
    do{
      for(char *s=ff.name;*s;s++) if(*s==' ') break;
      if(ff.attrib&0x10){
        if(strcmp(ff.name,".")){
          sprintf(str,*s ? "\"%s/%s\"" : "%s/%s",ff.name,buf);
          NewLine(str)->LinkBefore(pos);
        }
      }
    }while(_findnext(id,&ff)==0);
  }
  _findclose(id);

  id=_findfirst(buf,&ff);
  if(id!=-1){
    do{
      for(char *s=ff.name;*s;s++) if(*s==' ') break;
      if(!(ff.attrib&0x10)){
        memset(str,' ',32);
        sprintf(str,*s ? "\"%s\"" : "%s", ff.name);
        int l=strlen(str);
        if(l<32){ str[l]=' '; l=32; }
        sprintf(str+l,"%10ld %s %c%c%c%c",
                ff.size,
                ctime(&(ff.time_write)),
                ff.attrib&1 ? 'r' : '.',
                ff.attrib&2 ? 'h' : '.',
                ff.attrib&4 ? 's' : '.',
                ff.attrib&32 ? 'a' : '.');
        char &u=str[strlen(str)-6];
        if(u=='\n') u=' ';
        NewLine(str)->LinkBefore(pos);
      }
    }while(_findnext(id,&ff)==0);
  }
  _findclose(id);

  while(pos->prev) pos=pos->prev;
}
//&>>&0 0 0 6
//      f:\pub\*.*
//&>>&12 0 12 E
