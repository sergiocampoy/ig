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

/*
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
   */


   /*
   v.push_back(Tupla3f(50*cos(0), 0, 50*sin(0)));
   v.push_back(Tupla3f(50*cos((2*M_PI)/3), 0, 50*sin((2*M_PI)/3)));
   v.push_back(Tupla3f(50*cos((4*M_PI)/3), 0, 50*sin((4*M_PI)/3)));
   */

   v.push_back(Tupla3f(50*cos(0)         , 50*sin(-M_PI/6), 50*sin(0)         ));
   v.push_back(Tupla3f(50*cos((2*M_PI)/3), 50*sin(-M_PI/6), 50*sin((2*M_PI)/3)));
   v.push_back(Tupla3f(50*cos((4*M_PI)/3), 50*sin(-M_PI/6), 50*sin((4*M_PI)/3)));
   v.push_back(Tupla3f(0, 50, 0));



  f.push_back(Tupla3i(0, 1, 2));
  f.push_back(Tupla3i(3, 2, 1));
  f.push_back(Tupla3i(3, 1, 0));
  f.push_back(Tupla3i(3, 0, 2));

   

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

   // color modo puntos
   Tupla3f c_puntos(1, 0, 0); // Rojo
   for (unsigned int i = 0; i < v.size(); i++) {
      c_p.push_back(c_puntos);
   }

}

