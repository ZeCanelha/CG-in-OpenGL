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
        
        
        //Define um "candeeiro"
        //Localização do candeeiro
        GLfloat candeeiroPos[4] ={0, 10.0, 0.0, 1.0};
        //Definição da luz "simples" / "branca";
        GLfloat luzCandeeirolCor[4] = {0.1, 0.1, 0.1, 1.0};
        //Caracteristicas do candeeiro da atenuação atmosférica
        GLfloat candeeiroAttCon =1.0;
        GLfloat candeeiroAttLin =0.05;
        GLfloat candeeiroAttQua =0.0;
        
        
        //Candeeiro
        glLightfv(GL_LIGHT0, GL_POSITION, candeeiroPos );
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzCandeeirolCor );
        glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, candeeiroAttCon);
        glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, candeeiroAttLin);
        glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,candeeiroAttQua);
        
        
        GLfloat lightsPos[4][4] = {{-10 + 0.5, 5, -10 + 0.5, 1.0},
            {-10 + 0.5 , 5, 10 - 0.5, 1.0},
            {10 - 0.5, 5, -10 + 0.5, 1.0},
            {10 - 0.5, 5, 10 - 0.5, 1.0}};
        //Direção dos focos de luz
        GLfloat lightsDirections [3] = {0, -1, 0};
        //Concentração dos focos (Intencidade da luz)
        GLfloat concentracaoFoco = 0.3;
        
        GLfloat focoCorEsp[4] ={ 1.0 ,  1.0, 1.0, 1.0};
        GLfloat focoCorDif[4] ={ 0.85, 0.85,0.85, 1.0};
        //Angulo do foco
        GLfloat anguloFoco = 20;
        //CORNER LIGHTS
        
        glLightfv(GL_LIGHT1, GL_POSITION,      lightsPos[0]);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,lightsDirections);
        glLightf (GL_LIGHT1, GL_SPOT_EXPONENT ,concentracaoFoco);
        glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,   anguloFoco);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,       focoCorDif );
        glLightfv(GL_LIGHT1, GL_SPECULAR,      focoCorEsp  );
        
        glLightfv(GL_LIGHT2, GL_POSITION,      lightsPos[1]);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,lightsDirections);
        glLightf (GL_LIGHT2, GL_SPOT_EXPONENT ,concentracaoFoco);
        glLightf (GL_LIGHT2, GL_SPOT_CUTOFF,   anguloFoco);
        glLightfv(GL_LIGHT2, GL_DIFFUSE,       focoCorDif );
        glLightfv(GL_LIGHT2, GL_SPECULAR,      focoCorEsp  );
        
        glLightfv(GL_LIGHT3, GL_POSITION,      lightsPos[2]);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION,lightsDirections);
        glLightf (GL_LIGHT3, GL_SPOT_EXPONENT ,concentracaoFoco);
        glLightf (GL_LIGHT3, GL_SPOT_CUTOFF,   anguloFoco);
        glLightfv(GL_LIGHT3, GL_DIFFUSE,       focoCorDif );
        glLightfv(GL_LIGHT3, GL_SPECULAR,      focoCorEsp  );
        
        glLightfv(GL_LIGHT4, GL_POSITION,      lightsPos[3]);
        glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION,lightsDirections);
        glLightf (GL_LIGHT4, GL_SPOT_EXPONENT ,concentracaoFoco);
        glLightf (GL_LIGHT4, GL_SPOT_CUTOFF,   anguloFoco);
        glLightfv(GL_LIGHT4, GL_DIFFUSE,       focoCorDif );   
        glLightfv(GL_LIGHT4, GL_SPECULAR,      focoCorEsp  );
    
    
    
    
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
    
    
    /* LATA  */
    
    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("Textures/can.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    /* Landscape  */
    
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("landscape.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    
}


void draw_sala()
{
    
    /* Função para desenhar a sala */
    
   
        glEnable(GL_TEXTURE_2D);
        
        // Chão
        
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glPushMatrix();
        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glNormal3f(0.0f, -1.0f, 0.0f);
        
        glTexCoord2f(4.0f, 4.0f);      glVertex3i(-xC, 0, -xC);
        glTexCoord2f(4.0f, 0.0f);       glVertex3i(xC, 0, -xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, 0, xC);
        glTexCoord2f(0.0f, 4.0f);       glVertex3i(-xC, 0, xC);
        
        
        glEnd();
        glPopMatrix();
        
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glPushMatrix();
        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glNormal3f(0.0f, -1.0f, 0.0f);
        
        glTexCoord2f(10.0f, 10.0f);      glVertex3i(-xC, yC, -xC);
        glTexCoord2f(10.0f, 0.0f);       glVertex3i(xC, yC, -xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, yC, xC);
        glTexCoord2f(0.0f, 10.0f);       glVertex3i(-xC, yC, xC);
        
        
        glEnd();
        glPopMatrix();
        
        
        //BACK
        
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBegin(GL_QUADS);
        glTexCoord2f(10.0f, 10.0f);      glVertex3i(-xC, 0, -xC);
        glTexCoord2f(10.0f, 0.0f);       glVertex3i(-xC, yC, -xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, yC, -xC);
        glTexCoord2f(0.0f, 10.0f);       glVertex3i(xC, 0, -xC);
        glEnd();
        glPopMatrix();
        
        //ESQUERDA
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(10.0f, 10.0f);      glVertex3i(-xC, 0, -xC);
        glTexCoord2f(10.0f, 0.0f);       glVertex3i(-xC, yC, -xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(-xC, yC, xC);
        glTexCoord2f(0.0f, 10.0f);       glVertex3i(-xC, 0, xC);
        glEnd();
        glPopMatrix();
        
        
        
        //DIREITA
        
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(10.0f, 10.0f);      glVertex3i(xC, 0, -xC);
        glTexCoord2f(10.0f, 0.0f);       glVertex3i(xC, yC, -xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, yC, xC);
        glTexCoord2f(0.0f, 10.0f);       glVertex3i(xC, 0, xC);
        glEnd();
        glPopMatrix();
        
        
        //Front
        
        // CIMA
        glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(5.0f, 5.0f);        glVertex3i(-xC, yC - yC / 5, xC);
        glTexCoord2f(5.0f, 0.0f);        glVertex3i(-xC, yC, xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, yC, xC);
        glTexCoord2f(0.0f, 5.0f);        glVertex3i(xC, yC - yC / 5, xC);
        
        
        // BAIXO
        
        glTexCoord2f(5.0f, 5.0f);        glVertex3i(-xC, 0, xC);
        glTexCoord2f(5.0f, 0.0f);        glVertex3i(-xC, yC / 3, xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, yC / 3, xC);
        glTexCoord2f(0.0f, 5.0f);        glVertex3i(xC, 0, xC);
        
        // Esquerda
        
        glTexCoord2f(5.0f, 5.0f);        glVertex3i(-xC, 0, xC);
        glTexCoord2f(5.0f, 0.0f);        glVertex3i(-xC, yC, xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(-xC / 2.5, yC, xC);
        glTexCoord2f(0.0f, 5.0f);        glVertex3i(-xC / 2.5, 0, xC);
        
        // Direita
        
        glTexCoord2f(5.0f, 5.0f);        glVertex3i(xC / 2.5, 0, xC);
        glTexCoord2f(5.0f, 0.0f);        glVertex3i(xC / 2.5, yC, xC);
        glTexCoord2f(0.0f, 0.0f);        glVertex3i(xC, yC, xC);
        glTexCoord2f(0.0f, 5.0f);        glVertex3i(xC, 0, xC);
        
        
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        
        
    
}

void draw_window()
{
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.8, 0.8, 1.0, 0.25);
    
    glPushMatrix();
    glTranslatef(-4, 3, xC-0.2);
    
    
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
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);
    glVertex3f(0, 5, 0);
    glVertex3f(8, 5, 0);
    glVertex3f(8, 5, 0);
    glVertex3f(8, 0, 0);
    glVertex3f(8, 0, 0);
    glVertex3f(0, 0, 0);
    
    glVertex3f(0, 2.5, 0);
    glVertex3f(8, 2.5, 0);
    
    glVertex3f(4, 0, 0);
    glVertex3f(4, 5, 0);
    
    
    glEnd();
    
    glPopMatrix();
    
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
    
    glTranslatef(0, 0, 30);
    draw_outside_wall();
    
    glPopMatrix();
    
    //Posição dos quadros
    
    
    // LATA
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 4.1f, tam - 3);
    draw_can(0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-tam + 2.6, 3.9f, tam - 3);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    draw_can(1);
    glPopMatrix();
    
    // POSICÃO DO STAND LATA
    
    glPushMatrix();
    glTranslatef(-tam+2.5, 0.0f, tam - 3);
    draw_stand(4,1,1,1,1);
    glPopMatrix();
    
    // Janela
    
    draw_window();
    
    
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    
}

