#include <cstdio>
#if __has_include (<unistd.h>)
#   include <unistd.h>
#else
#   include <winsock.h>
#   pragma comment(lib, "ws2_32.lib")
#endif

#include <thread>
#include <iostream>

int main()
{
#if _WIN32
    int iResult;
    WSADATA wsaData;

    // Initialize Winsock
    iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    if ( iResult != 0 ) {
        printf( "WSAStartup failed: %d\n", iResult );
        return 1;
    }
#endif

    char hostname[100];
    unsigned int ncpus;

    gethostname( hostname, sizeof( hostname ) );
    ncpus = std::thread::hardware_concurrency();

    printf( "Host %s has %d CPU(s)\n", hostname, ncpus );
#if defined(__INTEL_LLVM_COMPILER)
    std::cout << "__INTEL_COMPILER: " << __INTEL_LLVM_COMPILER << "\n";
#endif
#if defined(__VERSION)
    std::cout << "__VERSION: " << __VERSION << "\n";
#endif
    // dpcpp only
#if defined(SYCL_LANGUAGE_VERSION) && defined (__INTEL_LLVM_COMPILER)
   // code specific for DPC++ compiler below
   // ... ...

   // example only
    std::cout << "SYCL_LANGUAGE_VERSION: " << SYCL_LANGUAGE_VERSION << std::endl;
    std::cout << "__INTEL_LLVM_COMPILER: " << __INTEL_LLVM_COMPILER << std::endl;
    std::cout << "__VERSION__: " << __VERSION__ << std::endl;
#endif
}
