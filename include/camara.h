#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"
#include "misc.h"

class Camara {
private:
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    int tipo; // ortogonal o perspectiva
    float left, right, bottom, top, near, far;

    unsigned int objeto;

public:
    Camara(
        Tupla3f eye,
        Tupla3f at,
        Tupla3f up,
        int tipo,
        float near,
        float far
    );

    void rotarXExaminar (float alpha);
    void rotarYExaminar (float alpha);
    void rotarZExaminar (float alpha);

    void rotarXFirstPerson (float alpha);
    void rotarYFirstPerson (float alpha);
    void rotarZFirstPerson (float alpha);

    void mover (float x, float y, float z);
    void zoom (float factor);

    void setObserver(); // algo de gluLookAt
    void setProyeccion();

    void girar (float x, float y);
    void girar3p (float x, float y);

    void redimensionar (float ratio);

    void setLeft (float n);
    void setRight (float n);
    void setBottom (float n);
    void setTop (float n);

    void setAt (float x, float y, float z);
    void setObjeto (unsigned int obj);
    unsigned int getObjeto () { return objeto; }
    unsigned int getTipo () { return tipo; }
};

#endif