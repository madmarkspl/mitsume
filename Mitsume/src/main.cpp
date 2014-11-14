#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
//#include <cstdio>
//#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

#include "Service.h"
#include "Window.h"
#include "Game.h"
#include "IntroState.h"

int main()
{
	CWindow* mainWindow = new CWindow("Test", 640, 480);
	CShader program("shader/basic.vert", "shader/basic.frag");
	mainWindow->addShaderProgram("basic", program);
	CService::provideGraphics(mainWindow);

	CGame mitsume;
	mitsume.pushState(new CIntroState());

	GLdouble previousFrameTime = glfwGetTime();
	GLdouble lagTime = 0.0;

	while (!mainWindow->closeCondition())
	{
		GLdouble currentFrameTime = glfwGetTime();
		GLdouble elapsedTime = (currentFrameTime - previousFrameTime) * 1000;
		previousFrameTime = currentFrameTime;
		lagTime += elapsedTime;

		mitsume.handleEvents();
		glfwPollEvents();

		while (lagTime >= 20)
		{
			mitsume.update();
			lagTime -= 20;	
		}

		Sleep(20);

		mitsume.draw(lagTime / 20.0);
	}

	return 0;
}
