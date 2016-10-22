#include "VectorMath.h"

Vec3 operator*(float scalar, Vec3 V){
	
	return Vec3(V[0] * scalar, V[1] * scalar, V[2] * scalar);
}

Vec3 jitter(float length){
		
	float r0 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		
	return Vec3(length * (-0.5 + r0), length * (-0.5 + r1), 0.0);
}