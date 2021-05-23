#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

float ballX = 0.0;  // ballX: ���� x��ǥ
float ballY = 0.0;  // ballY: ���� y��ǥ
float ballmoveX = 0.1;  // ballmoveX: x����ŭ �󸶳� �����̴����� �ǹ�
float ballmoveY = -0.1;  // ballmoveY: y����ŭ �󸶳� �����̴����� �ǹ�
float ballrotate = 0.0;  // ballrotate: ���� ȸ�� ���� �ǹ�
double radius = 0.1;  // radius: ���� �������� �ǹ�

float BarX = 0.0;  // BarX: ���� �� ���� ��� �������� x��ǥ
float BarRangeA = BarX;  // BarRangeA: ���� �� ���� �𼭸��� �ǹ�
float BarRangeB = BarX + 0.8;  // BarRangeB: ���� �� ������ �𼭸��� �ǹ�

GLfloat BarVertices[8][3] = {  // BarVertices[][]: ������� ��ǥ������ ������ �迭
	{ BarRangeA, -0.7, 0.2 },
	{ BarRangeB, -0.7, 0.2 },
	{ BarRangeB, -0.9, 0.2 },
	{ BarRangeA, -0.9, 0.2 },
	{ BarRangeA, -0.7, -0.2 },
	{ BarRangeB, -0.7, -0.2 },
	{ BarRangeB, -0.9, -0.2 },
	{ BarRangeA, -0.9, -0.2 }
};

GLfloat BarColors[8][3] = {  // BarColors[][]: ������� ���� ������ ������ �迭
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 }
};

GLfloat WallVertices[8][3] = {  // WallVertices[][]: �𼭸� ���� ��ǥ������ ������ �迭
	{ -0.05, -0.9, 0.2 },
	{ -0.05, 0.9, 0.2 },
	{ 0.05, 0.9, 0.2 },
	{ 0.05, -0.9, 0.2 },
	{ -0.05, -0.9, -0.2 },
	{ -0.05, 0.9, -0.2 },
	{ 0.05, 0.9, -0.2 },
	{ 0.05, -0.9, -0.2 }
};
GLfloat WallColors[8][3] = {  // WallColors[][]: �𼭸� ���� ���� ������ ������ �迭
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};

GLubyte MyVertexList[24] = {
	0, 3, 2, 1,
	2, 3, 7, 6,
	0, 4, 7, 3,
	1, 2, 6, 5,
	4, 5, 6, 7,
	0, 1, 5, 4
};

