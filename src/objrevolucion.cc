#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <fstream>




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, int eje, bool tapa_sup, bool tapa_inf) {

   unsigned num_vertices = 0, num_caras = 0;
   std::vector<Tupla3f> vertices;
   std::ifstream src;
   std::string na = archivo;

   // lee los datos del archivo
   ply::abrir_archivo(na, src);
   ply::leer_cabecera(src, num_vertices, num_caras, false);
   ply::leer_vertices(num_vertices, vertices, src);

   crearMalla(vertices, num_instancias, eje, tapa_sup, tapa_inf);
   colorea();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, int eje, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo, num_instancias, eje, tapa_sup, tapa_inf);
   colorea();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, int eje, bool tapa_sup, bool tapa_inf)
{
   std::vector<Tupla3f> perfil_ascendente;
   Tupla3f aux;
   float alpha = (2.0*M_PI) / (float)num_instancias;

   // comprueba que los puntos se dan en orden ascendente (invierte si no)
   if (perfil_original.front()(eje) < perfil_original.back()(eje)) {
      perfil_ascendente = perfil_original;
   } else {
      for (auto p : perfil_original)
         perfil_ascendente.insert(perfil_ascendente.begin(), p);
   }

   // calcula distancias de los puntos al eje de rotación
   std::vector<float> modulos;
   for (auto p : perfil_ascendente)
   {
      p(eje) = 0;
      modulos.push_back(sqrt(p.lengthSq()));
   }


   // rellena el vector de vértices
   for (unsigned int i = 0; i < num_instancias; i++)
   {
      for (unsigned int j = 0; j < perfil_ascendente.size(); j++)
      {
         aux(eje) = (perfil_ascendente[j])(eje);
         aux((eje+1)%3) = (modulos[j] * sin(alpha*i));
         aux((eje+2)%3) = (modulos[j] * cos(alpha*i));

         v.push_back(aux);
      }
   }

   // rellena el vector de caras
   unsigned int n = 0, tam = perfil_ascendente.size();
   for (unsigned int i = 0; i < num_instancias; i++)
   {
      n = i*tam;
      for (unsigned int j = 0; j < tam-1; j++)
      {
         f.push_back(Tupla3i(j+n, j+n+1, (j+n+tam)%(tam*num_instancias)));
         f.push_back(Tupla3i(j+n+1, (j+n+tam+1)%(tam*num_instancias), (j+n+tam)%(tam*num_instancias)));
      }
   }

   // Detecta y crea las tapas si es necesario
   if (tapa_sup && !(modulos.back() == 0))
      tapaSup = new ObjRevolucion(v.back(), num_instancias, eje, true);

   if (tapa_inf && !(modulos.front() == 0))
      tapaInf = new ObjRevolucion(v.front(), num_instancias, eje, false);
}


ObjRevolucion::ObjRevolucion(Tupla3f p, int num_instancias, int eje, bool tapa_sup)
{
   Tupla3f aux(p);
   float alpha = (2.0*M_PI) / (float)num_instancias;

   // Calcula la distancia del eje al punto
   aux(eje) = 0;
   float modulo = sqrt(aux.lengthSq());

   // añade el centro al array de vértices
   aux(0) = 0; aux(1) = 0; aux(2) = 0;
   aux(eje) = p(eje);
   v.push_back(aux);

   // añade el resto de puntos al array de vértices (eye Y)
   for (unsigned int i = 0; i < num_instancias; i++)
   {
      aux((eje+2)%3) = modulo * cos(alpha*(float)i);
      aux(eje) = p(eje);
      aux((eje+1)%3) = modulo * sin(alpha*(float)i);

      v.push_back(aux);
   }

   // crea el vector de caras
   if (tapa_sup) {
      for (unsigned int i = 0; i < num_instancias; i++)
         f.push_back(Tupla3i(i+1, 0, 1+(i+1)%num_instancias));
   } else {
      for (unsigned int i = 0; i < num_instancias; i++)
         f.push_back(Tupla3i(0, i+1, 1+(i+1)%num_instancias));
   }

   colorea();
}

// dibuja primero las tapas y luego el ObjRevolución
void ObjRevolucion::draw(unsigned int modo_vis, bool vbo, bool tapas)
{
   // Dibuja las tapas
   if (tapas){
      if (tapaSup != nullptr)
         tapaSup->draw(modo_vis, vbo, false);

      if (tapaInf != nullptr)
         tapaInf->draw(modo_vis, vbo, false);
   }

   // dibuja el cuerpo
   Malla3D::draw(modo_vis, vbo);
}


Cilindro::Cilindro (
   const int num_vert_perfil,
   const int num_instancias_perf,
   const float altura,
   const float radio
) {
   std::vector<Tupla3f> perfil;

   for (unsigned int i = 0; i < num_vert_perfil; i++) {
      perfil.emplace_back (
         radio,
         altura*((float)i/(num_vert_perfil-1)),
         0
      );
   }

   crearMalla(perfil, num_instancias_perf, 1, true, true);
   colorea();
}


Cono::Cono (
   const int num_vert_perfil,
   const int num_instancias_perf,
   const float altura,
   const float radio
) {
   std::vector<Tupla3f> perfil;

   for (unsigned int i = 0; i < num_vert_perfil; i++) {
      perfil.emplace_back (
         radio*((float)(num_vert_perfil-i-1)/(num_vert_perfil)),
         altura*((float)i/(num_vert_perfil-1)),
         0
      );
   }

   crearMalla(perfil, num_instancias_perf, 1, false, true);
   colorea();
}


Esfera::Esfera (
   const int num_vert_perfil,
   const int num_instancias_perf,
   const float radio
) {
   std::vector<Tupla3f> perfil;
   float alpha = (M_PI) / (float)(num_vert_perfil);

   for (unsigned int i = 0; i < num_vert_perfil; i++)
   {
      perfil.emplace_back (
         radio * sin(i*alpha),
         radio * cos(i*alpha),
         0
      );
   }

   crearMalla(perfil, num_instancias_perf, 1, false, false);
   colorea();
}