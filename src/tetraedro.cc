#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float size)
{

   // tabla de vértices
   v.push_back(Tupla3f(size*cos(0)         *cos(-M_PI/6), size*sin(-M_PI/6), size*sin(0)         *cos(-M_PI/6)));
   v.push_back(Tupla3f(size*cos((2*M_PI)/3)*cos(-M_PI/6), size*sin(-M_PI/6), size*sin((2*M_PI)/3)*cos(-M_PI/6)));
   v.push_back(Tupla3f(size*cos((4*M_PI)/3)*cos(-M_PI/6), size*sin(-M_PI/6), size*sin((4*M_PI)/3)*cos(-M_PI/6)));
   v.push_back(Tupla3f(0, size, 0));


   // tabla de triángulos
   f.push_back(Tupla3i(0, 1, 2));
   f.push_back(Tupla3i(3, 2, 1));
   f.push_back(Tupla3i(3, 1, 0));
   f.push_back(Tupla3i(3, 0, 2));


   colorea();
}

