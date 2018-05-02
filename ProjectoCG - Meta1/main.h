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
#define PI		 3.14159
#define SIZE_W   2
#define SIZE_P   2
#define MAX_SIZE 5
#define FLOOR    0
#define WALL     1
#define PAINT1   2
#define PAINT2   3



// Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

//Variáveis globais

GLfloat tam = 10;
GLint camera_no = 0;

//Textures


GLuint texture[10];
GLuint  tex;
RgbImage imag;

// Iluminação

GLint   noite=1;
GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0};

// --- Lampada dentro da sala ---

GLint   ligaLuz=1;

GLfloat localCor[4] ={0.2,0.3,0.2,1.0};
GLfloat localCorDif[4] ={ 1.0, 0.6f, 0.25f, 1.0};
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat localPos[4] ={xC/2, 10.0, xC/2, 0};
GLfloat localAttCon =1.0;
GLfloat localAttLin =0.05;
GLfloat localAttQua =0.0;

// --- Foco 1 -> Apontar para um quadro ----
GLint    liga_foco = 1;

GLfloat Pos1[]= {0, 1, -tam  };
GLfloat	anguloFoco= 15.0;

GLfloat Foco_direccao[]	= { 0, 0, -1   };	//=== X
GLfloat Foco1_cor[]		= { YELLOW };	//=== Cor da luz 1
GLfloat Foco_ak			= 1.0;
GLfloat Foco_al			= 0.05f;
GLfloat Foco_aq			= 0.0f;
GLfloat Foco_Expon		= 2.0;		// Foco, SPOT_Exponent




// Variáveis do observador
// Posição do observador

GLfloat xObs = 0, yObs = 5, zObs = 0;


GLfloat  rVisao=8, aVisao=0.5*PI, incVisao=0.15;

GLfloat  obsPini[] ={xObs,yObs, zObs};

GLfloat  obsP[] = {static_cast<GLfloat>(obsPini[0]-rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2]-rVisao*sin(aVisao))};

GLfloat coordZ;
GLfloat angZoom=90;
GLfloat incZoom=3;
GLfloat x_inc = 0;
GLfloat ang_inc = 0;






// Functions

void drawLata();
void drawScene();
void drawWalls(GLint texture_n, int w_size, int block, int a );
void defineTextures();
void update_obs();
void init_lights();
void draw_paintings(GLfloat widht, GLfloat height, GLfloat width, GLint text);
void draw_stand(int a , int b, int h, int z_size, int x);

#endif /* main_h */
