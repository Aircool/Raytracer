#pragma once

#include "Surface.h"
#include "Intersection.h"
#include "../VectorMath.h"

class Plane : public Surface {

public:

	Plane(Vec3 point, Vec3 normal, Vec3 color) : point(point), normal(normal), color(color) {}
	
	Plane(Vec3 point, Vec3 normal, bool checkerBoard) : point(point), normal(normal), checkerBoard(checkerBoard) {
		
		Vec3 up(0.0f, 1.0f, 0.0f);
		if(normal[0] == up[0] && normal[1] == up[1] && normal[2] == up[2]) up = Vec3(0, 0, -1.0f);
		
		Vec3 ux = up.cross(normal).normalized();
		Vec3 uz = normal;
		Vec3 uy = uz.cross(ux);
		
		plane_x = ux;
		plane_y = uy;
	}

	Intersection intersect(Ray3 ray){
		
		float angle = ray.D.dot(normal);
		if(fabs(angle) > 1e-4){
			
			float T = (point - ray.O).dot(normal) / angle;
			if(T > 1e-4){
				
				if(!checkerBoard) return Intersection(ray.pointAt(T) + (1e-2 * normal), normal, color, T);
				else {
					
					Vec3 offsetFromPoint = (ray.pointAt(T) - point);
					
					float tX = offsetFromPoint.dot(plane_x).norm();
					float tY = offsetFromPoint.dot(plane_y).norm();
					
					int colorX = ((int) tX) / 5;
					int colorY = ((int) tY) / 5;
				}
				
				return Intersection()
			}
		}
		
		return Intersection();
	}
	
private:

	Vec3 point;
	Vec3 normal;
	Vec3 color;
	
	Vec3 plane_x;
	Vec3 plane_y;
	
	bool checkerBoard;
};