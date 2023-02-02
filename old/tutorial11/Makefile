PROGRAMS = proc
INCLUDES = -I.

CFLAGS = -g -O0 -Wall $(INCLUDES)

all: $(PROGRAMS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

proc: proc.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGRAMS) *.o core a.out
