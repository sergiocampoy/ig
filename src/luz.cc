#include "luz.h"

void Luz::activar()
{
   glLightfv(id, GL_AMBIENT, colorAmbiente);
   glLightfv(id, GL_DIFFUSE, colorDifuso);
   glLightfv(id, GL_SPECULAR, colorEspecular);

   glLightfv(id, GL_POSITION, posicion);
   // printf("WIP Luz::activar\n");
   //glEnable(GL_LIGHT0);
   //glLightfv(GL_LIGHT0, GL_POSITION, this->posicion);
//   glLightfv(GL_LIGHT0, GL_POSITION, Tupla4f(0, 0, 0, 0));
   //GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
/*
 const GLfloat posf[4] = { 100, 100, 100, 1.0 } ; // (x,y,z,w)
 glLightfv( GL_LIGHT0, GL_POSITION, posf );
 glLightfv(GL_LIGHT0, GL_SPECULAR, Tupla4f(1, 0, 0, 1));

 glLightfv(GL_LIGHT1, GL_DIFFUSE, Tupla4f(0, 0, 1, 1));
*/
//const GLfloat dirf[4] = { 100, 100, 100, 0.0 } ; // (x,y,z,w)
//glLightfv( GL_LIGHT0, GL_POSITION, dirf );
}

LuzDireccional::LuzDireccional (
   const Tupla2f& direccion,
   const GLenum& idLuzOpenGL,
   const Tupla4f& colorAmbiente,
   const Tupla4f& colorDifuso,
   const Tupla4f& colorEspecular
) {
   // Asigna valores de Luz
   id = idLuzOpenGL;
   this->colorAmbiente = colorAmbiente;
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;

   // posicion
   this->posicion = {0, 0, 1, 0};

   // Asigna valor de la dirección
   alpha = direccion(0);
   beta  = direccion(1);
}

void LuzDireccional::VariarAnguloAlpha (float incremento)
{
   alpha += incremento;
}

void LuzDireccional::VariarAnguloBeta (float incremento)
{
   beta += incremento;
}


LuzPosicional::LuzPosicional (
   const Tupla3f& posicion,
   const GLenum& idLuzOpenGL,
   const Tupla4f& colorAmbiente,
   const Tupla4f& colorDifuso,
   const Tupla4f& colorEspecular
) {
   // Asigna valores de luz
   this->id = idLuzOpenGL;
   this->colorAmbiente = colorAmbiente;
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;

   // posicion
   this->posicion(0) = posicion(0);
   this->posicion(1) = posicion(1);
   this->posicion(2) = posicion(2);
   this->posicion(3) = 1; // posicional
}