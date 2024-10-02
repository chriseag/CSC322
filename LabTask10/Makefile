#	Makefile for the NameAge program

CC	= gcc
LD	= $(CC)
DEPEND	= mkdep

CFLAGS = -O6 -Wall

CFILES	=\
	NameAge.c\
	Person.c\
	mystrings.c

HFILES	=\
	Person.h\
	mystrings.h\
	boolean.h

OFILES	= $(CFILES:%.c=%.o)

NameAge:	$(OFILES)
	$(LD) -o $@ $(OFILES)

mystrings.o: mystrings.c mystrings.h boolean.h

Person.o: Person.c Person.h mystrings.h boolean.h

NameAge.o: NameAge.c Person.h mystrings.h boolean.h

depend:
	$(DEPEND) $(CFLAGS) $(CFILES)

clean:
	rm -f *.o *.bak
