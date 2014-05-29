/*
 * main.cpp
 *
 *  Created on: 22/05/2014
 *      Author: dmatos
 */
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0,
		-1.0 }, { -1.0, 1.0, -1.0 }, { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, {
		1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

float angGiroCena = 0.0;
float upDown = 0.1;
float leftRight = 0.0;
float angPorta = 0.0;

float cam_pos_x = 1.0;
float cam_pos_y = 0.0;
float cam_pos_z = 0.0;
float cam_norm_x = 0.0;
float cam_norm_y = 0.0;
float cam_norm_z = 0.0;
float cam_up_x = 0.0;
float cam_up_y = 1.0;
float cam_up_z = 0.0;

float hRadians, vRadians;

float walk = 0.0;

void loadDefaultMaterial() {
	GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.0, 1.0 };
	GLfloat mat_specular[] = { 0.4, 0.4, 0.0, 1.0 };
	GLfloat mat_shininess = { 50.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void polygon(int a, int b, int c, int d, float red, float green, float blue) {

	glBegin(GL_POLYGON);
	glColor3f(red, green, blue);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

/**
 * draws a cube with given RGB values.
 */
void cubo(float red, float green, float blue) {

	glEnable(GL_COLOR_MATERIAL);

	//vetor Normal � necess�rio para ilumina��o
	glNormal3f(0.0, 0.0, -1.0);
	polygon(0, 3, 2, 1, red, green, blue);

	glNormal3f(0.0, 1.0, 0.0);
	polygon(2, 3, 7, 6, red, green, blue);

	glNormal3f(-1.0, 0.0, 0.0);
	polygon(0, 4, 7, 3, red, green, blue);

	glNormal3f(1.0, 0.0, 0.0);
	polygon(1, 2, 6, 5, red, green, blue);

	glNormal3f(0.0, 0.0, 1.0);
	polygon(4, 5, 6, 7, red, green, blue);

	glNormal3f(0.0, -1.0, 0.0);
	polygon(0, 1, 5, 4, red, green, blue);

	glDisable(GL_COLOR_MATERIAL);

	loadDefaultMaterial();
}

// modelo de cilindro com eixo em Z
/**
 * draws a cylinder with the given RGB values
 */
void cilindro(float red, float green, float blue) {
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(red, green, blue);

	float raio = 1.0;
	float alt = 1.0;
	static GLUquadric* quad;
	quad = gluNewQuadric();
	gluCylinder(quad, raio, raio, alt, 20, 10);

	glDisable(GL_COLOR_MATERIAL);
	loadDefaultMaterial();
}

void pernaMesa() {
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.05, 0.05, 1);
	cilindro(1, 1, 1);
	glPopMatrix();
}

void mesa() {

	glPushMatrix();
	{
		glPushMatrix();
		glScalef(1, 0.05, 0.5);
		cubo(0.7, 0.7, 0.7); //tampo da mesa
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.9, 0, 0.35);
		pernaMesa();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.9, 0, 0.35);
		pernaMesa();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.9, 0, -0.35);
		pernaMesa();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.9, 0, -0.35);
		pernaMesa();
		glPopMatrix();
	}
	glPopMatrix();
}

//void armario() {
//	glPushMatrix();
//	glScalef(0.5, 1, 0.5);
//	cubo(0.8, 0.8, 0.8);
//	glPopMatrix();
//
//}

