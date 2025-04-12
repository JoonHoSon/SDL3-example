#include <iostream>
#include <SDL3/SDL.h>

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_AudioSpec spec;
    Uint8 *wavData;
    Uint32 wavLen = 0;

    SDL_SetAppMetadata("SDL3 Sound(Wave) Test", "1.0.0", "net.opencreator.sdl3.example.sound");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Sound Test(Wave)", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());

        return 1;
    }

    // load wave file
    if (!SDL_LoadWAV("assets/sample.wav", &spec, &wavData, &wavLen)) {
        SDL_Log("Couldn't load .wav file: %s", SDL_GetError());

        return 1;
    }

    SDL_AudioStream *stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);

    if (!stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());

        return 1;
    }

    SDL_ResumeAudioStreamDevice(stream);

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                // 종료
                running = false;
            }
        }

        if (SDL_GetAudioStreamQueued(stream) < static_cast<int>(wavLen)) {
            SDL_PutAudioStreamData(stream, wavData, static_cast<int>(wavLen));
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }


    return 0;
}
