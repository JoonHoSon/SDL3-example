//
// Created by JoonHo Son on 2025. 4. 15..
//

#include "Board.h"

Board::Board(SDL_Renderer *renderer) : Entity(renderer) {
    SDL_Surface *surface = IMG_Load("assets/side.png");
    sideTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    srand(time(NULL));

    x = 0;
    y = 0;
    width = 800;
    height = 600;

    boundTop = 21;
    boundBottom = 600 - 21;
}

Board::~Board() { SDL_DestroyTexture(sideTexture); }

void Board::Update(float delta) {}

void Board::Render(float delta) {
    SDL_FRect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 800;
    rect.h = 21;

    SDL_RenderTexture(renderer, sideTexture, nullptr, &rect);

    rect.x = 0;
    rect.y = 600 - 21;
    rect.w = 800;
    rect.h = 21;

    SDL_RenderTexture(renderer, sideTexture, nullptr, &rect);
}
