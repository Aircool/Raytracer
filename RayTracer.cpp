#include "RayTracer.h"

RayTracer::RayTracer(){
	
	Vec3 cam_pos = Vec3(0.0f, 0.0f, -10.0f);
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

	surfaces.push_back(new Triangle(Vec3(-200, -200, 10), Vec3(200, 200, 10), Vec3(-200, 200, 10), Vec3(255, 255, 0)));
	surfaces.push_back(new Triangle(Vec3(200, -200, 10), Vec3(200, 200, 10), Vec3(-200, -200, 10), Vec3(255, 255, 0)));
	
	lights.push_back(new Light(Vec3(-0.525, -0.025, -20), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(+0.525, -0.025, -20), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(-0.525, +0.025, -20), Vec3(255, 255, 255), 0.25));
	lights.push_back(new Light(Vec3(+0.525, +0.025, -20), Vec3(255, 255, 255), 0.25));
}

Vec3 RayTracer::rayTrace(int x, int y){
	
	Ray3 ray = camera->castRay(x, y);
	return rayTrace(ray);
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