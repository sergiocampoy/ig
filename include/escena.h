#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"

#include "flexo.h"
#include "habitacion.h"
#include "mesa.h"
#include "monitor.h"

#include "luz.h"
#include "ambience.h"

#include "cuadro.h"

#include "camara.h"

#include "misc.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, ANIMACION, AMANUAL, LUCES, CAMARAS} menu;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection(/* const float ratio_xy */);
	void change_observer();



   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * ply = nullptr;
   ObjRevolucion* rev = nullptr;

   ObjRevolucion* cono = nullptr;
   ObjRevolucion* esfera = nullptr;
   ObjRevolucion* cilindro = nullptr;

   Cuadro* cuadro = nullptr;

   Flexo* flexo = nullptr;
   Habitacion* habitacion = nullptr;
   Mesa* mesa = nullptr;
   Monitor* monitor = nullptr;
   ObjRevolucion* lata = nullptr;
   ObjRevolucion* peon1 = nullptr;
   ObjRevolucion* peon2 = nullptr;

   Luz* lp = nullptr;
   LuzDireccional* ld = nullptr;
   // LuzPosicional* ambiente = nullptr;
   Ambience* ambiente = nullptr;
   bool modificarAlpha = true;
   bool modificarGamer = false;

   // menú
   void help(menu modoMenu);
   void info(unsigned int obj, unsigned int vis, bool vbo);
   unsigned int obj = OBJ_ALL; // default = visualiza todos los objs
   unsigned int vis = VIS_SOL + VIS_TEX; // default = visualiza en modo sólido
   bool vbo = true;            // default = dibuja en VBO
   bool light_mode = false;
   unsigned int grd_libertad = 0b111;

   bool animacion_automatica = false;
   unsigned int camara = CAM_DEF;

   std::vector<Camara> camaras;
   unsigned int camaraActiva = 0;

   float xant = 0, yant = 0;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
    void dibujarObjetos();
    void dibujaSeleccion ();
    void pick (int x, int y);

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    void animarModeloJerarquico();
    void animarLuz();

    void clickRaton (int boton, int estado, int x, int y);
    void ratonMovido (int x, int y);

};
#endif
