#pragma once

#include "../Constants.h"
#include "../VectorMath.h"

class Camera {

public:

	// Assumes normalized Direction vector input
	Camera(Vec3 position, Vec3 direction) : position(position), direction(direction) {
		
		Vec3 up(0.0f, 1.0f, 0.0);
		if(direction[0] == up[0] direction[1] == up[1] && direction[2] == up[2]) up = Vec3(0, 0, -1.0f);
		
		Vec3 ux = up.cross(direction).normalized();
		Vec3 uz = direction;
		Vec3 uy = uz.cross(ux);
		
		camera_x = ux;
		camera_y = uy;
	}
	
	Ray3 castRay(float x, float y){
		
		// Ranges from -0.5 to 0.5, to determine how far the current pixel is from the center in each direction.
		float p_x = (x + 0.5f) - 0.5f * WIDTH;
		float p_y = 0.5f * HEIGHT - (y + 0.5f);
		
		Vec3 point = position + (p_x * camera_x) + (p_y * camera_y) + (direction * FOCAL_LENGTH);
		return Ray3(position, (point - position).normalized());
	}
	
	Vec3 getRelativeX(){
		
		return camera_x;
	}
	
	Vec3 getRelativeY(){
		
		return camera_y;
	}
	
private:

	Vec3 position;
	Vec3 direction;
	
	Vec3 camera_x;
	Vec3 camera_y;
	
};