/*******************************
* Search functions definitions *
********************************/

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

//&<<&struct GrepTbl;

struct refs;

GrepTbl SearchMasks;

//&<<&int GrepTbl::Find(char *s,int &len,int sflg,int r0,int dir);
int GrepTbl::Find(char *s,int &len,int sflg,int r0,int dir){
  if(s==0) return -1;
  int ls=strlen(s);
  if(r0==int(0x8000)) r0=dir==SEARCH_FORWARD ? 0 : ls;
  else if(r0<0){ if(dir!=SEARCH_FORWARD) return -1; r0=0; }
  else if(r0>=ls){ if(dir==SEARCH_FORWARD) return -1; r0=ls; }
  if(readyF==2){
//&<<&    GREP search
  ClrMask(CMask);

  if(r0==0) r0--;
  int k;
  for(k=r0;;k++){
    SetBit(CMask,0);
    ClrMask(tMask);
    for(int i=0;i<ncn;i++) if(TstBit(CMask,i)) OrMask(tMask,TMask+lpt*i);
    if(TstBit(tMask,ncn)) break;
    if(k>0 && s[k-1]==0) return -1;
    byte c=k<0 ? 0 : s[k];
    if(sflg&1) AndMask(tMask,AMask+c*lpt);
    else AndMask(tMask,AMask+c*lpt,AMask+lpt*mmm_KBD.AltCase[c]);
    short *tp=tMask; tMask=CMask; CMask=tp;
  }
  ClrMask(CMask);
  SetBit(CMask,ncn);
  int l;
  for(l=k;;){
    assert(!EmptyMask(CMask));
    ClrMask(tMask);
    for(int i=0;i<ncn;i++) if(!EmptyAndMask(CMask,TMask+lpt*i)) SetBit(tMask,i);
    if(TstBit(tMask,0)) break;
    assert(l>r0);
    byte c=l ? s[--l] : 0;
    if(sflg&1) AndMask(tMask,AMask+lpt*c);
    else AndMask(tMask,AMask+lpt*c,AMask+lpt*mmm_KBD.AltCase[c]);
    short *tp=tMask; tMask=CMask; CMask=tp;
  }
  if(s[k-1]==0) k--;
  if(l<0) l++;
  len=k-l;
  return l;
//&>>&1A 0 17 34
  }else if(readyF==1){
//&<<&    Normal search
   len=strlen(Ptrn);
   if(len==0) return r0;
   byte c=Ptrn[0],c1=mmm_KBD.AltCase[c];
   int lc=ls-len;
   if(dir==SEARCH_FORWARD){
     for(;r0<=lc;r0++){
       byte cs=s[r0];
       if(cs!=c && ((sflg&1) || cs!=c1)) continue;
       int i;
       for(i=0;Ptrn[i];i++) if(s[r0+i]!=Ptrn[i] && ((sflg&1) || s[r0+i]!=mmm_KBD.AltCase[byte(Ptrn[i])])) break;
       if(Ptrn[i]==0) return r0;
     }
   }else{
     if(r0>lc) r0=lc;
     for(;r0>=0;r0--){
       byte cs=s[r0];
       if(cs!=c && ((sflg&1) || cs!=c1)) continue;
       int i;
       for(i=0;Ptrn[i];i++) if(s[r0+i]!=Ptrn[i] && ((sflg&1) || s[r0+i]!=mmm_KBD.AltCase[byte(Ptrn[i])])) break;
       if(Ptrn[i]==0) return r0;
     }
   }
   return -1;
//&>>&12 1 12 50
  }else return -1;
}
//&>>&9 0 9 12

//&<<&Grep pattern
/*
  Grep pattern::

  [set]
    set::   ] - ~ are special
  {expr}
  (expr|expr|expr)
    (){}|[?* \bcqn are special (break/continue/conditional break/start-end of line)
  "\ " = "replace"
*/
//&>>&0 0 0 0