void estantePc() {

	float larg_peca = 0.01;
	float alt_peca = 0.3;
	float prof_peca = -0.2;
	float cor_pecaR = 0.8;
	float cor_pecaG = 0.6;
	float cor_pecaB = 0.2;
	//lat_inf
	glPushMatrix();
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//lat_inf
	glPushMatrix();
	glTranslated(0.6, 0, 0);
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//lat_inf
	glPushMatrix();
	glTranslated(0.9, 0, 0);
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//tampo
	glPushMatrix();
	glTranslated(0.45, 0.3, 0.01);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca - 0.09, 0.5);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//fundo
	glPushMatrix();
	glTranslated(0.3, 0.1, -0.2);
	glRotated(90, 0, 1, 0);
	glScalef(larg_peca, alt_peca - 0.1, 0.3);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//fundo_base
	glPushMatrix();
	glTranslated(0.3, -0.1, -0.1);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca / 3, 0.3);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//teclado_base
	glPushMatrix();
	glTranslated(0.3, 0.2, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca - 0.1, 0.3);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//teclado_base_trilho_direto
	glPushMatrix();
	glTranslated(0.59, 0.22, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca - 0.1, 0.01);
	cubo(cor_pecaR, cor_pecaG - 0.1, cor_pecaB);
	glPopMatrix();
	//teclado_base_trilho_esquerdo
	glPushMatrix();
	glTranslated(0.01, 0.22, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca - 0.1, 0.01);
	cubo(cor_pecaR, cor_pecaG - 0.1, cor_pecaB);
	glPopMatrix();
	//Gaveta
	glPushMatrix();
	glTranslated(0.75, 0.22, 0);
	glScalef(0.14, 0.06, prof_peca);
	cubo(cor_pecaR - 0.05, cor_pecaG - 0.1, cor_pecaB - 0.03);
	glPopMatrix();
	//Puxador_Gaveta
	glPushMatrix();
	glTranslated(0.75, 0.22, 0.2);
	glScalef(0.02, 0.02, 0.02);
	cilindro(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//Base_CpU
	glPushMatrix();
	glTranslated(0.75, -0.25, 0);
	glScalef(0.14, larg_peca, prof_peca);
	cubo(cor_pecaR - 0.05, cor_pecaG - 0.03, cor_pecaB - 0.03);
	glPopMatrix();
	//Haste_SegundoAndar_direito
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0.9, -0.05, -0.6);
	glScalef(0.01, 0.01, 0.3);
	cilindro(0.8, 0.8, 0.8);
	glPopMatrix();
	//Haste_SegundoAndar_esquerdo
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, -0.05, -0.6);
	glScalef(0.01, 0.01, 0.3);
	cilindro(0.8, 0.8, 0.8);
	glPopMatrix();
	//tampo_segundo_andar
	glPushMatrix();
	glTranslated(0.45, 0.6, -0.05);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca - 0.17, 0.5);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//base_central_segundo_andar
	glPushMatrix();
	glTranslated(0.5, 0.45, -0.05);
	glScalef(larg_peca, alt_peca - 0.16, alt_peca - 0.17);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//base_central_segundo_andar2
	glPushMatrix();
	glTranslated(0.4, 0.45, -0.05);
	glScalef(larg_peca, alt_peca - 0.16, alt_peca - 0.17);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//base_central_segundo_fundo
	glPushMatrix();
	glTranslated(0.45, 0.45, -0.18);
	glScalef(0.05, alt_peca - 0.16, larg_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//tampo_terceiro_andar
	glPushMatrix();
	glTranslated(0.45, 0.8, -0.05);
	glRotated(90, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	glScalef(larg_peca, alt_peca - 0.17, 0.5);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//base_lateral_terceiro_andar_esquerdo
	glPushMatrix();
	glTranslated(0, 0.7, -0.05);
	glScalef(larg_peca, alt_peca - 0.2, alt_peca - 0.17);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//base_lateral_terceiro_andar_esquerdo
	glPushMatrix();
	glTranslated(0.9, 0.7, -0.05);
	glScalef(larg_peca, alt_peca - 0.2, alt_peca - 0.17);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//Haste_Central_terceiroAndar
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0.45, -0.05, -0.8);
	glScalef(0.01, 0.01, 0.2);
	cilindro(0.8, 0.8, 0.8);
	glPopMatrix();

}
void notebook() {
	float larg_peca = 0.01;
	float alt_peca = 0.3;
	float prof_peca = -0.2;
	float cor_pecaR = 0;
	float cor_pecaG = 0;
	float cor_pecaB = 0;
	//armacao
	glPushMatrix();
	glTranslated(0.2, 0.44, -0.1);
	glScalef(0.15, alt_peca - 0.19, larg_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//tela
	glPushMatrix();
	glTranslated(0.2, 0.445, -0.09);
	glScalef(0.13, alt_peca - 0.21, larg_peca);
	cubo(cor_pecaR + 0.12, cor_pecaG + 0.12, cor_pecaB + 0.12);
	glPopMatrix();
	//teclado
	glPushMatrix();
	glTranslated(0.2, 0.31, 0);
	glRotated(90, 1, 0, 0);
	glScalef(0.15, alt_peca - 0.19, larg_peca + 0.01);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//teclado
	glPushMatrix();
	glTranslated(0.2, 0.315, 0.01);
	glRotated(90, 1, 0, 0);
	glScalef(0.13, alt_peca - 0.23, larg_peca + 0.01);
	cubo(cor_pecaR + 0.04, cor_pecaG + 0.04, cor_pecaB + 0.04);
	glPopMatrix();
}
void cadeira() {
	float x_peca = 0.01;
	float alt_peca = 0.3;
	float y_peca = 0.01;
	float cor_pecaR = 0.9;
	float cor_pecaG = 0.9;
	float cor_pecaB = 0.9;

	//Perna esquerda
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0.1, 0.3, 0);
	glScalef(x_peca, y_peca, alt_peca);
	cilindro(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//joelho esquerdo
	glPushMatrix();
	glTranslated(0.1, 0.025, 0.34);
	glRotated(145, 1, 0, 0);
	glScalef(x_peca, y_peca, alt_peca - 0.25);
	cilindro(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();

	//Perna direita
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0.5, 0.3, 0);
	glScalef(x_peca, y_peca, alt_peca);
	cilindro(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//joelho direita
	glPushMatrix();
	glTranslated(0.5, 0.025, 0.34);
	glRotated(145, 1, 0, 0);
	glScalef(x_peca, y_peca, alt_peca - 0.25);
	cilindro(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//almofada
	glPushMatrix();
	glTranslated(0.306, 0.04, 0.47);
	glRotated(90, 1, 0, 0);
	glScalef(alt_peca - 0.102, alt_peca - 0.16, 0.009);
	cubo(cor_pecaR - 0.9, cor_pecaG - 0.8, cor_pecaB);
	glPopMatrix();
	//acento
	glPushMatrix();
	glTranslated(0.305, 0.026, 0.47);
	glRotated(90, 1, 0, 0);
	glScalef(alt_peca - 0.093, alt_peca - 0.15, 0.009);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//Perna direita inferior
	glPushMatrix();
	glRotated(80, 1, 0, 0);
	glTranslated(0.5, 0.61, 0.071);
	glScalef(x_peca, y_peca, alt_peca + 0.05);
	cilindro(cor_pecaR + 0.1, cor_pecaG + 0.1, cor_pecaB);
	glPopMatrix();
	//Perna esquerda inferior
	glPushMatrix();
	glRotated(80, 1, 0, 0);
	glTranslated(0.11, 0.61, 0.071);
	glScalef(x_peca, y_peca, alt_peca + 0.05);
	cilindro(cor_pecaR + 0.1, cor_pecaG + 0.1, cor_pecaB);
	glPopMatrix();
	//encosto direita
	glPushMatrix();
	glRotated(95, 1, 0, 0);
	glTranslated(0.5, 0.61, -0.44);
	glScalef(x_peca, y_peca, alt_peca + 0.05);
	cilindro(cor_pecaR + 0.1, cor_pecaG + 0.1, cor_pecaB);
	glPopMatrix();
	//encosto esquerdo
	glPushMatrix();
	glRotated(95, 1, 0, 0);
	glTranslated(0.11, 0.61, -0.44);
	glScalef(x_peca, y_peca, alt_peca + 0.05);
	cilindro(cor_pecaR + 0.1, cor_pecaG + 0.1, cor_pecaB);
	glPopMatrix();
	//encosto_costas1
	glPushMatrix();
	glTranslated(0.305, 0.3, 0.65);
	glRotated(90, 0, 0, 1);
	glScalef(alt_peca - 0.28, alt_peca - 0.1, 0.009);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//encosto_costas2
	glPushMatrix();
	glTranslated(0.305, 0.35, 0.655);
	glRotated(90, 0, 0, 1);
	glScalef(alt_peca - 0.28, alt_peca - 0.1, 0.005);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();

}

void armario() {
    float r = 0.251;
    float g = 0.063;
    float b = 0.055;


    glPushMatrix();
	glScalef(1, 0.01, 3);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 3, 0);
	glScalef(1, 0.01, 3);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, 3);
	glScalef(1, 1.5, 0.01);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, 1);
	glScalef(1, 1.5, 0.01);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, -1);
	glScalef(1, 1.5, 0.01);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, -3);
	glScalef(1, 1.5, 0.01);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1, 1.5, 0);
	glScalef(0.01, 1.5, 3);
	cubo(r,g,b);
    glPopMatrix();

    //porta 1
    glPushMatrix();
	glTranslatef(-1, 1.5, -3);
	glRotatef(-angPorta,0,1,0);
    //maçaneta 1
	glPushMatrix();
	glTranslatef(-0.1, 0.5, 1.85);
	glRotatef(90,1,0,0);
	glScalef(0.05, 0.05, 1);
	cilindro(0.7, 0.7, 0.7);
	glPopMatrix();

	glTranslatef(0, 0, 1);
	glScalef(0.01, 1.48, 0.98);
	cubo(r,g,b);
    glPopMatrix();


    //porta 2
    glPushMatrix();
	glTranslatef(-1, 1.5, -1);
	glRotatef(-angPorta,0,1,0);
    //maçaneta 2
	glPushMatrix();
	glTranslatef(-0.1, 0.5, 1.85);
	glRotatef(90,1,0,0);
	glScalef(0.05, 0.05, 1);
	cilindro(0.7, 0.7, 0.7);
	glPopMatrix();

	glTranslatef(0, 0, 1);
	glScalef(0.01, 1.48, 0.98);
	cubo(r,g,b);
    glPopMatrix();


    //porta 3
    glPushMatrix();
	glTranslatef(-1, 1.5, 3);
	glRotatef(angPorta,0,1,0);
    //maçaneta 3
	glPushMatrix();
	glTranslatef(-0.1, 0.5, -1.85);
	glRotatef(90,1,0,0);
	glScalef(0.05, 0.05, 1);
	cilindro(0.7, 0.7, 0.7);
	glPopMatrix();

	glTranslatef(0, 0, -1);
	glScalef(0.01, 1.48, 0.98);
	cubo(r,g,b);
    glPopMatrix();

}

