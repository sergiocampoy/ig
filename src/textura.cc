#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura (std::string archivo) {
    // Genera el id de textura
    glGenTextures (1, &textura_id);

    // Declara un puntero a imagen (pimg)
    jpg::Imagen* pimg = NULL;

    // Carga la imagen
    pimg = new jpg::Imagen("./texturas/" + archivo + ".jpg");

    // almacena la imagen
    width = pimg->tamX();
    height = pimg->tamY();
    texels = pimg->leerPixels();

}

void Textura::activar () {
    glBindTexture (GL_TEXTURE_2D, textura_id);
    gluBuild2DMipmaps (
        GL_TEXTURE_2D,
        GL_RGB,
        width,
        height,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        texels
    );
}