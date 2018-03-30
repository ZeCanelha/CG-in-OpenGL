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

GLfloat tam = 10;
GLint camera_no = 0;

// Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

// Variáveis do observador
// Posição das cameras na sala.
const GLfloat cameras [4][3] = {
    {-tam,tam,tam},
    {-tam,tam,-tam},
    {tam,tam,-tam},
    {tam,tam,tam}
    
};

GLfloat  rVisao=8, aVisao=0.5*PI, incVisao=0.05;
GLfloat  obsP[] ={static_cast<GLfloat>(cameras[camera_no][0] - rVisao*cos(aVisao)), cameras[camera_no][1] , static_cast<GLfloat>(cameras[camera_no][0] - rVisao*sin(aVisao))};
GLfloat coordZ;
GLfloat angZoom=90;
GLfloat incZoom=3;
GLfloat x_inc = 0;
GLfloat ang_inc = 0;




static GLuint cima[] = {8,11, 10,  9};
static GLuint esquerda[] = {0,1,2,3};
static GLuint direita [] = {4,7,6,5};
static GLuint baixo [] = {12,15,14,13};
static GLuint frente[] = {16,19,18,17};
static GLuint tras [] = {20,23,22,21};


// Definição dos vertices da sala
// A colocação da ordem dos vertices é de acordo com a face visivel

static GLfloat vertices[]={
    //…………………………………………………………………………………………………… x=tam (Esquerda)
    -tam,   0,  tam,	// 0
    -tam,   tam,  tam,	// 1
    -tam,   tam, -tam,	// 2
    -tam,   0, -tam,	// 3
    //…………………………………………………… Direita
    tam,    0,  tam,	// 4
    tam,   tam,  tam,	// 5
    tam,   tam, -tam,	// 6
    tam,    0, -tam,	// 7
    //……………………………………………………… (Cima
    -tam,  tam,  tam,	// 8
    -tam,  tam, -tam,	// 9
    tam,  tam, -tam,	// 10
    tam,  tam,  tam,	// 11
    //……………………………………………………… (Baixo)
    -tam,   0,  tam,	// 12
    -tam,   0, -tam,	// 13
    tam,    0, -tam,	// 14
    tam,    0,  tam,	// 15
    //……………………………………………………… (Frente)
    -tam,   0, tam,     //16
    -tam, tam, tam,     //17
    tam, tam, tam,      //18
    tam,    0, tam,     //19
    //……………………………………………………… (Tras)
    -tam,   0, -tam,    //20
    -tam, tam, -tam,    //21
    tam, tam, -tam,     //22
    tam,    0, -tam,    //23
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
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    //……………………………………………………… (Tras)
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,

    
};


#endif /* main_h */
