#!/bin/bash

g++ src/main_gerador.cpp -o gerador
g++ src/main_cpu.cpp -o cpu
g++ src/main_omp.cpp -fopenmp -o omp