#pragma once

#include <iostream>
#include <vector>

#include "rendering/Camera.h"
#include "rendering/Light.h"
#include "rendering/Intersection.h"

#include "surfaces/Surface.h"

#include "Constants.h"
#include "VectorMath.h"

class RayTracer {
	
public:

	RayTracer();
	
	Vec3 rayTrace(int x, int y);
	Vec3 rayTrace(Ray3 ray);
	
private:

	Camera* camera;
	
	std::vector<Surface> surfaces;
	std::vector<Light> lights;
};