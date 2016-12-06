#!/bin/bash

g++ src/main_cpu.cpp -o cpu
g++ src/main_omp.cpp -fopenmp -o omp