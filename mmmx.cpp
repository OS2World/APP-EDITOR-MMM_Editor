/**********************************************
***********************************************
***  Main Editor file, contains commands,   ***
***  macro-language & setup stuff           ***
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

//&>>&10 0 10 16

//&<<&Global class elements     !!!!!!  UN-EDIT-ABLE  !!!!!!
//&<<&TPair_String_Function CommandArray[LEN_COMMAND_ARRAY]={  /// the first (before editor)
    TPair_String_Function CommandArray[LEN_COMMAND_ARRAY]={
        TPair_String_Function ( "Ascii0"        , MMMlib_Ascii0        ) ,
        TPair_String_Function ( "Ascii1"        , MMMlib_Ascii1        ) ,
        TPair_String_Function ( "Ascii2"        , MMMlib_Ascii2        ) ,
        TPair_String_Function ( "Space"         , MMMlib_Space         ) ,
        TPair_String_Function ( "Up"            , MMMlib_Up            ) ,
        TPair_String_Function ( "Down"          , MMMlib_Down          ) ,
        TPair_String_Function ( "Left"          , MMMlib_Left          ) ,
        TPair_String_Function ( "Right"         , MMMlib_Right         ) ,
        TPair_String_Function ( "TUp"           , MMMlib_TUp           ) ,
        TPair_String_Function ( "TDown"         , MMMlib_TDown         ) ,
        TPair_String_Function ( "TLeft"         , MMMlib_TLeft         ) ,
        TPair_String_Function ( "TRight"        , MMMlib_TRight        ) ,
        TPair_String_Function ( "PUp"           , MMMlib_PUp           ) ,
        TPair_String_Function ( "PDown"         , MMMlib_PDown         ) ,
        TPair_String_Function ( "FUp"           , MMMlib_FUp           ) ,
        TPair_String_Function ( "FDown"         , MMMlib_FDown         ) ,
        TPair_String_Function ( "FLeft"         , MMMlib_FLeft         ) ,
        TPair_String_Function ( "FRight"        , MMMlib_FRight        ) ,
        TPair_String_Function ( "Enter"         , MMMlib_Enter         ) ,
        TPair_String_Function ( "Tab"           , MMMlib_Tab           ) ,
        TPair_String_Function ( "LTab"          , MMMlib_LTab          ) ,
        TPair_String_Function ( "InsCh"         , MMMlib_InsCh         ) ,
        TPair_String_Function ( "DelCh"         , MMMlib_DelCh         ) ,
        TPair_String_Function ( "InsLine"       , MMMlib_InsLine       ) ,
        TPair_String_Function ( "InsFold"       , MMMlib_InsFold       ) ,
        TPair_String_Function ( "DelLine"       , MMMlib_DelLine       ) ,
        TPair_String_Function ( "BS"            , MMMlib_BS            ) ,
        TPair_String_Function ( "KillEnd"       , MMMlib_KillEnd       ) ,
        TPair_String_Function ( "KillBeg"       , MMMlib_KillBeg       ) ,
        TPair_String_Function ( "CSave"         , MMMlib_CSave         ) ,
        TPair_String_Function ( "CMove"         , MMMlib_CMove         ) ,
        TPair_String_Function ( "WSave"         , MMMlib_WSave         ) ,
        TPair_String_Function ( "WMove"         , MMMlib_WMove         ) ,
        TPair_String_Function ( "BWord"         , MMMlib_BWord         ) ,
        TPair_String_Function ( "TSave"         , MMMlib_TSave         ) ,
        TPair_String_Function ( "TMove"         , MMMlib_TMove         ) ,
        TPair_String_Function ( "CRest"         , MMMlib_CRest         ) ,
        TPair_String_Function ( "CClear"        , MMMlib_CClear        ) ,
        TPair_String_Function ( "LSave"         , MMMlib_LSave         ) ,
        TPair_String_Function ( "LTSave"        , MMMlib_LTSave        ) ,
        TPair_String_Function ( "LMove"         , MMMlib_LMove         ) ,
        TPair_String_Function ( "LTMove"        , MMMlib_LTMove        ) ,
        TPair_String_Function ( "LRest"         , MMMlib_LRest         ) ,
        TPair_String_Function ( "LClear"        , MMMlib_LClear        ) ,
        TPair_String_Function ( "Escape"        , MMMlib_Escape        ) ,
        TPair_String_Function ( "EscapeExec"    , MMMlib_EscapeExec    ) ,
        TPair_String_Function ( "EscapeExecLCB" , MMMlib_EscapeExecLCB ) ,
        TPair_String_Function ( "ABORT"         , MMMlib_ABORT         ) ,
        TPair_String_Function ( "S_AutoIndent"  , MMMlib_S_AutoIndent  ) ,
        TPair_String_Function ( "S_ModeIns"     , MMMlib_S_ModeIns     ) ,
        TPair_String_Function ( "S_ModeOvr"     , MMMlib_S_ModeOvr     ) ,
        TPair_String_Function ( "S_ACode1"      , MMMlib_S_ACode1      ) ,
        TPair_String_Function ( "S_ACode2"      , MMMlib_S_ACode2      ) ,
        TPair_String_Function ( "S_ACode3"      , MMMlib_S_ACode3      ) ,
        TPair_String_Function ( "S_StatusLine"  , MMMlib_S_StatusLine  ) ,
        TPair_String_Function ( "S_SearchMode"  , MMMlib_S_SearchMode  ) ,
        TPair_String_Function ( "SearchFWD"     , MMMlib_SearchFWD     ) ,
        TPair_String_Function ( "SearchBCK"     , MMMlib_SearchBCK     ) ,
        TPair_String_Function ( "Replace"       , MMMlib_Replace       ) ,
        TPair_String_Function ( "SearchPage"    , MMMlib_SearchPage    ) ,
        TPair_String_Function ( "PageIns"       , MMMlib_PageIns       ) ,
        TPair_String_Function ( "MarkUp"        , MMMlib_MarkUp        ) ,
        TPair_String_Function ( "MarkDown"      , MMMlib_MarkDown      ) ,
        TPair_String_Function ( "MarkTUp"       , MMMlib_MarkTUp       ) ,
        TPair_String_Function ( "MarkTDown"     , MMMlib_MarkTDown     ) ,
        TPair_String_Function ( "MarkPUp"       , MMMlib_MarkPUp       ) ,
        TPair_String_Function ( "MarkPDown"     , MMMlib_MarkPDown     ) ,
        TPair_String_Function ( "MarkSaveB"     , MMMlib_MarkSaveB     ) ,
        TPair_String_Function ( "MarkRestB"     , MMMlib_MarkRestB     ) ,
        TPair_String_Function ( "MarkLast"      , MMMlib_MarkLast      ) ,
        TPair_String_Function ( "MarkFirst"     , MMMlib_MarkFirst     ) ,
        TPair_String_Function ( "MarkPrev"      , MMMlib_MarkPrev      ) ,
        TPair_String_Function ( "MarkNext"      , MMMlib_MarkNext      ) ,
        TPair_String_Function ( "MarkBS"        , MMMlib_MarkBS        ) ,
        TPair_String_Function ( "Macro"         , MMMlib_Macro         ) ,
        TPair_String_Function ( "MacroRec"      , MMMlib_MacroRec      ) ,
        TPair_String_Function ( "Console"       , MMMlib_Console       )
        };
//&>>&14 0 D 30
TKeyArray KeyArray;                /// the second (before editor)
TCommandUsrArray CommandUsrArray;  /// also before editor
EDITOR Editor;                     ///  must be the last destructor
mmm_Screen mmm_screen;             /// must be !!BEFORE!! mmm_KBD, bcause of con_fd opening
mmm_KeyBoard mmm_KBD;              ///      in mmm_Screen::mmm_Screen()
//&>>&0 0 0 1C

//&<<&Forward_declarations

//&<<&void MemTest(int i){
void MemTest(int i){
    if(i)return;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("                ........TestMem(%x (%x))\n",i,MinimalExitFromEditor);
    #endif
//&>>&1 0 1 8
    Beep();
    Beep();
    if(MinimalExitFromEditor) abort();
    MinimalExitFromEditor=1;
    exit(1);
    }
//&>>&0 0 0 14
//&<<&void Redr(int LineToRedraw)
void Redr(int LineToRedraw){
    if(mmm_screen.Need()<LineToRedraw)
        mmm_screen.Need()=LineToRedraw;
    }
//&>>&2 0 2 12
//&<<&int lower(int c){
int lower(int c){
    if(c>='A' && c<='Z') return c+'a'-'A';
    return c;
    }
//&>>&0 0 0 1A
//&<<&char *getcurdir(int f){  // f -- reread current directory
static char pcGCD_SavedDir[256]="";
unsigned int iGCD_SavedDev=(unsigned int)-1;

//&<<&int SaveGetDrive()
int SaveGetDrive()
    { return iGCD_SavedDev; }
//&>>&1 0 1 1A
//&<<&void SaveChDir(char *s){
void SaveChDir(char *s){
  if(strcmp(s,pcGCD_SavedDir)==0) return;
  chdir(s);
  getcwd(pcGCD_SavedDir,255);
}
//&>>&3 0 3 17
//&<<&void SaveSetDrive(unsigned int n){
void SaveSetDrive(unsigned int n){
  if(iGCD_SavedDev==n) return;
  iGCD_SavedDev=n;
  unsigned int t;
  _dos_setdrive(n,&t);
  getcwd(pcGCD_SavedDir,255);
}

//&>>&2 0 2 F
//&<<&unsigned int GetSavedDev(){
unsigned int GetSavedDev(){
    unsigned int sd;
    _dos_getdrive(&sd);
    return sd;
    }
//&>>&0 0 0 18

char *getcurdir(int f){
    if(f){
        char *d=new char[strlen(pcGCD_SavedDir)+1];
        strcpy(d,pcGCD_SavedDir);
        return d;
        }else return pcGCD_SavedDir;
    }

//&>>&0 0 0 1B

//&>>&0 0 0 4
//&<<&Constants and variables
int MinimalExitFromEditor=0;

char *templine;    // line to be used as temporary strings storage

int fRecordingMacro=0;

Fold *RuntimeStack=NewFold(0);
long RuntimeFlag;

//&>>&7 0 7 3

//&<<&Commands in Canonical form
TMacro *my_macroF7=0;  int my_macroF7_ptr=0; /// I must Remove it out of here

//&<<&Movement
// Movement
void MMMlib_Up     (int ccode) { cur->Up   ();    }
void MMMlib_Down   (int ccode) { cur->Down ();    }
void MMMlib_Left   (int ccode) { cur->Left ();    }
void MMMlib_Right  (int ccode) { cur->Right();    }

void MMMlib_TUp    (int ccode) { cur->TUp   ();   }
void MMMlib_TDown  (int ccode) { cur->TDown ();   }
void MMMlib_TLeft  (int ccode) { cur->TLeft ();   }
void MMMlib_TRight (int ccode) { cur->TRight();   }

void MMMlib_PUp    (int ccode) { cur->PUp   ();   }
void MMMlib_PDown  (int ccode) { cur->PDown ();   }

void MMMlib_FUp    (int ccode) { _EXIT(0);        }
void MMMlib_FDown  (int ccode) { cur->FDown (0);  }
//&<<&void MMMlib_FLeft  (int ccode) {
void MMMlib_FLeft (int ccode) {
        if(Editor.IsInSearchFold)return;
        CurrentPage=CurrentPage->PagePrev();
        GetCurrentFileNameAndDepth();
        Redr();
        }
//&>>&2 0 2 8
//&<<&void MMMlib_FRight (int ccode) {
void MMMlib_FRight (int ccode) {
    if(Editor.IsInSearchFold)return;
    CurrentPage=CurrentPage->PageNext();
    GetCurrentFileNameAndDepth();
    Redr();
    }
//&>>&0 0 0 C

void MMMlib_Enter  (int ccode) { cur->_Enter();   }
void MMMlib_Tab    (int ccode) { cur->Tab();      }
void MMMlib_LTab   (int ccode) { cur->LTab();     }

//&>>&14 0 14 0
//&<<&Insert and delete
// Insert and delete
void MMMlib_InsCh   (int ccode) { cur->InsCh  ();  }
void MMMlib_DelCh   (int ccode) { cur->DelCh  ();  }
void MMMlib_InsLine (int ccode) { cur->InsLine();  }
void MMMlib_InsFold (int ccode) { cur->InsFold();  }
void MMMlib_DelLine (int ccode) { cur->DelLine();  }
void MMMlib_BS      (int ccode) { cur->BackSpace();}

//&>>&7 0 7 0
//&<<&Characters/Digits/delimiters Typing
//&<<&void MMMlib_Ascii0   (int ccode) {     // for digits
void MMMlib_Ascii0   (int ccode) {   // for digits
    int code=ccode & 0xff;
    int p_alt=(ccode & 0x200)>>8;
    int p_shift=(ccode & 0x100)>>8;
    cur->Ascii(( p_alt ? acode : mcode)[code*2+p_shift]);
    }
//&>>&1 0 1 1A
//&<<&void MMMlib_Ascii1   (int ccode) {     // for letters 
void MMMlib_Ascii1   (int ccode) {  // for letters
    int code=ccode & 0xff;
    int p_alt=(ccode & 0x200)>>8;
    int p_shift=(ccode & 0x100)>>8;
    cur->Ascii(( p_alt ? acode : mcode)[code*2+p_shift]);
    }
//&>>&1 0 1 19
//&<<&void MMMlib_Ascii2   (int ccode) {     // for delimiters
void MMMlib_Ascii2   (int ccode) {     // for delimiters
    int code=ccode & 0xff;
    int p_alt=(ccode & 0x200)>>8;
    int p_shift=(ccode & 0x100)>>8;
    cur->Ascii( p_alt ? acode[code*2+ p_shift ] : mcode[code*2+p_shift]);  return;
    }
//&>>&1 0 1 0
void MMMlib_Space    (int ccode) { cur->Ascii(' '); }
//&>>&0 0 0 32
//&<<&Line Killing
// Line Killing
void MMMlib_KillEnd  (int ccode) {   cur->KillEnd();  }
void MMMlib_KillBeg  (int ccode) {   cur->KillBeg();  }
//&>>&1 0 1 C
//&<<&Copying of chars
// Copying of chars
void MMMlib_CSave    (int ccode) { cur->CCopy(0); }
void MMMlib_CMove    (int ccode) { cur->CCopy(1); }
void MMMlib_WSave    (int ccode) { cur->BWord(); cur->WCopy(0); }
void MMMlib_WMove    (int ccode) { cur->BWord(); cur->WCopy(1); }
void MMMlib_BWord    (int ccode) { cur->BWord(); }
void MMMlib_TSave    (int ccode) { cur->TCopy(0); }
void MMMlib_TMove    (int ccode) { cur->TCopy(1); }
void MMMlib_CRest    (int ccode) { cur->CRest(); }
void MMMlib_CClear   (int ccode) { CClear(); }
//&>>&9 0 9 C
//&<<&Copying of lines

void MMMlib_LSave    (int ccode) { cur->LSave(0); }
void MMMlib_LTSave   (int ccode) { cur->LSave(1); }
void MMMlib_LMove    (int ccode) { cur->LMove(0); }
void MMMlib_LTMove   (int ccode) { cur->LMove(1); }
void MMMlib_LRest    (int ccode) { cur->LRest();  }
void MMMlib_LClear   (int ccode) { LClear();  }
//&>>&6 0 6 C
//&<<&Various types of exit
// Various types of exit
void MMMlib_Escape        (int ccode) { LClear(); __EXIT(); }
void MMMlib_EscapeExec    (int ccode) { LClear(); cur->LSave(0); __EXIT(); }
void MMMlib_EscapeExecLCB (int ccode) { __EXIT(); }
//&<<&void MMMlib_ABORT         (int ccode) {
void MMMlib_ABORT         (int ccode) {
    MinimalExitFromEditor=1;
    exit(1);
    }
//&>>&0 0 0 C

//&>>&4 0 4 C
//&<<&Various switchings  (ins/ovr , alt key , status line .........)
// Various switchings  (ins/ovr , alt key , status line .........)
void MMMlib_S_AutoIndent (int ccode) { Editor.IndFlag^=1; }
void MMMlib_S_ModeIns    (int ccode) { Editor.InsFlag=1; }
void MMMlib_S_ModeOvr    (int ccode) { Editor.InsFlag=0; }
void MMMlib_S_ACode1     (int ccode) { mmm_KBD.SetACode(1); }
void MMMlib_S_ACode2     (int ccode) { mmm_KBD.SetACode(2); }
void MMMlib_S_ACode3     (int ccode) { mmm_KBD.SetACode(3); }
void MMMlib_S_StatusLine (int ccode) { Editor.ShowStatusLineFlag^=1; Redr(); }
void MMMlib_S_SearchMode (int ccode) { Editor.SearchMode^=1; }

//&>>&6 0 6 2E
//&<<&Search & replace commands
// Search & replace commands
void MMMlib_SearchFWD  (int ccode) { SearchReplaceTextFragment(SEARCH_FORWARD); }
void MMMlib_SearchBCK  (int ccode) { SearchReplaceTextFragment(SEARCH_BACK); }
void MMMlib_Replace    (int ccode) { SearchReplaceTextFragment(SEARCH_FORWARD,1); }
void MMMlib_SearchPage (int ccode) { SwitchIntoSearchPage(); }
//&>>&4 0 4 C
void MMMlib_PageIns (int ccode) { cur->FDown(1); }
//&<<&Marked Lines Commands
void MMMlib_MarkUp    (int ccode) { cur->Up   (1); }
void MMMlib_MarkDown  (int ccode) { cur->Down (1); }
void MMMlib_MarkTUp   (int ccode) { cur->TUp  (1); }
void MMMlib_MarkTDown (int ccode) { cur->TDown(1); }
void MMMlib_MarkPUp   (int ccode) { cur->PUp  (1); }
void MMMlib_MarkPDown (int ccode) { cur->PDown(1); }
void MMMlib_MarkSaveB (int ccode) { SaveMarkedBlock(); }
void MMMlib_MarkRestB (int ccode) { RestMarkedBlock(); }
void MMMlib_MarkLast  (int ccode) { LastMarked();      }
void MMMlib_MarkFirst (int ccode) { FirstMarked();     }
void MMMlib_MarkPrev  (int ccode) { PrevMarked();      }
void MMMlib_MarkNext  (int ccode) { NextMarked();      }
void MMMlib_MarkBS    (int ccode) { LastMarked();  cur->MarkLine(); }

//&>>&C 0 C C
//&<<&MacroCommands
void MMMlib_Macro(int ccode){

    static int i=-1;
    if(fRecordingMacro){
        fRecordingMacro=0;
        (*my_macroF7)[my_macroF7_ptr-1]=0;
        i=CommandUsrArray.AddEntry("MacroF7",my_macroF7);
        return;
        }
    CommandUsrArray.base[i].Execute(ccode);
    }

void MMMlib_MacroRec(int ccode){
    if(my_macroF7!=0)delete my_macroF7;
    my_macroF7=new TMacro;
    fRecordingMacro=1;
    (*my_macroF7)[0]=MACRO_KEYSEQ;
    my_macroF7_ptr=1;
    }
//&>>&9 0 9 0

//&>>&2 0 2 1A

//&<<&TCommand.. / TKey / TMacro / TPair_String_Int
//&<<&int TKeyArray::AddEntry(int _scan, int _fnum){
int TKeyArray::AddEntry(int _scan, int _fnum){
    int i;
    for(i=0; i<lbase ; i++){
        if(base[i].fnum==-1) goto l_ka_InsertData;
        }

    TKey *base1;
    lbase+=0x100;
    base1=new TKey[lbase]; MemTest(base1!=0);
    if(base!=0){
        memcpy(base1, base, i * sizeof(TKey) );
        delete base;
        }
    base=base1;

l_ka_InsertData:
    base[i].scan   = _scan   ;
    base[i].fnum   = _fnum   ;
    return i;
    }
//&>>&0 0 0 5
//&<<&int TCommandUsrArray::AddEntry(char *_fname, TMacro *_fcode) {
int TCommandUsrArray::AddEntry(char *_fname, TMacro *_fcode) {

// TCommandUsr {
//     char *fName;
//     short *fCode; };

// концом вектора считается ф-я без имени (fName==0)

    int i,j;
    for(i=0; i<lbase ; i++){
        if(base[i].fName==0)                 goto l_cua_InsertName;
        if(strcmp(base[i].fName, _fname)==0) goto l_cua_InsertContents;
        }

    TCommandUsr *base1;
    lbase+=0x100;
    base1=new TCommandUsr[lbase]; MemTest(base1!=0);
    if(base!=0){
        memcpy(base1, base, i * sizeof(TCommandUsr) );
        delete base;
        }
    base=base1;

l_cua_InsertName:
    base[i].fName=new char[strlen(_fname)+1];  MemTest( base[i].fName!=0 );
    strcpy (base[i].fName , _fname );

l_cua_InsertContents:
    if(_fcode!=0){
        for(j=0;j<_fcode->lbase;j++){
            base[i].fCode[j]=(*_fcode)[j];
            }
        }

//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
    {
        DoLog("TCommandUsrArray::AddEntry(char *_fname, TMacro *_fcode) {\n");
        DoLog("    fname=%s\n    Entry=\n",_fname);
        if(_fcode!=0){
            for(int pppp=0;(*_fcode)[pppp]!=0;pppp++)
                DoLog("        %4d->%4x\n",pppp,(*_fcode)[pppp]);
            }
    }
    #endif
//&>>&4 0 4 0
    return i;
    }
//&>>&0 0 0 0

//&<<&short &TMacro::operator[](int idx) {
short &TMacro::operator[](int idx) {
    if(idx>=lbase){
        int i;
        short *base1;
        lbase+=0x10;
        base1=new short[lbase]; MemTest(base1!=0);
        if(base!=0){
            memcpy(base1, base, (lbase-0x10) * sizeof(short) );
            delete base;
            }
        base=base1;
        for(i=lbase-0x10;i<lbase;i++) base[i]=0;
        }
    return base[idx];
    }
//&>>&1 0 1 12
//&<<&int TCommandUsr::Execute(int arg){
int TCommandUsr::Execute(int arg) {
    int pc;
    if(fCode.base==0)return -1;
    switch(fCode[0]){
        case MACRO_PROC:
//&<<&            #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("Procedure <%s>execution {\n",fName);
            #endif
//&>>&1 0 1 1A
            for(pc=1; fCode[pc]!=0 && fCode[pc]!=TKN_RETURN_ ; pc++) {
//&<<&                #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("[%x->%x] ",pc,fCode[pc]);
            #endif
//&>>&1 0 1 22
//&<<&                if(fCode[pc]<LEN_LANGUAGE){     // if, do, ... analisys
        if(fCode[pc]>=0 && fCode[pc]<LEN_LANGUAGE){
            Line *nl;
//            char *tpc;
            int i,l;
            switch(fCode[pc]){
                case TKN_GOTO_:
                    pc=fCode[pc+1]-1;
                    break;
                case TKN_IF_:
                    if(RuntimeFlag) pc++;
                    else pc=fCode[pc+1]-1;
                    break;
//&<<&                case TKN_CONST_INT_:
                case TKN_CONST_INT_:
                    nl=NewLine(0);
                    nl->linenumber=fCode[++pc];
                    nl->type=SDATA_INT;
                    nl->LinkBefore(RuntimeStack->pos);
                    RuntimeStack->pos=nl;
                    break;
//&>>&7 0 7 15
//&<<&                case TKN_CONST_STRING_:
                case TKN_CONST_STRING_:
                    templine=new char[(l=fCode[++pc])+1]; MemTest(templine!=0);
                    for(i=0;i<l;i++)templine[i]=char(fCode[++pc]);
                    templine[i]=0;
                    nl=NewLine(templine);
                    delete templine;
                    nl->type=SDATA_STRING;
                    nl->LinkBefore(RuntimeStack->pos);
                    RuntimeStack->pos=nl;
                    break;

//&>>&1 0 1 4D
                case TKN_SWP_ :
                    RuntimeStack->stackSwp();
                    break;
                case TKN_DUP_ :
                    RuntimeStack->stackDup();
                    break;
                case TKN_DEL_ :
                    RuntimeStack->stackDel();
                    break;
                case TKN_SGET_:
                    RuntimeStack->stackSget();
                    break;
                case TKN_SPUT_:
                    RuntimeStack->stackSput();
                    break;
                case TKN_POP_:
                    RuntimeStack->stackPop();
                    break;
                case TKN_PUSH_:
                    RuntimeStack->stackPush();
                    break;
                case TKN_CONVERT_:
                    RuntimeStack->stackConvert();
                    break;
                case TKN_MATHOP_:
                    RuntimeStack->stackMathOperation();
                    break;
                case TKN_PREDICATE_:
                    RuntimeStack->stackPredicate();
                    break;
                case TKN_IOCTL_:
                    RuntimeStack->stackIOCTL();
                    break;
                case TKN_QUERY_:
                    RuntimeStack->stackQuery();
                    break;
                }
            // here must be analisys of Language Constructions
            //          if , do , ...
            // HERE "pc" may be modifyed
            continue;
            }
//&>>&A 0 A 0
//&<<&                if(fCode[pc]>=LEN_LANGUAGE && fCode[pc]<USER_FUNC){ // MMMlib
        if(fCode[pc]>=LEN_LANGUAGE && fCode[pc]<USER_FUNC){
            CommandArray[fCode[pc]-LEN_LANGUAGE].fRef(arg);
            continue;
            }
//&>>&1 0 1 0
//&<<&                if(fCode[pc]>=USER_FUNC && fCode[pc]<USER_FUNC+CommandUsrArray.lbase ) {
        if(fCode[pc]>=USER_FUNC && fCode[pc]<USER_FUNC+CommandUsrArray.lbase ){
            arg=CommandUsrArray.base[fCode[pc]-USER_FUNC].Execute(arg);
            continue;
            }
//&>>&1 0 1 12
                }
//&<<&            #ifdef _ENABLE_LOGGING_
            #ifdef _ENABLE_LOGGING_
                DoLog("    }complete.\n");
            #endif
//&>>&1 0 1 2A
            break;
        case MACRO_KEYSEQ:
            for(pc=1; fCode[pc]!=0 ; pc++) Command(fCode[pc]);
            break;
        }
    Redr();
    return arg;
    }
//
// макрокоманда сворачивается в "short *"<==>(TMacro) следующим образом:
//     0 -- конец макры.
//     [ 1 , LEN_LANGUAGE ) -- используемые в языке конструкции, пока 1 (пусто).
//            /*    #define USER_FUNC (LEN_LANGUAGE+LEN_COMMAND_ARRAY)   */
//     [ LEN_LANGUAGE , USER_FUNC ) -- встроенные в редактор C-ф-и
//     [ USER_FUNC , INFTY ] -- ф-и написанные в фолде *MACRO* или
//                                              набитые с клавиатуры.
//&>>&6 0 6 0

