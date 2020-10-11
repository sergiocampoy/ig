#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   Tupla3f a(100, 0, 0), b(0, 100, 0), c(0, 0, 100);
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);

   f.push_back(Tupla3i(0, 1, 2));

}

