//
// Created by JoonHo Son on 2025. 4. 15..
//

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Board.h"
#include "Paddle.h"

#define FPS_DELAY 500
#define AI_SPEED 400


class Game {
public:
    Game();
    ~Game();

    bool Init();
    void Run();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    unsigned int lastTick, fpsTick, fps, frameCount;

    Board *board;
    std::vector<Paddle *> paddle;
    Ball *ball;

    void Clean() const;
    void Update(float delta);
    void Render(float delta);

    void NewGame();

    void SetPaddleY(int index, float y);
    void CheckCollisions();
    float GetReflection(int index, float hitY);

    void AI(float delta);
};


#endif // GAME_H
