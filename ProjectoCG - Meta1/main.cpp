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
    gluQuadricNormals(y, GLU_SMOOTH);
    gluQuadricTexture(y, GL_TRUE);
    
    // Define a clear color
    
    glClearColor(WHITE);
    
    // Activar a profundidade;
    glEnable(GL_DEPTH_TEST);
    // Activar as normais
    glEnable(GL_NORMALIZE);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    
    // Carregar as texturas
    
    defineTextures();
    
    // Activar as texturas
    
    glEnable(GL_TEXTURE_2D);
    
    // Inicializar a iluminação
    
    init_lights();
    
    // Chuva
    
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        init_particles(loop);
    }
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    
    
}

void init_particles(int i)
{
    particles[i].life = 1.0f;
    particles[i].fade = float(rand()%100)/1000.0f+0.003f;
    
    // Posição
    
    particles[i].x = (float) -(xC * 3 ) + (rand() % 45) ;
    particles[i].y = 25.0f;
    particles[i].z = (float) -(xC * 3 ) + (rand() % 45) ;
    
    particles[i].r = 1.0f;
    particles[i].g = 1.0f;
    particles[i].b = 1.0f;
    
    particles[i].vel = speed;
    particles[i].gravity = -0.8;//-0.8;
}

void draw_rain() {
    float x, y, z;
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+1) {
        if (particles[loop].life > 0.0f) {
            x = particles[loop].x;
            y = particles[loop].y;
            z = particles[loop].z;
            
            
            if ( (x > -(xC+0.1) and x < (xC+0.1) ) and ((z > -(xC+0.1) and z < (xC+0.1) )) )
            {
                init_particles(loop);
                continue;
            }
        
            
            
            
            // Draw particles
            glLineWidth(1);
            glColor4f(1.0,1.0,1.0,1.0);
            glBegin(GL_LINES);
            glVertex3f(x, y, z);
            glVertex3f(x, y+0.3, z);
            glEnd();
            
            // Velocidade de descida com gravidade
            particles[loop].y += particles[loop].vel / (slowdown*100);
            particles[loop].vel += particles[loop].gravity;
            // Fade
            particles[loop].life -= particles[loop].fade;
            
            if (particles[loop].y <= -0) {
                particles[loop].life = -1.0;
            }
            //Revive
            if (particles[loop].life < 0.0) {
                init_particles(loop);
            }
        }
    }
}

void init_lights()
{
    
    //Define luz ambiente
    GLfloat luzAmbienteCor[4]={1.0,1.0,1.0,1.0};
    //Ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteCor);
    
    GLfloat localCor[4] ={0.4,0.4,0.0,1.0};
    GLfloat localCorDif[4] ={ 1, 1, 1, 1.0};
    GLfloat localPos[4] ={xC/2, 10.0, xC/2, 1.0};
    GLfloat localAttCon =1.0;
    GLfloat localAttLin =0.05;
    GLfloat localAttQua =0.0;
    
    glLightfv(GL_LIGHT0, GL_POSITION,      localPos );
    glLightfv(GL_LIGHT0, GL_AMBIENT,       localCor );
    glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif );
    glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION,   localAttLin) ;
    glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua) ;
    
    
    
}

