/**********************************************
***********************************************
***  Base Editor file, contains text manip. ***
***                 stuff                   ***
***********************************************
**********************************************/

//&<<&MMM headers
#include "mmmgrep.h"
#include "mmm_comm.h"

#ifdef __DOS__
    #include "mmm_dos.h"
#endif
#ifdef WIN32
    #include "mmm_w95.h"
#endif
#ifdef __OS2__
    #include "mmm_os2.h"
#endif
#ifdef __linux__
    #include "mmm_lnx.h"
#endif

//&>>&0 0 0 11

//&<<&Forward_declarations
//&<<&#ifdef _ENABLE_LOGGING_
#ifdef _ENABLE_LOGGING_
void DoLog(char *format, ... )
{
FILE *lf=fopen("log.","a+");
if(lf==0) exit(0);

va_list arglist;
va_start( arglist, format );
vfprintf(lf, format, arglist );
va_end( arglist );

fclose(lf);
}
#endif
//&>>&1 0 1 5
void putl(char *s,FILE *f){
  fputs(s,f); putc('\n',f);
}
void putl(char *s1,char *s2,char *s3,FILE *f){
  fputs(s1,f); fputs(s2,f); fputs(s3,f); putc('\n',f);
}
//void MkScan(int scancode);
//&>>&7 0 7 0
//&<<&Constants and variables
Chain *ConstantPage=0;
Chain *CurrentPage=0;

Fold *SearchFold=0;

Fold *cur=0;           // Current fold

Line *mmm_LineClipboard=0;    // Line clipboard
Fold *fLineClipboard=0;

unsigned long FileLinesCounter;  // very strange variable....temporary.....

int lHead=0;       // number of blank strings on the top of screen (for 2nd statusline)

int MarkedBlockLength;    // Number of lines in buffer
MarkedLine *MarkedBlock;  // pointer to buffer with ML-s
                          // it would be better to include it into Editor class,
                          // but mmmx.exe must use <= 64k in DOS (optimization)

char *comment;         // comment to be applied to file
int lcomment;          // length of current comment
//&>>&8 0 8 0

//&<<&class Line;
//&<<&Line::Line(char *s);
Line::Line(char *s):prev(0),next(0),fchg(0),buf(0),lbuf(0),marked(0){
  if(s){
    Realloc(strlen(s));
    strcpy(buf,s);
  }
}
//&>>&0 0 0 10
//&<<&Line::~Line();
Line::~Line(){
  UnLink();
  delete buf;
}
//&>>&2 0 2 9
//&<<&void Line::UnLink();
void Line::UnLink(){
  if(prev) prev->next=next;
  if(next) next->prev=prev;
}
//&>>&1 0 1 0
//&<<&Line *Line::LinkBefore(Line *f);
Line *Line::LinkBefore(Line *f){         // this is unlinked
  prev=f->prev; next=f;
  if(prev) prev->next=this;
  f->prev=this;
  return this;
}
//&>>&1 0 1 0
//&<<&Line *Line::Copy(int cln){
Line *Line::Copy(int cln){
  Line *x=NewLine(buf,cln?linenumber:0);
  x->type=type;
  x->fchg=LINE_NEW;
  return x;
}
//&>>&0 0 0 1A
//&<<&void Line::Realloc(int x);
void Line::Realloc(int x){
  if(x<lbuf) return;
  int lb=x+(buf ? 20 : 1);
  char *m=new char[lb]; MemTest(m!=0);
  if(lbuf) memcpy(m,buf,lbuf);
  while(lbuf<lb) m[lbuf++]=0;
  delete buf; buf=m;
}
//&>>&3 0 3 14
//&<<&void Line::Write(FILE *f,int);
void Line::Write(FILE *f,int){
  while(lbuf){
    lbuf--; if(buf[lbuf]==' ') buf[lbuf]=0;
    if(buf[lbuf]) break;
  }
  putl(buf,f);
}
//&>>&3 0 3 12

//&<<&void Line::InsChar(int cx);
void Line::InsChar(int cx){
  int i;
  if(cx>=lbuf || buf[cx]==0) return;
  if(lbuf<2 || buf[lbuf-2]) Realloc(lbuf+1);
  for(i=lbuf-1;i>cx;i--) buf[i]=buf[i-1];
  buf[cx]=' ';
  fchg|=LINE_CHG;
  Redr(marked?REDRAW_WHOLE_SCREEN:REDRAW_CURRENT_LINE);
}
//&>>&0 0 0 7
//&<<&void Line::DelChar(int cx);
void Line::DelChar(int cx){
  if(cx>=lbuf || buf[cx]==0) return;
  do{ buf[cx]=buf[cx+1]; cx++; }while(buf[cx]);
  fchg|=LINE_CHG;
  Redr(marked?REDRAW_WHOLE_SCREEN:REDRAW_CURRENT_LINE);
}
//&>>&5 0 5 17
//&<<&void Line::SetChar(int cx,char c);
void Line::SetChar(int cx,char c){
  int i;
  if((cx>=lbuf || buf[cx]==0) && c==' ') return;
  Realloc(cx+2);
  if(buf[cx]==0) for(i=cx;i>=0 && buf[i]==0; i--) buf[i]=' ';
  if(buf[cx]!=c){
    fchg|=LINE_CHG;
    Redr(marked?REDRAW_WHOLE_SCREEN:REDRAW_CURRENT_LINE);
    buf[cx]=c;
  }
}
//&>>&7 0 7 0

