//#include <vld.h>
#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <Windows.h>
#include <curses.h>
//#include <cstdio>
//#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Game.h"
#include "IntroState.h"
#include "PlayState.h"
#include "Renderer.h"
#include "Service.h"
#include "Window.h"

int main()
{
	initscr();
	std::list<GLdouble> fpsData(1000);
	srand((unsigned int)time(NULL));

	CWindow mainWindow("Test", 1280, 720);
	CCamera camera;
	CRenderer renderer;

	CShader program("shader/basic.vert", "shader/basic.frag");
	renderer.addShaderProgram("basic", program);
	
	CGame mitsume;
	mainWindow.attachCallbackPointer(&mitsume);
	mitsume.pushState(new CPlayState());

	CService::provideCamera(&camera);
	CService::provideRenderer(&renderer);
	CService::provideWindow(&mainWindow);

	GLdouble previousFrameTime = glfwGetTime();
	GLdouble lagTime = 0.0;
	GLuint frameCount = 0;
	GLdouble fpsLast = previousFrameTime;
	GLuint cpu = 0;

	while (!mainWindow.closeCondition())
	{
		clear();
		++frameCount;
		GLdouble currentFrameTime  = glfwGetTime();
		GLdouble elapsedTime = (currentFrameTime - previousFrameTime);
		previousFrameTime = currentFrameTime;
		lagTime += elapsedTime;

		if (currentFrameTime - fpsLast >= 1.0)
		{
			std::cout << "ms: " << 1000.0/double(frameCount) << "\tframes: " << frameCount << "\tcpu: " << cpu << std::endl;
			frameCount = 0;
			cpu = 0;
			fpsLast = currentFrameTime;
		}

		//mitsume.handleInput();
		glfwPollEvents();

		while (lagTime >= 0.02)
		{
			mitsume.update();
			lagTime -= 0.02;	
			++cpu;
		}

		//Sleep(20);

		mitsume.draw(lagTime / 0.02);
	}

	return 0;
}
