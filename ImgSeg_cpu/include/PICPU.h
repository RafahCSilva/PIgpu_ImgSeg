#ifndef PICPU_H
#define PICPU_H
#include "PBM.h"

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

#endif // PICPU_H
