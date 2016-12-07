
g++ src/main_gerador.cpp -o gerador.exe -std=c++11
g++ src/main_cpu.cpp -o cpu.exe -std=c++11
g++ src/main_omp.cpp -fopenmp -o omp.exe -std=c++11