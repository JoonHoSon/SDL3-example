//
// Created by JoonHo Son on 2025. 4. 15..
//

#include "Paddle.h"

Paddle::Paddle(SDL_Renderer *renderer) : Entity(renderer) {
    SDL_Surface *surface = IMG_Load("assets/paddle.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    width = 32;
    height = 128;

    x = 0;
    y = 0;
}

Paddle::~Paddle() { SDL_DestroyTexture(texture); }

void Paddle::Update(float delta) {}

void Paddle::Render(float delta) {
    SDL_FRect rect;

    rect.x = x + 0.5f;
    rect.y = y + 0.5f;
    rect.w = width;
    rect.h = height;

    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
