#include <iostream>
#include <SDL3/SDL.h>

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_AudioSpec spec;
    SDL_AudioStream *stream;

    SDL_SetAppMetadata("SDL3 Sound Test", "1.0.0", "net.opencreator.sdl3.example.sound");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Sound Test", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());

        return 1;
    }

    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = 44100;
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);

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
    }


    return 0;
}
