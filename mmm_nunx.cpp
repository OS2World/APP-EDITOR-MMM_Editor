#include "mmm_comm.h"
#include <direct.h>
#include <dos.h>

char RunDir[0x100];
//&<<&char *MFileName(char *s){
char *MFileName(char *s){
  char *xx;
  xx=getenv("MMM");
  if(xx!=0){
      strcpy(RunDir,xx);
      if(RunDir[strlen(RunDir)-1]!='\\') strcat(RunDir,"\\");
      }
  char *x=new char[strlen(s)+strlen(RunDir)+1]; MemTest(x!=0);
  strcpy(x,RunDir);
  for(xx=x+strlen(x);*--xx!='\\' && *xx!='/' ;) ;
  strcpy(xx+1,s);
  return x;
}
//&>>&2 0 2 1

//&<<&File::File(char *name,int fx);
File::File(char *name,int fx):flg(fx),Fold(0){
  int i;
  for(i=0;name[i];i++) if(name[i]=='/') name[i]='\\';
  if(name[0] && name[1]==':'){
    int x=(name[0]&0x1f);               // 1='A'
//    unsigned int ndrv;
    SaveSetDrive(x);
    name+=2;
  }
  for(i=strlen(name);--i>=0;) if(name[i]=='\\'){ name[i]=0; break; }
  if(i>=0){
    SaveChDir(i==0 ? "\\" : name);
  }
  name+=i+1; if(*name==0) name="mmm.dir";
  Realloc(strlen(name));
  strcpy(buf,name);

  CurDev=SaveGetDrive();
  CurDir=getcurdir();                   // current disk

  if(WildCard(buf)) MkWild();
  else{
    FILE *f=fopen(buf,"r");
    if(f){
      DrawLine(" Reading ...", cur->sy , 0x1f, mmm_screen.GetW() );
      Editor.SetComment(buf);
      templine=new char[INFTY+1]; MemTest(templine!=0);
      FileLinesCounter=0;
      Read(f,flg);

//&<<&      #ifdef _INCLUDE_SAFETY_MODULE_
#ifdef _INCLUDE_SAFETY_MODULE_
      {
      int l;
      Line *rpos;
      rpos=pos;
      while(rpos->next) rpos=rpos->next;
      while( fgets(templine,INFTY,f) ){
            l=strlen(templine);
            while(l>0 && byte(templine[l-1])<' ') templine[--l]=0;
            NewLine(templine)->LinkBefore(rpos);
            }
      }
#endif
//&>>&D 0 D 0

      delete templine;
      fclose(f);
    }
  }
}
//&>>&18 0 F 39

//// mmm_nunx.err mmm_nunx.err mmm_nunx.err mmm_nunx.err mmm_nunx.err
//&>>&7 0 7 21