//&<<&int fPair_String2Int  (TPair_String_Int psArr[], int len, const char *pcNam) {
int fPair_String2Int  (TPair_String_Int psArr[], int len, const char *pcNam) {
    for(int i=0;i<len;i++)
        if(0==strcmp(pcNam, psArr[i].fName))return psArr[i].iValue;
    return -1;
    }

//&>>&2 0 2 0
//&<<&char *fPair_Int2String(TPair_String_Int psArr[], int len, int iIdx   ) {
char *fPair_Int2String(TPair_String_Int psArr[], int len, int iIdx   ) {
    for(int i=0;i<len;i++)
        if(iIdx==psArr[i].iValue)return psArr[i].fName;
    return 0;
    }

//&>>&2 0 2 0

//&>>&4 0 4 F
//&<<&compiler
//&<<&char *ScanLanguageWord(FILE *fptr){
char *ScanLanguageWord(FILE *fptr){
    static int FoldDepth;
    char *body;
    static char *tline=0, *lptr=0;
    int i=0;
//&<<&    if(fptr!=0 && tline==0){
    if(fptr!=0 && tline==0){
        FoldDepth=0;
        tline=new char[0x100]; MemTest(tline!=0);
        lptr=tline;
        *lptr=0;
        }
//&>>&1 0 1 0
    if(fptr==0 && tline!=0) goto l_ShutdownScanner;

    do{
        if(*lptr==0){
            if(fgets(tline,0x100,fptr)==0)goto l_ShutdownScanner;
            if( Editor.IsComment(tline,"&<<&") )  FoldDepth++;
            else if( Editor.IsComment(tline,"&>>&") )  FoldDepth--;
            if(FoldDepth<0) goto l_ShutdownScanner;
            lptr=tline;
            }
        else{
            while(*lptr<=' '&& *lptr)lptr++;
            switch(*lptr){
                case '\"':    case '\'':
                    for(i=1; lptr[i]!=0 && lptr[i]!='\"' && lptr[i]!='\''  ; i++)
                        if(lptr[i]>0 && lptr[i]<' ')lptr[i]=' ';
                    if(lptr[i]!=0)i++;
                    break;
                case 0x25:  case 0:  // % & 0
                    *lptr=0;
                    i=0;
                default:
                    for(i=0; lptr[i]>' '; i++);
                }
            }
    }while(i==0);

    body=new char[i+1];
    memcpy(body, lptr, i * sizeof(char) );      body[i]=0;
    for(lptr+=i; *lptr!=0 && *lptr<=' '; lptr++);
    return body;

l_ShutdownScanner:
    delete tline;
    tline=lptr=0;
    return 0;
    }
