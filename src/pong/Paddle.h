//
// Created by JoonHo Son on 2025. 4. 15..
//

#ifndef PADDLE_H
#define PADDLE_H


#include "Entity.h"


class Paddle : public Entity {
public:
    Paddle(SDL_Renderer *renderer);
    ~Paddle();

    void Update(float delta);
    void Render(float delta);

private:
    SDL_Texture *texture;
};


#endif // PADDLE_H
