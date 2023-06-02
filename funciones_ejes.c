#include <windows.h>	//Inclusion de variables de windows

#include <glut.h>	//Inclusion de GLUT
#include <GL/gl.h>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	

#define INCREMENTO .01
#define DISTANCIA 3000
#define PI 3.1416

float alpha = 0;
float beta = 0;

extern int W_HEIGHT, W_WIDTH;

void myCamara(GLint W, GLint H) {
		
	//Configuración de la matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	//La ponemos auno
	glLoadIdentity();

	////Ajusta la vista a las dimensiones de la ventana
	glViewport(0, 0, W_WIDTH, W_HEIGHT);

	//glOrtho(-1.0,1.0f,-1.0,1.0f,1.0,10.0f);  
	gluPerspective(30.0,(float)W_WIDTH / W_HEIGHT, 1.0, 5000.0f);
	gluLookAt(((float)DISTANCIA*(float) sin(alpha)*cos(beta)),((float)DISTANCIA*(float) sin(beta)), ((float)DISTANCIA*cos(alpha)*cos(beta)), 0,0,0,0,1,0);  

}


void myTelescopio (float distancia, float angulo, float distanciaObj, float anguloObj) {

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

void myTeclado(unsigned char tras,int x,int y)
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
 void myTeclasespeciales(int cursor,int x,int y) 
{
	switch(cursor) 
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
			beta+=INCREMENTO;
			break;
		case GLUT_KEY_DOWN:
			beta-=INCREMENTO;
			break;
		case GLUT_KEY_RIGHT:
			alpha-=INCREMENTO;
			break;
		case GLUT_KEY_LEFT:
			alpha+=INCREMENTO;
			break;
		default:
			break;
	}

	if(alpha>=PI*2.0 && alpha<=0 ) alpha=0;
	if(beta>=PI*2.0 && beta<=0 ) beta=0; //hay que repasarlo para evitar el salto


		glutPostRedisplay();
}
