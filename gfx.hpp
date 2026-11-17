#pragma once
#include <SDL3/SDL.h>
#include <iostream>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int width=640, height=360;
float deltaTime = 1.f;

void gfxInit(const char* name) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr<<"SDL failed to init video";
        exit(-2);
    }
    if (!SDL_CreateWindowAndRenderer("Rhythm Engine", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer)) { 
        std::cerr<<"SDL failed to create window and renderer";
        exit(-2);
    }
    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

Uint64 last_time = SDL_GetPerformanceCounter();
bool gfxPoll() {
    Uint64 current_time = SDL_GetPerformanceCounter();
    deltaTime = (float)(current_time - last_time) / 1000000000.0f;
    last_time = current_time;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            /*switch (event.key.key) {
                case SDLK_LEFT: input = Input::Left; break;
                case SDLK_RIGHT: input = Input::Right; break;
                case SDLK_DOWN: input = Input::Down; break;
                case SDLK_UP: input = Input::Up; break;
            }*/
        }
    }
    return true;
}