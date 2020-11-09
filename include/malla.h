// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

#include "material.h" // P3

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(unsigned int modo_vis);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(unsigned int modo_vis);

   // dibuja el objeto en ajedrez
   void draw_ModoInmediato_Ajedrez();
   void draw_ModoDiferido_Ajedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(unsigned int modo_vis, bool) ;

   /// Asigna un material a la malla
   inline void setMaterial (Material mat) { m = mat; }

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void colorea();

   /// Tabla de vértices
   std::vector<Tupla3f> v ;
   /// Tabla de triángulos
   std::vector<Tupla3i> f ;
   /// Tabla de colores
   std::vector<Tupla3f> c ;

   /// Tabla de colores (modo puntos)
   std::vector<Tupla3f> c_p;
   /// Tabla de colores (modo líneas)
   std::vector<Tupla3f> c_l;
   /// Tabla de colores (modo sólido)
   std::vector<Tupla3f> c_s;

   /// Tabla de triángulos pares (modo ajedrez)
   std::vector<Tupla3i> f_par;
   /// Tabla de triángulos impares (modo ajedrez)
   std::vector<Tupla3i> f_imp;
   

   // VBOs modo diferido
   GLuint id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0; // inicializados a 0
   GLuint id_vbo_col_pun = 0, id_vbo_col_lin = 0, id_vbo_col_sol = 0;
   GLuint id_vbo_tri_par = 0, id_vbo_tri_imp = 0;



   // P3 

   /// Tabla de normales de las caras
   std::vector<Tupla3f> n_c;
   /// Tabla de normales de los vértices
   std::vector<Tupla3f> n_v;
   /// Tipo de material
   Material m;
} ;

GLuint CrearVBO(GLuint tipo_vbo, GLuint size_bytes, GLvoid* puntero_ram);


#endif
