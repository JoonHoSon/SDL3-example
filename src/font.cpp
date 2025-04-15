#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "han2unicode.h"

static constexpr int screenWidth = 640;
static constexpr int screenHeight = 480;

int main() {
    std::cout << "Start font test." << std::endl;

    SDL_Window *window;
    SDL_Renderer *renderer;
    // const std::string fontName = "assets/온글잎 콘콘체.ttf";
    const std::string fontName = "assets/font.ttf";

    SDL_SetAppMetadata("SDL3 TTF Test", "1.0.0", "net.opencreator.sdl3.example.font");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

        return 1;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());

        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Font Test", screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, &window,
                                     &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());

        return 1;
    }

    const SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                                                   screenWidth,
                                                   screenHeight);

    if (texture == nullptr) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());

        return 1;
    }

    TTF_Font *font = TTF_OpenFont(fontName.c_str(), 30.0);

    if (font == nullptr) {
        SDL_Log("Couldn't open font: %s", SDL_GetError());

        return 1;
    }

    SDL_Color textColor = {0, 0, 0, 255};
    const std::string text = "한글 글꼴은 잘 나올까?";
    // SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), std::strlen(text.c_str()), textColor);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), std::strlen(text.c_str()), textColor);
    // SDL_Surface *textSurface = TTF_RenderUNICODE_Solid(font, text.c_str(), std::strlen(text.c_str()), textColor);
    SDL_Texture *mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int mWidth = textSurface->w;
    int mHeight = textSurface->h;

    // render text
    // SDL_Rect renderQuad = {10, 10, mWidth, mHeight};
    SDL_FRect renderQuad = {10.0f, 10.0f, static_cast<float>(mWidth), static_cast<float>(mHeight)};
    bool running = true;


    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                running = false;
            } else if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderTexture(renderer, mTexture, nullptr, &renderQuad);
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
