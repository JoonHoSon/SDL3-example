//
// Created by JoonHo Son on 2025. 4. 15..
//

#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <time.h>
#include "Entity.h"

class Board : public Entity {
public:
    Board(SDL_Renderer *renderer);
    ~Board();

    void Update(float delta);
    void Render(float delta);

    float boundTop, boundBottom;

private:
    SDL_Texture *sideTexture;
};


#endif // BOARD_H
