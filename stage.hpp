#include "gfx.hpp"
#include "audio.hpp"

SDL_Texture* testdude;
SDL_Texture* arrowsUnlit;
SDL_Texture* arrowsLit;
void loadStageAssets() {
    SDL_Surface* surface = SDL_LoadPNG("assets/testdudeHD.png");
    if (!surface) {
        SDL_Log("Failed to load PNG: %s", SDL_GetError());
    }
    testdude = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    surface = SDL_LoadPNG("assets/images/fnf_arrows.png");
    if (!surface) {
        SDL_Log("Failed to load PNG: %s", SDL_GetError());
    }
    arrowsUnlit = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    surface = SDL_LoadPNG("assets/images/fnf_arrowsLIT.png");
    if (!surface) {
        SDL_Log("Failed to load PNG: %s", SDL_GetError());
    }
    arrowsLit = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

class Stage {
    Sound inst;
    Sound voices;
    
    public:

    Stage(std::string song_title) {
        inst.loadFile(("assets/songs/"+song_title+"/Inst.flac").c_str());
        voices.loadFile(("assets/songs/"+song_title+"/Voices.flac").c_str());
    }
    ~Stage() {
        SDL_DestroyTexture(testdude);
    }

    void start() {
        inst.start();
        voices.start();
    }

    void update() {

    }

    void draw() {

        float arrowWidth = 640*0.75;
        float arrowPosL = width/4-arrowWidth/2;
        float arrowPosR = width*0.75f-arrowWidth/2;

        gfxClear(50, 50, 50);
        SDL_FRect rect;
        rect.x = 0;     rect.y = height*0.6;
        rect.w = width; rect.h = height*0.4;
        SDL_SetRenderDrawColor(renderer, 100, 50, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        rect.x = 0;     rect.y = height*0.3;
        rect.w = width/3;    rect.h = width/3;
        SDL_FRect src_rect;
        src_rect.x = 0;     src_rect.y = 0;
        src_rect.w = testdude->w/5;    src_rect.h = testdude->h;
        SDL_RenderTexture(renderer, testdude, &src_rect, &rect);

        rect.x = arrowPosL;     rect.y = height-arrowWidth*0.25;
        rect.w = arrowWidth;    rect.h = arrowWidth*0.25;
        SDL_RenderTexture(renderer, arrowsLit, NULL, &rect);
        rect.x = arrowPosR;
        SDL_RenderTexture(renderer, arrowsLit, NULL, &rect);
    }
};