//&<<&char *Line::GetWord(int cx);
char *Line::GetWord(int cx){
  int i,j;
  if(buf==0 || cx>=lbuf) return 0;
  for(i=cx;--i>=0 && byte(buf[i])>' ';) ;
  i++;
  if(byte(buf[i])<=' ') return 0;
  for(j=i;byte(buf[j])>' ';j++) ;
  char *d=new char[j-i+1]; MemTest(d!=0);
  memcpy(d,buf+i,j-i); d[j-i]=0;
  return d;
}
//&>>&0 0 0 1C
//&<<&char *Line::GetFileName(int cx);
char *Line::GetFileName(int cx){
    int i0,i1;
    if(buf==0) return 0;
    if(cx && cx<lbuf && byte(buf[cx])<=' ') cx--;
    if(cx>=lbuf || byte(buf[cx])<=' ') return 0;

    if(cx>1 && byte(buf[cx+1])<=' ' && (byte(buf[cx])=='\"' || byte(buf[cx])=='>')) cx--;
    i0=cx;
    while(i0>=0 && byte(buf[i0])>' ' && byte(buf[i0])!='\"' && byte(buf[i0])!='<' )i0--;
    i1=i0+1;
    if(i0>=0 &&(byte(buf[i0])=='\"' || byte(buf[i0])=='<')){
        while(byte(buf[i1])!='\"' && byte(buf[i1])!='>' && i1<lbuf )i1++;
    }else{
        while(i1<lbuf && byte(buf[i1])>' ' && byte(buf[i1])!='\"' && byte(buf[i1])!='>')
            i1++;
        if(byte(buf[i1])=='\"' || byte(buf[i1])=='>'){
            while(byte(buf[i0])!='\"' && byte(buf[i0])!='>' && i0>=0 )  i0--;
            }
        }
    i0++;
    while(i0<lbuf && byte(buf[i0])<=' ') i0++;
    while(i1>=0 && byte(buf[i1-1])<=' ') i1--;
    if(i0>=i1) return 0;
    char *d=new char[i1-i0+1]; MemTest(d!=0);
    memcpy(d,buf+i0,i1-i0); d[i1-i0]=0;
    return d;
    }
//&>>&0 0 0 1E

//&<<&Line *NewLine(char *s,unsigned long LinNmb) {
Line *NewLine(char *s,unsigned long LinNmb) {
  Line *l=new Line(s);
  MemTest(l!=0);
  l->linenumber=LinNmb;
  return l;
}
//&>>&3 0 3 5
//&>>&4 0 4 1A
//&<<&class Fold;
//&<<&Fold::~Fold();
Fold::~Fold(){
  while(pos && pos->next) pos=pos->next;
  while(pos && pos->prev) delete pos->prev;
  delete pos;
}
//&>>&3 0 3 0
//&<<&Fold *NewFold(char *buf,unsigned long LinNmb){
Fold *NewFold(char *buf,unsigned long LinNmb){
  Fold *f=new Fold(buf);
  MemTest(f!=0);
  f->linenumber=LinNmb;
  return f;
}
//&>>&4 0 4 0
//&<<&Line *Fold::Copy(int cln){
Line *Fold::Copy(int cln){
  Line *r;
  Fold *f=NewFold(buf,cln?linenumber:0);
  f->type=type;
  Line *rr=f->pos;
  for(r=pos;r->next;r=r->next) r->Copy()->LinkBefore(rr);
  while(rr->prev) rr=rr->prev;
  f->pos=rr;
  for(r=pos->prev;r;r=r->prev) rr=r->Copy()->LinkBefore(rr);
  f->sx=sx; f->cx=cx; f->sy=sy;
  f->fchg=LINE_NEW;
  return f;
  }
