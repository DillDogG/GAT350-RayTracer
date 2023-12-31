#include "Scene.h"
#include "Canvas.h"
#include "Random.h"
#include "MathUtils.h"
//#include "Sphere.h"
#include <iostream>
#include <iomanip>

void Scene::Render(Canvas& canvas, int numSamples, int depth) {
	{
		// create vec2 pixel from canvas x,y

		// set initial color
		// cast a ray for each sample, accumulate color value for each sample
		// each ray will have a random offset
		for (int y = 0; y < canvas.GetSize().y; y++) {
			for (int x = 0; x < canvas.GetSize().x; x++) {
				glm::vec2 pixel = glm::vec2{ x, y };
				color3_t color{ 0 };
				for (int i = 0; i < numSamples; i++) {
					// get normalized (0 - 1) point coordinates from pixel
					// add random x and y offset (0-1) to each pixel
					glm::vec2 point = (pixel + glm::vec2{ randomf(), randomf() }) / (glm::vec2)canvas.GetSize();
					// flip y
					point.y = 1.0f - point.y;

					// create ray from camera
					ray_t ray = m_camera->GetRay(point);

					// cast ray into scene
					// add color value from trace
					raycastHit_t raycastHit;
					color += Trace(ray, 0, 100, raycastHit, depth);
				}
				color /= numSamples;
				canvas.DrawPoint(pixel, color4_t(color, 1));
			}
			std::cout << std::setprecision(2) << std::setw(5) << (((float)y / canvas.GetSize().y) * 100) << "%\n";
		}
		// draw color to canvas point (pixel)
		// get average color (average = (color + color + color) / number of samples)
		//<divide color by number of samples>
	}
}

//color3_t Scene::Trace(const ray_t& ray) {
//	glm::vec3 direction = glm::normalize(ray.direction);
//
//	// set scene sky color
//	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
//	color3_t color = Lerp(m_topColor, m_bottomColor, t);
//
//	return color;
//}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth) {
	bool rayHit = false;
	float closestDistance = maxDistance;

	// check if scene objects are hit by the ray
	for (auto& object : m_objects) {
		// when checking objects don't include objects farther than closest hit (starts at max distance)
		if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	// if ray hit object, scatter (bounce) ray and check for next hit
	if (rayHit)
	{
		ray_t scattered;
		color3_t color;
		color3_t emissive = raycastHit.material->GetEmissive();

		// check if maximum depth (number of bounces) is reached, get color from material and scattered ray
		if (raycastHit.material->Scatter(ray, raycastHit, color, scattered)) {
			// recursive function, call self and modulate colors of depth bounces
			return emissive + color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
		}
		else {
			// reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
			return emissive;
		}
	}
	// if ray not hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	color3_t color = Lerp(m_bottomColor, m_topColor, t);
	
	return color;
}