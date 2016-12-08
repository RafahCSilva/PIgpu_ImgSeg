/*
  Processamento de Imagens na GPU
    Rafael Cardoso da Silva    21048012
      Segmentacao de Imagem com o Algoritmo de Watershed
        Classe de funcoes para manipular imagem em CPU com OpenMP
 */
#ifndef PIOMP_H
#define PIOMP_H
#include <iostream>
#include <map>
#include <omp.h>
#include "PBM.cpp"
#include "UnionFind.cpp"

using namespace std;

class PIOMP {
public:
  PIOMP();
  virtual ~PIOMP();
  static PBM* TD2D (PBM* img);
  static PBM* CORTE (PBM* img, int corte);
  static PBM* BINARIO (PBM* img);
  static PBM* LABEL (PBM* img);
  static PBM* WATERSHED (PBM* img, PBM* original);
  static PBM* GETBORDA (PBM* img);

protected:
private:
};

PIOMP::PIOMP() {
  //ctor
}

PIOMP::~PIOMP() {
  //dtor
}


void PBM::copyOfParallel(PBM * img) {
  this->deleteIMG();

  int i, j;

  this->height = img->getHeight();
  this->width = img->getWidth();

  this->mat = new int*[this->height];
  for(i = 0; i < this->height; i++)
    this->mat[i] = new int[this->width];

  #pragma omp parallel for schedule(dynamic) private(i, j) shared(img)
  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      this->mat [i][j] = img->get(i, j);
    }
  }
}


/// TRANSFORMADA DA DISTANCIA em 2D
PBM* PIOMP::TD2D(PBM* img) {
  int i, j;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();

  PBM* in = new PBM();
  in->copyOfParallel(img);
  PBM* out = new PBM();
  out->zerado( HEIGTH, WIDTH);

  int ALTO = HEIGTH * WIDTH;
  #pragma omp parallel for schedule(dynamic) private(i, j) shared(in, HEIGTH, WIDTH)
  for(i = 0; i < HEIGTH; i++) {
    for(j = 0; j < WIDTH; j++) {
      in->set(i, j, in->get(i, j)*ALTO);
    }
  }

  while( true ) {
    // para cada pixel
    #pragma omp parallel for schedule(dynamic) private(i, j) shared(in, out, HEIGTH, WIDTH)
    for(i = 0; i < HEIGTH; i++) {
      for(j = 0; j < WIDTH; j++) {
        // se ele eh zero
        if( in->get(i, j) == 0 ) {
          out->set(i, j, 0);
        } else {
          int m = in->get(i, j);//FLT_MAX;
          // pega o menor numa mascara 3x3
          for( int k = -1; k <= 1; k++ ) {
            for( int l = -1; l <= 1; l++ ) {
              // evita a borda
              if( ( 0 <= i + k ) && ( i + k < HEIGTH ) && ( 0 <= j + l ) && ( j + l < WIDTH ) ) {
                // se eh menor, entao armazeza
                m = min( m, (int)in->get(i + k, j + l) + 1 );
              }
            }
          }
          // salva a menor distancia para aquele pixel
          out->set(i, j, m);
        }
      }
    }
    if( PBM::imgIGUAL(in, out) ) break;
    in->copyOfParallel(out);
  }
  in->deleteIMG();
  delete in;
  return out;
}

/// CORTE DA CURVA DE NIVEL
PBM* PIOMP::CORTE (PBM* img, int corte) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOfParallel(img);

  #pragma omp parallel for schedule(dynamic) private(i, j) shared(out, corte, HEIGTH, WIDTH)
  for(i = 0; i < HEIGTH; i++){
    for(j = 0; j < WIDTH; j++){
      if(out->get(i, j) < corte){
        out->set(i, j, 0);
      }
    }
  }

  return out;
}

/// QLQR ELEMENTO DIFERENTE DE 0 VIRA 1
PBM* PIOMP::BINARIO (PBM* img) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOfParallel(img);

  #pragma omp parallel for schedule(dynamic) private(i, j) shared(out, HEIGTH, WIDTH)
  for(i = 0; i < HEIGTH; i++){
    for(j = 0; j < WIDTH; j++){
      if(out->get(i, j) != 0){
        out->set(i, j, 1);
      }
    }
  }

  return out;
}

