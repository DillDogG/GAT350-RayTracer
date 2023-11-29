#include "Renderer.h"
#include <iostream>
#include <string>

using namespace std;

int main(int, char**) {
	cout << "Hello world" << endl;

	Renderer* renderer = new Renderer();
	renderer->Initialize();
	renderer->CreateWindow("Ray Tracer", 400, 300);
	
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
	}
	
	renderer->Shutdown();
	
	return 0;
}