void armario2() {
	float r = 0.141;
    float g = 0.082;
    float b = 0.063;


    glPushMatrix();
	glScalef(1, 0.01, 1);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 8, 0);
	glScalef(1, 0.01, 1);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 4, 1);
	glScalef(1, 4, 0.01);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 4, -1);
	glScalef(1, 4, 0.01);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1, 4, 0);
	glScalef(0.01, 4, 1);
	cubo(r,g,b);
    glPopMatrix();

    //porta
    glPushMatrix();
	glTranslatef(-1, 4, -1);
	glRotatef(-angPorta,0,1,0);
    //maçaneta
	glPushMatrix();
	glTranslatef(-0.1, 0.5, 1.85);
	glRotatef(90,1,0,0);
	glScalef(0.05, 0.05, 0.3);
	cilindro(0.7, 0.7, 0.7);
	glPopMatrix();

	glTranslatef(0, 0, 1);
	glScalef(0.01, 4, 1);
	cubo(r,g,b);
    glPopMatrix();


}


void mesinha() {
	float r = 0.141;
    float g = 0.090;
    float b = 0.067;


    glPushMatrix();
	glScalef(1.5, 0.05, 2);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, 0);
	glScalef(1.5, 0.05, 2);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 1.5, 0.5);
    glRotatef(270,1,0,0);
	cilindro(r,g,b);
    glPopMatrix();
}

