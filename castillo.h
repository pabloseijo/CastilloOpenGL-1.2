#ifndef CASTILLO_H
#define CASTILLO_H

#define INCREMENTO .01
#define DISTANCIA 1000
#define PI 3.1416
//Milisegundos que tarda en redibujar
#define MYTIEMPO 41

extern unsigned int W_HEIGHT, W_WIDTH;


void myCamara(int ancho, int alto);
void myTeclado(unsigned char tras, int x, int y);
void myTeclasespeciales(int cursor, int x, int y);


#endif