void timer_func(int mili)
{
    rotate_inc+=0.5;
    rotate_inc_r-=0.5;
    
    if(lift)
    {
        if (s_height > 5.5)
        {
            lift = false;
        }
        else
            s_height+= 0.01;
    }
    if(lift_d)
    {
        if (s_height <=  4)
        {
            lift_d = false;
        }
        else
            s_height-= 0.01;
    }

    
    glutPostRedisplay();
    glutTimerFunc(10, timer_func, 0);
    
}


void draw_can(int a)
{
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[CAN]);
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

void draw_stand(int max_cubes, int size, int h, int z_size, int stand)
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
        
        printf("%d",height);
        
        
        h = h * 2;
        // FRENTE
        
        glPushMatrix();
        glNormal3f(0.0f, 0.0f, -1.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height, z_size );
        glVertex3f(  size,  s_height + h, z_size );
        glVertex3f( -size,  s_height + h, z_size );
        glVertex3f( -size, s_height, z_size );
        glEnd();
        glPopMatrix();
        
        // TRAS
        
        glPushMatrix();
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height, -z_size );
        glVertex3f(  size,  s_height + h, -z_size );
        glVertex3f( -size,  s_height + h, -z_size );
        glVertex3f( -size, s_height, -z_size );
        glEnd();
        glPopMatrix();
        
        // CIMA
        
        glPushMatrix();
        glNormal3f(0.0f, -1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height + h, -z_size );
        glVertex3f(  size, s_height + h,  z_size );
        glVertex3f( -size, s_height + h,  z_size );
        glVertex3f( -size, s_height + h, -z_size );
        glEnd();
        glPopMatrix();
        
        // BAIXO
        
        glPushMatrix();
        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(  size, s_height, -z_size );
        glVertex3f(  size, s_height,  z_size );
        glVertex3f( -size, s_height,  z_size );
        glVertex3f( -size, s_height, -z_size );
        glEnd();
        glPopMatrix();
        
        // ESQUERDA
        
        glPushMatrix();
        glNormal3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f( -size, s_height,  z_size );
        glVertex3f( -size, s_height + h,  z_size );
        glVertex3f( -size, s_height + h, -z_size );
        glVertex3f( -size, s_height, -z_size );
        glEnd();
        glPopMatrix();
        
        // DIREITA
        
        glPushMatrix();
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f( size, s_height,  z_size );
        glVertex3f( size, s_height + h,  z_size );
        glVertex3f( size, s_height + h, -z_size );
        glVertex3f( size, s_height, -z_size );
        glEnd();
        glPopMatrix();
        
        
        
    }
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    
}
void drawWalls(GLint texture_n, int w_size, int block, int a )
{
    
    if(a == 0)
        glColor4f(BROWN);
    else
        glColor4f(GRAY1);
    
    if ( texture_n != -1)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[texture_n]);
    }
    
    int i,j;
    // Tamanho da parede = 5 * 2 -> 10x10
    int width = 0.1;
    int height = 0;
    
    for ( i = 1; i <= w_size; i++)
    {
        for (j = 1; j <= w_size; j++)
        {
            glPushMatrix();
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0f, 1.0f);   glVertex3f(  (block * j), height, width );
            glTexCoord2f(1.0f, 0.0f);   glVertex3f(  (block * j),  (block * i), width );
            glTexCoord2f(0.0f, 0.0f);   glVertex3f( -(block * j),  (block * i), width );
            glTexCoord2f(0.0f, 1.0f);   glVertex3f( -(block * j), height, width );
            glEnd();
            glPopMatrix();
            
        }
        height+=block;
    }
    
    if ( texture_n != -1)
    {
        glDisable(GL_TEXTURE_2D);
    }
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
}




void display(void){
    
    
    GLfloat lightsPos[4][4] = {{-10 + 0.5, 5, -10 + 0.5, 1.0},
        {-10 + 0.5 , 5, 10 - 0.5, 1.0},
        {10 - 0.5, 5, -10 + 0.5, 1.0},
        {10 - 0.5, 5, 10 - 0.5, 1.0}};
    
    //Direção dos focos de luz
    GLfloat lightsDirections [3] = {0, -1, 0};
    
    
    if (ligaLuz){
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        
    }
    else{
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
    }
    
    //Propriedades dadas a cada foco de luz
    glLightfv(GL_LIGHT1, GL_POSITION,      lightsPos[0]);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightsDirections);
    
    glLightfv(GL_LIGHT2, GL_POSITION,      lightsPos[1]);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightsDirections);
    
    glLightfv(GL_LIGHT3, GL_POSITION,      lightsPos[2]);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightsDirections);
    
    glLightfv(GL_LIGHT4, GL_POSITION,      lightsPos[3]);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightsDirections);
    
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
        case 'l':
            lift = true;
            break;
        case 'k':
            lift_d = true;
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
    glutTimerFunc(10, timer_func, 0);
    
    glutMainLoop();
    
    return 0;
}