void defineTextures()
{
    
    /* Textura do chão */
    
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("chao.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    /* Textura das paredes */
    
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("parede.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    
    /* LATA 1 */
    
    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("Textures/can.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    /* LATA 2 */
    
    glGenTextures(1, &texture[5]);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("can2.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    
    /* LATA 3 */
    
    glGenTextures(1, &texture[6]);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("can3.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    
    /* Landscape  */
    
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("landscape.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    
    /* Landscape  */
    
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("landscape.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    /* Janela  */
    
    glGenTextures(1, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("janela.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //------------------------------------------- FATO
    // -- Player 1
    //--- Front
    glGenTextures(1, &tuxedo1Textures[0]);
    glBindTexture(GL_TEXTURE_2D, tuxedo1Textures[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("FRONT.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //--- Head
    glGenTextures(1, &tuxedo1Textures[1]);
    glBindTexture(GL_TEXTURE_2D, tuxedo1Textures[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("HEAD_FRONT.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    
}

//------- Desenhar a frente dos players, com aplicação das texturas
void drawTuxedos(){
    
    // --- Player 1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tuxedo1Textures[0]);
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f,0.0f); glVertex3f(vBB1, vBB2, vBB3);
    glTexCoord2f(1.0f,0.0f); glVertex3f(vBB4, vBB5, vBB6);
    glTexCoord2f(1.0f,1.0f); glVertex3f(vBB7, vBB8, vBB9);
    glTexCoord2f(0.0f,1.0f); glVertex3f(vBB10,vBB11, vBB12);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
}
//----- Desenhar a cabeça dos players. Com aplicação das texturas
void drawHeads(){
    
    // --- Player 1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tuxedo1Textures[1]);
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f,0.0f); glVertex3f(vCB1, vCB2, vCB3);
    glTexCoord2f(1.0f,0.0f); glVertex3f(vCB4,vCB5, vCB6);
    glTexCoord2f(1.0f,1.0f); glVertex3f(vCB7, vCB8, vCB9);
    glTexCoord2f(0.0f,1.0f); glVertex3f(vCB10,vCB11, vCB12);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void draw_sala()
{
    
    /* Função para desenhar a sala */
    
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Chão
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glColor4f(BROWN);
        glVertex3i(-xC, 0, xC);
        glVertex3i(-xC, 0, -xC);
        glVertex3i(xC, 0, -xC);
        glVertex3i(xC, 0, xC);
    glEnd();
    
    
   
    // Paredes
    
    // CIMA
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(-xC, yC, xC);
        glTexCoord2f(0.0f, 1.0f); glVertex3i(-xC, yC, -xC);
        glTexCoord2f(1.0f, 1.0f); glVertex3i(xC, yC, -xC);
        glTexCoord2f(1.0f, 0.0f); glVertex3i(xC, yC, xC);

    glEnd();
 
        
        
    //BACK
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(-xC, 0, -xC);
        glTexCoord2f(0.0f, 1.0f); glVertex3i(-xC, yC, -xC);
        glTexCoord2f(1.0f, 1.0f); glVertex3i(xC, yC, -xC);
        glTexCoord2f(1.0f, 0.0f); glVertex3i(xC, 0, -xC);
    glEnd();

    
    //ESQUERDA -> Stands
   
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-xC, 0, xC);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-xC, yC, xC);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-xC, yC, -xC);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-xC, 0, -xC);
    glEnd();
    
    //DIREITA -> Quadro ou malha de poligonos
    

    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(xC, 0, xC);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(xC, yC, xC);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(xC, yC, -xC);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(xC, 0, -xC);
    glEnd();

    
    
    // Frente - Janela
    
    // CIMA

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);        glVertex3i(-xC, yC - yC / 5, xC);
    glTexCoord2f(0.0f, 1.0f);        glVertex3i(-xC, yC, xC);
    glTexCoord2f(1.0f, 1.0f);        glVertex3i(xC, yC, xC);
    glTexCoord2f(1.0f, 0.0f);        glVertex3i(xC, yC - yC / 5, xC);
    
    
    // BAIXO
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);        glVertex3i(-xC, 0, xC);
    glTexCoord2f(0.0f, 1.0f);        glVertex3i(-xC, yC / 3, xC);
    glTexCoord2f(1.0f, 1.0f);        glVertex3i(xC, yC / 3, xC);
    glTexCoord2f(1.0f, 0.0f);        glVertex3i(xC, 0, xC);
    
    // Esquerda
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);        glVertex3i(-xC, 0, xC);
    glTexCoord2f(0.0f, 1.0f);        glVertex3i(-xC, yC, xC);
    glTexCoord2f(1.0f, 1.0f);        glVertex3i(-xC / 2.5, yC, xC);
    glTexCoord2f(1.0f, 0.0f);        glVertex3i(-xC / 2.5, 0, xC);
    
    // Direita
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, 0, xC);
    glTexCoord2f(0.0f, 1.0f);        glVertex3i(xC, yC, xC);
    glTexCoord2f(1.0f, 1.0f);        glVertex3i(xC / 2.5, yC, xC);
    glTexCoord2f(1.0f, 0.0f);        glVertex3i(xC / 2.5, 0, xC);
    
    
    glEnd();
    glDisable(GL_TEXTURE_2D);

    
        
    
}

void draw_window()
{
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    glPushMatrix();
    glTranslatef(-4, 3, xC-0.2);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);
    glVertex3f(8, 5, 0);
    glVertex3f(8, 0, 0);
    glEnd();
    
    glColor4f(0, 0, 0, 1);
    glLineWidth(10);
    glBegin(GL_LINES);
    
    // Borda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(0, 5, 0);
    
    glTexCoord2f(0.0f, 5.0f); glVertex3f(0, 5, 0);
    glTexCoord2f(8.0f, 5.0f); glVertex3f(8, 5, 0);
    glTexCoord2f(8.0f, 5.0f); glVertex3f(8, 5, 0);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(8, 0, 0);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(8, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
    
    glTexCoord2f(0.0f, 2.5f); glVertex3f(0, 2.5, 0);
    glTexCoord2f(8.0f, 2.5f); glVertex3f(8, 2.5, 0);
    
    glTexCoord2f(4.0f, 0.0f); glVertex3f(4, 0, 0);
    glTexCoord2f(4.0f, 5.0f); glVertex3f(4, 5, 0);
    
    
    glEnd();
    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
}

void draw_outside_wall()
{
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);      glVertex3i(-xC-10, -10, -xC);
    glTexCoord2f(0.0f, 1.0f);       glVertex3i(-xC-10, yC+10, -xC);
    glTexCoord2f(1.0f, 1.0f);        glVertex3i(xC+10, yC+10, -xC);
    glTexCoord2f(1.0f, 0.0f);       glVertex3i(xC+10, -10, -xC);
    glEnd();

    
    glDisable(GL_TEXTURE_2D);
    
    

}


void drawScene()
{
    
    glBlendFunc (GL_ONE, GL_ZERO);
    
    // ------- Desenhar a sala ------- \\
    
    draw_sala();
    
    draw_rain();
    
    
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, tam-2);
    drawTuxedos();
    drawHeads();
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslatef(0, 0, 30);
    draw_outside_wall();
    glRotatef(90, 0, 1, 0);
    draw_outside_wall();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, 30);
    glRotatef(-90, 0, 1, 0);
    draw_outside_wall();
    glPopMatrix();
    
    //Posição dos quadros
    
    
    // LATA 1
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 4.1f, tam - 3);
    draw_can(0,CAN);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 3.9f, tam - 3);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    draw_can(1,CAN);
    glPopMatrix();
    
    // LATA 2
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 4.1f, 0);
    draw_can(0,CAN2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 3.9f, 0);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    draw_can(1,CAN2);
    glPopMatrix();
    
    // LATA 3
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 4.1f, -7);
    draw_can(0,CAN3);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 3.9f, -7);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    draw_can(1,CAN3);
    glPopMatrix();


    
    // POSICÃO DO STAND LATA 1
    
    glPushMatrix();
    glTranslatef(-tam+2.5, 0.0f, tam - 3);
    draw_stand(4,1,1,1,1,0);
    glPopMatrix();
    
    // POSICÃO DO STAND LATA 2
    
    glPushMatrix();
    glTranslatef(-tam+2.5, 0.0f, 0);
    draw_stand(4,1,1,1,1,1);
    glPopMatrix();
    
    // POSICÃO DO STAND LATA 3
    
    glPushMatrix();
    glTranslatef(-tam+2.5, 0.0f, -7);
    draw_stand(4,1,1,1,1,2);
    glPopMatrix();

    
    // Janela
    
    draw_window();
    
    
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    
}

