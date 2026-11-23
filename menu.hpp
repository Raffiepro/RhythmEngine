#include "gfx.hpp"

enum MenuState {
    MENU_TITLE,
    MENU_STAGE
};

class Menu {
    int selected = 0;

    void option(int id, float x, float y, const char* text) {
        if(id==selected) {
            if(keyHeld(SDL_SCANCODE_SPACE)) {
                gfxTextRGB(x, y, text, 0, 0, 255);
                state = MENU_STAGE;
            }
            else
                gfxTextRGB(x, y, text, 255, 255, 0);
        }
        else gfxTextRGB(x, y, text, 255, 255, 255);
    }

    public:
    MenuState state = MENU_TITLE;

    void update() {
        if (input==Input::Up && selected>0) selected--; 
        if (input==Input::Down && selected<2) selected++; 
    }
    void draw() {
        gfxClear(50,10,50);
        gfxTextRGB(0, 0, "Rhythm Engine V0.0.0.0.0.1", 20, 255, 255);
        option(0, 10, 20, "Start");
        option(1, 10, 30, "Ba");
        option(2, 10, 40, "Yee");
    }
};