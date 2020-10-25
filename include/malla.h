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

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void colorea();

   std::vector<Tupla3f> v ; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c ; // tabla de colores de los vértices (una tupla por vértice, con tres floats)

   std::vector<Tupla3f> c_p; // colores modo puntos
   std::vector<Tupla3f> c_l; // colores modo líneas
   std::vector<Tupla3f> c_s; // colores modo sólido

   std::vector<Tupla3i> f_par; // triángulos del modo ajedrez
   std::vector<Tupla3i> f_imp; // triángulos del modo ajedrez
   

   // VBOs modo diferido
   GLuint id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0; // inicializados a 0
   GLuint id_vbo_col_pun = 0, id_vbo_col_lin = 0, id_vbo_col_sol = 0;
   GLuint id_vbo_tri_par = 0, id_vbo_tri_imp = 0;

} ;

GLuint CrearVBO(GLuint tipo_vbo, GLuint size_bytes, GLvoid* puntero_ram);


#endif
