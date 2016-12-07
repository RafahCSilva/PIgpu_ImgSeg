#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <iostream>
#include "PBM.cpp"
#include "PBM1d.cpp"

using namespace std;

class UnionFind {
public:
  UnionFind();
  virtual ~UnionFind();
  void init(PBM* img);
  void init1d(PBM1d* img);
  int FIND( int el );
  void MERGE( int A, int B );
  void flat();
private:
  int* conj;
  int tam;
};

UnionFind::UnionFind() {
  //ctor
}

UnionFind::~UnionFind() {
  //dtor
}

void UnionFind::init(PBM* img) {
  int i, j;
  int HEIGTH = (int) img->getHeight();
  int WIDTH = (int) img->getWidth();

  int tamanho = HEIGTH * WIDTH;
  this-> tam = tamanho;

  this->conj = new int[tamanho];
  for( i = 0; i < HEIGTH ; i++ ) {
    for( j = 0; j < WIDTH ; j++ ) {
      if(img->get(i, j) == 0) {
        this->conj[i * HEIGTH + j] = 0;
      } else {
        this->conj[i * HEIGTH + j] = i * HEIGTH + j;
      }
    }
  }
}

void UnionFind::init1d(PBM1d* img) {
  int i, j;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();

  int tamanho = img->getTam();
  this-> tam = tamanho;

  this->conj = new int[tamanho];
  for( i = 0; i < tamanho ; i++ ) {
    if(img->get1(i) == 0) {
      this->conj[i] = 0;
    } else {
      this->conj[i] = i;
    }
  }
}

int UnionFind::FIND( int el ) {
  if( this->conj[el] == el )
    return el;
  this->conj[el] = FIND( this->conj[el] );
  return this->conj[el];
}

void UnionFind::MERGE( int A, int B ) {
  int raizA = FIND( A );
  int raizB = FIND( B );
  if( raizB < raizA ) this->conj[raizA] = raizB;
  if( raizA < raizB ) this->conj[raizB] = raizA;
}

/// atualiza a raiz (assim achatando a estrutura)
void UnionFind::flat() {
  for( int el = 0; el < this->tam; el++ )
    this->conj[el] = this->FIND( el );
}

#endif // UNIONFIND_H
