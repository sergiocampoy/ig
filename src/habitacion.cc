#include "habitacion.h"

Habitacion::Habitacion () {

    // inicializa la tabla de vértices
    v.emplace_back(0, 1, 0);
    v.emplace_back(1, 1, 0);

    v.emplace_back(0, 1, 0);
    v.emplace_back(0, 0, 0);
    v.emplace_back(1, 0, 0);
    v.emplace_back(1, 1, 0);
    v.emplace_back(0, 1, 0);

    v.emplace_back(0, 1, 1);
    v.emplace_back(0, 0, 1);
    v.emplace_back(1, 0, 1);
    v.emplace_back(1, 1, 1);
    v.emplace_back(0, 1, 1);

    v.emplace_back(0, 1, 1);
    v.emplace_back(1, 1, 1);

    // inicializa la tabla de caras
    f.emplace_back(0, 3, 4);
    f.emplace_back(0, 4, 1);

    f.emplace_back(2, 7, 8);
    f.emplace_back(2, 8, 3);
    f.emplace_back(3, 8, 9);
    f.emplace_back(3, 9, 4);

    f.emplace_back(4, 9, 10);
    f.emplace_back(4, 10, 5);
    f.emplace_back(5, 10, 11);
    f.emplace_back(5, 11, 6);

    f.emplace_back(8, 12, 13);
    f.emplace_back(8, 13, 9);

    // asigna las coordenadas de textura
    float t = 1.0/3;

    c_t.emplace_back(0.25f, 0);
    c_t.emplace_back(0.50f, 0);

    c_t.emplace_back(0.00f, t);
    c_t.emplace_back(0.25f, t);
    c_t.emplace_back(0.50f, t);
    c_t.emplace_back(0.75f, t);
    c_t.emplace_back(1.00f, t);

    c_t.emplace_back(0.00f, 2*t);
    c_t.emplace_back(0.25f, 2*t);
    c_t.emplace_back(0.50f, 2*t);
    c_t.emplace_back(0.75f, 2*t);
    c_t.emplace_back(1.00f, 2*t);

    c_t.emplace_back(0.25f, 1.00);
    c_t.emplace_back(0.50f, 1.00);

    //calcular_normales(); // nv

    nv.emplace_back(1, -1, 1);
    nv.emplace_back(-1, -1, 1);

    nv.emplace_back(1, -1, 1);
    nv.emplace_back(1, 1, 1);
    nv.emplace_back(-1, 1, 1);
    nv.emplace_back(-1, -1, 1);
    nv.emplace_back(1, -1, 1);

    nv.emplace_back(1, -1, -1);
    nv.emplace_back(1, 1, -1);
    nv.emplace_back(-1, 1, -1);
    nv.emplace_back(-1, -1, -1);
    nv.emplace_back(1, -1, -1);

    nv.emplace_back(1, -1, -1);
    nv.emplace_back(-1, -1, -1);

    for (unsigned int i = 0; i < nv.size(); i++) {
        nv[i] = nv[i].normalized();
    }
}