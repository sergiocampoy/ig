#include "material.h"

Material::Material (
   Tupla4f mdifuso,
   Tupla4f mespecular,
   Tupla4f mambiente,
   float brillo
) {
   difuso = mdifuso;
   especular = mespecular;
   ambiente = mambiente;
   this->brillo = brillo;
}

void Material::aplicar()
{
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

   glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
   glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
   glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   // printf("WIP Material::aplicar\n");
   /*
   glMaterialf(GL_FRONT, GL_SHININESS, 64);
   glMaterialfv(GL_FRONT, GL_SPECULAR, Tupla4f(1, 0, 0, 1));
   glMaterialfv(GL_FRONT, GL_DIFFUSE, Tupla4f(0, 0, 1, 1));
   */
/*
GLfloat color[4] = { 1, 1, 1, 1.0 } ;
// hace MA := (r, g, b), inicialmente (0.2,0.2,0.2)
glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color ) ;
// hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color ) ;
// hace MS := (r, g, b), inicialmente (0,0,0)
glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color ) ;
// hace e := v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 60 ) ;
*/
}

