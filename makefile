CPP=c++
CFLAGS=
LINK=c++

all: mmx mmm_cfg

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

mmx : mmmx.o mmmtext.o mmmgrep.o mmm_lnx.o mmm_unx.o
	$(LINK) -o mmx   mmmx.o mmmtext.o mmmgrep.o mmm_lnx.o mmm_unx.o

mmm_cfg : mmm_cfg.o
	$(LINK) -o mmm_cfg  mmm_cfg.o

mmmx.o  : mmmx.cpp     mmmx.h mmmconst.h mmm_comm.h mmmgrep.h mmm_lnx.h

include makedep.mif

#&>>&10 0 10 0
