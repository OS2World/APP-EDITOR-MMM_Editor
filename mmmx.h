/***************************************************
*   Main include file for MMMX Editor              *
*   Contains Common Editor Functions & structes    *
*                                                  *
*   To use editor you must at first create         *
*   mmm.cfg file by mmm_cfg utility                *
****************************************************/
// #define _ENABLE_LOGGING_
//////// #define _INCLUDE_SAFETY_MODULE_ /* define it to read after last Fold-Close sign */

#ifndef __INCLUDED_MMMX__
#define __INCLUDED_MMMX__
//&<<&Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//&>>&4 0 4 0
#include "mmmconst.h"

//&<<&editor structes pre-declaration
struct Chain;
struct Line;
struct Fold;
struct File;
struct MarkedLine;
struct EDITOR;
struct mmm_Screen;
struct mmm_KeyBoard;
typedef unsigned char byte;
struct TPair_String_Function;
struct TPair_String_Int;
struct TKeyArray;
//&>>&7 0 7 13
//&<<&Constants and variables
extern int MinimalExitFromEditor;  // this is set to 1 when memory allocation error occurs

extern char *comment;         // comment to be applied to file
extern int lcomment;          // length of current comment

extern char *templine;
extern unsigned _stklen;

extern mmm_Screen mmm_screen;
extern mmm_KeyBoard mmm_KBD;

extern MarkedLine *MarkedBlock;

extern Chain *ConstantPage;
extern Chain *CurrentPage;

extern Fold *fLineClipboard;
extern Fold *cur;                 // Current fold
extern Line *mmm_LineClipboard;   // Line clipboard
extern Line mmm_CharClipboard;     //character clipboard

extern int lHead;
const StatusLineLength=0x100;
extern char StatusLineText[];
extern int MarkedBlockLength;   // Number of lines in buffer

extern unsigned long FileLinesCounter;

//&<<&Various Keyboard flags
extern volatile int mmm_f_E0;
extern volatile int mmm_f_LeftShift,mmm_f_RightShift;
extern volatile int mmm_f_LeftCtrl,mmm_f_RightCtrl;
extern volatile int mmm_f_LeftAlt,mmm_f_RightAlt;
extern volatile int mmm_f_Caps;
extern volatile int mmm_f_FixShift,mmm_f_FixAlt;
extern volatile mmm_f_Shift,mmm_f_Alt,mmm_f_Ctrl;
//&>>&0 0 0 0

extern char *mcode,*acode;

extern TKeyArray KeyArray;

extern int fRecordingMacro;

extern Fold *RuntimeStack;

//&>>&E 0 B 11
//&<<&Forward declarations
//&<<&#ifdef _ENABLE_LOGGING_
#ifdef _ENABLE_LOGGING_
#include <stdarg.h>
extern void DoLog(char *, ... );
#endif
//&>>&0 0 0 0
extern void Process();
extern void InitCommand();
extern void MemTest(int i);
extern void View();
extern void Redr(int LineToRedraw=REDRAW_WHOLE_SCREEN);
extern void GetCurrentFileNameAndDepth();
extern void _EXIT(int n);
extern void __EXIT();
extern void PerformExitingFromFiles(FILE *filelist);
extern int _EDIT_ScriptFile(char *s,int &nx,int &fx);
extern int _EDIT(char *s,int &nx,int &fx,int IsNewPage);
extern Line *NewLine(char *s,unsigned long LinCnt=0);
extern char *MFileName(char *s);

extern void SetTitle(char *dirname,char *filename);
extern void DrawLine( char *Str, int PosY, char Attr,int slen);
extern void Beep();

extern char *getcurdir(int f=1);
extern int SaveGetDrive();
extern void SaveChDir(char *s);
extern void SaveSetDrive(unsigned int n);

extern void CClear();
extern void LClear();

extern void Command(short MMMscan);

int WildCard(char *n);

