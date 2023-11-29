#pragma once
//#include "../SDL2-2.28.5/include/SDL.h"
#include <../SDL2-2.28.5/include/SDL.h>
#include <string>

class Renderer {
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);
private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};