#include "aux.h"
#include "objrevolucion.h"
#include <fstream>
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {

   unsigned num_vertices = 0, num_caras = 0;
   std::ifstream src;
   std::string na = archivo;

   std::vector<Tupla3f> vertices;

   ply::abrir_archivo(na, src);
   ply::leer_cabecera(src, num_vertices, num_caras, false);
   ply::leer_vertices(num_vertices, vertices, src);
   
   // multiplica el tamaño por 50 (WIP)
   for (unsigned int i = 0; i < vertices.size(); i++)
   {
      vertices[i] = vertices[i]*50;
   }

   crearMalla(vertices, 16);

   colorea();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo, num_instancias);
   colorea();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias)
{
   Tupla3f aux;
   float alpha = (2.0*M_PI) / (float)num_instancias;

   // eje Y
   // crea los vértices
   for (unsigned int i = 0; i < num_instancias; i++)
   {
      for (unsigned int j = 0; j < perfil_original.size(); j++)
      {
         aux(0) = (perfil_original[j])(0) * cos(alpha*(float)i);
         aux(1) = (perfil_original[j])(1);
         aux(2) = (perfil_original[j])(0) * sin(alpha*(float)i);

         printf("(%f, %f, %f)\n", aux(0), aux(1), aux(2));

         v.push_back(aux);
      }    
   }

   // crea las caras
   unsigned int n = 0, tam = perfil_original.size();
   for (unsigned int i = 0; i < num_instancias; i++)
   {
      n = i*tam;
      for (unsigned int j = 0; j < tam-1; j++)
      {
         // arriba -> abajo
         /*
         f.push_back(Tupla3i(j+n, (j+n+tam)%(tam*num_instancias), j+n+1));
         f.push_back(Tupla3i(j+n+1, (j+n+tam)%(tam*num_instancias), (j+n+tam+1)%(tam*num_instancias)));
         */
         f.push_back(Tupla3i(j+n, j+n+1, (j+n+tam)%(tam*num_instancias)));
         f.push_back(Tupla3i(j+n+1, (j+n+tam+1)%(tam*num_instancias), (j+n+tam)%(tam*num_instancias)));
      }
   }
}