//&>>&0 0 0 2F
//&<<&Commands in canonical form
extern void MMMlib_Up            (int ccode);
extern void MMMlib_Down          (int ccode);
extern void MMMlib_Left          (int ccode);
extern void MMMlib_Right         (int ccode);
extern void MMMlib_TUp           (int ccode);
extern void MMMlib_TDown         (int ccode);
extern void MMMlib_TLeft         (int ccode);
extern void MMMlib_TRight        (int ccode);
extern void MMMlib_PUp           (int ccode);
extern void MMMlib_PDown         (int ccode);
extern void MMMlib_FUp           (int ccode);
extern void MMMlib_FDown         (int ccode);
extern void MMMlib_FLeft         (int ccode);
extern void MMMlib_FRight        (int ccode);
extern void MMMlib_Enter         (int ccode);
extern void MMMlib_Tab           (int ccode);
extern void MMMlib_LTab          (int ccode);
extern void MMMlib_InsCh         (int ccode);
extern void MMMlib_DelCh         (int ccode);
extern void MMMlib_InsLine       (int ccode);
extern void MMMlib_InsFold       (int ccode);
extern void MMMlib_DelLine       (int ccode);
extern void MMMlib_BS            (int ccode);
extern void MMMlib_Ascii0        (int ccode);
extern void MMMlib_Ascii1        (int ccode);
extern void MMMlib_Ascii2        (int ccode);
extern void MMMlib_Space         (int ccode);
extern void MMMlib_KillWord      (int ccode);
extern void MMMlib_KillEnd       (int ccode);
extern void MMMlib_KillBeg       (int ccode);
extern void MMMlib_CSave         (int ccode);
extern void MMMlib_CMove         (int ccode);
extern void MMMlib_WSave         (int ccode);
extern void MMMlib_WMove         (int ccode);
extern void MMMlib_BWord         (int ccode);
extern void MMMlib_TSave         (int ccode);
extern void MMMlib_TMove         (int ccode);
extern void MMMlib_CRest         (int ccode);
extern void MMMlib_CClear        (int ccode);
extern void MMMlib_LSave         (int ccode);
extern void MMMlib_LTSave        (int ccode);
extern void MMMlib_LMove         (int ccode);
extern void MMMlib_LTMove        (int ccode);
extern void MMMlib_LRest         (int ccode);
extern void MMMlib_LClear        (int ccode);
extern void MMMlib_Escape        (int ccode);
extern void MMMlib_EscapeExec    (int ccode);
extern void MMMlib_EscapeExecLCB (int ccode);
extern void MMMlib_ABORT         (int ccode);
extern void MMMlib_S_AutoIndent  (int ccode);
extern void MMMlib_S_ModeIns     (int ccode);
extern void MMMlib_S_ModeOvr     (int ccode);
extern void MMMlib_S_ACode1      (int ccode);
extern void MMMlib_S_ACode2      (int ccode);
extern void MMMlib_S_ACode3      (int ccode);
extern void MMMlib_S_StatusLine  (int ccode);
extern void MMMlib_S_SearchMode  (int ccode);
extern void MMMlib_SearchFWD     (int ccode);
extern void MMMlib_SearchBCK     (int ccode);
extern void MMMlib_Replace       (int ccode);
extern void MMMlib_SearchPage    (int ccode);
extern void MMMlib_PageIns       (int ccode);
extern void MMMlib_MarkUp        (int ccode);
extern void MMMlib_MarkDown      (int ccode);
extern void MMMlib_MarkTUp       (int ccode);
extern void MMMlib_MarkTDown     (int ccode);
extern void MMMlib_MarkPUp       (int ccode);
extern void MMMlib_MarkPDown     (int ccode);
extern void MMMlib_MarkSaveB     (int ccode);
extern void MMMlib_MarkRestB     (int ccode);
extern void MMMlib_MarkLast      (int ccode);
extern void MMMlib_MarkFirst     (int ccode);
extern void MMMlib_MarkPrev      (int ccode);
extern void MMMlib_MarkNext      (int ccode);
extern void MMMlib_MarkBS        (int ccode);
extern void MMMlib_Macro         (int ccode);
extern void MMMlib_MacroRec      (int ccode);
extern void MMMlib_Console       (int ccode);

