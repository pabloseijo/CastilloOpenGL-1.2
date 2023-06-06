#include <windows.h>	//Inclusion de variables de windows
#include <glut.h>	//Inclusion de GLUT mira que la tienes ahi
#include <GL/gl.h>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	
#include "castillo.h"
#include "cuerposGeometricos.h"


//Para la texturizacion
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int W_WIDTH = 500;	 //Ancho de la ventana
int W_HEIGHT = 500;		//Alto de la ventana

#define GL_PI 3.14f
//Milisegundos que tarda en redibujar
#define MYTIEMPO 41

// Ángulos de rotación para la cámara
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

int agua[16];
int agua_indice = 0;

// Definir el color gris claro de la niebla
GLfloat gray[] = { 0.7, 0.7, 0.7, 1.0 };
// Configurar la posición de la niebla
GLfloat fog_start = 600.0;
GLfloat fog_end = 800.0;

body cuerpo = { -350, -22, -250, 4, 12, 4, 0, 0 };
head cabeza = { 0, -6, 0, 6, 6, 6, 0, 0 };
arm brazo_izq = { 0, -6, 0, 1, 7, 1, 0, 0 };
arm brazo_der;
leg pierna_izq = { 0, -30, 0, 1.5, 12, 1.5, 0, 0 };
leg pierna_der;
personaje protagonista = { 0, 0, 0, 0, 0, 0, 0, 0 };

float Rot = 0;
camara = 0;
sueloScale = 50;
int cuadrado = 0, cono = 0, cilindro = 0, rectangulo = 0, cubo = 0, esfera = 0, soldado = 0;

int valorCutOff = 179;

const int SLICES = 32;
const int STACKS = 32;

void Idle();
void reshape(int width, int height);
void skyBox();

//Texturas paisaje
int hierba = 0, tejado = 0, muro = 0, cielo = 0, tejadoCasa[5], muroCasa[5], tronco = 0, hojas = 0, armadura = 0, cara = 0, pantalones = 0;

int flag = 0;

// GL_LIGHT1
GLfloat ambient_1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat diffuse_1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular_1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat luzPos_1[4] = { 1000.0f, 1000.0f, 0.0f, 1.0f };
GLfloat spotDir_1[3] = { -1.0f, -1.0f, -1.0f };
GLfloat specRef_1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };


//Asigno la camara a cada caso
void onMenu(int opcion) {
	//En funcion de la opcion selecciono la camara que quiero
	switch (opcion) {
	case 1:
		camara = 1;
		break;

	case 2:
		camara = 2;
		break;

	case 3:
		camara = 3;
		break;

	case 4:
		camara = 4;
		break;

	case 5:
		camara = 5;
		break;
	}

	glutPostRedisplay();
}

//Creo el menu
void myMenu(void) {
	int menuFondo = 0;

	menuFondo = glutCreateMenu(onMenu);

	glutAddMenuEntry("Voyayer", 1); //La sonda que nos muestra todo el sistema
	glutAddMenuEntry("Primera Persona", 2);
	glutAddMenuEntry("Tercera Persona", 3);
	glutAddMenuEntry("Activar Niebla", 4);
	glutAddMenuEntry("Desactivar Niebla", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* funcion que dibuja los ejes*/
void myEjes() {

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(.75f, 0.0f, 0.0f);
	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, .75f, 0.0f);
	glEnd();


	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.f, 0.0f, .75f);
	glEnd();

	//Diagonal
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(.35f, .35, .35f);
	glEnd();

}

//Lista del cono
int myCono() {
	int indice = glGenLists(1);
	glNewList(indice, GL_COMPILE);


	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	// Enable texture coordinates
	gluQuadricTexture(quadric, GL_TRUE);

	glPushMatrix();
	gluCylinder(quadric, 0.0f, 1.0f, 1.0f, SLICES, STACKS);
	glPopMatrix();

	gluDeleteQuadric(quadric);
	glEndList();
	return indice;
}

// Lista piramide

//Lista del Cilindro
int myCilindro() {
	int indice = glGenLists(1);
	glNewList(indice, GL_COMPILE);
	glEnable(GL_BLEND);

	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	// Enable texture coordinates
	gluQuadricTexture(quadric, GL_TRUE);

	glPushMatrix();
	gluCylinder(quadric, 1.0f, 1.0f, 1.0f, SLICES, STACKS);
	glPopMatrix();

	gluDeleteQuadric(quadric);
	glEndList();
	return indice;
}

