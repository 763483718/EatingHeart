#include "stdafx.h"
#include "IDrawHeart.h"

std::map<GLFWwindow*, IDrawHeart*> IDrawHeart::map_;

IDrawHeart::IDrawHeart(GLuint width, GLuint height, const char* name)
{
	window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (window_ == nullptr)
	{
		glfwDestroyWindow(window_);
		return;
	}

	initWindow();

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window_);
		return;
	}

	initParam();

	IDrawHeart::map_[window_] = this;
}


IDrawHeart::~IDrawHeart()
{
	for (auto it = IDrawHeart::map_.begin(); it != IDrawHeart::map_.end(); ++it)
	{
		if (it->second == this)
		{
			IDrawHeart::map_.erase(it);
		}
	}
}

void IDrawHeart::flush()
{
	glfwPollEvents();
	render();
	swapBuffers();
}

bool IDrawHeart::shouldClose()
{
	return glfwWindowShouldClose(window_);
}

void IDrawHeart::swapBuffers()
{
	glfwSwapBuffers(window_);
}

void IDrawHeart::initParam()
{
	glViewport(0, 0, width_, height_);
	glLineWidth(3.0);

	glEnable(GL_BLEND);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void IDrawHeart::hazyEffect(float blink)
{
	glBegin(GL_POINTS);
	float x, y, z;
	for (int i = 0; i < 2000; ++i)
	{
		x = static_cast<double>(rand()) / (RAND_MAX / 4.0) - 2.0;
		y = static_cast<double>(rand()) / (RAND_MAX / 4.0) - 2.0;
		z = static_cast<double>(rand()) / (RAND_MAX / 4.0) - 2.0;

		glVertex3f(x + blink, y + blink, z + blink);
		glVertex3f(x - blink, y - blink, z - blink);
	}
	glEnd();
}

void IDrawHeart::initWindow()
{
	glfwMakeContextCurrent(window_);
	
	glfwSetKeyCallback(window_, IDrawHeart::key_callback);

	glfwSetWindowSizeCallback(window_, IDrawHeart::windowResize_callback);
}

void IDrawHeart::resizeWindow(int width, int height)
{
	width_ = height_ = width > height ? height : width;

	glViewport((width - width_) / 2, (height - height_) / 2, width_, height_);
}
