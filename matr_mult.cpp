//
//
//

#include "cstdio"

using namespace std;

typedef float T;
//template <class T>
static void matr_mult(T const *A, T const *B, T *C, size_t N, size_t K, size_t M)
{
#if _ICC
#    pragma ivdep
#    pragma omp simd
#endif
    for(size_t i = 0 ; i != N ; ++i) {
        for (size_t j = 0 ; j != M ; ++j) {
            T s = 0;
            for(size_t k = 0 ; k != K ; ++k) {
                // A[i,k] * B[k,j]
                s += A[i * K + k] * B[k * M + j];
            }
            // C[i,j] = ...
            C[i*K + j] = s;
        }
    }
}

//
// A * transpose(B)
//

//template <class T>
typedef float T;
static void matr_mult_transposed(T const *A, T const *B, T *C, size_t N, size_t K, size_t M)
{
    for(size_t i = 0 ; i != N ; ++i) {
        for (size_t j = 0 ; j != M ; ++j) {
            T s = 0;
            //#pragma simd
            for(size_t k = 0 ; k != K ; ++k) {
                // A[i,k] * B[j, k]
                s += A[i * K + k] * B[j * K + k];
            }
            // C[i,j] = ...
            C[i*M + j] = s;
        }
    }
}

//template<class T>
static void print_as_matr(T const *M, size_t rows, size_t colls, char const *title)
{
    if(title)
        printf("%s\n", title);
    if(rows * colls > 100) {
        printf("... too big\n");
        return;
    }
        
    for(size_t i = 0 ; i != rows ; ++i) {
        for(size_t j = 0 ; j != colls ; ++j) {
            printf("%g ", (double)M[i * colls + j]);
        }
        printf("\n");
    }
}

static 
T *one(size_t n)
{
    T *data = new T[n];
    data += n;
    while(n--)
        *--data = (T)1;
    return data;
}

#include "timer.h"
#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#if _WIN32
extern int getopt(int argc, char** argv, const char* opt);
int getopt(int argc, char **argv, const char *opt)
{
    (void)argc;
    (void)argv;
    (void)opt;
    return -1;
}

extern char* optarg;
char *optarg = NULL;

#else
#   include <getopt.h>
#endif

static bool verbose = false;
static int n_try = 5;

int main(int argc, char **argv)
{
    int opt = 0;
    while ((opt = getopt(argc, argv, "n:v")) != -1) {
        switch (opt) {
        case 'v':
            verbose = true;
            break;
        case 'n':
            n_try = atoi(optarg);
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-n n_try] [-v]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    {
        const size_t N = 3, K = 3, M =3;
        
        float A[] = {1, 0, 0, 0, 2, 0, 0, 0, 3};
        if(verbose)
            print_as_matr(A, N, K, "A:");
        float B[] =  {1, 0, 0, 0, 1, 0, 0, 0, 1};
        if(verbose)
            print_as_matr(B, K, M, "B:");
        
        float C[N*M];

        Timer t;
        t.start();
        matr_mult_transposed(A, B, C, N, K, M);
        t.stop();
        if(verbose)
            print_as_matr(C, N, M, "C:");
        printf("Elapsed: %g sec.\n", t.elapsed());
    }
    {
        size_t N = 5, K = 2, M = 5;
        
        float *A = one(N*K);
        if(verbose)
            print_as_matr(A, N, K, "A:");
        float *B = one(K*M);
        if(verbose)
            print_as_matr(B, M, K, "B:");
        
        float *C = new float[N*M];

        Timer t;
        t.start();
        matr_mult_transposed(A, B, C, N, K, M);
        t.stop();
        if(verbose)
            print_as_matr(C, N, M, "C:");
        printf("Elapsed: %g sec.\n", t.elapsed());

    }
    {
        size_t N = 2, K = 5, M = 3;
        
        float *A = one(N*K);
        if(verbose)
            print_as_matr(A, N, K, "A:");
        float *B = one(K*M);
        if(verbose)
            print_as_matr(B, M, K, "B:");
        
        float *C = new float[N*M];

        Timer t;
        t.start();
        matr_mult_transposed(A, B, C, N, K, M);
        t.stop();
        if(verbose)
            print_as_matr(C, N, M, "C:");
        printf("Elapsed: %g sec.\n", t.elapsed());

    }

#if 1
    {
        size_t N = 1000, K = 2000, M =2000;
        
        

        float *A = one(N*K);
        if(verbose)
            print_as_matr(A, N, K, "A:");
        float *B = one(K*M);
        if(verbose)
            print_as_matr(B, K, M, "B:");
        
        float *C = new float[N*M];

        double *results = new double[(size_t)n_try];
        for(int i = 0 ; i < n_try ; ++i) {

            Timer t;
            t.start();
            matr_mult_transposed(A, B, C, N, K, M);
            t.stop();
            if(verbose)
                print_as_matr(C, N, M, "C:");
            results[i] = t.elapsed();
        }
        for(int i = 0 ; i < n_try ; ++i)
            printf("Elapsed: (%llu,%llu,%llu) %g sec.\n", N, K, M, results[i]);

    }
#endif
}

// Local Variables:
// mode: c++
// c-basic-offset: 4
// tab-width: 4
// indent-tabs-mode: nil
// End:
