#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include <iostream>
#include <string>

using namespace std;

int main(int, char**) {
	cout << "Hello world" << endl;
	seedRandom((unsigned int)time(nullptr));

	Renderer* renderer = new Renderer();
	renderer->Initialize();
	renderer->CreateWindow("Ray Tracer", 400, 300);
	Canvas canvas(400, 300, *renderer);
	
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ randomf(0, canvas.GetSize().x), randomf(0, canvas.GetSize().y) }, { randomf(0, 1), randomf(0, 1), randomf(0, 1), 1 });
		canvas.Update();

		renderer->PresentCanvas(canvas);
	}
	
	renderer->Shutdown();
	
	return 0;
}