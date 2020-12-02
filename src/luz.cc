#include "luz.h"

void Luz::activar () {
	glLightfv(id, GL_AMBIENT, ambiente);
	glLightfv(id, GL_AMBIENT, difuso);
	glLightfv(id, GL_AMBIENT, especular);

	glLightfv(id, GL_POSITION, posicion);
}

LuzDireccional::LuzDireccional (
	Tupla2f direccion,
	GLenum id,
	Tupla4f ambiente,
	Tupla4f difuso,
	Tupla4f especular
) {
	this->id = id;
	this->ambiente = ambiente;
	this->difuso = difuso;
	this->especular = especular;

	// TODO posición
}


LuzPosicional::LuzPosicional (
	Tupla3f posicion,
	GLenum id,
	Tupla4f ambiente,
	Tupla4f difuso,
	Tupla4f especular
) {
	// Asigna los valores de la luz
	this->id = id;
	this->ambiente = ambiente;
	this->difuso = difuso;
	this->especular = especular;

	// Posicion
	this->posicion = { posicion(0), posicion(1), posicion(2), 1 };
}
