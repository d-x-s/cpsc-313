#include <stdio.h>

long array[] = {10, 1,  3,  5,  7, 9};

int main(int argc, char *argv[]) {

	long sum = 0;
	long *lp = array;
	long max = *lp++;

	while (sum < max) {
		sum += *lp++;
	}

	printf("%ld\n", sum);
}

C. Write the equivalent  y86 program, leaving the value of sum in %rax instead of printing it.

D. The C program has a serious flaw, what is it?
out of bounds access if max is too big, it will definitely go out of ranges
