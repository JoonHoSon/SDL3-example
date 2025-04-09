#include <iostream>
#include <array>
#include <SDL3/SDL.h>

SDL_Color green{0, 255, 0, 255};
SDL_Color purple{255, 0, 255, 255};

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    constexpr int width = 640;
    constexpr int height = 480;
    constexpr float rectWidth = 100.0f;
    constexpr float rectHeight = 100.0f;

    if (!SDL_CreateWindowAndRenderer("SDL3 Window", width, height,
                                     SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        std::cerr << "SDL_CreateWindowAndRenderer error => " << SDL_GetError()
                << std::endl;

        return 1;
    }

    SDL_SetWindowTitle(window, "Screen flip example");

    int lastTickCount = static_cast<int>(SDL_GetTicks());
    int color = 0;
    bool running = true;
    std::array<SDL_FRect, 2> rects = {};

    rects[0] = {
        static_cast<float>(width) / 2 / 2 - rectWidth / 2,
        static_cast<float>(height) / 2 - rectHeight / 2, rectWidth, rectHeight
    };
    rects[1] = {
        static_cast<float>(width) / 2 + rectWidth,
        static_cast<float>(height) / 2 - rectHeight / 2, rectWidth, rectHeight
    };

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN) {
                std::cout << "Key pressed : " << SDL_GetKeyName(event.key.key)
                        << std::endl;

                if (event.key.key == SDLK_ESCAPE) {
                    running = false;
                }
            } else if (event.type == SDL_EVENT_KEY_UP) {
                std::cout << "Key released : " << SDL_GetKeyName(event.key.key)
                        << std::endl;
            } else if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        int currentTickCount = static_cast<int>(SDL_GetTicks());

        if (currentTickCount - lastTickCount > 1000) {
            color++;
            color = color % 2;
            lastTickCount = currentTickCount;
        }

        // SDL_RenderClear(renderer);

        if (color == 0) {
            SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
        } else {
            SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
        }

        // SDL_RenderFillRect(renderer, &rect);
        SDL_RenderFillRects(renderer, rects.data(), 2);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
