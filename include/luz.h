#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

/// Clase abstracta
class Luz {
protected:
	/// Tupla que contiene la posición/dirección
	Tupla4f posicion;
	/// GL_LIGHT<n>
	GLenum id;
	/// Color ambiente
	Tupla4f ambiente;
	/// Color difuso
	Tupla4f difuso;
	/// Color especular
	Tupla4f especular;

public:
	/// "Dibuja" la luz
	void activar();
};



/// Luz Direccional (w = 0)
class LuzDireccional : public Luz {
public:
	// Coordenadas esféricas

	/// Latitud
	float alpha;

	/// Longitud
	float beta;

	/// Constructor
	LuzDireccional (
		Tupla2f direccion,
		GLenum id,
		Tupla4f ambiente,
		Tupla4f difuso,
		Tupla4f especular
	);
	// TODO añadir funciones
};



/// Luz posicional (w = 1)
class LuzPosicional : public Luz {
public:	
	/// Constructor
	LuzPosicional (
		Tupla3f posicion,
		GLenum id,
		Tupla4f ambiente,
		Tupla4f difuso,
		Tupla4f especular
	);
};

#endif