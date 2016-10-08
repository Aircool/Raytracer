#include "SDL2/SDL.h"

#include "Constants.h"

SDL_Window* window;
SDL_Renderer* renderer;

void render(){
	
	for(int y = 0; y < HEIGHT; ++y){
		for(int x = 0; x < WIDTH; ++x){
			
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
		
		SDL_RenderPresent(renderer);
	}
}

int main(int argc, char* argv[]){
	
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	render();
	
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