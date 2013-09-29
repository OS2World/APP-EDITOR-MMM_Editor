/**********************************************
*   Linux CPP file for MMMX Editor            *
*   Contains Linux  specific functions        *
*    ( Tested on i386 RedHat Linux 3.0+ )     *
***********************************************/

#include "mmm_lnx.h"

int con_fd;       //// console descriptor, common for mmm_Screen, mmm_KBD

const  INTENSCOL=1;
const VOIDCOL=21;
extern int ed_gflag;
#define ED_G_KEYB  0x02

//&<<&int nonprintable(int c) {
int nonprintable(int c) {
   return(c=='\033' || c=='\n' || c=='\r' || c=='\t');
}
//&>>&3 0 3 1
//&<<&void mmm_Screen::setatr(int atr) {
void mmm_Screen::setatr(int atr) {
   char buf[30];
   write(con_fd,buf,sprintf(buf,"[%d;%d;%dm",(atr&7)+30,((atr&0x70)>>4)+40,(atr&0x8)?INTENSCOL:VOIDCOL));
   curatr=atr;
}
//&>>&0 0 0 F
//&<<&void mmm_Screen::Line(char *str,int len,int x,int y) {
void mmm_Screen::Line(char *str,int len,int x,int y) {
   static char buf[0x100];
   static int p;
   int i,atr;
   if(x<0) {len+=x;str-=x*2;x=0;}
   if(y<0 || y>=HEIGHT || x>=WIDTH || len<=0) return;
   p=0;
   SetCursor(x,y,70);
#ifdef BAD_LAST_SCREEN_POSITION
   if(y==HEIGHT-1 && x+len==WIDTH) len--;
#endif
   if(x+len>=WIDTH) len=WIDTH-x;
   for(i=0;i<len;i++) {
      v_screen[y*WIDTH*2+(x+i)*2]=str[i*2];
      v_screen[y*WIDTH*2+(x+i)*2+1]=str[i*2+1];
      atr=str[i*2+1];
      if(nonprintable(str[i*2])) atr=(atr&0xf0)|9;
      if(atr!=curatr) {
         if(p) {write(con_fd,buf,p);p=0;}
         setatr(atr);
      }
      if(!nonprintable(str[i*2])) buf[p++]=str[i*2];
      else buf[p++]=str[i*2]+0100;
   }
   if(p) write(con_fd,buf,p);
}
//&>>&E 0 E 8

//&<<&mmm_Screen::mmm_Screen(){
mmm_Screen::mmm_Screen(){
   struct winsize s;
   int r;
   int i,j;
   need=1;
   con_fd=open("/dev/tty",O_RDWR);
   if(con_fd<=0) {printf("mmm_Screen::mmm_Screen: Error opening console\n");exit(1);}
   r=ioctl(con_fd,TIOCGWINSZ,(long)&s);
   WIDTH=s.ws_col;
   HEIGHT=s.ws_row;
   v_screen=new char [WIDTH*HEIGHT*2];
   for(j=0;j<HEIGHT;j++)
      for(i=0;i<WIDTH;i++) {
         v_screen[j*WIDTH*2+i*2]=' ';
         v_screen[j*WIDTH*2+i*2+1]=7;
      }
   }
//&>>&E 0 E B
//&<<&mmm_Screen::~mmm_Screen(){
mmm_Screen::~mmm_Screen(){
//&<<&#ifdef _ENABLE_LOGGING_
#ifdef _ENABLE_LOGGING_
   DoLog("mmm_Screen::~mmm_Screen()  {\n");

   DoLog("    DrawLine("",HEIGHT-1 {\n");
   DrawLine("",HEIGHT-1,Editor.TextAttr,WIDTH-3);
   DoLog("        }\n");

   DoLog("    SetCursor {\n");
   SetCursor(0,HEIGHT-1,Editor.TextAttr);
   DoLog("        }\n");

   DoLog("    close(con_fd);  {\n");
   close(con_fd);
   DoLog("        }\n");

   DoLog("    }\n");
//&>>&1 0 1 21
//&<<&#else
#else
   DrawLine("",HEIGHT-1,Editor.TextAttr,WIDTH-3);
   SetCursor(0,HEIGHT-1,Editor.TextAttr);
   close(con_fd);
//&>>&3 0 3 1
#endif

   }
