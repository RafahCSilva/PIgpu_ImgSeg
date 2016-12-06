/*
  Processamento de Imagens na GPU
    Rafael Cardoso da Silva    21048012
      Segmentacao de Imagem com o Algoritmo de Watershed
      Versao em CPU com OpenMP
 */
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <ctime>
#include <omp.h>
#include "PBM.cpp"
#include "PIOMP.cpp"
#include "TEMPO.cpp"

int main(int argc, char const *argv[]) {

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <SOURCE> <DESTINATION> [-v, -vv]" << std::endl;
    return 1;
  }

  const char * entrada = argv[1];
  const char * saida = argv[2];

  bool verbose1 = false;
  bool verbose2 = false;

  if (argc == 4) {
    if( string(argv[3]) == "-v") {
      verbose1 = true;
      verbose2 = false;
    } else if( string(argv[3]) == "-vv") {
      verbose1 = true;
      verbose2 = true;
    } else {
      cerr << "Terceito paramentro invalido!" << std::endl;
      std::cerr << "Usage: " << argv[0] << " <SOURCE> <DESTINATION> [-v, -vv]" << std::endl;
      exit(1);
    }
  }

  if(verbose1){
    cout << "Processamento de Imagens na GPU" << endl;
    cout << "  Rafael Cardoso da Silva    21048012" << endl;
    cout << "    Segmentacao de Imagem com o Algoritmo de Watershed" << endl;
    cout << "    Versao em CPU com OpenMP" << endl;
  }

  if(verbose1)    cout << "\nCarregando Imagem de Entrada... ";
  PBM* img1 = new PBM();
  img1->loadAsP1(entrada);
  if(verbose1)    cout << "OK\n";
  if(verbose2)    img1->print();

  if(verbose1)    cout << "\nTD\n";
  if(verbose1)    TEMPO_tic();
  PBM* img2 = PIOMP::TD2D(img1);
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img2->print();

  if(verbose1)    cout << "\nCORTE ( abaixo de ";
  int corte = ceil( img2->MAX() * 0.6 );
  if(verbose1)    cout << corte << " )\n";
  if(verbose1)    TEMPO_tic();
  PBM* img3 = PIOMP::CORTE(img2, corte);
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img3->print();

  if(verbose1)    cout << "\nBINARIO\n";
  if(verbose1)    TEMPO_tic();
  PBM* img4 = PIOMP::BINARIO(img3);
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img4->print();

  if(verbose1)    cout << "\nLABEL\n";
  if(verbose1)    TEMPO_tic();
  PBM* img5 = PIOMP::LABEL(img4);
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img5->print();

  if(verbose1)    cout << "\nWATERSHED\n";
  if(verbose1)    TEMPO_tic();
  PBM* img6 = PIOMP::WATERSHED(img5, img1);
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img6->print();

  if(verbose1)    cout << "\nDESTACANDO BORDA\n";
  if(verbose1)    TEMPO_tic();
  PBM* img7 = PIOMP::GETBORDA(img6);
  if(verbose1)    TEMPO_toc();
  if(verbose2)    img7->print();

  if(verbose1)    cout << "\nSalvando Imagem de Saida... ";
  img7->saveAsP1(saida);
  if(verbose1)    cout << "OK\n";

  delete img1;
  delete img2;
  delete img3;
  delete img4;
  delete img5;
  delete img6;
  delete img7;

  return 0;
}
