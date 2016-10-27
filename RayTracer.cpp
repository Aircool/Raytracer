#include "RayTracer.h"

RayTracer::RayTracer(){
	
	Vec3 cam_pos = Vec3(0.0f, 0.0f, -50.0f);
	Vec3 cam_dir = Vec3(0.0f, 0.0f, 1.0f).normalized();
	camera = new Camera(cam_pos, cam_dir);
	
	surfaces.push_back(new Sphere(Vec3(0, 0, 0), 7.5f, Vec3(212, 225, 236), 1.0f, 0.0f));
	surfaces.push_back(new Sphere(Vec3(0, -15, 0), 5.0f, Vec3(0, 255, 0)));
	surfaces.push_back(new Sphere(Vec3(0, 15, 0), 5.0f, Vec3(0, 255, 0)));
	surfaces.push_back(new Sphere(Vec3(-15, 0, 0), 5.0f, Vec3(0, 255, 0)));
	surfaces.push_back(new Sphere(Vec3(15, 0, 0), 5.0f, Vec3(0, 255, 0)));
	
	surfaces.push_back(new Sphere(Vec3(-15, -15, 0), 5.0f, Vec3(0, 0, 255)));
	surfaces.push_back(new Sphere(Vec3(15, 15, 0), 5.0f, Vec3(0, 0, 255)));
	surfaces.push_back(new Sphere(Vec3(-15, 15, 0), 5.0f, Vec3(0, 0, 255)));
	surfaces.push_back(new Sphere(Vec3(15, -15, 0), 5.0f, Vec3(0, 0, 255)));

	surfaces.push_back(new Plane(Vec3(0, -50, 0), Vec3(0, 1, 0))); 
	
	//surfaces.push_back(new Triangle(Vec3(-400, -400, 50), Vec3(400, 400, 50), Vec3(-400, 400, 50), Vec3(255, 255, 100)));
	//surfaces.push_back(new Triangle(Vec3(400, -400, 50), Vec3(400, 400, 50), Vec3(-400, -400, 50), Vec3(255, 255, 100)));
	
	lights.push_back(new Light(Vec3(-10, -10, -30), Vec3(10, 10, 80).normalized(), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(-10, +10, -30), Vec3(10, -10, 80).normalized(), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(+10, -10, -30), Vec3(-10, 10, 80).normalized(), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(+10, +10, -30), Vec3(-10, -10, 80).normalized(), Vec3(255, 255, 255), 0.25));
}

Vec3 RayTracer::rayTrace(int x, int y){
	
	Vec3 color;
	
	if(ANTI_ALIAS_X > 1){
		
		for(float i = -ANTI_ALIAS_X + 1.0f; i < ANTI_ALIAS_X; i+=2.0f){
		for(float j = -ANTI_ALIAS_X + 1.0f; j < ANTI_ALIAS_X; j+=2.0f){
			
			Vec3 jitterVal = jitter(1.0f/ANTI_ALIAS_X);
			float jitterX = jitterVal[0] + i / (ANTI_ALIAS_X * ANTI_ALIAS_X);
			float jitterY = jitterVal[1] + j / (ANTI_ALIAS_X * ANTI_ALIAS_X);
			
			Ray3 ray = camera->castRay(x + jitterX, y + jitterY);
			color += rayTrace(ray);
			depth = 0;
		}
		}
		
		color /= (ANTI_ALIAS_X * ANTI_ALIAS_X);
	}
	
	else {
		
		Ray3 ray = camera->castRay(x, y);
		color += rayTrace(ray);
		depth = 0;
	}
	
	return color;
}

Vec3 RayTracer::rayTrace(Ray3 ray){
	
	Intersection intersection = intersect(ray);
	if(intersection.T > 0.0f){
		
		depth++;
		bool DO_REFLECT = ENABLE_REFLECTION * (depth < 5);
		bool DO_REFRACT = ENABLE_REFRACTION * (depth < 5);
		float originalColor = 1.0f - (DO_REFLECT * intersection.reflect) - (DO_REFRACT * intersection.refract);
		
		Vec3 color = intersection.C * originalColor;
		
		if(DO_REFLECT && intersection.reflect > 0.0f){
			
			color += rayTrace(Ray3(intersection.I, ray.D.reflect(intersection.N))) * intersection.reflect;
		}
		
		if(DO_REFRACT && intersection.refract > 0.0f){
			
			// Insert Refraction Logic.
		}
		
		intersection.C = color;
		return calculateColor(ray, intersection);
	}
	
	return Vec3();
}

Intersection RayTracer::intersect(Ray3 ray){
		
	Intersection closest;
		
	for(auto surface : surfaces){
			
		Intersection I = surface->intersect(ray);
				
		if(I.T > 0.0f){
			if(closest.T < 0.0f || I.T < closest.T) closest = I;
		}
	}

	return closest;
}

Vec3 RayTracer::calculateColor(Ray3 ray, Intersection intersection){

	Vec3 ambient = intersection.C * AMBIENT_COEFF;
	Vec3 lighting = Vec3();

	for(auto light : lights){

		lighting += light->calculateLighting(&surfaces, ray, intersection);
	}

	return ambient + lighting;
}