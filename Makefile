CFLAGS = -W -Wall -pedantic -O3 `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`


main : clean structure.o util.o display.o
	@gcc $(CFLAGS) $(LDFLAGS) main.c structure.o util.o display.o $(LDLIBS) -o main

structure.o :
	@gcc $(CFLAGS) $(LDFLAGS) -c structure.c $(LDLIBS) -o structure.o

util.o :
	@gcc $(CFLAGS) $(LDFLAGS) -c util.c $(LDLIBS) -o util.o

display.o :
	@gcc $(CFLAGS) $(LDFLAGS) -c display.c $(LDLIBS) -o display.o

clean :
	@rm -rf *.o main
