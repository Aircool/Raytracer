#include "RayTracer.h"

RayTracer::RayTracer(){
	
	Vec3 cam_pos = Vec3(0.0f, 0.0f, -100.0f);
	Vec3 cam_dir = Vec3(0.0f, 0.0f, 1.0f);
	camera = new Camera(cam_pos, cam_dir);
	
	
}

Vec3 RayTracer::rayTrace(int x, int y){
	
	Ray3 ray = camera->castRay(x, y);
	return rayTrace(ray);
}

Vec3 RayTracer::rayTrace(Ray3 ray){
	
	Vec3 color(0.0f, 0.0f, 0.0f);
	
	
	
	return color;
}