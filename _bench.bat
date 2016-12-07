@echo off

g++ src/main_gerador.cpp -o gerador.exe -std=c++11
g++ src/main_cpu.cpp -o cpu.exe -std=c++11
g++ src/main_omp.cpp -fopenmp -o omp.exe -std=c++11


gerador.exe 2 imgs/moedas_2.pbm
gerador.exe 3 imgs/moedas_3.pbm
gerador.exe 4 imgs/moedas_4.pbm
gerador.exe 5 imgs/moedas_5.pbm
gerador.exe 6 imgs/moedas_6.pbm
gerador.exe 7 imgs/moedas_7.pbm
gerador.exe 8 imgs/moedas_8.pbm
gerador.exe 9 imgs/moedas_9.pbm
gerador.exe 10 imgs/moedas_10.pbm
gerador.exe 11 imgs/moedas_11.pbm
gerador.exe 12 imgs/moedas_12.pbm
gerador.exe 13 imgs/moedas_13.pbm
gerador.exe 14 imgs/moedas_14.pbm
gerador.exe 15 imgs/moedas_15.pbm
gerador.exe 16 imgs/moedas_16.pbm
gerador.exe 17 imgs/moedas_17.pbm
gerador.exe 18 imgs/moedas_18.pbm
gerador.exe 19 imgs/moedas_19.pbm
gerador.exe 20 imgs/moedas_20.pbm


echo CPU
cpu.exe imgs/moedas_2.pbm imgs/moedas_2_saida_cpu.pbm -bench
cpu.exe imgs/moedas_3.pbm imgs/moedas_3_saida_cpu.pbm -bench
cpu.exe imgs/moedas_4.pbm imgs/moedas_4_saida_cpu.pbm -bench
cpu.exe imgs/moedas_5.pbm imgs/moedas_5_saida_cpu.pbm -bench
cpu.exe imgs/moedas_6.pbm imgs/moedas_6_saida_cpu.pbm -bench
cpu.exe imgs/moedas_7.pbm imgs/moedas_7_saida_cpu.pbm -bench
cpu.exe imgs/moedas_8.pbm imgs/moedas_8_saida_cpu.pbm -bench
cpu.exe imgs/moedas_9.pbm imgs/moedas_9_saida_cpu.pbm -bench
cpu.exe imgs/moedas_10.pbm imgs/moedas_10_saida_cpu.pbm -bench
cpu.exe imgs/moedas_11.pbm imgs/moedas_11_saida_cpu.pbm -bench
cpu.exe imgs/moedas_12.pbm imgs/moedas_12_saida_cpu.pbm -bench
cpu.exe imgs/moedas_13.pbm imgs/moedas_13_saida_cpu.pbm -bench
cpu.exe imgs/moedas_14.pbm imgs/moedas_14_saida_cpu.pbm -bench
cpu.exe imgs/moedas_15.pbm imgs/moedas_15_saida_cpu.pbm -bench
cpu.exe imgs/moedas_16.pbm imgs/moedas_16_saida_cpu.pbm -bench
cpu.exe imgs/moedas_17.pbm imgs/moedas_17_saida_cpu.pbm -bench
cpu.exe imgs/moedas_18.pbm imgs/moedas_18_saida_cpu.pbm -bench
cpu.exe imgs/moedas_19.pbm imgs/moedas_19_saida_cpu.pbm -bench
cpu.exe imgs/moedas_20.pbm imgs/moedas_20_saida_cpu.pbm -bench

echo.
echo OMP
omp.exe imgs/moedas_2.pbm imgs/moedas_2_saida_omp.pbm -bench
omp.exe imgs/moedas_3.pbm imgs/moedas_3_saida_omp.pbm -bench
omp.exe imgs/moedas_4.pbm imgs/moedas_4_saida_omp.pbm -bench
omp.exe imgs/moedas_5.pbm imgs/moedas_5_saida_omp.pbm -bench
omp.exe imgs/moedas_6.pbm imgs/moedas_6_saida_omp.pbm -bench
omp.exe imgs/moedas_7.pbm imgs/moedas_7_saida_omp.pbm -bench
omp.exe imgs/moedas_8.pbm imgs/moedas_8_saida_omp.pbm -bench
omp.exe imgs/moedas_9.pbm imgs/moedas_9_saida_omp.pbm -bench
omp.exe imgs/moedas_10.pbm imgs/moedas_10_saida_omp.pbm -bench
omp.exe imgs/moedas_11.pbm imgs/moedas_11_saida_omp.pbm -bench
omp.exe imgs/moedas_12.pbm imgs/moedas_12_saida_omp.pbm -bench
omp.exe imgs/moedas_13.pbm imgs/moedas_13_saida_omp.pbm -bench
omp.exe imgs/moedas_14.pbm imgs/moedas_14_saida_omp.pbm -bench
omp.exe imgs/moedas_15.pbm imgs/moedas_15_saida_omp.pbm -bench
omp.exe imgs/moedas_16.pbm imgs/moedas_16_saida_omp.pbm -bench
omp.exe imgs/moedas_17.pbm imgs/moedas_17_saida_omp.pbm -bench
omp.exe imgs/moedas_18.pbm imgs/moedas_18_saida_omp.pbm -bench
omp.exe imgs/moedas_19.pbm imgs/moedas_19_saida_omp.pbm -bench
omp.exe imgs/moedas_20.pbm imgs/moedas_20_saida_omp.pbm -bench
