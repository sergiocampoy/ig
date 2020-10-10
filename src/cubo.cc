#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   Tupla3f a(lado, 0, 0), b(0, lado, 0), c(0, 0, lado);
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.push_back(Tupla3i(0, 1, 2));
}

