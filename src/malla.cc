#include "aux.h"
#include "malla.h"
#include "menu.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(unsigned int modo_vis)
{
   // inicial
/*
   // habilita el uso de un array de vértices
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // indica el formato y la dirección de memoria del array de vértices
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glColorPointer(3, GL_FLOAT, 0, c.data());

   // dibuja el array
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

   // deshabilita el uso de un array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
*/

   // new
   
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());

   // modo puntos
   if (modo_vis & VIS_PUN)
   {
      glPointSize(5);

      glPolygonMode(GL_FRONT, GL_POINT);
      glColorPointer(3, GL_FLOAT, 0, c_p.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
   }

   // modo líneas
   if (modo_vis & VIS_LIN) {
      glPolygonMode(GL_FRONT, GL_LINE);
      glColorPointer(3, GL_FLOAT, 0, c_l.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
   }

   // modo sólido
   if (modo_vis & VIS_SOL) {
      glPolygonMode(GL_FRONT, GL_FILL);
      glColorPointer(3, GL_FLOAT, 0, c_s.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
   }

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // lo deja como estaba

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(unsigned int modo_vis)
{
   // Crea los VBOs (solo la primera vez que se llama a la función)
   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());

   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
   
   if (id_vbo_col == 0)
      id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), c.data());
   
   if (id_vbo_col_pun == 0)
      id_vbo_col_pun = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), c_p.data());
   
   if (id_vbo_col_lin == 0)
      id_vbo_col_lin = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), c_l.data());
   
   if (id_vbo_col_sol == 0)
      id_vbo_col_sol = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), c_s.data());
   
   // inicializa array de vértices y color
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // enlaza array de vértices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // modo puntos
   if (modo_vis & VIS_PUN)
   {
      glPointSize(5);
      glPolygonMode(GL_FRONT, GL_POINT);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_pun);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activa el VBO
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO
   }

   // modo lineas
   if (modo_vis & VIS_LIN)
   {
      glPolygonMode(GL_FRONT, GL_LINE);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_lin);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activa el VBO
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO
   }

   // modo sólido
   if (modo_vis & VIS_SOL)
   {
      glPolygonMode(GL_FRONT, GL_FILL);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_sol);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activa el VBO
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO
   }

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(unsigned int modo_vis, bool vbo)
{
   if (vbo) // elige el modo de visualización
      draw_ModoDiferido(modo_vis);
   else
      draw_ModoInmediato(modo_vis);
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
