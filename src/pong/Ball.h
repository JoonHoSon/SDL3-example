//
// Created by JoonHo Son on 2025. 4. 15..
//

#ifndef BALL_H
#define BALL_H

#include <math.h>
#include "Entity.h"

const float BALL_SPEED = 900;

class Ball : public Entity {
public:
    Ball(SDL_Renderer *renderer);
    ~Ball();

    void Update(float delta);
    void Render(float delta);
    void SetDirection(float dirX, float dirY);

    float dirX, dirY;

private:
    SDL_Texture *texture;
};


#endif // BALL_H
