#pragma once
#include <vector>

class CWindow;

class CService
{
public:
	CService();
	~CService();

	static int* getAudio() { return _audioService; }
	static CWindow* getGraphics(int index) { return _graphicsService; }

	static void provideAudio(int* service)
	{
		_audioService = service;
	}

	static void provideGraphics(CWindow* service)
	{
		_graphicsService = service;
	}

private:
	static int* _audioService;
	static CWindow* _graphicsService;
};

