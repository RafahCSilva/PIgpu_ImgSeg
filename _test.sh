#!/bin/bash

./cpu.out teste/ex1.pbm teste/cpu1_saida.pbm -vv
./cpu.out teste/moedas_x1100.pbm teste/cpu2_saida.pbm -v

./omp.out teste/ex1.pbm teste/omp1_saida.pbm -vv
./omp.out teste/moedas_x1100.pbm teste/omp2_saida.pbm -v

./cuda.out teste/ex1.pbm teste/omp1_saida.pbm -vv
./cuda.out teste/moedas_x1100.pbm teste/omp2_saida.pbm -v