//&>>&4 0 4 0
//&<<&void Fold::Write(FILE *f,int flg);
void Fold::Write(FILE *f,int flg){
  if(flg!=FILE_ASCII && buf) putl(comment,"&<<&",buf,f);
  long i=0;
  Line *r=pos;
  if(pos)
    {
    for(r=pos;r->prev;r=r->prev) i++;
    for(;r->next;r=r->next) r->Write(f,flg);
    }
  if(flg!=FILE_ASCII){
    char temp[64];
    sprintf(temp,"%s&>>&%lX %X %X %X\n",comment,i,sx,sy,cx);
    fputs(temp,f);
  }
}
//&>>&1 0 1 0
//&<<&void Fold::Read(FILE *f,int flg);
void Fold::Read(FILE *f,int flg){
  int l;
  while(fgets(templine,INFTY,f)){
    FileLinesCounter++;
    for(l=0;templine[l]!=0;l++) if(templine[l]=='\t') templine[l]=' ';
//    int l=strlen(templine);
    while(l>0 && byte(templine[l-1])<' ') templine[--l]=0;
    if(flg!=FILE_ASCII){
      if(Editor.IsComment(templine,"$<<$") ||
                      Editor.IsComment(templine,"&<<&")){
        Fold *r=NewFold(templine+lcomment+4);
        r->linenumber=FileLinesCounter;
        r->Read(f,flg);
        r->LinkBefore(pos);
        continue;
      }
      if(Editor.IsComment(templine,"$>>$") ||
                      Editor.IsComment(templine,"&>>&")){
        long i=0;
        char *s=templine+lcomment+4;
        i=strtol(s,&s,16);
        sx=int(strtol(s,&s,16));
        sy=int(strtol(s,&s,16));
        cx=int(strtol(s,&s,16));
        pos->linenumber=FileLinesCounter;
        while(pos->prev) pos=pos->prev;
        while(i && pos->next){ i--; pos=pos->next; }
        return;
      }
    }
    NewLine(templine,FileLinesCounter)->LinkBefore(pos);
  }
  while(pos->prev) pos=pos->prev;
}
//&>>&12 0 12 24
//&<<&int Fold::HasChange();
int Fold::HasChange(){
  Line *x;
  for(x=pos;x->prev;x=x->prev) ;
  while(x){
    if(x->fchg) return 1;
    Fold *f=x->Enter();
    if(f && f->HasChange()) return 1;
    x=x->next;
  }
  return 0;
}
//&>>&4 0 0 4
//&<<&void Fold::Draw();
void Fold::Draw(){
  int d=cx-sx;
  int W=mmm_screen.GetW();
  int H=mmm_screen.GetH()-Editor.ShowStatusLineFlag;
  if(d<0 || d>=W){
    if(d<0) sx=cx;
    else sx=cx-W+1;
    d=cx-sx;
    Redr();
  }
  if(sy<lHead){ sy=lHead; Redr(); }
  if(sy>=H){ sy=H-1; Redr(); }
  if(Editor.ShowStatusLineFlag) DrawStatusLine();
  mmm_screen.ClrCursor();
  if(mmm_screen.Need()){
    Line *r; int l;
    switch(mmm_screen.Need()){
//&<<&        case REDRAW_WHOLE_SCREEN:
        case REDRAW_WHOLE_SCREEN:
            if(sx<0) sx=0;
            l=sy;
            for(r=pos;l>lHead && r->prev;r=r->prev) l--;
            if(l>lHead){ sy-=l-lHead; l=lHead; }
            for(;l<H && r;r=r->next,l++){
              if(r->next){
                DrawLine(r->Buf(sx),l,r->GetTextAttr(),r->lbuf );
              }else{
                DrawLine(GetEnd(),l,GetTextAttr(), W );
                }
              }
            while(l<H) DrawLine("",l++,Editor.TextAttr, 0 );
            SetTitle(getcurdir(0),Editor.CurrentFileName);
            break;
//&>>&D 0 D 18
//&<<&        case REDRAW_CURRENT_LINE:
        case REDRAW_CURRENT_LINE:
            if(sx<0) sx=0;
            if(pos && pos->Buf(sx)){
                DrawLine(pos->Buf(sx),sy,pos->GetTextAttr(),pos->lbuf );
                }
            break;
//&>>&4 0 4 0
        }
    mmm_screen.Need()=0;
    }
  mmm_screen.SetCursor(d,sy,pos->next ? pos->GetCurAttr() : GetCurAttr());
}
//&>>&16 0 15 C
//&<<&void Fold::DrawStatusLine();
void Fold::DrawStatusLine(){
   static char StatusLineText[StatusLineLength];
   int W=mmm_screen.GetW();
   int H=mmm_screen.GetH()-Editor.ShowStatusLineFlag;
   static char*SSTR[4]={"SI","SS"};
   char *CD=getcurdir(0);
   sprintf(StatusLineText,                   // ?Would it be better to draw without PRINTF??????
           "%4ld,%-2d %02X  %s %s %s %c%c%c%c  %c %16s %d %d %d %-20s",
           cur->pos->linenumber,cur->cx+1,   // current position
           byte(cur->GetCh()),               // current symbol hex ASCII code
           SSTR[Editor.SearchMode],          // search mode
           (Editor.InsFlag==1)?"ins":"ovr",  // insert or overwrite
           (Editor.IndFlag==1)?"AI":"..",    // autoindent or not
           (mmm_f_Shift)?'s':'.',            // Shift pressed | locked
           (mmm_f_Alt)?'a':'.',              // ALT pressed | locked
           (mmm_f_Ctrl)?'c':'.',             // CTRL pressed
           (mmm_f_Caps)?'C':'.',             // CAPS pressed
           (mmm_f_FixAlt^mmm_f_Alt ? acode : mcode)[16*2+(mmm_f_FixShift^mmm_f_Shift)],  //keyboard layout
           Editor.CurrentFileName ,
           Editor.CurrentDepth,
           Editor.NumberOfPages,
           MarkedBlockLength,
           CD
        );
   DrawLine(StatusLineText, H , Editor.StatusLineAttr , W );
   }
