/***************************************************
*   DOS include file for MMMX Editor               *
*   Contains MS-DOS/PHARLAP specific functions     *
****************************************************/

#ifndef __INCLUDED_MMM_DOS__
#define __INCLUDED_MMM_DOS__

#define EXECUTER_FILENAME "__mmm__.bat"
//&<<&#include 
#include <conio.h>
#include <direct.h>
#include <dos.h>
#include <process.h>
#include "mmmx.h"
#include "mmmgrep.h"
//&>>&5 0 5 11

//&<<&class mmm_Screen;
class mmm_Screen{
  int need;
  int WIDTH,HEIGHT;
  int OldScr,OldCl;
  char far *OldCurs,OldAttr;
  unsigned short far *VMem;
  void Clear();
public:
  mmm_Screen();
  ~mmm_Screen();
  int GetH(){ return HEIGHT; }
  int GetW(){ return WIDTH; }
  int &Need(){ return need; }
  unsigned short far *Vmem(){ return VMem; }
  void View();
  void SetCursor(int x,int y,int attr);
  void ClrCursor();
};
//&>>&9 0 9 D
extern mmm_Screen mmm_screen;

//&<<&class mmm_KeyBoard;
#ifdef __TURBOC__
#  define IntArg ...
#else
#  define IntArg
#endif


#ifdef __386__
#define _far_
#else
#define _far_ far
#endif

class mmm_KeyBoard{
    unsigned char keybuf[256];
    volatile unsigned char bbuf,ebuf;
    volatile short code;
    int IsScan(){ return bbuf!=ebuf; }
    void AddScan(unsigned char k);
    void interrupt (far *OldInt9)(IntArg);
    static void interrupt NewInt9(IntArg);
public:
    void InitKeyboardLayout();
    char *InitDefaultAltCase();
    char *AltCase;
    char keys[4][108];
    int LastScanCode;
    void SetACode(int n);
    mmm_KeyBoard();
    ~mmm_KeyBoard();
    int GetScan();
};
  /////// mmmx.err
//&>>&16 0 C 0
//&<<&inline void mmm_KeyBoard::AddScan(unsigned char k){
inline void mmm_KeyBoard::AddScan(unsigned char k){
    if(code!=0x0666) return;
    if(bbuf==(unsigned char)(ebuf+1)){ Beep(); return; }
    keybuf[ebuf++]=k;
  }
//&>>&0 0 0 18
extern mmm_KeyBoard _far_ mmm_KBD;

void MkScan(int scancode);

#endif
//&>>&E 0 E 0
