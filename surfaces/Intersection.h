#pragma once
#include "../VectorMath.h"

struct Intersection {

	Intersection(){
		
		I = Vec3();
		N = Vec3();
		T = -1.0f;
		C = Vec3();
	}
	
	Intersection(Vec3 I, Vec3 N, Vec3 C, float T) : I(I), N(N), C(C), T(T) {
		
		reflect = 0.0;
		refract = 0.0;
	}
	
	Intersection(Vec3 I, Vec3 N, Vec3 C, float T, float reflect, float refract) : I(I), N(N), C(C), T(T), reflect(reflect), refract(refract) {}

	Vec3 I;
	Vec3 N;
	Vec3 C;
	float T;
	float reflect;
	float refract;
};