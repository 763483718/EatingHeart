#pragma once

#include <glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class IDrawHeart
{
public:
	IDrawHeart(GLuint width, GLuint height, const char* name);
	virtual ~IDrawHeart();
	virtual void render() = 0;
	

	void flush();
	bool shouldClose();
	void swapBuffers();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		auto p = IDrawHeart::map_[window];
		if (key == GLFW_KEY_UP)
			p->xRot_ -= 5.0f;

		else if (key == GLFW_KEY_DOWN)
			p->xRot_ += 5.0f;

		else if (key == GLFW_KEY_LEFT)
			p->yRot_ -= 5.0f;

		else if (key == GLFW_KEY_RIGHT)
			p->yRot_ += 5.0f;
	}

	static void windowResize_callback(GLFWwindow* window, int width, int height)
	{
		auto p = IDrawHeart::map_[window];
		p->resizeWindow(width, height);
	}

protected:
	virtual void initWindow();
	virtual void initParam();
	virtual void hazyEffect(float blink = 1);
	virtual void resizeWindow(int width, int height);

protected:
	GLuint width_ = 800, height_ = 800;

	GLfloat xRot_ = 0.0f;
	GLfloat yRot_ = 0.0f;
	GLFWwindow* window_;
	static std::map<GLFWwindow*, IDrawHeart*> map_;
};