//&>>&5 0 5 19
//&<<&int TestToken(char *lptr){
///////// supp_mmm.cpp supp_mmm.cpp supp_mmm.cpp supp_mmm.cpp

#define LENGTH_sToken2tId (21)
//&<<&TPair_String_Int psToken2tId[LENGTH_sToken2tId]={
TPair_String_Int psToken2tId[LENGTH_sToken2tId]={
//        TPair_String_Int("CONST_CHAR_"   , TKN_CONST_CHAR_ ) ,
//        TPair_String_Int("CONST_INT_"    , TKN_CONST_INT_ ) ,
//        TPair_String_Int("CONST_STRING_" , TKN_CONST_STRING_ ) ,
//        TPair_String_Int("GOTO_"         , TKN_GOTO_ ) ,
//        TPair_String_Int("CALL_"         , TKN_CALL_ ) ,

        TPair_String_Int("proc"          , TKN_PROC_     ) ,
        TPair_String_Int("endp"          , TKN_ENDP_     ) ,
        TPair_String_Int("if"            , TKN_IF_       ) ,
        TPair_String_Int("else"          , TKN_ELSE_     ) ,
        TPair_String_Int("endif"         , TKN_ENDIF_    ) ,
        TPair_String_Int("do"            , TKN_DO_       ) ,
        TPair_String_Int("enddo"         , TKN_ENDDO_    ) ,
        TPair_String_Int("break"         , TKN_BREAK_    ) ,
        TPair_String_Int("ret"           , TKN_RETURN_   ) ,
        TPair_String_Int("swp"           , TKN_SWP_      ) ,
        TPair_String_Int("dup"           , TKN_DUP_      ) ,
        TPair_String_Int("del"           , TKN_DEL_      ) ,
        TPair_String_Int("sget"          , TKN_SGET_     ) ,
        TPair_String_Int("sput"          , TKN_SPUT_     ) ,
        TPair_String_Int("mathop"        , TKN_MATHOP_   ) ,
        TPair_String_Int("predicate"     , TKN_PREDICATE_) ,
        TPair_String_Int("convert"       , TKN_CONVERT_  ) ,
        TPair_String_Int("query"         , TKN_QUERY_    ) ,
        TPair_String_Int("pop"           , TKN_POP_      ) ,
        TPair_String_Int("push"          , TKN_PUSH_     ) ,
        TPair_String_Int("ioctl"         , TKN_IOCTL_    ) };
