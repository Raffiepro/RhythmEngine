#include "gfx.hpp"

enum MenuState {
    MENU_TITLE
};

class Menu {
    int selected = 0;
    MenuState state = MENU_TITLE;

    void option(int id, float x, float y, const char* text) {
        if(id==selected) {
            if(input==Input::Accept)
                gfxTextRGB(x, y, text, 0, 0, 255);
            else
                gfxTextRGB(x, y, text, 255, 255, 0);
        }
        else gfxTextRGB(x, y, text, 255, 255, 255);
    }

    public:

    void update() {
        if (input==Input::Up && selected>0) selected--; 
        if (input==Input::Down && selected<2) selected++; 
    }
    void draw() {
        gfxTextRGB(0, 0, "Rhythm Engine V0.0.0.0.0.1", 20, 255, 255);
        option(0, 10, 20, "Start");
        option(1, 10, 30, "Ba");
        option(2, 10, 40, "Yee");
    }
};