# ======================================================================= 
# Makefile - Makefile for compiling warp and morph. 
# Copyright (C) 1993 by George Wolberg 
# 
# Written by: George Wolberg, 1993 
# ======================================================================
# These are all the files to be compiled. 
MWARP = warp.o  meshwarp.o util.o catmullrom.o 
MORPH = morph.o meshwarp.o util.o catmullrom.o

# These are the cc flags. 
FLAGS = -c -O

warp: $(MWARP) 
	cc $(MWARP) $(LDLIBS) -o warp

morph: $(MORPH) 
	cc $(MORPH) $(LDLIBS) -o morph

.c.o: 
	cc $(FLAGS) -o $@ $< 
 
clean:
	rm -f *.o *~ warp.exe morph.exe
