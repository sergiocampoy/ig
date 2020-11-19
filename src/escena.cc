

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
   ply = new ObjPLY("./plys/ori.ply");

   // Objetos de revolución
   rev = new ObjRevolucion("./plys/peon.ply", 16, 1, true, true);
   //rev = new Cono(16, 16, 1, 1);
   //rev = new Cilindro(4, 16, 1, 1);
   //rev = new Esfera(16, 16, 1);

   peon1 = new ObjRevolucion("./plys/peon.ply", 16, 1, true, true);
   peon2 = new ObjRevolucion("./plys/peon.ply", 16, 1, true, true);

   // Materiales de los peones
   peon1->setMaterial (
      Material (
         {1, 1, 1, 1},
         {0, 0, 0, 1},
         {0, 0, 0, 1},
         128
      )
   );
   peon2->setMaterial (
      Material (
         {0, 0, 0, 1},
         {1, 1, 1, 1},
         {0, 0, 0, 1},
         128
      )
   );

   // Iluminación
   lp = new LuzPosicional (
      {0, 0, 20},
      GL_LIGHT0,
      {1, 0, 0, 1},
      {1, 0, 0, 1},
      {1, 0, 0, 1}
   );
   ld = new LuzDireccional (
      {0, 0},
      GL_LIGHT1,
      {0, 1, 0, 1},
      {0, 1, 0, 1},
      {0, 1, 0, 1}
   );

   // Materiales
   Material m(
      Tupla4f(1.0, 1.0, 1.0, 1.0),
      Tupla4f(1.0, 1.0, 1.0, 1.0),
      Tupla4f(1.0, 1.0, 1.0, 1.0),
      0
   );

   rev->setMaterial(m);
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
   glEnable(GL_NORMALIZE);

   glEnable(GL_RESCALE_NORMAL);
   glShadeModel(GL_FLAT); // Smooth lighting = off

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

   glPushMatrix();
      glTranslatef(0, 0, 0);
      lp->activar();
   glPopMatrix();

   glPushMatrix();
      glRotatef(ld->alpha, 1, 0, 0);
      glRotatef(ld->beta, 0, 1, 0);
      ld->activar();
   glPopMatrix();

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

   glPushMatrix();
   glTranslatef(20, 0, 0);
   glScalef(20, 20, 20);
   if (obj & OBJ_REV)
      peon1->draw(vis, vbo, obj & OBJ_TAP);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-20, 0, 0);
   glScalef(20, 20, 20);
   if (obj & OBJ_REV)
      peon2->draw(vis, vbo, obj & OBJ_TAP);
   glPopMatrix();

   // GLfloat a = 128;
   // glMaterialfv(GL_FRONT, GL_SPECULAR, Tupla4f(1, 1, 1, 1));
   // glMaterialf(GL_FRONT, GL_SHININESS, a);
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
            // P3 - Desactiva iluminación
            glDisable(GL_LIGHTING);
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva todos los objetos
            if (obj != OBJ_ALL) {
               obj = OBJ_ALL;
               cout << "Todos los objetos " << FGRN("activados") << endl;
            } else {
               obj = 0;
               cout << "Todos los objetos " << FRED("desactivados") << endl;
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
         if (modoMenu == NADA) {
            // Seleccionar opciones iluminación
            modoMenu = SELILUMINACION;
            glEnable(GL_LIGHTING);
            cout << "Iluminación " << FGRN("activada") << endl;
            help(modoMenu);
         } else if (modoMenu == SELILUMINACION) {
            if (glIsEnabled(GL_LIGHTING)) {
               glDisable(GL_LIGHTING);
               cout << "Iluminación " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHTING);
               cout << "Iluminación " << FGRN("activada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
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
            // P3 - Desactiva iluminación
            glDisable(GL_LIGHTING);
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
            // P3 - Desactiva iluminación
            glDisable(GL_LIGHTING);
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
            // P3 - Desactiva iluminación
            glDisable(GL_LIGHTING);
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
         } else {
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
      case '1' :
         if (modoMenu == SELDIBUJADO) {
            vbo = false;
            cout << "Modo inmediato " << FGRN("activado") << endl;
            cout << "Modo diferido " << FRED("desactivado") << endl;
            cout << endl;
         } else if (modoMenu == SELILUMINACION) {
            if (glIsEnabled(GL_LIGHT0)) {
               glDisable(GL_LIGHT0);
               cout << "Luz 0 " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHT0);
               cout << "Luz 0 " << FGRN("activada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '2' :
         if (modoMenu == SELDIBUJADO) {
            vbo = true;
            cout << "Modo diferido " << FGRN("activado") << endl;
            cout << "Modo inmediato " << FRED("desactivado") << endl;
            cout << endl;
         } else if (modoMenu == SELILUMINACION) {
            if (glIsEnabled(GL_LIGHT1)) {
               glDisable(GL_LIGHT1);
               cout << "Luz 1 " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHT1);
               cout << "Luz 1 " << FGRN("activada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '3' :
         if (modoMenu == SELILUMINACION) {
            if (glIsEnabled(GL_LIGHT2)) {
               glDisable(GL_LIGHT2);
               cout << "Luz 2 " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHT2);
               cout << "Luz 2 " << FGRN("activada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      case '<':
         if (modoMenu == SELILUMINACION) {
            // Decrementa el ángulo
            if (inc_alpha) {
               ld->VariarAnguloAlpha(-ANG_ILU);
            } else {
               ld->VariarAnguloBeta(-ANG_ILU);
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '>':
         if (modoMenu == SELILUMINACION) {
            // Decrementa el ángulo
            if (inc_alpha) {
               ld->VariarAnguloAlpha(ANG_ILU);
            } else {
               ld->VariarAnguloBeta(ANG_ILU);
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '.':
         // Información
         info(modoMenu, obj, vis, vbo);
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
            "H - Muestra este menú\n"
            "L - Activar/Desactivar modo oscuro\n"
            ". - Información de la escena\n"
            "Q - Salir\n"
            "O - Selección de objeto\n"
            "V - Selección de modo de visualización\n"
            "D - Selección de modo de dibujado\n"
            "I - Opciones de iluminación\n"
         );
      break;
      case SELOBJETO:
         printf(
            BOLD(FBLU("Selección de objeto\n"))
            "H - Muestra este menú\n"
            ". - Información de la escena\n"
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
            "H - Muestra este menú\n"
            ". - Información de la escena\n"
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
            ". - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "1 - Visualizar mediante glDrawElements\n"
            "2 - Visualizar mediante VBOs\n"
         );
      break;
   }
   printf("\n");
}

void Escena::info(menu modoMenu, unsigned int obj, unsigned int vis, bool vbo)
{
   /*
   using namespace std;

   // info iluminación
   bool ilu = glIsEnabled(GL_LIGHTING);
   bool li0 = glIsEnabled(GL_LIGHT0);
   bool li1 = glIsEnabled(GL_LIGHT1);
   bool li2 = glIsEnabled(GL_LIGHT2);

   cout
     << BOLD(FBLU("Información de la escena")) << endl

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



     << endl << FBLU("Iluminación             ")
     << (ilu ? FGRN("si") : FRED("no")) << endl

     << "\tLIGHT0:         "
     << (li0 ? FGRN("si") : FRED("no"))
     << endl

     << "\tLIGHT1:         "
     << (li1 ? FGRN("si") : FRED("no"))
     << endl

     << "\tLIGHT2:         "
     << (li2 ? FGRN("si") : FRED("no"))
     << endl

     << endl;
   */
   
   using namespace std;

   switch (modoMenu)
   {
      case NADA:
         cout << BOLD(FBLU("Información de la escena")) << endl;
         cout << endl;
         infoObjetos(obj);
         cout << endl;
         infoVisualizacion(vis);
         cout << endl;
         infoDibujado(vbo);
         cout << endl;
         infoIluminacion();
      break;
      case SELOBJETO:
         infoObjetos(obj);
      break;
      case SELVISUALIZACION:
         infoVisualizacion(vis);
      break;
      case SELDIBUJADO:
         infoDibujado(vbo);
      break;
      case SELILUMINACION:
         infoIluminacion();
      break;
      default:
         cout << FRED("Error :(") << endl;
      break;
   }
}

void Escena::infoObjetos(unsigned int obj)
{
   using namespace std;
   cout
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
      << ")" << endl;
}

void Escena::infoVisualizacion(unsigned int vis)
{
   using namespace std;
   cout
      << FBLU("Modo de visualización") << endl

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
      << endl;
}

void Escena::infoDibujado(bool vbo)
{
   using namespace std;
   cout
      << FBLU("Modo de dibujado") << endl

      << "\tModo inmediato: "
      << (!vbo ? FGRN("si") : FRED("no"))
      << endl

      << "\tModo diferido:  "
      << (vbo ? FGRN("si") : FRED("no"))
      << endl;
}

void Escena::infoIluminacion()
{
   using namespace std;

   // info iluminación
   bool ilu = glIsEnabled(GL_LIGHTING);
   bool li0 = glIsEnabled(GL_LIGHT0);
   bool li1 = glIsEnabled(GL_LIGHT1);
   bool li2 = glIsEnabled(GL_LIGHT2);

   cout
      << FBLU("Iluminación             ")
      << (ilu ? FGRN("si") : FRED("no")) << endl

      << "\tLIGHT0:         "
      << (li0 ? FGRN("si") : FRED("no"))
      << endl

      << "\tLIGHT1:         "
      << (li1 ? FGRN("si") : FRED("no"))
      << endl

      << "\tLIGHT2:         "
      << (li2 ? FGRN("si") : FRED("no"))
      << endl;
}
