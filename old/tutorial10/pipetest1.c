#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

/*
 * The goal of this sequence of programs (pipetest1-N) is to
 * understand the need for the pipe system call and how to use
 * it.
 */

/*
 * Let's say that we want to implement child1 | child2.
 * Why can't we simply redirect output of C1 into input of C2?
 */
int
main(int argc, char *argv[]) {
	char buf[BUFSIZE];
	char *me;

	pid_t mypid;
	pid_t child1, child2;

	/* Now, fork off a child. */
	child1 = fork();

	if (child1 == 0) {
		/* I am the first child process. */
		mypid = getpid();
		me = "Child1";
		printf("I am %s and my pid is: %d\n", me, mypid);

		/*
		 * I want my stdout to connected to
		 * child 2's standard in.
		 */
	} else if (child1 < 0) {
		fprintf(stderr, "Fork failed %s\n", strerror(errno));
		exit(1);
	} else {
		/* I am the parent process. */
		mypid = getpid();
		me = "Parent";
		printf("I am %s and my pid is: %d\n", me, mypid);

		/* Fork off a second child. */
		child2 = fork();
		if (child2 == 0) {
			/* I am the second child. */
			mypid = getpid();
			me = "Child2";
			printf("I am %s and my pid is: %d\n", me, mypid);

			/* Dup stdout (which should be the same
			 * for both children) into std in
			 */
			dup2(STDOUT_FILENO, STDIN_FILENO);
		} else {
			/* Let the parent sleep for a bit. */
			sleep(1);
		}
	}

	// Now let us have every process print something.
	printf("I am pid %d and I am writing some data.\n", mypid);

	/* Now let's see what happens if I try to read. */
	while (scanf("%s", buf) != 0)
		printf("Pid %d just read: %s\n", mypid, buf);

	printf("Pid %d exiting\n", mypid);
	exit(0);
}