//&>>&11 0 11 18
//&>>&7 0 7 4
//&<<&class File;
//&<<&int WildCard(char *n);
int WildCard(char *n){
  while(*n){ if(*n=='?' || *n=='*') return 1; n++; }
  return 0;
}
//&>>&0 0 0 11
//&<<&Fold *File::Exit();
Fold *File::Exit(){
  Fold *ret=top;
  if(flg!=FILE_LIST && HasChange()){
    SaveSetDrive(CurDev);
    SaveChDir(CurDir);
    delete CurDir;
    FILE *f=fopen(buf,"w");
    if(f==0){
        Beep();
        if(buf[0]!='_')buf[0]='_';
        else buf[0]='a';
        f=fopen(buf,"w");
        }
    if(f){
      char *_buf=buf; buf=0;
      Editor.SetComment(_buf);
      Write(f,flg);
      fclose(f);
      buf=_buf;
    }
  }
  delete this;
  return ret;
}
//&>>&0 0 0 0
//&<<&char *File::FileName();
char *File::FileName(){
  char *x=new char[5+strlen(CurDir)+1+strlen(buf)+1]; MemTest(x!=0);
  char *xx=x;
  if(flg!=FILE_FOLD){
    *xx++='-';
    *xx++=flg==FILE_LIST ? 'l' : 'a';
    *xx++=' ';
  }
  *xx++='@'+CurDev;
  *xx++=':';
  strcpy(xx,CurDir); if(xx[strlen(xx)-1]!='\\') strcat(xx,"\\"); strcat(xx,buf);
  return x;
}
//&>>&2 0 2 6
//&<<&void  GetCurrentFileNameAndDepth();
void GetCurrentFileNameAndDepth(){
  Editor.CurrentDepth=0;
  Fold *s;
  s=cur;
  while(!s->IsFile()){
    s=s->Exit();
    if(!s){
        if(Editor.IsInSearchFold)Editor.CurrentFileName="*SEARCH*";
        else Editor.CurrentFileName="*TEMP*";
        return;}
    Editor.CurrentDepth++;
  }
//  unsigned int ndrv;
  if(s->CurDevNum()){ SaveSetDrive(s->CurDevNum()); }
  char *uuu=s->CurDirName();
  SaveChDir(uuu);
  delete uuu;
  Editor.CurrentFileName=s->buf;
}
//&>>&E 0 E 6
//&>>&1 0 1 15
//&<<&class MarkedLine;
//&<<&void Fold::MarkLine();
void Fold::MarkLine(){
    MarkedLine *f;
    if(pos->marked)
        {
        for(f=MarkedBlock; f->Prev() && f->ref!=pos; f=f->Prev());
        if( f->ref==pos) f->ConnectUnMark();
        else Beep();
        }
    else
        {
        if(MarkedBlock->Next())  f=MarkedBlock->Next();   // Move line to Onmmm_Screen lines
        else  f=new MarkedLine(0);         // add one more line to list
        f->ConnectMark(pos);
        }
    Redr();
}
//&>>&A 1 A 50
//&<<&void MarkedLine::ConnectMark(Line *cpos){
void MarkedLine::ConnectMark(Line *cpos){
if(!cpos->next)return;
ref=cpos;
ref->marked=1;
UnLink();
LinkBefore(MarkedBlock);
}
//&>>&0 0 0 1D
//&<<&void MarkedLine::ConnectUnMark(){
void MarkedLine::ConnectUnMark(){
UnLink();
ref->marked=0;
next=MarkedBlock->Next();
MarkedBlock->next=this;
prev=MarkedBlock;
pcb=0;
}
//&>>&0 0 0 0
//&<<&void MarkedLine::AddCcb(char c);
void MarkedLine::AddCcb(char c){
  Realloc(pcb+1);
  buf[pcb++]=(c ? c : ' ');
  qcb=pcb;
}
//&>>&0 0 0 1C
//&<<&void FirstMarked();
void FirstMarked(){
    MarkedLine *f=MarkedBlock;
    if(!f->Prev()) {Beep(); return;}
    while(f->Prev()) f=f->Prev();
    cur->pos=f->ref;
    Redr();
}
//&>>&3 0 3 19
//&<<&void LastMarked();
void LastMarked(){
    MarkedLine *f=MarkedBlock;
    if(!f->Prev()) {Beep(); return;}
    f=f->Prev();
    cur->pos=f->ref;
    Redr();
}
//&>>&3 0 3 D
//&<<&void NextMarked();
void NextMarked(){
    if(!cur->pos->marked){ FirstMarked(); return; }

    MarkedLine *f=MarkedBlock;
    if(!f->Prev()){Beep(); return; }

    while( f->ref!=cur->pos && f->Prev() )
        f=f->Prev();

    if( f->ref==cur->pos && f->Next()!=MarkedBlock && f->Next() ) cur->pos=f->Next()->ref;
    Redr();
}
//&>>&4 0 4 F
//&<<&void PrevMarked();
void PrevMarked(){
    if(!cur->pos->marked){ LastMarked(); return; }
    MarkedLine *f=MarkedBlock;
    if(!f->Prev()) {Beep(); return;}
    for(f=MarkedBlock; f->Prev() && f->ref!=cur->pos; f=f->Prev());
    if( f->ref==cur->pos && f->Prev() ) cur->pos=f->Prev()->ref;
    Redr();
}
//&>>&3 0 3 0
//&<<&void SaveMarkedBlock();
void SaveMarkedBlock(){
MarkedLine *f;
MarkedBlockLength=0;
while(MarkedBlock->Next()) delete MarkedBlock->Next(); // delete the end of buffer
while(MarkedBlock->Prev())
    {
    f=MarkedBlock->Prev();
    f->ConnectUnMark();
    MarkedBlockLength++;
    }
Redr();
}
//&>>&3 0 3 1
//&<<&void RestMarkedBlock();
void RestMarkedBlock(){
MarkedLine *f;
Line *cpos=cur->pos;
while(MarkedBlock->Next() && cpos->next && MarkedBlockLength>0)
    {
    f=MarkedBlock->Next();
    f->ConnectMark(cpos);
    cpos=cpos->next;
    MarkedBlockLength--;
    }
Redr();
}
//&>>&0 0 0 0
//&>>&0 0 0 D
//&<<&class Chain     /// Knows about 'cur' and 'Fold::Exit()' func.
//&<<&Chain *Chain::LinkBefore(Chain *f);
Chain *Chain::LinkBefore(Chain *f){         // 'this' is unlinked
  Editor.NumberOfPages++;
  prev=f->prev; next=f;
  if(prev) prev->next=this;
  f->prev=this;
  return this;
  }
