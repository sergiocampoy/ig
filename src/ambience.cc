#include "ambience.h"

Ambience::Ambience (GLenum id) {
    this->id = id;
    this->difuso = {0, 0, 0, 0};
    this->especular = {0, 0, 0, 0};
    this->ambiente = {1, 1, 1, 1};

    step = -1;
    speed = 0;
}

void Ambience::animar () {
    if (speed != 0) {
        if (0 <= step && step < 100) {
            // Blanco a Rojo
            ambiente(0) = ambiente(0);
            ambiente(1) = ambiente(1) - 0.01;
            ambiente(2) = ambiente(2) - 0.01;
            ambiente(3) = ambiente(3);
        }

        if (100 <= step && step < 200) {
            // Rojo a Verde
            ambiente(0) = ambiente(0) - 0.01;
            ambiente(1) = ambiente(1) + 0.01;
            ambiente(2) = ambiente(2);
            ambiente(3) = ambiente(3);
        }

        if (200 <= step && step < 300) {
            // Verde a Azul
            ambiente(0) = ambiente(0);
            ambiente(1) = ambiente(1) - 0.01;
            ambiente(2) = ambiente(2) + 0.01;
            ambiente(3) = ambiente(3);
        }

        if (300 <= step && step < 400) {
            // Azul a Blanco
            ambiente(0) = ambiente(0) + 0.01;
            ambiente(1) = ambiente(1) + 0.01;
            ambiente(2) = ambiente(2);
            ambiente(3) = ambiente(3);
        }

        step += speed;
        step = (step + speed)%400;
    }
}