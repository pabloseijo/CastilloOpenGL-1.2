#include <windows.h>	//Inclusion de variables de windows
#include <glut.h>	//Inclusion de GLUT mira que la tienes ahi
#include <GL/gl.h>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	
#include "castillo.h"


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

float Rot = 0;
camara = 0;
sueloScale = 25;
int cuadrado = 0, cono = 0, cilindro = 0, rectangulo = 0;

const int SLICES = 32;
const int STACKS = 32;

void Idle();
void reshape(int width, int height);

//Texturas paisaje
int hierba = 0, tejado = 0;

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
	}
	glutPostRedisplay();
}

//Creo el menu
void myMenu(void) {
	int menuFondo = 0;

	menuFondo = glutCreateMenu(onMenu);

	glutAddMenuEntry("Voyayer", 1); //La sonda que nos muestra todo el sistema
	glutAddMenuEntry("Cubo", 2);

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

//Lista del cuadrado
int myCuadrado() {
	int indice;
	indice = glGenLists(1);
	glNewList(indice, GL_COMPILE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 0.5);

	glBegin(GL_TRIANGLES);

	glVertex3f(0, 0, -0.5f);
	glVertex3f(1, 0, -0.5f);
	glVertex3f(1, 1, -0.5f);

	glVertex3f(1, 1, -0.5f);
	glVertex3f(0, 1, -0.5f);
	glVertex3f(0, 0, -0.5f);

	glEnd();

	glEndList();
	return indice;
}

//Lista del cono
int myCono() {
	int indice = glGenLists(1);
	glNewList(indice, GL_COMPILE);
	glEnable(GL_BLEND);
	glColor3f(0, 0, 1);

	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	glPushMatrix();
	gluCylinder(quadric, 0.0f, 1.0f, 1.0f, SLICES, STACKS);
	glPopMatrix();

	gluDeleteQuadric(quadric);
	glEndList();
	return indice;
}

//Lista del Cilindro
int myCilindro() {
	int indice = glGenLists(1);
	glNewList(indice, GL_COMPILE);
	glEnable(GL_BLEND);
	glColor3f(1, 0, 0);

	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

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

	glColor3f(0, 1, 0);

	glBegin(GL_TRIANGLES);
	//CUADRADO 1
	glVertex3f(.5f, -.5f, -.5f);
	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(.5f, .5f, -.5f);
	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(.5f, .5f, -.5f);

	//CUADRADO 2
	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(.5f, -.5f, .5f);
	glVertex3f(.5f, .5f, .5f);
	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(.5f, .5f, .5f);

	//CUADRADO 3
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(-.5f, -.5f, -.5f);

	//CUADRADO 4
	glVertex3f(.5f, -.5f, -.5f);
	glVertex3f(.5f, .5f, -.5f);
	glVertex3f(.5f, .5f, .5f);
	glVertex3f(.5f, .5f, .5f);
	glVertex3f(.5f, -.5f, .5f);
	glVertex3f(.5f, -.5f, -.5f);

	//CUADRADO 5
	glVertex3f(.5f, -.5f, -.5f);
	glVertex3f(.5f, -.5f, .5f);
	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(.5f, -.5f, -.5f);

	//CUADRADO 6
	glVertex3f(.5f, .5f, .5f);
	glVertex3f(.5f, .5f, -.5f);
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(.5f, .5f, .5f);

	glEnd();
	glEndList();
	return indice;
}
//Funcion para dibujar el suelo
void dibujaSuelo() {

	glColor3f(1, 0, 0);
	for (int i = -500; i <= 500; i += sueloScale)
		for (int j = -500; j <= 500; j += sueloScale) {
			glPushMatrix();
				glTranslatef(i, 0, j);
				glScalef(sueloScale, sueloScale, sueloScale);
				glRotatef(-90.0f, 1, 0, 0);
				glBindTexture(GL_TEXTURE_2D, hierba);
				glCallList(cuadrado);
			glPopMatrix();
		}

	glPushMatrix();
		glTranslatef(50, -25, 0);
		glScalef(50, 50, 1);
		glColor4f(1, 1, 1, 0.5);
	glPopMatrix();

}

void dibujaMuros() {
	//Muro Frontal 
	glPushMatrix();
	glTranslatef(0, 0, 100);
	glScalef(175, 50, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Muro Lateral Izq
	glPushMatrix();
	glTranslatef(-100, 0, 0);
	glRotatef(-90.0f, 0, 1, 0);
	glScalef(175, 50, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Muro Lateral Dcho
	glPushMatrix();
	glTranslatef(100, 0, 0);
	glRotatef(-90.0f, 0, 1, 0);
	glScalef(175, 50, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();

	//Muro Trasero 
	glPushMatrix();
	glTranslatef(0, 0, -100);
	glScalef(175, 50, 20);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(rectangulo);
	glPopMatrix();
}

void dibujaTorre() {

	//Torre frontal 1: paredes
	glPushMatrix();
	glTranslatef(100, -25, 100);
	glScalef(25, 100, 25);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(cilindro);
	glPopMatrix();

	//Torre frontal 1: tejado
	glPushMatrix();
	glTranslatef(100, 100, 100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glPopMatrix();

	//Torre frontal 2: paredes
	glPushMatrix();
	//traslado 200 en el eje x
	glTranslatef(-100, -25, 100);
	glScalef(25, 100, 25);
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(cilindro);
	glPopMatrix();

	//Torre frontal 2: tejado
	glPushMatrix();
	glTranslatef(-100, 100, 100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glPopMatrix();

	//Torre trasera 1:paredes
	glPushMatrix();
	glTranslatef(100, -25, -100);
	glScalef(25, 100, 25);
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(cilindro);
	glPopMatrix();

	//Torre trasera 1: tejado
	glPushMatrix();
	glTranslatef(100, 100, -100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
	glPopMatrix();

	//Torre trasera 2: paredes
	glPushMatrix();
	glTranslatef(-100, -25, -100);
	glScalef(25, 100, 25);
	glRotatef(-90.0f, 1, 0, 0);
	glCallList(cilindro);
	glPopMatrix();

	//Torre trasera 2: tejado
	glPushMatrix();
	glTranslatef(-100, 100, -100);
	glScalef(35, 35, 35);
	//Lo roto para ponerlo de pie
	glRotatef(90.0f, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tejado);
	glCallList(cono);
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


	myCamara(W_WIDTH, W_HEIGHT);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Matriz del Modelo
	glLoadIdentity(); // Inicializamos la matriz del modelo a la identidad
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	dibujaSuelo();
	dibujaTorre();
	dibujaMuros();
	myEjes();
	glScalef(.5f, .5f, .5f);

	glFlush();
	glutSwapBuffers();


}

int myTexturas(char* nombre) {

	GLint textura;

	//load and create a texture
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(nombre, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else { printf("algo ha fallado"); }

	stbi_image_free(data);

	printf("%d", textura);
	return textura;

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
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_ALPHA_TEST);

	hierba = myTexturas("hierba.jpg");
	tejado = myTexturas("roof.jpg");

	myCamara(W_WIDTH, W_HEIGHT);
	//myMovimiento();
	myMenu();
	cuadrado = myCuadrado();
	cilindro = myCilindro();
	cono = myCono();
	rectangulo = myRectangulo();

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
