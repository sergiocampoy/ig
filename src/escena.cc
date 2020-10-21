

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....


//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

   cubo = new Cubo(50, Tupla3f(0, 0, 0));
   tetraedro = new Tetraedro(50);
    // crear los objetos de la escena....
    // .......completar: ...
    // .....

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	//glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
   // #f8f8f2
   glClearColor( 40.0/255, 42.0/255, 54.0/255, 1.0); // #DarkModeEverything

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable(GL_CULL_FACE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 

   if (obj & OBJ_CUB)
      cubo->draw(vis, vbo);

   if (obj & OBJ_TET)
      tetraedro->draw(vis, vbo);

   
    // o
    // tetraedro.draw()
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA) {
            modoMenu=NADA;
            help(modoMenu);
         }
         else {
            salir=true ;
         }
      break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         help(modoMenu);
      break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         help(modoMenu);
      break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         help(modoMenu);
      break ;
      
      // OPCIONES DE SELECCIÓN DE OBJETO
      case 'C' :
         if (modoMenu == SELOBJETO) {
            obj ^= OBJ_CUB; // Alterna visibilidad
            if (obj & OBJ_CUB) {
               cout << "Cubo " << FGRN("activado") << endl;
            } else {
               cout << "Cubo " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'T' :
         if (modoMenu == SELOBJETO) {
            obj ^= OBJ_TET; // Alterna visibilidad
            if (obj & OBJ_TET) {
               cout << "Tetraedro " << FGRN("activado") << endl;
            } else {
               cout << "Tetraedro " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;

      // OPCIONES DE SELECCIÓN DE MODO DE VISUALIZACIÓN
      case 'P' :
         if (modoMenu == SELVISUALIZACION) {
            vis ^= VIS_PUN; // Alterna estado
            if (vis & VIS_PUN) {
               cout << "Modo puntos " << FGRN("activado") << endl;
            } else {
               cout << "Modo puntos " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'L' :
         if (modoMenu == SELVISUALIZACION) {
            vis ^= VIS_LIN; // Alterna estado
            if (vis & VIS_LIN) {
               cout << "Modo lineas " << FGRN("activado") << endl;
            } else {
               cout << "Modo lineas " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'S' :
         if (modoMenu == SELVISUALIZACION) {
            vis ^= VIS_SOL; // Alterna estado
            if (vis & VIS_SOL) {
               cout << "Modo sólido " << FGRN("activado") << endl;
            } else {
               cout << "Modo sólido " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'A' :
         if (modoMenu == SELVISUALIZACION) {
            vis ^= VIS_AJE; // Alterna estado
            if (vis & VIS_AJE) {
               cout << "Modo ajedrez " << FGRN("activado") << endl;
            } else {
               cout << "Modo ajedrez " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;

      // OPCIONES DE SELECCIÓN DE MODO DE DIBUJADO
      case '1' :
         if (modoMenu == SELDIBUJADO) {
            vbo = false;
            cout << "Modo inmediato " << FGRN("activado") << endl;
            cout << "Modo diferido " << FRED("desactivado") << endl;
            cout << endl;
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '2' :
         if (modoMenu == SELDIBUJADO) {
            vbo = true;
            cout << "Modo diferido " << FRED("activado") << endl;
            cout << "Modo inmediato " << FGRN("desactivado") << endl;
            cout << endl;
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'H' :
         // AYUDA
         help(modoMenu);
      break;
      case 'I' :
         // INFO
         info(obj, vis, vbo);
      break;
      default:
         cout << FRED("Opción inválida.") << endl;
         help(modoMenu);
      break;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}


// Función de ayuda

void Escena::help(menu modoMenu)
{
   switch (modoMenu)
   {
      case NADA:
         printf(
            BOLD(FBLU("Menú principal:\n"))
            "H - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Salir\n"
            "O - Selección de objeto\n"
            "V - Selección de modo de visualización\n"
            "D - Selección de modo de dibujado\n"
         );
      break;
      case SELOBJETO:
         printf(
            BOLD(FBLU("Selección de objeto\n"))
            "H - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "C - Activar/desactivar cubo\n"
            "T - Activar/desactivar tetraedro\n"
         );
      break;
      case SELVISUALIZACION:
         printf(
            BOLD(FBLU("Selección de modo de visualización\n"))
            "H - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "P - Activar/desactivar modo puntos\n"
            "L - Activar/desactivar modo línea\n"
            "S - Activar/desactivar modo sólido (default)\n"
            "A - Activar/desactivar modo ajedrez\n"
         );
      break;
      case SELDIBUJADO:
         printf(
            BOLD(FBLU("Selección de modo de dibujado\n"))
            "H - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "1 - Visualizar mediante glDrawElements\n"
            "2 - Visualizar mediante VBOs\n"
         );
      break;
   }
   printf("\n");
}

void Escena::info(unsigned int obj, unsigned int vis, bool vbo)
{
   using namespace std;

   cout
     << BOLD(FBLU("Información de la escena.")) << endl
     << FBLU("Objetos") << endl

     << "\tCubo:\t\t"
     << ((obj & OBJ_CUB) ? FGRN("si") : FRED("no"))
     << endl

     << "\tTetraedro:\t"
     << ((obj & OBJ_TET) ? FGRN("si") : FRED("no"))
     << endl


     << endl << FBLU("Modo de visualización") << endl

     << "\tModo puntos:\t"
     << ((vis & VIS_PUN) ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo líneas:\t"
     << ((vis & VIS_LIN) ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo sólido:\t"
     << ((vis & VIS_SOL) ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo ajedrez:\t"
     << ((vis & VIS_AJE) ? FGRN("si") : FRED("no"))
     << endl


     << endl << FBLU("Modo de dibujado") << endl

     << "\tModo inmediato:\t"
     << (!vbo ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo diferido:\t"
     << (vbo ? FGRN("si") : FRED("no"))
     << endl

     << endl;
}