//&>>&F 0 F B
int TestToken(const char *lptr){
    if(*lptr=='\"')return TKN_CONST_STRING_;
    if(*lptr=='\'')return TKN_CONST_CHAR_;
    if( (*lptr=='-' && lptr[1]>='0' && lptr[1]<='9')  ||
                       (*lptr>='0' && *lptr<='9') )
        return TKN_CONST_INT_;

    int i=fPair_String2Int( psToken2tId, LENGTH_sToken2tId, lptr);
    return (i>=0)?i:TKN_CALL_;
    }
//&>>&3 0 3 4
//&<<&void Compile(FILE *fptr){

void Compile(FILE *fptr){
    int i,l;
    char *tk;
    int cstat=TKN_INITIAL_;
    int ttype;
    char *FuncName;
    TMacro *ctStack, *mb;
    int p,np;
    while( (tk=ScanLanguageWord(fptr))!=0 ) {
        ttype=TestToken(tk);
//&<<&        #ifdef _ENABLE_LOGGING_
#ifdef _ENABLE_LOGGING_
    DoLog(">%25s< <-0x%-4x : cstat=0x%-4x p=0x%-4x\n",tk,ttype,cstat,p);
#endif
//&>>&0 0 0 26
        switch(cstat){
//&<<&            case TKN_INITIAL_:
            case TKN_INITIAL_:
                if(ttype==TKN_PROC_){
                    cstat=TKN_PROC_;
                    }
                break;
//&>>&2 0 2 2A
//&<<&            case TKN_PROC_:
            case TKN_PROC_:
                ctStack=new TMacro;
                mb=new TMacro;
                FuncName=new char[strlen(tk)+1];
                MemTest(mb!=0 && ctStack!=0 && FuncName!=0);
                strcpy(FuncName,tk);
                (*mb)[0]=MACRO_PROC;
                p=1; np=0;
                cstat=TKN_INPROC_;
                break;
//&>>&A 0 A D
//&<<&            case TKN_INPROC_:
    case TKN_INPROC_:
        switch(ttype){
//&<<&            case TKN_ENDP:
            case TKN_ENDP_:
                CommandUsrArray.AddEntry(FuncName,mb);
                delete FuncName;
                delete mb;
                delete ctStack;
                cstat=TKN_INITIAL_;
                p=np=0;
                break;
//&>>&5 0 5 22
//&<<&            case TKN_IF, TKN_ELSE, TKN_ENDIF 
            case TKN_IF_:
                (*mb)[p++]=TKN_IF_;
                (*ctStack)[++np]=p++;
                break;
            case TKN_ELSE_:
                (*mb)[p++]=TKN_GOTO_;
                (*mb)[(*ctStack)[np]]=p+1;
                (*ctStack)[np]=p++;
                break;
            case TKN_ENDIF_:
                (*mb)[(*ctStack)[np--]]=p;
                break;

//&>>&9 0 9 0
//&<<&            case TKN_DO, TKN_ENDDO
            case TKN_DO_:
                (*mb)[p++]=TKN_IF_;
                (*ctStack)[++np]=p++;
                break;
            case TKN_ENDDO_:
                (*mb)[p++]=TKN_GOTO_;
                (*mb)[p++]=(*ctStack)[np]-1;
                (*mb)[(*ctStack)[np--]]=p;
                break;

//&>>&6 0 6 2A
//&<<&            case TKN_CONST_CHAR, TKN_CONST_NUMBER, TKN_CONST_STRING:
            case TKN_CONST_CHAR_:
                (*mb)[p++]=TKN_CONST_INT_;
                (*mb)[p++]=tk[1];
                break;

            case TKN_CONST_INT_:
                (*mb)[p++]=TKN_CONST_INT_   ;
                (*mb)[p++]=short(strtol(tk,0,16));
                break;

            case TKN_CONST_STRING_:
                l=strlen(tk);
                (*mb)[p++]=TKN_CONST_STRING_;
                (*mb)[p++]=l-2;
                for(i=1;i<l-1;i++)(*mb)[p++]=tk[i];
                break;

//&>>&6 0 6 34
//&<<&            case TKN_CALL_:
            case TKN_CALL_:
                for(i=0;i<LEN_COMMAND_ARRAY;i++)
                    if(strcmp(CommandArray[i].fName,tk)==0)break;
                if(i<LEN_COMMAND_ARRAY)
                    i+=LEN_LANGUAGE;
                else
                    i=CommandUsrArray.AddEntry(tk)+USER_FUNC;
                (*mb)[p++]=i;
                break;
//&>>&0 0 0 8
//&<<&            default: // Arithm, pred, ... functions
            default:
                (*mb)[p++]=ttype;
                break;
//&>>&0 0 0 0
            }
//&>>&4 0 4 17
            }
        delete tk;
        }
    }
