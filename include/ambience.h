#ifndef AMBIENCE_H_INCLUDED
#define AMBIENCE_H_INCLUDED

#include "aux.h"
#include "luz.h"

class Ambience : public Luz {
private:
    int step;
    int speed;
public:
    Ambience (GLenum id);

    void animar ();
    inline void aumentarVelocidad() { speed++; };
    inline void disminuirVelocidad() { speed--; if (speed < 0) { speed = 0; }};
};

#endif