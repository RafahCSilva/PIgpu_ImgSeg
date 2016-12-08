/*
  Processamento de Imagens na GPU
    Rafael Cardoso da Silva    21048012
      Segmentacao de Imagem com o Algoritmo de Watershed
        Gerador de Imagens
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <stack>
#include <ctime>
#include "PBM.cpp"

using namespace std;

void circulo(PBM* img, int x, int y, int raio) {
  //cout << x << " " << y << " " << raio << endl;
  int raio2 = pow(raio, 2);
  for( int i = x - raio; i < x + raio; i++ )
    for( int j = y - raio; j < y + raio; j++ )
      if( (pow(i - x, 2) + pow(j - y, 2)) <= raio2 )
        img->set(i, j, 1);
}

int pos(int marg, int pto, int raio) {
  return marg + raio + (pto * raio * 2);
}

void GERADOR(int marg, int qtdd, int raio, const char * arquivo ) {
  int tam = (2 * marg) + qtdd * 2 * raio;
  int sobre = (int)raio / 10;
  PBM* img = new PBM();
  img->zerado( tam, tam );

  //cout << "gerando... \n";
  for ( int x = 0; x < qtdd; x++ )
    for ( int y = 0; y < qtdd; y++ )
      circulo(img, pos(marg, x, raio), pos(marg, y, raio), raio + sobre); // + rand() % sobre );
  //cout << "OK\n";

  //cout << "salvando... ";
  img->saveAsP1(arquivo);
  //cout << "OK\n";
}

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <NUMERO> <DESTINO>" << std::endl;
    return 1;
  }

  int num = atoi(argv[1]);
  const char * saida = argv[2];

  GERADOR(50, num, 50, saida);

  return 0;
}
