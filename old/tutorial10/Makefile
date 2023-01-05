
PROGRAMS = copy pipetest1 pipetest2 pipetest3
INCLUDES = -I.

CFLAGS = -O3 -Wall $(INCLUDES)

all: $(PROGRAMS)


%.s:%.c
	$(CC) -S $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROGRAMS) *.o core connector