//&<<&char GetMacroChar(char *&s);
int HexDig(char c){ return c>='0' && c<='9' ? c-'0' : c>='A' && c<='F' ? c-'A'+10 : c>='a' && c<='f' ? c-'a'+10 : -1; }
char GetMacroChar(char *&s){
    if(*s==0) return 0;
    char c=*s++;
    if(c!='\\') return c;
    if(*s=='x'){ s++;
      int i=HexDig(*s); if(i<0) return 0; s++;
      int j=HexDig(*s); if(j<0) return i; s++;
      return i*16+j;
    }
    if(*s==0) return 0;
    return *s++;
}
//&>>&0 0 0 0
//&<<&void GetAsciiSet(char *&s,short *asc,char fend);  // s - first char in [], fend=term char
void GetAsciiSet(char *&s,short *asc,char fend){  // s - first char in [], fend=term char
  memset(asc,0,256/8); int fnot=0;
  if(*s=='^'){ s++; fnot=1; }
  if(*s==']'){ asc[5]|=0x2000; s++; }  /// вздергивается бит для ']'
  while(*s!=fend && *s!=0){
    byte c=GetMacroChar(s);
    if(*s=='-' && s[1]!=fend && s[1]!=0){
      s++; byte c1=GetMacroChar(s);
      for(;c<=c1;c++) asc[c>>4]|=1<<(c&15);
    }else asc[c>>4]|=1<<(c&15);
  }
  if(fnot){ for(int i=1;i<256/16;i++) asc[i]^=-1; asc[0]^=-2; }
}
//&>>&D 0 D F
struct refs{ int r1,r2,a,f; };
//&<<&void GrepTbl::Set(char *ptrn);
//&<<&char *GetPattern(char *&p);
char *GetPattern(char *&p){
  char *q=new char[strlen(p)+1]; MemTest(q!=0);
  char *r=q;
  while(*p){
    if(*p!='\\') *r++=*p++;
    else{
      p++;
      if(*p==' '){ p++; *r=0; return q; }
      if(*p==0){ *r=0; return q; }
      *r++=*p++;
    }
  }
  *r=0;
  return q;
}
//&>>&C 0 C 1B