//&>>&F 0 F 17
//&>>&1 0 1 0
//&<<&RuntimeStack functions
// mmmx.h

//&<<&void Fold::stackSwp() {           ?
void Fold::stackSwp() {
    Line *ff=pos->next;
    if(ff==0)return;
    ff->UnLink();
    ff->LinkBefore(pos);
    pos=ff;
    }
//&>>&5 0 5 0
//&<<&void Fold::stackDel() {           ?
void Fold::stackDel() {
    Line *ff=pos;
    pos=pos->next;
    delete ff;
    }
//&>>&1 0 1 0
//&<<&void Fold::stackDup() {           ok
void Fold::stackDup() {
    Line *ff=pos->Copy(1);
    ff->LinkBefore(pos);
    pos=ff;
    }
//&>>&0 0 0 0
//&<<&void Fold::stackSget() {          ok
void Fold::stackSget() {
    if(pos->type!=SDATA_INT)return;
    Line *nl;
    Line *optr;
    int dpth=pos->linenumber;
    stackDel();
    optr=pos;
    while(--dpth > 0){ if(0==(optr=optr->next))return; }
    nl=optr->Copy(1);
    nl->LinkBefore(pos);
    pos=nl;
    }
//&>>&B 0 B 4
//&<<&void Fold::stackSput() {          ok
void Fold::stackSput() {
    if(pos->type!=SDATA_INT)return;
//    Line *nl;
    Line *optr,*oput;
    int dpth=pos->linenumber;
    stackDel();
    oput=pos; optr=pos=pos->next;
    oput->UnLink();
    while(--dpth > 0){ if(0==(optr=optr->next))return; }
    oput->LinkBefore(optr);
    delete optr;
    }


//&>>&A 0 A 0

//&<<&Line *Fold::TestTopOfTheStackIsInt() { ok
Line *Fold::TestTopOfTheStackIsInt() {
    Line *nxt=pos->next;
    if(nxt==0)return 0;
    Line *nnxt=nxt->next;
    if( pos->type!=SDATA_INT || nxt->type!=SDATA_INT ||
          nnxt==0 || nnxt->type!=SDATA_INT )return 0;
    return nnxt; // 2-nd argument
    }

