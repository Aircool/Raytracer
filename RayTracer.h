#pragma once

#include <vector>

#include "rendering/Camera.h"
#include "rendering/Light.h"

#include "surfaces/Surface.h"
#include "surfaces/Intersection.h"
#include "surfaces/Sphere.h"
#include "surfaces/Triangle.h"

#include "Constants.h"
#include "VectorMath.h"

class RayTracer {
	
public:

	RayTracer();
	
	Vec3 rayTrace(int x, int y);
	Vec3 rayTrace(Ray3 ray);
	Intersection intersect(Ray3 ray);
	Vec3 calculateColor(Ray3 ray, Intersection intersection);
	
private:

	Camera* camera;
	
	std::vector<Surface*> surfaces;
	std::vector<Light*> lights;
};