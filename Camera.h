#pragma once

#include "Constants.h"
#include "VectorMath.h"

class Camera {

public:

	// Assumes normalized Direction vector input
	Camera(Vec3 position, Vec3 direction) : position(position), direction(direction) {
		
		// Probably can't look straight up or down, as that would be parallel to (0, 1, 0)... 
		Vec3 up = (Vec3(0.0f, 1.0f, 0.0f)).cross(direction).cross(direction);
		
		Vec3 ux = direction.cross(up).normalized();
		Vec3 uz = direction;
		Vec3 uy = uz.cross(ux);
		
		camera_x = ux;
		camera_y = uy;
	}
	
	Ray3 castRay(int x, int y){
		
		// Ranges from -0.5 to 0.5, to determine how far the current pixel is from the center in each direction.
		float p_x = (((float) x) / WIDTH) - 0.5f;
		float p_y = (((float) y) / HEIGHT) - 0.5f;
		
		float aperture_x = p_x * APERTURE_WIDTH;
		float aperture_y = p_y * APERTURE_HEIGHT;
		
		float lens_x = p_x * LENS_WIDTH;
		float lens_y = p_y * LENS_HEIGHT;
		
		Vec3 aperture_point = position + (camera_x * aperture_x) + (camera_y * aperture_y);
		Vec3 lens_point = position + (camera_x * lens_x) + (camera_y * lens_y) + (direction * FOCAL_LENGTH);
		
		return Ray3(aperture_point, (lens_point - aperture_point).normalized());
	}
	
private:

	Vec3 position;
	Vec3 direction;
	
	Vec3 camera_x;
	Vec3 camera_y;
	
};