/**************************
*  mmm.cfg file creator   *
* Creates default config. *
***************************/
//&<<&Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//&>>&2 0 2 0
#include "mmmconst.h"

//&<<&void putSearch(FILE *fptr);
void putSearch(FILE *fptr){
    fprintf(fptr,"&<<&*SEARCH*\n");
    fprintf(fptr,"Lines to search to\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&3 0 3 0
//&<<&void putTemp(FILE *fptr);
void putTemp(FILE *fptr){
    fprintf(fptr,"&<<&*TEMP*\n");
    fprintf(fptr,"/usr/include/stdio.h\n");
    fprintf(fptr,"/usr/include/signal.h\n");
    fprintf(fptr,"/usr/include/asm/signal.h\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&7 0 7 4
//&<<&void putLCB(FILE *fptr);
void putLCB(FILE *fptr){
    fprintf(fptr,"&<<&*LCB*\n");
    fprintf(fptr,"Line Clipboard\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&2 0 2 0
//&<<&void putExtensions(FILE *fptr);
void putExtensions(FILE *fptr){
    fprintf(fptr,"&<<&*EXTENSIONS*\n");
    fprintf(fptr,"cpp //\nc //\nhpp //\nh //\n"); // c/c++
    fprintf(fptr,"tex %%\nsty %%\n");               // TeX
    fprintf(fptr,"prg //\nch  //\nrmk #\n");      // Clipper
    fprintf(fptr,"bat @Rem -\nsys rem -\n");      // MSDOS config
    fprintf(fptr,"lsp ;\nasm ;\n");               // Lsp, asm
    fprintf(fptr,"conf #\n");                     // Linux ".conf"
    fprintf(fptr,"mif #\n");                      // makefiles
    fprintf(fptr," #\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&A 0 A 0
//&<<&void putKeyboardLayouts(FILE *fptr);
//&<<&void pkl_PrintTable(FILE *fptr, char *keys[]){
void pkl_PrintTable(FILE *fptr, char *keys[]){
    int i;
    for(i=0;i<4;i++) fprintf(fptr,"%s\n",keys[i]);
    }
//&>>&2 0 2 32
void putKeyboardLayouts(FILE *fptr){
    int etype=100;
    while(etype!=0 && etype!=1 && etype!=2 && etype!=3 ){
        printf("encoding type (0-ALT, 1-KOI8, 2-ISO, 3-WIN) :");
        scanf("%d",&etype);
        }

    fprintf(fptr,"&<<&*KEYMAP*\n");
    if(etype==0){
//&<<&        Alt enc. (dos, os2)
    char *altCase="aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
          " €¡¢‚£ƒ¤„¥…¦†§‡¨ˆ©‰ªŠ«‹¬Œ­®Ž¯àá‘â’ã“ä”å•æ–ç—è˜é™ìœë›êšíîžïŸ";

    char *keys[]={                   /*  size = 4x108  */
      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    // 0..13
      "....qQwWeErRtTyYuUiIoOpP[{]}"                    // 14..27
      "....aAsSdDfFgGhHjJkKlL;:'\"`~"                   // 28..41
      "..\\|zZxXcCvVbBnNmM,<.>/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    // 0..13
      "....ïŸ¢‚¥…àâ’ë›ã“¨ˆ®Ž¯è˜é™"                    // 14..27
      ".... €á‘¤„ä”£ƒå•©‰ªŠ«‹êší`~"                    // 28..41
      "..\\|§‡ìœæ–¦†¡­¬Œç—îž/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    // 0..13
      "....©‰æ–ã“ªŠ¥…­£ƒè˜é™§‡å•êš"                    // 14..27
      "....ä”ë›¢‚ €¯à®Ž«‹¤„¦†í`~"                    // 28..41
      "..\\|ïŸç—á‘¬Œ¨ˆâ’ìœ¡îž/?",                      // 42..53

      "....ðñòóôõö÷øùúûüý......þþ.."                    // 0..13
      "....ÚÕÂÑ¿¸ÖÉÒË·»..ßß°°±±²²ÛÛ"                    // 14..27
      "....ÃÆÅØ´µÇÌ×Î¶¹ÝÝÞÞ³³ººÄÍ.."                    // 28..41
      "....ÀÔÁÏÙ¾ÓÈÐÊ½¼ÜÜ......"                        // 42..53
      };

//&>>&0 0 0 0
        fprintf(fptr,"%s\n", altCase);
        pkl_PrintTable(fptr, keys);
        }
    if(etype==1){
//&<<&        KOI8
    char *altCase="aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
          "ÁáÂâ×÷ÇçÄäÅåÖöÚúÉéÊêËëÌìÍíÎîÏïÐðÒòÓóÔôÕõÆæÈèÃãÞþÛûÝýØøÙùßÿÜüÀàÑñ";

    char *keys[]={      /* size = 4x108 */
      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    //  0..13
      "....qQwWeErRtTyYuUiIoOpP[{]}"                    // 14..27
      "....aAsSdDfFgGhHjJkKlL;:'\"`~"                   // 28..41
      "..\\|zZxXcCvVbBnNmM,<.>/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    //  0..13
      "....Ññ×÷ÅåÒòÔôÙùÕõÉéÏïÐðÛûÝý"                    // 14..27
      "....ÁáÓóÄäÆæÇçÊêÈèËëÌìßÿÜü`~"                    // 28..41
      "..\\|ÚúØøÓó×÷ÂâÎîÍíÞþÀà/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    //  0..13
      "....ÊêÃãÕõËëÅåÎîÇçÛûÝýÚúÈèßÿ"                    // 14..27
      "....ÆæÙù×÷ÁáÐðÒòÏïÌìÄäÖöÜü`~"                    // 28..41
      "..\\|ÑñÞþÓóÍíÉéÔôØøÂâÀà/?",                      // 42..53

      "......™˜“›Ÿ—œ...........””.."                    //  0..13
      "....‚¢ˆ¶ƒ¦¤¥·¸§¨..‹‹‘‘’’"                    // 14..27
      "....†¯Š¼‡²°±½¾´µŽŽ¡¡€ .."                    // 28..41
      "....„©‰¹…¬ª«º»­®ŒŒ......"                        // 42..53

      };
//&>>&0 0 0 8
        fprintf(fptr,"%s\n", altCase);
        pkl_PrintTable(fptr, keys);
        }
    if(etype==2){
//&<<&        ISO
    char *altCase="aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
          "Ð°Ñ±Ò²Ó³Ô´ÕµÖ¶×·Ø¸Ù¹ÚºÛ»Ü¼Ý½Þ¾ß¿àÀáÁâÂãÃäÄåÅæÆçÇèÈéÉìÌëËêÊíÍîÎïÏ";

    char *keys[]={      /* size = 4x108 */
      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    //  0..13
      "....qQwWeErRtTyYuUiIoOpP[{]}"                    // 14..27
      "....aAsSdDfFgGhHjJkKlL;:'\"`~"                   // 28..41
      "..\\|zZxXcCvVbBnNmM,<.>/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    //  0..13
      "....ïÏÒ²ÕµàÀâÂëËãÃØ¸Þ¾ß¿èÈéÉ"                    // 14..27
      "....Ð°áÁÔ´äÄÓ³åÅÙ¹ÚºÛ»êÊíÍ`~"                    // 28..41
      "..\\|×·ìÌáÁÒ²Ñ±Ý½Ü¼çÇîÎ/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    //  0..13
      "....Ù¹æÆãÃÚºÕµÝ½Ó³èÈéÉ×·åÅêÊ"                    // 14..27
      "....äÄëËÒ²Ð°ß¿àÀÞ¾Û»Ô´Ö¶íÍ`~"                    // 28..41
      "..\\|ïÏçÇáÁÜ¼Ø¸âÂìÌÑ±îÎ/?",                      // 42..53

      "............................"                    //  0..13
      "............................"                    // 14..27
      "............................"                    // 28..41
      "........................"                        // 42..53

      };
//&>>&17 0 14 0
        fprintf(fptr,"%s\n", altCase);
        pkl_PrintTable(fptr, keys);
        }
    if(etype==3){
//&<<&        WIN    (w95)
    char *altCase="aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
          " €¡¢‚£ƒ¤„¥…¦†§‡¨ˆ©‰ªŠ«‹¬Œ­®Ž¯àá‘â’ã“ä”å•æ–ç—è˜é™ìœë›êšíîžïŸ";

    char *keys[]={      /* size = 4x108 */
      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    // 0..13
      "....qQwWeErRtTyYuUiIoOpP[{]}"                    // 14..27
      "....aAsSdDfFgGhHjJkKlL;:'\"`~"                   // 28..41
      "..\\|zZxXcCvVbBnNmM,<.>/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    // 0..13
      "....ÿßâÂåÅðÐòÒûÛóÓèÈîÎïÏøØùÙ"                    // 14..27
      "....àÀñÑäÄôÔãÃõÕéÉêÊëËúÚýÝ`~"                    // 28..41
      "..\\|çÇüÜöÖæÆáÁíÍìÌ÷×þÞ/?",                      // 42..53

      "....1!2@3#4$5%6^7&8*9(0)-_=+"                    // 0..13
      "....éÉöÖóÓêÊåÅíÍãÃøØùÙçÇõÕúÚ"                    // 14..27
      "....ôÔûÛâÂàÀïÏðÐîÎëËäÄæÆýÝ`~"                    // 28..41
      "..\\|ÿß÷×ñÑìÌèÈòÒüÜáÁþÞ/?",                      // 42..53

      "....°±²³´µ¶·¸¹º»¼½......¾¾.."                    // 0..13
      "....ª¥’¡ˆ¦™¢›‡‹..¯¯€€‚‚««"                    // 14..27
      "....“–•¨„…—œ§ž†‰­­®®ƒƒŠŠ”.."                    // 28..41
      "....¤‘Ÿ©Ž£˜ šŒ¬¬......"                        // 42..53
      };

//&>>&9 0 9 0
        fprintf(fptr,"%s\n", altCase);
        pkl_PrintTable(fptr, keys);
        }
    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&1C 0 14 16
//&<<&void putSetup(FILE *fptr);
void putSetup(FILE *fptr){
    int etype=100;
    while(etype!=0 && etype!=1){
        printf("Color type (0-Dos,os2,win, 1-Linux-color) :");
        scanf("%d",&etype);
        }

    fprintf(fptr,"&<<&*SETUP*\n");
    switch(etype){
//&<<&        case 0:
        case 0:
            fprintf(fptr,"Attrs=7 70 a 60 17 6f 1a 31\n");
            break;
//&>>&1 0 1 32
//&<<&        case 1:
        case 1:
            fprintf(fptr,"Attrs=7 70 a 60 47 6f 4a 60\n");
            break;
//&>>&1 0 1 32
        }
    fprintf(fptr,"Params=1 1 1 0\n");
    fprintf(fptr,"&>>&0 0 0 0\n");

    }
//&>>&A 0 A B
//&<<&void putCommand(FILE *fptr);
void putCommand(FILE *fptr) {
    int etype=100;
    while(etype!=0 && etype!=1 && etype!=2 && etype!=3 ){
        printf("Command Table (0-DOS, 1-OS2, 2-Linux, 3-Win95) :");
        scanf("%d",&etype);
        }
    fprintf(fptr,"&<<&*COMMAND*\n");
    fprintf(fptr,"40e HelloWorld\n");
//&<<&    if(etype==0 || etype==2 || etype==3 ){    /// Dos Linux Win95
    if(etype==0 || etype==2 || etype==3 ){    /// Dos Linux Win95
//&<<&        // Movement
    fprintf(fptr, "048 Up\n");
    fprintf(fptr, "068 Up\n");
    fprintf(fptr, "050 Down\n");
    fprintf(fptr, "06d Down\n");
    fprintf(fptr, "04b Left\n");
    fprintf(fptr, "06a Left\n");
    fprintf(fptr, "04d Right\n");
    fprintf(fptr, "06b Right\n");

    fprintf(fptr, "448 TUp\n");  // Ctrl + Up
    fprintf(fptr, "468 TUp\n");  // Ctrl + Up
    fprintf(fptr, "450 TDown\n");  // Ctrl + Down
    fprintf(fptr, "46d TDown\n");  // Ctrl + Down
    fprintf(fptr, "44b TLeft\n");  // Ctrl + Left
    fprintf(fptr, "46a TLeft\n");  // Ctrl + Left
    fprintf(fptr, "44d TRight\n");  // Ctrl + Right
    fprintf(fptr, "46b TRight\n");  // Ctrl + Right

    fprintf(fptr, "148 PUp\n");  // Shift + Up
    fprintf(fptr, "168 PUp\n");  // Shift + Up
    fprintf(fptr, "150 PDown\n");  // Shift + Down
    fprintf(fptr, "16d PDown\n");  // Shift + Down
    fprintf(fptr, "14b PLeft\n");  // Shift + Left
    fprintf(fptr, "16a PLeft\n");  // Shift + Left
    fprintf(fptr, "14d PRight\n");  // Shift + Right
    fprintf(fptr, "16b PRight\n");  // Shift + Right

    fprintf(fptr, "248 FUp\n");  // Alt + Up
    fprintf(fptr, "268 FUp\n");  // Alt + Up
    fprintf(fptr, "250 FDown\n");  // Alt + Down
    fprintf(fptr, "26d FDown\n");  // Alt + Down
    fprintf(fptr, "24b FLeft\n");  // Alt + Left
    fprintf(fptr, "26a FLeft\n");  // Alt + Left
    fprintf(fptr, "24d FRight\n");  // Alt + Right
    fprintf(fptr, "26b FRight\n");  // Alt + Right

    fprintf(fptr, "01c Enter\n");  // Enter
    fprintf(fptr, "061 Enter\n");  // Enter
    fprintf(fptr, "11c REnter\n");  // Shift + Enter
    fprintf(fptr, "161 REnter\n");  // Shift + Enter

    fprintf(fptr, "00f Tab\n");  // Tab
    fprintf(fptr, "10f LTab\n");  // Shift + Tab

//&>>&0 0 0 14
//&<<&        // Insert and delete
// Insert and delete

    fprintf(fptr, "052 InsCh\n");  // Ins
    fprintf(fptr, "06f InsCh\n");  // Ins
    fprintf(fptr, "053 DelCh\n");  // Del
    fprintf(fptr, "070 DelCh\n");  // Del
    fprintf(fptr, "152 InsLine\n");  // Shift + Ins
    fprintf(fptr, "16f InsLine\n");  // Shift + Ins
    fprintf(fptr, "252 InsFold\n");  // Alt + Ins
    fprintf(fptr, "26f InsFold\n");  // Alt + Ins
    fprintf(fptr, "153 DelLine\n");  // Shift + Del
    fprintf(fptr, "170 DelLine\n");  // Shift + Del
    fprintf(fptr, "253 DelLine\n");  // Alt + Del
    fprintf(fptr, "270 DelLine\n");  // Alt + Del
    fprintf(fptr, "00E BS\n");  // BS
    fprintf(fptr, "10e R_BS\n");  // Shift + BS

//&>>&F 0 F B
//&<<&        // Line Killing
// Line Killing
    fprintf(fptr, "04a KillWord\n" );     // [+]
    fprintf(fptr, "14a KillEnd\n" );     // SHIFT [+]
    fprintf(fptr, "44a KillBeg\n" );     // CTRL [+]
    fprintf(fptr, "04e KillWord\n" );     // [-]
    fprintf(fptr, "14e KillEnd\n" );     // SHIFT [-]
    fprintf(fptr, "44e KillBeg\n" );     // CTRL [-]
//&>>&6 0 6 14
//&<<&        // Copying of chars
    fprintf(fptr,"03b CSave\n"      );  //  F1:            Ch
    fprintf(fptr,"13b CMove\n"      );  //  SHIFT-F1:      Ch
    fprintf(fptr,"23b WSave\n"      );  //  ALT-F1:        Wo
    fprintf(fptr,"33b WMove\n"      );  //  ALT-SHIFT-F1:  Wo
    fprintf(fptr,"63b BWord\n"      );  //  CTRL-ALT-F1
    fprintf(fptr,"73b BWord\n"      );  //  CTRL-SHIFT-ALT-F1
    fprintf(fptr,"43b TSave\n"      );  //  CTRL-F1:       Li
    fprintf(fptr,"53b TMove\n"      );  //  CTRL-SHIFT-F1: Li
    fprintf(fptr,"03c CRest\n"      );  //  F2: Clipboard =>
    fprintf(fptr,"13c CClear\n"     );  //  SHIFT-F2: Clear C
//&>>&6 0 6 1B
//&<<&        // Copying of lines
// Copying of lines
    fprintf(fptr, "03d LSave\n");  // F3:
    fprintf(fptr, "43d LTSave\n");  // CTRL-F3:
    fprintf(fptr, "13d LMove\n");  // SHIFT-F3:
    fprintf(fptr, "53d LTMove\n");  // CTRL-SHIFT-F3
    fprintf(fptr, "03e LRest\n");  // F4:
    fprintf(fptr, "13e LClear\n");  // SHIFT-F4:
//&>>&6 0 6 0
//&<<&        // Various types of exit
// Various types of exit

    fprintf(fptr,"001 Escape\n"); // ESC: temporary exit to DOS
    fprintf(fptr,"101 EscapeExec\n"); // SHIFT-ESC: execute current line
    fprintf(fptr,"23e EscapeExecLCB\n"); // ALT-F4: execute ClipBoard
//&>>&4 0 4 1E
//&<<&        // Various switchings  (ins/ovr , alt key , status line .........)
    fprintf(fptr, "21c S_AutoIndent\n");   // ALT-ENTER    (on/off auto-indent)
    fprintf(fptr, "452 S_ModeIns\n");   // CTRL-INS (insert mode)
    fprintf(fptr, "453 S_ModeOvr\n");   // CTRL-DEL (overwrite mode)
    fprintf(fptr, "46f S_ModeIns\n");   // CTRL-INS (insert mode)
    fprintf(fptr, "470 S_ModeOvr\n");   // CTRL-DEL (overwrite mode)
    fprintf(fptr, "802 S_ACode1\n");   // CAPS+1 switch to QQ keyboard as alt
    fprintf(fptr, "803 S_ACode2\n");   // CAPS+2 switch to QJ keyboard as alt
    fprintf(fptr, "804 S_ACode3\n");   // CAPS+3 switch to ÅÎ keyboard as alt
    fprintf(fptr, "41f S_StatusLine\n");   // Ctrl+'S' switch status line ON/OFF
    fprintf(fptr, "837 S_SearchMode\n");   // CAPS + "*\n"  search modes switching
//&>>&5 0 5 16
//&<<&        // Search & replace commands
    fprintf(fptr,"037 SearchFWD\n");       // "*\n" search forward
    fprintf(fptr,"137 SearchBCK\n");       // SHIFT+"*\n" search back
    fprintf(fptr,"237 Replace\n");       // ALT+"*\n" REPLACE
    fprintf(fptr,"437 SearchPage\n");       //  CTRL+"*\n"  switch into SearchPage
//&>>&3 0 3 13
        fprintf(fptr,"852 PageIns\n");    // CAPS+INS insert new page
        fprintf(fptr,"86f PageIns\n");    // CAPS+INS insert new page
//&<<&        // Marked Lines Commands

    fprintf(fptr,"848 MarkUp\n");  // CAPS+UP
    fprintf(fptr,"868 MarkUp\n");  // CAPS+UP
    fprintf(fptr,"850 MarkDown\n");  // CAPS+DOWN
    fprintf(fptr,"86d MarkDown\n");  // CAPS+DOWN
    fprintf(fptr,"c48 MarkTUp\n");  // CAPS+CTRL+UP
    fprintf(fptr,"c68 MarkTUp\n");  // CAPS+CTRL+UP
    fprintf(fptr,"c50 MarkTDown\n");  // CAPS+CTRL+DOWN
    fprintf(fptr,"c6d MarkTDown\n");  // CAPS+CTRL+DOWN
    fprintf(fptr,"948 MarkPUp\n");  // CAPS+SHIFT+UP
    fprintf(fptr,"968 MarkPUp\n");  // CAPS+SHIFT+UP
    fprintf(fptr,"950 MarkPDown\n");  // CAPS+SHIFT+DOWN
    fprintf(fptr,"96d MarkPDown\n");  // CAPS+SHIFT+DOWN

    fprintf(fptr,"03f MarkSaveB\n");  // F5 - push marked lines to stack
    fprintf(fptr,"040 MarkRestB\n");  // F6 - pop marked lines from stack

    fprintf(fptr,"c4b MarkLast\n");     // CAPS-CTRL-LEFT  : LastMarked();
    fprintf(fptr,"c6a MarkLast\n");     // CAPS-CTRL-LEFT  : LastMarked();
    fprintf(fptr,"c4d MarkFirst\n");     // CAPS-CTRL-RIGHT
    fprintf(fptr,"c6b MarkFirst\n");     // CAPS-CTRL-RIGHT

    fprintf(fptr,"84b MarkPrev\n");    // CAPS-Left
    fprintf(fptr,"86a MarkPrev\n");    // CAPS-Left
    fprintf(fptr,"84d MarkNext\n");    // CAPS-Right
    fprintf(fptr,"86b MarkNext\n");    // CAPS-Right

    fprintf(fptr,"80e MarkBS\n");                   // CAPS-BS

//&>>&1B 0 15 13
//&<<&        // Macros
    fprintf(fptr,"041 Macro\n");        // F7
    fprintf(fptr,"141 MacroRec\n");     // SHIFT+F7
//&>>&0 0 0 23
        }
//&>>&5 0 5 1C
//&<<&    if(etype==1){    /// os2
    if(etype==1){    /// os2
//&<<&        // Movement
    fprintf(fptr, "048 Up\n");
    fprintf(fptr, "050 Down\n");
    fprintf(fptr, "04b Left\n");
    fprintf(fptr, "04d Right\n");

    fprintf(fptr, "48d TUp\n");  // Ctrl + Up
    fprintf(fptr, "491 TDown\n");  // Ctrl + Down
    fprintf(fptr, "473 TLeft\n");  // Ctrl + Left
    fprintf(fptr, "474 TRight\n");  // Ctrl + Right

    fprintf(fptr, "148 PUp\n");  // Shift + Up
    fprintf(fptr, "150 PDown\n");  // Shift + Down
    fprintf(fptr, "14b PLeft\n");  // Shift + Left
    fprintf(fptr, "14d PRight\n");  // Shift + Right

    fprintf(fptr, "298 FUp\n");  // Alt + Up
    fprintf(fptr, "2A0 FDown\n");  // Alt + Down
    fprintf(fptr, "29b FLeft\n");  // Alt + Left
    fprintf(fptr, "29d FRight\n");  // Alt + Right

    fprintf(fptr, "01c Enter\n");  // Enter
    fprintf(fptr, "11c REnter\n");  // Shift + Enter

    fprintf(fptr, "00f Tab\n");  // Tab
    fprintf(fptr, "10f LTab\n");  // Shift + Tab

//&>>&0 0 0 14
//&<<&        // Insert and delete
// Insert and delete

    fprintf(fptr, "052 InsCh\n");  // Ins
    fprintf(fptr, "053 DelCh\n");  // Del
    fprintf(fptr, "152 InsLine\n");  // Shift + Ins
    fprintf(fptr, "2a2 InsFold\n");  // Alt + Ins
    fprintf(fptr, "153 DelLine\n");  // Shift + Del
    fprintf(fptr, "2a3 DelLine\n");  // Alt + Del
    fprintf(fptr, "00e BS\n");  // BS
    fprintf(fptr, "10e R_BS\n");  // Shift + BS

//&>>&7 0 7 0
//&<<&        // Line Killing
// Line Killing
    fprintf(fptr, "04a KillWord\n" );     // [+]
    fprintf(fptr, "14a KillEnd\n" );     // SHIFT [+]
    fprintf(fptr, "490 KillBeg\n" );     // CTRL [+]
    fprintf(fptr, "04e KillWord\n" );     // [-]
    fprintf(fptr, "14e KillEnd\n" );     // SHIFT [-]
    fprintf(fptr, "48e KillBeg\n" );     // CTRL [-]
//&>>&6 0 6 14
//&<<&        // Copying of chars
    fprintf(fptr,"03b CSave\n"      );  //  F1:            Ch
    fprintf(fptr,"154 CMove\n"      );  //  SHIFT-F1:      Ch
    fprintf(fptr,"268 WSave\n"      );  //  ALT-F1:        Wo
    fprintf(fptr,"368 WMove\n"      );  //  ALT-SHIFT-F1:  Wo
    fprintf(fptr,"668 BWord\n"      );  //  CTRL-ALT-F1
    fprintf(fptr,"768 BWord\n"      );  //  CTRL-SHIFT-ALT-F1
    fprintf(fptr,"45e TSave\n"      );  //  CTRL-F1:       Li
    fprintf(fptr,"55e TMove\n"      );  //  CTRL-SHIFT-F1: Li
    fprintf(fptr,"03c CRest\n"      );  //  F2: Clipboard =>
    fprintf(fptr,"155 CClear\n"     );  //  SHIFT-F2: Clear C
//&>>&6 0 6 1B
//&<<&        // Copying of lines
// Copying of lines
    fprintf(fptr, "03d LSave\n");  // F3:
    fprintf(fptr, "460 LTSave\n");  // CTRL-F3:
    fprintf(fptr, "156 LMove\n");  // SHIFT-F3:
    fprintf(fptr, "560 LTMove\n");  // CTRL-SHIFT-F3
    fprintf(fptr, "03e LRest\n");  // F4:
    fprintf(fptr, "157 LClear\n");  // SHIFT-F4:
//&>>&6 0 6 1F
//&<<&        // Various types of exit
// Various types of exit

    fprintf(fptr,"001 Escape\n"); // ESC: temporary exit to DOS
    fprintf(fptr,"101 EscapeExec\n"); // SHIFT-ESC: execute current line
    fprintf(fptr,"26b EscapeExecLCB\n"); // ALT-F4: execute ClipBoard
//&>>&2 0 2 13
//&<<&        // Various switchings  (ins/ovr , alt key , status line .........)
    fprintf(fptr, "21c S_AutoIndent\n");   // ALT-ENTER    (on/off auto-indent)
    fprintf(fptr, "492 S_ModeIns\n");   // CTRL-INS (insert mode)
    fprintf(fptr, "493 S_ModeOvr\n");   // CTRL-DEL (overwrite mode)
    fprintf(fptr, "802 S_ACode1\n");   // CAPS+1 switch to QQ keyboard as alt
    fprintf(fptr, "803 S_ACode2\n");   // CAPS+2 switch to QJ keyboard as alt
    fprintf(fptr, "804 S_ACode3\n");   // CAPS+3 switch to ÅÎ keyboard as alt
    fprintf(fptr, "41f S_StatusLine\n");   // Ctrl+'S' switch status line ON/OFF
    fprintf(fptr, "837 S_SearchMode\n");   // CAPS + "*\n"  search modes switching
//&>>&1 0 1 0
//&<<&        // Search & replace commands
    fprintf(fptr,"037 SearchFWD\n");       // "*\n" search forward
    fprintf(fptr,"137 SearchBCK\n");       // SHIFT+"*\n" search back
    fprintf(fptr,"237 Replace\n");       // ALT+"*\n" REPLACE
    fprintf(fptr,"496 SearchPage\n");       //  CTRL+"*\n"  switch into SearchPage
//&>>&3 0 3 13
        fprintf(fptr,"852 PageIns\n");    // CAPS+INS insert new page
        fprintf(fptr,"86f PageIns\n");    // CAPS+INS insert new page
//&<<&        // Marked Lines Commands

    fprintf(fptr,"848 MarkUp\n");  // CAPS+UP
    fprintf(fptr,"850 MarkDown\n");  // CAPS+DOWN
    fprintf(fptr,"c8d MarkTUp\n");  // CAPS+CTRL+UP
    fprintf(fptr,"c91 MarkTDown\n");  // CAPS+CTRL+DOWN
    fprintf(fptr,"948 MarkPUp\n");  // CAPS+SHIFT+UP
    fprintf(fptr,"950 MarkPDown\n");  // CAPS+SHIFT+DOWN

    fprintf(fptr,"03f MarkSaveB\n");  // F5 - push marked lines to stack
    fprintf(fptr,"040 MarkRestB\n");  // F6 - pop marked lines from stack

    fprintf(fptr,"c73 MarkLast\n");     // CAPS-CTRL-LEFT  : LastMarked();
    fprintf(fptr,"c74 MarkFirst\n");     // CAPS-CTRL-RIGHT

    fprintf(fptr,"84b MarkPrev\n");    // CAPS-Left
    fprintf(fptr,"84d MarkNext\n");    // CAPS-Right

    fprintf(fptr,"80e MarkBS\n");                   // CAPS-BS

//&>>&12 0 12 10
//&<<&        // Macros
    fprintf(fptr,"041 Macro\n");     // F7
    fprintf(fptr,"15a MacroRec\n");     // SHIFT+F7
//&>>&1 0 1 0
        }
//&>>&5 0 5 14
//&<<&    digits/Letters/Delimiters

fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  2  , 0x100+ 2 , 0x200+ 2 , 0x300+ 2  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  3  , 0x100+ 3 , 0x200+ 3 , 0x300+ 3  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  4  , 0x100+ 4 , 0x200+ 4 , 0x300+ 4  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  5  , 0x100+ 5 , 0x200+ 5 , 0x300+ 5  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  6  , 0x100+ 6 , 0x200+ 6 , 0x300+ 6  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  7  , 0x100+ 7 , 0x200+ 7 , 0x300+ 7  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  8  , 0x100+ 8 , 0x200+ 8 , 0x300+ 8  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" ,  9  , 0x100+ 9 , 0x200+ 9 , 0x300+ 9  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 10  , 0x100+10 , 0x200+10 , 0x300+10  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 11  , 0x100+11 , 0x200+11 , 0x300+11  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 12  , 0x100+12 , 0x200+12 , 0x300+12  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 13  , 0x100+13 , 0x200+13 , 0x300+13  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 41  , 0x100+41 , 0x200+41 , 0x300+41  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 43  , 0x100+43 , 0x200+43 , 0x300+43  );
fprintf( fptr, " %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n %0004x Ascii0\n" , 53  , 0x100+53 , 0x200+53 , 0x300+53  );

fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 16  , 0x100+16 , 0x200+16 , 0x300+16  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 17  , 0x100+17 , 0x200+17 , 0x300+17  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 18  , 0x100+18 , 0x200+18 , 0x300+18  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 19  , 0x100+19 , 0x200+19 , 0x300+19  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 20  , 0x100+20 , 0x200+20 , 0x300+20  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 21  , 0x100+21 , 0x200+21 , 0x300+21  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 22  , 0x100+22 , 0x200+22 , 0x300+22  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 23  , 0x100+23 , 0x200+23 , 0x300+23  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 24  , 0x100+24 , 0x200+24 , 0x300+24  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 25  , 0x100+25 , 0x200+25 , 0x300+25  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 30  , 0x100+30 , 0x200+30 , 0x300+30  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 31  , 0x100+31 , 0x200+31 , 0x300+31  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 32  , 0x100+32 , 0x200+32 , 0x300+32  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 33  , 0x100+33 , 0x200+33 , 0x300+33  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 34  , 0x100+34 , 0x200+34 , 0x300+34  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 35  , 0x100+35 , 0x200+35 , 0x300+35  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 36  , 0x100+36 , 0x200+36 , 0x300+36  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 37  , 0x100+37 , 0x200+37 , 0x300+37  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 38  , 0x100+38 , 0x200+38 , 0x300+38  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 44  , 0x100+44 , 0x200+44 , 0x300+44  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 45  , 0x100+45 , 0x200+45 , 0x300+45  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 46  , 0x100+46 , 0x200+46 , 0x300+46  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 47  , 0x100+47 , 0x200+47 , 0x300+47  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 48  , 0x100+48 , 0x200+48 , 0x300+48  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 49  , 0x100+49 , 0x200+49 , 0x300+49  );
fprintf( fptr, " %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n %0004x Ascii1\n" , 50  , 0x100+50 , 0x200+50 , 0x300+50  );

fprintf( fptr, " %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n" , 26  , 0x100+26 , 0x200+26 , 0x300+26  );
fprintf( fptr, " %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n" , 27  , 0x100+27 , 0x200+27 , 0x300+27  );
fprintf( fptr, " %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n" , 39  , 0x100+39 , 0x200+39 , 0x300+39  );
fprintf( fptr, " %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n" , 40  , 0x100+40 , 0x200+40 , 0x300+40  );
fprintf( fptr, " %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n" , 51  , 0x100+51 , 0x200+51 , 0x300+51  );
fprintf( fptr, " %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n %0004x Ascii2\n" , 52  , 0x100+52 , 0x200+52 , 0x300+52  );

fprintf( fptr, " %0004x Space \n %0004x Space \n %0004x Space \n %0004x Space \n" , 57  , 0x100+57 , 0x200+57 , 0x300+57  );

//&>>&31 0 13 0
//&<<&    if(etype==2){    //// Linux Console
    if(etype==2){    //// Linux Console
        fprintf(fptr, " 702 Console\n");
        fprintf(fptr, " 703 Console\n");
        fprintf(fptr, " 704 Console\n");
        fprintf(fptr, " 705 Console\n");
        fprintf(fptr, " 706 Console\n");
        fprintf(fptr, " 707 Console\n");
        fprintf(fptr, " 708 Console\n");
        fprintf(fptr, " 709 Console\n");
        }
//&>>&1 0 1 1E
    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&7 0 7 0
//&<<&void putMacro(FILE *fptr);
void putMacro(FILE *fptr){
    fprintf(fptr,"&<<&*MACRO*\n");

//&<<&    fprintf(fptr,"&<<&Arithmetics & ...\n");
    fprintf(fptr,"&<<&Arithmetics & ...\n");
    fprintf(fptr,"proc add %03x mathop endp\n",MATHOP_ADD);
    fprintf(fptr,"proc sub %03x mathop endp\n",MATHOP_SUB);
    fprintf(fptr,"proc mul %03x mathop endp\n",MATHOP_MUL);
    fprintf(fptr,"proc div %03x mathop endp\n",MATHOP_DIV);
    fprintf(fptr,"proc mod %03x mathop endp\n",MATHOP_MOD);
    fprintf(fptr,"proc and %03x mathop endp\n",MATHOP_AND);
    fprintf(fptr,"proc or  %03x mathop endp\n",MATHOP_OR );
    fprintf(fptr,"proc xor %03x mathop endp\n",MATHOP_XOR);
    fprintf(fptr,"proc eq  %03x predicate endp\n",PREDICATE_EQ);
    fprintf(fptr,"proc ne  %03x predicate endp\n",PREDICATE_NE);
    fprintf(fptr,"proc lt  %03x predicate endp\n",PREDICATE_LT);
    fprintf(fptr,"proc gt  %03x predicate endp\n",PREDICATE_GT);
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&C 0 C 1F
//&<<&    fprintf(fptr,"&<<&Definitions...\n");
    fprintf(fptr,"&<<&Definitions...\n");

    fprintf(fptr,"proc pushf   %03x push endp\n",PUSH_FLAG);
    fprintf(fptr,"proc pushl   %03x push endp\n",PUSH_CLINE_L);
    fprintf(fptr,"proc pushls  %03x push endp\n",PUSH_CLINE_S);
    fprintf(fptr,"proc pushc   %03x push endp\n",PUSH_CHAR);
    fprintf(fptr,"proc pushlcb %03x push endp\n",PUSH_LCB);
    fprintf(fptr,"proc pushccb %03x push endp\n",PUSH_CCB);

    fprintf(fptr,"proc cvtI2SH %03x convert endp\n", CONVERT_I2SH);
    fprintf(fptr,"proc cvtI2SD %03x convert endp\n", CONVERT_I2SD);
    fprintf(fptr,"proc cvtS2IH %03x convert endp\n", CONVERT_S2IH);
    fprintf(fptr,"proc cvtS2ID %03x convert endp\n", CONVERT_S2ID);
    fprintf(fptr,"proc cvtS2L  %03x convert endp\n", CONVERT_S2L );
    fprintf(fptr,"proc cvtL2S  %03x convert endp\n", CONVERT_L2S );
    fprintf(fptr,"proc cvtI2C  %03x convert endp\n", CONVERT_I2C );
    fprintf(fptr,"proc cvtC2I  %03x convert endp\n", CONVERT_C2I );


    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&4 0 4 0
//&<<&    fprintf(fptr,"&<<&Movement...\n");
    fprintf(fptr,"&<<&Movement...\n");
//&<<&    fprintf(fptr,"proc PRight\n");
    fprintf(fptr,"&<<&proc PRight\n");
    fprintf(fptr,"proc PRight\n");
    fprintf(fptr,"    pushc \' \' gt\n");
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        Right\n");
    fprintf(fptr,"        pushc \' \' gt\n");
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"    pushc \' \' eq\n");
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        Right\n");
    fprintf(fptr,"        pushc \' \' eq\n");
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"endp\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&0 0 0 0
//&<<&    fprintf(fptr,"proc PLeft\n");
    fprintf(fptr,"&<<&proc PLeft\n");
    fprintf(fptr,"proc PLeft\n");
    fprintf(fptr,"    pushc \' \' ne\n");
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        Left\n");
    fprintf(fptr,"        pushc \' \' ne pushf\n");
    fprintf(fptr,"        %03x ioctl 0 gt pushf\n",IOCTL_CX);
    fprintf(fptr,"        and pop\n");
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"    pushc \' \' eq\n");
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        Left\n");
    fprintf(fptr,"        pushc \' \' eq pushf\n");
    fprintf(fptr,"        %03x ioctl 0 gt pushf\n",IOCTL_CX);
    fprintf(fptr,"        and pop\n");
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"endp\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&12 0 12 1
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&2 0 2 1A
//&<<&    fprintf(fptr,"&<<&Editing,killing...\n");
    fprintf(fptr,"&<<&Editing,killing...\n");
//&<<&    fprintf(fptr,"proc KillWord\n");
    fprintf(fptr,"&<<&proc KillWord\n");
    fprintf(fptr,"proc KillWord\n");
    fprintf(fptr,"    %03x ioctl if ret endif\n",IOCTL_ISMARKED);
    fprintf(fptr,"    BWord\n");
    fprintf(fptr,"    pushc \' \' gt\n");
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        DelCh\n");
    fprintf(fptr,"        pushc \' \' gt\n");
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"    pushc \' \' eq\n");
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        DelCh\n");
    fprintf(fptr,"        pushc \' \' eq\n");
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"endp\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&E 0 E 0
//&<<&    fprintf(fptr,"proc R_BS\n");
    fprintf(fptr,"&<<&proc R_BS\n");
    fprintf(fptr,"proc R_BS\n");
    fprintf(fptr,"    %03x ioctl if ret endif\n",IOCTL_ISMARKED);
    fprintf(fptr,"    %03x ioctl if ret endif\n",IOCTL_ISFOLD);
    fprintf(fptr,"    %03x ioctl 0 eq if ret endif\n",IOCTL_SY);
    fprintf(fptr,"    KillBeg\n");
    fprintf(fptr,"    pushls\n");
    fprintf(fptr,"    DelLine\n");
    fprintf(fptr,"    Up\n");
    fprintf(fptr,"    TRight\n");
    fprintf(fptr,"    %03x ioctl\n",IOCTL_CX);
    fprintf(fptr,"    swp\n");
    fprintf(fptr,"    pop\n");
    fprintf(fptr,"    dup %03x ioctl lt\n",IOCTL_CX);
    fprintf(fptr,"    do\n");
    fprintf(fptr,"        Left\n");
    fprintf(fptr,"        dup %03x ioctl lt\n",IOCTL_CX);
    fprintf(fptr,"    enddo\n");
    fprintf(fptr,"endp\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&7 0 7 1C
//&<<&    fprintf(fptr,"proc REnter\n");
    fprintf(fptr,"&<<&proc REnter\n");
    fprintf(fptr,"proc REnter\n");
    fprintf(fptr,"    007 ioctl if ret endif\n");
    fprintf(fptr,"    pushls\n");
    fprintf(fptr,"    KillEnd\n");
    fprintf(fptr,"    Down\n");
    fprintf(fptr,"    cvtS2L\n");
    fprintf(fptr,"    pop\n");
    fprintf(fptr,"    KillBeg\n");
    fprintf(fptr,"endp\n");
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&B 0 B 0
    fprintf(fptr,"&>>&0 0 0 0\n");
//&>>&2 0 2 2A

    fprintf(fptr,"proc HelloWorld\n");
    fprintf(fptr,"    InsLine\n");
    fprintf(fptr,"    TLeft\n");
    fprintf(fptr,"    Tab Tab Tab Tab\n");
    fprintf(fptr,"    \"Hello World! \"\n");
    fprintf(fptr,"    pop\n");
    fprintf(fptr,"endp\n");

    fprintf(fptr,"&>>&0 0 0 0\n");
    }
//&>>&4 0 4 1

//&<<&void main(){
int main(int argc,char **argv){
    FILE *fptr;
    if(argc>1) fptr=fopen(argv[1],"w");
//&<<&    else {
    else {
        char *env_home,*env_mmm;
        env_home=getenv("HOME");
        env_mmm=getenv("MMM");
        char *RunDir=new char[0x100]; if(RunDir==0)exit(1);
        strcpy(RunDir,env_home!=0?env_home:
                      env_mmm!=0 ?env_mmm :
#ifdef __linux__
                      "./");
        if(RunDir[strlen(RunDir)-1]!='/') strcat(RunDir,"/");
#else
                      ".\\");
        if(RunDir[strlen(RunDir)-1]!='\\') strcat(RunDir,"\\");
#endif
        strcat(RunDir,"mmm_base.cfg");
        printf("Editing file <%s>\n",RunDir);
        fptr=fopen(RunDir,"w");
        }
//&>>&E 0 E 1F

    if(fptr==0) {
        printf("Cannot open output file\n");
        exit(-1);
        }

////    putSearch(fptr);
////    putTemp(fptr);
////    putLCB(fptr);
    putExtensions(fptr);
    putKeyboardLayouts(fptr);
    putSetup(fptr);
    putCommand(fptr);
    putMacro(fptr);
    return 0;
    }
//&>>&11 0 11 0
#if 0
//&<<&*MACRO*
//&<<&Arithmetics & ...
proc add 0 mathop endp
proc sub 1 mathop endp
proc mul 2 mathop endp
proc div 3 mathop endp
proc mod 4 mathop endp
proc and 5 mathop endp
proc or  6 mathop endp
proc xor 7 mathop endp

proc eq  0 predicate endp
proc ne  1 predicate endp
proc lt  2 predicate endp
proc gt  3 predicate endp
//&>>&C 0 C 15
//&<<&proc PrintString
proc PrintString
    4 convert Enter pop
endp
//&>>&1 0 1 9
//&<<&proc PrintInt
proc PrintInt
    dup
    0 convert
%    pop
    PrintString
endp
//&>>&2 0 2 5
//&<<&proc TestQuery
proc TestQuery
    query
    0 convert
    "type is:" pop
    pop
    "." pop
endp
//&>>&7 0 7 0
//&<<&proc TestSgetSput
proc TestSgetSput
    "push5"
    "push4"
    "push3"
    "push2"
    "push1"

    " !StrangeValue(for3)! " 3 sput
    1 sget pop
    2 sget pop
    3 sget pop
    4 sget pop
    5 sget pop
    %del del del del del
    pop pop pop pop pop
endp
//&>>&E 0 E 1
//&<<&proc TestIf
proc TestIf
    10 20 eq
    if
        "a = b" pop
    else
        "a != b" pop
    endif

    10 20 gt
    if
        "a > b" pop
    else
        "a < b" pop
    endif
endp
//&>>&8 0 8 0
//&<<&proc Test2Z
proc Test2Z
    dup 0 eq
    if
        "==0 " pop
    else
        dup 0 gt
        if
            ">0 " pop
        else
            "<0 " pop
        endif
    endif
endp
//&>>&3 0 3 0
//&<<&proc TestDo
proc TestDo
'a'
dup 'z' lt
do
    Down TLeft
    dup 6 convert pop % enumerate lines by letters a-z
    1 add
    dup 'z' lt
enddo

endp
//&>>&5 0 5 0
//&<<&proc TestIoctl
proc TestIoctl
    "typing mode :" pop  1 ioctl if "Ins" else "Ovr" endif          pop Enter
    "search :" pop  3 ioctl if "sensetive" else "insensetive" endif pop Enter
    "In Search Page :" pop  0a ioctl if "yes" else "no" endif       pop Enter
    "In Temp Page :" pop  0b ioctl if "yes" else "no" endif         pop Enter
    "Number Of lines:" pop 0c  ioctl 1 convert                      pop Enter
    "Number Of col-s:" pop 0d  ioctl 1 convert                      pop Enter
    "Line Number    :" pop 012 ioctl 1 convert                      pop Enter
    "cx=" pop     0e  ioctl  1 convert                              pop Enter
    "sx=" pop     0f  ioctl  1 convert                              pop Enter
    "sy=" pop     011 ioctl  1 convert                              pop Enter
endp
//&>>&2 0 2 0
//&<<&proc nPRight
proc nPRight
    4 push 20 gt
    do
        Right
        4 push 20 gt
    enddo

    4 push 20 eq
    do
        Right
        4 push
        4 push 20 eq
    enddo
endp
//&>>&0 0 0 0

proc HelloWorld
    nPRight
endp
//&>>&A 0 A 7
#endif
///// mmm_cfg.err mmm_cfg.err mmm_cfg.err mmm_cfg.err mmm_cfg.err
///// -a mmm.cfg mmm.cfg mmm.cfg mmm.cfg mmm.cfg
///// -a ../../mmm_base.cfg ../mmm.cfg ../mmm.cfg ../mmm.cfg ../mmm.cfg
//&>>&C 0 C 8
