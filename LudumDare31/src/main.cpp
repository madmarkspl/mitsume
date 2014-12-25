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
#include "Service.h"
#include "Window.h"
#include "Game.h"
#include "IntroState.h"
#include "PlayState.h"
#include "Camera.h"

int main()
{
	initscr();
	std::list<GLdouble> fpsData(1000);
	srand((unsigned int)time(NULL));
	CWindow* mainWindow = new CWindow("Test", 1280, 720);

	CCamera camera;
	CService::provideCamera(&camera);

	CShader program("shader/basic.vert", "shader/basic.frag");
	mainWindow->addShaderProgram("basic", program);
	CService::provideGraphics(mainWindow);

	CGame mitsume;
	mainWindow->attachCallbackPointer(&mitsume);
	mitsume.pushState(new CPlayState());

	GLdouble previousFrameTime = glfwGetTime();
	GLdouble lagTime = 0.0;
	GLuint frameCount = 0;
	//GLdouble updateFPS;
	GLdouble renderFPS;

	while (!mainWindow->closeCondition())
	{
		clear();
		GLdouble currentFrameTime = glfwGetTime();
		GLdouble elapsedTime = (currentFrameTime - previousFrameTime);
		previousFrameTime = currentFrameTime;
		lagTime += elapsedTime;

		fpsData.push_back(elapsedTime);
		fpsData.pop_front();
		//mitsume.handleInput();
		glfwPollEvents();

		while (lagTime >= 0.02)
		{
			mitsume.update();
			lagTime -= 0.02;	
		}

		//Sleep(20);

		mitsume.draw(lagTime / 0.02);

		renderFPS = 0;
		for (GLdouble f : fpsData)
		{
			renderFPS += f;
		}
		renderFPS /= 1000;
		renderFPS = 1.0 / renderFPS;
		//std::cout << renderFPS << "\t" << fpsData.size() << std::endl;
		frameCount++;
	}

	return 0;
}
