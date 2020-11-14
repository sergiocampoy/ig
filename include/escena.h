#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "luz.h"

#include "menu.h"

typedef enum {
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELTAPAS,
    SELILUMINACION
} menu;

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
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * ply = nullptr;
   ObjRevolucion* rev = nullptr;
   ObjRevolucion* peon1 = nullptr;
   ObjRevolucion* peon2 = nullptr;

   // Luces

   /// Luz posicional
   LuzPosicional* lp = nullptr;
   /// Luz direccional
   LuzDireccional* ld = nullptr;


   // menú
   void help(menu modoMenu);
   void info(menu modoMenu, unsigned int obj, unsigned int vis, bool vbo);
   void infoObjetos(unsigned int obj);
   void infoVisualizacion(unsigned int vis);
   void infoDibujado(bool vbo);
   void infoIluminacion();
   unsigned int obj = OBJ_ALL; // default = visualiza todos los objs
   unsigned int vis = VIS_SOL; // default = visualiza en modo sólido
   bool vbo = true;            // default = dibuja en VBO
   bool light_mode = false;
   
   // P3

   /// true : incrementa alpha, false : incrementa beta
   bool inc_alpha = true;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
