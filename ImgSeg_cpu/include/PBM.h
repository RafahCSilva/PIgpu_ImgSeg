#ifndef PBM_H
#define PBM_H
#include <iostream>
#include <string>

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
	void zerado( int h, int w);
	int  MAX();

	static bool imgIGUAL(PBM* A, PBM* B);
	static PBM* gerador1100();

protected:
private:
	int height = 0;
	int width = 0;
	int ** mat = NULL;
};

#endif // PBM_H
