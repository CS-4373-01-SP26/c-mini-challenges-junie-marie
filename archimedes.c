#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <time.h>

/*
TASK:
    Estimate pi for inscribed/circumscribed polygons with n sides, 
    up to 100, doubling n at each step, and time it.

Steps:
    1. Start with n=6 (this gives iterations with n=6, 12, 24, 48, and 96),
    2. Compute side length of the circumscribed and inscribed n-gons (s_in = 2*sin(pi/n), s_out =2*tan(pi/n))
    3. while (n < 100):
    4. Compute the perimeters (P_in, P_out = n*s_in, n*s_out)
    5. Compute lower and upper bounds for pi approximation (P_in/2, P_out/2)
    6. Approximate pi (low+high/2)
    7. if (2n < 100): 
        Update params: 
            - s_in = sqrt(2-sqrt(4 - s_in^2))
            - s_out = (2 * s_out) / sqrt(4 + s_in^2)
            - n = 2 * n
        Repeat steps 4-7

        else: 
            return
*/

struct Side_Lengths {
    double s_in;
    double s_out;
};

struct Perimeters {
    double P_in;
    double P_out;
};

struct Bounds {
    double lower;
    double upper;
};


struct Side_Lengths side_lengths(int n) {
    struct Side_Lengths s;
    s.s_in = 2 * sin(M_PI / n);
    s.s_out = 2 * tan(M_PI / n);

    return s;
}

struct Perimeters perims(int n, struct Side_Lengths *s) {
    struct Perimeters p;
    p.P_in = n * s->s_in;
    p.P_out = n * s->s_out;

    return p;
}

struct Bounds bounds(struct Perimeters *p) {
    struct Bounds b;
    b.lower = p->P_in / 2;
    b.upper = p->P_out / 2;

    return b;
}

double approximate_pi(struct Bounds *b) {
    double pi_approx = (b->lower + b->upper) / 2;

    return pi_approx;
}

void update_params(struct Side_Lengths *s) {
    s->s_in = sqrt(2 - sqrt(4 - s->s_in * s->s_in));
    s->s_out = (2 * s->s_out) / sqrt(s->s_out * s->s_out + 4);
}

int main() {
    clock_t start, end;
    double runtime;
    start = clock();

    int n = 6;
    while (n < 100) {
        struct Side_Lengths s = side_lengths(n);
        struct Perimeters p = perims(n, &s);
        struct Bounds b = bounds(&p);
        double approx = approximate_pi(&b);
        
        printf("Number of sides: %d\n", n);
        printf("Lower Bound for Pi: %f\n", b.lower);
        printf("Upper Bound for Pi: %f\n", b.upper);
        printf("Midpoint Approximation of Pi: %f\n", approx);
        printf("\n");
        if (n * 2 < 100) {
            printf("Updating Parameters...\n");
        }
        update_params(&s);
        n = n * 2;
    }
    end = clock();
    runtime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time Elapsed: %f seconds\n", runtime);
    return 0;
}