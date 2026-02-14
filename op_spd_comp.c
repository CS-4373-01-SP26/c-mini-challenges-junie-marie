#include <stdio.h>
#include <time.h>
#include <math.h>

/*
TASK - Compare the speed of *,/,sqrt, sin operations/functions.
*/

int main() {
    double a = 1.2345573, b = 2.5363479, c;
    int N = 100000000;
    double runtimes[4];
    const char *ops[4] = {"Multiplication", "Division", 
                          "Square Root Function", "Sine Function"};

    clock_t start, end;
    double runtime_mult, runtime_div, runtime_sqrt, runtime_sin;

    // Multiplication
    start = clock();
    for(int i=0;i<N;i++) c = a*b;
    end = clock();
    runtime_mult = ((double)(end - start)) / CLOCKS_PER_SEC;
    runtimes[0] = runtime_mult;
    printf("Multiplication: %f seconds\n", runtime_mult);

    // Division
    start = clock();
    for(int i=0;i<N;i++) c = a/b;
    end = clock();
    runtime_div = ((double)(end - start)) / CLOCKS_PER_SEC;
    runtimes[1] = runtime_div;
    printf("Division: %f seconds\n", runtime_div);

    // Square Root
    start = clock();
    for(int i=0;i<N;i++) c = sqrt(a);
    end = clock();
    runtime_sqrt = ((double)(end - start)) / CLOCKS_PER_SEC;
    runtimes[2] = runtime_sqrt;
    printf("Square Root: %f seconds\n", runtime_sqrt);

    // Sine
    start = clock();
    for(int i=0;i<N;i++) c = sin(b);
    end = clock();
    runtime_sin = ((double)(end - start)) / CLOCKS_PER_SEC;
    runtimes[3] = runtime_sin;
    printf("Sine Function: %f seconds\n", runtime_sin);

    int min_idx = 0, max_idx = 0;
    for(int i=1;i<4;i++){
        if(runtimes[i] < runtimes[min_idx]) min_idx = i;
        if(runtimes[i] > runtimes[max_idx]) max_idx = i;
    }

    printf("Fastest operation: %s (%f seconds)\n", ops[min_idx], runtimes[min_idx]);
    printf("Slowest operation: %s (%f seconds)\n", ops[max_idx], runtimes[max_idx]);

    return 0;
}