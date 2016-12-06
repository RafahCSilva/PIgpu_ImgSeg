#ifndef PICPU_H
#define PICPU_H
#include <iostream>
#include <map>
#include "PBM.cpp"
#include "UnionFind.cpp"

using namespace std;

class PICPU {
public:
  PICPU();
  virtual ~PICPU();
  static PBM* TD2D (PBM* img);
  static PBM* CORTE (PBM* img, int corte);
  static PBM* BINARIO (PBM* img);
  static PBM* LABEL (PBM* img);
  static PBM* WATERSHED (PBM* img, PBM* original);
  static PBM* GETBORDA (PBM* img);

protected:
private:
};

PICPU::PICPU() {
  //ctor
}

PICPU::~PICPU() {
  //dtor
}

/// TRANSFORMADA DA DISTANCIA em 2D
PBM* PICPU::TD2D(PBM* img) {
  int i, j;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();

  PBM* in = new PBM();
  in->copyOf(img);
  PBM* out = new PBM();
  out->zerado( HEIGTH, WIDTH);

  int ALTO = HEIGTH * WIDTH;
  for(i = 0; i < HEIGTH; i++) {
    for(j = 0; j < WIDTH; j++) {
      in->set(i, j, in->get(i, j)*ALTO);
    }
  }

  while( true ) {
    // para cada pixel
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
    in->copyOf(out);
  }
  in->deleteIMG();
  delete in;
  return out;
}

/// CORTE DA CURVA DE NIVEL
PBM* PICPU::CORTE (PBM* img, int corte) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOf(img);

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
PBM* PICPU::BINARIO (PBM* img) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOf(img);

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
PBM* PICPU::LABEL (PBM* img) {
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOf(img);

  UnionFind* labels = new UnionFind();
  labels->init(img);

  int x, y, i, j, id;

  /// Passo 1 - encontra o LABEL
  // para cada elemento da img
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


PBM* PICPU::WATERSHED(PBM* img, PBM* original) {
  int i, j, k, l;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();

  PBM* in = new PBM();
  in->copyOf(img);
  PBM* out = new PBM();
  out->copyOf(img);

  // eqto tiver ZEROs na IMG
  while( true ) {
    // para cada pixel
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
    in->copyOf(out);
      // cout << endl; in->print();
  }

  delete in;

  return out;
}

PBM* PICPU::GETBORDA(PBM* img) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  PBM* out = new PBM();
  out->copyOf(img);

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

#endif // PICPU_H