#include "monitor.h"

Monitor::Monitor (const std::string& fichero) {
    monitor = new ObjPLY("./plys/Monitor.ply");
    monitor->colorea({0, 0, 0});
    pantalla = new Cuadro();
    pantalla->setTextura(fichero);
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
            pantalla->draw(modo_vis, vbo);
        glPopMatrix();
    glPopMatrix();
}