#pragma once
#include <vector>

#include "..//surfaces//Intersection.h"
#include "../surfaces//Surface.h"
#include "../Constants.h"
#include "../VectorMath.h"

class Light {

public:

	Light(Vec3 position, Vec3 color, float intensity) : position(position), color(color), intensity(intensity) {}
	Light(Vec3 position, Vec3 direction, Vec3 color, float intensity) : position(position), direction(direction), color(color), intensity(intensity) {
		
		Vec3 up(0.0f, 1.0f, 0.0f);
		if(direction[0] == up[0] && direction[1] == up[1] && direction[2] == up[2]) up = Vec3(0, 0, -1.0f);
		
		Vec3 ux = up.cross(direction).normalized();
		Vec3 uz = direction;
		Vec3 uy = uz.cross(ux);
		
		light_x = ux;
		light_y = uy;
	}

	Vec3 calculateLighting(std::vector<Surface*>* S, Ray3 R, Intersection I){
		
		Vec3 L = position - I.I;
		if(ENABLE_AREA_LIGHTING){
			
			Vec3 jitterVal = jitter(1.0f);
			L = position + (light_x * jitterVal[0]) + (light_y * jitterVal[1]) - I.I; 
		}
		
		float MAX_DIST = (L - I.I).norm();
		L.normalize();
		
		Ray3 LRay(I.I, L);
		if(intersect(S, LRay, MAX_DIST)) return Vec3();
		
		float diffuse = L.dot(I.N);
		float specular = L.reflect(I.N).dot(R.D);
		
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
	
	Vec3 position;
	Vec3 direction;
	Vec3 color;
	
	Vec3 light_x;
	Vec3 light_y;
	
	float intensity;
};