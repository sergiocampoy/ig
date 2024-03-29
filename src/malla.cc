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
   
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());

   // modo puntos
   if (modo_vis & VIS_PUN)
   {
      glDisable(GL_CULL_FACE);

      glPointSize(5);

      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      glColorPointer(3, GL_FLOAT, 0, c_p.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

      glEnable(GL_CULL_FACE);
   }

   // modo líneas
   if (modo_vis & VIS_LIN) {
      glDisable(GL_CULL_FACE);
      
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glColorPointer(3, GL_FLOAT, 0, c_l.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

      glEnable(GL_CULL_FACE);
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
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      glDisable(GL_CULL_FACE);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_pun);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activa el VBO
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO

      glEnable(GL_CULL_FACE);
   }

   // modo lineas
   if (modo_vis & VIS_LIN)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDisable(GL_CULL_FACE);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_lin);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activa el VBO
      glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO
      
      glEnable(GL_CULL_FACE);
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
   /*
   if (vbo) // elige el modo de visualización
      draw_ModoDiferido(modo_vis);
   else
      draw_ModoInmediato(modo_vis);
   */

   m.aplicar();

   if (vbo) {
      if (modo_vis & VIS_AJE) {
         draw_ModoDiferido_Ajedrez();
      } else {
         draw_ModoDiferido(modo_vis);
      }
   } else {
      if (modo_vis & VIS_AJE) {
         draw_ModoInmediato_Ajedrez();
      } else {
         draw_ModoInmediato(modo_vis);
      }
   }

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


void Malla3D::draw_ModoInmediato_Ajedrez()
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, v.data());


   // Divide los triángulos en dos grupos
   if (f_par.size() == 0) {
      for (unsigned int i = 0; i < f.size(); i++) {
         if (i % 2 == 0) {
            f_par.push_back(f[i]);
         } else {
            f_imp.push_back(f[i]);
         }
      }
   }

   glPolygonMode(GL_FRONT, GL_FILL);

   glColorPointer(3, GL_FLOAT, 0, c_l.data());
   glDrawElements(GL_TRIANGLES, f_par.size()*3, GL_UNSIGNED_INT, f_par.data());

   glColorPointer(3, GL_FLOAT, 0, c_p.data());
   glDrawElements(GL_TRIANGLES, f_imp.size()*3, GL_UNSIGNED_INT, f_imp.data());


   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // lo deja como estaba

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}


void Malla3D::draw_ModoDiferido_Ajedrez()
{
   // Divide los triángulos en dos grupos
   if (f_par.size() == 0) {
      for (unsigned int i = 0; i < f.size(); i++) {
         if (i % 2 == 0) {
            f_par.push_back(f[i]);
         } else {
            f_imp.push_back(f[i]);
         }
      }
   }


   // Crea los vbos (solo una vez)
   if (id_vbo_tri_par == 0)
      id_vbo_tri_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f_par.size()*3*sizeof(int), f_par.data());

   if (id_vbo_tri_imp == 0)
      id_vbo_tri_imp = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f_imp.size()*3*sizeof(int), f_imp.data());


   // inicializa array de vértices y color
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // enlaza array de vértices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);


   glPolygonMode(GL_FRONT, GL_FILL);

   // Pinta las caras pares del color de los líneas
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_lin);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_par); // activa el VBO
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO


   // Pinta las caras impares del color de las puntos
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_pun);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_imp); // activa el VBO
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0); // pinta
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactiva el VBO


   // Deja todo como estaba
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::colorea()
{
   // colores
   Tupla3f c_solido(0.8f, 0.8f, 0.8f); // Gris
   Tupla3f c_linea (0.0f, 1.0f, 0.0f); // Verde
   Tupla3f c_puntos(1.0f, 0.0f, 0.0f); // Rojo

   // color sólido
   for (unsigned int i = 0; i < v.size(); i++)
      c_s.push_back(c_solido);

   // color línea
   for (unsigned int i = 0; i < v.size(); i++)
      c_l.push_back(c_linea);

   // color puntos
   for (unsigned int i = 0; i < v.size(); i++)
      c_p.push_back(c_puntos);
}



// P3

/// Calcula las tablas de normales (caras y vértices)
void Malla3D::calcular_normales()
{
   // Calcula la tabla de normales de las caras
   for (auto cara : f)
   {
      Tupla3f p, q, r;
      Tupla3f a, b;
      Tupla3f m, n;

      // obtiene los 3 vértices de la cara
      p = v[cara(0)];
      q = v[cara(1)];
      r = v[cara(2)];

      // calcula los vectores a y b
      a = q - p;
      b = r - p;

      // vector perpendicular
      m = a.cross(b);
      
      // vector normalizado
      n = m.normalized();

      // añade el vector normalizado a la tabla
      n_c.push_back(n);
   }

   // inicializa la tabla de normales de los vértices
   for (auto i : v)
   {
      n_v.emplace_back(0, 0, 0);
   }

   // Calcula la tabla de normales de los vértices
   for (unsigned int i = 0; i < f.size(); i++)
   {
      Tupla3i cara = f[i];
      Tupla3f normal = n_c[i];

      n_v.at(cara(0)) = n_v[cara(0)] + normal;
      n_v.at(cara(1)) = n_v[cara(1)] + normal;
      n_v.at(cara(2)) = n_v[cara(2)] + normal;
   }

   printf("normales:\n");
   for (auto i : n_v)
   {
      //i = i.normalized();
   }

   for (unsigned int i = 0; i < n_v.size(); i++)
   {
      //printf("%d, %d, %d\n", n_v[i](0), n_v[i](1), n_v[i](2));
      n_v[i] = n_v[i].normalized();
   }
}