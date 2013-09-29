verify =on

copy *.cpp a:
copy *.h   a:
copy make* a:
copy make*.* a:
copy *.bat a:
copy *.dir a:

mkdir a:\tex
copy tex\*.dir a:\tex
copy tex\*.tex a:\tex
copy tex\*.sty a:\tex

mkdir a:\compiler
copy compiler\*.dir a:\compiler
copy compiler\*.cpp a:\compiler
copy compiler\*.h   a:\compiler

mkdir a:\html
copy html\*.* a:\html