//Lista del subo
int myRectangulo() {
	int indice;
	indice = glGenLists(1);
	glNewList(indice, GL_COMPILE);

	// Aplicar la textura en el cuadrado
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muro);

	glBegin(GL_TRIANGLES);
	// CUADRADO 1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, -.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f, -.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, -.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f, -.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, -.5f);

	// CUADRADO 2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, .5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, .5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f, .5f, .5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, .5f);

	// CUADRADO 3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f, -.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-.5f, .5f, .5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, .5f, .5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-.5f, -.5f, -.5f);

	// CUADRADO 4
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, -.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, -.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(.5f, .5f, .5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(.5f, .5f, .5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(.5f, -.5f, .5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, -.5f);

	// CUADRADO 5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, -.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, -.5f, .5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f, -.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, -.5f);

	// CUADRADO 6
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, .5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, .5f, -.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f, .5f, .5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(.5f, .5f, .5f);

	glEnd();


	// Aplicar la textura en el cuadrado
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();
	return indice;
}

void dibujaSoldado(int posicion_x, int posicion_z) {
	//Piernas
	glPushMatrix();
	glTranslatef(posicion_x - 2, -30, posicion_z);
	glScalef(1.5, 12, 1.5);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pantalones);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	//Piernas
	glPushMatrix();
	glTranslatef(posicion_x + 2, -30, posicion_z);
	glScalef(1.5, 12, 1.5);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pantalones);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	//Tronco
	glPushMatrix();
	glTranslatef(posicion_x, -22, posicion_z);
	glScalef(4, 12, 4);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, armadura);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Brazos
	glPushMatrix();
	glTranslatef(posicion_x - 5, -20, posicion_z);
	glScalef(1, 7, 1);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, armadura);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	//Brazos
	glPushMatrix();
	glTranslatef(posicion_x + 5, -20, posicion_z);
	glScalef(1, 7, 1);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, armadura);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Cabeza
	glPushMatrix();
	glTranslatef(posicion_x, -6, posicion_z);
	glScalef(6, 6, 6);
	//
	glRotatef(122.5f, 0, 1, 0);
	//Lo roto para ponerlo de pie
	glRotatef(180.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cara);
	glCallList(esfera);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

//Funcion para dibujar el suelo
void dibujaSuelo() {

	for (int i = -1500; i <= 1500; i += sueloScale)
		for (int j = -1500; j <= 1500; j += sueloScale) {
			glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(i, j, 0);

			glScalef(sueloScale, sueloScale, sueloScale);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hierba);
			glCallList(cuadrado);
			glDisable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();
		}
}