void hack() {
	float r = 0.141;
    float g = 0.090;
    float b = 0.067;


    glPushMatrix();
	glScalef(1, 0.05, 1.5);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 3, 0);
	glScalef(1, 0.05, 1.5);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, 0.8);
	glScalef(1, 1.5, 0.05);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 1.5, -0.8);
	glScalef(1, 1.5, 0.05);
	cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(1, 0.05, 0.8);
	cubo(r,g,b);
    glPopMatrix();

}

void estante(){
    float r = 0.655;
    float g = 0.604;
    float b = 0.439;

    glPushMatrix();
    glTranslatef(0, 2, -0.6);
    glScalef(0.2, 2.05, 0.01);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2, 0.6);
    glScalef(0.2, 2.05, 0.01);
    cubo(r,g,b);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0.1, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.75, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.4, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.05, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.7, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3.35, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 4, 0);
    glScalef(0.2, 0.01, 0.6);
    cubo(r,g,b);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glScalef(0.01, 2.05, 0.6);
    cubo(r,g,b);
    glPopMatrix();
}

void monitor(){
    float r = 0.2;
    float g = 0.2;
    float b = 0.2;

    glPushMatrix();
    glScalef(0.3, 1, 1);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.26, 0, 0);
    glScalef(0.05, 1, 1);
    cubo(0.3,0.3,0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    glScalef(0.3, 0.7, 0.7);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 0, 1);
    glScalef(0.1, 1, 0.1);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 0, -1);
    glScalef(0.1, 1, 0.1);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 1, 0);
    glScalef(0.1, 0.1, 1.1);
    cubo(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, -1, 0);
    glScalef(0.1, 0.1, 1.1);
    cubo(r,g,b);
    glPopMatrix();
}
void cama(){
    float larg_peca = 0.02;
    float alt_peca = 0.25;
    float prof_peca = 0.03;
    float cor_pecaR= 0.6;
    float cor_pecaG= 0.2;
    float cor_pecaB= 0;

    //pe_esquerdo_inf
	glPushMatrix();
	glTranslated(0,-0.05,0);
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
    //pe_direito_inf
	glPushMatrix();
	glTranslated(0.7,-0.05,0);
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//pe_esquerdo_sup
	glPushMatrix();
	glTranslated(0,-0.05,-1.2);
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
    //pe_direito_sup
	glPushMatrix();
	glTranslated(0.7,-0.05,-1.2);
	glScalef(larg_peca, alt_peca, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	  //barra lateral esquerda
	glPushMatrix();
	glTranslated(0,0.03,-0.6);
	glScalef(larg_peca-0.01, alt_peca/3, prof_peca+0.55);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	  //barra lateral direita
	glPushMatrix();
	glTranslated(0.7,0.03,-0.6);
	glScalef(larg_peca-0.01, alt_peca/3, prof_peca+0.55);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//barra_fundo
	glPushMatrix();
	glTranslated(0.35,0.03,0);
	glScalef(larg_peca+0.31, alt_peca/3, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//barra_frente
	glPushMatrix();
	glTranslated(0.35,0.03,-1.2);
	glScalef(larg_peca+0.31, alt_peca/3, prof_peca);
	cubo(cor_pecaR, cor_pecaG, cor_pecaB);
	glPopMatrix();
	//Colch�o
	glPushMatrix();
	glTranslated(0.35,0.12,-0.6);
	glScalef(0.35, alt_peca/3, prof_peca+0.54);
	cubo(0.9, 0.9, 0.9);
	glPopMatrix();



}

void prateleira() {

}

void cena() {
	glPushMatrix();
	glTranslatef(2, 0, -1);
	mesa();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.5, -0.2, -0.5);
	notebook();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, 0, -1);
//	armario();
//    monitor();
//    hack();
//    armario2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, 0, -3);
	estantePc();
	notebook();
	cadeira();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -0.2, -1.5);
	cama();
	glPopMatrix();

}

