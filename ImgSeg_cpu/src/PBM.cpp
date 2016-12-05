#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PBM.h"

using namespace std;

PBM::PBM() {
}

PBM::~PBM() {
	this->deleteIMG();
}

void PBM::saveAsP1(const char * arquivo) {
	FILE *arq = fopen(arquivo, "w");
	int i, j;

	fprintf(arq, "P1 \n");
	//fprintf(arq, "#comentario qualquer \n");
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
//	cout << "loadAsP1\n";
	int i, j;
	char * p1;
	FILE *arq = fopen(arquivo, "r"); //	cout << "leu\n";

	fscanf(arq, "%s", &p1); //	cout << "p1\n";
	fscanf(arq, "%ud", &this->width);
	fscanf(arq, "%ud", &this->height);//	cout << "WH " << this->width << " " << this->height << endl;

	this->mat = new int*[this->height];
	for(i = 0; i < this->height; i++)
		this->mat[i] = new int[this->width];//	cout << "mallocOK\n";

	for(i = 0; i < this->height; i++) {
		for(j = 0; j < this->width; j++) {
			fscanf(arq, "%ud", &this->mat[i][j]);
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

void circulo(PBM* img, int x, int y, int raio) {
	for( int i = x - raio; i < x + raio; i++ )
		for( int j = y - raio; j < y + raio; j++ )
			if( (pow(i - x, 2) + pow(j - y, 2)) <= pow(raio, 2) )
				img->set(i, j, 1);
}

PBM* PBM::gerador1100() {
	int tam = 1100;
	PBM* out = new PBM();
	out->zerado( tam, tam);
	for( int x = 250; x < tam - 150; x += 200 )
		for( int y = 250; y < tam - 150; y += 200 )
			circulo(out, x, y, 110);
	out->saveAsP1("gerador1100.pbm");
	return out;
}
