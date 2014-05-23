/*
 * main.cpp
 *
 *  Created on: 22/05/2014
 *      Author: dmatos
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0,
		-1.0 }, { -1.0, 1.0, -1.0 }, { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, {
		1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

float angGiroCena = 0.0;
float upDown = 0.1;
float leftRight = 0.0;

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

void cubo(float red, float green, float blue) {

	glEnable(GL_COLOR_MATERIAL);

	//vetor Normal é necessário para iluminação
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

void armario() {
	glPushMatrix();
	glScalef(0.5, 1, 0.5);
	cubo(0.8, 0.8, 0.8);
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
	glTranslatef(-2, 0, -1);
	armario();
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
	cam_up_y = abs(cam_pos_y + (float) (radius * sin(vRadians + M_PI / 2)));
	cam_up_z = cam_pos_z - cam_norm_z;
}

void place() {
	gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z, cam_norm_x,
			cam_norm_y, cam_norm_z, cam_up_x, cam_up_y, cam_up_z);
}

void exibe() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

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
	case 27:
		exit(EXIT_SUCCESS);  // tecla ESC para sair
	}
}

void controleSpecial(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_LEFT:
		angGiroCena -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		angGiroCena += 0.1;
		break;
	case GLUT_KEY_UP:
		upDown -= 0.1;
		break;
	case GLUT_KEY_DOWN:
		upDown += 0.1;
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
