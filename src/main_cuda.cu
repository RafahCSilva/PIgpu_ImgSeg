/*
  Processamento de Imagens na GPU
    Rafael Cardoso da Silva    21048012
      Segmentacao de Imagem com o Algoritmo de Watershed
      Versao em CPU
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include "PBM1d.cpp"
#include "PICUDA.cu"
#include "TEMPO.cpp"

using namespace std;

int main(int argc, char const *argv[]) {

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <ORIGEM> <DESTINO> [-v, -vv, -bench]" << std::endl;
    return 1;
  }

  const char * entrada = argv[1];
  const char * saida = argv[2];

  bool verbose1 = false;
  bool verbose2 = false;
  bool bench = false;

  if (argc == 4) {
    if( string(argv[3]) == "-v") {
      verbose1 = true;
      verbose2 = false;
    } else if( string(argv[3]) == "-vv") {
      verbose1 = true;
      verbose2 = true;
    } else if( string(argv[3]) == "-bench") {
      verbose1 = false;
      verbose2 = false;
      bench = true;
    } else {
      cerr << "Terceito paramentro invalido!" << std::endl;
      std::cerr << "Usage: " << argv[0] << " <ORIGEM> <DESTINO> [-v, -vv, -bench]" << std::endl;
      exit(1);
    }
  }

  if(verbose1) {
    cout << "Processamento de Imagens na GPU" << endl;
    cout << "  Rafael Cardoso da Silva    21048012" << endl;
    cout << "    Segmentacao de Imagem com o Algoritmo de Watershed" << endl;
    cout << "    Versao em CPU" << endl;
  }

  double tempo = 0;

  if(verbose1)    cout << "\nCarregando Imagem de Entrada... ";
  PBM1d* img1 = new PBM1d();
  img1->loadAsP1(entrada);
  if(verbose1)    cout << "OK\n";
  if(verbose2)    img1->print();

  if(verbose1)    cout << "\nTD\n";
  if(verbose1)    TEMPO_tic();
  if(bench)       TEMPO_tic();
  PBM1d* img2 = PICUDA::TD2D(img1);
  if(bench)       tempo += TEMPO_toc_bench();
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img2->print();

  img2->saveAsP1_("TD2.pbm");

  if(verbose1)    cout << "\nCORTE ( abaixo de ";
  int corte = ceil( img2->MAX() );
  if(verbose1)    cout << corte << " )\n";
  if(verbose1)    TEMPO_tic();
  if(bench)       TEMPO_tic();
  PBM1d* img3 = PICUDA::CORTE(img2, corte);
  if(bench)       tempo += TEMPO_toc_bench();
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img3->print();

  if(verbose1)    cout << "\nBINARIO\n";
  if(verbose1)    TEMPO_tic();
  if(bench)       TEMPO_tic();
  PBM1d* img4 = PICUDA::BINARIO(img3);
  if(bench)       tempo += TEMPO_toc_bench();
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img4->print();

  if(verbose1)    cout << "\nLABEL\n";
  if(verbose1)    TEMPO_tic();
  if(bench)       TEMPO_tic();
  PBM1d* img5 = PICUDA::LABEL(img4);
  if(bench)       tempo += TEMPO_toc_bench();
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img5->print();

  if(verbose1)    cout << "\nWATERSHED\n";
  if(verbose1)    TEMPO_tic();
  if(bench)       TEMPO_tic();
  PBM1d* img6 = PICUDA::WATERSHED(img5, img1);
  if(bench)       tempo += TEMPO_toc_bench();
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img6->print();

  if(verbose1)    cout << "\nDESTACANDO BORDA\n";
  if(verbose1)    TEMPO_tic();
  if(bench)       TEMPO_tic();
  PBM1d* img7 = PICUDA::GETBORDA(img6);
  if(bench)       tempo += TEMPO_toc_bench();
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img7->print();

  if(verbose1)    cout << "\nSalvando Imagem de Saida... ";
  img7->saveAsP1(saida);
  if(verbose1)    cout << "OK\n";

  if(bench) cout << tempo << endl;

  delete img1;
  delete img2;
  delete img3;
  delete img4;
  delete img5;
  delete img6;
  delete img7;

  return 0;
}
