#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

int main() {
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (!SDL_CreateWindowAndRenderer("SDL3 Image test", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		std::cout << "SDL_CreateWindowAndRenderer error => " << SDL_GetError() << std::endl;

		return 1;
	}

	// BMP image
	SDL_Surface* helloImage = SDL_LoadBMP("assets/kagura.bmp");


	// JPEG image
	//SDL_Surface* helloImage = IMG_Load("gintoki.jpg");

	if (helloImage == 0) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		std::cout << "SDL_LoadBMP error => " << SDL_GetError() << std::endl;

		return 1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, helloImage);

	//SDL_FreeSurface(helloBMP); // 메모리 해제
	SDL_DestroySurface(helloImage); // 메모리 해제

	if (texture == 0) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		std::cout << "SDL_CreateTextureFromSurface error => " << SDL_GetError() << std::endl;

		return 1;
	}

	bool running = true;

	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
				running = false;
			}
			else if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		SDL_RenderClear(renderer);
		//SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderTexture(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}