//&>>&7 0 7 0
//&<<&Chain *Chain::PageNext();          /// modify CUR
Chain *Chain::PageNext(){
  if(MarkedBlock->Prev()) SaveMarkedBlock();
  entry=cur;
  MemTest(next!=0);
  cur=next->entry;
  return next;
  }
//&>>&1 0 1 0
//&<<&Chain *Chain::PagePrev();          /// modify CUR
Chain *Chain::PagePrev(){
  if(MarkedBlock->Prev()) SaveMarkedBlock();
  entry=cur;
  MemTest(prev!=0);
  cur=prev->entry;
  return prev;
  }
//&>>&1 0 1 0
//&<<&void   Chain::PageUnlink();
void   Chain::PageUnlink(){
  while(entry) entry->Exit();
  if(next==prev) {    /// there is only one page left
      remove(MFileName("__mmm__.mmm"));
      exit(0);
      }
  next->prev=prev;
  prev->next=next;
  Editor.NumberOfPages--;
  }
//&>>&1 0 1 0
//&>>&2 0 2 C

//&<<&void View();
void View(){
  if(cur==0) return;
  cur->Draw();
}
//&>>&4 0 4 9
//&<<&Fold/File Movement
//&<<&void _EXIT(int n);
void _EXIT(int n){
    if(MarkedBlock->Prev()) SaveMarkedBlock();
    Fold *f;
    if(!cur->IsFile() && cur->top) cur->Exit()->pos=cur;
    do{
      f=cur->Exit();
      if(!f){
            if(CurrentPage==ConstantPage) {Beep(); break;}
            if(Editor.IsInSearchFold) {SwitchIntoSearchPage(); break;}
            Chain *pp=CurrentPage;
            CurrentPage=CurrentPage->PageNext();
            pp->entry=0; pp->PageUnlink(); delete pp;
            break;
            }
      cur=f;
    }while(n);
    GetCurrentFileNameAndDepth();
    Redr();
}
//&>>&5 0 5 0
//&<<&int _EDIT_ScriptFile(char *s,int &nx,int &fx);
//&<<&char *get_next_word(char *&str);
char *get_next_word(char *&str){
    char *ccur,*rv;
    while(*str==' ')str++;
    if(*str==0 || *str==0x0d || *str==0x0a)return 0;
    ccur=str;
    while(*str!=' ' && *str!=0 && *str!=0x0d && *str!=0x0a)str++;
    rv=new char[str-ccur+1];
    int i=0;
    while(ccur<str) *(rv+i++)=*(ccur++);
    *(rv+i)=0;
    return rv;
    }
