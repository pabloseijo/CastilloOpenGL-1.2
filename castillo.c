#include <windows.h>	//Inclusion de variables de windows

#include <glut.h>	//Inclusion de GLUT
#include <GL/gl.h>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	
#include "castillo.h"



float alpha = 0;
float beta = 0;




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

void primeraPersona(personaje protagonista) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)W_WIDTH / (float)W_HEIGHT, .1, 2500.0);
	gluLookAt(protagonista.cabeza.px + 10, protagonista.cabeza.py + 30, protagonista.cabeza.pz + 10,
		protagonista.cabeza.px + cos(protagonista.angulo_tras_x * PI / 180.0) + 10, 20 + sin(protagonista.angulo_tras_x * PI / 180.0), protagonista.cabeza.pz + sin(protagonista.angulo_tras_x * PI / 180.0) + 10,
		0.0, 1.0, 0.0);
}

void terceraPersona(personaje protagonista) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)W_WIDTH / (float)W_HEIGHT, .1, 2500.0);
	gluLookAt(protagonista.cabeza.px - 150 * cos(protagonista.angulo_tras_x * PI / 180.0), protagonista.cabeza.py + 150, protagonista.cabeza.pz - 150 * sin(protagonista.angulo_tras_x * PI / 180.0),
		protagonista.cabeza.px + cos(protagonista.angulo_tras_x * PI / 180.0), protagonista.cabeza.py, protagonista.cabeza.pz + sin(protagonista.angulo_tras_x),
		0.0, 1.0, 0.0);
}

void dibujaProtagonista(personaje protagonista) {
	//Piernas
	glPushMatrix();
	glTranslatef(protagonista.pierna_der.px - 2, -30, protagonista.pierna_der.pz - 2);
	glScalef(1.5, 12, 1.5);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glRotatef(protagonista.angulo_tras_x, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, protagonista.pierna_der.textura);
	glCallList(protagonista.pierna_der.lista_render);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	//Piernas
	glPushMatrix();
	glTranslatef(protagonista.pierna_izq.px + 2, -30, protagonista.pierna_izq.pz);
	glScalef(1.5, 12, 1.5);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glRotatef(protagonista.angulo_tras_x, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, protagonista.pierna_izq.textura);
	glCallList(protagonista.pierna_izq.lista_render);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	//Tronco
	glPushMatrix();
	glTranslatef(protagonista.cuerpo.px, -22, protagonista.cuerpo.pz);
	glScalef(4, 12, 4);
	//Lo roto para ponerlo de pie
	glRotatef(-90.0f, 1, 0, 0);
	glRotatef(protagonista.angulo_tras_x, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, protagonista.cuerpo.textura);
	glCallList(protagonista.cuerpo.lista_render);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Brazos
	glPushMatrix();
		glTranslatef(protagonista.brazo_der.px - 5, -20, protagonista.brazo_der.pz);
		glScalef(1, 7, 1);
		//Lo roto para ponerlo de pie
		glRotatef(-90.0f, 1, 0, 0);
		glRotatef(protagonista.angulo_tras_x, 0.0, 0.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, protagonista.brazo_der.textura);
		glCallList(protagonista.brazo_der.lista_render);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Brazos
	glPushMatrix();
		glTranslatef(protagonista.brazo_izq.px + 5, -20, protagonista.brazo_izq.pz);
		glScalef(1, 7, 1);
		//Lo roto para ponerlo de pie
		glRotatef(-90.0f, 1, 0, 0);
		glRotatef(protagonista.angulo_tras_x, 0.0, 0.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, protagonista.brazo_izq.textura);
		glCallList(protagonista.brazo_izq.lista_render);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	//Cabeza
	glPushMatrix();
	glTranslatef(protagonista.cabeza.px, -6, protagonista.cabeza.pz);
	glScalef(6, 6, 6);
	//
	glRotatef(122.5f, 0, 1, 0);
	//Lo roto para ponerlo de pie
	glRotatef(180.0f, 1, 0, 0);
	glRotatef(protagonista.angulo_tras_x, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, protagonista.cabeza.textura);
	glCallList(protagonista.cabeza.lista_render);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void myTeclado(unsigned char tras, int x, int y)
{
	switch (tras) {
	case 's':
		// Mueve la grúa hacia atrás
		break;
	case 'w':
		// Mueve la grúa hacia delante
		protagonista.cuerpo.px += cos(protagonista.angulo_tras_x * PI / 180.0f);
		protagonista.cuerpo.pz += sin(protagonista.angulo_tras_x * PI / 180.0f);
		
		protagonista.cabeza.px += cos(protagonista.angulo_tras_x * PI / 180.0f);
		protagonista.cabeza.pz += sin(protagonista.angulo_tras_x * PI / 180.0f);

		protagonista.brazo_der.px += cos(protagonista.angulo_tras_x * PI / 180.0f);
		protagonista.brazo_der.pz += sin(protagonista.angulo_tras_x * PI / 180.0f);

		protagonista.brazo_izq.px += cos(protagonista.angulo_tras_x * PI / 180.0f);
		protagonista.brazo_izq.pz += sin(protagonista.angulo_tras_x * PI / 180.0f);

		protagonista.pierna_der.px += cos(protagonista.angulo_tras_x * PI / 180.0f);
		protagonista.pierna_der.pz += sin(protagonista.angulo_tras_x * PI / 180.0f);

		protagonista.pierna_izq.px += cos(protagonista.angulo_tras_x * PI / 180.0f);
		protagonista.pierna_izq.pz += sin(protagonista.angulo_tras_x * PI / 180.0f);
		break;
	case 'a':
		protagonista.angulo_tras_x++;
		break;
	case 'd':
		protagonista.angulo_tras_x--;
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
	glutTimerFunc(1000, moverAgua, 0); // aumentar el tiempo a 300 ms
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