//&>>&4 0 4 0
//&<<&void Fold::stackMathOperation() {      ok
void Fold::stackMathOperation() {
    Line *nnext=TestTopOfTheStackIsInt();
    if(nnext==0)return;
    long val1=pos->next->linenumber;
    long val2=nnext->linenumber;
    long valr;
    switch(pos->linenumber) {
        case MATHOP_SUB:
            valr=val2 - val1;
            break;
        case MATHOP_MUL:
            valr=val2 * val1;
            break;
        case MATHOP_DIV:
            valr=val2 / val1;
            break;
        case MATHOP_MOD:
            valr=val2 % val1;
            break;
        case MATHOP_AND:
            valr=val2 & val1;
            break;
        case MATHOP_OR:
            valr=val2 | val1;
            break;
        case MATHOP_XOR:
            valr=val2 ^ val1;
            break;
        default:  ///  case MATHOP_ADD: (as default, for idiots)
            valr=val2 + val1;
            break;
        }
    pos->linenumber=valr;
    delete pos->next;
    delete pos->next;
    }

//&>>&25 0 1A 2
//&<<&void Fold::stackPredicate() {          ok
void Fold::stackPredicate() {
    Line *nnext=TestTopOfTheStackIsInt();
    if(nnext==0)return;
    int val1=pos->next->linenumber;
    int val2=nnext->linenumber;
    switch(pos->linenumber) {
        case PREDICATE_EQ:
            RuntimeFlag=(val2 == val1)?1:0;
            break;
        case PREDICATE_LT:
            RuntimeFlag=(val2 < val1)?1:0;
            break;
        case PREDICATE_GT:
            RuntimeFlag=(val2 > val1)?1:0;
            break;
        default:         /// case PREDICATE_NE: (by default, for idiots)
            RuntimeFlag=(val2 != val1)?1:0;
            break;
        }
    stackDel();  // kill operation type
    stackDel();  // kill 1-st agrument
    stackDel();  // kill 2-nd agrument
    }

//&>>&0 0 0 0
//&<<&void Fold::stackQuery() {              ok
void Fold::stackQuery() {
    Line *pp=NewLine(0);
    pp->type=SDATA_INT;
    pp->linenumber=pos->type;
    pp->LinkBefore(pos);
    pos=pos->prev;
    }
//&>>&2 0 2 0
//&<<&void Fold::stackConvert() {            ok
void Fold::stackConvert() {
    if(pos->type!=SDATA_INT)return;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("Fold::stackConvert(0x%x){\n",pos->linenumber);
    #endif
//&>>&1 0 1 3D
    short ct=short(pos->linenumber);
    stackDel();
    long n;
    char *ts;
    Line *nl;
    switch(ct){
        case CONVERT_I2SH:
        case CONVERT_I2SD:
        case CONVERT_I2C:
            if(pos->type!=SDATA_INT)return;
            ts=new char[0x10]; MemTest(ts!=0);
            sprintf(ts,
                    (ct==CONVERT_I2SH)?"%x":
                        (ct==CONVERT_I2SD)?"%d":"%c"
                   ,int(pos->linenumber));
            nl=NewLine(ts);
            nl->type=SDATA_STRING;
            delete ts;
            break;
        case CONVERT_S2IH:
        case CONVERT_S2ID:
        case CONVERT_C2I:
            if(pos->type!=SDATA_STRING)return;
            if(ct==CONVERT_C2I) n=pos->buf[0];
            else n=strtol( pos->buf, 0, (ct==CONVERT_S2IH)?16:10 );
            nl=NewLine(0);
            nl->linenumber=n;
            nl->type=SDATA_INT;
            break;
        case CONVERT_S2L:
            if(pos->type!=SDATA_STRING)return;
            pos->type=SDATA_LINE;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 19
            return;
        case CONVERT_L2S:
            if(pos->type!=SDATA_LINE)return;
            pos->type=SDATA_STRING;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 19
            return;
        }
    nl->LinkBefore(pos);
    delete pos;
    pos=nl;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 19
    }
//&>>&2 0 2 0
//&<<&void Fold::stackPop() {                ok
void Fold::stackPop() {
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("Fold::stackPop(){\n");
    #endif
//&>>&1 0 1 0
    int i;
    Line *ff;
    switch(pos->type){
        case SDATA_LINE:
            ff=pos;
            pos=pos->next;
            ff->UnLink();
            ff->LinkBefore(cur->pos);
            cur->pos=ff;
            return;  // !!NOT break!!
        case SDATA_INT:
            RuntimeFlag=pos->linenumber;
            break;
        case SDATA_STRING:
            for(i=0;*(pos->Buf(i));i++) cur->Ascii(*(pos->Buf(i)));
            break;
        }
    stackDel();
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 19
    }
//&>>&10 0 10 41
//&<<&void Fold::stackPush() {               ok
void Fold::stackPush() {
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("Fold::stackPush(){\n");
    #endif
//&>>&3 0 3 4
//    char aa[2];
    Line *nl;
    int itPush=pos->linenumber;
    stackDel();
    switch(itPush){
        case PUSH_FLAG    :
            nl=NewLine(0);
            nl->linenumber=RuntimeFlag;
            nl->type=SDATA_INT;
            break;
        case PUSH_CLINE_L :
            nl=cur->pos->Copy();
            nl->type=SDATA_LINE;
            break;
        case PUSH_CLINE_S :
            nl=NewLine(cur->pos->buf);
            nl->type=SDATA_STRING;
            break;
        case PUSH_CCB     :
            nl=NewLine(mmm_CharClipboard.buf);
            nl->type=SDATA_STRING;
            break;
        case PUSH_LCB     :
            nl=fLineClipboard->Copy();
            nl->type=SDATA_LINE;
            break;
        case PUSH_CHAR    :
            nl=NewLine(0);
            nl->linenumber=byte(cur->GetCh());
            nl->type=SDATA_INT;
            break;
        }
    nl->LinkBefore(pos);
    pos=nl;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 19
    }
//&>>&1E 0 F 0
//&<<&void Fold::stackIOCTL() {
void Fold::stackIOCTL() {
    Line *nl;
//    int i;
    int itF=pos->linenumber;
    stackDel();
    switch(itF){
        case IOCTL_MODEINS   :     // Опросить, включен ли режим вставки.
            RuntimeFlag=Editor.InsFlag;
            return;
        case IOCTL_MODEAI    :     // Опросить, включен ли режим автоотступа.
            RuntimeFlag=Editor.IndFlag;
            return;
        case IOCTL_MODESEARCH:     // Опросить, режим поиска
            RuntimeFlag=Editor.SearchMode;
            return;
        case IOCTL_MODECAPS  :     // Опросить, включен ли CAPS (верхние буквы бе
            RuntimeFlag=mmm_f_FixShift;
            return;
        case IOCTL_MODEALT   :     // Опросить, включен ли ALT (---''---)
            RuntimeFlag=mmm_f_FixAlt;
            return;
        case IOCTL_ISFOLD    :     // Опросить, текущая строка -- фолд?
            RuntimeFlag=(cur->pos->Enter()!=0);
            return;
        case IOCTL_ISMARKED  :     // Опросить, помечена ли текущая строка.
            RuntimeFlag=cur->pos->marked;
            return;
        case IOCTL_ISLAST    :     // Опросить, последняя строка в фолде?
            RuntimeFlag=(cur->pos->next==0);
            return;
        case IOCTL_INSEARCH  :     // Опросить, находимся ли в {\tt SearchPage}.
            RuntimeFlag=Editor.IsInSearchFold;
            return;
        case IOCTL_INTEMP    :     // Опросить, находимся ли в {\tt *TEMP*}.
            RuntimeFlag=(CurrentPage==ConstantPage);
            return;
        case IOCTL_MAXY      :     // Положить на стек кол-во строк на экране
            nl=NewLine(0);
            nl->type=SDATA_INT;
            nl->linenumber=mmm_screen.GetH();
            break;
        case IOCTL_MAXX      :     // Положить на стек кол-во столбцов на экране
            nl=NewLine(0);
            nl->type=SDATA_INT;
            nl->linenumber=mmm_screen.GetW();
            break;
        case IOCTL_CX        :     // Положить на стек {\tt cx}
            nl=NewLine(0);
            nl->type=SDATA_INT;
            nl->linenumber=cur->cx;
            break;
        case IOCTL_SX        :     // Положить на стек {\tt sx}
            nl=NewLine(0);
            nl->type=SDATA_INT;
            nl->linenumber=cur->sx;
            break;
        case IOCTL_SY        :     // Положить на стек {\tt sy}
            nl=NewLine(0);
            nl->type=SDATA_INT;
            nl->linenumber=cur->sy;
            break;
        case IOCTL_LINENUM   :     // Положить на стек номер строки
            nl=NewLine(0);
            nl->type=SDATA_INT;
            nl->linenumber=cur->pos->linenumber;
            break;
        }
    nl->LinkBefore(pos);
    pos=nl;
    }
