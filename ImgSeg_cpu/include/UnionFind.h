#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "PBM.h"

class UnionFind {
public:
	UnionFind();
	virtual ~UnionFind();
	void init(PBM* img);
	int FIND( int el );
	void MERGE( int A, int B );
	void flat();
private:
	int* conj;
	int tam;
};

#endif // UNIONFIND_H
