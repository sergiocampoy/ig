#include "luz.h"

void Luz::aplicar () {
    glLightfv (id, GL_DIFFUSE, difuso);
    glLightfv (id, GL_SPECULAR, especular);
    glLightfv (id, GL_AMBIENT, ambiente);
    glLightfv (id, GL_POSITION, posicion);
}

LuzPosicional::LuzPosicional (
    Tupla3f posicion,
    GLenum id,
    Tupla4f difuso,
    Tupla4f especular,
    Tupla4f ambiente
) {
    this->id = id;
    this->difuso = difuso;
    this->especular = especular;
    this->ambiente = ambiente;

    this->posicion(0) = posicion(0);
    this->posicion(1) = posicion(1);
    this->posicion(2) = posicion(2);
    this->posicion(3) = 1; // posicional
}

LuzDireccional::LuzDireccional (
    Tupla2f direccion,
    GLenum id,
    Tupla4f difuso,
    Tupla4f especular,
    Tupla4f ambiente
) {
    this->id = id;
    this->difuso = difuso;
    this->especular = especular;
    this->ambiente = ambiente;

    alpha = direccion(0);
    beta = direccion(1);

    convertirPosicion();
}

void LuzDireccional::convertirPosicion () {
    float a, b;
    float x, y, z;

    // convierte a radianes
    a = alpha * M_PI / 180.0;
    b = beta * M_PI / 180.0;

    // calcula vector
    x = sin(a)*cos(b);
    z = cos(a)*cos(b);
    y = sin(b);

    posicion = {x, y, z, 0};
}

void LuzDireccional::variarAnguloAlpha (float incremento) {
    alpha += incremento;
    convertirPosicion();
}

void LuzDireccional::variarAnguloBeta (float incremento) {
    beta += incremento;
    convertirPosicion();
}

Tupla2f LuzDireccional::getDireccion () {
    return Tupla2f(alpha, beta);
}

void LuzDireccional::printDireccion () {
    printf("(%f, %f)\n", alpha, beta);
}