/**********************************************
*   GREP include file for MMMX Editor         *
*   Contains functions & classes for Search   *
***********************************************/

#ifndef __INCLUDED_MMMGREP__
#define __INCLUDED_MMMGREP__
#include "mmmx.h"

struct refs;
//&<<&struct GrepTbl{
struct GrepTbl{
  int readyF;   // 0 for none, 1 for simple, 2 for grep
  int lpt;      // len of CMask = (ncn/16)+1;
  int ncn;      // number of conditions
  int lpt0;     // allocated CMask
  char *Ptrn,*Repl;
  short *AMask;    // [256*lpt];
  short *TMask;    // [ltm=ncn*lpt];
  short *CMask;    // current  [lpt]
  short *tMask;    // temp     [lpt]

  static int Dir(int dir,int flg){ return dir!=SEARCH_FORWARD && flg!=2 ? -1 : 1; }

  void ClrMask(short *a){ memset((char*)a,0,sizeof(short)*lpt); }
  void SetBit(short *a,int n){ a[n>>4]|=1<<(n&15); }
  int TstBit(short *a,int n){ return a[n>>4]&1<<(n&15); }
  void OrMask(short *a,short *b){ for(int i=0;i<lpt;i++) *a++|=*b++; }
  void AndMask(short *a,short *b){ for(int i=0;i<lpt;i++) *a++&=*b++; }
  void AndMask(short *a,short *b,short *c){ for(int i=0;i<lpt;i++) *a++&=*b++|*c++; }
  int EmptyMask(short *a){ for(int i=0;i<lpt;i++) if(*a++) return 0; return 1; }
  int EmptyAndMask(short *a,short *b){ for(int i=0;i<lpt;i++) if(*a++&*b++) return 0; return 1; }

  GrepTbl():lpt0(0),AMask(0),TMask(0),CMask(0),tMask(0),Ptrn(0),Repl(0),readyF(0){}
  void Set(char *ptrn);
  int Find(char *str,int &len,int sflg,int r0,int dir);

  void SetASC(char s);
  void GetASC(char *&s);
  void ProcChar(char *&s,int &n,refs *R,int LastLb);
};
//&>>&1E 0 13 0
extern GrepTbl SearchMasks;
extern Fold *SearchFold;

extern void SwitchIntoSearchPage();
extern void SearchReplaceTextFragment(int SearchDirection,int DoReplace=0);
#endif
//&>>&6 0 6 1A
