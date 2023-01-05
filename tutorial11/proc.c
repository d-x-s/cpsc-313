/*
 * Copyright (c) 2000-2016
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * This is derived from a stripped down version of the OS/161 shell.
 * The goal of today's exercise is to develop intuition about process
 * isolation.
 */

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <err.h>

#define CMDLINE_MAX 1024


long *region = NULL;
long global  = 1;
long *gptr = &global;
long *mptr = NULL;

typedef enum {
	PT_GLOBAL,
	PT_LOCAL,
	PT_MALLOC,
	PT_SHARED,
	PT_EXIT
} ptrType_t;

struct {
	char *cmd;
	ptrType_t type;
} lookup[] = {
	{"g", PT_GLOBAL},
	{"G", PT_GLOBAL},
	{"l", PT_LOCAL},
	{"L", PT_LOCAL},
	{"m", PT_MALLOC},
	{"M", PT_MALLOC},
	{"s", PT_SHARED},
	{"S", PT_SHARED},
	{"e", PT_EXIT},
	{"x", PT_EXIT},
	{NULL, PT_EXIT}
};

/*
 * docommand --
 * Accepts first item on a line as a command and ignores everything else.
 * Based on the command, we'll either exit or change the value of one of
 * our variables and see what happens both in us (the parent) and our child.
 */
int docommand(char *buf, long *lptr)
{
	char *args[2];

	args[0] = strtok(buf, " \t\r\n");
	args[1] = NULL;

	/* Check for empty line. */
	if (args[0] == NULL)
		return(0);

	/* Check for builtin command. */
	// generate a random number
	long r = random();
	for (int i = 0; lookup[i].cmd != NULL; i++) {
		if (strcmp(lookup[i].cmd, args[0]) == 0) {
			switch (lookup[i].type) {
				case PT_GLOBAL:
					*gptr = r;
					break;
				case PT_LOCAL:
					*lptr = r;
					break;
				case PT_SHARED:
					*region = r;
					break;
				case PT_MALLOC:
					*mptr = r;
					break;
				case PT_EXIT:
					return(1);
			}
			return(0);
		}
	}
	return (0);
}

void
dump(long *lptr) {
	printf("%ld: Local: %ld\n", (long)getpid(), *lptr);
	printf("%ld: Global: %ld\n", (long)getpid(), *gptr);
	printf("%ld: Malloc: %ld\n", (long)getpid(), *mptr);
	printf("%ld: Mmap: %ld\n", (long)getpid(), *region);
}

/*
 * getcmd --
 * Reads valid characters from the console, filling the buffer.
 * Backspace deletes a character, by moving the position backwards.
 * A newline or carriage return breaks the loop, which terminates
 * the string and returns.
 *
 * If there is an invalid character or a backspace when there is nothing
 * in the buffer, outputs an alert (bell).
 */
static void
getcmd(char *buf, size_t len)
{
	size_t pos;
	int ch, done;

	pos = 0;
	done = 0;

	/*
	 * In the absence of a <ctype.h>, assume input is 7-bit ASCII.
	 */

	while (!done) {
		ch = getchar();
		if (ch == EOF) {
			buf[0] = 'x';
			buf[1] = 0;
			return;
		}
		if ((ch == '\b' || ch == 127) && pos > 0) {
			pos--;
		} else if (ch == '\r' || ch == '\n') {
			done = 1;
		} else if (ch >= 32 && ch < 127 && pos < len-1) {
			buf[pos++] = ch;
		}
	}
	buf[pos] = 0;
}

/*
 * interactive --
 * Reads stuff typed in and does something in response.
 */
static void
interactive(long *lptr)
{
	char buf[CMDLINE_MAX];

	while (1) {
		printf("Proc: ");
		getcmd(buf, sizeof(buf));
		/*
         	 * We don't do anything with the error status
		 * in interactive mode.
		 */
		if (docommand(buf, lptr))
			break;
		dump(lptr);
	}
}


/*
 * main --
 * Map a chunk of shared memory; fork a child and then use command line
 * input to change and print out various types of variables so that we
 * can see which changes in the parent affect things in the child.
 */
int
main(int argc, char *argv[])
{
	long local;
	long *lptr = &local;

	// Map a tiny region of shared memory.
	region = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if (region == NULL) {
		fprintf(stderr, "mmap failed: %s\n", strerror(errno));
		return(-1);
	}

	// Malloc some memory.
	mptr = malloc(100);
	if (mptr == NULL)
		return (-1);

	/* Create child process. */
	pid_t mypid = fork();
	int is_parent = 1;

	if (mypid == 0) {
		// I am the child
		printf("%ld\tI am the child\n", (long)getpid());
		is_parent = 0;
	} else if (mypid > 0) {
		// I am the parent
		printf("%ld\tI am the parent\n", (long)getpid());
	} else {
		// Something bad happened!
		perror("proc: ");
		return(-1);
	}

	if (is_parent) {
		// I am the parent; run interactive program
		interactive(lptr);
		kill(mypid, SIGKILL);
	} else {
		// Child: Just output data
		while (1) {
			dump(lptr);
			sleep(3);
		}
	}

	return (0);
}
