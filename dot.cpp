//
//
//

#include "cstdio"

using namespace std;

//template <class T>
typedef float T;
static
T dot(T const *A, T const *B, size_t N)
{
    //#pragma ivdep
    //#pragma simd
    T s = 0;
    for(size_t i = 0 ; i != N ; ++i) {
        s += A[i] * B[i];
    }

    return s;
}

// template<class T>
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
int main()
{
    {
        size_t N = 1000000;
        
        float *A = one(N);
        float *B = one(N);

        Timer t;
        t.start();
        auto r = dot(A, B, N);
        t.stop();
        printf("dot = %g\n", (double)r);
        printf("Elapsed: %g sec.\n", t.elapsed());
    }
}

// Local Variables:
// mode: c++
// c-basic-offset: 4
// tab-width: 4
// indent-tabs-mode: nil
// End:
