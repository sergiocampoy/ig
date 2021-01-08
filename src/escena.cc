

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....


//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 40.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 4000 );

   cubo = new Cubo(40, Tupla3f(0, 0, 0));
   tetraedro = new Tetraedro(40);
   ply = new ObjPLY("./plys/ori.ply");

   rev = new ObjRevolucion("./plys/peon.ply", 16, 1, true, true);
   cono = new Cono(4, 16, 1, 1);
   cilindro = new Cilindro(4, 16, 1, 1);
   esfera = new Esfera(16, 16, 1);

   cuadro = new Cuadro();
   cuadro->setTextura("minihabitacion");

   cilindro->setTextura("lata1");

   flexo = new Flexo(16);
   habitacion = new Habitacion();
   habitacion->setTextura("minihabitacion");

   mesa = new Mesa (16);
   monitor = new Monitor("rick");

   lata = new Cilindro(4, 16, 3, 1);
   lata->colorea({1, 1, 1});
   lata->setTextura("lata1");

   peon1 = new ObjRevolucion("./plys/peon.ply", 16, 1, true, true);
   peon1->colorea({1, 1, 0});
   peon2 = new ObjRevolucion("./plys/peon.ply", 16, 1, true, true);
   peon2->colorea({0, 1, 1});
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	//glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
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
int sergio = 0;
void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();

   glPushMatrix();
      glScalef(500, 500, 500);
      glRotatef(-90, 0, 1, 0);
      glTranslatef(-0.5, -0.5, -0.5);
      habitacion->draw(vis, vbo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0, -90, -170);
      glScalef(4, 4, 4);
      mesa->draw (vis, vbo, true);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(120, -90, -200);
      glScalef(5, 5, 5);
      glRotatef(-135, 0, 1, 0);
      flexo->draw(vis, vbo, true);
   glPopMatrix();
   
   glPushMatrix();
      //glTranslatef(120, -90, -200);
      glScalef(5, 5, 5);
      glRotatef(-135, 0, 1, 0);
      flexo->draw(vis, vbo, true);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0, -90, -200);
      glScalef(40, 40, 40);
      monitor->draw(vis, vbo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-120, -90, -210);
      glScalef(10, 10, 10);
      glTranslatef(0, 1.5, 0);
      lata->draw(vis, vbo, true);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-25, -90, -140);
      glScalef(20, 20, 20);
      glTranslatef(0, 1.4, 0);
      peon1->draw(vis, vbo, true);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(25, -90, -140);
      glScalef(20, 20, 20);
      glTranslatef(0, 1.4, 0);
      peon2->draw(vis, vbo, true);
   glPopMatrix();

    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
   
   /*
   glPushMatrix();
   glTranslatef(-150, -150, -50);
   glScalef(300, 300, 0);
   if (obj & OBJ_CUB)
      cuadro->draw(vis, vbo);
   glPopMatrix();
   */
   /*
   
   glPushMatrix();
   glTranslatef(0, -25, 0);
   glScalef(25, 50, 25);
   if (obj & OBJ_REV)
      cilindro->draw(vis, vbo, true);
   glPopMatrix();
*/
   /*
   glPushMatrix();
   glTranslatef(100, 0, 0);
   if (obj & OBJ_CUB)
      cubo->draw(vis, vbo);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-100, 0, 0);
   if (obj & OBJ_TET)
      tetraedro->draw(vis, vbo);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0, 0, -100);
   glRotatef(-90, 1, 0, 0);
   glScalef(10, 10, 10);
   if (obj & OBJ_PLY)
      ply->draw(vis, vbo);
   glPopMatrix();

   // Objetos de revolución
   glPushMatrix();
   glTranslatef(0, 0, 40);
   glScalef(20, 20, 20);
   if (obj & OBJ_REV)
      rev->draw(vis, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef(0, 0, -40);
   glScalef(20, 20, 20);
   if (obj & OBJ_REV)
      cono->draw(vis, vbo, obj & OBJ_TAP);
   glPopMatrix();
   */
  /*
   glPushMatrix();
   glTranslatef(50, 0, 0);
   glScalef(20, 20, 20);
   if (obj & OBJ_REV)
      cono->draw(vis, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef(-50, 0, 0);
   glScalef(20, 20, 20);
   if (obj & OBJ_REV)
      esfera->draw(vis, vbo, obj & OBJ_TAP);
   glPopMatrix();
*/
   
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
   switch(toupper(tecla))
   {
      case 'A':
         if (modoMenu == SELVISUALIZACION) {
            // Activa/desactiva modo ajedrez
            vis ^= VIS_AJE;
            if (vis & VIS_AJE) {
               cout << "Modo ajedrez " << FGRN("activado") << endl;
            } else {
               cout << "Modo ajedrez " << FRED("desactivado") << endl;
            }
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva todos los objetos
            if (obj != OBJ_ALL) {
               obj = OBJ_ALL;
               cout << "Todos los objetos " << FGRN("activados") << endl;
            } else {
               obj = 0;
               cout << "Todos los objetos " << FRED("desactivados") << endl;
            }
         } else if (modoMenu == NADA) {
            // Menú de animación
            modoMenu = ANIMACION;
            if (animacion_automatica) {
               animacion_automatica = false;
               cout << "Animacion automática " << FRED("desactivada") << endl;
            } else {
               animacion_automatica = true;
               cout << "Animación automática " << FGRN("activada") << endl;
            }
            help(modoMenu);
         } else if (modoMenu == ANIMACION) {
            if (animacion_automatica) {
               animacion_automatica = false;
               cout << "Animacion automática " << FRED("desactivada") << endl;
            } else {
               animacion_automatica = true;
               cout << "Animación automática " << FGRN("activada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'C':
         if (modoMenu == SELOBJETO) {
            // Activar/desactivar cubo
            obj ^= OBJ_CUB;
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
      case 'D':
         // Seleccionar dibujado
         modoMenu = SELDIBUJADO;
         help(modoMenu);
      break;
      case 'H':
         // Ayuda
         help(modoMenu);
      break;
      case 'I':
         // Información
         info(obj, vis, vbo);
      break;
      case 'L':
         if (modoMenu == SELVISUALIZACION) {
            // Activa/desactiva modo líneas
            vis ^= VIS_LIN;
            if (vis & VIS_LIN) {
               cout << "Modo lineas " << FGRN("activado") << endl;
            } else {
               cout << "Modo lineas " << FRED("desactivado") << endl;
            }
         } else if (modoMenu == NADA) {
            light_mode = !light_mode;
            if (light_mode)
            {
               glClearColor( 1.0, 1.0, 1.0, 1.0 );
               cout << "Modo oscuro " << FRED("desactivado") << endl;
            } else {
               glClearColor( 40.0/255, 42.0/255, 54.0/255, 1.0); // #DarkModeEverything
               cout << "Modo oscuro " << FGRN("activado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'N':
         if (modoMenu == SELTAPAS) {
            // Desactiva las tapas del objeto de revolución
            obj &= ~OBJ_TAP;
            cout << "Tapas " << FRED("desactivadas") << endl;
            modoMenu = SELOBJETO;
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'M':
         if (modoMenu == NADA) {
            // Menú de animación manual
            modoMenu = AMANUAL;
            animacion_automatica = false;
            help(modoMenu);
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'O':
         // Seleccionar objeto
         modoMenu = SELOBJETO;
         help(modoMenu);
      break;
      case 'P':
         if (modoMenu == SELVISUALIZACION) {
            // Activa/desactiva modo ajedrez
            vis ^= VIS_PUN;
            if (vis & VIS_PUN) {
               cout << "Modo puntos " << FGRN("activado") << endl;
            } else {
               cout << "Modo puntos " << FRED("desactivado") << endl;
            }
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva PLY
            obj ^= OBJ_PLY;
            if (obj & OBJ_PLY) {
               cout << "Objeto PLY " << FGRN("activado") << endl;
            } else {
               cout << "Objeto PLY " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'Q':
         if (modoMenu != NADA) {
            // Salir al menú principal
            modoMenu = NADA;
            help(modoMenu);
         } else {
            // Salir del programa
            salir = true;
         }
      break;
      case 'R':
         if (modoMenu == SELOBJETO) {
            // Activa/desactiva objeto de revolución
            obj ^= OBJ_REV;
            if (obj & OBJ_REV) {
               cout << "Objeto de revolución " << FGRN("activado") << endl;
               cout << "Quieres tapas? ("
                    << FGRN("y") << "/" << FRED("n") << ")" << endl;
               modoMenu = SELTAPAS;
            } else {
               cout << "Objeto de revolución " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'S':
         if (modoMenu == SELVISUALIZACION) {
            // Activa/desactiva modo sólido
            vis ^= VIS_SOL;
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
      case 'T':
         if (modoMenu == SELOBJETO) {
            // Activa/desactiva tetraedro
            obj ^= OBJ_TET;
            if (obj & OBJ_TET) {
               cout << "Tetraedro " << FGRN("activado") << endl;
            } else {
               cout << "Tetraedro " << FRED("desactivado") << endl;
            }
         } else if (modoMenu == SELVISUALIZACION) {
            // Activa/desactiva modo sólido
            vis ^= VIS_TEX;
            if (vis & VIS_TEX) {
               cout << "Texturas " << FGRN("activadas") << endl;
            } else {
               cout << "Texturas " << FRED("desactivadas") << endl;
            }
         }{
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'V':
         // Seleccionar modo de visualización
         modoMenu = SELVISUALIZACION;
         help(modoMenu);
      break;
      case 'Y':
         if (modoMenu == SELTAPAS) {
            // Activa/desactiva tapas del objeto de revolución
            obj |= OBJ_TAP;
            cout << "Tapas " << FGRN("activadas") << endl;
            modoMenu = SELOBJETO;
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '0':
         if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b111; // Selecciona todos los grados de libertad
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '1' :
         if (modoMenu == SELDIBUJADO) {
            vbo = false;
            cout << "Modo inmediato " << FGRN("activado") << endl;
            cout << "Modo diferido " << FRED("desactivado") << endl;
            cout << endl;
         } else if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b1; // Cabeza
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
         } else if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b10; // Brazo
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '3':
         if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b100; // Altura
         }
      break;
      case '+':
         if (modoMenu == ANIMACION) {
            if (grd_libertad & 0b001) {
               flexo->modificarVelocidadCabeza(0.5);
            }
            if (grd_libertad & 0b010) {
               flexo->modificarVelocidadBrazo(0.5);
            }
            if (grd_libertad & 0b100) {
               flexo->modificarVelocidadAltura(0.5);
            }
         } else if (modoMenu == AMANUAL) {
            if (grd_libertad & 0b001) {
               flexo->modificaAnguloCabeza(180.0/20);
            }
            if (grd_libertad & 0b010) {
               flexo->modificaAnguloBrazo(180.0/20);
            }
            if (grd_libertad & 0b100) {
               flexo->modificaAltura(8.0/20);
            }
         }
      break;
      case '-':
         if (modoMenu == ANIMACION) {
            if (grd_libertad & 0b001) {
               flexo->modificarVelocidadCabeza(-0.5);
            }
            if (grd_libertad & 0b010) {
               flexo->modificarVelocidadBrazo(-0.5);
            }
            if (grd_libertad & 0b100) {
               flexo->modificarVelocidadAltura(-0.5);
            }
         } else if (modoMenu == AMANUAL) {
            if (grd_libertad & 0b001) {
               flexo->modificaAnguloCabeza(-180.0/20);
            }
            if (grd_libertad & 0b010) {
               flexo->modificaAnguloBrazo(-180.0/20);
            }
            if (grd_libertad & 0b100) {
               flexo->modificaAltura(-8.0/20);
            }
         }
      break;
      default:
         cout << FRED("Opción inválida") << endl;
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
            ". - Muestra este menú\n"
            "I - Información de la escena\n"
            "L - Activar/Desactivar modo oscuro\n"
            "Q - Salir\n"
            "O - Selección de objeto\n"
            "V - Selección de modo de visualización\n"
            "D - Selección de modo de dibujado\n"
         );
      break;
      case SELOBJETO:
         printf(
            BOLD(FBLU("Selección de objeto\n"))
            ". - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "A - Activar/desactivar todos los objetos\n"
            "C - Activar/desactivar cubo\n"
            "T - Activar/desactivar tetraedro\n"
            "P - Activar/desactivar objeto ply\n"
            "R - Activar/desactivar objeto revolución\n"
         );
      break;
      case SELVISUALIZACION:
         printf(
            BOLD(FBLU("Selección de modo de visualización\n"))
            ". - Muestra este menú\n"
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
            ". - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "1 - Visualizar mediante glDrawElements\n"
            "2 - Visualizar mediante VBOs\n"
         );
      break;
      case ANIMACION:
         printf(
            BOLD(FBLU("Opciones de animación automática\n"))
            ". - Muestra este menú\n"
            "Q - Volver al menú principal\n"
            "A - Activar/Desactivar animación automática\n"
            "0 - Modificar todos los grados de libertad\n"
            "1 - Modificar la cabeza\n"
            "2 - Modificar el brazo\n"
            "3 - Modificar el tronco\n"
            "+ - Aumentar la velocidad\n"
            "- - Disminuir la velocidad\n"
         );
      break;
      case AMANUAL:
         printf(
            BOLD(FBLU("Opciones de animación manual\n"))
            ". - Muestra este menú\n"
            "Q - Volver al menú principal\n"
            "0 - Modificar todos los grados de libertad\n"
            "1 - Modificar la cabeza\n"
            "2 - Modificar el brazo\n"
            "3 - Modificar el tronco\n"
            "+ - Aumentar el valor\n"
            "- - Disminuir el valor\n"
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

     << "\tCubo:           "
     << ((obj & OBJ_CUB) ? FGRN("si") : FRED("no"))
     << endl

     << "\tTetraedro:      "
     << ((obj & OBJ_TET) ? FGRN("si") : FRED("no"))
     << endl

     << "\tObjeto PLY:     "
     << ((obj & OBJ_PLY) ? FGRN("si") : FRED("no"))
     << endl

     << "\tObjeto de rev:  "
     << ((obj & OBJ_REV) ? FGRN("si") : FRED("no"))
     << " (tapas: "
     << ((obj & OBJ_TAP) ? FGRN("si") : FRED("no"))
     << ")" << endl


     << endl << FBLU("Modo de visualización") << endl

     << "\tModo puntos:    "
     << ((vis & VIS_PUN) ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo líneas:    "
     << ((vis & VIS_LIN) ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo sólido:    "
     << ((vis & VIS_SOL) ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo ajedrez:   "
     << ((vis & VIS_AJE) ? FGRN("si") : FRED("no"))
     << endl


     << endl << FBLU("Modo de dibujado") << endl

     << "\tModo inmediato: "
     << (!vbo ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo diferido:  "
     << (vbo ? FGRN("si") : FRED("no"))
     << endl

     << endl;
}


void Escena::animarModeloJerarquico() {
   if (animacion_automatica)
      flexo->animarModeloJerarquico();
}
    