//&>>&10 0 10 14

//&<<&struct EDITOR
//&<<&Attributes
enum{
   _TextAttr,
   _CurAttr,
   _FoldAttr,
   _CurFoldAttr,
   _MarkedAttr,
   _CurMarkedAttr,
   _FoldMarkedAttr,
   _StatusLineAttr,
    NAttr};


#define TextAttr       attrs[_TextAttr       ]
#define CurAttr        attrs[_CurAttr        ]
#define FoldAttr       attrs[_FoldAttr       ]
#define CurFoldAttr    attrs[_CurFoldAttr    ]
#define MarkedAttr     attrs[_MarkedAttr     ]
#define CurMarkedAttr  attrs[_CurMarkedAttr  ]
#define FoldMarkedAttr attrs[_FoldMarkedAttr ]
#define StatusLineAttr attrs[_StatusLineAttr ]

extern int MonoAttrs[];

//&>>&0 0 0 0
//&<<&PARAMETERS
enum{
   _InsFlag,
   _IndFlag,
   _ShowStatusLineFlag,
   _SearchMode,
    NParams};

#define InsFlag             Params[ _InsFlag            ]
#define IndFlag             Params[ _IndFlag            ]
#define ShowStatusLineFlag  Params[ _ShowStatusLineFlag ]
#define SearchMode          Params[ _SearchMode         ]
//&>>&B 0 B 4
struct EDITOR{
    char *InitialDir;
    char *ConfigFileName;        // name of config file
    char *CurrentFileName;
    int NumberOfPages;
    int CurrentDepth;        // Depth of current fold in current file
    int IsInSearchFold;
    int Attrs[NAttr];
    int *attrs;
    int Params[NParams];

    EDITOR();
    ~EDITOR();
    void InitUserSetup();
    void InitEditorSetup();
    void InitFirstPage();
//&<<&    SetDefaultAttributes(){
void SetDefaultAttributes(){
    TextAttr=7;
    CurAttr=0xf0;
    FoldAttr=0x0f;
    CurFoldAttr=0xf0;
    MarkedAttr=0x17;
    CurMarkedAttr=0xf0;
    FoldMarkedAttr=0x1f;
    StatusLineAttr=0x7f;
    InsFlag=1;
    IndFlag=1;
    ShowStatusLineFlag=1;
    SearchMode=1;
};
//&>>&0 0 0 13

    int nExt;
    char **FileExt;
    char **FileCmt;
    int IsComment(char *buf,char *ptrn);
    void SetComment(char *n);
    void Init_ExtensionsFold2Mem(Fold *ExtFold);

    void Init_keymapFold2Mem(FILE *fptr);

    void Init_SetupFold2Mem(FILE *fptr);

    void Init_CommandFold2Mem(FILE *fptr);
    void Init_MacroFold2Mem(char *str);

    };
//&>>&20 0 19 25
extern EDITOR Editor;

//&<<&struct Line;
struct Line{
    Line *prev;
    Line *next;
    char *buf;
    short lbuf, fchg, marked, type;
    long linenumber;


    Line(char *s);
    virtual ~Line();
    virtual Fold *Enter(){ return 0; }
    void UnLink();
    Line *LinkBefore(Line *);
    virtual Line *Copy(int cln=0);
    void Realloc(int);
    virtual void Write(FILE *f,int flg);
    virtual int GetTextAttr(){ return (marked)?Editor.MarkedAttr:Editor.TextAttr; }
    virtual int GetCurAttr(){ return (marked)?Editor.CurMarkedAttr:Editor.CurAttr; }
    virtual char *GetEnd(){ return ""; }
    char *Buf(int x){ return x>=lbuf ? "" : buf+x; }

