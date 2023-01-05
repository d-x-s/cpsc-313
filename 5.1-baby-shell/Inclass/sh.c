/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
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
 * sh - shell
 *
 * Usage:
 *     sh
 *     sh -c command
 *
 * This is a stripped down version of the OS/161 shell.  The goal of today's 
 * exercise is to provide practice using the key system calls used to
 * manipulating processes.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <err.h>

/*
 * We are going to limit the number of arguments to a shell command. On
 * most UNIX systems, there is no NARG_MAX. The structure below including
 * a #define brackeded by #ifndef and #endif is how we define things that
 * are not already defined in the system include files.
 */
#ifndef NARG_MAX
#define NARG_MAX 1024
#endif

/* We'll also limit the total size allocated for arguments. */
#ifndef ARG_MAX
#define CMDLINE_MAX 4096
#elif ARG_MAX > 4096
#define CMDLINE_MAX 4096
#else
#define CMDLINE_MAX ARG_MAX
#endif

/*
 * dowait -- this is a routine you need to write so that a parent can
 * wait for its child to complete. The pid parameter is the pid of the
 * child for whom this process wishes to wait.
 */
static int
dowait(pid_t pid)
{
	/*
	 * TODO -- eventually (that is, if you don't have time to
	 * do this during class, that's fine; it will be instructive
	 * for you to see if you can implement this after watching
	 * the preclass video on the use of wait/waitpid).
	 *
	 * Make a process wait on a particular pid, and give proper
	 * error messages and/or warnings on failure. Return exit
	 * status.
	 */
	return (0);
}

/*
 * chdir
 * This is just an interface to the chdir system call.  This shell has
 * no notion of current working directory (you'll get to implement this
 * for assignment 3), so you need full pathnames here.
 */
static int
cmd_chdir(int argc, char *argv[])
{
	if (argc == 2) {
		if (chdir(argv[1]) != 0) {
			warn("chdir");
			return (1);
		}
		return (0);
	}
	printf("Usage: chdir dir\n");
	return (1);
}

static int
cmd_exit(int argc, char *argv[])
{
	int stat;

	stat = 0;
	if (argc == 2) {
		stat = atoi(argv[1]);
	} else if (argc > 1) {
		printf("Usage: exit [status]\n");
		return (1);
	} 
	exit(stat);

	return (0);
}

/*
 * This is a command dispatch table for a few of the builtin functions. Each
 * of them takes an argc and argv.
 *
 * Feel free to add some builtins here if you want.
 */
static struct {
	const char *name;
	int (*func)(int, char **);
} builtins[] = {
	{ "cd",    cmd_chdir },
	{ "chdir", cmd_chdir },
	{ "exit", cmd_exit },
	{ NULL, NULL }
};

/*
 * docommand --
 * Tokenizes the command line using strtok.  If there aren't any commands,
 * simply returns.  Checks to see if the command is a builtin, and runs it
 * if it is, otherwise, it's a standard command and we need to launch it.
 */
void docommand(char *buf)
{
	char *args[NARG_MAX + 1];
	int nargs, i;
	char *s;
	nargs = 0;

	for (s = strtok(buf, " \t\r\n"); s; s = strtok(NULL, " \t\r\n")) {
		if (nargs >= NARG_MAX) {
			fprintf(stderr, "%s: Too many arguments "
			  "(exceeds system limit)\n", args[0]);
			return;
		}
		args[nargs++] = s;
	}
	args[nargs] = NULL;

	/* Check for empty line. */
	if (nargs == 0)
		return;

	/* Check for builtin command. */
	for (i = 0; builtins[i].name; i++) {
		if (strcmp(builtins[i].name, args[0]) == 0) {
			builtins[i].func(nargs, args);
			return;
		}
	}

	/* Not a builtin; run it */

	/*
	 * TODO
	 * If you get here, then you are dealing with a command that
	 * will be implemented by executing a program. You will need 
	 * to do a fork here. Then the parent should wait for its child
	 * while the child should call execvp (using args).
	 */

	 // This function doesn't do anything right now.
	 dowait(0);
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
		if (ch == EOF)
			exit(0);
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
 * Runs the interactive shell.  This is your basic infinite loop that
 * grabs commands and executes them (printing the exit status if it's not
 * success.)
 */
static void
interactive(void)
{
	char buf[CMDLINE_MAX];

	while (1) {
		printf("BabySh: ");
		getcmd(buf, sizeof(buf));
		/*
         	 * We don't do anything with the error status
		 * in interactive mode.
		 */
		docommand(buf);
	}
}


/*
 * main --
 * If there are no arguments, run interactively, otherwise, run a program
 * from within the shell, but immediately exit.
 */
int
main(int argc, char *argv[])
{
	if (argc == 0 || argc == 1) {
		interactive();
	} else {
		errx(1, "Usage: sh [-c command]");
	}

	return (0);
}