//&>>&0 0 0 F
int _EDIT_ScriptFile(char *s,int &nx,int &fx){  // edit file
FILE *fptr=fopen(s+1,"r");
if(fptr==0)return 0;
char *strin=new char[0x100]; MemTest(strin!=0);
char *word,*scur;
int rv=0,f_page;
while(fgets(strin,0xff,fptr)>0){
  f_page=0; /// if the page was added (for current line)
  scur=strin;
  while(word=get_next_word(scur)){
      Beep();
      if(f_page)  { rv|=_EDIT(word,nx,fx,0); }
      else   rv|=(f_page=_EDIT(word,nx,fx,1));
      delete word;
      }
  }
fclose(fptr);
delete strin;
return rv;
}
//&>>&C 0 C 0
//&<<&int _EDIT(char *s,int &nx,int &fx,int IsNewPage);
int _EDIT(char *s,int &nx,int &fx,int IsNewPage){  // edit file
  if(s[0]=='@') return  _EDIT_ScriptFile( s, nx, fx);
//&<<&  if(s[0]=='-'){ .... exit }
  if(s[0]=='-'){
    char c=s[1];
    switch(c){
      case 'a': case 'A': fx=FILE_ASCII; break;
      case 'l': case 'L': fx=FILE_LIST; break;
      default:
        if(c>'0' && c<='9') nx=int(strtol(s+1,0,10));
    }
    return 0;
  }
//&>>&3 0 3 22
  File *fil=new File(s,fx);
  if(IsNewPage)
//&<<&    Inserting new page
    {
    CurrentPage->entry=cur;
    Chain *NewNode=new Chain(fil);
    CurrentPage=NewNode->LinkBefore(CurrentPage);
    fil->top=0;
    }
//&>>&0 0 0 10
  else fil->top=cur;
  cur=fil;
  while(--nx){
    Fold *f=cur->pos->Enter();
    if(f==0) break;
    f->top=cur; cur=f;
  }
  Redr();
  nx=1; fx=FILE_FOLD;
  return 1;
}
//&>>&11 0 11 5
//&<<&void Fold::FDown(int IsNewPage);
void Fold::FDown(int IsNewPage){
  if(MarkedBlock->Prev()) SaveMarkedBlock();
  Fold *f=pos->Enter();
  if(f){
    f->top=cur; cur=f;
  }else{
    int tcx=cx;
    int fx=FILE_FOLD,fn=1;
    int k=0;
    char *x;

    while((x=pos->GetFileName(cx))!=0){
      k=_EDIT(x,fn,fx,IsNewPage);
      delete x;
      if(k) break;
      while(pos->buf[cx++]>' ');
      while(pos->buf[cx++]==' ');
      }

    cx=tcx;
    if(k==0) _EDIT("*.*",fx,fn,IsNewPage);
  }
  GetCurrentFileNameAndDepth();
  Redr();
}
//&>>&19 0 19 3
//&<<&void PerformExitingFromFiles(FILE *filelist){
void PerformExitingFromFiles(FILE *filelist){
    char *s, *u;
    int n=1;     // depth counter

    s=new char[2]; s[0]='\n'; s[1]=0;
    Fold *curf=cur;
    while(cur){
        u=cur->FileName();
        if(u==0) n++;   // Not in a File, but in Fold
//&<<&        else{           // Print fileinfo to "filelist" (File top reached)
        else{           // Print fileinfo to "filelist" (File top reached)
            cur->pos->fchg|=LINE_OTHER;
            char *ss=new char[strlen(s)+strlen(u)+10]; MemTest(ss!=0);
            sprintf(ss," -%d %s%s",n,u,s);
            delete s; delete u; n=1;
            s=ss;
            }
//&>>&0 0 0 A
        curf=cur->Exit();
        if(curf) cur=curf;  // only exit one level up
        else{               // Sittin' on the top of the Page
//&<<&            #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("    Top of the Page reached{ \n");
            #endif
//&>>&1 0 1 10
            n=1;
            if(Editor.IsInSearchFold) {SwitchIntoSearchPage(); continue;}
//&<<&            if(CurrentPage==ConstantPage){ NextPage(); continue; }
        if(CurrentPage==ConstantPage && ConstantPage->next!=ConstantPage )
            {
            CurrentPage=CurrentPage->PageNext();
            GetCurrentFileNameAndDepth();
            continue;
            }
//&>>&0 0 0 0
            fputs(s,filelist); delete s; s=0;
            if(CurrentPage->next == CurrentPage->prev)break;
            Chain *pp=CurrentPage;
            CurrentPage=CurrentPage->PagePrev();
//&<<&            #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("        pp->entry=0; pp->PageUnlink(); delete pp;{ \n");
            #endif
//&>>&1 0 1 10
            pp->entry=0; pp->PageUnlink(); delete pp;
//&<<&            #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("            }\n");
            #endif
//&>>&1 0 1 10
            GetCurrentFileNameAndDepth();
            s=new char[2]; s[0]='\n'; s[1]=0;
//&<<&            #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("        }\n");
            #endif
//&>>&1 0 1 10
            }
        }
    if(s!=0) delete s;
    }
//&>>&1A 0 19 21
//&>>&4 0 4 16
//&<<&Copying of characters
Line mmm_CharClipboard("");          //character clipboard
int pmmm_CharClipboard=0,qmmm_CharClipboard=0;