void lift_func(int stand)
{
    if (s_height[stand] > 5.5)
    {
        switch (stand) {
            case 0:
                lift = false;
                break;
            case 1:
                lift_1 = false;
                break;
            case 2:
                lift_2 = false;
                break;
            default:
                break;
        }
        
    }
    else
        s_height[stand]+= 0.01;
}
void lift_d_func(int stand)
{
    if (s_height[stand] <=  4)
    {
        switch (stand) {
            case 0:
                lift_d = false;
                break;
            case 1:
                lift_d_1 = false;
                break;
            case 2:
                lift_d_2 = false;
                break;
            default:
                break;
        }
    }
    else
        s_height[stand]-= 0.01;
    
}

void timer_func(int mili)
{
    rotate_inc+=0.5;
    rotate_inc_r-=0.5;
    
    if(lift)
    {
        lift_func(0);
    }
    if(lift_d)
    {
        lift_d_func(0);
    }
    
    if(lift_1)
    {
        lift_func(1);
    }
    if(lift_d_1)
    {
        lift_d_func(1);
        
    }
    if(lift_2)
    {
        lift_func(2);
    }
    if(lift_d_2)
    {
        lift_d_func(2);
        
    }


    
    glutPostRedisplay();
    glutTimerFunc(10, timer_func, 0);
    
}


