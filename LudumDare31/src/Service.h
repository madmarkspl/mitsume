#pragma once

class CCamera;
class CRenderer;
class CWindow;

class CService
{
public:
	CService();
	~CService();

	static int* getAudio() { return _audioService; }
	static CCamera* getCamera() { return _cameraService; }
	static CRenderer* getRenderer() { return _renderService; }
	static CWindow* getWindow() { return _window; }

	static void provideAudio(int* audio)
	{
		_audioService = audio;
	}

	static void provideCamera(CCamera* camera)
	{
		_cameraService = camera;
	}

	static void provideRenderer(CRenderer* renderer)
	{
		_renderService = renderer;
	}

	static void provideWindow(CWindow* window)
	{
		_window = window;
	}

private:
	static int* _audioService;
	static CCamera* _cameraService;
	static CRenderer* _renderService;
	static CWindow* _window;
};