//&<<&void AddCcb(char c){
void AddCcb(char c){
  mmm_CharClipboard.Realloc(pmmm_CharClipboard+1);
  mmm_CharClipboard.buf[pmmm_CharClipboard++]=(c ? c : ' ');
  qmmm_CharClipboard=pmmm_CharClipboard;
}
//&>>&3 0 3 27
//&<<&void Fold::MoveCh(int f){
void Fold::MoveCh(int f){
  if(f) DelCh(); else cx++;
}
//&>>&0 0 0 5
void CClear(){ pmmm_CharClipboard=qmmm_CharClipboard=0; }
//&<<&void Fold::CCopy(int f){
void Fold::CCopy(int f){
if(!pos->marked) AddCcb(GetCh());
else{
  MarkedLine *f=MarkedBlock;
  while(f->Prev()){
    f=f->Prev();
    f->AddCcb(f->GetCh());
  }
}
MoveCh(f);
}
//&>>&0 0 0 B
//&<<&void Fold::CRest(){
void Fold::CRest(){
if(!pos->marked) {
  for(pmmm_CharClipboard=0;pmmm_CharClipboard<qmmm_CharClipboard;pmmm_CharClipboard++)
      Ascii(mmm_CharClipboard.buf[pmmm_CharClipboard]);
  pmmm_CharClipboard=0;
}else{
  MarkedLine *f=MarkedBlock;
  int scx;
  while(f->Prev()){
    f=f->Prev();
    scx=cx;
    for(f->pcb=0;f->pcb<f->qcb;f->pcb++)
        {
        if(Editor.InsFlag) f->ref->InsChar(cx);
        f->ref->SetChar(cx,f->buf[f->pcb]);
        cx++;
    }
    f->pcb=0;
    cx=scx;
  }
}}
//&>>&B 0 B 0
//&<<&char Fold::GetCh(){
char Fold::GetCh(){
  return cx>=pos->lbuf ? 0 : pos->buf[cx];
}
//&>>&0 0 0 0
//&<<&void Fold::WCopy(int f){
void Fold::WCopy(int f){
  if(pos->marked) return;
  char c;
  while(byte(c=GetCh())>' '){ AddCcb(c); MoveCh(f); }
  while(GetCh()==' ') MoveCh(f);
  AddCcb(' ');
}
//&>>&0 0 0 B
//&<<&void Fold::TCopy(int f){
void Fold::TCopy(int f){
  if(pos->marked) return;
  char c;
  while((c=GetCh())!=0){ AddCcb(c); MoveCh(f); }
}
//&>>&0 0 0 B
//&>>&3 0 3 1
//&<<&Copying of lines
void LCheck(){
  if(mmm_LineClipboard==0) mmm_LineClipboard=NewLine(0);
  while(mmm_LineClipboard->next){
    mmm_LineClipboard=mmm_LineClipboard->next;
    delete mmm_LineClipboard->prev;
  }
}

void LClear(){
  LCheck();
  while(mmm_LineClipboard->prev) delete mmm_LineClipboard->prev;
}

void Fold::LSave(int f){
  if(pos->marked)return;
  LCheck();
  while(pos->next){
    pos->Copy()->LinkBefore(mmm_LineClipboard);
    pos=pos->next; sy++;
    if(f==0) break;
  }
}

void Fold::LMove(int f){
  if(pos->marked)return;
  LCheck();
  while(pos->next){
    if((pos->fchg&LINE_OTHER) || !(pos->fchg&LINE_NEW)) pos->next->fchg|=LINE_OTHER;
    Line *p=pos;
    pos=pos->next;
    p->UnLink();
    p->LinkBefore(mmm_LineClipboard);
    if(f==0) break;
  }
  Redr();
}

void Fold::LRest(){
  if(mmm_LineClipboard){
    while(mmm_LineClipboard->next) mmm_LineClipboard=mmm_LineClipboard->next;
    while(mmm_LineClipboard->prev){
      mmm_LineClipboard=mmm_LineClipboard->prev; pos=mmm_LineClipboard->Copy()->LinkBefore(pos);
    }
    Redr();
  }
}
//&>>&2E 0 1A 0
//&<<&Line Movements
void Fold::TRight(){
  for(cx=pos->lbuf;--cx>=0 && byte(pos->buf[cx])<=' ';) ;
  cx++;
}

void Fold::BWord(){
  if(cx>=pos->lbuf || byte(pos->buf[cx])<=' ') return;
  while(cx>=0 && byte(pos->buf[cx])>' ') cx--;
  cx++;
}
//&>>&0 0 0 0
//&<<&InterLine Movements
void Fold::Up(int DoMarkLine){
  if(pos->prev){
    if(DoMarkLine)MarkLine();
    pos=pos->prev; sy--;
    }
}
void Fold::Down(int DoMarkLine){
  if(pos->next){
    if(DoMarkLine)MarkLine();
    pos=pos->next; sy++;
    }
}
void Fold::TUp(int DoMarkLine){
  while(pos->prev){
    if(DoMarkLine)MarkLine();
    pos=pos->prev; sy--;
    }
}
void Fold::TDown(int DoMarkLine){
  while(pos->next){
    if(DoMarkLine)MarkLine();
    pos=pos->next; sy++;
    }
}
void Fold::PUp(int DoMarkLine){
  int i;
  for(i=mmm_screen.GetH()-lHead;--i>1 && pos->prev;){
    if(DoMarkLine)MarkLine();
    pos=pos->prev;
    }
  Redr();
}

