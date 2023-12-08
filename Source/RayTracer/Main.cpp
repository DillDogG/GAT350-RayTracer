#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"
#include <iostream>
#include <string>

using namespace std;

const int width = 400;
const int height = 300;
const int samples = 20;
const int depth = 5;

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);

int main(int, char**) {
	cout << "Hello world" << endl;
	seedRandom((unsigned int)time(nullptr));

	Renderer* renderer = new Renderer();
	renderer->Initialize();
	renderer->CreateWindow("Ray Tracer", width, height);
	Canvas canvas(width, height, *renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	//std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f }); // sky color could be set with the top and bottom color
	InitScene01(scene, canvas);
	scene.SetCamera(camera);
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	//for (int i = 0; i < 16; i++) {
	//	auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -0.5 }, glm::vec3{ 0.5 }), randomf(0.0625, 0.25), material);
	//	scene.AddObject(std::move(sphere));
	//}
	// create material
	//auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	//auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	//for (int i = 0; i < 10; i++)
	//{
	//	std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(lambertian);
	//	auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -0.5 }, glm::vec3{ 0.5 }), randomf(0.0625, 0.25), material);
	//	scene.AddObject(std::move(sphere));
	//}

	//for (int x = -10; x < 10; x++)
	//{
	//	for (int z = -10; z < 10; z++)
	//	{
	//
	//		std::shared_ptr<Material> material;
	//
	//		// create random material
	//		float r = randomf();
	//		if (r < 0.3f)		material = std::make_shared<Lambertian>(color3_t(glm::vec3{ randomf(0, 360), 1.0f, 1.0f }));
	//		else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ randomf(0.5f, 1.0f) }, randomf(0, 0.5f));
	//		else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, randomf(0.8f, 1.5f));
	//		else				material = std::make_shared<Emissive>(color3_t(glm::vec3{ randomf(0, 360), 1.0f, 1.0f }), 2.5f);
	//
	//		// set random sphere radius
	//		float radius = randomf(0.2f, 0.3f);
	//		// create sphere using random radius and material
	//		auto sphere = std::make_unique<Sphere>(glm::vec3{ x + randomf(-0.5f, 0.5f), radius, z + randomf(-0.5f, 0.5f) }, radius, material);
	//		// add sphere to the scene
	//		scene.AddObject(std::move(sphere));
	//	}
	//}
	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));


	//material = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	//auto tri = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, material);
	//scene.AddObject(std::move(tri));

	material = std::make_shared<Lambertian>(color3_t{ 0.2f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));
	scene.Render(canvas, samples, depth);
	canvas.Update();

	renderer->PresentCanvas(canvas);
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
		//for (int i = 0; i < 1000; i++) canvas.DrawPoint({ randomf(0, canvas.GetSize().x), randomf(0, canvas.GetSize().y) }, { randomf(0, 1), randomf(0, 1), randomf(0, 1), 1 });
		
	}
	
	renderer->Shutdown();
	
	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++) {
		for (int z = -10; z < 10; z++) {
			std::shared_ptr<Material> material;

			// create random material
			float r = randomf();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(color3_t(glm::vec3{ randomf(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ randomf(0.5f, 1.0f) }, randomf(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, randomf(1.1f, 2));
			else				material = std::make_shared<Emissive>(color3_t(glm::vec3{ randomf(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = randomf(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + randomf(-0.5f, 0.5f), radius, z + randomf(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}