void draw_can(int a, int text_n)
{
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[text_n]);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    if (!a)
        glRotatef(rotate_inc, 0.0f, 0.0f, 1.0f);
    else
        glRotatef(rotate_inc_r, 0.0f, 0.0f, 1.0f);

    gluCylinder(y, 0.3, 0.3, 0.7 , 32, 32);
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void draw_stand(int max_cubes, int size, int h, int z_size, int stand, int stand_n)
{
    int i,j;
    int height = 0;
    bool cima = false;
    
    glColor4f(BLUE);
    
    for ( i = 1; i <= max_cubes; i++)
    {
        for (j = 1; j <= max_cubes; j++ )
        {
            
            if( i == max_cubes && j == max_cubes)
            {
                cima = true;
            }
            
            // FRENTE
            
            glPushMatrix();
            glNormal3f(0.0f, 0.0f, -1.0f);
            glBegin(GL_POLYGON);
            glVertex3f(  size, height, z_size );
            glVertex3f(  size,  height + h, z_size );
            glVertex3f( -size,  height + h, z_size );
            glVertex3f( -size, height, z_size );
            glEnd();
            glPopMatrix();
            
            // TRAS
            
            glPushMatrix();
            glNormal3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
            glVertex3f(  size, height, -z_size );
            glVertex3f(  size,  height + h, -z_size );
            glVertex3f( -size,  height + h, -z_size );
            glVertex3f( -size, height, -z_size );
            glEnd();
            glPopMatrix();
            
            // CIMA
            
            if ( cima )
            {
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(WHITE_A);

                glPushMatrix();
                glNormal3f(0.0f, -1.0f, 0.0f);
                glBegin(GL_POLYGON);
                glVertex3f(  size, height + h, -z_size );
                glVertex3f(  size, height + h,  z_size );
                glVertex3f( -size, height + h,  z_size );
                glVertex3f( -size, height + h, -z_size );
                glEnd();
                glPopMatrix();

            }
            
            
            // BAIXO
            
            glPushMatrix();
            glNormal3f(0.0f, 1.0f, 0.0f);
            glBegin(GL_POLYGON);
            glVertex3f(  size, height, -z_size );
            glVertex3f(  size, height,  z_size );
            glVertex3f( -size, height,  z_size );
            glVertex3f( -size, height, -z_size );
            glEnd();
            glPopMatrix();
            
            // ESQUERDA
            
            glPushMatrix();
            glNormal3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_POLYGON);
            glVertex3f( -size, height,  z_size );
            glVertex3f( -size, height + h,  z_size );
            glVertex3f( -size, height + h, -z_size );
            glVertex3f( -size, height, -z_size );
            glEnd();
            glPopMatrix();
            
            // DIREITA
            
            glPushMatrix();
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glBegin(GL_POLYGON);
            glVertex3f( size, height,  z_size );
            glVertex3f( size, height + h,  z_size );
            glVertex3f( size, height + h, -z_size );
            glVertex3f( size, height, -z_size );
            glEnd();
            glPopMatrix();
            
        }
        
        height = height + h;
        
    }
    
    if(stand)
    {
        // DESENHAR UM CUBO TRANSPARENTE
        
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(WHITE_A);
        
        
        
        h = h * 2;
        // FRENTE
        
        glPushMatrix();
        glNormal3f(0.0f, 0.0f, -1.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height[stand_n], z_size );
        glVertex3f(  size,  s_height[stand_n] + h, z_size );
        glVertex3f( -size,  s_height[stand_n] + h, z_size );
        glVertex3f( -size, s_height[stand_n], z_size );
        glEnd();
        glPopMatrix();
        
        // TRAS
        
        glPushMatrix();
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height[stand_n], -z_size );
        glVertex3f(  size,  s_height[stand_n] + h, -z_size );
        glVertex3f( -size,  s_height[stand_n] + h, -z_size );
        glVertex3f( -size, s_height[stand_n], -z_size );
        glEnd();
        glPopMatrix();
        
        // CIMA
        
        glPushMatrix();
        glNormal3f(0.0f, -1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height[stand_n] + h, -z_size );
        glVertex3f(  size, s_height[stand_n] + h,  z_size );
        glVertex3f( -size, s_height[stand_n] + h,  z_size );
        glVertex3f( -size, s_height[stand_n] + h, -z_size );
        glEnd();
        glPopMatrix();
        
        // BAIXO
        
        glPushMatrix();
        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height[stand_n], -z_size );
        glVertex3f(  size, s_height[stand_n],  z_size );
        glVertex3f( -size, s_height[stand_n],  z_size );
        glVertex3f( -size, s_height[stand_n], -z_size );
        glEnd();
        glPopMatrix();
        
        // ESQUERDA
        
        glPushMatrix();
        glNormal3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f( -size, s_height[stand_n],  z_size );
        glVertex3f( -size, s_height[stand_n] + h,  z_size );
        glVertex3f( -size, s_height[stand_n] + h, -z_size );
        glVertex3f( -size, s_height[stand_n], -z_size );
        glEnd();
        glPopMatrix();
        
        // DIREITA
        
        glPushMatrix();
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f( size, s_height[stand_n],  z_size );
        glVertex3f( size, s_height[stand_n] + h,  z_size );
        glVertex3f( size, s_height[stand_n] + h, -z_size );
        glVertex3f( size, s_height[stand_n], -z_size );
        glEnd();
        glPopMatrix();
        
        
        
    }
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    
}



