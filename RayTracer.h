#pragma once

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Surface.h"
#include "Light.h"
#include "Intersection.h"

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