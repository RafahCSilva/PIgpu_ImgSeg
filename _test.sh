#!/bin/bash

./cpu imgs/ex1.pbm imgs/saida_cpu1.pbm -vv
./cpu imgs/moedas_x1100.pbm imgs/saida_cpu2.pbm -v

./omp imgs/ex1.pbm imgs/saida_omp1.pbm -vv
./omp imgs/moedas_x1100.pbm imgs/saida_omp2.pbm -v