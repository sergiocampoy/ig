#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"


class Material
{
private:
   Tupla4f difuso;
   Tupla4f especular;
   Tupla4f ambiente;
   float brillo;

public:
   /// Constructor por defecto
   Material () {}
   /// Constructor con argumentos
   Material (
      Tupla4f mdifuso,
      Tupla4f mespecular,
      Tupla4f mambiente,
      float brillo
   );

   void aplicar();
};

#endif