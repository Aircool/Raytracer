#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"

#include "Constants.h"
#include "VectorMath.h"
#include "RayTracer.h"

SDL_Window* window;
SDL_Renderer* renderer;

RayTracer* RT;

int render(void* ptr){
	
	for(int y = 0; y < HEIGHT; ++y){
		for(int x = 0; x < WIDTH; ++x){
			
			Vec3 color = RT->rayTrace(x, y);
			
			SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
		
		if(y % 10 == 9) SDL_RenderPresent(renderer);
	}
	
	return 0;
}

int main(int argc, char* argv[]){
	
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	RT = new RayTracer();
	
	SDL_Thread* thread = SDL_CreateThread(render, "Render", (void *)NULL);
	SDL_DetachThread(thread);
	
	SDL_Event event;
	while(1){
		
		SDL_WaitEvent(&event);
		
		if(event.type == SDL_QUIT) break;
		
		else if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_ESCAPE) break;
		}
	}
	
	SDL_Quit();
	return 0;
}