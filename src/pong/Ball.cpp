//
// Created by JoonHo Son on 2025. 4. 15..
//

#include "Ball.h"

Ball::Ball(SDL_Renderer *renderer) : Entity(renderer) {
    SDL_Surface *surface = IMG_Load("assets/ball.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    x = 0;
    y = 0;
    width = 24;
    height = 24;

    SetDirection(1, 1);
}

Ball::~Ball() {
    // clean resources
    SDL_DestroyTexture(texture);
}

void Ball::Update(float delta) {
    x += dirX * delta;
    y += dirY * delta;
}

void Ball::Render(float delta) {
    SDL_FRect rect;

    rect.x = x + 0.5f;
    rect.y = y + 0.5f;
    rect.w = width;
    rect.h = height;

    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}

void Ball::SetDirection(float dirX, float dirY) {
    float length = sqrt(dirX * dirX + dirY * dirY);
    this->dirX = BALL_SPEED * (dirX / length);
    this->dirY = BALL_SPEED * (dirY / length);
}