void Fold::PDown(int DoMarkLine){
  int i;
  for(i=mmm_screen.GetH()-lHead;--i>1 && pos->next;){
    if(DoMarkLine)MarkLine();
    pos=pos->next;
    }
  Redr();
}

int lspc(Line *p){
  int i;
  if(!(Editor.IndFlag&1)) return -1;
  char *s=p->buf; if(s==0) return -1;
  for(i=0;s[i]==' ';i++) ;
  if(s[i]==0) return -1;
  return i;
}

void Fold::_Enter(){
    int i=lspc(pos);
    if(pos->next){ pos=pos->next; sy++; }
    int j=lspc(pos);
    cx=j<0 ? i : j; if(cx<0) cx=0;
    return;
}
//&>>&20 0 8 0
//&<<&Line Editing
//&<<&void Fold::BackSpace()
void Fold::BackSpace(){
if(!pos->marked){
  if(pos->next!=0){
    if(cx){
      cx--;
      if(Editor.InsFlag) pos->DelChar(cx);
      else pos->SetChar(cx,' ');
    }
  }
}else{
  MarkedLine *f=MarkedBlock;
  if(cx){
    cx--;
    while(f->Prev()){
      f=f->Prev();
      if(Editor.InsFlag) f->ref->DelChar(cx);
      else f->ref->SetChar(cx,' ');
    }
  }
}}

//&>>&15 0 15 3
//&<<&void Fold::Ascii(int code);
void Fold::Ascii(int code){
if(!pos->marked){
  if(pos->next==0) InsLine();
  if(Editor.InsFlag) pos->InsChar(cx);
  pos->SetChar(cx,code);
  cx++;
}else{
  MarkedLine *f=MarkedBlock;
  while(f->Prev()){
    f=f->Prev();
    if(Editor.InsFlag) f->ref->InsChar(cx);
    f->ref->SetChar(cx,code);
    }
  cx++;
}}
//&>>&2 0 2 6
//&<<&void Fold::KillEnd();
void Fold::KillEnd(){
int i;
if(!pos->marked){
  for(i=cx;i<pos->lbuf;i++) pos->buf[i]=0;
  pos->fchg|=LINE_CHG;
}else{
  MarkedLine *f=MarkedBlock;
  while(f->Prev()){
    f=f->Prev();
    for(i=cx;i<f->ref->lbuf;i++) f->ref->buf[i]=0;
    f->ref->fchg|=LINE_CHG;
  }
}
Redr();
}
//&>>&9 0 9 8
//&<<&void Fold::KillBeg();
void Fold::KillBeg(){
int i;
if(!pos->marked){
  if(Editor.InsFlag){
    for(i=0;i+cx<pos->lbuf;i++) pos->buf[i]=pos->buf[i+cx];
    for(;i<pos->lbuf;i++) pos->buf[i]=0;
    cx=0;
  }else{
    for(i=0;i<cx && pos->buf[i];i++) pos->buf[i]=' ';
  }
  pos->fchg|=LINE_CHG;
}else{
  MarkedLine *f=MarkedBlock;
  while(f->Prev()){
    f=f->Prev();
    if(Editor.InsFlag){
      for(i=0;i+cx<f->ref->lbuf;i++) f->ref->buf[i]=f->ref->buf[i+cx];
      for(;i<f->ref->lbuf;i++) f->ref->buf[i]=0;
    }else{
      for(i=0;i<cx && f->ref->buf[i];i++) f->ref->buf[i]=' ';
    }
    f->ref->fchg|=LINE_CHG;
  }
  if(Editor.InsFlag) cx=0;
}
Redr();
}
//&>>&13 0 13 A
//&<<&void Fold::InsCh()
void Fold::InsCh(){
if(!pos->marked){
   if(pos->next) pos->InsChar(cx);}
else{
  MarkedLine *f=MarkedBlock;
  while(f->Prev()){
    f=f->Prev();
    f->ref->InsChar(cx);
  }
}}
//&>>&0 0 0 0
//&<<&void Fold::DelCh()
void Fold::DelCh(){
if(!pos->marked){
   if(pos->next) pos->DelChar(cx);}
else{
  MarkedLine *f=MarkedBlock;
  while(f->Prev()){
    f=f->Prev();
    f->ref->DelChar(cx);
  }
}}
//&>>&4 0 0 8
//&>>&0 0 0 D
//&<<&void Fold::DelLine();
void Fold::DelLine(){
  if(pos->marked)return;
  if(pos->next){
    if((pos->fchg&LINE_OTHER) || !(pos->fchg&LINE_NEW)) pos->next->fchg|=LINE_OTHER;
    pos=pos->next;
    delete pos->prev;
    Redr();
  }
}
//&>>&0 0 0 1

//&>>&17 0 17 E