//&>>&1 0 1 17
//&<<&void mmm_Screen::SetCursor(int x,int y,int attr) {
void mmm_Screen::SetCursor(int x,int y,int attr) {
   char buf[0x20];
   write(con_fd,buf,sprintf(buf,"[%d;%dH",y+1,x+1));
}
//&>>&0 0 0 F
void mmm_Screen::ClrCursor(){}
//&<<&void DrawLine(char *Str, int PosY, char Attr,int slen){
void DrawLine(char *Str, int PosY, char Attr,int slen){
   static char *PRTLINE=0;
   if(!PRTLINE)PRTLINE=new char[mmm_screen.GetW()*2+1];
   for(int i=0 ; i<mmm_screen.GetW(); i++) {
      PRTLINE[i*2]=*Str==0?' ':(char)*Str;
      PRTLINE[i*2+1]=(char)Attr;
      if(*Str) ++Str;
      }
   mmm_screen.Line( PRTLINE, mmm_screen.GetW() , 0, PosY);
}
//&>>&8 0 8 27
void SetTitle(char *,char *){}

//&<<&void SegmentViolationHandler(int a) {
void SegmentViolationHandler(int a) {
   int r;
   puts("Now In SegmentViolationHandler(...)\n");
   r=ioctl(con_fd,KDSKBMODE,mmm_KBD.om);
   if(r<0) puts("ioctl failed\n");
   r=tcsetattr(con_fd,TCSANOW,&(mmm_KBD.t1));
   if(r<0) puts("tcsetattr failed\n");
   _exit(1);
}
//&>>&5 0 5 27
//&<<&mmm_KeyBoard::mmm_KeyBoard(){
//&<<&void falarm(int a) {
void falarm(int a) {
   signal(SIGALRM,falarm);
   alarm(1);
}
//&>>&4 0 4 0
mmm_KeyBoard::mmm_KeyBoard(){
   struct termios t2;
   int r;
   r=tcgetattr(con_fd,&t1);
   if(r<0) {printf("E3 %d\n",r);exit(1);}
   r=tcgetattr(con_fd,&t2);
   if(r<0) {printf("E4 %d\n",r);exit(1);}
   t2.c_iflag=0;
   t2.c_lflag&=~(ECHO|ICANON|ISIG);
   t2.c_cc[VMIN]=1;
   t2.c_cc[VTIME]=0x10;
   r=tcsetattr(con_fd,TCSANOW,&t2);
   if(r<0) {printf("E5 %d\n",r);exit(1);}
   r=ioctl(con_fd,KDGKBMODE,&om);
   if(r<0) {printf("E1 %d\n",r);}
   r=ioctl(con_fd,KDSKBMODE,K_RAW);
   if(r<0) {printf("E2 %d\n",r);}
  /////////// ed_keyget=mykeyget;
   signal(SIGALRM,falarm);
   alarm(1);
   signal(SIGSEGV,SegmentViolationHandler);
   signal(SIGKILL ,SegmentViolationHandler );
   signal(SIGQUIT ,SegmentViolationHandler );
   signal(SIGTERM ,SegmentViolationHandler );
   InitKeyboardLayout();
   AltCase=InitDefaultAltCase();
}
//&>>&19 0 17 7
//&<<&mmm_KeyBoard::~mmm_KeyBoard(){
mmm_KeyBoard::~mmm_KeyBoard(){
//&<<&   #ifdef _ENABLE_LOGGING_
   #ifdef _ENABLE_LOGGING_
       DoLog("mmm_KeyBoard::~mmm_KeyBoard() {\n");
   #endif
//&>>&1 0 1 29
   int r;
   r=ioctl(con_fd,KDSKBMODE,om);
   r=tcsetattr(con_fd,TCSANOW,&t1);
   if(r<0) {printf("E6 %d\n",r);}
//&<<&   #ifdef _ENABLE_LOGGING_
   #ifdef _ENABLE_LOGGING_
       DoLog("    }\n");
   #endif
//&>>&1 0 1 7
}
//&>>&1 0 1 1B
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
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("mmm_KeyBoard::SetACode(%d) {\n",n);
    #endif
//&>>&1 0 1 1B
    acode=mmm_KBD.keys[n];
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 4
    }
