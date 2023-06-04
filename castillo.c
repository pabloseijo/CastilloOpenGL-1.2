#include <windows.h>	//Inclusion de variables de windows

#include <glut.h>	//Inclusion de GLUT
#include <GL/gl.h>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	
#include "castillo.h"



float alpha = 0;
float beta = 0;



//void myCamara(GLint W, GLint H) {
//		
//	//Configuración de la matriz de proyeccion
//	glMatrixMode(GL_PROJECTION);
//	//La ponemos auno
//	glLoadIdentity();
//
//	////Ajusta la vista a las dimensiones de la ventana
//	glViewport(0, 0, W_WIDTH, W_HEIGHT);
//
//	//glOrtho(-1.0,1.0f,-1.0,1.0f,1.0,10.0f);  
//	gluPerspective(30.0,(float)W_WIDTH / W_HEIGHT, 1.0, 5000.0f);
//	gluLookAt(((float)DISTANCIA*(float) sin(alpha)*cos(beta)),((float)DISTANCIA*(float) sin(beta)), ((float)DISTANCIA*cos(alpha)*cos(beta)), 0,0,0,0,1,0);  
//
//}


void myCamara(int ancho, int alto) {

	//Configuración de la matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	//La ponemos a uno
	glLoadIdentity();
	//Se pone una proyeccion ortografica, especificando que se verá desde -200 a la izquierda hasta 200 a la derecha, desde -200 hacia abajo hasta 200 hacia arriba y desde 1 como muy cerca hasta 2000 a lo lejos
	//glOrtho(-200.0,200.0f,-200.0,200.0f,1.0,2000.0f);
	gluPerspective(45.f, (float)ancho / (float)alto, 1.0, 2500);
	//La camara se coloca segunlos valores de alpha y beta, a 1000 de distancia, cambiando al pulsar las flechas, mirando hacia el centro con la camara orientada sobre el eje Y

	gluLookAt(((float)DISTANCIA * (float)sin(alpha) * cos(beta)), ((float)DISTANCIA * (float)sin(beta)) + 100, ((float)DISTANCIA * cos(alpha) * cos(beta)), 0, 10, 0, 0, 1, 0);

}

void myTelescopio(float distancia, float angulo, float distanciaObj, float anguloObj) {

	//Configuracion de la matriz de proyeccion
	glMatrixMode(GL_PROJECTION);

	//La ponemos a uno
	glLoadIdentity();
	gluPerspective(45.0, (float)W_WIDTH / W_HEIGHT, 1.0, 2000.0f);
	gluLookAt(distancia * cos(angulo * PI / 180.0), 0, -1 * distancia * sin(angulo * PI / 180.0),
		distanciaObj * cos(anguloObj * PI / 180.0), 0, -1 * distanciaObj * sin(anguloObj * PI / 180.0),
		0, 1, 0);
}

void myTelescopioSatelite(float distancia, float angulo, float distanciaObj, float anguloObj) {

	//Configuración de la matriz de proyección
	glMatrixMode(GL_PROJECTION);

	//La ponemos a uno
	glLoadIdentity();

	//Calculamos la posición de la luna en coordenadas cartesianas
	float PosicionLunaX = distancia * cos(angulo * (PI / 180.0)) + distanciaObj * cos(anguloObj * (PI / 180.0) + angulo * (PI / 180.0));
	float PosicionLunaZ = distancia * sin(angulo * (PI / 180.0)) + distanciaObj * sin(anguloObj * (PI / 180.0) + angulo * (PI / 180.0));

	//Configuramos la matriz de proyección con la perspectiva y la matriz de vista con la posición de la cámara y la luna
	gluPerspective(45.0, (float)W_WIDTH / W_HEIGHT, 1.0, 2000.0f);
	gluLookAt(distancia * cos(angulo * (PI / 180.0)), 0, -1 * distancia * sin(angulo * (PI / 180.0)),
		PosicionLunaX, 0, -1 * PosicionLunaZ,
		0, 1, 0);
}

void myTeclado(unsigned char tras, int x, int y)
{
	switch (tras) {
	case 'l':

		break;
	case 'c':
		break;
	case 'r':
		break;
	case 'p':

		break;
	case 'o':
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;
	case 'i':
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	case 'z':
		valorCutOff++;
		break;
	case 'x':
		valorCutOff--;
		break;

	default:
		break;
	}
	// Se se modificou algo redebúxase
	glutPostRedisplay();
}

/**************************************
FUNCION DE CONTROL DE TECLAS ESPECIAIS:
**************************************
*/
void myTeclasespeciales(int cursor, int x, int y)
{
	switch (cursor)
	{
		//Traslaciones:
	case GLUT_KEY_F1:
		break;
	case GLUT_KEY_F2:

		break;
	case GLUT_KEY_F3:

		break;
	case GLUT_KEY_F4:
		break;
	case GLUT_KEY_F5:

		break;
	case GLUT_KEY_F6:

		break;
		//Giros:
	case GLUT_KEY_UP:
		beta += INCREMENTO;
		break;
	case GLUT_KEY_DOWN:
		beta -= INCREMENTO;
		break;
	case GLUT_KEY_RIGHT:
		alpha -= INCREMENTO;
		break;
	case GLUT_KEY_LEFT:
		alpha += INCREMENTO;
		break;
	default:
		break;
	}

	if (alpha >= PI * 2.0 && alpha <= 0) alpha = 0;
	if (beta >= PI * 2.0 && beta <= 0) beta = 0; //hay que repasarlo para evitar el salto


	glutPostRedisplay();
}

void moverAgua() {
	agua_indice++;
	if (agua_indice == 15)
		agua_indice = 0;
	glutPostRedisplay();
	glutTimerFunc(300, moverAgua, 0); // aumentar el tiempo a 300 ms
}

void dibujaAgua() {

	glPushMatrix();

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	/*printf("Agua = %d", agua_indice);*/

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua[agua_indice]);

	glRotatef(-90, 1, 0, 0);
	glTranslatef(200, -250, 8);
	glScalef(200, 200, 1);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, -0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -0.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void myIluminacion() {
	// primera luz
	GLfloat ambient_0[4] = { 0.5f, 0.5f,0.5f, 1.0f };
	GLfloat diffuse_0[4] = { 0.3f, 0.3f,0.3f, 1.0f };
	GLfloat specular_0[4] = { 0.0f, 0.0f,0.0f, 1.0f };
	GLfloat luzPos_0[4] = { 0.0f, 0.0f,100.0f, 1.0f };

	glEnable(GL_NORMALIZE);
	// definimos la luz GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_0);
	glLightfv(GL_LIGHT0, GL_POSITION, luzPos_0);


	// definimos la luz GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_1);
	glLightfv(GL_LIGHT1, GL_POSITION, luzPos_1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir_1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	printf("Hola");
}