void display(void){
    
    
    if (noite)
        glClearColor(GRAY1);
    else
        glClearColor(GRAY2);
    
    if (ligaLuz)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
    
    
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
    
    /*
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
     */
    
    
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
        case 'z':
            lift_1 = true;
            break;
        case 'x':
            lift_d_1 = true;
            break;
        case 'l':
            lift = true;
            break;
        case 'k':
            lift_d = true;
            break;
        case 'c':
            lift_2 = true;
            break;
        case 'v':
            lift_d_2 = true;
            break;
        case 'q':
            obsPini[1]=obsPini[1]-incVisao;
            glutPostRedisplay();
            break;
        case 'w':
            obsPini[1]=obsPini[1]+incVisao;
            glutPostRedisplay();
            break;
        case 't':
            ligaLuz=!ligaLuz;
            glutPostRedisplay();
            break;
        case 'n':
        case 'N':
            noite=!noite;
            if (noite)
            { luzGlobalCor[0]=1.0;   luzGlobalCor[1]=1.0;   luzGlobalCor[2]=1.0; }
            else
            { luzGlobalCor[0]=0.4;   luzGlobalCor[1]=0.4;   luzGlobalCor[2]=0.4; }
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            glutPostRedisplay();	
            break;
        case 27:
            exit(0);
            break;
    }
    
}

GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    drawScene();
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
    glutReshapeFunc(resize);
    glutSpecialFunc(teclasNotAscii);
    glutTimerFunc(10, timer_func, 0);
    
    glutMainLoop();
    
    return 0;
}
