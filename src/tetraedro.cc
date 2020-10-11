#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
/*
   Tupla3f a(100, 0, 0), b(0, 100, 0), c(0, 0, 100);
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);

   f.push_back(Tupla3i(0, 1, 2));
*/

   v.push_back(Tupla3f( 50,   0,   0));
   v.push_back(Tupla3f(-50,   0,   0));
   v.push_back(Tupla3f(  0,  50,   0));
   v.push_back(Tupla3f(  0, -50,   0));
   v.push_back(Tupla3f(  0,   0,  50));
   v.push_back(Tupla3f(  0,   0, -50));

   f.push_back(Tupla3i(2, 4, 0));
   f.push_back(Tupla3i(2, 0, 5));
   f.push_back(Tupla3i(2, 5, 1));
   f.push_back(Tupla3i(2, 1, 4));

   f.push_back(Tupla3i(3, 4, 1));
   f.push_back(Tupla3i(3, 1, 5));
   f.push_back(Tupla3i(3, 5, 0));
   f.push_back(Tupla3i(3, 0, 4));

}

