#pragma once
#include <vector>

class CWindow;

class CService
{
public:
	CService();
	~CService();

	static int* getAudio() { return _audioService; }
	static CWindow* getGraphics(int index) { return _graphics.at(index); }

	static void provideAudio(int* service)
	{
			_audioService = service;
	}

	static void provideGraphics(CWindow* service)
	{
			_graphics.push_back(service);
			_graphicsService = service;
	}

private:
		static int* _audioService;
		static CWindow* _graphicsService;
		static std::vector<CWindow*> _graphics;
};

