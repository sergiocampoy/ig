#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

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


