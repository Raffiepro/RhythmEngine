#include "gfx.hpp"
#include "audio.hpp"

SDL_Texture* testdude;
SDL_Texture* background;
void loadStageAssets() {
    testdude = gfxLoadImage("assets/testdudeHD.png");
    background = gfxLoadImage("assets/stages/london.png");
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
        gfxClear(50, 50, 50);
        SDL_FRect rect;

        rect.x = width/2 - background->w/2; rect.y = height/2 - background->h/2;
        rect.w = background->w;             rect.h = background->h;
        SDL_RenderTexture(renderer, background, NULL, &rect);

        rect.x = width*0.125f;   rect.y = height*0.3;
        rect.w = width/2.5;     rect.h = width/2.5;
        SDL_FRect src_rect;
        src_rect.x = 0;     src_rect.y = 0;
        src_rect.w = testdude->w/5;    src_rect.h = testdude->h;
        SDL_RenderTexture(renderer, testdude, &src_rect, &rect);

        gfxArrows();
    }
};