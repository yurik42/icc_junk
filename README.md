# Miscellaneous c++ code samples

## Setup environment

	$ . ~/intel/sw_dev_tools/bin/compilervars.sh intel64
	$ mkdir bin-intel
	$ cd bin-intel
	$ cmake source-directory -DCMAKE_CXX_COMPILER=icpc
	$ qsub matr_mult_proj

## Login remotely
	$ ssh colfax

## Submit jobs to Xeon CPU
	$ man qsub
	$ realpath ./hello | qsub
   
## Setup environment at Windows

Start Developer command prompt for VS2017
	$ "c:\Program Files\CMake\bin\cmake.exe" .. -G "Visual Studio 15 2017" -A x64 -T "Intel C++ Compiler 19.1"

### Updated on 6/20/2022
Intel(R) oneAPI DPC++/C++ Compiler for applications running on Intel(R) 64, Version 2022.1.0 Build 20220316

	$ "c:\Program Files\CMake\bin\cmake.exe" .. -G "Visual Studio 16 2019" -A x64 -T "Intel C++ Compiler 2022" -DCMAKE_CXX_COMPILER="icx"
	
### Updated on 5/19/2023
Intel(R) oneAPI DPC++/C++ Compiler 2023.1.0 (2023.1.0.20230320)
Target: x86_64-pc-windows-msvc
Thread model: posix
	
	$ "c:\Program Files\CMake\bin\cmake.exe" .. -G "Visual Studio 17 2022" -A x64 -T "Intel(R) oneAPI DPC++ Compiler 2023"
	$ "c:\Program Files\CMake\bin\cmake.exe" --build . --config Release

### Updated on 7/6/2023
VisualStudio clang compiler
	$ "c:\Program Files\CMake\bin\cmake.exe" .. -G "Visual Studio 17 2022" -T "ClangCL"
