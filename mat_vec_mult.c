#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
TASK - Implement matrix – vector multiplication.

Read in the following text file (mv.txt) which contains the matrix and vector to be multiplied. 
Print your answer to the screen and time the computation. 
The format of mv.txt is: line 1 contains numrows, numcols. 
The next numrows contains the rows of the matrix, each with numcols integer values. 
The next line contains the length of the vector. The next line contains the vector of that length.
*/

typedef struct {
    int rows;
    int cols;
    int *data;
} Matrix;

typedef struct {
    int len;
    int *data;
} Vector;

Matrix create_matrix(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = malloc(rows * cols * sizeof(int));
    if (!m.data) {
        m.rows = m.cols = 0;
    }
    return m;
}

void free_matrix(Matrix *m) {
    free(m->data);
    m->data = NULL;
    m->rows = m->cols = 0;
}

Vector create_vector(int len) {
    Vector v;
    v.len = len;
    v.data = malloc(len * sizeof(int));
    if (!v.data) {
        v.len = 0; // invalid
    }
    return v;
}

void free_vector(Vector *v) {
    free(v->data);
    v->data = NULL;
    v->len = 0;
}

Vector matvec_mul(Matrix *mat, Vector vec) {
    Vector result = create_vector(mat->rows);
    if (!result.data || mat->cols != vec.len) {
        printf("Error: dimension mismatch or allocation failed\n");
        return result;
    }

    for (int i = 0; i < mat->rows; i++) {
        result.data[i] = 0;
        for (int j = 0; j < mat->cols; j++) {
            result.data[i] += mat->data[i * mat->cols + j] * vec.data[j];
        }
    }

    return result;
}

int read_matrix_vector(const char *filename, Matrix *mat, Vector *vec) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: cannot open file %s\n", filename);
        return 0;
    }

    int numrows, numcols;
    if (fscanf(file, "%d %d", &numrows, &numcols) != 2) {
        printf("Error reading matrix dimensions\n");
        fclose(file);
        return 0;
    }

    *mat = create_matrix(numrows, numcols);
    if (!mat->data) {
        fclose(file);
        return 0;
    }

    // Read matrix data
    for (int i = 0; i < numrows; i++)
        for (int j = 0; j < numcols; j++)
            if (fscanf(file, "%d", &mat->data[i*numcols + j]) != 1) {
                printf("Error reading matrix element [%d][%d]\n", i, j);
                free_matrix(mat);
                fclose(file);
                return 0;
            }

    int veclen;
    if (fscanf(file, "%d", &veclen) != 1) {
        printf("Error reading vector length\n");
        free_matrix(mat);
        fclose(file);
        return 0;
    }

    *vec = create_vector(veclen);
    if (!vec->data) {
        free_matrix(mat);
        fclose(file);
        return 0;
    }

    // Read vector data
    for (int i = 0; i < veclen; i++)
        if (fscanf(file, "%d", &vec->data[i]) != 1) {
            printf("Error reading vector element [%d]\n", i);
            free_matrix(mat);
            free_vector(vec);
            fclose(file);
            return 0;
        }

    fclose(file);
    return 1;
}

int main() {
    Matrix mat;
    Vector vec;

    if (!read_matrix_vector("mv.txt", &mat, &vec)) {
        return 1; // failed to read
    }

    clock_t start, end;
    double runtime;
    start = clock();
    Vector result = matvec_mul(&mat, vec);
    end = clock();
    runtime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time Elapsed: %f seconds\n", runtime);
    printf("Result of matrix-vector multiplication:\n[");
    for (int i = 0; i < result.len-1; i++)
        printf("%d, ", result.data[i]);
    printf("%d", result.data[result.len - 1]);
    printf("]\n");

    free_matrix(&mat);
    free_vector(&vec);
    free_vector(&result);

    return 0;
}