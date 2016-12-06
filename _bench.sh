#!/bin/bash

g++ src/main_gerador.cpp -o gerador
g++ src/main_cpu.cpp -o cpu
g++ src/main_omp.cpp -fopenmp -o omp


./gerador 2 imgs/moedas_2.pbm
./gerador 3 imgs/moedas_3.pbm
./gerador 4 imgs/moedas_4.pbm
./gerador 5 imgs/moedas_5.pbm
./gerador 6 imgs/moedas_6.pbm
./gerador 7 imgs/moedas_7.pbm
./gerador 8 imgs/moedas_8.pbm
./gerador 9 imgs/moedas_9.pbm
./gerador 10 imgs/moedas_10.pbm
./gerador 11 imgs/moedas_11.pbm
./gerador 12 imgs/moedas_12.pbm
./gerador 13 imgs/moedas_13.pbm
./gerador 14 imgs/moedas_14.pbm
./gerador 15 imgs/moedas_15.pbm
./gerador 16 imgs/moedas_16.pbm
./gerador 17 imgs/moedas_17.pbm
./gerador 18 imgs/moedas_18.pbm
./gerador 19 imgs/moedas_19.pbm
./gerador 20 imgs/moedas_20.pbm


echo CPU
./cpu imgs/moedas_2.pbm imgs/moedas_2_saida_cpu.pbm -bench
./cpu imgs/moedas_3.pbm imgs/moedas_3_saida_cpu.pbm -bench
./cpu imgs/moedas_4.pbm imgs/moedas_4_saida_cpu.pbm -bench
./cpu imgs/moedas_5.pbm imgs/moedas_5_saida_cpu.pbm -bench
./cpu imgs/moedas_6.pbm imgs/moedas_6_saida_cpu.pbm -bench
./cpu imgs/moedas_7.pbm imgs/moedas_7_saida_cpu.pbm -bench
./cpu imgs/moedas_8.pbm imgs/moedas_8_saida_cpu.pbm -bench
./cpu imgs/moedas_9.pbm imgs/moedas_9_saida_cpu.pbm -bench
./cpu imgs/moedas_10.pbm imgs/moedas_10_saida_cpu.pbm -bench
./cpu imgs/moedas_11.pbm imgs/moedas_11_saida_cpu.pbm -bench
./cpu imgs/moedas_12.pbm imgs/moedas_12_saida_cpu.pbm -bench
./cpu imgs/moedas_13.pbm imgs/moedas_13_saida_cpu.pbm -bench
./cpu imgs/moedas_14.pbm imgs/moedas_14_saida_cpu.pbm -bench
./cpu imgs/moedas_15.pbm imgs/moedas_15_saida_cpu.pbm -bench
./cpu imgs/moedas_16.pbm imgs/moedas_16_saida_cpu.pbm -bench
./cpu imgs/moedas_17.pbm imgs/moedas_17_saida_cpu.pbm -bench
./cpu imgs/moedas_18.pbm imgs/moedas_18_saida_cpu.pbm -bench
./cpu imgs/moedas_19.pbm imgs/moedas_19_saida_cpu.pbm -bench
./cpu imgs/moedas_20.pbm imgs/moedas_20_saida_cpu.pbm -bench

echo.
echo OMP
./omp imgs/moedas_2.pbm imgs/moedas_2_saida_omp.pbm -bench
./omp imgs/moedas_3.pbm imgs/moedas_3_saida_omp.pbm -bench
./omp imgs/moedas_4.pbm imgs/moedas_4_saida_omp.pbm -bench
./omp imgs/moedas_5.pbm imgs/moedas_5_saida_omp.pbm -bench
./omp imgs/moedas_6.pbm imgs/moedas_6_saida_omp.pbm -bench
./omp imgs/moedas_7.pbm imgs/moedas_7_saida_omp.pbm -bench
./omp imgs/moedas_8.pbm imgs/moedas_8_saida_omp.pbm -bench
./omp imgs/moedas_9.pbm imgs/moedas_9_saida_omp.pbm -bench
./omp imgs/moedas_10.pbm imgs/moedas_10_saida_omp.pbm -bench
./omp imgs/moedas_11.pbm imgs/moedas_11_saida_omp.pbm -bench
./omp imgs/moedas_12.pbm imgs/moedas_12_saida_omp.pbm -bench
./omp imgs/moedas_13.pbm imgs/moedas_13_saida_omp.pbm -bench
./omp imgs/moedas_14.pbm imgs/moedas_14_saida_omp.pbm -bench
./omp imgs/moedas_15.pbm imgs/moedas_15_saida_omp.pbm -bench
./omp imgs/moedas_16.pbm imgs/moedas_16_saida_omp.pbm -bench
./omp imgs/moedas_17.pbm imgs/moedas_17_saida_omp.pbm -bench
./omp imgs/moedas_18.pbm imgs/moedas_18_saida_omp.pbm -bench
./omp imgs/moedas_19.pbm imgs/moedas_19_saida_omp.pbm -bench
./omp imgs/moedas_20.pbm imgs/moedas_20_saida_omp.pbm -bench
