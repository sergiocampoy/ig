#include "material.h"

Material::Material (
   Tupla4f mdifuso,
   Tupla4f mespecular,
   Tupla4f mambiente,
   float brillo
) {
   difuso = mdifuso;
   especular = mespecular;
   ambiente = mambiente;
   this->brillo = brillo;
}

void Material::aplicar()
{
   printf("WIP Material::aplicar\n");
}