//&>>&23 0 17 19

//&>>&E 0 E 1

void Process(){ for(;;) MkScan(mmm_KBD.GetScan()); }

//&<<&void Command(short MMMscan){
void Command(short MMMscan){
    if(MMMscan==0) return;
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("Command(int code=0x%4x ) {\n", MMMscan);
    #endif
//&>>&1 0 1 3A

    if(MMMscan==0x701) MMMlib_ABORT(0x701);

    if(fRecordingMacro)  (*my_macroF7)[my_macroF7_ptr++]=MMMscan;

    int i,fnum;
    for(i=0;i<KeyArray.lbase;i++){
        fnum=KeyArray.base[i].fnum;
        if(fnum==-1) break;
        if(KeyArray.base[i].scan==MMMscan)
            {
            if(fnum<LEN_COMMAND_ARRAY)
                CommandArray[fnum].fRef(MMMscan);
            else
                CommandUsrArray.base[fnum-LEN_COMMAND_ARRAY].Execute(MMMscan);
            return;
            }
        }
//&<<&    #ifdef _ENABLE_LOGGING_
    #ifdef _ENABLE_LOGGING_
        DoLog("    }\n");
    #endif
//&>>&1 0 1 8
    }
//&>>&F 0 F 2

//&<<&EDITOR functions
//&<<&int EDITOR::IsComment(char *buf,char *ptrn);
int EDITOR::IsComment(char *buf,char *ptrn){
  if(buf==0) return 0;
  if(memcmp(buf,comment,lcomment)) return 0;
  if(memcmp(buf+lcomment,ptrn,strlen(ptrn))) return 0;
  return 1;
}
//&>>&3 0 3 6
//&<<&void EDITOR::SetComment(char *n);
void EDITOR::SetComment(char *name){
  int i,j,k;
  for(i=0;name[i];i++) if(name[i]=='.'){ i++; break; }
  for(j=0;j<nExt;j++){
    for(k=0;name[i+k];k++) if(lower(FileExt[j][k])!=lower(name[i+k])) break;
    if(name[i+k]==0 && FileExt[j][k]==0){
      comment=FileCmt[j]; lcomment=strlen(comment); return;
    }
  }
  comment=""; lcomment=0;
}
//&>>&0 0 0 8

//&<<&void EDITOR::Init_ExtensionsFold2Mem(Fold *ExtFold){
void EDITOR::Init_ExtensionsFold2Mem(Fold *ExtFold){
   int i, k, fldd;

   Line *pp=ExtFold->pos;
   while(pp->next)pp=pp->next;
   for(nExt=0;pp->prev;nExt++)pp=pp->prev;

   FileExt=new char*[nExt]; MemTest(FileExt!=0);
   FileCmt=new char*[nExt]; MemTest(FileCmt!=0);

    for(i=0;pp && i<nExt;i++){
        fldd=0;
        FileExt[i]=new char[4]; MemTest(FileExt[i]!=0);
        FileCmt[i]=new char[8]; MemTest(FileCmt[i]!=0);
        for(k=0;*(pp->Buf(k))!=0;k++){
            if(*(pp->Buf(k))==' ' && !fldd){
                strncpy(FileExt[i], pp->Buf(0), k); FileExt[i][k]=0;
                fldd=k+1;
                }
            }
        strncpy(FileCmt[i], pp->Buf(fldd), k+1-fldd);
        FileCmt[i][k+1-fldd]=0;
        pp=pp->next;
        }
   }
///const nExt=13;
///char *FileExt[nExt]={"h" ,"hpp","c" ,"cpp","tex","bat"  ,"asm","sty","prg","ch","" ,"rc","sys"};
///char *FileCmt[nExt]={"//","//" ,"//","//" ,"%"  ,"@rem ",";"  ,"%"  ,"//" ,"//","#","//","Rem "};
//&>>&1C 0 1C 6
//&<<&void EDITOR::Init_keymapFold2Mem(FILE *fptr) {
void EDITOR::Init_keymapFold2Mem(FILE *fptr) {
    int i=0,l,j;
    for(;fgets(templine,0xff,fptr)!=0;i++){
        if ( Editor.IsComment(templine,"&>>&") ) return;
        if(i==0){
            l=strlen(templine);
            for(j=0;j<l;j+=2){            // read altcase table
                mmm_KBD.AltCase[templine[j]]   =templine[j+1];
                mmm_KBD.AltCase[templine[j+1]] =templine[j];
                }
            continue;
            }
        if(i<5) memcpy(mmm_KBD.keys[i-1],templine,108*sizeof(char)); // read keytable
        }
   }
//&>>&C 0 C 1E
//&<<&void  EDITOR::Init_SetupFold2Mem() {
void EDITOR::Init_SetupFold2Mem(FILE *fptr) {
    char *s;
    int i;
    while(fgets(templine,0xff,fptr)!=0){
        if( Editor.IsComment(templine,"&>>&") ) return;
        if(memcmp(templine,"Attrs=",6)==0){
            s=templine+6;
            for(i=0;i<NAttr;i++) Attrs[i]=int(strtol(s,&s,16));
            }
        if(memcmp(templine,"Params=",7)==0){
            s=templine+7;
            for(i=0;i<NParams;i++) Params[i]=int(strtol(s,&s,16));
            }
        }
    }
//&>>&B 0 B D
//&<<&void EDITOR::Init_CommandFold2Mem(FILE *fptr) {
void EDITOR::Init_CommandFold2Mem(FILE *fptr) {
    //// This function is called only from EDITOR::InitEditorSetup,
    //// Where 'templine' is already allocated!
    ////     if(strcmp(templine,"&<<&*COMMAND*\n")==0) Init_CommandFold2Mem();

    char *s;
    int nl,i;
    int _scan;
    while(fgets(templine,0xff,fptr)!=0){
        if( Editor.IsComment(templine,"&>>&") ) return;
        s=templine;
        _scan=int(strtol(s,&s,16));
        while(*s<=' ')s++;
        for(nl=0 ; s[nl]>' '; nl++);    s[nl]=0;
        for(i=0;i<LEN_COMMAND_ARRAY;i++){
            if(strcmp(CommandArray[i].fName,s)==0){
                KeyArray.AddEntry(_scan, i);
                break;
                }
            }
        if(i>=LEN_COMMAND_ARRAY){          // Notfound in MMMLIB, add to UsrLib.
            i=CommandUsrArray.AddEntry(s,0);
            KeyArray.AddEntry(_scan, LEN_COMMAND_ARRAY+i);
            }
        }
    }

//&>>&16 0 11 0
//&<<&void EDITOR::Init_MacroFold2Mem(FILE *fptr) {



//&>>&0 0 0 2


//&<<&EDITOR::EDITOR();
EDITOR::EDITOR(){
//&<<&#ifdef _ENABLE_LOGGING_
#ifdef _ENABLE_LOGGING_
{
FILE *flog=fopen("log.","w");
if(flog){ fputs("MM2 LogFile\n",flog); fclose(flog); }
}
#endif
//&>>&6 0 6 1B
IsInSearchFold=0; attrs=Attrs;
}
//&>>&3 0 3 A
//&<<&void EDITOR::InitFirstPage()
void EDITOR::InitFirstPage()
    {
    cur=new Fold("*TEMP*");
    cur->top=0;
    CurrentPage=new Chain(cur);
    CurrentPage->next=CurrentPage;
    CurrentPage->prev=CurrentPage;
    ConstantPage=CurrentPage;
    NumberOfPages=1;
    }
