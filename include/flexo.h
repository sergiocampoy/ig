#ifndef FLEXO_H_INCLUDED
#define FLEXO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cabeza {
private:
    Cilindro* c = nullptr;
    Esfera*   e = nullptr;
public:
    Cabeza (int ns);
    void draw (unsigned int modo_vis, bool vbo, bool tapas);
};

class Brazo {
private:
    Cilindro* cil = nullptr;
    Cabeza*   cab = nullptr;
public:
    Brazo (int n);
    void draw (unsigned int modo_vis, bool vbo, bool tapas, float alpha);
};

class Cuerpo {
private:
    Cilindro* cil = nullptr;
    Esfera*   esf = nullptr;
    Brazo*    bra = nullptr;
public:
    Cuerpo (int n);
    void draw (unsigned int modo_vis, bool vbo, bool tapas, float alpha, float beta, float gamma);
};

class Flexo {
private:
    Cilindro* cil = nullptr;
    Cuerpo*   cue = nullptr;
    float giroCabeza;
    float giroBrazo;
    float altura;

    float velocidad = 1;

    float velocidadCabeza = 1;
    float velocidadBrazo = 1;
    float velocidadAltura = 1;

    float sentidoCabeza = 1;
    float sentidoBrazo = 1;
    float sentidoAltura = 1;

public:
    Flexo (int n);
    void draw (unsigned int modo_vis, bool vbo, bool tapas);
    
    void modificaAnguloCabeza (float n);
    void modificaAnguloBrazo  (float n);
    void modificaAltura       (float n);

    void animarModeloJerarquico ();

    void modificarVelocidadCabeza (float n);
    void modificarVelocidadBrazo (float n);
    void modificarVelocidadAltura (float n);
    
};

#endif