void dibujaMuros() {
	//Muro Frontal 
	glPushMatrix();
	glTranslatef(0, 15, 100);
	glScalef(175, 100, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Muro Lateral Izq
	glPushMatrix();
	glTranslatef(-100, 15, 0);
	glRotatef(-90.0f, 0, 1, 0);
	glScalef(175, 100, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Muro Lateral Dcho
	glPushMatrix();
	glTranslatef(100, 15, 0);
	glRotatef(-90.0f, 0, 1, 0);
	glScalef(175, 100, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Muro Trasero 
	glPushMatrix();
	glTranslatef(0, 15, -100);
	glScalef(175, 100, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();
}

void dibujaTorre() {

	//Torre frontal 1: paredes
	glPushMatrix();
	glTranslatef(100, -30, 100);
	glScalef(25, 150, 25);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muro);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre frontal 1: tejado
	glPushMatrix();
	glTranslatef(100, 145, 100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre frontal 2: paredes
	glPushMatrix();
	//traslado 200 en el eje x
	glTranslatef(-100, -30, 100);
	glScalef(25, 150, 25);
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muro);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre frontal 2: tejado
	glPushMatrix();
	glTranslatef(-100, 145, 100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre trasera 1:paredes
	glPushMatrix();
	glTranslatef(100, -30, -100);
	glScalef(25, 150, 25);
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muro);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre trasera 1: tejado
	glPushMatrix();
	glTranslatef(100, 145, -100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre trasera 2: paredes
	glPushMatrix();
	glTranslatef(-100, -30, -100);
	glScalef(25, 150, 25);
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muro);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre trasera 2: tejado
	glPushMatrix();
	glTranslatef(-100, 145, -100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void dibujaCastillo() {

	//Muro Frontal 
	glPushMatrix();
	glTranslatef(0, 35, 0);
	glScalef(100, 150, 100);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Torre frontal 1: paredes
	glPushMatrix();
	glTranslatef(0, 60, 0);
	glScalef(25, 150, 25);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muro);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre frontal 1: tejado
	glPushMatrix();
	glTranslatef(0, 240, 0);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

}

void dibujaCasa(int posicion_x, int posicion_z, int muro, int tejado) {

	//Torre frontal 1: paredes
	glPushMatrix();
	glTranslatef(posicion_x, -30, posicion_z);
	glScalef(35, 50, 35);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, muroCasa[muro]);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre frontal 1: tejado
	glPushMatrix();
	glTranslatef(posicion_x, 55, posicion_z);
	glScalef(45, 45, 45);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tejadoCasa[tejado]);
	glCallList(cono);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void dibujaArbol(int posicion_x, int posicion_z) {

	//Tronco
	glPushMatrix();
	glTranslatef(posicion_x, -30, posicion_z);
	glScalef(5, 50, 5);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tronco);
	glCallList(cilindro);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Torre frontal 1: tejado
	glPushMatrix();
	glTranslatef(posicion_x, 35, posicion_z);
	glScalef(20, 20, 20);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, hojas);
	glCallList(esfera);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

}

void myMovimiento() {
	Rot += 5.0f;
	if (Rot > 360) Rot -= 360;

	glutPostRedisplay(); //se vuelve a dibujar
	glutTimerFunc(MYTIEMPO, myMovimiento, 0);//se vuelve a ejecutar myMovimiento
}

// Funcion de dibujo
void myDisplay(void) {
	// Clear the window with current clearing color

	if (camara == 1) {
		myCamara(W_WIDTH, W_HEIGHT);
	}
	else if (camara == 2) {
		primeraPersona(protagonista);
	}
	else if (camara == 3) {
		terceraPersona(protagonista);
	}
	else if (camara == 4) {
		myCamara(W_WIDTH, W_HEIGHT);
		// Habilitar la niebla
		glEnable(GL_FOG);

		// Configurar los parámetros de niebla
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gray);

		glFogf(GL_FOG_START, fog_start);
		glFogf(GL_FOG_END, fog_end);

		// Configurar la densidad de la niebla
		GLfloat fog_density = 0.5;
		glFogf(GL_FOG_DENSITY, fog_density);
	}
	else if (camara == 5) {
		myCamara(W_WIDTH, W_HEIGHT);
		// Deshabilitar la niebla
		glDisable(GL_FOG);
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Matriz del Modelo
	glLoadIdentity(); // Inicializamos la matriz del modelo a la identidad
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (camara == 4) {
		// Habilitar la niebla
		glEnable(GL_FOG);

		// Configurar los parámetros de niebla
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gray);

		glFogf(GL_FOG_START, fog_start);
		glFogf(GL_FOG_END, fog_end);

		// Configurar la densidad de la niebla
		GLfloat fog_density = 0.2;
		glFogf(GL_FOG_DENSITY, fog_density);
	}

	glDisable(GL_LIGHTING);
	skyBox();
	glEnable(GL_LIGHTING);
	dibujaSuelo();
	srand(33);

	glPushMatrix();
	glTranslatef(0, 30, 0);
	glPushMatrix();
	//Dibujamos las murallas
	dibujaMuros();
	dibujaTorre();

	//dibujamos el castillo
	dibujaCastillo();

	dibujaCasa(-300, -200, 0, 0);
	dibujaCasa(-450, -300, 1, 1);
	dibujaCasa(-200, 168, 2, 2);
	dibujaCasa(-500, 134, 3, 3);
	dibujaCasa(-245, 398, 4, 4);

	srand(33);

	for (int i = 0; i < 100; i++) {
		int randomX = rand() % 1000 + 300;
		int randomZ = rand() % 1000 + 300;

		dibujaArbol(randomX, randomZ);
	}

	for (int i = 0; i < 32; i++) {
		int randomX = rand() % 600 + 50;
		int randomZ = -(rand() % 600 + 50);

		dibujaSoldado(randomX, randomZ);
	}

	dibujaProtagonista(protagonista);

	glPopMatrix();
	glPopMatrix();
	dibujaAgua();
	myEjes();

	glFlush();
	glutSwapBuffers();


}

int myCargarTexturas(char* name) {
	int textura;

	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);

	// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);

	if (data) {
		if (nrChannels == 3) { // hierba
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 4) { // agua, tiene 4 por canal alpha
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}

	stbi_image_free(data);

	return textura;
}

