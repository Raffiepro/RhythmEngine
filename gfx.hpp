#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int width=640, height=360;
float deltaTime = 1.f;

enum class Input {
    None,
    Left,
    Right,
    Up,
    Down,
    Accept
};
Input input;

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
    TTF_Init();
}

Uint64 last_time = SDL_GetPerformanceCounter();
bool gfxPoll() {
    SDL_RenderPresent(renderer);
    Uint64 current_time = SDL_GetPerformanceCounter();
    deltaTime = (float)(current_time - last_time) / 1000000000.0f;
    last_time = current_time;
    
    SDL_Event event;
    input = Input::None;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_LEFT: input = Input::Left; break;
                case SDLK_RIGHT: input = Input::Right; break;
                case SDLK_DOWN: input = Input::Down; break;
                case SDLK_UP: input = Input::Up; break;
                case SDLK_SPACE: input = Input::Accept; break;
                case SDLK_RETURN: input = Input::Accept; break;
            }
        }
    }
    return true;
}

void gfxClear(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r,g,b, 255);
    SDL_RenderClear(renderer);
}

// Using debug text for now
void gfxText(float x, float y, const char* text) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, text);
}
void gfxTextRGB(float x, float y, const char* text, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDebugText(renderer, x, y, text);
}