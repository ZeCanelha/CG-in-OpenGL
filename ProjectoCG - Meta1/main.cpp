//
//  main.cpp
//  ProjectoCG - Meta1
//
//  Created by Ze Canelha on 27/03/18.
//  Copyright © 2018 Ze Canelha. All rights reserved.
//

#include <iostream>
#include "main.h"



void inicializa()
{
    // Define a clear color
    
    glClearColor(WHITE);
    
    // Activar a profundidade
    
    glEnable(GL_DEPTH_TEST);
    
    // Carregar as texturas
    
    defineTextures();
    
    // Activar as texturas
    
    glEnable(GL_TEXTURE_2D);
    
    

}

void defineTextures()
{
  
    /* Textura do chão */
        
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("Textures/chao.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                    imag.GetNumCols(),
                    imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                    imag.ImageData());
    
      /* Textura das paredes */
    
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("Textures/parede.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    
}


void drawScene()
{
    
    // Desenhar a sala
    
    drawWalls();
    
    
}

void drawWalls()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    
    //CHAO
    glPushMatrix();
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,1.0f);        glVertex3f(  tam, 0, -tam );
    glTexCoord2f(1.0f,0.0f);        glVertex3f(  tam, 0,  tam );
    glTexCoord2f(0.0f,0.0f);     	glVertex3f( -tam, 0, tam );
    glTexCoord2f(0.0f,1.0f);     	glVertex3f( -tam, 0, -tam );
    glEnd();
    glPopMatrix();

    
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    
    //FRENTE
    glPushMatrix();
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,1.0f);    	glVertex3f(  tam, 0, -tam );
    glTexCoord2f(1.0f,0.0f);    	glVertex3f(  tam,  tam, -tam );
    glTexCoord2f(0.0f,0.0f);     	glVertex3f( -tam,  tam, -tam );
    glTexCoord2f(0.0f,1.0f);     	glVertex3f( -tam, 0, -tam );
    glEnd();
    glPopMatrix();
    
    //TRAS
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,1.0f);        glVertex3f(  tam, 0, tam );
    glTexCoord2f(1.0f,0.0f);        glVertex3f(  tam,  tam, tam );
    glTexCoord2f(0.0f,0.0f);     	glVertex3f( -tam,  tam, tam );
    glTexCoord2f(0.0f,1.0f);     	glVertex3f( -tam, 0, tam );
    glEnd();
    glPopMatrix();
    
    //DIREITA
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,1.0f);        glVertex3f( tam, 0, -tam );
    glTexCoord2f(1.0f,0.0f);        glVertex3f( tam,  tam, -tam );
    glTexCoord2f(0.0f,0.0f);     	glVertex3f( tam,  tam,  tam );
    glTexCoord2f(0.0f,1.0f);     	glVertex3f( tam, 0,  tam );
    glEnd();
    glPopMatrix();
    
    //ESQUERDA
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,1.0f);        glVertex3f( -tam, 0, tam );
    glTexCoord2f(1.0f,0.0f);        glVertex3f( -tam,  tam,  tam );
    glTexCoord2f(0.0f,0.0f);     	glVertex3f( -tam,  tam, -tam );
    glTexCoord2f(0.0f,1.0f);     	glVertex3f( -tam, 0, -tam );
    glEnd();
    glPopMatrix();
    
    //TOPO
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,1.0f);        glVertex3f(  tam,  tam,  tam );
    glTexCoord2f(1.0f,0.0f);        glVertex3f(  tam,  tam, -tam );
    glTexCoord2f(0.0f,0.0f);     	glVertex3f( -tam,  tam, -tam );
    glTexCoord2f(0.0f,1.0f);     	glVertex3f( -tam,  tam,  tam );
    glEnd();
    glPopMatrix();
    
    
    
    
}



void drawEixos()
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3i( 0, 0, 0);
    glVertex3i(10, 0, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3i(0,  0, 0);
    glVertex3i(0, 10, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3i( 0, 0, 0);
    glVertex3i( 0, 0,10);
    glEnd();
    
}


void display(void){
    
    // Apaga ecran/profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    
    
    //Definição do tipo de projecção
    
    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 3*zC);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1], obsPini[2],obsP[0],obsP[1],obsP[2] , 0, 1, 0);
   
    
    // Desenho da cena
    
    drawEixos();
    drawScene();
    glPopMatrix();
    
    
    
    
    // Substituir pelo novo buffer
    glutSwapBuffers();
}


void teclasNotAscii(int key, int x, int y){
    
    if(key == GLUT_KEY_UP) {
        obsPini[0]=obsPini[0]+incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT) {
        aVisao = (aVisao + 0.3) ;
        
    }
    if(key == GLUT_KEY_RIGHT) {
        aVisao = (aVisao - 0.3) ;
    }
    
    
    // Limites em Y
    
    if (obsPini[1] > tam)
    {
        obsPini[1] = tam;
        
    }
    if (obsPini[1] < -tam)
    {
        obsPini[1] = -tam;
    }
    
    // Limites em X
    
    if (obsPini[0] > tam )
    {
        obsPini[0] = tam;
    }
    if (obsPini[0] < -tam )
    {
        obsPini[0] = -tam;
    }
    
    // Limites em Z
    
    if (obsPini[2] > tam )
    {
        obsPini[2] = tam;
    }
    if (obsPini[2] < -tam )
    {
        obsPini[2] = -tam;
    }
    
    
    update_obs();

}

void update_obs()
{
    obsP[0] =obsPini[0]+rVisao*cos(aVisao);
    obsP[2] =obsPini[2]-rVisao*sin(aVisao);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    
    
    switch (key) {
                
        case '+':
            angZoom-=2;
            glutPostRedisplay();
            break;
        case '-':
            angZoom+=2;
            glutPostRedisplay();
            break;
        case 'q':
            obsPini[1]=obsPini[1]-incVisao;
            glutPostRedisplay();
            break;
        case 'w':
            obsPini[1]=obsPini[1]+incVisao;
            glutPostRedisplay();
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }
    
}


int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (300, 100);
    glutCreateWindow ("Luís Amaro; José Canelha; Meta2 - Iluminacao");
    
    inicializa();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    
    glutMainLoop();
    
    return 0;
}
