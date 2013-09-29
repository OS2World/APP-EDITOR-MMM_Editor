
#define LEN_LANGUAGE     0x50
#define LEN_COMMAND_ARRAY  0x4d
#define USER_FUNC        (LEN_LANGUAGE+LEN_COMMAND_ARRAY)

enum { MACRO_PROC, MACRO_KEYSEQ };  // macros styles

enum{FILE_FOLD,FILE_LIST,FILE_ASCII};  // style of file opening

enum { SEARCH_FORWARD , SEARCH_BACK }; // search directions

#define REDRAW_WHOLE_SCREEN 666
#define REDRAW_CURRENT_LINE 1

#define  INFTY         32767
#define  TAB_STEP_SIZE 3

#define LINE_CHG   1
#define LINE_OTHER 2
#define LINE_NEW   4

//&<<&enum {  // datatypes for stack
enum{ SDATA_LINE=0,
      SDATA_INT=1,
      SDATA_STRING=2 }; // datatypes for stack
//&>>&0 0 0 1B
//&<<&enum {  // Token-constants definition (for compiler & interpreter
enum {  TKN_NULL_             ,
        TKN_RETURN_           ,

        TKN_CONST_STRING_     , // constants
        TKN_CONST_CHAR_       ,
        TKN_CONST_INT_        ,

        TKN_GOTO_             , // Language operators
        TKN_IF_               ,
        TKN_ELSE_             ,
        TKN_ENDIF_            ,
        TKN_DO_               ,
        TKN_ENDDO_            ,
        TKN_BREAK_            ,
        TKN_PROC_             ,
        TKN_ENDP_             ,

        TKN_SWP_              , // stack operators
        TKN_DUP_              ,
        TKN_DEL_              ,
        TKN_SGET_             ,
        TKN_SPUT_             ,

        TKN_MATHOP_           ,
        TKN_PREDICATE_        ,

        TKN_CONVERT_          , // I/O operators
        TKN_QUERY_            ,
        TKN_POP_              ,
        TKN_PUSH_             ,
        TKN_IOCTL_            ,

        TKN_INITIAL_          , // specials for compiler/interpreter
        TKN_INPROC_           ,
        TKN_CALL_
        };
//&>>&1B 0 12 0
//&<<&enum {  // mathematical operations
enum { MATHOP_ADD=0,
       MATHOP_SUB=1,
       MATHOP_MUL=2,
       MATHOP_DIV=3,
       MATHOP_MOD=4,
       MATHOP_AND=5,
       MATHOP_OR =6,
       MATHOP_XOR=7
       };  // mathematical operations
//&>>&0 0 0 4
//&<<&enum {  // predicates
enum { PREDICATE_EQ=0,
       PREDICATE_NE=1,
       PREDICATE_LT=2,
       PREDICATE_GT=3
       }; // predicates

//&>>&0 0 0 16
//&<<&enum {  // conversions
enum { CONVERT_I2SH=0,
       CONVERT_I2SD=1,
       CONVERT_S2IH=2,
       CONVERT_S2ID=3,
       CONVERT_S2L =4,
       CONVERT_L2S =5,
       CONVERT_I2C =6,
       CONVERT_C2I =7
       };
//&>>&1 0 1 0
//&<<&enum {  // push type
enum {
        PUSH_FLAG    = 0  ,
        PUSH_CLINE_L = 1  ,
        PUSH_CLINE_S = 2  ,
        PUSH_CCB     = 3  ,
        PUSH_LCB     = 4  ,
        PUSH_CHAR    = 5
        };
//&>>&2 0 2 14
//&<<&enum {  // ioctl
enum {
        IOCTL_MODEINS     = 0x1 ,     // ������, ����祭 �� ०�� ��⠢��.
        IOCTL_MODEAI      = 0x2 ,     // ������, ����祭 �� ०�� ��⮮���㯠.
        IOCTL_MODESEARCH  = 0x3 ,     // ������, ०�� ���᪠
        IOCTL_MODECAPS    = 0x4 ,     // ������, ����祭 �� CAPS (���孨� �㪢� ��
        IOCTL_MODEALT     = 0x5 ,     // ������, ����祭 �� ALT (---''---)
        IOCTL_ISFOLD      = 0x6 ,     // ������, ⥪��� ��ப� -- 䮫�?
        IOCTL_ISMARKED    = 0x7 ,     // ������, ����祭� �� ⥪��� ��ப�.
        IOCTL_ISLAST      = 0x9 ,     // ������, ��᫥���� ��ப� � 䮫��?
        IOCTL_INSEARCH    =0x0a ,     // ������, ��室���� �� � {\tt SearchPage}.
        IOCTL_INTEMP      =0x0b ,     // ������, ��室���� �� � {\tt *TEMP*}.
        IOCTL_MAXY        =0x0c ,     // �������� �� �⥪ ���-�� ��ப �� �࠭�
        IOCTL_MAXX        =0x0d ,     // �������� �� �⥪ ���-�� �⮫�殢 �� �࠭�
        IOCTL_CX          =0x0e ,     // �������� �� �⥪ {\tt cx}
        IOCTL_SX          =0x0f ,     // �������� �� �⥪ {\tt sx}
        IOCTL_SY          =0x11 ,     // �������� �� �⥪ {\tt sy}
        IOCTL_LINENUM     =0x12       // �������� �� �⥪ ����� ��ப�
        };

//&>>&8 0 8 0

//&>>&17 0 14 1F
