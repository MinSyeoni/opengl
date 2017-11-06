#include<GL/glut.h>

GLfloat cubeX = 0.0;
GLfloat cubeSpeedX = 0.03;
GLfloat cube1RotateAngleY = 0;
GLfloat cube2RotateAngleX = 0;
GLfloat cube2RotateAngleY = 0;
GLfloat cube3RotateAngleX = 0;
GLfloat cube3RotateAngleZ = 0;

void SetupRC() {
	glEnable(GL_DEPTH_TEST);
}
void DrawCube() {
	// 맨아래 정육면체
	glBegin(GL_QUADS);

	// 윗면 (y = 2.0)
	glVertex3f(1.0, 2.0, -1.0);
	glVertex3f(-1.0, 2.0, -1.0);
	glVertex3f(-1.0, 2.0, 1.0);
	glVertex3f(1.0, 2.0, 1.0);

	// 아랫면 (y = 0.0)
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(-1.0, 0.0, 1.0);
	glVertex3f(-1.0, 0.0, -1.0);
	glVertex3f(1.0, 0.0, -1.0);

	// 앞면  (z = 1.0)
	glVertex3f(1.0, 2.0, 1.0);
	glVertex3f(-1.0, 2.0, 1.0);
	glVertex3f(-1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);

	// 뒷면 (z = -1.0)
	glVertex3f(1.0, 0.0, -1.0);
	glVertex3f(-1.0, 0.0, -1.0);
	glVertex3f(-1.0, 2.0, -1.0);
	glVertex3f(1.0, 2.0, -1.0);

	// 왼쪽면 (x = -1.0)
	glVertex3f(-1.0, 2.0, 1.0);
	glVertex3f(-1.0, 2.0, -1.0);
	glVertex3f(-1.0, 0.0, -1.0);
	glVertex3f(-1.0, 0.0, 1.0);

	// 오른쪽면 (x = 1.0)
	glVertex3f(1.0, 2.0, -1.0);
	glVertex3f(1.0, 2.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, -1.0);

	glEnd();
}

void DrawFloor() {
	glBegin(GL_POLYGON);
	glVertex3f(2.0, 0.0, -10.0);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glVertex3f(-2.0, 0.0, -10.0);
	glEnd();
}

void ChangeTransformParameters() {
	if (cubeX > 2 || cubeX < -2)
		cubeSpeedX *= -1;
	cubeX += cubeSpeedX;
}

void DrawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(0, -1.5, -5);
	glColor3f(1, 1, 1);
	DrawFloor();

	// 맨 아래 육면체
	glTranslatef(cubeX, 0, 0);
	glColor3f(1, 0, 0);
	glRotatef(cube1RotateAngleY, 0, 1, 0);
	glScalef(0.3, 0.3, 0.2);
	DrawCube();

	// 중간 육면체
	glColor3f(0, 0, 1);
	glTranslatef(0, 2, 0);
	glScalef(0.3, 0.8, 0.5);
	glRotatef(cube2RotateAngleY, 0, 1, 0);
	glRotatef(cube2RotateAngleX, 1, 0, 0);
	DrawCube();

	// 윗 육면체
	glColor3f(0, 1, 0);
	glTranslatef(0, 2, 0);
	glScalef(0.7, 0.6, 0.6);
	glRotatef(cube3RotateAngleZ, 0, 0, 1);
	glRotatef(cube3RotateAngleX, 1, 0, 1);
	DrawCube();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1f, 100.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		cube1RotateAngleY += 6;
		break;
	case 'Y':
		cube1RotateAngleY -= 6;
		break;
	case 'a':
		cube2RotateAngleY += 6;
		break;
	case 'd':
		cube2RotateAngleY -= 6;
		break;
	case 'w':
		if (cube2RotateAngleX < 90)
			cube2RotateAngleX += 6;
		break;
	case 's':
		if (cube2RotateAngleX > -90)
			cube2RotateAngleX -= 6;
		break;
	case 'j':
		if (cube3RotateAngleZ < 90)
			cube3RotateAngleZ += 6;
		break;
	case 'l':
		if (cube3RotateAngleZ > -90)
			cube3RotateAngleZ -= 6;
		break;
	case 'i':
		if (cube3RotateAngleX < 90)
			cube3RotateAngleX += 6;
		break;
	case 'k':
		if (cube3RotateAngleX > -90)
			cube3RotateAngleX -= 6;
		break;
	}
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
	ChangeTransformParameters();
	glutTimerFunc(10, TimerFunction, 1);
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Points Drawing");
	// 상태 변수 초기화 함수
	SetupRC();
	// 필요한 콜백 함수 설정
	glutDisplayFunc(DrawScene); // 출력 콜백 함수
	glutReshapeFunc(Reshape); // 다시 그리기 콜백 함수
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(10, TimerFunction, 1); // 타이머 콜백 함수
	glutMainLoop(); // 이벤트 루프 실행하기
}