/// Verifica se eh um vizinho que posso me ligar
static bool ehVizinho(PBM* img, int x, int y, int i, int j ) {
  // o proprio elemento nao eh vizinho dele msm
  if( i == 0 && j == 0 ) return false;

  // nao olha pra fora da borda
  if( x == 0 && i < 0 ) return false;  // esq
  if( y == 0 && j < 0 ) return false;  // cima
  if( x == img->getHeight() - 1 && i > 0 ) return false;  // dir
  if( y == img->getWidth() - 1 && j > 0 ) return false;  // baixo

  // img(x,y) == 1?
  if( img->get( x, y ) == 0 ) return false;
  // meu visinho img(x+i,y+j) == 1 tbm?
  if( img->get( ( x + i ), ( y + j ) ) == 0 ) return false;
  // ainda nao processei?
  //if( labels[ a( ( x + i ), ( y + j ) ) ] == -1 ) return false;

  // eh um vizinho valido
  return true;
}

/// LABEL
PBM* PIOMP::LABEL (PBM* img) {
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOfParallel(img);

  UnionFind* labels = new UnionFind();
  labels->init(img);

  int x, y, i, j, id;

  /// Passo 1 - encontra o LABEL
  // para cada elemento da img
  #pragma omp parallel for schedule(dynamic) private(x,y,i,j) shared(img, labels, HEIGTH, WIDTH)
  for( x = 0; x < HEIGTH ; x++ ) {
    for( y = 0; y < WIDTH ; y++ ) {
      // olha para os N8 (=mascara de 3x3)
      for( i = -1; i <= 1 ; i++ ) {
        for( j = -1; j <= 1 ; j++ ) {
          // verifica se eh meu vizinho conectado
          if( ehVizinho(img,  x, y, i, j ) ){
            // uni meu vizinho ao meu conjunto
            labels->MERGE( ( ( x + i ) * HEIGTH + ( y + j ) ) , ( x * HEIGTH + y ) );
          }
        }
      }
    }
  }

  /// Passo 2 - unifica o LABEL e passa do UnionFind para a img out
  // para cada elemento da img
  labels->flat();
  std::map<int, int> contMap;
  int cont = 0;
  contMap[0] = 0;

  // nao da pra paralelizar por causa do deadlock da espera do labels e contMap
  // #pragma omp parallel for schedule(dynamic) private(i,j) shared(out, labels, contMap, cont, HEIGTH, WIDTH)
  for(i = 0; i < HEIGTH; i++){
    for(j = 0; j < WIDTH; j++) {
      id = i * HEIGTH + j;
      if(contMap.find( labels->FIND(id) ) == contMap.end()) {
        contMap[id] = ++cont;
      }
      out->set(i, j, contMap.find(labels->FIND(id))->second);
    }
  }

  return out;
}


PBM* PIOMP::WATERSHED(PBM* img, PBM* original) {
  int i, j, k, l;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();

  PBM* in = new PBM();
  in->copyOfParallel(img);
  PBM* out = new PBM();
  out->copyOfParallel(img);

  // eqto tiver ZEROs na IMG
  while( true ) {
    // para cada pixel
    #pragma omp parallel for schedule(dynamic) private(i, j, k, l) shared(in, out, HEIGTH, WIDTH)
    for( i = 0; i < HEIGTH; i++ ) {
      for( j = 0; j < WIDTH; j++ ) {
        // se IMG == 1 e IN == 0
        if( original->get(i, j) == 1 && in->get(i, j) <= 0 ) {
          int m = 0;
          bool borda = false;
          int dif = -2;
          // pega o menor numa mascara 3x3
          for( k = -1; k <= 1; k++ ) {
            for( l = -1; l <= 1; l++ ) {
              // evita a borda
              if( ( 0 <= i + k ) && ( i + k < HEIGTH ) && ( 0 <= j + l ) && ( j + l < WIDTH ) ) {
                  // se eh menor, entao armazeza
                if( m < in->get((i + k), (j + l))) {
                  m = in->get((i + k), (j + l));
                }
                  // eh borda ao ver na mask 3x3
                if(original->get((i + k), (j + l)) == 0) {
                  borda = true;
                }
                if( m > 0 ) {
                  if(dif == -2) {
                    dif = m;
                  } else if(m != dif ) {
                    borda = true;
                  }
                }
              }
            }
          }
          // se eh borda e "alagou" salva o -1, senao o maior
          out->set(i, j, (borda && m > 0 ? -1 : m));
        }
      }
    }
    if( PBM::imgIGUAL(in, out) ) break;
    // copia os valores de OUT pra IN
    in->copyOfParallel(out);
    // cout << endl; in->print();
  }

  delete in;

  return out;
}

PBM* PIOMP::GETBORDA(PBM* img) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOfParallel(img);

  #pragma omp parallel for schedule(dynamic) private(i, j) shared(out, HEIGTH, WIDTH)
  for(i = 0; i < HEIGTH; i++){
    for(j = 0; j < WIDTH; j++){
      if(out->get(i, j) == -1){
        out->set(i, j, 1);
      }else{
        out->set(i, j, 0);
      }
    }
  }
  return out;
}

#endif // PIOMP_H
