// heart.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "HeartTrigonometric.h"
#include "heartLevels.h"

GLuint WIDTH = 800, HEIGHT = 800;

int main()
{
	glfwInit();

	//IDrawHeart* guanzhou = new HeartTrigonometric(WIDTH, HEIGHT, "guanzhou heart for eating");
	IDrawHeart* eating = new heartLevels(WIDTH, HEIGHT, "eating heart for guanzhou");


	// Game loop    
	while (!eating->shouldClose())
	{
		if (!eating->shouldClose())
		{
			eating->flush();
		}
		//if (!eating->shouldClose())
		//{
		//	eating->flush();
		//}
	}

	glfwTerminate();
	system("pause");
	return 0;
}
