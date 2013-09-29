/**********************************************
*   OS/2 include file for MMMX Editor         *
*   Contains OS/2 WARP specific functions     *
***********************************************/

#ifndef __INCLUDED_MMM_OS2__
#define __INCLUDED_MMM_OS2__

#define EXECUTER_FILENAME "__mmm__.cmd"
//&<<&#include
#define INCL_DOSQUEUES
#define INCL_DOS
#define INCL_SUB

#include <os2.h>
#include <conio.h>
#include <process.h>
#include <direct.h>
#include <dos.h>

#include "mmmx.h"
#include "mmmgrep.h"
//&>>&B 0 B 11

//&<<&class mmm_Screen;
class mmm_Screen{
  int need;
  int WIDTH,HEIGHT;
////////////////  int OldScr,OldCl;
////////////////  char far *OldCurs,OldAttr;
///  void Clear();
  VIOMODEINFO saveVideoConfig;
public:
  mmm_Screen();
  ~mmm_Screen();
  int GetH(){ return HEIGHT; }
  int GetW(){ return WIDTH; }
  void View();
  int &Need(){ return need; }
  void SetCursor(int x,int y,int attr);
  void ClrCursor();
};
//&>>&9 0 9 D

//&<<&class mmm_KeyBoard;
#ifdef __TURBOC__
#  define IntArg ...
#else
#  define IntArg
#endif

class mmm_KeyBoard{
    APIRET retcode;
    KBDKEYINFO keydata;
    KBDINFO SaveKBD;
    void InitKeyboardLayout();
    char *InitDefaultAltCase();
public:
    char *AltCase;
    char keys[4][108];
    int LastScanCode;
    void SetACode(int n);
    mmm_KeyBoard();
    ~mmm_KeyBoard();
    int GetScan();
};

void ProcessShiftsStatus(USHORT stat);
  /////// mmmx.err
//&>>&9 0 9 10

void MkScan(int scancode);
#endif
//&>>&D 0 D 12