void GrepTbl::Set(char *ptrn){
  int i,j,k;
  char *s;
  short asc[16];

  delete Ptrn; delete Repl; Ptrn=Repl=0;

  char *s0=ptrn+strlen(ptrn);
  while(s0!=ptrn && s0[-1]==' ') s0--;
  if(*s0==0) s0=0; else *s0=0;

  if(ptrn[0]!='\\' || ptrn[1]!=' '){
    Ptrn=GetPattern(ptrn);
    if(*ptrn) Repl=GetPattern(ptrn);
    readyF=1;
    return;
  }

  ptrn+=2;
  char *s1=0;
//&<<&  Find Number of multiletters
  int nl=1,nr=1;
  for(s=ptrn;*s!=0;){
    switch(*s){
    case '(': nr++; s++; break;
    case '}': case ')': nl++; s++; break;
    case '{':
    case '|': s++; nr+=2; break;
    case '[': s++; GetAsciiSet(s,asc,']'); if(*s==']') s++; nl++; break;
    case '\\':
      switch(s[1]){
        case 'b': case 'c': case 'q': s+=2; nr++; break;
        case ' ': s1=s; *s1=0; s+=2; Repl=GetPattern(s); goto _1;
        case 0: s1=s; *s1=0; goto _1;
        default: GetMacroChar(s); nl++; break;
      }
      break;
    case '*': nr++;
    default:
      s++; nl++;
    }
  }
_1:
  nr+=nl;
//&>>&C 0 C 25

//&<<&  Init memory
  refs *R=new refs[nr];
  lpt=nl/16+1;
  if(lpt>lpt0){
    delete AMask; AMask=new short[256*lpt];
    delete TMask; TMask=new short[nl*lpt];
    delete CMask; CMask=new short[lpt];
    delete tMask; tMask=new short[lpt];
    lpt0=lpt;
  }
  memset((char*)AMask,0,256*lpt*sizeof(short));
  memset((char*)TMask,0,nl*lpt*sizeof(short));
//&>>&0 0 0 5

  for(i=0;i<nr;i++){ R[i].r1=i+1; R[i].r2=R[i].a=0; }
  int n=1; ncn=1;
  for(s=ptrn;*s;) ProcChar(s,n,R,0);
  R[n].a=ncn;

  for(i=0;i<n;i++) assert(R[i].r1>=0 && R[i].r2>=0);
  for(i=0;i<n;i++) if(i==0 || R[i].a){
    for(j=0;j<=n;j++) R[j].f=0;
    R[R[i].r1].f=R[R[i].r2].f=1;
    for(;;){
      k=0;
      for(j=1;j<n;j++) if(R[j].a==0 && R[j].f==1){
        k=1;
        R[R[j].r1].f|=1;
        R[R[j].r2].f|=1;
        R[j].f=2;
      }
      if(k==0) break;
    }
    for(j=1;j<=n;j++) if(R[j].f && R[j].a){
      TMask[R[i].a*lpt+(R[j].a>>4)]|=1<<(R[j].a&15);
    }
  }
  if(s0) *s0=' '; if(s1) *s1='\\';
  readyF=2;
}
//&>>&11 0 11 14
void GrepTbl::SetASC(char s){ AMask[byte(s)*lpt+(ncn>>4)]|=1<<(ncn&15); }
//&<<&void GrepTbl::GetASC(char *&s);
void GrepTbl::GetASC(char *&s){
  short asc[16];
  s++;
  GetAsciiSet(s,asc,']');
  if(*s==']') s++;
  for(int i=0;i<256;i++) if(asc[i>>4]&(1<<(i&15))) SetASC(i);
}
//&>>&5 0 5 10
//&<<&void GrepTbl::ProcChar(char *&s,int &n,refs *R,int LastLb);
void GrepTbl::ProcChar(char *&s,int &n,refs *R,int LastLb){
  int i;
  switch(*s){
  case '(':{
//&<<&    Process "(...)" }
    int lp=n,lor=n; n++; s++;
    while(*s!=')' && *s){
      if(*s=='|'){
        R[n].r1=0; R[n].r2=-1; n++;
        R[lor].r2=n; lor=n; n++; s++;
      }else ProcChar(s,n,R,LastLb);
    }
    for(;lp<n;lp++) if(R[lp].r2==-1) R[lp].r2=n;
    if(*s==')') s++; return; }
//&>>&0 0 0 17
  case '{':{
//&<<&    Process "{...}" }
    int lp=n,lor=n; n++; s++;
    while(*s!='}' && *s){
      if(*s=='|'){
        R[n].r1=0; R[n].r2=lp; n++;
        R[lor].r2=n; lor=n; n++; s++;
      }else ProcChar(s,n,R,lp);
    }
    R[n].r1=lp; n++;
    i=0;
    for(;lp<n;lp++) if(R[lp].r2==-2) i=R[lp].r2=n;
    if(i==0) R[lor].r2=n;
    if(*s=='}') s++; return; }
//&>>&7 0 7 B
  case '*':           // {\q?}
    R[n].r2=n+2;
    R[n+1].r1=n;
    n++;
  case '?':
    for(i=1;i<256;i++) SetASC(i); R[n++].a=ncn++; s++; return;
  case '[': GetASC(s); R[n++].a=ncn++; return;
  case '\\':
    switch(s[1]){
    case 'b': R[n].r2=-2; R[n].r1=0; s+=2; n++; return;
    case 'c': R[n].r2=LastLb; R[n].r1=0; s+=2; n++; return;
    case 'q': R[n].r2=-2; s+=2; n++; return;
    case 'n': SetASC(0); R[n++].a=ncn++; s+=2; return;
    }
  default:
    SetASC(GetMacroChar(s)); R[n++].a=ncn++; return;
  }
}
//&>>&6 0 6 D
//&>>&5 0 5 19
//&<<&void SearchReplaceTextFragment(int SearchDirection,int DoReplace=0);
void SearchReplaceTextFragment(int SearchDirection,int DoReplace){
  if(cur==0 || cur->pos==0 || //cur->pos->buf==0 ||
           SearchFold==0 || SearchFold->pos==0 || SearchFold->pos->buf==0 ){
      Beep();
      return;
      }

  Line *sp_pos=cur->pos;

  if(SearchMasks.readyF==0){
    SearchMasks.Set(SearchFold->pos->buf);
//    SearchMasks.readyF=1;
  }

  int i,l,k;
  int ccx=cur->cx;
  k=SearchMasks.Find(sp_pos->buf,l,Editor.SearchMode,ccx,SearchDirection);
  char *Repl=SearchMasks.Repl;
  if(k==ccx && DoReplace && Repl){
    int lR=strlen(Repl);
    if(l<lR)    { for(i=0;i<lR-l;i++) sp_pos->InsChar(ccx); }
    else        { for(i=0;i<l-lR;i++) sp_pos->DelChar(ccx); }
    for( i=0;Repl[i];i++) sp_pos->SetChar(ccx+i,Repl[i]);
    cur->cx=ccx+lR;
    Redr();
    return;
  }
  if(k==ccx){
    k=SearchMasks.Find(sp_pos->buf,l,Editor.SearchMode,ccx+GrepTbl::Dir(SearchDirection,SearchMasks.readyF),SearchDirection);
  }
  if(k>=0){ cur->cx=k; Redr(); return; }
// not in current string!
  Fold *f=cur->FindCont(SearchDirection,0,SearchDirection==SEARCH_FORWARD ? 2 : 0);
  if(f){ cur=f; Redr(); }else Beep();
}

