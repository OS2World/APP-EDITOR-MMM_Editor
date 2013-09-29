copy a:*.cpp  .
copy a:*.h    .
copy a:make*  .
copy a:*.bat  .
copy a:*.dir  .

copy a:\tex\*.dir .\tex
copy a:\tex\*.tex .\tex
copy a:\tex\*.sty .\tex

copy a:\compiler\*.dir .\compiler
copy a:\compiler\*.cpp .\compiler
copy a:\compiler\*.h   .\compiler
@Rem -&>>&D 0 D 0
