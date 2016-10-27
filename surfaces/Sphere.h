#pragma once

#include "Surface.h"
#include "Intersection.h"
#include "../VectorMath.h"

class Sphere : public Surface {

public:

	Sphere(Vec3 center, float radius, Vec3 color) : center(center), radius(radius), Surface(color) {}
	Sphere(Vec3 center, float radius, Vec3 color, float reflect, float refract) : center(center), radius(radius), Surface(color, reflect, refract) {}

	Intersection intersect(Ray3 ray){
		
		Vec3 V = center - ray.O;
		
		float projection = V.dot(ray.D);
		float discriminant = (radius * radius) + (projection * projection) - (V.dot(V));
		
		/*
			This Works Because:
			
				1)	V.dot(V) is the squared length of the Hypotenuse of a triangle. (The edge from the Camera to Sphere Center)
				2)	projection^2 is the squared length of the base of a triangle.	(The edge from the Camera along Viewing Direction)
				3)	If (radius * radius) is larger than the remaining edge's squared length then:
					
					A)	The Discriminant is greater than 0, given Pythagorean Theorem.
					B)	The remaining edge's length is shorter than the radius of the circle,
						guaranteeing that the Ray intersects the Sphere
					
				4)	If (radius * radius) is smaller than the remaining edge's squared length then:
					
					A)	The Discriminant is less than 0, given Pythagorean Theorem.
					B)	The remaining edge's length is longer than the radius of the circle,
						guaranteeing that the Ray does not intersect the Sphere.
						
			Pythagorean Theorem:
			
				Squared Length of Hypotenuse - Squared Length of Edge A - Squared Length of Edge B = 0
				
				or rearranged
									
				Squared Length of Edge A + Squared Length of Edge B - Squared Length of Hypotenuse = 0
		*/
		
		if(discriminant < 0) return Intersection();
		
		float offset = sqrt(discriminant);
		float t1 = projection - offset;
		float t2 = projection + offset;
		
		if(t1 > 0.0f){
			
			Vec3 I = ray.pointAt(t1);
			Vec3 N = (I - center).normalized();
			return Intersection(I + (N * 1e-2), N, this->color, t1, this->reflect, this->refract);
		}
		
		if(t2 > 0.0f){
			
			Vec3 I = ray.pointAt(t2);
			Vec3 N = (I - center).normalized();
			return Intersection(I + (N * 1e-2), N, this->color, t2, this->reflect, this->refract);
		}
		
		return Intersection();
	}
	
	
private:

	Vec3 center;
	float radius;
};