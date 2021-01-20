#include "camara.h"

Camara::Camara (
    Tupla3f eye,
    Tupla3f at,
    Tupla3f up,
    int tipo,
    float near,
    float far
) {
    this->eye  = eye;
    this->at   = at;
    this->up   = up;
    this->tipo = tipo;
    this->near = near;
    this->far  = far;

    objeto = 0;
}

void Camara::setObserver () {
    gluLookAt(
        eye(0), eye(1), eye(2),
         at(0),  at(1),  at(2),
         up(0),  up(1),  up(2)
    );
}

void Camara::setProyeccion () {
    if (tipo & CAM_ORT) {
        // La cámara es ortogonal
        glOrtho (left, right, bottom , top, near, far);
    } else {
        // La cámara está en perspectiva
        glFrustum (left, right, bottom, top, near, far);
    }
}

void Camara::rotarXExaminar (float alpha) {
    // Vector que va de at a eye y vamos a rotar
    Tupla3f vector = eye - at;

    float mod = sqrt(vector.lengthSq());

    // Aplicamos la matriz de transformación para rotar
    vector(1) = vector(1)*cos(alpha) - vector(2)*sin(alpha);
    vector(2) = vector(1)*sin(alpha) + vector(2)*cos(alpha);

    // Recuperamos la longitud original del vector
    vector = vector.normalized() * mod;

    // Modificamos eye para que coincida
    eye = at + vector;
}

void Camara::rotarYExaminar (float alpha) {
    // Vector que va de at a eye y vamos a rotar
    Tupla3f vector = eye - at;

    float mod = sqrt(vector.lengthSq());

    // Aplicamos la matriz de transformación para rotar
    vector(0) =   vector(0)*cos(alpha) + vector(2)*sin(alpha);
    vector(2) = - vector(0)*sin(alpha) + vector(2)*cos(alpha);

    // Recuperamos la longitud original del vector
    vector = vector.normalized() * mod;

    // Modificamos eye para que coincida
    eye = at + vector;
}

void Camara::rotarZExaminar (float alpha) {
    // Vector que va de at a eye y vamos a rotar
    Tupla3f vector = eye - at;

    float mod = sqrt(vector.lengthSq());

    // Aplicamos la matriz de transformación para rotar
    vector(0) = vector(0)*cos(alpha) - vector(1)*sin(alpha);
    vector(1) = vector(0)*sin(alpha) + vector(1)*cos(alpha);

    // Recuperamos la longitud original del vector
    vector = vector.normalized() * mod;

    // Modificamos eye para que coincida
    eye = at + vector;
}

void Camara::rotarXFirstPerson (float alpha) {
    // Vector que va de eye a at y vamos a rotar
    Tupla3f vector = at - eye;

    float mod = sqrt(vector.lengthSq());

    // Aplicamos la matriz de transformación para rotar
    vector(1) = vector(1)*cos(alpha) - vector(2)*sin(alpha);
    vector(2) = vector(1)*sin(alpha) + vector(2)*cos(alpha);

    // Recuperamos la longitud original del vector
    vector = vector.normalized() * mod;

    // Modificamos at para que coincida
    at = eye + vector;
}

void Camara::rotarYFirstPerson (float alpha) {
    // Vector que va de eye a at y vamos a rotar
    Tupla3f vector = at - eye;

    float mod = sqrt(vector.lengthSq());

    // Aplicamos la matriz de transformación para rotar
    vector(0) =   vector(0)*cos(alpha) + vector(2)*sin(alpha);
    vector(2) = - vector(0)*sin(alpha) + vector(2)*cos(alpha);

    // Recuperamos la longitud original del vector
    vector = vector.normalized() * mod;

    // Modificamos at para que coincida
    at = eye + vector;
   
}

void Camara::rotarZFirstPerson (float alpha) {
    // Vector que va de eye a at y vamos a rotar
    Tupla3f vector = at - eye;

    float mod = sqrt(vector.lengthSq());

    // Aplicamos la matriz de transformación para rotar
    vector(0) = vector(0)*cos(alpha) - vector(1)*sin(alpha);
    vector(1) = vector(0)*sin(alpha) + vector(1)*cos(alpha);

    // Recuperamos la longitud original del vector
    vector = vector.normalized() * mod;

    // Modificamos at para que coincida
    at = eye + vector;
}

void Camara::girar (float x, float y) {

    rotarYFirstPerson(-x*M_PI/180.0);

    // calcular ángulo entre {0, 0, 1} y at-eye
    Tupla3f a = (at - eye); a(1) = 0;
    Tupla3f b(0, 0, 1);

    float cosalpha = (a.dot(b))/(sqrt(a.lengthSq())*sqrt(b.lengthSq()));
    float alpha = acos(cosalpha);

    // Rotar
    rotarXFirstPerson((y*M_PI/180.0)*cos(alpha));

    if (a(0) < 0) {
        rotarZFirstPerson((y*M_PI/180.0)*sin(alpha));
    } else {
        rotarZFirstPerson(-(y*M_PI/180.0)*sin(alpha));
    }
}

void Camara::girar3p (float x, float y) {

    rotarYExaminar(-x*M_PI/180.0);

    // calcular ángulo entre {0, 0, 1} y at-eye
    Tupla3f a = (at - eye); a(1) = 0;
    Tupla3f b(0, 0, 1);

    float cosalpha = (a.dot(b))/(sqrt(a.lengthSq())*sqrt(b.lengthSq()));
    float alpha = acos(cosalpha);

    // Rotar
    rotarXExaminar((y*M_PI/180.0)*cos(alpha));

    if (a(0) < 0) {
        rotarZExaminar((y*M_PI/180.0)*sin(alpha));
    } else {
        rotarZExaminar(-(y*M_PI/180.0)*sin(alpha));
    }
}

void Camara::redimensionar (float ratio) {
    left = bottom*ratio;
    right = top*ratio;
}

void Camara::setLeft (float n) {
    left = n;
}
void Camara::setRight (float n) {
    right = n;
}
void Camara::setBottom (float n) {
    bottom = n;
}
void Camara::setTop (float n) {
    top = n;
}

void Camara::zoom (float factor) {
    printf("%f\n", left);
    left   *= factor;
    right  *= factor;
    bottom *= factor;
    top    *= factor;
}

void Camara::setAt (float x, float y, float z) {
    at(0) = x;
    at(1) = y;
    at(2) = z;
}

void Camara::setObjeto (unsigned int obj) {
    objeto = obj;
}