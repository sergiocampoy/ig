#include "luz.h"

void Luz::activar()
{
   printf("WIP Luz::activar\n");
}

LuzDireccional::LuzDireccional (
   const Tupla2f& direccion,
   const GLenum& idLuzOpenGL,
   const Tupla4f& colorAmbiente,
   const Tupla4f& colorDifuso,
   const Tupla4f& colorEspecular
) {
   // Asigna valores de Luz
   id = idLuzOpenGL;
   this->colorAmbiente = colorAmbiente;
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;

   // posicion
   this->posicion(0) = direccion(0);
   this->posicion(1) = direccion(1);
   this->posicion(3) = 0; // direccional

   // Asigna valor de la dirección
   alpha = direccion(0);
   beta  = direccion(1);
}

void LuzDireccional::VariarAnguloAlpha (float incremento)
{
   alpha += incremento;
   posicion(0) = alpha;
}

void LuzDireccional::VariarAnguloBeta (float incremento)
{
   beta += incremento;
   posicion(1) = beta;
}


LuzPosicional::LuzPosicional (
   const Tupla3f& posicion,
   const GLenum& idLuzOpenGL,
   const Tupla4f& colorAmbiente,
   const Tupla4f& colorDifuso,
   const Tupla4f& colorEspecular
) {
   // Asigna valores de luz
   this->id = idLuzOpenGL;
   this->colorAmbiente = colorAmbiente;
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;

   // posicion
   this->posicion(0) = posicion(0);
   this->posicion(1) = posicion(1);
   this->posicion(2) = posicion(2);
   this->posicion(3) = 1; // posicional
}