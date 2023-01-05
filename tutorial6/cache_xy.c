#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define X 10000
#define Y 10000

unsigned long array[X][Y];
clock_t start, end;
int temp = -9999;
double timeX = 0;
double timeY = 0;
int sumX = 0;
int sumY = 0;

void sum_x_major(int times) {
  start = clock();
  for (int t = 0; t < times; t++) {
    for (int i = 0; i < X; i++) {       // important line 1
      for (int j = 0; j < Y; j++) {     // important line 2
        sumX += array[i][j];
      }
    }
  }

  end = clock();
  timeX = (double)(end - start) / CLOCKS_PER_SEC;
  printf("X-major order took %lf\n", timeX);
  printf("to calculate the sum: %d\n", sumX);
}

void sum_y_major(int times) {
  start = clock();
  for (int t = 0; t < times; t++) {
    for (int j = 0; j < Y; j++) {       // important line 1
      for (int i = 0; i < X; i++) {     // important line 2
        sumY += array[i][j];
      }
    }
  }
  end = clock();
  timeY = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Y-major order took %lf\n", timeY);
  printf("to calculate the sum: %d\n", sumY);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: %s <iterations>\n", argv[0]);
    exit(0);
  }
  int times = atoi(argv[1]);
  for (int i = 0; i < X; i++) {
    for (int j = 0; j < Y; j++) {
      array[i][j] = i;
    }
  }
  sum_x_major(times);
  sum_y_major(times);
}
