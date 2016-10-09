#pragma once

#include "Surface.h"
#include "Intersection.h"
#include "../VectorMath.h"

class Triangle : public Surface {

public:

	Triangle(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 color) : p0(p0), p1(p1), p2(p2), Surface(color) {
		
		normal = ((p2 - p0).cross(p1 - p0));
		totalArea = normal.norm();
		normal.normalize();
	}
	
	Intersection intersect(Ray3 ray){
		
		float angle = normal.dot(ray.D);
		if(fabs(angle) > 1e-4){
			
			float T = (p0 - ray.O).dot(normal) / angle;
			if(T > 1e-4){
				
				Vec3 I = (ray.O) + (ray.D * T);
				
				float alpha	= area(I, p1, p2) / totalArea;
				float beta	= area(I, p0, p2) / totalArea;
				float gamma = area(I, p0, p1) / totalArea;
				
				if(alpha < 0.0f || alpha > 1.0f) return Intersection();
				if(beta  < 0.0f || beta  > 1.0f) return Intersection();
				if(gamma < 0.0f || gamma > 1.0f) return Intersection();
				
				if(1.0f - alpha - beta - gamma > -1e-4){
					
					return Intersection(I, normal, this->color, T);
				}
			}
		}
		
		return Intersection();
	}
	
	float area(Vec3 v0, Vec3 v1, Vec3 v2){
		
		return (v2 - v0).cross(v1 - v0).norm();
	}

private:

	Vec3 p0;
	Vec3 p1;
	Vec3 p2;
	Vec3 normal;
	
	float totalArea;

};