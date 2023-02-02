#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct boring {
	long long unsigned var1 ;
	long long var2 ;
	long long unsigned var3 ;
	long long var4 ;
	long long var5 ;
	long long var6 ;
};

int main () {
	long long foo;

	printf( "The address of local is 0x%p\n" , &foo);
	return 0;
}