//&>>&1 0 1 14
//&<<&Fold *Fold::FindCont(int SearchDirection,int fcur,int ft);
Fold *Fold::FindCont(int SearchDirection,int fcur,int ft){
                // fcur: 0=from current (and up), 1=from start/end (to end/start)
                // ft:1 if in current line; 2 if in current fold
  if(this==0) return 0;
  Line *CurLine=pos,*CL=pos;
  int cury=sy;
  Fold *rv=0;
  if(SearchDirection!=SEARCH_FORWARD){
//&<<&    Search Backward
    if(fcur){
      while(pos->next){ pos=pos->next; sy++; }
      ft=0;
    }
    for(;;){
      if(ft&2){
        Fold *f=pos->Enter();
        if(f){
          f->top=this;
          rv=f->FindCont(SearchDirection,1,0);
          if(rv) break;
        }
      }
      if(ft&1){
        int l,k;
        k=SearchMasks.Find(pos->buf,l,Editor.SearchMode,0x8000,SearchDirection);
        if(k>=0){ cx=k; rv=this; break; }
      }
      if(!pos->prev) break;
      pos=pos->prev; sy--;
      ft=3;
    }
//&>>&0 0 0 0
  }else{
//&<<&    Search Forward
    if(fcur){
      while(pos->prev){ pos=pos->prev; sy--; }
      ft=3;
    }
    for(;;){
      if(pos->next==0) break;
      if(ft&1){
        int l,k;
        k=SearchMasks.Find(pos->buf,l,Editor.SearchMode,0x8000,SearchDirection);
        if(k>=0){ cx=k; rv=this; break; }
      }
      if(ft&2){
        Fold *f=pos->Enter();
        if(f){
          f->top=this;
          rv=f->FindCont(SearchDirection,1,0);
          if(rv) break;
        }
      }
      pos=pos->next; sy++;
      ft=3;
    }
//&>>&13 0 13 0
  }
  if(rv) return rv;
  assert(CurLine==CL);
  pos=CurLine;
  sy=cury;
  if(fcur || IsFile()) return 0;
  return Exit()->FindCont(SearchDirection,0,SearchDirection);    // 0,1 !!!
}
//&>>&8 0 8 17

//&<<&void SwitchIntoSearchPage(); 
void SwitchIntoSearchPage() {
    SearchMasks.readyF=0;
    SaveMarkedBlock();
    Editor.IsInSearchFold=!Editor.IsInSearchFold;
    Fold *u=cur;
    cur=SearchFold;
    SearchFold=u;
    GetCurrentFileNameAndDepth();
    Redr();
}
//&>>&5 0 5 13

/// mmmgrep.err mmmgrep.err mmmgrep.err mmmgrep.err mmmgrep.err
//&>>&14 0 14 7
