#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
TASK - Use the attached code snippets as a basis 
for comparing the performance of row-major vs. column major computations. 
One snippet uses a static allocation for the array, the other allocates the array dynamically. 
Do a little experimentation with each approach. 
Vary the size of the square array from 128 X 128 on up, doubling it in size each time. 
Chart your results. Is there a difference in performance or behavior between static and dynamic? 
Between row-major and column-major?
*/

#define N 16384
// ===== Static Array =====
double arr_static[N][N];

int main(int argc, char **argv) {
  int sizes[] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384};
  int num_sizes = sizeof(sizes)/sizeof(sizes[0]);

  // Open CSV file
  FILE *fp = fopen("outputs/benchmark.csv", "w");
  if (!fp) {
      printf("Error opening file!\n");
      return 1;
  }

  // Write header
  fprintf(fp, "Size,Row_Static,Col_Static,Row_Dynamic,Col_Dynamic\n");

  for (int idx = 0; idx < num_sizes; idx++) {
    int n = sizes[idx];
    clock_t start, end;
    double sum, row_time_static, col_time_static, row_time_dyn, col_time_dyn;
    
    // Fill static array
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        arr_static[i][j] = (double)rand() / RAND_MAX;
      }
    }

    // Row-major static
    start = clock();
    sum = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        sum += arr_static[i][j];
      }
    }
    end = clock();
    row_time_static = (double)(end - start)/CLOCKS_PER_SEC;

    // Column-major static
    start = clock();
    sum = 0;
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < n; i++) {
        sum += arr_static[i][j];
      }
    }
    end = clock();
    col_time_static = (double)(end - start)/CLOCKS_PER_SEC;

    // ===== Dynamic Array =====
    double *arr_dyn = malloc(n * n * sizeof(double));
    if (!arr_dyn) {
        printf("Malloc failed for size %d\n", n);
        fclose(fp);
        return 1;
    }

    // Fill dynamic array
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        arr_dyn[i*n + j] = (double)rand() / RAND_MAX;
      }
    }
    // Row-major dynamic
    start = clock();
    sum = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        sum += arr_dyn[i*n + j];
      }
    }
    end = clock();
    row_time_dyn = (double)(end - start)/CLOCKS_PER_SEC;

    // Column-major dynamic
    start = clock();
    sum = 0;
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < n; i++) {
        sum += arr_dyn[i*n + j];
      }
    }
    end = clock();
    col_time_dyn = (double)(end - start)/CLOCKS_PER_SEC;

    free(arr_dyn);

    // Write a CSV line
    fprintf(fp, "%d,%.6lf,%.6lf,%.6lf,%.6lf\n", n,
            row_time_static, col_time_static,
            row_time_dyn, col_time_dyn);
  }

  fclose(fp); // close the file
  printf("CSV written to benchmark.csv\n");
  return 0;
}
