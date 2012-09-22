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

$(EXEC) : worktimer.o
	$(CC) -o $(EXEC) worktimer.o $(LDFLAGS)

work.o : work.c
	$(CC) $(CFLAGS) -c -o worktimer.o worktimer.c

clean :
	rm -f $(EXEC) *.o
