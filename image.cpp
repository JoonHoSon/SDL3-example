#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

int main() {
	SDL_Window* window;
	SDL_Renderer* renderer;
	constexpr int width = 640;
	constexpr int height = 480;
	constexpr int imageWidth = 200;
	constexpr int imageHeight = 200;

	if (!SDL_CreateWindowAndRenderer("SDL3 Image test", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		std::cout << "SDL_CreateWindowAndRenderer error => " << SDL_GetError() << std::endl;

		return 1;
	}

	// BMP image
	SDL_Surface* leftImage = SDL_LoadBMP("assets/kagura.bmp");

	if (leftImage == nullptr) {
		SDL_DestroySurface(leftImage); // 메모리 해제
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		std::cout << "Left image load fail [assets/kagura.bmp] => " << SDL_GetError() << std::endl;

		return 1;
	}

	SDL_Texture* leftTexture = SDL_CreateTextureFromSurface(renderer, leftImage);
	SDL_FRect leftTarget = { static_cast<float>(width) / 4 - static_cast<float>(imageWidth) / 2, static_cast<float>(height) / 2 - static_cast<float>(imageHeight) / 2 , static_cast<float>(imageWidth), static_cast<float>(imageHeight)};

	SDL_DestroySurface(leftImage); // 메모리 해제

	if (leftTexture == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		std::cout << "SDL_CreateTextureFromSurface error => " << SDL_GetError() << std::endl;

		return 1;
	}

	// JPG image
	SDL_Surface* rightImage = IMG_Load("assets/gintama.jpg");

	if (rightImage == nullptr) {
		SDL_DestroySurface(rightImage);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		std::cout << "Right image load fail [assets/gintama.jpg] => " << SDL_GetError() << std::endl;

		return 1;
	}

	SDL_Texture* rightTexture = SDL_CreateTextureFromSurface(renderer, rightImage);
	SDL_FRect rightTarget = { static_cast<float>(width) / 4 * 3 - static_cast<float>(imageWidth) / 2, static_cast<float>(height / 2) - static_cast<float>(imageHeight) / 2, static_cast<float>(imageWidth), static_cast<float>(imageHeight) };

	SDL_DestroySurface(rightImage); // 메모리 해제

	if (rightTexture == nullptr) {
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
		//SDL_RenderTexture(renderer, leftTexture, nullptr, nullptr);
		SDL_RenderTexture(renderer, leftTexture, nullptr, &leftTarget);
		SDL_RenderTexture(renderer, rightTexture, nullptr, &rightTarget);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(leftTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}