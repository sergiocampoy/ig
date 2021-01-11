#ifndef MESA_H_INCLUDED
#define MESA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "cubo.h"

class Mesa {
private:
    Cilindro* cil = nullptr;
    Cubo*     cub = nullptr;
public:
    Mesa (int n);
    void draw (unsigned int modo_vis, bool vbo, bool tapas);
    void colorea (Tupla3f c);
    void setMaterial (Material m);
};

#endif