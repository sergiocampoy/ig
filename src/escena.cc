

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

   ejes.changeAxisSize (4000);

   int n = 256;
   // OBJETOS ESCENA
   cubo       = new Cubo();
   tetraedro  = new Tetraedro(1);
   cono       = new Cono(n/4, n, 1, 1);
   esfera     = new Esfera(n, n, 1);
   flexo      = new Flexo(n);
   habitacion = new Habitacion();
   mesa       = new Mesa(n);
   monitor    = new Monitor("rick");
   lata       = new Cilindro(n/4, n, 3, 1);
   peon1      = new ObjRevolucion("./plys/peon.ply", n, 1, true, true);
   peon2      = new ObjRevolucion("./plys/peon.ply", n, 1, true, true);


   // COLORES
   cubo      -> colorea ({0.8, 0.8, 0.8});
   tetraedro -> colorea ({0.4, 0.4, 0.4});
   cono      -> colorea ({0.2, 0.2, 0.2});
   esfera    -> colorea ({1.0, 0.0, 1.0});
   flexo     -> colorea ({0.0, 0.0, 1.0});
   habitacion-> colorea ({1.0, 1.0, 1.0});
   mesa      -> colorea ({0.0, 0.2, 0.0});
   monitor   -> colorea ({0.0, 0.0, 0.0});
   lata      -> colorea ({1.0, 0.0, 0.0});
   peon1     -> colorea ({1.0, 1.0, 0.0});
   peon2     -> colorea ({0.0, 1.0, 1.0});


   // MATERIALES
   Material azul_flexo (
      {0, 0, 1, 1},
      {1, 1, 1, 1},
      {0, 0, 0.25, 1},
      128
   );
   Material gris_flexo (
      {0.8, 0.8, 0.8, 1},
      {1, 1, 1, 1},
      {0.2, 0.2, 0.2, 1},
      128
   );
   Material gris_habitacion (
      {0.5, 0.5, 0.5, 1},
      {0, 0, 0, 1},
      {0.25, 0.25, 0.25, 1},
      128
   );
   Material verde_mesa (
      {0, 0.25, 0, 1},
      {1, 1, 1, 1},
      {0, 0.0625, 0, 1},
      128
   );
   Material blanco_lata (
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {0.25, 0.25, 0.25, 1},
      128
   );
   Material blanco_peon (
      {1, 1, 1, 1},
      {0, 0, 0, 1},
      {0.25, 0.25, 0.25, 1},
      128
   );
   Material negro_peon (
      {0, 0, 0, 1},
      {1, 1, 1, 1},
      {0, 0, 0, 1},
      64
   );
   
   cubo      -> setMaterial (azul_flexo);
   tetraedro -> setMaterial (gris_habitacion);
   cono      -> setMaterial (blanco_peon);
   esfera    -> setMaterial (verde_mesa);
   flexo     -> setMateriales (azul_flexo, gris_flexo);
   habitacion-> setMaterial (gris_habitacion);
   mesa      -> setMaterial (verde_mesa);
   monitor   -> setMaterial (negro_peon);
   lata      -> setMaterial (blanco_lata);
   peon1     -> setMaterial (blanco_peon);
   peon2     -> setMaterial (negro_peon);

   
   // TEXTURAS
   habitacion->setTextura("hab");
   lata      ->setTextura("lata1");


   // LUCES
   lp = new LuzPosicional (
      {0, 0, 0},
      GL_LIGHT0,
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {0, 0, 0, 1}
   );
   ld = new LuzDireccional (
      {-90, 45},
      GL_LIGHT0,
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {0, 0, 0, 1}
   );
   ambiente = new Ambience (GL_LIGHT1);


   // CÁMARAS
   camaras.push_back(
      Camara (
         {0, 100, 100},
         {0, 0, 0},
         {0, 1, 0},
         CAM_1PS,
         10.0,
         2000.0
      )
   );

   camaras.push_back(
      Camara (
         {500, 500, 500},
         {0, 0, 0},
         {0, 1, 0},
         CAM_ORT,
         10.0,
         2000.0
      )
   );

   camaras.push_back(
      Camara (
         {500, 500, 500},
         {0, 0, 0},
         {0, 1, 0},
         0,
         10.0,
         2000.0
      )
   );

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
   glEnable(GL_NORMALIZE); // No modifica las normales

   glShadeModel(GL_SMOOTH);

   // TODO: Luces temporal
   glEnable(GL_LIGHT0);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   // parámetros extra de las cámaras
   camaras[0].setLeft(-15);
   camaras[0].setRight(15);
   camaras[0].setBottom(-15);
   camaras[0].setTop(15);

   camaras[1].setLeft(-400);
   camaras[1].setRight(400);
   camaras[1].setBottom(-400);
   camaras[1].setTop(400);

   camaras[2].setLeft(-5);
   camaras[2].setRight(5);
   camaras[2].setBottom(-5);
   camaras[2].setTop(5);

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );

   help(modoMenu);
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

   // Aplicar luces
   ld->aplicar();
   ambiente->aplicar();

   // Dibujar objetos
   dibujarObjetos();
}

