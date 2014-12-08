#pragma once
#include <vector>

class CWindow;
class CCamera;

class CService
{
public:
	CService();
	~CService();

	static int* getAudio() { return _audioService; }
	static CWindow* getGraphics() { return _graphicsService; }
	static CCamera* getCamera() { return _cameraService; }

	static void provideAudio(int* service)
	{
		_audioService = service;
	}

	static void provideGraphics(CWindow* service)
	{
		_graphicsService = service;
	}

	static void provideCamera(CCamera* camera)
	{
		_cameraService = camera;
	}

private:
	static int* _audioService;
	static CWindow* _graphicsService;
	static CCamera* _cameraService;
};

