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
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, int eje, bool tapa_sup=true, bool tapa_inf=true) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, int eje, bool tapa_sup=true, bool tapa_inf=true) ;

   void draw(unsigned int modo_vis, bool vbo, bool tapas) ;
   void setMaterial (Material mat);

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, int eje, bool tapa_sup=true, bool tapa_inf=true);
private:
    ObjRevolucion *tapaSup = nullptr, *tapaInf = nullptr;

    // constructor de tapa
    ObjRevolucion(Tupla3f p, int num_instancias, int eje, bool tapa_sup);

} ;

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