void Escena::dibujarObjetos () {
   glPushMatrix();
      glTranslatef(85, -90, -15);
      glScalef(10, 10, 10);
      if (obj & OBJ_CUB)
         cubo->draw(vis, vbo);
      if (camaras[camaraActiva].getObjeto() & OBJ_CUB)
         cubo->draw(vis | VIS_LIN, vbo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-120, -90 - 10*sin(-M_PI/6), -10);
      glScalef(10, 10, 10);
      if (obj & OBJ_TET)
         tetraedro->draw(vis, vbo);
      if (camaras[camaraActiva].getObjeto() & OBJ_TET)
         tetraedro->draw(vis | VIS_LIN, vbo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-120, -90, 15);
      glScalef(10, 30, 10);
      if (obj & OBJ_CON)
         cono->draw(vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_CON)
         cono->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0, -220, 0);
      glScalef(30, 30, 30);
      if (obj & OBJ_ESF)
         esfera->draw(vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_ESF)
         esfera->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
      glScalef(500, 500, 500);
      glRotatef(90, 0, 1, 0);
      glTranslatef(-0.5, -0.5, -0.5);
      if (obj & OBJ_HAB)
         habitacion->draw(vis, vbo);
      if (camaras[camaraActiva].getObjeto() & OBJ_HAB)
         habitacion->draw(vis | VIS_LIN, vbo);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(0, -90, 0);
      glScalef(4, 4, 4);
      if (obj & OBJ_MES)
         mesa->draw (vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_MES)
         mesa->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(120, -90, -30);
      glScalef(5, 5, 5);
      glRotatef(-135, 0, 1, 0);
      if (obj & OBJ_FLE)
         flexo->draw(vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_FLE)
         flexo->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(0, -90, -30);
      glScalef(40, 40, 40);
      if (obj & OBJ_MON)
         monitor->draw(vis, vbo);
      if (camaras[camaraActiva].getObjeto() & OBJ_MON)
         monitor->draw(vis | VIS_LIN, vbo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-120, -90, -40);
      glScalef(10, 10, 10);
      glTranslatef(0, 1.5, 0);
      glRotatef(90, 0, 1, 0);
      if (obj & OBJ_LAT)
         lata->draw(vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_LAT)
         lata->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-25, -90, 30);
      glScalef(20, 20, 20);
      glTranslatef(0, 1.4, 0);
      glRotatef(90, 0, 1, 0);
      if (obj & OBJ_PE1)
         peon1->draw(vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_PE1)
         peon1->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(25, -90, 30);
      glScalef(20, 20, 20);
      glTranslatef(0, 1.4, 0);
      glRotatef(90, 0, 1, 0);
      if (obj & OBJ_PE2)
         peon2->draw(vis, vbo, obj & OBJ_TAP);
      if (camaras[camaraActiva].getObjeto() & OBJ_PE2)
         peon2->draw(vis | VIS_LIN, vbo, obj & OBJ_TAP);
   glPopMatrix();
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
               glDisable(GL_LIGHTING);
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
         } else if (modoMenu == LUCES) {
            modificarAlpha = true;
            modificarGamer = false;
            cout << "Se va a modificar " << FBLU("alfa") << endl;
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'B':
         if (modoMenu == LUCES) {
            modificarAlpha = false;
            modificarGamer = false;
            cout << "Se va a modificar " << FBLU("beta") << endl;
         }
      break;
      case 'C':
         if (modoMenu == NADA) {
            modoMenu = CAMARAS;
            help(modoMenu);
         } else if (modoMenu == SELOBJETO) {
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
      case 'E':
         if (modoMenu == SELOBJETO) {
            // Activa/desactiva esfera
            obj ^= OBJ_ESF;
            if (obj != OBJ_ESF) {
               cout << "Esfera " << FGRN("activada") << endl;
            } else {
               cout << "Esfera " << FRED("desactivada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'F':
         if (modoMenu == SELOBJETO) {
            // Activa/desactiva flexo
            obj ^= OBJ_FLE;
            if (obj != OBJ_FLE) {
               cout << "Flexo " << FGRN("activado") << endl;
            } else {
               cout << "Flexo " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'G':
         if (modoMenu == LUCES) {
            if (modificarGamer) {
               modificarGamer = false;
               cout << "Modo "
                    << FRED("G")
                    << FYEL("A")
                    << FGRN("M")
                    << FCYN("E")
                    << FBLU("R")
                    << FRED(" desactivado")
                    << endl;
            } else {
               modificarGamer = true;
               cout << "Modo "
                    << FRED("G")
                    << FYEL("A")
                    << FGRN("M")
                    << FCYN("E")
                    << FBLU("R")
                    << FGRN(" activado")
                    << endl;
            }
         } 
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
               glDisable(GL_LIGHTING);
               cout << "Modo lineas " << FGRN("activado") << endl;
            } else {
               cout << "Modo lineas " << FRED("desactivado") << endl;
            }
         } else if (modoMenu == NADA || modoMenu == LUCES) {
            modoMenu = LUCES;
            vis &= 0b10100; // Sólido y texturas
            if (glIsEnabled(GL_LIGHTING)) {
               glDisable(GL_LIGHTING);
               cout << "Iluminación " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHTING);
               cout << "Iluminación " << FGRN("activada") << endl;
            }
            help(modoMenu);
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva lata
            obj ^= OBJ_LAT;
            if (obj != OBJ_LAT) {
               cout << "Lata " << FGRN("activada") << endl;
            } else {
               cout << "Lata " << FRED("desactivada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case 'N':
         if (modoMenu == SELOBJETO) {
            // Activa/desactiva cono
            obj ^= OBJ_CON;
            if (obj != OBJ_CON) {
               cout << "Cono " << FGRN("activado") << endl;
            } else {
               cout << "Cono " << FRED("desactivado") << endl;
            }
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
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva mesa
            obj ^= OBJ_MES;
            if (obj != OBJ_MES) {
               cout << "Mesa " << FGRN("activada") << endl;
            } else {
               cout << "Mesa " << FRED("desactivada") << endl;
            }
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
            // Activa/desactiva modo puntos
            vis ^= VIS_PUN;
            if (vis & VIS_PUN) {
               glDisable(GL_LIGHTING);
               cout << "Modo puntos " << FGRN("activado") << endl;
            } else {
               cout << "Modo puntos " << FRED("desactivado") << endl;
            }
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva tapas
            obj ^= OBJ_TAP;
            if (obj != OBJ_TAP) {
               cout << "Tapas " << FGRN("activadas") << endl;
            } else {
               cout << "Tapas " << FRED("desactivadas") << endl;
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
            // Activa/desactiva habitación
            obj ^= OBJ_HAB;
            if (obj != OBJ_HAB) {
               cout << "Habitación " << FGRN("activado") << endl;
            } else {
               cout << "Habitación " << FRED("desactivado") << endl;
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
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva monitor
            obj ^= OBJ_MON;
            if (obj != OBJ_MON) {
               cout << "Monitor " << FGRN("activado") << endl;
            } else {
               cout << "Monitor " << FRED("desactivado") << endl;
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
      case '0':
         if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b111; // Selecciona todos los grados de libertad
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '1' :
         if (modoMenu == CAMARAS) {
            camaraActiva = 0;
            change_projection();
            cout << "Cámara en primera persona " << FGRN("activada") << endl;
         } else if (modoMenu == SELDIBUJADO) {
            vbo = false;
            cout << "Modo inmediato " << FGRN("activado") << endl;
            cout << "Modo diferido " << FRED("desactivado") << endl;
            cout << endl;
         } else if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b1; // Cabeza
         } else if (modoMenu == LUCES) {
            if (glIsEnabled(GL_LIGHT0)) {
               glDisable(GL_LIGHT0);
               cout << "Luz direccional " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHT0);
               cout << "Luz direccional " << FGRN("activada") << endl;
            }
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva peon1
            obj ^= OBJ_PE1;
            if (obj != OBJ_PE1) {
               cout << "Peon1 " << FGRN("activado") << endl;
            } else {
               cout << "Peon1 " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '2' :
         if (modoMenu == CAMARAS) {
            camaraActiva = 1;
            change_projection();
            cout << "Cámara ortogonal " << FGRN("activada") << endl;
         } else if (modoMenu == SELDIBUJADO) {
            vbo = true;
            cout << "Modo diferido " << FRED("activado") << endl;
            cout << "Modo inmediato " << FGRN("desactivado") << endl;
            cout << endl;
         } else if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b10; // Brazo
         } else if (modoMenu == LUCES) {
            if (glIsEnabled(GL_LIGHT1)) {
               glDisable(GL_LIGHT1);
               cout << "Luz ambiente " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHT1);
               cout << "Luz ambiente " << FGRN("activada") << endl;
            }
         } else if (modoMenu == SELOBJETO) {
            // Activa/desactiva peon2
            obj ^= OBJ_PE2;
            if (obj != OBJ_PE2) {
               cout << "Peon2 " << FGRN("activado") << endl;
            } else {
               cout << "Peon2 " << FRED("desactivado") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
         }
      break;
      case '3':
         if (modoMenu == CAMARAS) {
            camaraActiva = 2;
            change_projection();
            cout << "Cámara en tercera persona " << FGRN("activada") << endl;
         } else if (modoMenu == AMANUAL || modoMenu == ANIMACION) {
            grd_libertad = 0b100; // Altura
         } else if (modoMenu == LUCES) {
            if (glIsEnabled(GL_LIGHT2)) {
               glDisable(GL_LIGHT2);
               cout << "Luz del flexo " << FRED("desactivada") << endl;
            } else {
               glEnable(GL_LIGHT2);
               cout << "Luz del flexo " << FGRN("activada") << endl;
            }
         } else {
            cout << FRED("Opción inválida") << endl;
            help(modoMenu);
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
         } else if (modoMenu == LUCES) {
            if (modificarGamer) {
               ambiente->aumentarVelocidad();
            } else {
               if (modificarAlpha) {
                  ld->variarAnguloAlpha(5);
               } else {
                  ld->variarAnguloBeta(5);
               }
               ld->printDireccion();
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
         } else if (modoMenu == LUCES) {
            if (modificarGamer) {
               ambiente->disminuirVelocidad();
            } else {
               if (modificarAlpha) {
                  ld->variarAnguloAlpha(-5);
               } else {
                  ld->variarAnguloBeta(-5);
               }
               ld->printDireccion();
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
         Observer_angle_y-- ; camaras[camaraActiva].girar3p(1, 0);
         //camaras[camaraActiva].rotarYExaminar(-1.0*2*M_PI/360.0);
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ; camaras[camaraActiva].girar3p(-1, 0);
         //camaras[camaraActiva].rotarYExaminar(1.0*2*M_PI/360.0);
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ; camaras[camaraActiva].girar3p(0, 1);
         //camaras[camaraActiva].rotarZExaminar(-1.0*2*M_PI/360.0);
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ; camaras[camaraActiva].girar3p(0, -1);
         //camaras[camaraActiva].rotarZExaminar(1.0*2*M_PI/360.0);
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

void Escena::change_projection(/* const float ratio_xy */)
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   camaras[camaraActiva].setProyeccion();

   // OLD change_proyection
   /*
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   */
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   float ratio = (float)newWidth/(float)newHeight;

   for (unsigned int i = 0; i < camaras.size(); i++) {
      camaras[i].redimensionar(ratio);
   }

   change_projection();
   glViewport (0, 0, newWidth, newHeight);

   // OLD redimensionar
   /*
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
   */
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva].setObserver();

   // PRE - P6
   /*
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
   */
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
            "L - Menú de iluminación\n"
            "O - Selección de objeto\n"
            "V - Selección de modo de visualización\n"
            "D - Selección de modo de dibujado\n"
            "A - Menú de animación automática\n"
            "M - Menú de animación manual\n"
         );
      break;
      case SELOBJETO:
         printf(
            BOLD(FBLU("Selección de objeto\n"))
            "H - Muestra este menú\n"
            "I - Información de la escena\n"
            "Q - Volver al menú principal\n"
            "A - Activar/desactivar todos los objetos\n"
            "P - Activar/desactivar tapas\n"
            "C - Activar/desactivar cubo\n"
            "T - Activar/desactivar tetraedro\n"
            "N - Activar/desactivar cono\n"
            "E - Activar/desactivar esfera\n"
            "F - Activar/desactivar flexo\n"
            "R - Activar/desactivar habitación\n"
            "M - Activar/desactivar mesa\n"
            "S - Activar/desactivar monitor\n"
            "L - Activar/desactivar lata\n"
            "1 - Activar/desactivar peon1\n"
            "2 - Activar/desactivar peon2\n"
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
            "T - Activar/desactivar texturas\n"
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
      case ANIMACION:
         printf(
            BOLD(FBLU("Opciones de animación automática\n"))
            "H - Muestra este menú\n"
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
            "H - Muestra este menú\n"
            "Q - Volver al menú principal\n"
            "0 - Modificar todos los grados de libertad\n"
            "1 - Modificar la cabeza\n"
            "2 - Modificar el brazo\n"
            "3 - Modificar el tronco\n"
            "+ - Aumentar el valor\n"
            "- - Disminuir el valor\n"
         );
      break;
      case LUCES:
         printf(
            BOLD(FBLU("Opciones iluminación\n"))
            "H - Muestra este menú\n"
            "Q - Volver al menú principal\n"
            "L - Activar/Desactivar iluminación\n"
            "1 - Activar/Desactivar luz direccional de la ventana\n"
            "2 - Activar/Desactivar luz ambiente\n"
            "3 - Activar/Desactivar luz del flexo\n"
            "A - Modificar el valor alfa de la luz direccional\n"
            "B - Modificar el valor beta de la luz direccional\n"
            "G - Modo Gamer\n"
            "+ - Aumentar el valor o velocidad\n"
            "- - Disminuir el valor o velocidad\n"
         );
      break;
      case CAMARAS:
      printf(
            BOLD(FBLU("Opciones Cámaras\n"))
            "H - Muestra este menú\n"
            "Q - Volver al menú principal\n"
            "1 - Seleccionar cámara en primera persona\n"
            "2 - Cámara ortogonal (3a persona)\n"
            "3 - Cámara ortogonal (3a persona)\n"
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

     << "\tCono:           "
     << ((obj & OBJ_CON) ? FGRN("si") : FRED("no"))
     << endl

     << "\tEsfera:         "
     << ((obj & OBJ_ESF) ? FGRN("si") : FRED("no"))
     << endl

     << "\tFlexo:          "
     << ((obj & OBJ_FLE) ? FGRN("si") : FRED("no"))
     << endl

     << "\tHabitacion:     "
     << ((obj & OBJ_HAB) ? FGRN("si") : FRED("no"))
     << endl

     << "\tMesa:           "
     << ((obj & OBJ_MES) ? FGRN("si") : FRED("no"))
     << endl

     << "\tMonitor:        "
     << ((obj & OBJ_MON) ? FGRN("si") : FRED("no"))
     << endl

     << "\tLata:           "
     << ((obj & OBJ_LAT) ? FGRN("si") : FRED("no"))
     << endl

     << "\tPeon1:          "
     << ((obj & OBJ_PE1) ? FGRN("si") : FRED("no"))
     << endl

     << "\tPeon2:          "
     << ((obj & OBJ_PE2) ? FGRN("si") : FRED("no"))
     << endl

     << "\tTapas:          "
     << ((obj & OBJ_TAP) ? FGRN("si") : FRED("no"))
     << endl


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

     << "\tTexturas:       "
     << ((vis & VIS_TEX) ? FGRN("si") : FRED("no"))
     << endl


     << endl << FBLU("Modo de dibujado") << endl

     << "\tModo inmediato: "
     << (!vbo ? FGRN("si") : FRED("no"))
     << endl

     << "\tModo diferido:  "
     << (vbo ? FGRN("si") : FRED("no"))
     << endl


     << endl << FBLU("Iluminación") << endl

     << "\tGL_LIGHTING:    "
     << (glIsEnabled(GL_LIGHTING) ? FGRN("si") : FRED("no"))
     << endl

     << "\tDireccional:    "
     << (glIsEnabled(GL_LIGHT0) ? FGRN("si") : FRED("no"))
     << endl

     << "\tAmbiente:       "
     << (glIsEnabled(GL_LIGHT1) ? FGRN("si") : FRED("no"))
     << endl

     << "\tFlexo:          "
     << (glIsEnabled(GL_LIGHT2) ? FGRN("si") : FRED("no"))
     << endl

     << endl;
}


void Escena::animarModeloJerarquico() {
   if (animacion_automatica)
      flexo->animarModeloJerarquico();
}
    
void Escena::animarLuz () {
   if (modificarGamer) {
      ambiente->animar();
   }
}

void Escena::clickRaton (int boton, int estado, int x, int y) {

   xant = x;
   yant = y;

   if (boton == GLUT_RIGHT_BUTTON) {
      if (estado == GLUT_DOWN) {
         // entra en el estado 'moviendo cámara'
         camara |= CAM_MOV;
         //camara |= CAM_1PS;
      } else {
         // sale del estado 'moviendo cámara' 
         camara &= ~CAM_MOV;
      }
   }

   // Rueda del ratón
   if (boton == 3) {
      camaras[camaraActiva].zoom(0.8);
   }
   if (boton == 4) {
      camaras[camaraActiva].zoom(1.2);
   }

   // Seleccionar objeto
   if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
      dibujaSeleccion();
      pick(x, y);
      // dibujaSeleccion();
      /*
      GLfloat pixel[3];
      glReadPixels (x, y, 1, 1, GL_RGB, GL_FLOAT, (void*)pixel);

      printf("%f, %f, %f\n", pixel[0], pixel[1], pixel[2]);
      // void glReadPixels ( GLint x , GLint y , GLsizei width , GLsizei height ,GLenum format , GLenum type , GLvoid * pixels );
*/
   }

   change_projection();
}

void Escena::ratonMovido (int x, int y) {
   if (camara & CAM_MOV) {
      // Voy a mover la cámara
      if (camara & CAM_1PS && camaras[camaraActiva].getTipo() & CAM_1PS) {
         // Estoy en primera persona
         camaras[camaraActiva].girar(x-xant, y-yant);
         xant = x;
         yant = y;
      } else {
         // Estoy en tercera persona
         camaras[camaraActiva].girar3p(x-xant, y-yant);
         xant = x;
         yant = y;
      }
   }
}

void Escena::dibujaSeleccion () {
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

   glDisable (GL_DITHER);

   bool tex = vis & VIS_TEX;
   vis &= ~VIS_TEX; // deshabilita texturas

   bool lighting = glIsEnabled (GL_LIGHTING);
   glDisable (GL_LIGHTING);

   dibujarObjetos();

   glEnable (GL_DITHER);
   
   if (tex)
      vis |= VIS_TEX; // habilita texturas si es necesario

   if (lighting)
      glEnable (GL_LIGHTING); // habilita la luz si es necesario

}

void Escena::pick (int x, int y) {
   // Obtiene el color
   GLfloat pixel[3];
   GLint viewport[4];

   glGetIntegerv (GL_VIEWPORT, viewport);
   glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, pixel);

   Tupla3f color (pixel[0], pixel[1], pixel[2]);
   printf("(%f, %f, %f)\n", color(0), color(1), color(2));
   printf("(%f, %f, %f)\n", lata->getColor()(0), lata->getColor()(1), lata->getColor()(2));
   

   camara &= ~CAM_1PS;

   // Obtiene el objeto al que pertenece el color

   if (color == cubo->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_CUB);
      camaras[camaraActiva].setAt(85, -90, -15);
   } else if (color == tetraedro->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_TET);
      camaras[camaraActiva].setAt(-120, -90 - 10*sin(-M_PI/6), -10);
   } else if (color == cono->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_CON);
      camaras[camaraActiva].setAt(-120, -90, 15);
   } else if (color == esfera->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_ESF);
      camaras[camaraActiva].setAt(0, -220, 0);
   } else if (color == flexo->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_FLE);
      camaras[camaraActiva].setAt(120, -90, -30);
   } else if (color == habitacion->getColor()) {
      /*
      camaras[camaraActiva].setObjeto(OBJ_CUB);
      camaras[camaraActiva].setAt(-0.5, -0.5, -0.5);
      */
      camaras[camaraActiva].setObjeto(0);
      camara |= CAM_1PS;
   } else if (color == mesa->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_MES);
      camaras[camaraActiva].setAt(0, -90, 0);
   } else if (color == monitor->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_MON);
      camaras[camaraActiva].setAt(0, -90, -30);
   } else if (color == lata->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_LAT);
      camaras[camaraActiva].setAt(-120, -90, -40);
   } else if (color == peon1->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_PE1);
      camaras[camaraActiva].setAt(-25, -90, 30);
   } else if (color == peon2->getColor()) {
      camaras[camaraActiva].setObjeto(OBJ_PE2);
      camaras[camaraActiva].setAt(25, -90, 30);
   } else {
      camaras[camaraActiva].setObjeto(0);
      camara |= CAM_1PS;
   }
}