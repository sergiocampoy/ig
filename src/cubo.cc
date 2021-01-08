#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado, Tupla3f pos)
{
   float x = pos[0], y = pos[1], z = pos[2];

   // inicializar la tabla de vértices
   v.push_back(Tupla3f(x +    0, y +    0, z + lado));
   v.push_back(Tupla3f(x + lado, y +    0, z + lado));
   v.push_back(Tupla3f(x +    0, y + lado, z + lado));
   v.push_back(Tupla3f(x + lado, y + lado, z + lado));
   v.push_back(Tupla3f(x +    0, y +    0, z +    0));
   v.push_back(Tupla3f(x + lado, y +    0, z +    0));
   v.push_back(Tupla3f(x +    0, y + lado, z +    0));
   v.push_back(Tupla3f(x + lado, y + lado, z +    0));


   // tabla de caras
   f.push_back(Tupla3i(0, 1, 2));
   f.push_back(Tupla3i(1, 3, 2));
   f.push_back(Tupla3i(2, 3, 7));
   f.push_back(Tupla3i(2, 7, 6));
   f.push_back(Tupla3i(1, 7, 3));
   f.push_back(Tupla3i(1, 5, 7));
   f.push_back(Tupla3i(6, 7, 4));
   f.push_back(Tupla3i(7, 5, 4));
   f.push_back(Tupla3i(0, 4, 1));
   f.push_back(Tupla3i(1, 4, 5));
   f.push_back(Tupla3i(2, 6, 4));
   f.push_back(Tupla3i(0, 2, 4));
}

