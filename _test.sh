#!/bin/bash

./cpu teste/ex1.pbm teste/cpu1_saida.pbm -vv
./cpu teste/moedas_x1100.pbm teste/cpu2_saida.pbm -v

./omp teste/ex1.pbm teste/omp1_saida.pbm -vv
./omp teste/moedas_x1100.pbm teste/omp2_saida.pbm -v