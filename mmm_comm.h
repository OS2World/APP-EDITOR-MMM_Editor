/**********************************************
*   COMMON include file for MMMX Editor       *
*   Contains UNIX/notUNIX specific functions  *
***********************************************/

#ifndef __INCLUDED_MMM_COMMON__
#define __INCLUDED_MMM_COMMON__
#include "mmmx.h"
//&<<&#ifdef __DOS__ / WIN32 / __OS2__ / __linux__
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
//&>>&0 0 0 0

extern char RunDir[];
char *MFileName(char *s);

//&<<&#ifdef __linux__   // for compatibility
#ifdef __linux__
  extern void     _dos_getdrive( unsigned *__drive );
  extern void     _dos_setdrive( unsigned __drivenum, unsigned *__drives );
#endif
//&>>&1 0 1 0

#endif
//&>>&D 0 D 1
