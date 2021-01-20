#include "monitor.h"

Monitor::Monitor (const std::string& fichero) {
    monitor = new ObjPLY("./plys/Monitor.ply");
    monitor->colorea({0, 0, 0});
    pantalla = new Cuadro();
    pantalla->colorea({0, 0, 0});
    pantalla->setTextura(fichero);
    emision = {1, 1, 1, 1};
}

void Monitor::draw (unsigned int modo_vis, bool vbo) {
    glPushMatrix();
        glTranslatef(0, 0.19259, 0);
        glRotatef(-90, 1, 0, 0);
        monitor->draw(modo_vis, vbo);

        glPushMatrix();
            glTranslatef(0, 0.2341, (2.3932+0.50784)/2);
            glScalef(2*1.867, 1, 2.3932-0.50784);
            glTranslatef(-0.5, 0, -0.5);
            glRotatef(90, 1, 0, 0);
            if (glIsEnabled(GL_LIGHTING)) {
                emision = {1, 1, 1, 1};
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
            }
            pantalla->draw(modo_vis, vbo);
            if (glIsEnabled(GL_LIGHTING)) {
                emision = {0, 0, 0, 1};
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
            }
        glPopMatrix();
    glPopMatrix();
}

void Monitor::colorea (Tupla3f c) {
    color = c;
    monitor->colorea(c);
    pantalla->colorea(c);
}

void Monitor::setMaterial (Material m) {
    monitor->setMaterial(m);
    pantalla->setMaterial(m);
}