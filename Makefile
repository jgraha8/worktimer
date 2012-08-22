CC=gcc
CFLAGS=-O2 -Wall
LDFLAGS=

all : work

install : work
	cp -v work $(INSTDIR)

uninstall : 
	rm -f $(INSTDIR)/work

work : work.o
	$(CC) -o work work.o $(LDFLAGS)

work.o : work.c
	$(CC) $(CFLAGS) -c -o work.o work.c

clean :
	rm -f work *.o