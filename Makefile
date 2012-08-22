CC=gcc
CFLAGS=-O2 -Wall -g
LDFLAGS=
INSTDIR=/usr/local/bin
EXEC=worktimer

all : $(EXEC)

install : $(EXEC)
	cp $(EXEC) $(INSTDIR)

uninstall : 
	rm -f $(INSTDIR)/$(EXEC)

$(EXEC) : work.o
	$(CC) -o $(EXEC) work.o $(LDFLAGS)

work.o : work.c
	$(CC) $(CFLAGS) -c -o work.o work.c

clean :
	rm -f $(EXEC) *.o
