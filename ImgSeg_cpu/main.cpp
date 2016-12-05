#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <ctime>
#include "PBM.h"
#include "PICPU.h"
#include "TEMPO.h"

int main() {
	bool verbose = true;
	bool verbose2 = false;

	if(verbose)		cout << "\nCarregando Original\n";
  //PBM* img1 = PBM::gerador1100();
	PBM* img1 = new PBM();
	img1->loadAsP1("gerador1100.pbm");
	if(verbose2)		img1->print();


	if(verbose)		cout << "\nTD\n";
	TEMPO_tic();
	PBM* img2 = PICPU::TD2D(img1);
	TEMPO_toc();
	if(verbose2)		img2->print();

	if(verbose)		cout << "\nCORTE abaixo de ";
	int corte = ceil( img2->MAX() * 0.6 );
	if(verbose)		cout << corte << "\n";
	TEMPO_tic();
	PBM* img3 = PICPU::CORTE(img2, corte);
	TEMPO_toc();
	if(verbose2)	img3->print();

	if(verbose)		cout << "\nBINARIO\n";
	TEMPO_tic();
	PBM* img4 = PICPU::BINARIO(img3);
	TEMPO_toc();
	if(verbose2)		img4->print();

	if(verbose)		cout << "\nLABEL\n";
	TEMPO_tic();
	PBM* img5 = PICPU::LABEL(img4);
	TEMPO_toc();
	if(verbose2)		img5->print();

	if(verbose)		cout << "\nWATERSHED\n";
	TEMPO_tic();
	PBM* img6 = PICPU::WATERSHED(img5, img1);
	TEMPO_toc();
	if(verbose2)		img6->print();

	if(verbose)		cout << "\nDestaca a borda\n";
	TEMPO_tic();
	PBM* img7 = PICPU::GETBORDA(img6);
	TEMPO_toc();
	if(verbose2)		img7->print();

	img7->saveAsP1("saida.pbm");


	delete img1;
	delete img2;
	delete img3;
	delete img4;
	delete img5;
	delete img6;
	delete img7;

	return 0;
}
