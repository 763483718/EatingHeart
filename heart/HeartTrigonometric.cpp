#include "stdafx.h"
#include "HeartTrigonometric.h"


HeartTrigonometric::HeartTrigonometric(GLuint width, GLuint height, const char* name):IDrawHeart(width, height, name)
{
	current_size_ = 1;
	current_count_ = 0;
}


HeartTrigonometric::~HeartTrigonometric()
{
}

void HeartTrigonometric::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glfwMakeContextCurrent(window_);
	hazyEffect((3 - current_size_) * 0.3);

	DrawOne(1 - float(current_size_) * 0.15);

	if (++current_count_ == 15)
	{
		if (++current_size_ == 3)
		{
			current_size_ = 0;
		}
		current_count_ = 0;
	}
	yRot_ += 0.5;
}

void HeartTrigonometric::DrawOne(float scale)
{
	int seed = 0;
	float step = M_PI / 180;
	for (float theta = 0; theta <= M_PI / 2; theta += step)
	{
		float scaleZ = sin(theta);
		float scaleXY = cos(theta);
		DrawHeard(scale * (0.05 - float(current_size_) * 0.01), ++seed, scaleZ, scaleXY);
	}
}

void HeartTrigonometric::DrawHeard(float scale, int seed, float scaleZ, float scaleXY)
{
	glfwMakeContextCurrent(window_);
	
	srand(seed);
	glLoadIdentity();
	glRotatef(xRot_, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot_, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	glColor3ub(249, 43, 115);

	float x, y, z, theta;
	float step = 0.01f;

	for (theta = 0; theta <= 2 * M_PI; theta += step)
	{
		float randx = rand() % 100 / 500.0 - 0.1;
		float randy = rand() % 100 / 500.0 - 0.1;
		float randz = rand() % 100 / 1000.0 - 0.05;
		x = 16 * pow(sin(theta), 3);
		y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
		z = 8 * sin(theta) * scaleZ;

		x *= scale;
		y *= scale;
		z *= scale;

		x *= scaleXY;
		y *= scaleXY;

		x += randx / 5;
		y += randy / 5;

		glVertex3f(x, y, z + randz / 5);
		glVertex3f(x, y, -z + randz / 5);
	}

	glEnd();
}
