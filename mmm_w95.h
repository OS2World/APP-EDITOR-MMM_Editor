/**********************************************
*   WIN95 include file for MMMX Editor        *
*   Contains WIN95/NT specific functions      *
*     ( NT is untested )                      *
***********************************************/

#ifndef __INCLUDED_MMM_W95__
#define __INCLUDED_MMM_W95__

#define EXECUTER_FILENAME "__mmm__.bat"
//&<<&#include 
#include <conio.h>
#include <direct.h>
#include <dos.h>
#include <process.h>
#include <windows.h>
#include <wincon.h>
#include "mmmx.h"
#include "mmmgrep.h"

//&>>&7 0 7 11

//&<<&struct mmm_Screen;
struct mmm_Screen{
  int need;
  SMALL_RECT Rect;
  COORD Zero,Size;
  COORD OldCur;
#if 1
  CHAR_INFO *scr;
#else
  char *scr;
#endif
  WORD *attrs; char **strs; int *lens;
  WORD CCurAttr;
  int HEIGHT;
public:
  mmm_Screen();
  ~mmm_Screen();
  void Init();
  int GetH(){ return HEIGHT; }
  int GetW(){ return Size.X; }
  void DrawLine(char *Str, int PosY, char Attr,int slen);
  int &Need(){ return need; }
  void SetCursor(int x,int y,WORD attr);
  void ClrCursor();
};
//&>>&12 0 12 D
extern mmm_Screen mmm_screen;

//&<<&struct KeyRes;
struct KeyRes{
  BOOL keydown;
  WORD scode;
  DWORD ctrl;
};

//&>>&0 0 0 0
//&<<&struct mmm_KeyBoard;
struct mmm_KeyBoard{
    int bch,ech;
    KeyRes *buf;
    void InitKeyboardLayout();
    char *InitDefaultAltCase();
public:
    char *AltCase;
    char keys[4][108];
    void SetACode(int n);
    mmm_KeyBoard();
    ~mmm_KeyBoard(){ delete buf; }
    KeyRes &GetScan();
    void GetEvent(int);
};
//&>>&A 0 A 11
extern mmm_KeyBoard mmm_KBD;
void MkScan(KeyRes &scancode);
void _dos_setdrive(unsigned int n,unsigned int *t);
void _dos_getdrive(unsigned int *res);

#endif
//&>>&C 0 C 1B
