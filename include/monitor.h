#ifndef MONITOR_H_INCLUDED
#define MONITOR_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "cuadro.h"

class Monitor {
private:
    ObjPLY* monitor = nullptr;
    Cuadro* pantalla = nullptr;

public:
    Monitor (const std::string& fichero);
    void draw (unsigned int modo_vis, bool vbo);
    
    void colorea (Tupla3f c);
    void setMaterial (Material a);

    Tupla4f emision;
};

#endif