#
# File:     %M%	SCCS: %I% - %G%
# Author:   Matt Stemen
#
# Created:  12/05/1992
# Edited:   
#
# The use, disclosure, reproduction, modification, transfer, or
# transmittal of this work for any purpose in any form or by any
# means without the written permission of United Parcel Services
# is strictly prohibited.
#
# Confidential, Unpublished Property of United Parcel Services.
# Use and Distribution Limited Solely to Authorized Personnel.
#
# Copyright (c) 1992, United Parcel Service of America, Inc.
# All Rights Reserved.
#
# Purpose:
#    Build sentry.
#
.KEEP_STATE :

.INIT :
	@echo "Copyright (c) 1992 by Roadnet Technologies, Inc."
	@echo "Copyright (c) 1992 by United Parcel Service of America."
	@echo "All rights reserved."
	@echo ""

SCCSGETFLAGS=	-s
OPENWINHOME=	/usr/openwin/

# LIBAUDIO = /usr/lib/libaudio.a
# CC=	    /home/dbi0/toolset/licensed/C/acc
# CC=	   CC 
# CFLAGS=		-I/home/mw5/openwin30/include -I/usr/demo/SOUND
# LD=		$(CC) -L$(OPENWINHOME)/lib # -L/usr/demo/SOUND
# LDLIBS=		-L. $(LIBAUDIO) -lxview -lolgx -lX11 


 CC = CC
 CFLAGS=  -I/opt/SUNWspro/SC4.0/include/CC -I. -DMAIN
 LD=     $(CC) 
 LDLIBS= -L. -L/opt/SUNWspro/SC4.0/include/lib

EXE=		matchit2

OBJECTS=	tableCell.o tableRow.o table.o mstring.o matchit2.o 

install :=	CFLAGS += -fast
install :=	LDFLAGS += -s

debug   :=	CFLAGS += -g -DDEBUG -sb
debug   :=	LDFLAGS += -g -sb

all debug install : $(EXE)

$(EXE) : $(OBJECTS)
	$(LD) $(CFLAGS) $(LDFLAGS) -o a.out $(OBJECTS)  $(LDLIBS)
	mv a.out $(EXE)

clean :
	rm -f *.o ,* core
	sccs clean

immaculate :
	rm -f *.a $(TASKEXE)
	make clean


