#ifndef PBM1d_H
#define PBM1d_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class PBM1d {
public:
  PBM1d();
  virtual ~PBM1d();
  int getHeight() {
    return height;
  }
  void setHeight( int val) {
    height = val;
  }
  int getWidth() {
    return width;
  }
  void setWidth(int val) {
    width = val;
  }
  int getTam() {
    return tam;
  }
  void setTam(int val) {
    tam = val;
  }
  int * getMat() {
    return mat;
  }
  void setMat(int * val) {
    mat = val;
  }

  int  get1(int i);
  void set1(int i, int v);
  int  get2(int i, int j);
  void set2(int i, int j, int v);
  void saveAsP1(const  char * arquivo);
  void saveAsP1_(const  char * arquivo);
  void loadAsP1(const  char * arquivo);
  void print();
  void deleteIMG();
  void copyOf(PBM1d * img);
  void copyOfParallel(PBM1d * img);
  void zerado( int h, int w);
  void transpose();
  int  MAX();

  static bool imgIGUAL(PBM1d* A, PBM1d* B);

protected:
private:
  int height;
  int width;
  int tam;
  int * mat;
};

PBM1d::PBM1d() {
  height = 0;
  width = 0;
  tam = 0;
  mat = NULL;
}

PBM1d::~PBM1d() {
  this->deleteIMG();
}

void PBM1d::saveAsP1(const char * arquivo) {
  int i, j;
  FILE *arq = fopen(arquivo, "w");

  if(arq == NULL) {
    cerr << "Nao foi possivel salvar o arquivo: " << arquivo << endl;
    exit(1);
  }

  fprintf(arq, "P1 \n");
  fprintf(arq, "%d\n%d \n", this->width, this->height);
  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      if(this->mat[i * this->height + j] == 0) {
        fprintf(arq, "0 ");
      } else {
        fprintf(arq, "1 ");
      }
    }
    fprintf(arq, "\n");
  }
  fclose(arq);
}

void PBM1d::saveAsP1_(const char * arquivo) {
  int i, j;
  FILE *arq = fopen(arquivo, "w");

  if(arq == NULL) {
    cerr << "Nao foi possivel salvar o arquivo: " << arquivo << endl;
    exit(1);
  }

  fprintf(arq, "P1 \n");
  fprintf(arq, "%d\n%d \n", this->width, this->height);
  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      fprintf(arq, "%d ", this->get2(i, j));
    }
    fprintf(arq, "\n");
  }
  fclose(arq);
}

void PBM1d::loadAsP1(const char * arquivo) {
  int i;
  char p1[10];
  FILE *arq = fopen(arquivo, "r");

  if(arq == NULL) {
    cerr << "Nao foi possivel abrir o arquivo: " << arquivo << endl;
    exit(1);
  }

  fscanf(arq, "%s", &p1);
  fscanf(arq, "%d", &this->width);
  fscanf(arq, "%d", &this->height);

  this->tam = this->width * this->height;

  int mais = (this->tam % 16);
  this->mat = new int[this->tam + (mais ? 16 - mais : 0)];

  for(i = 0; i < this->tam; i++) {
    fscanf(arq, "%d", &this->mat[i]);
  }

  if(mais) {
    for(i = this->tam; i < this->tam + 16 - mais; i++) {
      this->mat[i] = 0;
    }
  }
  this->tam += (mais ? 16 - mais : 0);
  fclose(arq);
}

void PBM1d::print() {
  int i, j;

  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      cout << this->get2(i, j) << ' ';
    }
    cout << endl;
  }
}

void PBM1d::deleteIMG() {
  if (this->mat) {
    delete [] this->mat;
  }

  this->mat = NULL;
  this->height = 0;
  this->width = 0;
  this->tam = 0;
}

void PBM1d::copyOf(PBM1d * img) {
  this->deleteIMG();

  int i;

  this->height = img->getHeight();
  this->width = img->getWidth();
  this->tam = img->getTam();

  this->mat = new int[this->tam];

  for(i = 0; i < this->tam; i++) {
    this->mat [i] = img->get1(i);
  }
}

int PBM1d::get2(int i, int j) {
  return this->mat[i * this->height + j];
}
int PBM1d::get1(int i) {
  return this->mat[i];
}
void PBM1d::set2(int i, int j, int v) {
  this->mat[i * this->height + j] = v;
}
void PBM1d::set1(int i, int v) {
  this->mat[i ] = v;
}

void PBM1d::zerado( int h, int w) {
  int i;
  this->height = h;
  this->width = w;
  this->tam = h * w ;
  int mais = (this->tam % 16);
  this->tam += (mais ? 16 - mais : 0);

  this->mat = new int[this->tam];
  for(i = 0; i < this->tam; i++) {
    this->mat[i] = 0;
  }
}

bool PBM1d::imgIGUAL(PBM1d* A, PBM1d* B) {
  int TAM = A->getTam();

  for( int i = 0; i < TAM; i++ ) {
    if(A->get1(i) != B->get1(i) )
      return false;
  }
  return true;
}

int PBM1d::MAX() {
  int m = this->mat[0];
  for( int i = 0; i < this->tam; i++ )
    if( m < this->get1(i) )
      m = this->get1(i);
  return m;
}

void PBM1d::transpose() {
  int * out = new int[this->tam];
  int H = this->getHeight();
  int W = this->getWidth();

  for( int i = 0; i < H; i++ )
    for( int j = 0; j < W; j++ )
      out[i * H + j] = this->get2(j, i);

  for( int i = H * W; i < this->tam; i++ )
    out[i ] = 0;

  delete[] this->mat;
  this->mat = out;
}

#endif // PBM1d_H
