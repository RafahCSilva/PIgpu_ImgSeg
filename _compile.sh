#!/bin/bash

g++ src/main_gerador.cpp -o gerador -std=c++11
g++ src/main_cpu.cpp -o cpu -std=c++11
g++ src/main_omp.cpp -fopenmp -o omp -std=c++11