GLfloat barLight0_ambient[] = { 0.0, 1.0, 1.0, 1.0 };     // ����� ���� Ư��
GLfloat barLight0_diffuse[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat barLight0_specular[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat barLightPosition[] = { 0.0, -0.7, 0.1, 1.0 };

GLfloat ballLight0_ambient[] = { 1.0, 1.0, 0.0, 1.0 };     // �� ���� Ư��
GLfloat ballLight0_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat ballLight0_specular[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat ballLightPosition[] = { ballX, ballY, 0.2, 1.0 };

void checking() {

	if (ballY <= -0.8)  // ���� �ٴ����� �������� ���� ����
		exit(0);

	if ((ballY <= -0.6 && (ballX >= BarRangeA && ballX <= BarRangeB + 0.1))) {  // ���� ���� �ٿ� �΋Hġ�� ƨ��� ȸ����Ŵ
		ballmoveY = ballmoveY * -1;

		if(ballmoveX < 0) ballrotate = ballrotate + 90;  // �� �� ���ʿ��� �Դ��� �����ʿ��� �Դ����� ���� ȸ�� ������ �޸���
		else if (ballmoveX > 0) ballrotate = ballrotate - 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;  // 360�� ȸ���� ȸ���� ���� ���̳� ���������̹Ƿ� 0���� ����
	}

	if (ballX <= -0.7) {  // ���� ���� ���� �΋Hġ�� ƨ��� ȸ����Ŵ
		ballmoveX = ballmoveX * -1;
		
		if (ballmoveY < 0) ballrotate = ballrotate - 90;
		else if (ballmoveY > 0) ballrotate = ballrotate + 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;
	}

	if (ballX >= 0.8) {  // ���� ������ ���� �΋Hġ�� ƨ��� ȸ����Ŵ
		ballmoveX = ballmoveX * -1;

		if (ballmoveY < 0) ballrotate = ballrotate + 90;
		else if (ballmoveY > 0) ballrotate = ballrotate - 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;
	}

	if (ballY >= 0.7) {  // ���� ���� ���� �΋Hġ�� ƨ��� ȸ����Ŵ
		ballmoveY = ballmoveY * -1;
		
		if (ballmoveX < 0) ballrotate = ballrotate - 90;
		else if (ballmoveX > 0) ballrotate = ballrotate + 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;
	}
}

void drawHexahedron() {  // ����ü�� �׸��� �Լ�
	for (GLint i = 0; i < 6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
}

void MyDisplay() {
	glViewport(0, 0, 500, 500);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glMatrixMode(GL_MODELVIEW);

	glColorPointer(3, GL_FLOAT, 0, WallColors);
	glVertexPointer(3, GL_FLOAT, 0, WallVertices);

	glLoadIdentity();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(-0.95, 0.1, 0.0);
	drawHexahedron();  // �Ʒ��� �𼭸��� ����ü ����

	glLoadIdentity();
	glRotatef(-15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(-0.95, -0.05, 0.0);
	drawHexahedron();  // ���� �𼭸��� ����ü ����

	glLoadIdentity();
	glRotatef(-15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(0.95, 0.05, 0.0);
	drawHexahedron();  // ������ �𼭸��� ����ü ����

	glLoadIdentity();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(0.95, -0.1, 0.0);
	drawHexahedron();  // ���� �𼭸��� ����ü ����

	glLoadIdentity();
	glShadeModel(GL_SMOOTH);    //���� ���̵�
	glEnable(GL_DEPTH_TEST);    //���� ���� Ȱ��ȭ
	glEnable(GL_LIGHTING);      //���� Ȱ��ȭ
	glEnable(GL_LIGHT0);

	glColorPointer(3, GL_FLOAT, 0, BarColors);
	glVertexPointer(3, GL_FLOAT, 0, BarVertices);

	glLoadIdentity();
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glRotatef(15.0, 1.0, 0.0, 0.0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, barLight0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, barLight0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, barLight0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, barLightPosition);

	drawHexahedron();  // ����� ����

	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_AMBIENT, ballLight0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ballLight0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ballLight0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, ballLightPosition);

	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(ballX, ballY, 0.0);
	glRotatef(ballrotate, 0, 0, 1.0);
	glutSolidSphere(0.1, 50.0, 50.0);  // �� ����
	glPopMatrix();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glLoadIdentity();

	glFlush();
	glutPostRedisplay();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed) {
	case 'a':  // 'a' Ű�� ������ ����ٰ� �������� �̵�
		if(BarRangeA >= -0.95) BarX = BarX - 0.1;  // ��, ����ٰ� �����̳� ������ ���� �ִ� ��� �̵� ����
		break;
	case 'd':  // 'd' Ű�� ������ ����ٰ� ���������� �̵�
		if(BarRangeB <= 0.85) BarX = BarX + 0.1;  
		break;
	case 27:  // 'Esc' Ű�� ������ �ٷ� ���� ����
		exit(0);
		break;
	}

	BarRangeA = BarX;  // ���� �� �� �𼭸� ���� �׻� ��������
	BarRangeB = BarX + 0.8;

	BarVertices[0][0] = BarRangeA;
	BarVertices[1][0] = BarRangeB;
	BarVertices[2][0] = BarRangeB;
	BarVertices[3][0] = BarRangeA;
	BarVertices[4][0] = BarRangeA;
	BarVertices[5][0] = BarRangeB;
	BarVertices[6][0] = BarRangeB;
	BarVertices[7][0] = BarRangeA;  // ����ٰ� �����̸� x��ǥ ���� �׻� ��ȭ�ϵ��� ��
}

void MyTimer(int Value) {  // �ִϸ��̼�ó�� ���̰� �ϱ� ���� Ÿ�̸Ӹ� ���

	checking();

	ballX = ballX + ballmoveX;
	ballY = ballY + ballmoveY;  // ���� ��ġ�� ����

	glutPostRedisplay();  // ȭ���� �׻� ����
	glutTimerFunc(50, MyTimer, 1);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ball Game !!");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(50, MyTimer, 1);
	glutMainLoop();
}