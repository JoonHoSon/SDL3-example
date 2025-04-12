#include <iostream>
#include <random>
#include <SDL3/SDL.h>

static constexpr int screenWidth = 640;
static constexpr int screenHeight = 480;

typedef struct {
    float x, y;
    float vx, vy;
    int lifetime;
} Particle;

void spawn_particle(Particle *particle, const int x, const int y, const int vx, const int vy, const int lifetime) {
    particle->x = static_cast<float>(x % screenWidth);
    particle->y = static_cast<float>(y % screenHeight);
    particle->vx = (static_cast<float>(vx) / screenWidth) * 2 - 1;
    particle->vy = (static_cast<float>(vy) / screenHeight) * 2 - 1;
    particle->lifetime = 60 * lifetime % 60;
}

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_SetAppMetadata("SDL3 Particles Test", "1.0.0", "net.opencreator.sdl3.example.particle");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Particle Test", screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, &window,
                                     &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return 1;
    }

    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution dist(1, screenWidth);
    Particle particles[100];
    bool running = true;

    for (auto &particle: particles) {
        spawn_particle(&particle, dist(mt), dist(mt), dist(mt), dist(mt), dist(mt));
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                running = false;
            } else if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (auto &particle: particles) {
            particle.x += particle.vx;
            particle.y += particle.vy;
            particle.lifetime--;

            if (particle.lifetime <= 0) {
                spawn_particle(&particle, dist(mt), dist(mt), dist(mt), dist(mt), dist(mt));
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderPoint(renderer, particle.x, particle.y);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
