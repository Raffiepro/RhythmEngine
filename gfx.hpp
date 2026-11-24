#pragma once
#include <SDL3/SDL.h>
//#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int width=1280, height=720;
float deltaTime = 1.f;

SDL_Texture* arrowsUnlit;
SDL_Texture* arrowsLit;

enum class Input {
    None,
    Left,
    Right,
    Up,
    Down,
    Accept
};
Input input;

static const bool* keys = SDL_GetKeyboardState(NULL);
bool keyHeld(SDL_Scancode key) {
    return keys[key];
}
bool inputHeld(Input action) {
    switch (action) {
        case Input::Left: return keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_D];
        case Input::Down: return keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_F];
        case Input::Up: return keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_J];
        case Input::Right: return keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_K];
    }
    return false;
}

SDL_Texture* gfxLoadImage(const char* path) {
    SDL_Surface* surface = SDL_LoadPNG(path);
    if (!surface) {
        SDL_Log("Failed to load PNG: %s", SDL_GetError());
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}

void gfxInit(const char* name) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr<<"SDL failed to init video";
        exit(-2);
    }
    if (!SDL_CreateWindowAndRenderer("Rhythm Engine", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer)) { 
        std::cerr<<"SDL failed to create window and renderer";
        exit(-2);
    }
    //SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    //TTF_Init();

    arrowsUnlit = gfxLoadImage("assets/images/fnf_arrows.png");
    arrowsLit   = gfxLoadImage("assets/images/fnf_arrowsLIT.png");
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

void gfxArrows() {
    const float arrowWidth = width/3;
    const float arrowPosL = width*0.25f-arrowWidth/2;
    const float arrowPosR = width*0.75f-arrowWidth/2;
    
    SDL_FRect src_rect;
    src_rect.x = 0; src_rect.y = 0;
    SDL_FRect rect;
    rect.x = arrowPosL;     rect.y = height*0.9-arrowWidth*0.25;
    rect.w = arrowWidth;    rect.h = arrowWidth*0.25;
    SDL_RenderTexture(renderer, arrowsUnlit, NULL, &rect);

    src_rect.w = arrowsLit->w/4;
    src_rect.h = arrowsLit->h;
    rect.w = rect.w/4;
    if(inputHeld(Input::Left)) {
        SDL_RenderTexture(renderer, arrowsLit, &src_rect, &rect);
    }
    rect.x += rect.w;
    src_rect.x += src_rect.w;
    if(inputHeld(Input::Down)) {
        SDL_RenderTexture(renderer, arrowsLit, &src_rect, &rect);
    }
    rect.x += rect.w;
    src_rect.x += src_rect.w;
    if(inputHeld(Input::Up)) {
        SDL_RenderTexture(renderer, arrowsLit, &src_rect, &rect);
    }
    rect.x += rect.w;
    src_rect.x += src_rect.w;
    if(inputHeld(Input::Right)) {
        SDL_RenderTexture(renderer, arrowsLit, &src_rect, &rect);
    }
}