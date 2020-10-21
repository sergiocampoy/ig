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


   // color sólido
   Tupla3f c_solido(0.8, 0.8, 0.8); // Gris
   for (unsigned int i = 0; i < v.size(); i++) {
      c_s.push_back(c_solido);
   }

   // color línea
   Tupla3f c_linea(0, 1, 0); // Verde
   for (unsigned int i = 0; i < v.size(); i++) {
      c_l.push_back(c_linea);
   }

   // color modo puntos
   Tupla3f c_puntos(1, 0, 0); // Rojo
   for (unsigned int i = 0; i < v.size(); i++) {
      c_p.push_back(c_puntos);
   }
}

