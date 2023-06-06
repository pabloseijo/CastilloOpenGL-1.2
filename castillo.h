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

typedef struct {
	float px, py, pz; // posicion inicial
	float sx, sy, sz; // escalado en los 2 ejes
	int lista_render;
	int textura;
} arm;

typedef struct {
	float px, py, pz; // posicion inicial
	float sx, sy, sz; // escalado en los 2 ejes
	int lista_render;
	int textura;
} body;

typedef struct {
	float px, py, pz; // posicion inicial
	float sx, sy, sz; // escalado en los 2 ejes
	int lista_render;
	int textura;
} leg;

typedef struct {
	float px, py, pz; // posicion inicial
	float sx, sy, sz; // escalado en los 2 ejes
	int lista_render;
	int textura;
} head;

typedef struct {
	body cuerpo;
	head cabeza;
	arm brazo_izq, brazo_der;
	leg pierna_izq, pierna_der;
	float angulo_tras_x; // angulo giro eje x
	float angulo_tras_z; // angulo giro eje z
} personaje;

extern personaje protagonista;

void myCamara(int ancho, int alto);
void myTeclado(unsigned char tras, int x, int y);
void myTeclasespeciales(int cursor, int x, int y);

void dibujaAgua();
void moverAgua();
void dibujaProtagonista(personaje protagonista);
void terceraPersona(personaje protagonista);
void primeraPersona(personaje protagonista);

void myIluminacion();


#endif

