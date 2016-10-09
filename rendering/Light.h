#pragma once
#include <vector>

#include "..//surfaces//Intersection.h"
#include "../surfaces//Surface.h"
#include "../Constants.h"
#include "../VectorMath.h"

class Light {

public:

	Light(Vec3 position, Vec3 color, float intensity) : position(position), color(color), intensity(intensity) {}

	Vec3 calculateLighting(std::vector<Surface*>* S, Ray3 R, Intersection I){
		
		Vec3 L;
		
		if(JITTER)	L = (jitter(1) - I.I);
		else		L = position - I.I;
		
		float MAX_DIST = (L - I.I).norm();
		L.normalize();
		
		Ray3 LRay(I.I, L);
		if(intersect(S, LRay, MAX_DIST)) return Vec3();
		
		float diffuse = L.dot(I.N);
		float specular = L.reflect(I.N).dot(R.D * -1.0f);
		
		Vec3 C = Vec3();
		if(diffuse  > 1e-4) C += color * intensity * diffuse * DIFFUSE_COEFF;
		if(specular > 1e-4) C += color * intensity * pow(specular, 32) * SPECULAR_COEFF;
		return C;
	}
	
private:
	
	bool intersect(std::vector<Surface *>* S, Ray3 ray, float MAX_DIST){
		
		for(auto surface : *S){
			
			Intersection I = surface->intersect(ray);
			if(I.T > 0.0f && I.T < MAX_DIST){
				return true;
			}
		}

		return false;
	}
	
	Vec3 jitter(float length){
		
		float r0 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		
		return Vec3(length * (-0.5 + r0), length * (-0.5 + r1), 0.0) + position;
	}
	
	Vec3 position;
	Vec3 color;
	float intensity;
};