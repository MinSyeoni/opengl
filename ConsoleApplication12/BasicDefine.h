#pragma once
#pragma once

#include "stdafx.h"

#define FPS_PERSECOND 60
#define GL_PI 3.1415f
#define MOVE_FACTOR 0.5f
#define ROTATE_FACTOR 5.0f

struct Vector2D
{
	GLfloat x;
	GLfloat y;
};

struct Vector3D
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct Matirx
{
	Vector3D r1;
	Vector3D r2;
	Vector3D r3;
};


constexpr float fTransAngle = 18.0f;

inline void CreateCylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h)
{
	GLfloat x, y, angle;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_TRIANGLE_FAN);           //¿ø±âµÕÀÇ À­¸é
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(centerx, centery, centerz);
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(x, y, centerz);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);            //¿ø±âµÕÀÇ ¿·¸é
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);           //¿ø±âµÕÀÇ ¹Ø¸é
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(centerx, centery, centerz + h);
	for (angle = (2.0f*GL_PI); angle > 0.0f; angle -= (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();
}