    void InsChar(int cx);
    void DelChar(int cx);
    void SetChar(int cx,char c);

    char *GetWord(int cx);
    char *GetFileName(int cx);

    };
//&>>&5 0 5 0
//&<<&struct Fold;
struct Fold:Line{
    Fold *top;
    Line *pos;
    int sx,sy,cx;

    Fold(char *buf):Line(buf),pos(NewLine(0)),sx(0),sy(0),cx(0){}
    ~Fold();
    void Read(FILE *f,int flg);
    void Write(FILE *f,int flg);
    virtual Fold *Exit(){ return top; }
    Fold *Enter(){ return this; }
    Line *Copy(int cln=0);
    void Draw();
    void DrawStatusLine();
    virtual int GetTextAttr(){ return marked?Editor.FoldMarkedAttr:Editor.FoldAttr; }
    virtual int GetCurAttr(){ return marked?Editor.CurMarkedAttr:Editor.CurFoldAttr; }
    virtual char *GetEnd(){ return "[* End of Fold *]"; }
    virtual char *FileName(){ return 0; }
    virtual int IsFile(){ return 0; }
    virtual char *CurDirName(){ return 0; }
    virtual unsigned int CurDevNum(){ return 0; }

    int HasChange();
    Fold *FindCont(int SearchDirection,int fcur,int ft);

  // COMMANDS

    void Ascii(int code);
    friend Fold *NewFold(char *buf,unsigned long LinCnt=0);
    void InsLine(){ pos=NewLine("")->LinkBefore(pos); pos->fchg=LINE_NEW; Redr(); }
    void InsFold(){ pos=NewFold("")->LinkBefore(pos); pos->fchg=LINE_NEW; Redr(); }
    void DelLine();
    void InsCh();
    void DelCh();
    void Left(){ if(cx) cx--; }
    void Right(){ if(cx<INFTY) cx++; }
//&<<&    void Up,TUp,PUp,Down,TDown,PDown
  void Up(int DoMarkLine=0);
  void TUp(int DoMarkLine=0);
  void PUp(int DoMarkLine=0);
  void Down(int DoMarkLine=0);
  void TDown(int DoMarkLine=0);
  void PDown(int DoMarkLine=0);
//&>>&4 0 4 0
    void TLeft(){ cx=0; }
    void TRight();
    void BWord(),FDown(int IsNewPage);
    void BackSpace();
    void _Enter();
    void Tab(){ cx=(cx|TAB_STEP_SIZE)+1; }
    void LTab(){ if(cx) cx=(cx-1)&~TAB_STEP_SIZE; }

    void MarkLine();

    void LSave(int),LRest(),LMove(int),LRest1();
    void CRest(),CCopy(int),WCopy(int),TCopy(int),MoveCh(int);
    char GetCh();

    void KillEnd(),KillBeg();

    Line *TestTopOfTheStackIsInt(); // used by Mathop & Predicate.
    void stackMathOperation();
    void stackPredicate();
    void stackSwp();
    void stackDel();
    void stackDup();
    void stackSget();
    void stackSput();
    void stackQuery();
    void stackConvert();
    void stackPop();
    void stackPush();
    void stackIOCTL();
    };

//&>>&21 0 0 12
//&<<&struct File;
struct File:Fold{
    char *CurDir;
    unsigned int CurDev;
    int flg;

    File(char *name,int fx);
    Fold *Exit();
    virtual int GetTextAttr(){ return Editor.TextAttr; }
    virtual int GetCurAttr(){ return Editor.CurAttr; }
    virtual char *GetEnd(){ return "[* End of File *]"; }
    virtual char *FileName();
    virtual int IsFile(){ return 1; }
//&<<&    virtual char *CurDirName(){
  virtual char *CurDirName(){
         if(!CurDir)return 0;
         char *xx=new char[strlen(CurDir)+1];
         MemTest(xx!=0);
         strcpy(xx,CurDir);
         return xx;
         }
//&>>&2 0 2 1A
    virtual unsigned int CurDevNum(){ return CurDev; }
    void MkWild();
    };
