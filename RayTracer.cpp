#include "RayTracer.h"

RayTracer::RayTracer(){
	
	Vec3 cam_pos = Vec3(0.0f, 0.0f, -50.0f);
	Vec3 cam_dir = Vec3(0.0f, 0.0f, 1.0f).normalized();
	camera = new Camera(cam_pos, cam_dir);
	
	surfaces.push_back(new Sphere(Vec3(0, 0, 0), 5.0f, Vec3(255, 0, 0)));
	surfaces.push_back(new Sphere(Vec3(0, -15, 0), 5.0f, Vec3(0, 255, 0)));
	surfaces.push_back(new Sphere(Vec3(0, 15, 0), 5.0f, Vec3(0, 255, 0)));
	surfaces.push_back(new Sphere(Vec3(-15, 0, 0), 5.0f, Vec3(0, 255, 0)));
	surfaces.push_back(new Sphere(Vec3(15, 0, 0), 5.0f, Vec3(0, 255, 0)));
	
	surfaces.push_back(new Sphere(Vec3(-15, -15, 0), 5.0f, Vec3(0, 0, 255)));
	surfaces.push_back(new Sphere(Vec3(15, 15, 0), 5.0f, Vec3(0, 0, 255)));
	surfaces.push_back(new Sphere(Vec3(-15, 15, 0), 5.0f, Vec3(0, 0, 255)));
	surfaces.push_back(new Sphere(Vec3(15, -15, 0), 5.0f, Vec3(0, 0, 255)));

	surfaces.push_back(new Triangle(Vec3(-200, -200, 10), Vec3(200, 200, 10), Vec3(-200, 200, 10), Vec3(255, 255, 100)));
	surfaces.push_back(new Triangle(Vec3(200, -200, 10), Vec3(200, 200, 10), Vec3(-200, -200, 10), Vec3(255, 255, 100)));
	
	lights.push_back(new Light(Vec3(-10.50, 49.00, -30), Vec3(0.15, -0.30, 0.40).normalized(), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(-10.00, 49.00, -30), Vec3(0.15, -0.30, 0.40).normalized(), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(-10.50, 49.1, -30), Vec3(0.15, -0.30, 0.40).normalized(), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(-10.00, 49.1, -30), Vec3(0.15, -0.30, 0.40).normalized(), Vec3(255, 255, 255), 0.25));
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
		}
		}
		
		color /= (ANTI_ALIAS_X * ANTI_ALIAS_X);
	}
	
	else {
		
		Ray3 ray = camera->castRay(x, y);
		color += rayTrace(ray);
	}
	
	return color;
}

Vec3 RayTracer::rayTrace(Ray3 ray){
	
	Vec3 color(0.0f, 0.0f, 0.0f);
	
	Intersection intersection = intersect(ray);
	if(intersection.T > 0.0f){
		
		color += calculateColor(ray, intersection);
	}
	
	return color;
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