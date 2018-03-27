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
    
    glClearColor(BLACK);
    
    // Activar a profundidade
    
    glEnable(GL_DEPTH_TEST);
    
    // Atribuir os vértices
    
    glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Activar as normais
    
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
}

void drawScene()
{
    
    // Desenhar a sala
    
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
    
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
    
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
    
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
    
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
    

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
    gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0, 1, 0);
   
    
    // Desenho da cena
    
    drawEixos();
    drawScene();
    glPopMatrix();
    
    
    
    
    // Substituir pelo novo buffer
    glutSwapBuffers();
}


void teclasNotAscii(int key, int x, int y){
    
    if(key == GLUT_KEY_UP)
        obsP[1] = (obsP[1]+ 0.1) ;
    if(key == GLUT_KEY_DOWN)
        obsP[1] = (obsP[1]- 0.1) ;
    
    if (obsP[1]>yC)
        obsP[1]=yC;
    if (obsP[1]<-yC)
        obsP[1]=-yC;
    
    if(key == GLUT_KEY_LEFT)
        aVisao = (aVisao + 0.1) ;
    if(key == GLUT_KEY_RIGHT)
        aVisao = (aVisao - 0.1) ;
    
    obsP[0]=rVisao*cos(aVisao);
    obsP[2]=rVisao*sin(aVisao);
    
    
    glutPostRedisplay();
    
}

void keyboard(unsigned char key, int x, int y){
    
    
    switch (key) {
                
        case 'A':
        case 'a':
            x_inc-=1;
            glutPostRedisplay();
            break;
            
        case 'S':
        case 's':
            x_inc+=1;
            glutPostRedisplay();
            break;
            
        case 'e':
        case 'E':
            ang_inc+=2;
            glutPostRedisplay();
            break;
            
        case 'd':
        case 'D':
            ang_inc-=2;
            glutPostRedisplay();
            break;
        case 'z':
        case 'Z':
            coordZ+=1;
            glutPostRedisplay();
            break;
        case '+':
            angZoom-=2;
            glutPostRedisplay();
            break;
        case '-':
            angZoom+=2;
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
    glutCreateWindow ("Luís Amaro; José Canelha; Meta1 - Coordenadas");
    
    inicializa();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    
    glutMainLoop();
    
    return 0;
}
