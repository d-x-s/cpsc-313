#include <stdlib.h>
#include <stdio.h>

unsigned long array[1000][1000];

int main(int argc, char **argv) {
  printf("%p\n", &array[0][0]);
}