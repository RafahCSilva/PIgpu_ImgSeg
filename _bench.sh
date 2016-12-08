#!/bin/bash

g++ src/main_gerador.cpp -o gerador.out -std=c++11
g++ src/main_cpu.cpp -o cpu.out -std=c++11
g++ src/main_omp.cpp -fopenmp -o omp.out -std=c++11
nvcc src/main_cuda.cu -o cuda.out -std=c++11


./gerador.out 2 imgs/moedas_2.pbm
./gerador.out 3 imgs/moedas_3.pbm
./gerador.out 4 imgs/moedas_4.pbm
./gerador.out 5 imgs/moedas_5.pbm
./gerador.out 6 imgs/moedas_6.pbm
./gerador.out 7 imgs/moedas_7.pbm
./gerador.out 8 imgs/moedas_8.pbm
./gerador.out 9 imgs/moedas_9.pbm
./gerador.out 10 imgs/moedas_10.pbm
./gerador.out 11 imgs/moedas_11.pbm
./gerador.out 12 imgs/moedas_12.pbm
./gerador.out 13 imgs/moedas_13.pbm
./gerador.out 14 imgs/moedas_14.pbm
./gerador.out 15 imgs/moedas_15.pbm
./gerador.out 16 imgs/moedas_16.pbm
./gerador.out 17 imgs/moedas_17.pbm
./gerador.out 18 imgs/moedas_18.pbm
./gerador.out 19 imgs/moedas_19.pbm
./gerador.out 20 imgs/moedas_20.pbm


echo CPU
./cpu.out.out imgs/moedas_2.pbm imgs/moedas_2_saida_cpu.pbm -bench
./cpu.out imgs/moedas_3.pbm imgs/moedas_3_saida_cpu.pbm -bench
./cpu.out imgs/moedas_4.pbm imgs/moedas_4_saida_cpu.pbm -bench
./cpu.out imgs/moedas_5.pbm imgs/moedas_5_saida_cpu.pbm -bench
./cpu.out imgs/moedas_6.pbm imgs/moedas_6_saida_cpu.pbm -bench
./cpu.out imgs/moedas_7.pbm imgs/moedas_7_saida_cpu.pbm -bench
./cpu.out imgs/moedas_8.pbm imgs/moedas_8_saida_cpu.pbm -bench
./cpu.out imgs/moedas_9.pbm imgs/moedas_9_saida_cpu.pbm -bench
./cpu.out imgs/moedas_10.pbm imgs/moedas_10_saida_cpu.pbm -bench
./cpu.out imgs/moedas_11.pbm imgs/moedas_11_saida_cpu.pbm -bench
./cpu.out imgs/moedas_12.pbm imgs/moedas_12_saida_cpu.pbm -bench
./cpu.out imgs/moedas_13.pbm imgs/moedas_13_saida_cpu.pbm -bench
./cpu.out imgs/moedas_14.pbm imgs/moedas_14_saida_cpu.pbm -bench
./cpu.out imgs/moedas_15.pbm imgs/moedas_15_saida_cpu.pbm -bench
./cpu.out imgs/moedas_16.pbm imgs/moedas_16_saida_cpu.pbm -bench
./cpu.out imgs/moedas_17.pbm imgs/moedas_17_saida_cpu.pbm -bench
./cpu.out imgs/moedas_18.pbm imgs/moedas_18_saida_cpu.pbm -bench
./cpu.out imgs/moedas_19.pbm imgs/moedas_19_saida_cpu.pbm -bench
./cpu.out imgs/moedas_20.pbm imgs/moedas_20_saida_cpu.pbm -bench

echo.
echo OMP
./omp.out imgs/moedas_2.pbm imgs/moedas_2_saida_omp.pbm -bench
./omp.out imgs/moedas_3.pbm imgs/moedas_3_saida_omp.pbm -bench
./omp.out imgs/moedas_4.pbm imgs/moedas_4_saida_omp.pbm -bench
./omp.out imgs/moedas_5.pbm imgs/moedas_5_saida_omp.pbm -bench
./omp.out imgs/moedas_6.pbm imgs/moedas_6_saida_omp.pbm -bench
./omp.out imgs/moedas_7.pbm imgs/moedas_7_saida_omp.pbm -bench
./omp.out imgs/moedas_8.pbm imgs/moedas_8_saida_omp.pbm -bench
./omp.out imgs/moedas_9.pbm imgs/moedas_9_saida_omp.pbm -bench
./omp.out imgs/moedas_10.pbm imgs/moedas_10_saida_omp.pbm -bench
./omp.out imgs/moedas_11.pbm imgs/moedas_11_saida_omp.pbm -bench
./omp.out imgs/moedas_12.pbm imgs/moedas_12_saida_omp.pbm -bench
./omp.out imgs/moedas_13.pbm imgs/moedas_13_saida_omp.pbm -bench
./omp.out imgs/moedas_14.pbm imgs/moedas_14_saida_omp.pbm -bench
./omp.out imgs/moedas_15.pbm imgs/moedas_15_saida_omp.pbm -bench
./omp.out imgs/moedas_16.pbm imgs/moedas_16_saida_omp.pbm -bench
./omp.out imgs/moedas_17.pbm imgs/moedas_17_saida_omp.pbm -bench
./omp.out imgs/moedas_18.pbm imgs/moedas_18_saida_omp.pbm -bench
./omp.out imgs/moedas_19.pbm imgs/moedas_19_saida_omp.pbm -bench
./omp.out imgs/moedas_20.pbm imgs/moedas_20_saida_omp.pbm -bench

echo.
echo CUDA
./cuda.out imgs/moedas_2.pbm imgs/moedas_2_saida_cuda.pbm -bench
./cuda.out imgs/moedas_3.pbm imgs/moedas_3_saida_cuda.pbm -bench
./cuda.out imgs/moedas_4.pbm imgs/moedas_4_saida_cuda.pbm -bench
./cuda.out imgs/moedas_5.pbm imgs/moedas_5_saida_cuda.pbm -bench
./cuda.out imgs/moedas_6.pbm imgs/moedas_6_saida_cuda.pbm -bench
./cuda.out imgs/moedas_7.pbm imgs/moedas_7_saida_cuda.pbm -bench
./cuda.out imgs/moedas_8.pbm imgs/moedas_8_saida_cuda.pbm -bench
./cuda.out imgs/moedas_9.pbm imgs/moedas_9_saida_cuda.pbm -bench
./cuda.out imgs/moedas_10.pbm imgs/moedas_10_saida_cuda.pbm -bench
./cuda.out imgs/moedas_11.pbm imgs/moedas_11_saida_cuda.pbm -bench
./cuda.out imgs/moedas_12.pbm imgs/moedas_12_saida_cuda.pbm -bench
./cuda.out imgs/moedas_13.pbm imgs/moedas_13_saida_cuda.pbm -bench
./cuda.out imgs/moedas_14.pbm imgs/moedas_14_saida_cuda.pbm -bench
./cuda.out imgs/moedas_15.pbm imgs/moedas_15_saida_cuda.pbm -bench
./cuda.out imgs/moedas_16.pbm imgs/moedas_16_saida_cuda.pbm -bench
./cuda.out imgs/moedas_17.pbm imgs/moedas_17_saida_cuda.pbm -bench
./cuda.out imgs/moedas_18.pbm imgs/moedas_18_saida_cuda.pbm -bench
./cuda.out imgs/moedas_19.pbm imgs/moedas_19_saida_cuda.pbm -bench
./cuda.out imgs/moedas_20.pbm imgs/moedas_20_saida_cuda.pbm -bench
