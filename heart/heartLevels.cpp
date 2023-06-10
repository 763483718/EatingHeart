#include "stdafx.h"
#include "heartLevels.h"


heartLevels::heartLevels(GLuint width, GLuint height, const char* name):IDrawHeart(width, height, name)
{
}


heartLevels::~heartLevels()
{
}

void heartLevels::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glfwMakeContextCurrent(window_);
	hazyEffect((3 - current_size_) * 0.3);

	DrawOneLevel(1 - float(current_size_) * 0.15);

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

void heartLevels::DrawOneLevel(float scale)
{
	int seed = 0;
	float step = M_PI / 180;
	for (float theta = 0; theta <= M_PI / 2; theta += step)
	{
		float z = sin(theta) / 4;
		DrawHeard(scale * (0.05 - float(current_size_) * 0.01) * cos(theta), ++seed, z);
	}
}

void heartLevels::DrawHeard(float scale, int seed, float z)
{
	glfwMakeContextCurrent(window_);
	srand(seed);
	glLoadIdentity();
	glRotatef(xRot_, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot_, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	glColor3ub(249, 43, 115);

	float x, y, theta;
	float step = 0.01f;

	for (theta = 0; theta <= 2 * M_PI; theta += step)
	{
		float randx = rand() % 100 / 500.0 - 0.1;
		float randy = rand() % 100 / 500.0 - 0.1;
		float randz = rand() % 100 / 1000.0 - 0.05;
		x = 16 * pow(sin(theta), 3);
		y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);

		x *= scale;
		y *= scale;

		x += randx / 5;
		y += randy / 5;

		glVertex3f(x, y, z + randz / 5);
		glVertex3f(x, y, -z + randz / 5);
	}

	glEnd();
}
