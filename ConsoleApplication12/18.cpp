#include <GL/glut.h>
#include "stdafx.h"
#include "RuntimeFrameWokr.h"

GLUquadricObj *qobj;
GLfloat sphereRotateX = 0;
GLfloat sphereRotateY = 0;
GLfloat sphereRotateZ = 0;
GLfloat Xpos = 0;
GLfloat Ypos = 0;
GLfloat Zpos = 0;
GLfloat m_mtxLocal[16];

void SetupRC() 
{
	glEnable(GL_DEPTH_TEST);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1f, 100.0);
}

void DrawFloor()
{
	glBegin(GL_POLYGON);
	glVertex3f(2.0, 0.0, -2.0);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glVertex3f(-2.0, 0.0, -2.0);
	glEnd();
}

void DrawY()
{
	glBegin(GL_LINES);
	glVertex2f(0.0, 2.0);
	glVertex2f(0.0, -1.0);
	glEnd();
}

void Sphere()
{
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluQuadricNormals(qobj, GLU_SMOOTH);   // ���� ����  
	gluQuadricOrientation(qobj, GLU_OUTSIDE);  // ���� ����
	gluSphere(qobj, 1.5, 10, 10);
}

void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glColor3f(1, 1, 0);
	glTranslatef(0, -1.5, -6);
	DrawFloor();

	glColor3f(0, 1, 0);
	DrawY();

	m_mtxLocal[0] = m_mtxLocal[5] = m_mtxLocal[10] = m_mtxLocal[15] = 1;   // �������.

	glColor3f(1, 0, 1);
	glTranslatef(Xpos, 0.3 + Ypos, Zpos);
	glRotatef(sphereRotateX, 1, 0, 0);
	glRotatef(sphereRotateY, 0, 1, 0);
	glRotatef(sphereRotateZ, 0, 0, 1);
	glScalef(0.2, 0.2, 0.2);
	Sphere();

	glFlush();
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(10, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i'://�ʱ�ȭ
	case 'I':
		sphereRotateX = 0;
		sphereRotateY = 0;
		sphereRotateZ = 0;
		Xpos = 0;
		Ypos = 0;
		Zpos = 0;
		break;
	case 'l': //x�� ���� �� ȸ���ϸ鼭 ȸ���������� �̵�
		glPushMatrix();
		{
			glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
			glMultMatrixf(m_mtxLocal);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mtxLocal);
			sphereRotateX += 10;
		}
		glPopMatrix();
		if (Xpos < 2) 
			Xpos += 0.05;
		break;
	case 'L': //x�� ���� �� ȸ���ϸ鼭 ȸ���������� �̵�
		glPushMatrix();
		{
			glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
			glMultMatrixf(m_mtxLocal);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mtxLocal);
			sphereRotateX -= 10;
		}
		glPopMatrix();
		if(Xpos > -2)
			Xpos -= 0.05;
		break;
	case 'm': //Y�� ���� �� ȸ���ϸ鼭 ȸ���������� �̵�
		glPushMatrix();
		{
			glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glMultMatrixf(m_mtxLocal);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mtxLocal);
			sphereRotateY += 10;
		}
		break;
	case 'M': //Y�� ���� �� ȸ���ϸ鼭 ȸ���������� �̵�      
		glPushMatrix();
		{
			glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
			glMultMatrixf(m_mtxLocal);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mtxLocal);
			sphereRotateY -= 10;
		}		break;
	case 'n': //Z�� ���� �� ȸ���ϸ鼭 ȸ���������� �̵�
		glPushMatrix();
		{
			glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
			glMultMatrixf(m_mtxLocal);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mtxLocal);
			sphereRotateZ += 10;
		}
		if(Zpos < 2)
		Zpos += 0.05;
		break;
	case 'N': //Z�� ���� �� ȸ���ϸ鼭 ȸ���������� �̵�
		glPushMatrix();
		{
			glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
			glMultMatrixf(m_mtxLocal);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_mtxLocal);
			sphereRotateZ -= 10;
		}
		if(Zpos > -2)
		Zpos -= 0.05;
		break;
	}
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Points Drawing");
	// ���� ���� �ʱ�ȭ �Լ�
	SetupRC();
	// �ʿ��� �ݹ� �Լ� ����
	glutDisplayFunc(DrawScene); // ��� �ݹ� �Լ�
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ� �Լ�
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸� �ݹ� �Լ�
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // �̺�Ʈ ���� �����ϱ�
}