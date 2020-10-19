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


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

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


   // inicializa la tabla de colores
   // monocromo
   
   // color sólido
   Tupla3f c_solido(0.8, 0.8, 0.8);
   for (unsigned int i = 0; i < v.size(); i++) {
      c_s.push_back(c_solido);
   }

   // color línea
   Tupla3f c_linea(0, 1, 0);
   for (unsigned int i = 0; i < v.size(); i++) {
      c_l.push_back(c_linea);
   }

   /*
   // nomonocromo
   c.push_back(Tupla3f(0, 0, 0));
   c.push_back(Tupla3f(0, 0, 1));
   c.push_back(Tupla3f(0, 1, 0));
   c.push_back(Tupla3f(0, 1, 1));
   c.push_back(Tupla3f(1, 0, 0));
   c.push_back(Tupla3f(1, 0, 1));
   c.push_back(Tupla3f(1, 1, 0));
   c.push_back(Tupla3f(1, 1, 1));
   */

   // color modo puntos
   Tupla3f c_puntos(1, 0, 0); // Rojo
   for (unsigned int i = 0; i < v.size(); i++) {
      c_p.push_back(c_puntos);
   }

}