void skyBox() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE); // Habilita la ocultacion de caras
	glDisable(GL_NORMALIZE);

	glPushMatrix();

	glScalef(1200, 1200, 1200);
	glTranslatef(0, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cielo);
	glCallList(esfera);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // Habilita la ocultacion de caras
	glEnable(GL_NORMALIZE);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Castillo");

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE); // Habilita la ocultacion de caras
	glEnable(GL_NORMALIZE);

	//Eventos comentado hasta la siguiente practica
	glutKeyboardFunc(myTeclado);
	glutSpecialFunc(myTeclasespeciales);
	glutDisplayFunc(myDisplay);
	// Funcion de actualizacion
	glutIdleFunc(Idle);
	// Función de devolución de llamada para el cambio de tamaño de la ventana
	glutReshapeFunc(reshape);

	//Habilito las texturas
	// glShadeModel(GL_SMOOTH);

	//General
	hierba = myCargarTexturas("hierba.jpg");
	tejado = myCargarTexturas("roof.jpg");
	muro = myCargarTexturas("muro.jpg");
	cielo = myCargarTexturas("cielo.jpg");

	//Casas
	muroCasa[0] = myCargarTexturas("muroCasa0.jpg");
	tejadoCasa[0] = myCargarTexturas("tejadoCasa0.jpg");
	muroCasa[1] = myCargarTexturas("muroCasa1.jpg");
	tejadoCasa[1] = myCargarTexturas("tejadoCasa1.jpg");
	muroCasa[2] = myCargarTexturas("muroCasa2.jpg");
	tejadoCasa[2] = myCargarTexturas("tejadoCasa2.jpg");
	muroCasa[3] = myCargarTexturas("muroCasa3.jpg");
	tejadoCasa[3] = myCargarTexturas("tejadoCasa3.jpg");
	muroCasa[4] = myCargarTexturas("muroCasa4.jpg");
	tejadoCasa[4] = myCargarTexturas("tejadoCasa4.jpg");

	// lago
	agua[0] = myCargarTexturas("caust00.png");
	agua[1] = myCargarTexturas("caust01.png");
	agua[2] = myCargarTexturas("caust02.png");
	agua[3] = myCargarTexturas("caust03.png");
	agua[4] = myCargarTexturas("caust04.png");
	agua[5] = myCargarTexturas("caust05.png");
	agua[6] = myCargarTexturas("caust06.png");
	agua[7] = myCargarTexturas("caust07.png");
	agua[8] = myCargarTexturas("caust08.png");
	agua[9] = myCargarTexturas("caust09.png");
	agua[10] = myCargarTexturas("caust10.png");
	agua[11] = myCargarTexturas("caust11.png");
	agua[12] = myCargarTexturas("caust12.png");
	agua[13] = myCargarTexturas("caust12.png");
	agua[14] = myCargarTexturas("caust14.png");
	agua[15] = myCargarTexturas("caust15.png");

	//Arboles
	tronco = myCargarTexturas("tronco.jpg");
	hojas = myCargarTexturas("hojas.png");
	pantalones = myCargarTexturas("pantalones.jpg");

	//soldados
	armadura = myCargarTexturas("armadura.jpg");
	cara = myCargarTexturas("cara.jpg");

	//Luces
	//Sol
	glLightfv(GL_LIGHT1, GL_POSITION, luzPos_1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, valorCutOff);

	//myMovimiento();
	moverAgua();
	myMenu();
	myIluminacion();

	// cubo = myCubo(cielo);
	cuadrado = myCuadrado(hierba);
	cilindro = myCilindro();
	cono = myCono();
	rectangulo = myRectangulo();
	esfera = myEsfera();

	cabeza.px = cuerpo.px;
	cabeza.pz = cuerpo.pz;
	cabeza.lista_render = esfera;
	cabeza.textura = cara;
	brazo_izq.px = cuerpo.px - 5;
	brazo_izq.pz = cuerpo.pz;
	brazo_der.px = cuerpo.px + 5;
	brazo_der.pz = cuerpo.pz;
	cuerpo.textura = brazo_der.textura = brazo_izq.lista_render = armadura;
	pierna_izq.px = cuerpo.px - 2;
	pierna_izq.pz = cuerpo.pz;
	pierna_der.px = cuerpo.px + 2;
	pierna_der.pz = cuerpo.pz;
	brazo_izq.lista_render = brazo_der.lista_render = pierna_der.lista_render = pierna_izq.lista_render = cuerpo.lista_render = cilindro;
	pierna_der.textura = pierna_izq.textura = pantalones;
	protagonista.cabeza = cabeza;
	protagonista.cuerpo = cuerpo;
	protagonista.brazo_der = brazo_der;
	protagonista.brazo_izq = brazo_izq;
	protagonista.pierna_der = pierna_der;
	protagonista.pierna_izq = pierna_izq;

	// Empieza en bucle principal
	glutMainLoop();
	return 0;
}

void reshape(int width, int height) {
	W_WIDTH = width;
	W_HEIGHT = height;

	// Ajusta la vista a las dimensiones de la ventana
	glViewport(0, 0, width, height);

	// Reinicia el sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establece el volumen de trabajo
	gluPerspective(45.0f, (GLdouble)width / height, 1.0f, 500.0f);
}

void Idle() {
	glutPostRedisplay();
}
