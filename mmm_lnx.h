/**********************************************
*   Linux include file for MMMX Editor        *
*   Contains Linux  Spacific functions        *
*    ( Tested on i386 RedHat Linux 3.0+ )     *
***********************************************/

#ifndef __INCLUDED_MMM_LINUX__
#define __INCLUDED_MMM_LINUX__

#define EXECUTER_FILENAME "__mmm__.bat"
//&<<&#include 
#include "mmmx.h"
#include "mmmgrep.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/tty.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <signal.h>
#include <termios.h>       /* for tcget(set)attr */
#include <sys/ioctl.h>
#include <dirent.h>
#include <sys/stat.h>
//&>>&1 0 1 11

void DrawLine(char *Str, int PosY, char Attr,int slen);

//&<<&class mmm_Screen {
class mmm_Screen {
   char *v_screen;
   int need;
   int WIDTH,HEIGHT;
   int curatr;
   int OldScr,OldCl;            /// only for compatibility ?
   char *OldCurs,OldAttr;       /// only for compatibility ?
   void setatr(int atr);
public:
   mmm_Screen();
   ~mmm_Screen();
   void SetCursor(int x,int y,int attr);
   void ClrCursor();
   void Line(char *str,int len,int x,int y);
   int &Need(){ return need; }
   int GetH(){ return HEIGHT; }
   int GetW(){ return WIDTH; }
   void View(){};
   };
//&>>&1 0 1 B
extern mmm_Screen mmm_screen;

//&<<&class mmm_KeyBoard{
class mmm_KeyBoard{
    int ed_gflag;
    struct termios t1;
    int om;
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
    friend void SegmentViolationHandler(int a);
    void ChangeConsole(int num);
};
//&>>&C 0 C 11
extern mmm_KeyBoard mmm_KBD;

void MkScan(int scancode);

#endif
//&>>&12 0 12 1B
