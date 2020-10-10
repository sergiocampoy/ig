#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)

   typedef GLfloat Real; // renombra los tipos de GL como Real y Natural
   typedef GLuint Natural;
   
   const unsigned int X=0, Y=1, Z=2; // define el orden de las coordenadas

   typedef Real Tupla3r[3]; // define un tipo de array de 3 reales/naturales
   typedef Natural Tupla3n[3];

   typedef struct {
      unsigned long num_tri;
      Tupla3r* tri;
   } mallaTA;

   mallaTA test;


  //
  // habilita el uso de un array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  
  // indica el formato y la dirección de memoria del array de vértices
  glVertexPointer(3, GL_FLOAT, 0, v.data());

  // dibuja el array
  glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

  // deshabilita el uso de un array de vértices
  glDisableClientState(GL_VERTEX_ARRAY);
  
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
   if (id_vbo_ver == 0)
   {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
   }

   if (id_vbo_tri == 0)
   {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
   }

   // pinta

   glEnableClientState(GL_VERTEX_ARRAY); // habilita la tabla de vértices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activa el VBO
   glVertexPointer(3, GL_FLOAT, 0, 0); // enlaza el VBO
   glBindBuffer(GL_ARRAY_BUFFER, 0); // desactiva el VBO
   

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activa el VBO
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO

   glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
   // completar .....(práctica 1)

}

GLuint CrearVBO(GLuint tipo_vbo, GLuint size_bytes, GLvoid* puntero_ram)
{
   GLuint id_vbo;

   glGenBuffers(1, &id_vbo); // crea VBO

   glBindBuffer(tipo_vbo, id_vbo); // vincula VBO

   // realiza la transferencia
   glBufferData(tipo_vbo, size_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0); // desvincula el VBO

   return id_vbo;
}