//&>>&F 0 F 4
//&<<&struct MarkedLine:Line{
struct MarkedLine:Line{
  Line *ref;
  int pcb,qcb;
  MarkedLine(char *name):Line(name),ref(0),pcb(0),qcb(0){}
  MarkedLine *Next(){ return (MarkedLine *)next; }
  MarkedLine *Prev(){ return (MarkedLine *)prev; }
  void ConnectMark(Line *cpos);
  void ConnectUnMark();
  void AddCcb(char c);
//&<<&  char GetCh();
char GetCh(){
  return cur->cx>=ref->lbuf ? 0 : ref->buf[cur->cx];
  }
//&>>&2 0 2 2
};
extern void FirstMarked();
extern void LastMarked();
extern void NextMarked();
extern void PrevMarked();
extern void SaveMarkedBlock();
extern void RestMarkedBlock();
//&>>&0 0 0 0
//&<<&struct Chain     /// Knows about 'cur' and 'Fold::Exit()' func.
struct Chain{
Chain *next,*prev;
Fold *entry;

Chain():next(0),prev(0),entry(0){}
Chain(Fold *ie):next(0),prev(0){entry=ie;}
void UnLink();
Chain *LinkBefore(Chain *f);
Chain *PageNext();
Chain *PagePrev();
void   PageUnlink();   // with Complete quiting
};
//&>>&0 0 0 0

//&<<&struct TPair_String_Function {
struct TPair_String_Function {
    char *fName;
    void (*fRef)(int);

//&<<&    TPair_String_Function(char *_name, void (*_ref)(int) ){
    TPair_String_Function(char *_name, void (*_ref)(int) ){
        fName= _name;
        fRef = _ref ;
        }
//&>>&0 0 0 19
    };
//&>>&5 0 5 8
//&<<&struct TPair_String_Int {
struct TPair_String_Int {
    char *fName;
    int  iValue;

//&<<&    TPair_String_Int (char *_name, int _ivalue ) {
    TPair_String_Int (char *_name, int _ivalue ) {
        fName  = _name ;
        iValue = _ivalue ;
        }
//&>>&0 0 0 14
    };

extern int fPair_String2Int(TPair_String_Int psArr[]  ,int len, char *pcNam);
extern char *fPair_Int2String(TPair_String_Int psArr[],int len, int iIdx );

//&>>&8 0 8 0
//&<<&struct TMacro {
struct TMacro {
    short *base;
    int lbase;

    TMacro(){ base=0; lbase=0; }
    ~TMacro() { if(base)delete base; }
    short &operator[](int idx);
    };
//&>>&5 0 5 0
//&<<&struct TCommandUsr {
struct TCommandUsr {
    char *fName;
    TMacro fCode;

    TCommandUsr() { fName=0; }

    int Execute(int arg);
    };
//&>>&5 0 5 0
//&<<&struct TCommandUsrArray {

struct TCommandUsrArray {
    TCommandUsr *base;
    int lbase;

    TCommandUsrArray (){ base=0; lbase=0; }
//    ~TCommandUsrArray(){ if(base!=0)delete base; }

    int AddEntry(char *_fname, TMacro *_fcode=0);
    };
//&>>&6 0 6 2
//&<<&struct TKeyArray {
//&<<&struct TKey {
struct TKey {
    int scan;
    int fnum;

    TKey() { scan= fnum= -1; }
    };
//&>>&4 0 4 11
struct TKeyArray {
    TKey *base;
    int lbase;

    TKeyArray(){ base=0; lbase=0; }
//    ~TKeyArray(){ if(base!=0)delete base; }
    int AddEntry(int _scan, int _fnum);
    };
//&>>&6 0 6 0

#endif
//// mmmx.err mmmx.err mmmx.err mmmx.err mmmx.err mmmx.err
//&>>&18 0 18 8
