#ifndef CASTILLO_H
#define CASTILLO_H

#define INCREMENTO .01
#define DISTANCIA 750
#define PI 3.1416
//Milisegundos que tarda en redibujar
#define MYTIEMPO 41

extern unsigned int W_HEIGHT, W_WIDTH;
extern int agua[16];
extern int agua_indice;
extern int valorCutOff;
// GL_LIGHT1

extern GLfloat ambient_1[4];
extern GLfloat diffuse_1[4];
extern GLfloat specular_1[4];
extern GLfloat luzPos_1[4];
extern GLfloat spotDir_1[3];
extern GLfloat specRef_1[4];

void myCamara(int ancho, int alto);
void myTeclado(unsigned char tras, int x, int y);
void myTeclasespeciales(int cursor, int x, int y);

void dibujaAgua();
void moverAgua();

void myIluminacion();


#endif

