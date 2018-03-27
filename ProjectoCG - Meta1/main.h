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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159


//Variáveis globais

// Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

// Variáveis do observador
GLfloat  rVisao=10, aVisao=0.5*PI, incVisao=0.05;
GLfloat  obsP[] ={static_cast<GLfloat>(rVisao*cos(aVisao)), 3.0, static_cast<GLfloat>(rVisao*sin(aVisao))};
GLfloat coordZ;
GLfloat angZoom=90;
GLfloat incZoom=3;
GLfloat x_inc = 0;
GLfloat ang_inc = 0;


GLfloat tam = 2;

static GLuint cima[] = {8,11, 10,  9};
static GLuint esquerda[] = {0,1,2,3};
static GLuint direita [] = {4,7,6,5};
static GLuint baixo [] = {12,15,14,13};


// Definição dos vertices da sala
// A colocação da ordem dos vertices é de acordo com a face visivel

static GLfloat vertices[]={
    //…………………………………………………………………………………………………… x=tam (Esquerda)
    -tam,  -tam,  tam,	// 0
    -tam,   tam,  tam,	// 1
    -tam,   tam, -tam,	// 2
    -tam,  -tam, -tam,	// 3
    //…………………………………………………… Direita
    tam,  -tam,  tam,	// 4
    tam,   tam,  tam,	// 5
    tam,   tam, -tam,	// 6
    tam,  -tam, -tam,	// 7
    //……………………………………………………… (Cima
    -tam,  tam,  tam,	// 8
    -tam,  tam, -tam,	// 9
    tam,  tam, -tam,	// 10
    tam,  tam,  tam,	// 11
    //……………………………………………………… (Baixo)
    -tam,  -tam,  tam,	// 12
    -tam,  -tam, -tam,	// 13
    tam,  -tam, -tam,	// 14
    tam,  -tam,  tam,	// 15

    
    //……………………………………………………… (Frente)
    //……………………………………………………… (Tras)
};

//Definição das normais da sala

static GLfloat normais[] = {
    //…………………………………………………………………………………………………… x=tam (Esquerda)
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    //…………………………………………………………………………………………………… x=tam (Direita)
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    //…………………………………………………………………………………………………… y=tam (Cima)
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    //……………………………………………………… y = -tam(Baixo)
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    
    //……………………………………………………… (Frente)
    //……………………………………………………… (Tras)

    
};


#endif /* main_h */
