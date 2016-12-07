#ifndef PBM_H
#define PBM_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class PBM {
public:
  PBM();
  virtual ~PBM();
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
  int ** getMat() {
    return mat;
  }
  void setMat(int ** val) {
    mat = val;
  }

  int  get(int i, int j);
  void set(int i, int j, int v);
  void saveAsP1(const  char * arquivo);
  void loadAsP1(const  char * arquivo);
  void print();
  void deleteIMG();
  void copyOf(PBM * img);
  void copyOfParallel(PBM * img);
  void zerado( int h, int w);
  int  MAX();

  static bool imgIGUAL(PBM* A, PBM* B);

protected:
private:
  int height;
  int width;
  int ** mat;
};

PBM::PBM() {
  height = 0;
  width = 0;
  mat = NULL;
}

PBM::~PBM() {
  this->deleteIMG();
}

void PBM::saveAsP1(const char * arquivo) {
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
      if(this->mat[i][j] == 0) {
        fprintf(arq, "0 ");
      } else {
        fprintf(arq, "1 ");
      }
    }
    fprintf(arq, "\n");
  }
  fclose(arq);
}

void PBM::loadAsP1(const char * arquivo) {
  int i, j;
  char * p1;
  FILE *arq = fopen(arquivo, "r");

  if(arq == NULL) {
    cerr << "Nao foi possivel abrir o arquivo: " << arquivo << endl;
    exit(1);
  }

  fscanf(arq, "%s", &p1);
  fscanf(arq, "%d", &this->width);
  fscanf(arq, "%d", &this->height);

  this->mat = new int*[this->height];
  for(i = 0; i < this->height; i++)
    this->mat[i] = new int[this->width];

  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      fscanf(arq, "%d", &this->mat[i][j]);
    }
  }
  fclose(arq);
}

void PBM::print() {
  int i, j;

  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      cout << this->mat[i][j] << ' ';
    }
    cout << endl;
  }
}

void PBM::deleteIMG() {
  if (this->mat) {
    for (int i = 0; i < this->height; ++i)
      delete [] this->mat[i];
    delete [] this->mat;
  }

  this->mat = NULL;
  this->height = 0;
  this->width = 0;
}

void PBM::copyOf(PBM * img) {
  this->deleteIMG();

  int i, j;

  this->height = img->getHeight();
  this->width = img->getWidth();

  this->mat = new int*[this->height];
  for(i = 0; i < this->height; i++)
    this->mat[i] = new int[this->width];

  for(i = 0; i < this->height; i++) {
    for(j = 0; j < this->width; j++) {
      this->mat [i][j] = img->get(i, j);
    }
  }
}

int PBM::get(int i, int j) {
  return this->mat[i][j];
}
void PBM::set(int i, int j, int v) {
  this->mat[i][j] = v;
}

void PBM::zerado( int h, int w) {
  int i, j;
  this->height = h;
  this->width = w;

  this->mat = new int*[this->height];
  for(i = 0; i < this->height; i++) {
    this->mat[i] = new int[this->width];
    for(j = 0; j < this->width; j++) {
      this->mat [i][j] = 0;
    }
  }
}

bool PBM::imgIGUAL(PBM* A, PBM* B) {
  int HEIGTH = A->getHeight();
  int WIDTH = A->getWidth();

  for( int i = 0; i < HEIGTH; i++ ) {
    for( int j = 0; j < WIDTH; j++ ) {
      if(A->get(i, j) != B->get(i, j) )
        return false;
    }
  }
  return true;
}

int PBM::MAX() {
  int m = this->mat[0][0];
  for( int i = 0; i < this->height; i++ )
    for( int j = 0; j < this->width; j++ )
      if( m < this->get(i, j) )
        m = this->get(i, j);
  return m;
}

#endif // PBM_H