//&>>&0 0 0 7
//&<<&void EDITOR::InitUserSetup() {
void EDITOR::InitUserSetup() {
    FILE *f;
    InitialDir=getcurdir();

//&<<&    UserSetup Folds Init
    MarkedBlock=new MarkedLine("*ML*");
    SearchFold=new Fold("*SEARCH*"); SearchFold->top=0;

    mmm_LineClipboard=NewLine(0);
    fLineClipboard=new Fold("*LCB*");
    fLineClipboard->pos=mmm_LineClipboard;

    InitFirstPage();
//&>>&5 0 5 5
    templine=new char[INFTY+1]; MemTest(templine!=0);

    comment=""; lcomment=0;

    f=fopen(ConfigFileName,"r"); if(f==0)return;
    while(fgets(templine,INFTY,f)!=0){
//&<<&        if(strcmp(templine,"&<<&*SEARCH*\n")==0){
        if(strcmp(templine,"&<<&*SEARCH*\n")==0){
            SearchFold->Read(f,FILE_FOLD);
            }
//&>>&1 0 1 0
//&<<&        if(strcmp(templine,"&<<&*TEMP*\n")==0){
        if(strcmp(templine,"&<<&*TEMP*\n")==0){
            cur->Read(f,FILE_FOLD);
            }
//&>>&1 0 1 C
//&<<&        if(strcmp(templine,"&<<&*LCB*\n")==0){
        if(strcmp(templine,"&<<&*LCB*\n")==0){
            fLineClipboard->Read(f,FILE_FOLD);
            }
//&>>&1 0 1 D
        }
    fclose(f);
    while(mmm_LineClipboard->prev) mmm_LineClipboard=mmm_LineClipboard->prev;
    delete templine;

    }
//&>>&D 0 D 0
//&<<&void EDITOR::InitEditorSetup(){
void EDITOR::InitEditorSetup(){
    FILE *f;
    SetDefaultAttributes();
//&<<&    ExtensionsFold 
    Fold *ExtensionsFold=new Fold("*EXTENSIONS*");
    ExtensionsFold->pos=NewLine(0);
//&>>&0 0 0 1D
    templine=new char[INFTY+1]; MemTest(templine!=0);

    comment=""; lcomment=0;
//&<<&    f=fopen(cFName,"r"); if(f==0)return; delete cFName;
    char *cFName=MFileName("mmm_base.cfg");
    f=fopen(cFName,"r"); if(f==0)return; delete cFName;
//&>>&0 0 0 0
    while(fgets(templine,INFTY,f)!=0){
//&<<&        if(strcmp(templine,"&<<&*EXTENSIONS*\n")==0) {
        if(strcmp(templine,"&<<&*EXTENSIONS*\n")==0) {
            ExtensionsFold->Read(f,FILE_FOLD);
            Init_ExtensionsFold2Mem(ExtensionsFold);
            }
//&>>&2 0 2 37
//&<<&        if(strcmp(templine,"&<<&*KEYMAP*\n")==0) {
        if(strcmp(templine,"&<<&*KEYMAP*\n")==0) {
            Init_keymapFold2Mem(f);
            }
//&>>&1 0 1 2D
//&<<&        if(strcmp(templine,"&<<&*SETUP*\n")==0) {
        if(strcmp(templine,"&<<&*SETUP*\n")==0) {
            Init_SetupFold2Mem(f);
            }
//&>>&1 0 1 10
//&<<&        if(strcmp(templine,"&<<&*COMMAND*\n")==0) {
        if(strcmp(templine,"&<<&*COMMAND*\n")==0) {
            Init_CommandFold2Mem(f);
            }
//&>>&1 0 1 13
//&<<&        if(strcmp(templine,"&<<&*MACRO*\n")==0) {
        if(strcmp(templine,"&<<&*MACRO*\n")==0) {
            Compile(f);
            }
//&>>&1 0 1 17
        }
    fclose(f);
    delete ExtensionsFold;

    delete templine;

    RuntimeStack->pos=NewLine(0);
    }
//&>>&D 0 D 8
//&<<&EDITOR::~EDITOR();
EDITOR::~EDITOR(){
    if(MinimalExitFromEditor) return;
//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("EDITOR::~EDITOR() {\n");
  #endif
//&>>&1 0 1 19
    SaveChDir(InitialDir);
//&<<&    ConstantPage->Exit();   SearchFold->Exit();
//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("    ConstantPage, SearchFold ->Exit() {\n");
  #endif
//&>>&1 0 1 F
    if(CurrentPage!=ConstantPage)cur=ConstantPage->entry;
    Fold *r=0;    /// temporary variable
    while((r=cur->Exit())!=0) cur=r;
    while((r=SearchFold->Exit())!=0) SearchFold=r;
//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("        }(r=0)\n");
  #endif
//&>>&1 0 1 6
//&>>&0 0 0 19
    comment=""; lcomment=0;
//&<<&          #ifdef _ENABLE_LOGGING_
        #ifdef _ENABLE_LOGGING_
            DoLog("    f=fopen(ConfigFileName,w);\n");
        #endif
//&>>&1 0 1 C
    FILE *f=fopen(ConfigFileName,"w");  MemTest(f!=0);
//&<<&          #ifdef _ENABLE_LOGGING_
        #ifdef _ENABLE_LOGGING_
            DoLog("    SearchFold->Write\n");
        #endif
//&>>&1 0 1 C
    SearchFold->Write(f,FILE_FOLD);     //// Writing *SEARCH*
//&<<&          #ifdef _ENABLE_LOGGING_
        #ifdef _ENABLE_LOGGING_
            DoLog("    cur->Write\n");
        #endif
//&>>&1 0 1 C
    cur->Write(f,FILE_FOLD);            //// Writing *TEMP*
//&<<&          #ifdef _ENABLE_LOGGING_
        #ifdef _ENABLE_LOGGING_
            DoLog("    LCB->Write\n");
        #endif
//&>>&1 0 1 C
    fLineClipboard->Write(f,FILE_FOLD);  //// Writing *LCB*
//&<<&          #ifdef _ENABLE_LOGGING_
        #ifdef _ENABLE_LOGGING_
            DoLog("    written!!!!!\n");
        #endif
//&>>&1 0 1 C
    fclose(f);
//&<<&          #ifdef _ENABLE_LOGGING_
        #ifdef _ENABLE_LOGGING_
            DoLog("    CLOSED!!!!!\n");
        #endif
//&>>&1 0 1 D

//&<<&    #ifdef _ENABLE_LOGGING_
  #ifdef _ENABLE_LOGGING_
      DoLog("    }\n");
  #endif
//&>>&1 0 1 10
    }
//&>>&D 0 D 5

//&>>&6 0 6 1A

//&<<&void main()

void main(int argc,char *argv[]){
  int i;

  strcpy(RunDir,argv[0]);
  SaveChDir(".");

  iGCD_SavedDev=GetSavedDev();

  Editor.InitEditorSetup();
  Editor.ConfigFileName=MFileName("mmm.cfg");
  Editor.InitUserSetup();

  int fx=FILE_FOLD,fn=1;
  int k=0;


  FILE *pfScriptExists=fopen(MFileName("__mmm__.mmm"),"r");
  if(pfScriptExists==0){
      for(i=1;i<argc;i++) k|=_EDIT(argv[i],fn,fx,1);
      if(k==0) _EDIT("",fn,fx,1);
  }else{
      fclose(pfScriptExists);
      _EDIT_ScriptFile(MFileName("__mmm__.mmm")-1,fn,fx);
      }

  GetCurrentFileNameAndDepth();
  Process();
}
//&>>&E 0 E 7
//// mmmx.err mmmx.err mmmx.err mmmx.err mmmx.err mmmx.err
//&>>&11 0 D 7
