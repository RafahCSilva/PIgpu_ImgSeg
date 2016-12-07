#!/bin/bash

g++ src/main_gerador.cpp -o gerador.out -std=c++11
g++ src/main_cpu.cpp -o cpu.out -std=c++11
g++ src/main_omp.cpp -fopenmp -o omp.out -std=c++11
nvcc main_cuda.cu -o cuda.out -std=c++11
