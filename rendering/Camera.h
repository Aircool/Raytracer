#pragma once

#include <iostream>
#include "../Constants.h"
#include "../VectorMath.h"

class Camera {

public:

	bool once = true;

	// Assumes normalized Direction vector input
	Camera(Vec3 position, Vec3 direction) : position(position), direction(direction) {
		
		// Probably can't look straight up or down, as that would be parallel to (0, 1, 0)... 
		Vec3 up = direction.cross(Vec3(0, 1, 0)).cross(direction);
		
		Vec3 ux = up.cross(direction).normalized();
		Vec3 uz = direction;
		Vec3 uy = uz.cross(ux);
		
		camera_x = ux;
		camera_y = uy;
	}
	
	Ray3 castRay(int x, int y){
		
		// Ranges from -0.5 to 0.5, to determine how far the current pixel is from the center in each direction.
		float p_x = (x + 0.5f) - 0.5f * WIDTH;
		float p_y = 0.5f * HEIGHT - (y + 0.5f);
		
		Vec3 point = position + (p_x * camera_x) + (p_y * camera_y) + (direction * FOCAL_LENGTH);
		return Ray3(position, (point - position).normalized());
	}
	
private:

	Vec3 jitter(float length){
		
		float r0 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		
		return Vec3(length * (-0.5 + r0), length * (-0.5 + r1), 0.0) + position;
	}

	Vec3 position;
	Vec3 direction;
	
	Vec3 camera_x;
	Vec3 camera_y;
	
};