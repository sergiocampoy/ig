// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
public:
   /// Constructor sin argumentos
   ObjRevolucion();
   /// Constructor por archivo
   ObjRevolucion(
      const std::string & archivo,
      int num_instancias,
      int eje,
      bool tapa_sup=true,
      bool tapa_inf=true
   );
   // Constructor por vector de vertices
   ObjRevolucion(
      std::vector<Tupla3f> vertices,
      int num_instancias,
      int eje,
      bool tapa_sup=true,
      bool tapa_inf=true
   );
   // Método para dibujar (con o sin tapas)
   void draw(unsigned int modo_vis, bool vbo, bool tapas) ;

protected:
   /// crea los vectores de vértices y caras a partir de un perfil
   void crearMalla(
      std::vector<Tupla3f> perfil_original,
      int num_instancias,
      int eje,
      bool tapa_sup=true,
      bool tapa_inf=true
   );

   void creaTapas(
      std::vector<Tupla3f> perfil_original,
      int num_instancias,
      int eje,
      bool tapa_sup=true,
      bool tapa_inf=true
   );

private:
   // TBD
   ObjRevolucion *tapaSup = nullptr, *tapaInf = nullptr;
   /// tamaño del vector de caras SIN TAPAS
   int tamSinTapas;
   int tamParSinTapas;
   int tamImpSinTapas;

   // constructor de tapa TBD
   ObjRevolucion(Tupla3f p, int num_instancias, int eje, bool tapa_sup);

};

class Cilindro : public ObjRevolucion
{
public:
   Cilindro (
      const int num_vert_perfil,
      const int num_instancias_perf,
      const float altura,
      const float radio
   );
};

class Cono : public ObjRevolucion
{
public:
   Cono (
      const int num_vert_perfil,
      const int num_instancias_perf,
      const float altura,
      const float radio
   );
};

class Esfera : public ObjRevolucion
{
public:
   Esfera (
      const int num_vert_perfil,
      const int num_instancias_perfil,
      const float radio
   );
};



#endif
