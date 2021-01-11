#include "material.h"

Material::Material () {}

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

void Material::aplicar () {
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);


   glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
   glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
   glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void Material::operator= (const Material& m) {
    difuso = m.difuso;
    especular = m.especular;
    ambiente = m.ambiente;
    brillo = m.brillo;
}