//&>>&2 0 2 11
//&<<&void mmm_KeyBoard::ChangeConsole(int num)
void mmm_KeyBoard::ChangeConsole(int num)
{
   int r;
   r=ioctl(con_fd,VT_ACTIVATE,num+1);
   if(r<0) {Beep();}
}
//&>>&0 0 0 11
//&<<&mmm_KeyBoard::GetScan() {
mmm_KeyBoard::GetScan() {
   unsigned char c;
   int cd=0;
   ioctl(con_fd,TIOCINQ,&cd);
   if(cd==0) View();   // Redraw screen only if system KB-buffer is empty
   read(con_fd,&c,1);  // get next scancode from console
   return c;
}
//&>>&0 0 0 C
//&<<&void MkScan(int scancode);             

int cvE0(int sc){
  switch(sc){
    case 0x1C: return 0x61;     // R-[Enter]
    case 0x1D: return 0x62;     // R-CTRL
    case 0x35: return 0x63;     // [/]
    case 0x37: return 0x64;     // CTRL-Printmmm_Screen
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
//&>>&35 0 17 44

//&<<&Keyboard Layouts 

char *mcode=mmm_KBD.keys[0],*acode=mmm_KBD.keys[2];

volatile int   mmm_f_E0=0;
volatile int   mmm_f_LeftShift=0,mmm_f_RightShift=0;
volatile int   mmm_f_LeftCtrl=0,mmm_f_RightCtrl=0;
volatile int   mmm_f_LeftAlt=0,mmm_f_RightAlt=0;
volatile int   mmm_f_Caps=0;
volatile int   mmm_f_FixShift=0,mmm_f_FixAlt=0;
volatile int   mmm_f_Shift=0,mmm_f_Alt=0,mmm_f_Ctrl=0;
//&>>&3 0 3 0

void Beep(){ printf("%c",7); fflush(stdout); }

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
  if(lcd>3 && cd[lcd-1]=='/') cd[--lcd]=0;
  fprintf(f,"cd %s\n",cd);
  delete cd;
}
//&>>&4 0 4 1

void __EXIT(){
//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("void __EXIT(){ \n");
  #endif
//&>>&1 0 1 6
    char *s;
    FILE *fRunScript,*filelist;

    s=MFileName(EXECUTER_FILENAME);
    fRunScript=fopen(s,"w"); MemTest(fRunScript!=0);
    delete s;

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

    chmod(MFileName(EXECUTER_FILENAME), 0755 );
//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("    } exit(-1)...\n");
  #endif
//&>>&1 0 1 6
    system(MFileName(EXECUTER_FILENAME));
    exit(-1);
}
///// mmm_os2.err mmm_os2.err mmm_os2.err mmm_os2.err mmm_os2.err
//&>>&1E 0 F 0
//&<<&void MMMlib_Console    (int ccode)
void MMMlib_Console    (int ccode) {   // digits '1', '2', .. are fixed now!!!!!!!
    int ca;
    ca=( ccode & 0x0f ) - 2;  /* 0x702->0 , 0x703->1 .... */
    if(ca>0 && ca<10) mmm_KBD.ChangeConsole(ca);
    }
//&>>&3 0 3 1D

//&<<&void File::MkWild();
void File::MkWild(){
  char str[0x100];
  DIR *cdir;
  struct dirent *dp;
  struct stat fI;
//&<<&  cdir=opendir("."); /////////read directories
  cdir=opendir(".");
  if(cdir==NULL){ NewLine("here must be directory\nbut sorry....")->LinkBefore(pos); }
  dp=readdir(cdir);
  while(dp!=0){
    stat(dp->d_name,&fI);
    if( (fI.st_mode&S_IFDIR) && strcmp(dp->d_name,".") ) {
        sprintf(str,"%s/%s",dp->d_name,buf);
        NewLine(str)->LinkBefore(pos);
        }
    dp=readdir(cdir);
    }
//&>>&0 0 0 0
//&<<&  cdir=opendir("."); ///////// read files
  cdir=opendir(".");
  if(cdir==NULL){ NewLine("here must be directory\nbut sorry....")->LinkBefore(pos); }
  dp=readdir(cdir);
  while(dp!=0){
    stat(dp->d_name,&fI);
    if(!(fI.st_mode & S_IFDIR)){
        sprintf(str,"%-25s %8ld <%2d> %02d:%02d:%02d",dp->d_name,
                 fI.st_size, fI.st_nlink,
                 (fI.st_mtime>>11)&15, (fI.st_mtime>>5)&63,  (fI.st_mtime&31)*2 );
        NewLine(str)->LinkBefore(pos);
        }
    dp=readdir(cdir);
    }
//&>>&D 0 D C
  while(pos->prev) pos=pos->prev;
}
//&>>&6 0 6 7

//&>>&24 0 17 E
