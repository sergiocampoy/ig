#include "flexo.h"

Cabeza::Cabeza (int n) {
    c = new Cilindro(n/2, n, 2, 1);
    e = new Esfera(n, n, 1);
    l = new LuzPosicional (
        {0, 0, 0},
        GL_LIGHT2,
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 0, 1}
    );
}

void Cabeza::draw (unsigned int modo_vis, bool vbo, bool tapas) {
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        c->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.5, 1.5, 0);
        glPushMatrix();
            glTranslatef(0, -1, 0);
            l->aplicar();
        glPopMatrix();
        glScalef(5, 1, 2.5);
        glPushMatrix();
            glScalef(1, 0.5, 1);
            c->draw(modo_vis, vbo, tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0.5, 0);
            e->draw(modo_vis, vbo, tapas);
        glPopMatrix();
    glPopMatrix();
}

Brazo::Brazo (int n) {
    cil = new Cilindro (n/2, n, 2, 1);
    cab = new Cabeza (n);
}

void Brazo::draw (unsigned int modo_vis, bool vbo, bool tapas, float alpha) {
    glPushMatrix();
        glTranslatef(5, 0, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(0.5, 5, 0.25);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10, 0, 0);
        glRotatef(alpha, 0, 0, 1);
        cab->draw(modo_vis, vbo, tapas);
    glPopMatrix();
}

Cuerpo::Cuerpo (int n) {
    cil = new Cilindro (n/2, n, 2, 1);
    esf = new Esfera (n, n, 1);
    bra = new Brazo (n);
}

void Cuerpo::draw (unsigned int modo_vis, bool vbo, bool tapas, float alpha, float beta, float gamma) {
    glPushMatrix();
        glTranslatef(0, 5, 0);
        glScalef(1, 5, 1);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 10, 0);
        esf->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 10, 0);
        glRotatef(beta, 0, 0, 1);
        glTranslatef(gamma, 0, 0);
        bra->draw(modo_vis, vbo, tapas, alpha);
    glPopMatrix();
}

Flexo::Flexo (int n) {
    cil = new Cilindro (n/2, n, 2, 1);
    cue = new Cuerpo (n);

    /*
    giroCabeza = -15;
    giroBrazo = 15;
    altura = -3;
    velocidad = 1;
    */
    giroCabeza = 0;
    giroBrazo = 0;
    altura = 0;
}

void Flexo::draw (
    unsigned int modo_vis,
    bool vbo,
    bool tapas
) {
    glPushMatrix();
        glScalef(5, 0.5, 5);
        cil->draw(modo_vis, vbo, tapas);
    glPopMatrix();

    glPushMatrix();
        cue->draw(modo_vis, vbo, tapas, giroCabeza, giroBrazo, altura);
    glPopMatrix();
}

void Flexo::modificaAnguloCabeza (float n) {
    giroCabeza += n;
    if (giroCabeza > 90) { giroCabeza = 90; }
    if (giroCabeza < -90) { giroCabeza = -90; }
}

void Flexo::modificaAnguloBrazo (float n) {
    giroBrazo += n;
    if (giroBrazo > 180) { giroBrazo = 180; }
    if (giroBrazo < 0) { giroBrazo = 0; }
}

void Flexo::modificaAltura (float n) {
    altura += n;
    if (altura > 0) { altura = 0; }
    if (altura < -8) { altura = -8; }
}

void Flexo::animarModeloJerarquico () {
    if (giroCabeza < -90 || giroCabeza > 0) {
        sentidoCabeza *= -1;
    }
    giroCabeza += velocidadCabeza*sentidoCabeza;

    if (giroBrazo < 0 || giroBrazo > 90) {
        sentidoBrazo *= -1;
    }
    giroBrazo += velocidadBrazo*sentidoBrazo;

    if (altura < -8 || altura >= 0) {
        sentidoAltura *= -1;
    }
    altura += velocidadAltura*sentidoAltura*0.1;
}

void Flexo::modificarVelocidadCabeza (float n) {
    velocidadCabeza += n;
    if (velocidadCabeza > 5) { velocidadCabeza = 5; }
    if (velocidadCabeza < -5) { velocidadCabeza = -5; }
    printf("Velocidad Cabeza = %f\n", velocidadCabeza);
}

void Flexo::modificarVelocidadBrazo (float n) {
    velocidadBrazo += n;
    if (velocidadBrazo > 2.5) { velocidadBrazo = 2.5; }
    if (velocidadBrazo < -2.5) { velocidadBrazo = -2.5; }
    printf("Velocidad Brazo = %f\n", velocidadBrazo);
}

void Flexo::modificarVelocidadAltura (float n) {
    velocidadAltura += n;
    if (velocidadAltura > 2.5) { velocidadAltura = 2.5; }
    if (velocidadAltura < -2.5) { velocidadAltura = -2.5; }
    printf("Velocidad Altura = %f\n", velocidadAltura);
}

void Flexo::colorea (Tupla3f c) {
    cil->colorea(c);
    cue->colorea(c);
}

void Cuerpo::colorea (Tupla3f c) {
    cil->colorea(c);
    esf->colorea(c);
    bra->colorea(c);
}

void Brazo::colorea (Tupla3f c) {
    cil->colorea(c);
    cab->colorea(c);
}

void Cabeza::colorea (Tupla3f c) {
    this->c->colorea(c);
    e->colorea(c);
}

void Flexo::setMateriales (Material a, Material b) {
    cil->setMaterial(a);
    cue->setMateriales(a, b);
}

void Cuerpo::setMateriales (Material a, Material b) {
    cil->setMaterial(a);
    esf->setMaterial(a);
    bra->setMateriales(a, b);
}

void Brazo::setMateriales (Material a, Material b) {
    cil->setMaterial(b);
    cab->setMateriales(a, b);
}

void Cabeza::setMateriales (Material a, Material b) {
    c->setMaterial(a);
    e->setMaterial(a);
}