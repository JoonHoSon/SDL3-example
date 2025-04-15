//
// Created by JoonHo Son on 2025. 4. 15..
//

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Entity {
public:
    Entity(SDL_Renderer *renderer);
    virtual ~Entity();
    virtual void Update(float delta);
    virtual void Render(float delta);
    bool Collides(Entity *other);

    float x, y, width, height;

protected:
    SDL_Renderer *renderer;
};

#endif // ENTITY_H
