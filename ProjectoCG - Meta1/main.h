//
//  main.h
//  ProjectoCG - Meta1
//
//  Created by Ze Canelha on 27/03/18.
//  Copyright © 2018 Ze Canelha. All rights reserved.
//

#ifndef main_h
#define main_h

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "RgbImage.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define WHITE_A  1.0, 1.0, 1.0, 0.3
#define BLACK    0.0, 0.0, 0.0, 1.0
#define BROWN    0.87, 0.72, 0.52, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.93, 0.93, 0.93, 1.0
#define ORANGE   1.0, 0.6, 0.25, 1.0
#define PI		 3.14159
#define SIZE_W   2
#define SIZE_P   2
#define MAX_SIZE 5
#define FLOOR    0
#define WALL     1
#define CAN      2
#define CAN2     5
#define CAN3     6

#define MAX_PARTICLES 10000

GLfloat tam = 10;

// Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

//Variáveis globais



int loop;
float slowdown = 0.95;
float speed = 0.0;
bool isRaining;


typedef struct
{
    float   size;
    float   life;
    float   fade;
    float   r,g,b;
    float   x,y,z;
    float   vel;
    float   gravity;
}Particle;

Particle particles[MAX_PARTICLES];


GLint camera_no = 0;
GLUquadricObj * y =  gluNewQuadric();

GLfloat s_height[3] = {4,4,4};

// Nevoeiro

GLfloat nevoeiroCor[] = {0.75, 0.75, 0.75, 1.0}; //definicao da cor do nevoeiro
GLfloat density = 0.05;
bool fog = false;

// Stand azul

bool lift = false;
bool lift_d = false;

// Stand meio

bool lift_1 = false;
bool lift_d_1 = false;

// Stand canto

bool lift_2 = false;
bool lift_d_2 = false;


// BONECO

GLuint tuxedo1Textures[2];
int flag = 1;
int vBB1 = 9.5, vBB2 = 0.0, vBB3 = 0 ,
vBB4 = 6.5, vBB5 = 0.0, vBB6 = 0,
vBB7 = 6.5, vBB8 = 5.0, vBB9 = 0,
vBB10 = 9.5,vBB11 = 5.0,vBB12 = 0;

int vCB1 = 9.5, vCB2 = 5.0, vCB3 = 0 ,
vCB4 = 6.5, vCB5 = 5.0, vCB6 = 0,
vCB7 = 6.5, vCB8 = 7.0, vCB9 = 0,
vCB10 = 9.5,vCB11 = 7.0,vCB12 = 0;

int cabecaBonecoX = 3, cabecaBonecoY = 6.0, cabecaBonecoZ = -8;


GLfloat rotate_inc = 0;
GLfloat rotate_inc_r = 0;
//Textures

GLuint texture[20];
GLuint  tex;
RgbImage imag;

// Iluminação

GLint   noite=1;
GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0};

// --- Lampada dentro da sala ---

GLint   ligaLuz=0;



// Variáveis do observador
// Posição do observador

GLfloat xObs = 0, yObs = 5, zObs = 0;


GLfloat  rVisao=8, aVisao=0.5*PI, incVisao=0.45;

GLfloat  obsPini[] ={xObs,yObs, zObs};

GLfloat  obsP[] = {static_cast<GLfloat>(obsPini[0]-rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2]-rVisao*sin(aVisao))};

GLfloat coordZ;
GLfloat angZoom=90;
GLfloat incZoom=3;
GLfloat x_inc = 0;
GLfloat ang_inc = 0;


char     texto[30];



// Functions

void drawLata();
void drawScene();
void drawWalls(GLint texture_n, int w_size, int block, int a );
void defineTextures();
void update_obs();
void init_lights();
void draw_stand(int a , int b, int h, int z_size, int x, int stand_n);
void draw_can(int,int);
void timer_func(int a);
void draw_sala();
void draw_outside_wall();
void draw_window();
void init_particles(int );
void draw_rain();
void drawHeads();
void drawTuxedos();
void draw_painting(int , int , int );
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z);

#endif /* main_h */
