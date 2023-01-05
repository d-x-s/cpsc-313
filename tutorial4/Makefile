
PROGRAMS = struct
INCLUDES = -I.

CFLAGS = -Wall $(INCLUDES)
LDFLAGS = -lpthread

all: $(PROGRAMS)


%.s:%.c
	$(CC) -S $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROGRAMS) *.o core 
