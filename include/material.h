#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material {
private:
	Tupla4f ambiente;
	Tupla4f difuso;
	Tupla4f especular;
	float brillo;

public:
	/// Constructor por defecto
	Material () {}

	/// Constructor con argumentos
	Material (
		Tupla4f ambiente,
		Tupla4f difuso,
		Tupla4f especular,
		float brillo
	);

	/// "Dibuja" el material
	void aplicar ();
};

#endif
