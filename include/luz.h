#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz {
public:
    Tupla4f posicion;
    GLenum id;
    Tupla4f difuso;
    Tupla4f especular;
    Tupla4f ambiente;

public:
    void aplicar ();
};

class LuzPosicional : public Luz {
public:
    LuzPosicional (
        Tupla3f posicion,
        GLenum id,
        Tupla4f difuso,
        Tupla4f especular,
        Tupla4f ambiente
    );
};

class LuzDireccional : public Luz {
protected:
    float alpha;
    float beta;

    void convertirPosicion();

public:
    LuzDireccional (
        Tupla2f direccion,
        GLenum id,
        Tupla4f difuso,
        Tupla4f especular,
        Tupla4f ambiente
    );

    void variarAnguloAlpha (float incremento);
    void variarAnguloBeta (float incremento);
    Tupla2f getDireccion ();
    void printDireccion ();
};

#endif