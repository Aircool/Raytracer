#pragma once

#include "Intersection.h"
#include "../VectorMath.h"

class Surface {

public:

	Surface(){
		
		color = Vec3(1.0f, 1.0f, 1.0f);
	}
	
	Surface(Vec3 color) : color(color) {}
	Surface(Vec3 color, float reflect, float refract) : color(color), reflect(reflect), refract(refract) {}

	virtual Intersection intersect(Ray3 ray) = 0;
	
protected:

	Vec3 color;
	float reflect = 0.0f;
	float refract = 0.0f;
	
};