void rotateCamera(float h, float v) {
	hRadians += h;
	vRadians += v;

	float radius = 1.0;

	cam_norm_y = cam_pos_y + (float) (radius * sin(vRadians));
	cam_norm_x = cam_pos_x + (float) (radius * cos(vRadians) * cos(hRadians));
	cam_norm_z = cam_pos_z + (float) (radius * cos(vRadians) * sin(hRadians));

	cam_up_x = cam_pos_x - cam_norm_x;
	cam_up_y = abs(
			int(cam_pos_y + (float) (radius * sin(vRadians + M_PI / 2))));
	cam_up_z = cam_pos_z - cam_norm_z;
}

void place() {
	gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z, cam_norm_x, cam_norm_y,
			cam_norm_z, cam_up_x, cam_up_y, cam_up_z);
}

void exibe() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	/*O movimento para frente e para tr�s n�o est� pronto.
	 *Se quiser dar zoom na cena descomente a linha abaixo
	 */
	glTranslatef(0, 0, -upDown);

	glTranslatef(0, -0.5, 0);
	rotateCamera(angGiroCena, 0);
	angGiroCena = 0;
	place();

	cena();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void inicia() {
	// estabelece parametros de iluminacao
	loadDefaultMaterial();

	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };

	GLfloat light_position[] = { -3.0, 3.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	exibe();
}

void controle(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'a':
	    if(angPorta < 90)
	        angPorta += 1;
	    break;
	case 'A':
	    if(angPorta > 0)
	        angPorta -= 1;
	    break;
	case 27:
		exit(EXIT_SUCCESS);  // tecla ESC para sair
	}
}

void controleSpecial(int tecla, int x, int y) {
	float radius = 1.0;

	switch (tecla) {
	case GLUT_KEY_LEFT:
		angGiroCena -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		angGiroCena += 0.1;
		break;
	case GLUT_KEY_UP:
		cam_pos_x += upDown * (float) (radius * cos(vRadians) * cos(hRadians));
		cam_pos_z += upDown * (float) (radius * cos(vRadians) * sin(hRadians));
		break;
	case GLUT_KEY_DOWN:
		cam_pos_x -= upDown * (float) (radius * cos(vRadians) * cos(hRadians));
		cam_pos_z -= upDown * (float) (radius * cos(vRadians) * sin(hRadians));
		break;
	}
	exibe();
	glutPostRedisplay();
}

//TODO animacao, caso haja
void idle() {
	glutPostRedisplay();
}

void janela(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("tp01");
	glutReshapeFunc(janela);
	glutDisplayFunc(exibe);
	glutSpecialFunc(controleSpecial);
	glutKeyboardFunc(controle);
	glutIdleFunc(idle);
	inicia();
	glutMainLoop();
}
