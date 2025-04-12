#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_AudioSpec spec;

    SDL_SetAppMetadata("SDL3 Sound(MP3) Test", "1.0.0", "net.opencreator.sdl3.example.sound");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Sound Test(MP3)", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());

        return 1;
    }

    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;

    if (!Mix_OpenAudio(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec)) {
        SDL_Log("Couldn't open audio: %s", SDL_GetError());

        return 1;
    }

    Mix_QuerySpec(&spec.freq, &spec.format, &spec.channels);

    Mix_Music *music = Mix_LoadMUS("assets/sample.mp3");

    if (music == nullptr) {
        SDL_Log("Couldn't load mp3 file: %s", SDL_GetError());

        return 1;
    }

    // Mix_FadeInMusic(music, 3, 1000);

    Mix_PlayMusic(music, 2);
    Mix_VolumeMusic(2);


    double loop_start = Mix_GetMusicLoopStartTime(music);
    double loop_end = Mix_GetMusicLoopEndTime(music);
    double loop_length = Mix_GetMusicLoopLengthTime(music);

    SDL_Log("Loop points: start %gs, end %gs, length %gs", loop_start, loop_end, loop_length);

    while (Mix_PlayingMusic()) {
        const double current_position = Mix_GetMusicPosition(music);

        SDL_Log("Current position: %gs", current_position);
        SDL_Delay(200);
    }

    Mix_FreeMusic(music);
    music = nullptr;

    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
