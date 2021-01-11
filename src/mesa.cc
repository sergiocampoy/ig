#include "mesa.h"

Mesa::Mesa (int n) {
    cil = new Cilindro(n/2, n, 2, 1);
    cub = new Cubo();
}

void Mesa::draw (unsigned int modo_vis, bool vbo, bool tapas) {
    glPushMatrix();
        // Superficie de la mesa
        glTranslatef(0, -1, 0);
        glScalef(40, 1, 20);
        // Cubo centrado 2x2x2
        glTranslatef(-1, -1, -1);
        glScalef(2, 2, 2);
        cub->draw(modo_vis, vbo);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(38, -21, 18);
        glScalef(1, 19, 1);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(38, -21, -18);
        glScalef(1, 19, 1);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-38, -21, 18);
        glScalef(1, 19, 1);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-38, -21, -18);
        glScalef(1, 19, 1);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();
}

void Mesa::colorea (Tupla3f c) {
    cil->colorea(c);
    cub->colorea(c);
}

void Mesa::setMaterial (Material m) {
    cil->setMaterial(m);
    cub->setMaterial(m);
}