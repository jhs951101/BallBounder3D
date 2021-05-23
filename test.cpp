#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

float ballX = 0.0;  // ballX: 공의 x좌표
float ballY = 0.0;  // ballY: 공의 y좌표
float ballmoveX = 0.1;  // ballmoveX: x값만큼 얼마나 움직이는지를 의미
float ballmoveY = -0.1;  // ballmoveY: y값만큼 얼마나 움직이는지를 의미
float ballrotate = 0.0;  // ballrotate: 공의 회전 값을 의미
double radius = 0.1;  // radius: 원의 반지름을 의미

float BarX = 0.0;  // BarX: 막대 바 왼쪽 상단 꼭지점의 x좌표
float BarRangeA = BarX;  // BarRangeA: 막대 바 왼쪽 모서리를 의미
float BarRangeB = BarX + 0.8;  // BarRangeB: 막대 바 오른쪽 모서리를 의미

GLfloat BarVertices[8][3] = {  // BarVertices[][]: 막대바의 좌표값들을 저장한 배열
	{ BarRangeA, -0.7, 0.2 },
	{ BarRangeB, -0.7, 0.2 },
	{ BarRangeB, -0.9, 0.2 },
	{ BarRangeA, -0.9, 0.2 },
	{ BarRangeA, -0.7, -0.2 },
	{ BarRangeB, -0.7, -0.2 },
	{ BarRangeB, -0.9, -0.2 },
	{ BarRangeA, -0.9, -0.2 }
};

GLfloat BarColors[8][3] = {  // BarColors[][]: 막대바의 색깔 정보를 저장한 배열
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 }
};

GLfloat WallVertices[8][3] = {  // WallVertices[][]: 모서리 벽의 좌표값들을 저장한 배열
	{ -0.05, -0.9, 0.2 },
	{ -0.05, 0.9, 0.2 },
	{ 0.05, 0.9, 0.2 },
	{ 0.05, -0.9, 0.2 },
	{ -0.05, -0.9, -0.2 },
	{ -0.05, 0.9, -0.2 },
	{ 0.05, 0.9, -0.2 },
	{ 0.05, -0.9, -0.2 }
};
GLfloat WallColors[8][3] = {  // WallColors[][]: 모서리 벽의 색깔 정보를 저장한 배열
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

GLfloat barLight0_ambient[] = { 0.0, 1.0, 1.0, 1.0 };     // 막대바 조명 특성
GLfloat barLight0_diffuse[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat barLight0_specular[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat barLightPosition[] = { 0.0, -0.7, 0.1, 1.0 };

GLfloat ballLight0_ambient[] = { 1.0, 1.0, 0.0, 1.0 };     // 공 조명 특성
GLfloat ballLight0_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat ballLight0_specular[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat ballLightPosition[] = { ballX, ballY, 0.2, 1.0 };

void checking() {

	if (ballY <= -0.8)  // 공이 바닥으로 떨어지면 게임 종료
		exit(0);

	if ((ballY <= -0.6 && (ballX >= BarRangeA && ballX <= BarRangeB + 0.1))) {  // 공이 막대 바에 부딫치면 튕기고 회전시킴
		ballmoveY = ballmoveY * -1;

		if(ballmoveX < 0) ballrotate = ballrotate + 90;  // 이 때 왼쪽에서 왔는지 오른쪽에서 왔는지에 따라 회전 방향을 달리함
		else if (ballmoveX > 0) ballrotate = ballrotate - 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;  // 360도 회전은 회전을 안한 것이나 마찬가지이므로 0도로 지정
	}

	if (ballX <= -0.7) {  // 공이 왼쪽 벽에 부딫치면 튕기고 회전시킴
		ballmoveX = ballmoveX * -1;
		
		if (ballmoveY < 0) ballrotate = ballrotate - 90;
		else if (ballmoveY > 0) ballrotate = ballrotate + 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;
	}

	if (ballX >= 0.8) {  // 공이 오른쪽 벽에 부딫치면 튕기고 회전시킴
		ballmoveX = ballmoveX * -1;

		if (ballmoveY < 0) ballrotate = ballrotate + 90;
		else if (ballmoveY > 0) ballrotate = ballrotate - 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;
	}

	if (ballY >= 0.7) {  // 공이 위쪽 벽에 부딫치면 튕기고 회전시킴
		ballmoveY = ballmoveY * -1;
		
		if (ballmoveX < 0) ballrotate = ballrotate - 90;
		else if (ballmoveX > 0) ballrotate = ballrotate + 90;

		if (ballrotate >= 360 || ballrotate <= -360) ballrotate = 0;
	}
}

void drawHexahedron() {  // 육면체를 그리는 함수
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
	drawHexahedron();  // 아래쪽 모서리에 육면체 생성

	glLoadIdentity();
	glRotatef(-15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(-0.95, -0.05, 0.0);
	drawHexahedron();  // 왼쪽 모서리에 육면체 생성

	glLoadIdentity();
	glRotatef(-15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(0.95, 0.05, 0.0);
	drawHexahedron();  // 오른쪽 모서리에 육면체 생성

	glLoadIdentity();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glRotatef(15.0, -1.0, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(0.95, -0.1, 0.0);
	drawHexahedron();  // 위쪽 모서리에 육면체 생성

	glLoadIdentity();
	glShadeModel(GL_SMOOTH);    //구로 셰이딩
	glEnable(GL_DEPTH_TEST);    //깊이 버퍼 활성화
	glEnable(GL_LIGHTING);      //조명 활성화
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

	drawHexahedron();  // 막대바 생성

	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_AMBIENT, ballLight0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ballLight0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ballLight0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, ballLightPosition);

	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(ballX, ballY, 0.0);
	glRotatef(ballrotate, 0, 0, 1.0);
	glutSolidSphere(0.1, 50.0, 50.0);  // 공 생성
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
	case 'a':  // 'a' 키를 누르면 막대바가 왼쪽으로 이동
		if(BarRangeA >= -0.95) BarX = BarX - 0.1;  // 단, 막대바가 왼쪽이나 오른쪽 끝에 있는 경우 이동 안함
		break;
	case 'd':  // 'd' 키를 누르면 막대바가 오른쪽으로 이동
		if(BarRangeB <= 0.85) BarX = BarX + 0.1;  
		break;
	case 27:  // 'Esc' 키를 누르면 바로 게임 종료
		exit(0);
		break;
	}

	BarRangeA = BarX;  // 막대 바 두 모서리 값을 항상 지정해줌
	BarRangeB = BarX + 0.8;

	BarVertices[0][0] = BarRangeA;
	BarVertices[1][0] = BarRangeB;
	BarVertices[2][0] = BarRangeB;
	BarVertices[3][0] = BarRangeA;
	BarVertices[4][0] = BarRangeA;
	BarVertices[5][0] = BarRangeB;
	BarVertices[6][0] = BarRangeB;
	BarVertices[7][0] = BarRangeA;  // 막대바가 움직이면 x좌표 값이 항상 변화하도록 함
}

void MyTimer(int Value) {  // 애니메이션처럼 보이게 하기 위해 타이머를 사용

	checking();

	ballX = ballX + ballmoveX;
	ballY = ballY + ballmoveY;  // 공의 위치를 변경

	glutPostRedisplay();  // 화면을 항상 리셋
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