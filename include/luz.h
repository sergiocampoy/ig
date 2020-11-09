#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

/// Clase abstracta
class Luz
{
protected:
   Tupla4f posicion;
   GLenum id;
   Tupla4f colorAmbiente;
   Tupla4f colorDifuso;
   Tupla4f colorEspecular;

public:
   void activar();
};



class LuzDireccional : public Luz
{
protected:
   // Coordenadas esféricas
   /// Latitud
   float alpha;
   /// Longitud
   float beta;
public:
   /// Constructor
   LuzDireccional (
      const Tupla2f& direccion,
      const GLenum& idLuzOpenGL,
      const Tupla4f& colorAmbiente,
      const Tupla4f& colorDifuso,
      const Tupla4f& colorEspecular
   );
   /// Constructor pdf
   LuzDireccional (const Tupla2f& orientacion);
   /// Cambiar ángulo alpha
   void VariarAnguloAlpha (float incremento);
   /// Cambiar ángulo beta
   void VariarAnguloBeta (float incremento);
};



class LuzPosicional : public Luz
{
public:
   /// Constructor
   LuzPosicional (
      const Tupla3f& posicion,
      const GLenum& idLuzOpenGL,
      const Tupla4f& colorAmbiente,
      const Tupla4f& colorDifuso,
      const Tupla4f& colorEspecular
   );
   /// Constructor
   // LuzPosicional (const Tupla3f& posicion);
};

#endif